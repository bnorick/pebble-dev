# PebbleKit.PebbleDataLogReceiver

Source: https://developer.repebble.com/docs/pebblekit-android/com/getpebble/android/kit/PebbleKit.PebbleDataLogReceiver/

[java.lang.Object](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/Object.html "class or interface in java.lang")
android.content.BroadcastReceiver
com.getpebble.android.kit.PebbleKit.PebbleDataLogReceiver

Enclosing class:[PebbleKit](/docs/pebblekit-android/com/getpebble/android/kit/PebbleKit.md "class in com.getpebble.android.kit")
* * *

public abstract static class PebbleKit.PebbleDataLogReceiverextends android.content.BroadcastReceiver

A special-purpose BroadcastReceiver that makes it easy to handle 'DATA\_AVAILABLE' data logging intents broadcast from pebble.apk.

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

`PebbleDataLogReceiver(UUID subscribedUuid)`

Instantiates a new pebble nack receiver.

- 
## Method Summary

All MethodsInstance MethodsConcrete Methods

Modifier and Type

Method

Description

`void`

`onFinishSession(android.content.Context context,
 UUID logUuid,
 Long timestamp,
 Long tag)`

Called when a session has been finished on the watch and all data has been transmitted by pebble.apk

`void`

`onReceive(android.content.Context context,
 android.content.Intent intent)`

`void`

`receiveData(android.content.Context context,
 UUID logUuid,
 Long timestamp,
 Long tag,
 byte[] data)`

Handle a byte array data unit that was logged the watch and broadcast by pebble.apk.

`void`

`receiveData(android.content.Context context,
 UUID logUuid,
 Long timestamp,
 Long tag,
 int data)`

Handle an int data unit that was logged the watch and broadcast by pebble.apk.

`void`

`receiveData(android.content.Context context,
 UUID logUuid,
 Long timestamp,
 Long tag,
 Long data)`

Handle an UnsignedInteger data unit that was logged the watch and broadcast by pebble.apk.

### Methods inherited from class&nbsp;android.content.BroadcastReceiver
`abortBroadcast, clearAbortBroadcast, getAbortBroadcast, getDebugUnregister, getResultCode, getResultData, getResultExtras, getSentFromPackage, getSentFromUid, goAsync, isInitialStickyBroadcast, isOrderedBroadcast, peekService, setDebugUnregister, setOrderedHint, setResult, setResultCode, setResultData, setResultExtras`

### Methods inherited from class&nbsp;java.lang.[Object](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/Object.html "class or interface in java.lang")
`clone, equals, finalize, getClass, hashCode, notify, notifyAll, toString, wait, wait, wait`

- 
## Constructor Details

  - 
### PebbleDataLogReceiver

protected&nbsp;PebbleDataLogReceiver([UUID](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/util/UUID.html "class or interface in java.util")&nbsp;subscribedUuid)

Instantiates a new pebble nack receiver.
Parameters:`subscribedUuid` - the subscribed uuid
- 
## Method Details

  - 
### receiveData

public&nbsp;void&nbsp;receiveData(android.content.Context&nbsp;context, [UUID](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/util/UUID.html "class or interface in java.util")&nbsp;logUuid, [Long](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/Long.html "class or interface in java.lang")&nbsp;timestamp, [Long](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/Long.html "class or interface in java.lang")&nbsp;tag, [Long](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/Long.html "class or interface in java.lang")&nbsp;data)

Handle an UnsignedInteger data unit that was logged the watch and broadcast by pebble.apk.
Parameters:`context` - The BroadcastReceiver's context.`logUuid` - The UUID that uniquely identifies a data log.`timestamp` - The timestamp when a data log was first created.`tag` - The user-defined tag for the corresponding data log.`data` - The unit of data that was logged on the watch.Throws:`UnsupportedOperationException` - Thrown if data is received and this handler is not implemented.
  - 
### receiveData

public&nbsp;void&nbsp;receiveData(android.content.Context&nbsp;context, [UUID](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/util/UUID.html "class or interface in java.util")&nbsp;logUuid, [Long](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/Long.html "class or interface in java.lang")&nbsp;timestamp, [Long](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/Long.html "class or interface in java.lang")&nbsp;tag, byte[]&nbsp;data)

Handle a byte array data unit that was logged the watch and broadcast by pebble.apk.
Parameters:`context` - The BroadcastReceiver's context.`logUuid` - The UUID that uniquely identifies a data log.`timestamp` - The timestamp when a data log was first created.`tag` - The user-defined tag for the corresponding data log.`data` - The unit of data that was logged on the watch.Throws:`UnsupportedOperationException` - Thrown if data is received and this handler is not implemented.
  - 
### receiveData

public&nbsp;void&nbsp;receiveData(android.content.Context&nbsp;context, [UUID](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/util/UUID.html "class or interface in java.util")&nbsp;logUuid, [Long](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/Long.html "class or interface in java.lang")&nbsp;timestamp, [Long](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/Long.html "class or interface in java.lang")&nbsp;tag, int&nbsp;data)

Handle an int data unit that was logged the watch and broadcast by pebble.apk.
Parameters:`context` - The BroadcastReceiver's context.`logUuid` - The UUID that uniquely identifies a data log.`timestamp` - The timestamp when a data log was first created.`tag` - The user-defined tag for the corresponding data log.`data` - The unit of data that was logged on the watch.Throws:`UnsupportedOperationException` - Thrown if data is received and this handler is not implemented.
  - 
### onFinishSession

public&nbsp;void&nbsp;onFinishSession(android.content.Context&nbsp;context, [UUID](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/util/UUID.html "class or interface in java.util")&nbsp;logUuid, [Long](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/Long.html "class or interface in java.lang")&nbsp;timestamp, [Long](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/Long.html "class or interface in java.lang")&nbsp;tag)

Called when a session has been finished on the watch and all data has been transmitted by pebble.apk
Parameters:`context` - The BroadcastReceiver's context.`logUuid` - The UUID that uniquely identifies a data log.`timestamp` - The timestamp when a data log was first created.`tag` - The user-defined tag for the corresponding data log.
  - 
### onReceive

public&nbsp;void&nbsp;onReceive(android.content.Context&nbsp;context, android.content.Intent&nbsp;intent)
Specified by:`onReceive`&nbsp;in class&nbsp;`android.content.BroadcastReceiver`
