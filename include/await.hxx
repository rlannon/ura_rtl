#pragma once

#include "rtl.hxx"

/**
 * @file await.hxx
 * @brief Functionality for awaiting responses
 * 
 */

URA_RTL_BEGIN

class Message;
class Actor;
class Promise;

/**
 * @brief Sends a message to the recipient and waits for the reply.
 * 
 * @param p The promise to be fulfilled
 * @param m The message to send
 * @param recipient The intended recipient
 */
void await(Promise& p, Message& m, Actor& recipient);

/**
 * @brief Waits for the `Promise` to be fulfilled.
 * 
 */
void await(Promise& p);

/**
 * @brief Indicates that the message should be sent asynchronously,
 * but the response will be sent to a different actor and should
 * not be awaited by the sending actor.
 * 
 * @param p The promise to be fulfilled
 * @param m The message to send
 * @param recipient The intended recipient of the message
 */
void await_forward(Promise& p, Message& m, Actor& recipient);

/**
 * @brief Sends a message to the recipient, but allows the sender
 * to contine operating while waiting for the response.
 * 
 * @param p 
 * @param m 
 * @param recipient 
 */
void await_meanwhile(Promise& p, Message& m, Actor& recipient);

URA_RTL_END
