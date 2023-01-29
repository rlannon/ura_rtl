#pragma once

#include "actor.hxx"

#include "rtl.hxx"

URA_RTL_BEGIN

class Listener: public Actor
{
    virtual void sendMessageInternal(Message& m) override
    {
        // todo: process message immediately
    }

public:
    Listener() : Actor(Actor::Type::LISTENER, false, true) { }
};

URA_RTL_END
