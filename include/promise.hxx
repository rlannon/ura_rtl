#pragma once

#include "rtl.hxx"
#include "message_receiver.hxx"
#include "message.hxx"

#include <semaphore>
#include <memory>

URA_RTL_BEGIN

class Promise: public MessageReceiver
{
    bool _resolved {false};
    std::binary_semaphore _resolve_lock {0};
    std::unique_ptr<Message> _message;

public:
    virtual void sendMessage(Message& m) override;
    const Message* getMessage() const;
    void waitUntilResolved();

    Promise();
    virtual ~Promise();
};

URA_RTL_END
