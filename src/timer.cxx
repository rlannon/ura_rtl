#include "timer.hxx"
#include "codes.hxx"

#include <any>
#include <chrono>

URA_RTL_BEGIN

using ura::messaging::Message;

void Timer::processEventLoop()
{
    while (_running)
    {
        onExecute();
        
        {
            std::unique_lock<std::mutex> lock(_done_mx);
            _done_cv.wait_until(lock, std::chrono::system_clock::now() + _interval, [&]() -> bool
            {
                return !_running || hasUrgentMessage();
            });
        }
    }

    return;
}

void Timer::sendMessageInternal(Message& m)
{
    // Only respond to START and STOP messages
    // All others should be ignored
    if (m.getType() == Message::Type::START)
    {
        start();
    }
    else if (m.getType() == Message::Type::STOP)
    {
        stop();
    }
    else
    {
        return;
    }

    // send an acknowledgement message back
    //
    // todo: allow error messages to be ignored here...we don't want to
    // create a situation where two threads continually message each other
    // that they can't accept messages
    //
    if (m.getReturnAddress())
    {
        Message ack(nullptr,
                    Message::Type::RESPONSE,
                    0,
                    StandardCodes::ACKNOWLEDGE);

        m.getReturnAddress()->sendMessage(ack);
    }
}

bool Timer::hasUrgentMessage()
{
    return false;
}

void Timer::notifyThreadUrgentMessage()
{
    _done_cv.notify_one();
}

void Timer::start(const uint8_t priority)
{
    {
        std::lock_guard<std::mutex> guard(_running_lock);
        _running = true;
        
        if (priority == ura::messaging::priority::URGENT)
        {
            notifyThreadUrgentMessage();
        }
    }

    _thread = std::thread(&Timer::processEventLoop, this);
}

void Timer::stop(const uint8_t priority)
{
    {
        std::lock_guard<std::mutex> guard(_running_lock);
        _running = false;
        
        if (priority == ura::messaging::priority::URGENT)
        {
            notifyThreadUrgentMessage();
        }
    }

    _thread.join();
}

Timer::Timer(   const std::chrono::milliseconds interval,
                const Actor::Type type,
                const bool use_queue,
                const bool has_public_queue )
    : Actor(type, use_queue, has_public_queue)
    , _interval(interval)
    , _running(false)
{
}

Timer::Timer(const std::chrono::milliseconds interval)
    : Actor(Actor::Type::TIMER, false, false)
    , _interval(interval)
    , _running(false)
{
}

Timer::~Timer()
{
    if (_running)
    {
        stop();
    }
}

URA_RTL_END
