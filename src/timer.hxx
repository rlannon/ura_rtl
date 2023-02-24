#pragma once

#include "rtl.hxx"
#include "actor.hxx"

#include <cinttypes>
#include <mutex>
#include <thread>

URA_RTL_BEGIN

class Timer: public Actor
{
private:
    void (*_callback)(void);    /**< Executed at interval */
    std::chrono::milliseconds _interval;   /**< Number of ms between invocations */
    bool _running;
    std::mutex _running_lock;
    std::thread _thread;

protected:
    virtual void processEventLoop() override;
    virtual void sendMessageInternal(Message& m) override;

public:
    virtual void start() override;
    void stop();

    bool running() const
    {
        return _running;
    }

    Timer(void (*callback)(), const std::chrono::milliseconds interval);
    virtual ~Timer();
};

URA_RTL_END
