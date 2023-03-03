#include "await.hxx"
#include "promise.hxx"
#include "message.hxx"
#include "actor.hxx"

URA_RTL_BEGIN

void await(Message& m, Actor& recipient)
{
    Promise p;
    m.returnTo(&p);

    recipient.sendMessage(m);
    p.waitUntilResolved();
}

void await(Promise& p, Message& m, Actor& recipient)
{
    m.returnTo(&p);
    recipient.sendMessage(m);
}

void await(Promise& p)
{
    p.waitUntilResolved();
}

void meanwhile(Promise& p, std::function<void()> to_execute)
{
    to_execute();
    p.waitUntilResolved();
}

URA_RTL_END
