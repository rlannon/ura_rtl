#include "await.hxx"
#include "promise.hxx"
#include "message.hxx"
#include "actor.hxx"

URA_RTL_BEGIN

void await(Message& m, Actor& recipient)
{
    recipient.sendMessage(m);
}

void await_meanwhile(Promise& p, Message& m, Actor& recipient)
{
    m.returnTo(&p);
    recipient.sendMessage(m);
    p.waitUntilResolved();
}

void await(Promise& p)
{
    p.waitUntilResolved();
}

URA_RTL_END
