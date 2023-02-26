#include "rtl.hxx"
#include "queue.hxx"

#include <any>

URA_RTL_BEGIN

void Queue::enqueue(const Message& m)
{
    std::lock_guard<std::mutex> guard(_lock);
    _queue.push_back(m.copy());
}

bool Queue::hasMessages() const
{
    return !_queue.empty();
}

Message Queue::nextMessageInternal(const bool peek)
{
    std::lock_guard<std::mutex> guard(_lock);
    
    if (_queue.empty())
    {
        Message error_message(  nullptr,
                                nullptr,
                                ura::Message::Type::ERROR,
                                std::any(),
                                1 );
        return error_message;
    }
    else
    {
        Message m = _queue.front();
        
        if (!peek)
        {
            _queue.pop_front();
        }

        return m;
    }
}

Message Queue::peekNextMessage()
{
    return nextMessageInternal(true);
}

Message Queue::nextMessage()
{
    return nextMessageInternal(false);
}

URA_RTL_END
