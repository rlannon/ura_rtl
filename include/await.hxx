#pragma once

#include <functional>

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
void await(Message& m, Actor& recipient);

/**
 * @brief Sends a message to the recipient, but allows the sender
 * to contine operating while waiting for the response.
 * 
 * @param p 
 * @param m 
 * @param recipient 
 */
void await(Promise& p, Message& m, Actor& recipient);

/**
 * @brief Waits for the `Promise` to be fulfilled.
 * 
 */
void await(Promise& p);

/**
 * @brief Runs the specified code before waiting for the given promise to be resolved.
 * 
 * @param p The promise this block is waiting on.
 * @param to_execute The code to execute while waiting.
 */
void meanwhile(Promise& p, std::function<void()> to_execute);

URA_RTL_END
