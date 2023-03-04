#include "promise.hxx"

URA_RTL_BEGIN

void Promise::sendMessage(Message& m)
{
    _resolve_lock.release();
    _message = std::make_unique<Message>(m);
    _resolved = true;
}

const Message* Promise::getMessage() const
{
    if (_resolved)
        return _message.get();
    else
        return nullptr;
}

void Promise::waitUntilResolved()
{
    _resolve_lock.acquire();
}

bool Promise::isResolved() const
{
    return _resolved;
}

Promise::Promise() 
    : MessageReceiver(MessageReceiver::Type::PROMISE)
    , _resolved(false) { }

Promise::~Promise() { }

URA_RTL_END
