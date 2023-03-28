#pragma once

#include "rtl.hxx"
#include "message.hxx"
#include "message_receiver.hxx"

URA_RTL_BEGIN

class Actor: public MessageReceiver
{
public:
    enum class Type
    {
        TIMER,
        EVENT_LOOP,
        LISTENER
    };

    virtual void sendMessage(Message& m) override;

    /**
     * @brief Starts the actor's event loop and message processing.
     * 
     * Actors should also accept a START message to perform this function.
     */
    virtual void start() = 0;

    /**
     * @brief Stops the actor's event loop and message processing.
     * 
     * Actors should also accept a STOP message to perform this function.
     */
    virtual void stop() = 0;

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
    Actor(const Type type, const bool use_queue, const bool has_public_queue);
    virtual ~Actor();

    /**
     * @brief The event loop run by this actor.
     * 
     * If the actor is threaded, this will be the method run by the thread.
     * 
     */
    virtual void processEventLoop() = 0;
    
    /**
     * @brief Performs the work of sending a message to this actor.
     * 
     * If the actor does not accept messages, this method may do nothing.
     * However, actors should generally accept `START` and `STOP` messages.
     * 
     * @param m The message to send.
     */
    virtual void sendMessageInternal(Message& m) = 0;

    virtual bool adheresToMessagingPolicy(const Message& m) const;

private:
    Type _type;
    bool _use_queue;
    bool _has_public_queue;
};

URA_RTL_END
