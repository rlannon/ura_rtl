#include "actor.hxx"

URA_RTL_BEGIN

Actor::Actor(const Type type, const bool useQueue, const bool hasPublicQueue)
    : _type(type)
    , _use_queue(useQueue)
    , _has_public_queue(hasPublicQueue) { }

Actor::~Actor() { }

void Actor::sendMessage(Message m)
{
    if (canSendMessage(m))
    {
        sendMessageInternal(m);
    }
}

bool Actor::canSendMessage(Message& m)
{
    if (_has_public_queue)
    {
        return true;
    }
    else
    {
        Generic value;
        Message error_message(this, nullptr, Message::Type::ERROR, value, 0);

        m.getSender()->sendMessage(error_message);

        return false;
    }
}

URA_RTL_END
