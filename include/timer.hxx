#pragma once

#include "rtl.hxx"
#include "actor.hxx"

#include <mutex>
#include <thread>

URA_RTL_BEGIN

class Timer: public Actor
{
private:
    std::chrono::milliseconds _interval;   /**< Number of ms between invocations */
    bool _running;  /**< Whether the thread is running */
    std::mutex _running_lock;
    std::thread _thread;

    virtual void processEventLoop() override;
    virtual void sendMessageInternal(Message& m) override;

protected:
    /**
     * @brief The method that gets executed every time the timer runs.
     * 
     * Any timer actors should inherit from this class and override the
     * `onExecute` method.
     * 
     */
    virtual void onExecute() = 0;

    Timer(  const std::chrono::milliseconds interval,
            const Actor::Type type,
            const bool use_queue,
            const bool has_public_queue );

public:
    virtual void start() override;
    virtual void stop() override;

    bool running() const
    {
        return _running;
    }

    Timer(const std::chrono::milliseconds interval);
    virtual ~Timer();
};

URA_RTL_END
