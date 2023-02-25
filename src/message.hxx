#pragma once

#include "generic.hxx"

#include "rtl.hxx"

URA_RTL_BEGIN

class Actor;

class Message
{
public:
    enum class Type: int
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

    Generic getValue()
    {
        return _value;
    }

    Type getType()
    {
        return _type;
    }

    unsigned int getCode()
    {
        return _code;
    }

    Message copy() const
    {
        return Message(*this);
    }

    Message(const Message& other)
        : Message(other._sender, other._return_address, other._type, other._value, other._code)
    {
    }

    Message(Actor* sender, Actor* returnAddress, Type type, Generic value, unsigned int code)
        : _sender(sender)
        , _return_address(returnAddress)
        , _type(type)
        , _value(value)
        , _code(code) { }
    
    ~Message() { }

private:
    Actor* _sender;
    Actor* _return_address;

    Generic _value;
    Type _type;
    unsigned int _code;
};

URA_RTL_END
