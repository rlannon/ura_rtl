#include "message.hxx"

#include <utility>
#include <any>

URA_RTL_BEGIN

Message& Message::operator=(const Message& other)
{
    _sender = other._sender;
    _return_address = other._return_address;
    _type = other._type;
    _value = other._value;
    _code = other._code;
    _priority = other._priority;

    return *this;
}

Message& Message::operator=(Message&& other)
{
    _sender = other._sender;
    _return_address = other._return_address;
    _type = other._type;
    _value = std::move(other._value);
    _code = other._code;
    _priority = other._priority;

    return *this;
}

Message::Message(const Message& other)
    : _sender(other._sender)
    , _return_address(other._return_address)
    , _type(other._type)
    , _value(other._value)
    , _code(other._code)
    , _priority(other._priority) { }

Message::Message(Message&& other)
    : _sender(other._sender)
    , _return_address(other._return_address)
    , _type(other._type)
    , _value(std::move(other._value))
    , _code(other._code)
    , _priority(other._priority) { }

Message::Message(Actor* sender,
                 MessageReceiver* return_address,
                 const Type type,
                 std::any value,
                 const unsigned int code,
                 const uint8_t priority )
    : _sender(sender)
    , _return_address(return_address)
    , _type(type)
    , _value(value)
    , _code(code)
    , _priority(priority) { }

Message::~Message() { }

URA_RTL_END
