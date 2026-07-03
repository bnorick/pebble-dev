# PebbleKit.PebbleDataReceiver

Source: https://developer.repebble.com/docs/pebblekit-android/com/getpebble/android/kit/PebbleKit.PebbleDataReceiver/

[java.lang.Object](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/Object.html "class or interface in java.lang")
android.content.BroadcastReceiver
com.getpebble.android.kit.PebbleKit.PebbleDataReceiver

Enclosing class:[PebbleKit](/docs/pebblekit-android/com/getpebble/android/kit/PebbleKit.md "class in com.getpebble.android.kit")
* * *

public abstract static class PebbleKit.PebbleDataReceiverextends android.content.BroadcastReceiver

A special-purpose BroadcastReceiver that makes it easy to handle 'RECEIVE' intents broadcast from pebble.apk.

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

`PebbleDataReceiver(UUID subscribedUuid)`

Instantiates a new pebble data receiver.

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

`receiveData(android.content.Context context,
 int transactionId,
 PebbleDictionary data)`

Perform some work on the data received from the connected watch.

### Methods inherited from class&nbsp;android.content.BroadcastReceiver
`abortBroadcast, clearAbortBroadcast, getAbortBroadcast, getDebugUnregister, getResultCode, getResultData, getResultExtras, getSentFromPackage, getSentFromUid, goAsync, isInitialStickyBroadcast, isOrderedBroadcast, peekService, setDebugUnregister, setOrderedHint, setResult, setResultCode, setResultData, setResultExtras`

### Methods inherited from class&nbsp;java.lang.[Object](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/Object.html "class or interface in java.lang")
`clone, equals, finalize, getClass, hashCode, notify, notifyAll, toString, wait, wait, wait`

- 
## Constructor Details

  - 
### PebbleDataReceiver

protected&nbsp;PebbleDataReceiver([UUID](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/util/UUID.html "class or interface in java.util")&nbsp;subscribedUuid)

Instantiates a new pebble data receiver.
Parameters:`subscribedUuid` - the subscribed uuid
- 
## Method Details

  - 
### receiveData

public abstract&nbsp;void&nbsp;receiveData(android.content.Context&nbsp;context, int&nbsp;transactionId, [PebbleDictionary](/docs/pebblekit-android/com/getpebble/android/kit/util/PebbleDictionary.md "class in com.getpebble.android.kit.util")&nbsp;data)

Perform some work on the data received from the connected watch.
Parameters:`context` - The BroadcastReceiver's context.`transactionId` - The transaction ID of the message in which the data was received. This is required when ACK/NACKing the received message.`data` - A dictionary of one-or-more key-value pairs received from the connected watch.
  - 
### onReceive

public&nbsp;void&nbsp;onReceive(android.content.Context&nbsp;context, android.content.Intent&nbsp;intent)
Specified by:`onReceive`&nbsp;in class&nbsp;`android.content.BroadcastReceiver`
