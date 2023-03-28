#include "actor.hxx"
#include "codes.hxx"

#include <string>

URA_RTL_BEGIN

Actor::Actor(const Type type, const bool use_queue, const bool has_public_queue)
    : MessageReceiver(MessageReceiver::Type::ACTOR)
    , _type(type)
    , _use_queue(use_queue)
    , _has_public_queue(has_public_queue) { }

Actor::~Actor() { }

void Actor::sendMessage(Message& m)
{
    if (adheresToMessagingPolicy(m))
    {
        sendMessageInternal(m);
    }
    else
    {
        Message error_message(  this,
                                nullptr,
                                Message::Type::ERROR,
                                std::string("Message not allowed according to actor messaging policy"),
                                StandardCodes::ERROR_POLICY_VIOLATION );

        m.getSender()->sendMessage(error_message);
    }
}

bool Actor::adheresToMessagingPolicy(const Message& m) const
{
    return  this->hasPublicQueue() ||
            m.getType() == Message::Type::START ||
            m.getType() == Message::Type::STOP;
}

URA_RTL_END
