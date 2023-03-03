#include "timer.hxx"
#include "codes/error.hxx"
#include "codes/response.hxx"

#include <any>

URA_RTL_BEGIN

void Timer::processEventLoop()
{
    while (_running)
    {
        onExecute();
        std::this_thread::sleep_for(_interval);
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
        Message ack(this,
                    nullptr,
                    Message::Type::RESPONSE,
                    0,
                    Codes::Response::Acknowledge);

        m.getReturnAddress()->sendMessage(ack);
    }
}

void Timer::start()
{
    {
        std::lock_guard<std::mutex> guard(_running_lock);
        _running = true;
    }

    _thread = std::thread(&Timer::processEventLoop, this);
}

void Timer::stop()
{
    {
        std::lock_guard<std::mutex> guard(_running_lock);
        _running = false;
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
