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
        std::lock_guard<std::mutex> guard(_queue_lock);
        _queue.push_back(m);
    }
}

void EventLoop::onExecute()
{
    eventLoop();

    std::lock_guard<std::mutex> guard(_queue_lock);

    while (!_queue.empty())
    {
        Message m = _queue.front();
        _queue.pop_front();
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
