#include "messaging_policy.hxx"
#include "actor.hxx"
#include "message.hxx"

URA_RTL_BEGIN

namespace MessagingPolicy
{

const Policy DEFAULT_POLICY { };

bool Policy::AdheresToPolicy(const Message& m, const Actor& recipient) const
{
    return  recipient.hasPublicQueue() ||
            m.getType() == Message::Type::START ||
            m.getType() == Message::Type::STOP;
}

}   /* namespace MessagingPolicy */

URA_RTL_END
