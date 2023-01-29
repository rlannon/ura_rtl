#pragma once

#include "actor.hxx"
#include "queue.hxx"

#include "rtl.hxx"

URA_RTL_BEGIN

class EventLoop: public Actor
{
    Queue _queue;

    virtual void sendMessageInternal(Message& m) override
    {
        _queue.enqueue(m);
    }

public:
    EventLoop() : Actor(Actor::Type::EVENT_LOOP, true, true) { }
};

URA_RTL_END
