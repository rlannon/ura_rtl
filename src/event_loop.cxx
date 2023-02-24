#include "event_loop.hxx"

URA_RTL_BEGIN

void EventLoop::sendMessageInternal(Message& m)
{
    _queue.enqueue(m);
}

void EventLoop::start()
{
    // todo: run event loop...
}

EventLoop::EventLoop()
     : Actor(Actor::Type::EVENT_LOOP, true, true) { }

URA_RTL_END
