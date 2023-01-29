#pragma once

#include "message_receiver.hxx"
#include "message.hxx"

#include <deque>
#include <mutex>

namespace ura
{

class Queue: public MessageReceiver
{
    std::deque<Message> _queue;
    std::mutex _lock;

public:
    const std::deque<Message>& getQueue() const
    {
        return _queue;
    }

    void enqueue(const Message& m);
};

}   /* namespace ura */
