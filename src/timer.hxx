#pragma once

#include "rtl.hxx"
#include "actor.hxx"

#include <mutex>
#include <thread>
#include <functional>

URA_RTL_BEGIN

class Timer: public Actor
{
private:
    std::function<void()> _callback;
    std::chrono::milliseconds _interval;   /**< Number of ms between invocations */
    bool _running;
    std::mutex _running_lock;
    std::thread _thread;

protected:
    virtual void processEventLoop() override;
    virtual void sendMessageInternal(Message& m) override;

    Timer(  std::function<void()> callback,
            const std::chrono::milliseconds interval,
            const Actor::Type type,
            const bool use_queue,
            const bool has_public_queue );

public:
    virtual void start() override;
    void stop();

    bool running() const
    {
        return _running;
    }

    Timer(std::function<void()> callback, const std::chrono::milliseconds interval);
    virtual ~Timer();
};

URA_RTL_END
