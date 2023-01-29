#include "queue.hxx"

namespace ura
{

void Queue::enqueue(const Message& m)
{
    std::lock_guard<std::mutex> guard(_lock);
    _queue.push_back(m);
}

}   /* namespace ura */
