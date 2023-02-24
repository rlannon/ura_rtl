#pragma once

#include "actor.hxx"
#include "queue.hxx"

#include "rtl.hxx"

URA_RTL_BEGIN

class EventLoop: public Actor
{
    Queue _queue;

    virtual void sendMessageInternal(Message& m) override;

public:
    virtual void start() override;

    EventLoop();
};

URA_RTL_END
