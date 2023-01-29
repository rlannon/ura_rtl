#pragma once

#include "message.hxx"

#include "rtl.hxx"

URA_RTL_BEGIN

class Actor
{
public:
    enum class Type
    {
        TIMER,
        EVENT_LOOP,
        LISTENER
    };

    virtual void sendMessage(Message m)
    {
        if (canSendMessage(m))
        {
            sendMessageInternal(m);
        }
    }

    virtual void start() = 0;

    Type getType() const
    {
        return _type;
    }

    bool useQueue() const
    {
        return _use_queue;
    }

    bool hasPublicQueue() const
    {
        return _has_public_queue;
    }

protected:
    Actor(const Type type, const bool useQueue, const bool hasPublicQueue)
        : _type(type)
        , _use_queue(useQueue)
        , _has_public_queue(hasPublicQueue) { }

    virtual void processEventLoop() = 0;
    
    virtual void sendMessageInternal(Message& m) { };

    bool canSendMessage(Message& m)
    {
        if (_has_public_queue)
        {
            return true;
        }
        else
        {
            Generic value;
            Message error_message(this, nullptr, Message::Type::ERROR, value, 0);

            m.getSender()->sendMessage(error_message);

            return false;
        }
    }

private:
    Type _type;
    bool _use_queue;
    bool _has_public_queue;
};

URA_RTL_END
