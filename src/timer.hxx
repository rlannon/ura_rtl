#pragma once

#include "rtl.hxx"
#include "actor.hxx"

#include <cinttypes>

URA_RTL_BEGIN

class Timer: public Actor
{
private:
    void (*_callback)(void);
    uint64_t _interval;   /**< Number of ms between invocations */

protected:
    virtual void processEventLoop() override;
    virtual void sendMessageInternal(Message& m) override;

public:
    virtual void start() override;

    Timer(void (*callback)(), const uint64_t interval);
    virtual ~Timer();
};

URA_RTL_END
