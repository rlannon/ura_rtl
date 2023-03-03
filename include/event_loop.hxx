#pragma once

#include "rtl.hxx"
#include "actor.hxx"
#include "message.hxx"
#include "timer.hxx"

#include <deque>
#include <mutex>

URA_RTL_BEGIN

class EventLoop: public Timer
{
    std::deque<Message> _queue;   /**< The actor's message queue */
    std::mutex _queue_lock;
    
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
     * @return Message The thread's response to the message.
     */
    virtual Message handleMessage(Message& message) = 0;

public:
    EventLoop(const std::chrono::milliseconds interval);
    virtual ~EventLoop();
};

URA_RTL_END
