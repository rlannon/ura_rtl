# Ura Runtime Library

This library is designed to facilitate the concurrency features of Ura (working name), a concurrency-focused programming language. However, it may be used as a concurrency support library in C++.

## Actors

At the center of this concurrency model are _actors._

### Event Loop

An event loop is an actor that processes messages from a queue. It may receive messages and process them in turn.

### Timer

A timer is an actor that executes a single method at given intervals. It is essentially an event loop that does not respond to messages.

### Listener

A listener is an actor that simply awaits a message and responds to it. Unlike an event loop, it does not maintain a queue.

## Communication

Actors communicate by sending messages to one another. When an actor attempts to send a message to another actor, the recipient can do one of three things:

1. Handle the message immediately
1. Add the message to a queue for later processing
1. Ignore or refuse the request

Actors may or may not send acknowledgements or other types of responses when receiving or handling a message. Actors may also specify that a response should get forwarded to another actor instead of responding to the sender directly.

### Messages

Messages are objects that actors use to communicate. They encode data using a generic type interface.

### Messaging Policy

Controlling the flow of messages between actors are their _messaging policies._ These are rules that dictate what types of messages an actor may receive. These may be controlled at the `class` level or at the object level. For example, a user might implement an `EventLoop` that can receive messages from anyone, but create a specific instance of that object that can only receive messages from a particular source, or of a particular type.

### Error Conditions

Unlike C++, where error conditions are handled through _exceptions,_ actors will send `ERROR` messages in the face of erroneous or exceptional conditions.
