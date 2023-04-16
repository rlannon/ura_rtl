#include "event_loop.hxx"
#include "rtl.hxx"
#include "codes.hxx"

URA_RTL_BEGIN

void EventLoop::sendMessageInternal(messaging::Message& m)
{
    if (!running() && 
        m.getType() == messaging::Message::Type::START &&
        m.getCode() == StandardCodes::START_ACTOR)
    {
        start(m.getPriority());
    }
    else if (running() &&
            m.getType() == messaging::Message::Type::STOP &&
            m.getCode() == StandardCodes::STOP_ACTOR)
    {
        stop(m.getPriority());
    }
    else
    {
        std::lock_guard<std::mutex> guard(_queue_lock);

        if (m.getPriority() == messaging::priority::URGENT)
        {
            notifyThreadUrgentMessage();
            _queue.push_front(m);
        }
        else
        {
            _queue.push_back(m);
        }
    }
}

void EventLoop::onExecute()
{
    eventLoop();

    std::lock_guard<std::mutex> guard(_queue_lock);

    while (!_queue.empty())
    {
        messaging::Message m = _queue.front();
        _queue.pop_front();
        
        messaging::Message response = handleMessage(m);

        if (m.getReturnAddress())
        {
            m.getReturnAddress()->sendMessage(response);
        }
    }
}

bool EventLoop::hasUrgentMessage()
{
    std::lock_guard<std::mutex> guard(_queue_lock);

    if (_queue.empty())
    {
        return false;
    }

    return _queue.front().getPriority() == messaging::priority::URGENT;
}

EventLoop::EventLoop(const std::chrono::milliseconds interval)
    : Timer(interval,
            Actor::Type::EVENT_LOOP,
            true,
            true) { }

EventLoop::~EventLoop()
{
    if (running())
    {
        stop();
    }
}

URA_RTL_END
