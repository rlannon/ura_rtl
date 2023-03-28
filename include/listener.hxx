#pragma once

#include "rtl.hxx"
#include "actor.hxx"

URA_RTL_BEGIN

class Listener: public Actor
{
    virtual void processEventLoop() override;   /**< Not relevant for class */
    virtual void start(const uint8_t priority=priority::URGENT) override;  /**< Not relevant for class */
    virtual void stop(const uint8_t priority=priority::URGENT) override;   /**< Not relevant for class */

    virtual void sendMessageInternal(Message& m) override;

protected:
    /**
     * @brief Processes the next message in the queue.
     * 
     * Any listener actors should inherit from this class and
     * override this method.
     * 
     * @param message 
     */
    virtual void handleMessage(Message& message) = 0;

public:
    Listener();
    virtual ~Listener();
};

URA_RTL_END
