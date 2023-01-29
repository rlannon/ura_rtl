#pragma once

namespace ura
{

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

}   /* namespace ura */
