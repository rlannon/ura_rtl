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

    const Actor* getSender() const
    {
        return _sender;
    }

    Actor* getSender()
    {
        return _sender;
    }

    const Actor* getReturnAddress() const
    {
        return _return_address;
    }

    Actor* getReturnAddress()
    {
        return _return_address;
    }

    Generic getValue() const
    {
        return _value.copy();
    }

    Type getType() const
    {
        return _type;
    }

    unsigned int getCode() const
    {
        return _code;
    }

    Message copy() const
    {
        return Message(*this);
    }

    Message(const Message& other);
    Message(Message&& other);
    Message(Actor* sender, Actor* returnAddress, Type type, Generic value, unsigned int code);
    
    ~Message();

private:
    Actor* _sender;
    Actor* _return_address;

    Generic _value;
    Type _type;
    unsigned int _code;
};

URA_RTL_END
