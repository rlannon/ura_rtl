#pragma once

#include "rtl.hxx"

URA_RTL_BEGIN

class Message;

class MessageReceiver
{
public:
    enum class Type
    {
        PROMISE,
        QUEUE,
        ACTOR,
    };

    Type getType() const
    {
        return _type;
    }

    MessageReceiver(const Type type) : _type(type) { }
    virtual ~MessageReceiver() { }

    virtual void sendMessage(Message& m) = 0;

private:
    Type _type;

};

URA_RTL_END
