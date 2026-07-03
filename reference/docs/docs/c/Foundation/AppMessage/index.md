# AppMessage

Source: https://developer.repebble.com/docs/c/Foundation/AppMessage/index.html

Bi-directional communication between phone apps and Pebble watchapps

AppMessage is a bi-directional messaging subsystem that enables communication between phone apps and Pebble watchapps. This is accomplished by allowing phone and watchapps to exchange arbitrary sets of key/value pairs. The key/value pairs are stored in the form of a Dictionary, the layout of which is left for the application developer to define.

AppMessage implements a push-oriented messaging protocol, enabling your app to call functions and methods to push messages from Pebble to phone and vice versa. The protocol is symmetric: both Pebble and the phone can send messages. All messages are acknowledged. In this context, there is no client-server model, as such.

During the sending phase, one side initiates the communication by transferring a dictionary over the air. The other side then receives this message and is given an opportunity to perform actions on that data. As soon as possible, the other side is expected to reply to the message with a simple acknowledgment that the message was received successfully.

PebbleKit JavaScript provides you with a set of standard JavaScript APIs that let your app receive messages from the watch, make HTTP requests, and send new messages to the watch. AppMessage APIs are used to send and receive data. A Pebble watchapp can use the resources of the connected phone to fetch information from web services, send information to web APIs, or store login credentials. On the JavaScript side, you communicate with Pebble via a Pebble object exposed in the namespace.

Messages always need to get either ACKnowledged or "NACK'ed," that is, not acknowledged. If not, messages will result in a time-out failure. The AppMessage subsystem takes care of this implicitly. In the phone libraries, this step is a bit more explicit.

The Pebble watch interfaces make a distinction between the Inbox and the Outbox calls. The Inbox receives messages from the phone on the watch; the Outbox sends messages from the watch to the phone. These two buffers can be managed separately.

#### Warning

