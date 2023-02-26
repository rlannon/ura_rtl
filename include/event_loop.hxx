#pragma once

#include "rtl.hxx"

#include "actor.hxx"
#include "queue.hxx"
#include "timer.hxx"

URA_RTL_BEGIN

class EventLoop: public Timer
{
    Queue _queue;   /**< The actor's message queue */
    
    virtual void sendMessageInternal(Message& m) override;
    virtual void onExecute() override;

protected:
    /**
     * @brief The event that gets run by this actor.
     * 
     * This method will execute periodically and is separate from
     * message handling. Any event loop actors should inherit from
     * this class and override this method.
     * 
     */
    virtual void eventLoop() = 0;
    /**
     * @brief Processes the next message in the queue.
     * 
     * Any event loop actors should inherit from this class
     * and override this method.
     * 
     * @param message The message to process.
     */
    virtual void handleMessage(Message& message) = 0;

public:
    EventLoop(const std::chrono::milliseconds interval);
    virtual ~EventLoop();
};

URA_RTL_END
