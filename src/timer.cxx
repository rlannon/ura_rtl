#include "timer.hxx"

URA_RTL_BEGIN

void Timer::processEventLoop()
{
    // todo: execute timer code here...
    // invoke _callback() at interval...
    return;
}

void Timer::sendMessageInternal(Message& m)
{
    return;
}

Timer::Timer(void (*callback)(), const uint64_t interval)
    : Actor(Actor::Type::TIMER, false, false)
    , _callback(callback)
    , _interval(interval) { }

Timer::~Timer() { }

URA_RTL_END
