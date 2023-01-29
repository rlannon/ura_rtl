#pragma once

#include "generic.hxx"

namespace ura
{

class Actor;

class Message
{
public:
    enum class Type
    {
        OK,
        ERROR,
        START,
        STOP,
    };

    Actor* getSender()
    {
        return _sender;
    }

    Actor* getReturnAddress()
    {
        return _return_address;
    }

    Message(Actor* sender, Actor* returnAddress, Type type, Generic value, unsigned int code)
        : _sender(sender)
        , _return_address(returnAddress)
        , _type(type)
        , _value(value)
        , _code(code) { }

private:
    Actor* _sender;
    Actor* _return_address;

    Generic _value;
    Type _type;
    unsigned int _code;
};

}   /* namespace ura */
