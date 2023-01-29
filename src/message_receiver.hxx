#pragma once

#include "rtl.hxx"

URA_RTL_BEGIN

class MessageReceiver
{
public:
    enum class Type
    {
        PROMISE,
        QUEUE
    };

    Type getType() const
    {
        return _type;
    }

private:
    Type _type;
};

URA_RTL_END
