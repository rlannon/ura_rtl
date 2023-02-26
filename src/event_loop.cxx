#include "event_loop.hxx"

URA_RTL_BEGIN

void EventLoop::sendMessageInternal(Message& m)
{
    _queue.enqueue(m);
}

void EventLoop::onExecute()
{
    eventLoop();

    Message m = _queue.nextMessage();
    handleMessage(m);    
}

EventLoop::EventLoop(const std::chrono::milliseconds interval)
    : Timer(interval,
            Actor::Type::EVENT_LOOP,
            true,
            true) { }

EventLoop::~EventLoop() { }

URA_RTL_END
