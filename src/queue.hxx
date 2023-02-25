#pragma once

#include "message_receiver.hxx"
#include "message.hxx"

#include <deque>
#include <mutex>

#include "rtl.hxx"

URA_RTL_BEGIN

class Queue: public MessageReceiver
{
    std::deque<Message> _queue;
    std::mutex _lock;

    Message nextMessageInternal(const bool peek);

public:
    const std::deque<Message>& getQueue() const
    {
        return _queue;
    }

    void enqueue(const Message& m);
    bool hasMessages() const;
    Message peekNextMessage();
    Message nextMessage();
};

URA_RTL_END
