#include "timer.hxx"

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

Timer::Timer(void (*callback)(), const std::chrono::milliseconds interval)
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
