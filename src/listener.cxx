#include "listener.hxx"

URA_RTL_BEGIN

void Listener::processEventLoop() { }

void Listener::start() { }

void Listener::stop() { }

void Listener::sendMessageInternal(Message& m)
{
    handleMessage(m);
}

Listener::Listener() : Actor(Actor::Type::LISTENER, false, true) { }

Listener::~Listener() { }

URA_RTL_END
