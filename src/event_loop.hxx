#pragma once

#include "rtl.hxx"

#include "actor.hxx"
#include "queue.hxx"
#include "timer.hxx"

URA_RTL_BEGIN

class EventLoop: public Timer
{
    Queue _queue;
    std::function<void()> _main_event;
    std::function<void(Queue& message_queue)> _message_handler;

    virtual void sendMessageInternal(Message& m) override;
    void eventHandler();

public:
    EventLoop(  std::function<void()> main_event,
                std::function<void(Queue& message_queue)> message_handler,
                const std::chrono::milliseconds interval);
    virtual ~EventLoop();
};

URA_RTL_END
