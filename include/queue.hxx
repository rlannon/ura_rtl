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

    Message fetchMessage(const bool peek);  /**< A helper method to simplify message fetching */

public:
    /**
     * @brief Adds a message to the queue
     * 
     * A copy of the message will be added to the queue.
     * 
     * @param m The message to add
     */
    void enqueue(const Message& m);
    /**
     * @brief Whether the queue has messages to be processed.
     * 
     * @return true If there are messages
     * @return false If there are not
     */
    bool hasMessages() const;
    /**
     * @brief Fetches the next message without removing it from the queue.
     * 
     * @return Message The next message to be processed.
     */
    Message peekNextMessage();
    /**
     * @brief Fetches the next message and removes it from the queue.
     * 
     * @return Message The next message to be processed.
     */
    Message nextMessage();
};

URA_RTL_END
