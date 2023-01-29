#pragma once

#include "actor.hxx"

#include "rtl.hxx"

URA_RTL_BEGIN

class Timer: public Actor
{
public:
    Timer() : Actor(Actor::Type::TIMER, false, false) { }
};

URA_RTL_END
