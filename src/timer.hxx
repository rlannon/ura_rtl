#pragma once

#include "actor.hxx"

namespace ura
{

class Timer: public Actor
{
public:
    Timer() : Actor(Actor::Type::TIMER, false, false) { }
};

}   /* namespace ura */
