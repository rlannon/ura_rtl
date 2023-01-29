#pragma once

#include "generic.hxx"

#include "rtl.hxx"

URA_RTL_BEGIN

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

    Message copy() const
    {
        return Message(_sender, _return_address, _type, _value.copy(), _code);
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

URA_RTL_END
