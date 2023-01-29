#include "queue.hxx"

#include "rtl.hxx"

URA_RTL_BEGIN

void Queue::enqueue(const Message& m)
{
    std::lock_guard<std::mutex> guard(_lock);
    _queue.push_back(m.copy());
}

URA_RTL_END
