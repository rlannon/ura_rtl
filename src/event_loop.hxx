#pragma once

#include "rtl.hxx"

#include "actor.hxx"
#include "queue.hxx"
#include "timer.hxx"

URA_RTL_BEGIN

class EventLoop: public Timer
{
    Queue _queue;
    
    virtual void sendMessageInternal(Message& m) override;
    virtual void onExecute() override;

protected:
    virtual void eventLoop() = 0;
    virtual void handleMessage(const Message& message) = 0;

public:
    EventLoop(const std::chrono::milliseconds interval);
    virtual ~EventLoop();
};

URA_RTL_END
