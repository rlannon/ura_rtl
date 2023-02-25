#include "event_loop.hxx"

URA_RTL_BEGIN

void EventLoop::sendMessageInternal(Message& m)
{
    _queue.enqueue(m);
}

void EventLoop::eventHandler()
{
    _main_event();
    _message_handler(_queue);    
}

EventLoop::EventLoop(   std::function<void()> main_event,
                        std::function<void(Queue& message_queue)> message_handler,
                        const std::chrono::milliseconds interval)
    : Timer([this]() { this->eventHandler(); },
            interval,
            Actor::Type::EVENT_LOOP,
            true,
            true)
    , _main_event(main_event)
    , _message_handler(message_handler) { }

EventLoop::~EventLoop() { }

URA_RTL_END
