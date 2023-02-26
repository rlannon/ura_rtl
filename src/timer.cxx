#include "timer.hxx"
#include "error_codes.hxx"

URA_RTL_BEGIN

void Timer::processEventLoop()
{
    while (_running)
    {
        _callback();
        std::this_thread::sleep_for(_interval);
    }

    return;
}

void Timer::sendMessageInternal(Message& m)
{
    Actor* sender = m.getSender();
    if (sender)
    {
        Message err(this, nullptr, Message::Type::ERROR, Generic(), ErrorCodes::CANNOT_RECEIVE_MESSAGES);
        sender->sendMessage(std::move(err));
    }

    return;
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

Timer::Timer(   std::function<void()> callback,
                const std::chrono::milliseconds interval,
                const Actor::Type type,
                const bool use_queue,
                const bool has_public_queue )
    : Actor(type, use_queue, has_public_queue)
    , _callback(callback)
    , _interval(interval)
    , _running(false)
{
}

Timer::Timer(std::function<void()> callback, const std::chrono::milliseconds interval)
    : Actor(Actor::Type::TIMER, false, false)
    , _callback(callback)
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