A critical constraint of AppMessage is that messages are limited in size. An ingoing (outgoing) message larger than the inbox (outbox) will not be transmitted and will generate an error. You can choose your inbox and outbox size when you call [app\_message\_open()](/docs/c/Foundation/AppMessage/#app_message_open).

Pebble SDK provides a static minimum guaranteed size (APP\_MESSAGE\_INBOX\_SIZE\_MINIMUM and APP\_MESSAGE\_OUTBOX\_SIZE\_MINIMUM). Requesting a buffer of the minimum guaranteed size (or smaller) is always guaranteed to succeed on all Pebbles in this SDK version or higher, and with every phone.

In some context, Pebble might be able to provide your application with larger inbox/outbox. You can call [app\_message\_inbox\_size\_maximum()](/docs/c/Foundation/AppMessage/#app_message_inbox_size_maximum) and [app\_message\_outbox\_size\_maximum()](/docs/c/Foundation/AppMessage/#app_message_outbox_size_maximum) in your code to get the largest possible value you can use.

To always get the largest buffer available, follow this best practice:

app\_message\_open([app\_message\_inbox\_size\_maximum()](/docs/c/Foundation/AppMessage/#app_message_inbox_size_maximum), [app\_message\_outbox\_size\_maximum()](/docs/c/Foundation/AppMessage/#app_message_outbox_size_maximum))

AppMessage uses your application heap space. That means that the sizes you pick for the AppMessage inbox and outbox buffers are important in optimizing your app’s performance. The more you use for AppMessage, the less space you’ll have for the rest of your app.

To register callbacks, you should call [app\_message\_register\_inbox\_received()](/docs/c/Foundation/AppMessage/#app_message_register_inbox_received), [app\_message\_register\_inbox\_dropped()](/docs/c/Foundation/AppMessage/#app_message_register_inbox_dropped), [app\_message\_register\_outbox\_sent()](/docs/c/Foundation/AppMessage/#app_message_register_outbox_sent), [app\_message\_register\_outbox\_failed()](/docs/c/Foundation/AppMessage/#app_message_register_outbox_failed).

Pebble recommends that you call them before [app\_message\_open()](/docs/c/Foundation/AppMessage/#app_message_open) to ensure you do not miss a message arriving between starting AppMessage and registering the callback. You can set a context that will be passed to all the callbacks with [app\_message\_set\_context()](/docs/c/Foundation/AppMessage/#app_message_set_context).

In circumstances that may not be ideal, when using AppMessage several types of errors may occur. For example:

- The send can’t start because the system state won't allow for a success. Several reasons you're unable to perform a send: A send() is already occurring (only one is possible at a time) or Bluetooth is not enabled or connected.

- The send and receive occur, but the receiver can’t accept the message. For instance, there is no app that receives such a message.

- The send occurs, but the receiver either does not actually receive the message or can’t handle it in a timely fashion.

- In the case of a dropped message, the phone sends a message to the watchapp, while there is still an unprocessed message in the Inbox.

Other errors are possible and described by [AppMessageResult](/docs/c/Foundation/AppMessage/#AppMessageResult). A client of the AppMessage interface should use the result codes to be more robust in the face of communication problems either in the field or while debugging.

Refer to the

[App Communication in the Pebble Developer Guides](http://developer.getpebble.com/guides/pebble-apps/communications/)
 for a conceptual overview and code usage.

For code examples, refer to the SDK Examples that directly use App Message. These include:

- [pebblekit-js-weather](https://github.com/pebble-examples/pebblekit-js-weather)

- [pebblekit-js-quotes](https://github.com/pebble-examples/pebblekit-js-quotes) 

## Function Documentation

[AppMessageResult](/docs/c/Foundation/AppMessage/#AppMessageResult) app\_message\_open(const [uint32\_t](/docs/c/Standard_C/#uint32_t) size\_inbound, const [uint32\_t](/docs/c/Standard_C/#uint32_t) size\_outbound)

Open AppMessage to transfers.

Use [dict\_calc\_buffer\_size\_from\_tuplets()](/docs/c/Foundation/Dictionary/#dict_calc_buffer_size_from_tuplets) or [dict\_calc\_buffer\_size()](/docs/c/Foundation/Dictionary/#dict_calc_buffer_size) to estimate the size you need.

##### Note

It is recommended that if the Inbox will be used, that at least the Inbox callbacks should be registered before this call. Otherwise it is possible for an Inbox message to be NACK'ed without being seen by the application.

#### Parameters
 size\_inbound (in)

The required size for the Inbox buffer

 size\_outbound (in)

The required size for the Outbox buffer

#### Returns

A result code such as APP\_MSG\_OK or APP\_MSG\_OUT\_OF\_MEMORY.

void app\_message\_deregister\_callbacks(void)

Deregisters all callbacks and their context.

void \* app\_message\_get\_context(void)

Gets the context that will be passed to all AppMessage callbacks.

#### Returns

The current context on record.

void \* app\_message\_set\_context(void \* context)

Sets the context that will be passed to all AppMessage callbacks.

#### Parameters
 context (in)

The context that will be passed to all AppMessage callbacks.

#### Returns

The previous context that was on record.

[AppMessageInboxReceived](/docs/c/Foundation/AppMessage/#AppMessageInboxReceived) app\_message\_register\_inbox\_received([AppMessageInboxReceived](/docs/c/Foundation/AppMessage/#AppMessageInboxReceived) received\_callback)

Registers a function that will be called after any Inbox message is received successfully.

Only one callback may be registered at a time. Each subsequent call to this function will replace the previous callback. The callback is optional; setting it to NULL will deregister the current callback and no function will be called anymore.

#### Parameters
 received\_callback (in)

The callback that will be called going forward; NULL to not have a callback.

#### Returns

The previous callback (or NULL) that was on record.

[AppMessageInboxDropped](/docs/c/Foundation/AppMessage/#AppMessageInboxDropped) app\_message\_register\_inbox\_dropped([AppMessageInboxDropped](/docs/c/Foundation/AppMessage/#AppMessageInboxDropped) dropped\_callback)

Registers a function that will be called after any Inbox message is received but dropped by the system.

Only one callback may be registered at a time. Each subsequent call to this function will replace the previous callback. The callback is optional; setting it to NULL will deregister the current callback and no function will be called anymore.

#### Parameters
 dropped\_callback (in)

The callback that will be called going forward; NULL to not have a callback.

#### Returns

The previous callback (or NULL) that was on record.

[AppMessageOutboxSent](/docs/c/Foundation/AppMessage/#AppMessageOutboxSent) app\_message\_register\_outbox\_sent([AppMessageOutboxSent](/docs/c/Foundation/AppMessage/#AppMessageOutboxSent) sent\_callback)

Registers a function that will be called after any Outbox message is sent and an ACK reply occurs in a timely fashion.

Only one callback may be registered at a time. Each subsequent call to this function will replace the previous callback. The callback is optional; setting it to NULL will deregister the current callback and no function will be called anymore.

#### Parameters
 sent\_callback (in)

The callback that will be called going forward; NULL to not have a callback.

#### Returns

The previous callback (or NULL) that was on record.

[AppMessageOutboxFailed](/docs/c/Foundation/AppMessage/#AppMessageOutboxFailed) app\_message\_register\_outbox\_failed([AppMessageOutboxFailed](/docs/c/Foundation/AppMessage/#AppMessageOutboxFailed) failed\_callback)

Registers a function that will be called after any Outbox message is not sent with a timely ACK reply. The call to [app\_message\_outbox\_send()](/docs/c/Foundation/AppMessage/#app_message_outbox_send) must have succeeded.

Only one callback may be registered at a time. Each subsequent call to this function will replace the previous callback. The callback is optional; setting it to NULL will deregister the current callback and no function will be called anymore.

#### Parameters
 failed\_callback (in)

The callback that will be called going forward; NULL to not have a callback.

#### Returns

The previous callback (or NULL) that was on record.

[uint32\_t](/docs/c/Standard_C/#uint32_t) app\_message\_inbox\_size\_maximum(void)

Programatically determine the inbox size maximum in the current configuration.

#### Returns

The inbox size maximum on this firmware.

#### See Also
[APP\_MESSAGE\_INBOX\_SIZE\_MINIMUM](/docs/c/Foundation/AppMessage/#APP_MESSAGE_INBOX_SIZE_MINIMUM)  
[app\_message\_outbox\_size\_maximum()](/docs/c/Foundation/AppMessage/#app_message_outbox_size_maximum)

[uint32\_t](/docs/c/Standard_C/#uint32_t) app\_message\_outbox\_size\_maximum(void)

Programatically determine the outbox size maximum in the current configuration.

#### Returns

The outbox size maximum on this firmware.

#### See Also
[APP\_MESSAGE\_OUTBOX\_SIZE\_MINIMUM](/docs/c/Foundation/AppMessage/#APP_MESSAGE_OUTBOX_SIZE_MINIMUM)  
[app\_message\_inbox\_size\_maximum()](/docs/c/Foundation/AppMessage/#app_message_inbox_size_maximum)

[AppMessageResult](/docs/c/Foundation/AppMessage/#AppMessageResult) app\_message\_outbox\_begin([DictionaryIterator](/docs/c/Foundation/Dictionary/#DictionaryIterator) \*\* iterator)

Begin writing to the Outbox's Dictionary buffer.

##### Note

After a successful call, one can add values to the dictionary using functions like [dict\_write\_data()](/docs/c/Foundation/Dictionary/#dict_write_data) and friends.

#### Parameters
 iterator (out)

Location to write the [DictionaryIterator](/docs/c/Foundation/Dictionary/#DictionaryIterator) pointer. This will be NULL on failure.

#### Returns

A result code, including but not limited to APP\_MSG\_OK, APP\_MSG\_INVALID\_ARGS or APP\_MSG\_BUSY.

#### See Also
[Dictionary](/docs/c/Foundation/Dictionary/)

[AppMessageResult](/docs/c/Foundation/AppMessage/#AppMessageResult) app\_message\_outbox\_send(void)

Sends the outbound dictionary.

#### Returns

A result code, including but not limited to APP\_MSG\_OK or APP\_MSG\_BUSY. The APP\_MSG\_OK code does not mean that the message was sent successfully, but only that the start of processing was successful. Since this call is asynchronous, callbacks provide the final result instead.

#### See Also
[AppMessageOutboxSent](/docs/c/Foundation/AppMessage/#AppMessageOutboxSent)  
[AppMessageOutboxFailed](/docs/c/Foundation/AppMessage/#AppMessageOutboxFailed)

## Enum Documentation

enum AppMessageResult

AppMessage result codes.

#### Enumerators
APP\_MSG\_OK

(0) All good, operation was successful.

APP\_MSG\_SEND\_TIMEOUT

(2) The other end did not confirm receiving the sent data with an (n)ack in time.

APP\_MSG\_SEND\_REJECTED

(4) The other end rejected the sent data, with a "nack" reply.

APP\_MSG\_NOT\_CONNECTED

(8) The other end was not connected.

APP\_MSG\_APP\_NOT\_RUNNING

(16) The local application was not running.

APP\_MSG\_INVALID\_ARGS

(32) The function was called with invalid arguments.

APP\_MSG\_BUSY

(64) There are pending (in or outbound) messages that need to be processed first before new ones can be received or sent.

APP\_MSG\_BUFFER\_OVERFLOW

(128) The buffer was too small to contain the incoming message.

APP\_MSG\_ALREADY\_RELEASED

(512) The resource had already been released.

APP\_MSG\_CALLBACK\_ALREADY\_REGISTERED

(1024) The callback was already registered.

APP\_MSG\_CALLBACK\_NOT\_REGISTERED

(2048) The callback could not be deregistered, because it had not been registered before.

APP\_MSG\_OUT\_OF\_MEMORY

(4096) The system did not have sufficient application memory to perform the requested operation.

APP\_MSG\_CLOSED

(8192) App message was closed.

APP\_MSG\_INTERNAL\_ERROR

(16384) An internal OS error prevented AppMessage from completing an operation.

APP\_MSG\_INVALID\_STATE

(32768) The function was called while App Message was not in the appropriate state.

## Typedef Documentation

 typedef void(\* AppMessageInboxReceived)(DictionaryIterator \*iterator, void \*context) 

Called after an incoming message is received.

#### Parameters
 iterator (in)

The dictionary iterator to the received message. Never NULL. Note that the iterator cannot be modified or saved off. The library may need to re-use the buffered space where this message is supplied. Returning from the callback indicates to the library that the received message contents are no longer needed or have already been externalized outside its buffering space and iterator.

 context (in)

Pointer to application data as specified when registering the callback.

 typedef void(\* AppMessageInboxDropped)(AppMessageResult reason, void \*context) 

Called after an incoming message is dropped.

Note that you can call [app\_message\_outbox\_begin()](/docs/c/Foundation/AppMessage/#app_message_outbox_begin) from this handler to prepare a new message. This will invalidate the previous dictionary iterator; do not use it after calling [app\_message\_outbox\_begin()](/docs/c/Foundation/AppMessage/#app_message_outbox_begin).

#### Parameters
 result (in)

The reason why the message was dropped. Some possibilities include APP\_MSG\_BUSY and APP\_MSG\_BUFFER\_OVERFLOW.

 context (in)

Pointer to application data as specified when registering the callback.

 typedef void(\* AppMessageOutboxSent)(DictionaryIterator \*iterator, void \*context) 

Called after an outbound message has been sent and the reply has been received.

#### Parameters
 iterator (in)

The dictionary iterator to the sent message. The iterator will be in the final state that was sent. Note that the iterator cannot be modified or saved off as the library will re-open the dictionary with dict\_begin() after this callback returns.

 context (in)

Pointer to application data as specified when registering the callback.

 typedef void(\* AppMessageOutboxFailed)(DictionaryIterator \*iterator, AppMessageResult reason, void \*context) 

Called after an outbound message has not been sent successfully.

Note that you can call [app\_message\_outbox\_begin()](/docs/c/Foundation/AppMessage/#app_message_outbox_begin) from this handler to prepare a new message. This will invalidate the previous dictionary iterator; do not use it after calling [app\_message\_outbox\_begin()](/docs/c/Foundation/AppMessage/#app_message_outbox_begin).

#### Parameters
 iterator (in)

The dictionary iterator to the sent message. The iterator will be in the final state that was sent. Note that the iterator cannot be modified or saved off as the library will re-open the dictionary with dict\_begin() after this callback returns.

 result (in)

The result of the operation. Some possibilities for the value include APP\_MSG\_SEND\_TIMEOUT, APP\_MSG\_SEND\_REJECTED, APP\_MSG\_NOT\_CONNECTED, APP\_MSG\_APP\_NOT\_RUNNING, and the combination `(APP_MSG_NOT_CONNECTED | APP_MSG_APP_NOT_RUNNING)`.

 context

Pointer to application data as specified when registering the callback.

## Macro Definition Documentation

#define APP\_MESSAGE\_INBOX\_SIZE\_MINIMUM 124

As long as the firmware maintains its current major version, inboxes of this size or smaller will be allowed.

#### See Also
[app\_message\_inbox\_size\_maximum()](/docs/c/Foundation/AppMessage/#app_message_inbox_size_maximum)  
[APP\_MESSAGE\_OUTBOX\_SIZE\_MINIMUM](/docs/c/Foundation/AppMessage/#APP_MESSAGE_OUTBOX_SIZE_MINIMUM)

#define APP\_MESSAGE\_OUTBOX\_SIZE\_MINIMUM 636

As long as the firmware maintains its current major version, outboxes of this size or smaller will be allowed.

#### See Also
[app\_message\_outbox\_size\_maximum()](/docs/c/Foundation/AppMessage/#app_message_outbox_size_maximum)  
[APP\_MESSAGE\_INBOX\_SIZE\_MINIMUM](/docs/c/Foundation/AppMessage/#APP_MESSAGE_INBOX_SIZE_MINIMUM)
