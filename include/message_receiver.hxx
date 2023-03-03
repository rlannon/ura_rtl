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
        ACTOR,
    };

    Type getType() const
    {
        return _type;
    }

    MessageReceiver(const Type type) : _type(type) { }
    virtual ~MessageReceiver() { }

    virtual void sendMessage(Message& m) = 0;   // todo: should we alter this to allow const Message& ?
                                                // The problem lies with needing to message the return address...
                                                // We could get around that with `mutable`, but that seems like a code smell

private:
    Type _type;

};

URA_RTL_END
