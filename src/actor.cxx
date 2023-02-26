#include "actor.hxx"

URA_RTL_BEGIN

Actor::Actor(const Type type, const bool use_queue, const bool has_public_queue)
    : _type(type)
    , _use_queue(use_queue)
    , _has_public_queue(has_public_queue) { }

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
        std::any value;
        Message error_message(this, nullptr, Message::Type::ERROR, value, 0);

        m.getSender()->sendMessage(error_message);

        return false;
    }
}

URA_RTL_END
