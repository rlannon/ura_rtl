#include "event_loop.hxx"
#include "rtl.hxx"
#include "codes/start.hxx"
#include "codes/stop.hxx"

URA_RTL_BEGIN

void EventLoop::sendMessageInternal(Message& m)
{
    if (!running() && 
        m.getType() == Message::Type::START &&
        m.getCode() == Codes::Start::START_ACTOR)
    {
        start();
    }
    else if (running() &&
            m.getType() == Message::Type::STOP &&
            m.getCode() == Codes::Stop::STOP_ACTOR)
    {
        stop();
    }
    else
    {
        _queue.enqueue(m);
    }
}

void EventLoop::onExecute()
{
    eventLoop();

    if (_queue.hasMessages())
    {
        Message m = _queue.nextMessage();
        handleMessage(m);
    }
}

EventLoop::EventLoop(const std::chrono::milliseconds interval)
    : Timer(interval,
            Actor::Type::EVENT_LOOP,
            true,
            true) { }

EventLoop::~EventLoop() { }

URA_RTL_END
