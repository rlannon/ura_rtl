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

    void sendMessage(Message m);

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
    Actor(const Type type, const bool useQueue, const bool hasPublicQueue);
    virtual ~Actor();

    virtual void processEventLoop() = 0;
    
    virtual void sendMessageInternal(Message& m) = 0;

    bool canSendMessage(Message& m);

private:
    Type _type;
    bool _use_queue;
    bool _has_public_queue;
};

URA_RTL_END
