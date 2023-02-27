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
    // todo:

    p.resolve();
}

void await(Promise& p)
{
    // todo:

    p.resolve();
}

URA_RTL_END
