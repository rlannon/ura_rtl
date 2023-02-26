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
     * This method should be implemented if the actor accepts messages.
     * By default it does nothing. If the actor accepts messages but
     * does not override this method, all messages will get lost in
     * the ether!
     * 
     * @param m The message to send.
     */
    virtual void sendMessageInternal(Message& m);
    /**
     * @brief Whether the given message can be sent to the thread.
     * 
     * This is based on the actor's _messaging policy._ This determines
     * whether the actor can accept messages, what types of messages it
     * can accept, and how many it can process at a time. 
     * 
     * @param m The message to be sent
     * @return true If the message can be sent
     * @return false If the thread does not accept messages or the
     * type of message supplied
     */
    bool canSendMessage(Message& m);

private:
    Type _type;
    bool _use_queue;
    bool _has_public_queue;
};

URA_RTL_END
