#include "message.hxx"

#include <utility>

URA_RTL_BEGIN

Message::Message(const Message& other)
    : _sender(other._sender)
    , _return_address(other._return_address)
    , _type(other._type)
    , _value(other._value.copy())
    , _code(other._code) { }

Message::Message(Message&& other)
    : _sender(other._sender)
    , _return_address(other._return_address)
    , _type(other._type)
    , _value(std::move(other._value))
    , _code(other._code) { }

Message::Message(Actor* sender, Actor* returnAddress, Type type, Generic value, unsigned int code)
    : _sender(sender)
    , _return_address(returnAddress)
    , _type(type)
    , _value(value)
    , _code(code) { }

Message::~Message() { }

URA_RTL_END