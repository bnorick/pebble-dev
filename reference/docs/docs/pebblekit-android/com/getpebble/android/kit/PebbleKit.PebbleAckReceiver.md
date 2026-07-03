# PebbleKit.PebbleAckReceiver

Source: https://developer.repebble.com/docs/pebblekit-android/com/getpebble/android/kit/PebbleKit.PebbleAckReceiver/

[java.lang.Object](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/Object.html "class or interface in java.lang")
android.content.BroadcastReceiver
com.getpebble.android.kit.PebbleKit.PebbleAckReceiver

Enclosing class:[PebbleKit](/docs/pebblekit-android/com/getpebble/android/kit/PebbleKit.md "class in com.getpebble.android.kit")
* * *

public abstract static class PebbleKit.PebbleAckReceiverextends android.content.BroadcastReceiver

A special-purpose BroadcastReceiver that makes it easy to handle 'RECEIVE\_ACK' intents broadcast from pebble .apk.

- 
## Nested Class Summary

## Nested classes/interfaces inherited from class&nbsp;android.content.BroadcastReceiver
`android.content.BroadcastReceiver.PendingResult`
- 
## Constructor Summary

Constructors

Modifier

Constructor

Description

`protected `

`PebbleAckReceiver(UUID subscribedUuid)`

Instantiates a new pebble ack receiver.

- 
## Method Summary

All MethodsInstance MethodsAbstract MethodsConcrete Methods

Modifier and Type

Method

Description

`void`

`onReceive(android.content.Context context,
 android.content.Intent intent)`

`abstract void`

`receiveAck(android.content.Context context,
 int transactionId)`

Handle the ACK received from the connected watch.

### Methods inherited from class&nbsp;android.content.BroadcastReceiver
`abortBroadcast, clearAbortBroadcast, getAbortBroadcast, getDebugUnregister, getResultCode, getResultData, getResultExtras, getSentFromPackage, getSentFromUid, goAsync, isInitialStickyBroadcast, isOrderedBroadcast, peekService, setDebugUnregister, setOrderedHint, setResult, setResultCode, setResultData, setResultExtras`

### Methods inherited from class&nbsp;java.lang.[Object](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/Object.html "class or interface in java.lang")
`clone, equals, finalize, getClass, hashCode, notify, notifyAll, toString, wait, wait, wait`

- 
## Constructor Details

  - 
### PebbleAckReceiver

protected&nbsp;PebbleAckReceiver([UUID](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/util/UUID.html "class or interface in java.util")&nbsp;subscribedUuid)

Instantiates a new pebble ack receiver.
Parameters:`subscribedUuid` - the subscribed uuid
- 
## Method Details

  - 
### receiveAck

public abstract&nbsp;void&nbsp;receiveAck(android.content.Context&nbsp;context, int&nbsp;transactionId)

Handle the ACK received from the connected watch.
Parameters:`context` - The BroadcastReceiver's context.`transactionId` - The transaction ID of the message for which the ACK was received. This indicates which message was successfully received.
  - 
### onReceive

public&nbsp;void&nbsp;onReceive(android.content.Context&nbsp;context, android.content.Intent&nbsp;intent)
Specified by:`onReceive`&nbsp;in class&nbsp;`android.content.BroadcastReceiver`
