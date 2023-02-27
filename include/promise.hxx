#pragma once

#include "rtl.hxx"
#include "message_receiver.hxx"

URA_RTL_BEGIN

class Promise: public MessageReceiver
{
    bool _resolved {false};

public:
    void resolve();

    Promise();
    virtual ~Promise();
};

URA_RTL_END
