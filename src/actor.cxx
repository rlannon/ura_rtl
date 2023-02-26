#include "actor.hxx"
#include "codes/error.hxx"

#include <string>

URA_RTL_BEGIN

Actor::Actor(const Type type, const bool use_queue, const bool has_public_queue)
    : _type(type)
    , _use_queue(use_queue)
    , _has_public_queue(has_public_queue) { }

Actor::~Actor() { }

void Actor::sendMessage(Message m)
{
    if (_messaging_policy->AdheresToPolicy(m, *this))
    {
        sendMessageInternal(m);
    }
    else
    {
        Message error_message(  this,
                                nullptr,
                                Message::Type::ERROR,
                                std::string("Message not allowed according to actor messaging policy"),
                                Codes::Error::CANNOT_RECEIVE_MESSAGES );

        m.getSender()->sendMessage(error_message);
    }
}

void Actor::sendMessageInternal(Message& m)
{
    return;
}

bool Actor::canSendMessage(Message& m)
{
    return _has_public_queue /* todo: messaging policy */;
}

URA_RTL_END
