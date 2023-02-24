# Ura Runtime Library

This library is designed to facilitate the concurrency features of Ura (working name), a concurrency-focused programming language.

## Actors

At the center of this concurrency model are _actors._

### Event Loop

An event loop is an actor that processes messages from a queue. It may receive messages and process them in turn.

### Timer

A timer is an actor that executes a single method at given intervals.

### Listener

A listener is an actor that simply awaits a message and responds to it. Unlike an event loop, it does not maintain a queue.

## Messages

Messages are objects that actors use to communicate. They encode data using a generic type interface, implemented through NaN-boxing.
