#pragma once

#include "rtl.hxx"

URA_RTL_BEGIN

class Actor;
class Message;

namespace MessagingPolicy
{

/**
 * @brief Manages the messaging policy for an actor
 * 
 * Actors can use any messaging policy want. Custom policies
 * should inherit from this class and utilize the provided
 * `Actor` methods to set policy for an object or class.
 */
class Policy
{
public:
    /**
     * @brief Whether the given message adheres to the current policy.
     * 
     * The default policy only checks whether the recipient can accept messages (has a public queue).
     * 
     * @param m The message being sent
     * @param recipient The intended recipient of the message
     * @return false If the message violates the policy
     */
    virtual bool AdheresToPolicy(const Message& m, const Actor& recipient) const;
};

/**
 * @brief The default policy for the application.
 *
 */
extern const Policy DEFAULT_POLICY;

}

URA_RTL_END
