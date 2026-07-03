# PebbleKit

Source: https://developer.repebble.com/docs/pebblekit-android/com/getpebble/android/kit/PebbleKit/

[java.lang.Object](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/Object.html "class or interface in java.lang")
com.getpebble.android.kit.PebbleKit

* * *

public final class PebbleKitextends [Object](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/Object.html "class or interface in java.lang")

A helper class providing methods for interacting with third-party Pebble Smartwatch applications. Pebble-enabled Android applications may use this class to assist in sending/receiving data between the watch and the phone.

- 
## Nested Class Summary

Nested Classes

Modifier and Type

Class

Description

`static class `

`PebbleKit.FirmwareVersionInfo`

&nbsp;

`static class `

`PebbleKit.PebbleAckReceiver`

A special-purpose BroadcastReceiver that makes it easy to handle 'RECEIVE\_ACK' intents broadcast from pebble .apk.

`static class `

`PebbleKit.PebbleDataLogReceiver`

A special-purpose BroadcastReceiver that makes it easy to handle 'DATA\_AVAILABLE' data logging intents broadcast from pebble.apk.

`static class `

`PebbleKit.PebbleDataReceiver`

A special-purpose BroadcastReceiver that makes it easy to handle 'RECEIVE' intents broadcast from pebble.apk.

`static class `

`PebbleKit.PebbleNackReceiver`

A special-purpose BroadcastReceiver that makes it easy to handle 'RECEIVE\_NACK' intents broadcast from pebble .apk.

- 
## Method Summary

All MethodsStatic MethodsConcrete Methods

Modifier and Type

Method

Description

`static boolean`

`areAppMessagesSupported(android.content.Context context)`

Synchronously query the Pebble application to see if the connected watch is running a firmware version that supports PebbleKit messages.

`static void`

`closeAppOnPebble(android.content.Context context,
 UUID watchappUuid)`

Send a message to the connected Pebble to close an application identified by a UUID.

`static void`

`customizeWatchApp(android.content.Context context,
 Constants.PebbleAppType appType,
 String name,
 android.graphics.Bitmap icon)`

Send a message to the connected Pebble to "customize" a built-in PebbleKit watch-app.

`static PebbleKit.FirmwareVersionInfo`

`getWatchFWVersion(android.content.Context context)`

Get the version information of the firmware running on a connected watch.

`static boolean`

`isDataLoggingSupported(android.content.Context context)`

Synchronously query the Pebble application to see if the connected watch is running a firmware version that supports PebbleKit data logging.

`static boolean`

`isWatchConnected(android.content.Context context)`

Synchronously query the Pebble application to see if an active Bluetooth connection to a watch currently exists.

`static android.content.BroadcastReceiver`

`registerDataLogReceiver(android.content.Context context,
 PebbleKit.PebbleDataLogReceiver receiver)`

A convenience function to assist in programatically registering a broadcast receiver for the 'DATA\_AVAILABLE' intent.

`static android.content.BroadcastReceiver`

`registerPebbleConnectedReceiver(android.content.Context context,
 android.content.BroadcastReceiver receiver)`

A convenience function to assist in programatically registering a broadcast receiver for the 'CONNECTED' intent.

`static android.content.BroadcastReceiver`

`registerPebbleDisconnectedReceiver(android.content.Context context,
 android.content.BroadcastReceiver receiver)`

A convenience function to assist in programatically registering a broadcast receiver for the 'DISCONNECTED' intent.

`static android.content.BroadcastReceiver`

`registerReceivedAckHandler(android.content.Context context,
 PebbleKit.PebbleAckReceiver receiver)`

A convenience function to assist in programatically registering a broadcast receiver for the 'RECEIVE\_ACK' intent.

`static android.content.BroadcastReceiver`

`registerReceivedDataHandler(android.content.Context context,
 PebbleKit.PebbleDataReceiver receiver)`

A convenience function to assist in programatically registering a broadcast receiver for the 'RECEIVE' intent.

`static android.content.BroadcastReceiver`

`registerReceivedNackHandler(android.content.Context context,
 PebbleKit.PebbleNackReceiver receiver)`

A convenience function to assist in programatically registering a broadcast receiver for the 'RECEIVE\_NACK' intent.

`static void`

`requestDataLogsForApp(android.content.Context context,
 UUID appUuid)`

A convenience function to emit an intent to pebble.apk to request the data logs for a particular app.

`static void`

`sendAckToPebble(android.content.Context context,
 int transactionId)`

Send a message to the connected watch acknowledging the receipt of a PebbleDictionary.

`static void`

`sendDataToPebble(android.content.Context context,
 UUID watchappUuid,
 PebbleDictionary data)`

Send one-or-more key-value pairs to the watch-app identified by the provided UUID.

`static void`

`sendDataToPebbleWithTransactionId(android.content.Context context,
 UUID watchappUuid,
 PebbleDictionary data,
 int transactionId)`

Send one-or-more key-value pairs to the watch-app identified by the provided UUID.

`static void`

`sendNackToPebble(android.content.Context context,
 int transactionId)`

Send a message to the connected watch that the previously sent PebbleDictionary was not received successfully.

`static void`

`startAppOnPebble(android.content.Context context,
 UUID watchappUuid)`

Send a message to the connected Pebble to launch an application identified by a UUID.

### Methods inherited from class&nbsp;java.lang.[Object](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/Object.html "class or interface in java.lang")
`clone, equals, finalize, getClass, hashCode, notify, notifyAll, toString, wait, wait, wait`

- 
## Method Details

  - 
### customizeWatchApp

public static&nbsp;void&nbsp;customizeWatchApp(android.content.Context&nbsp;context, [Constants.PebbleAppType](/docs/pebblekit-android/com/getpebble/android/kit/Constants.PebbleAppType.md "enum class in com.getpebble.android.kit")&nbsp;appType, [String](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/String.html "class or interface in java.lang")&nbsp;name, android.graphics.Bitmap&nbsp;icon) throws [IllegalArgumentException](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/IllegalArgumentException.html "class or interface in java.lang")

Send a message to the connected Pebble to "customize" a built-in PebbleKit watch-app. This is intended to allow third-party Android applications to apply custom branding (both name and icon) on the watch without needing to distribute a complete watch-app.
Parameters:`context` - The context used to send the broadcast. (Protip: pass in the ApplicationContext here.)`appType` - The watch-app to be configured. Options are either`name` - The custom name to be applied to the watch-app. Names must be less than 32 characters in length.`icon` - The custom icon to be applied to the watch-app. Icons must be black-and-white bitmaps no larger than 32px in either dimension.Throws:`IllegalArgumentException` - Thrown if the specified name or icon are invalid. [`Constants.PebbleAppType.SPORTS`](/docs/pebblekit-android/com/getpebble/android/kit/Constants.PebbleAppType.md#SPORTS) or [`Constants.PebbleAppType.GOLF`](/docs/pebblekit-android/com/getpebble/android/kit/Constants.PebbleAppType.md#GOLF).
  - 
### isWatchConnected

public static&nbsp;boolean&nbsp;isWatchConnected(android.content.Context&nbsp;context)

Synchronously query the Pebble application to see if an active Bluetooth connection to a watch currently exists.
Parameters:`context` - The Android context used to perform the query. _Protip:_ You probably want to use your ApplicationContext here.Returns:true if an active connection to the watch currently exists, otherwise false. This method will also return false if the Pebble application is not installed on the user's handset.
  - 
### areAppMessagesSupported

public static&nbsp;boolean&nbsp;areAppMessagesSupported(android.content.Context&nbsp;context)

Synchronously query the Pebble application to see if the connected watch is running a firmware version that supports PebbleKit messages.
Parameters:`context` - The Android context used to perform the query. _Protip:_ You probably want to use your ApplicationContext here.Returns:true if the watch supports PebbleKit messages, otherwise false. This method will always return false if no Pebble is currently connected to the handset.
  - 
### getWatchFWVersion

public static&nbsp;[PebbleKit.FirmwareVersionInfo](/docs/pebblekit-android/com/getpebble/android/kit/PebbleKit.FirmwareVersionInfo.md "class in com.getpebble.android.kit")&nbsp;getWatchFWVersion(android.content.Context&nbsp;context)

Get the version information of the firmware running on a connected watch.
Parameters:`context` - The Android context used to perform the query. _Protip:_ You probably want to use your ApplicationContext here.Returns:null if the watch is disconnected or we can't get the version. Otherwise, a FirmwareVersionObject containing info on the watch FW version
  - 
### isDataLoggingSupported

public static&nbsp;boolean&nbsp;isDataLoggingSupported(android.content.Context&nbsp;context)

Synchronously query the Pebble application to see if the connected watch is running a firmware version that supports PebbleKit data logging.
Parameters:`context` - The Android context used to perform the query. _Protip:_ You probably want to use your ApplicationContext here.Returns:true if the watch supports PebbleKit messages, otherwise false. This method will always return false if no Pebble is currently connected to the handset.
  - 
### startAppOnPebble

public static&nbsp;void&nbsp;startAppOnPebble(android.content.Context&nbsp;context, [UUID](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/util/UUID.html "class or interface in java.util")&nbsp;watchappUuid) throws [IllegalArgumentException](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/IllegalArgumentException.html "class or interface in java.lang")

Send a message to the connected Pebble to launch an application identified by a UUID. If another application is currently running it will be terminated and the new application will be brought to the foreground.
Parameters:`context` - The context used to send the broadcast.`watchappUuid` - A UUID uniquely identifying the target application. UUIDs for the stock PebbleKit applications are available in [`Constants`](/docs/pebblekit-android/com/getpebble/android/kit/Constants.md "class in com.getpebble.android.kit").Throws:`IllegalArgumentException` - Thrown if the specified UUID is invalid.
  - 
### closeAppOnPebble

public static&nbsp;void&nbsp;closeAppOnPebble(android.content.Context&nbsp;context, [UUID](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/util/UUID.html "class or interface in java.util")&nbsp;watchappUuid) throws [IllegalArgumentException](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/IllegalArgumentException.html "class or interface in java.lang")

Send a message to the connected Pebble to close an application identified by a UUID. If this application is not currently running, the message is ignored.
Parameters:`context` - The context used to send the broadcast.`watchappUuid` - A UUID uniquely identifying the target application. UUIDs for the stock kit applications are available in [`Constants`](/docs/pebblekit-android/com/getpebble/android/kit/Constants.md "class in com.getpebble.android.kit").Throws:`IllegalArgumentException` - Thrown if the specified UUID is invalid.
  - 
### sendDataToPebble

public static&nbsp;void&nbsp;sendDataToPebble(android.content.Context&nbsp;context, [UUID](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/util/UUID.html "class or interface in java.util")&nbsp;watchappUuid, [PebbleDictionary](/docs/pebblekit-android/com/getpebble/android/kit/util/PebbleDictionary.md "class in com.getpebble.android.kit.util")&nbsp;data) throws [IllegalArgumentException](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/IllegalArgumentException.html "class or interface in java.lang")

Send one-or-more key-value pairs to the watch-app identified by the provided UUID. This is the primary method for sending data from the phone to a connected Pebble. The watch-app and phone-app must agree of the set and type of key-value pairs being exchanged. Type mismatches or missing keys will cause errors on the receiver's end.
Parameters:`context` - The context used to send the broadcast.`watchappUuid` - A UUID uniquely identifying the target application. UUIDs for the stock kit applications are available in [`Constants`](/docs/pebblekit-android/com/getpebble/android/kit/Constants.md "class in com.getpebble.android.kit").`data` - A dictionary containing one-or-more key-value pairs. For more information about the types of data that can be stored, see [`PebbleDictionary`](/docs/pebblekit-android/com/getpebble/android/kit/util/PebbleDictionary.md "class in com.getpebble.android.kit.util").Throws:`IllegalArgumentException` - Thrown in the specified PebbleDictionary or UUID is invalid.
  - 
### sendDataToPebbleWithTransactionId

public static&nbsp;void&nbsp;sendDataToPebbleWithTransactionId(android.content.Context&nbsp;context, [UUID](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/util/UUID.html "class or interface in java.util")&nbsp;watchappUuid, [PebbleDictionary](/docs/pebblekit-android/com/getpebble/android/kit/util/PebbleDictionary.md "class in com.getpebble.android.kit.util")&nbsp;data, int&nbsp;transactionId) throws [IllegalArgumentException](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/IllegalArgumentException.html "class or interface in java.lang")

Send one-or-more key-value pairs to the watch-app identified by the provided UUID. The watch-app and phone-app must agree of the set and type of key-value pairs being exchanged. Type mismatches or missing keys will cause errors on the receiver's end.
Parameters:`context` - The context used to send the broadcast.`watchappUuid` - A UUID uniquely identifying the target application. UUIDs for the stock kit applications are available in [`Constants`](/docs/pebblekit-android/com/getpebble/android/kit/Constants.md "class in com.getpebble.android.kit").`data` - A dictionary containing one-or-more key-value pairs. For more information about the types of data that can be stored, see [`PebbleDictionary`](/docs/pebblekit-android/com/getpebble/android/kit/util/PebbleDictionary.md "class in com.getpebble.android.kit.util").`transactionId` - An integer uniquely identifying the transaction. This can be used to correlate messages sent to the Pebble and ACK/NACKs received from the Pebble.Throws:`IllegalArgumentException` - Thrown in the specified PebbleDictionary or UUID is invalid.
  - 
### sendAckToPebble

public static&nbsp;void&nbsp;sendAckToPebble(android.content.Context&nbsp;context, int&nbsp;transactionId) throws [IllegalArgumentException](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/IllegalArgumentException.html "class or interface in java.lang")

Send a message to the connected watch acknowledging the receipt of a PebbleDictionary. To avoid protocol timeouts on the watch, applications _must_ ACK or NACK all received messages.
Parameters:`context` - The context used to send the broadcast.`transactionId` - The transaction id of the message in which the data was received. Valid transaction IDs are between (0, 255).Throws:`IllegalArgumentException` - Thrown if an invalid transaction id is specified.
  - 
### sendNackToPebble

public static&nbsp;void&nbsp;sendNackToPebble(android.content.Context&nbsp;context, int&nbsp;transactionId) throws [IllegalArgumentException](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/IllegalArgumentException.html "class or interface in java.lang")

Send a message to the connected watch that the previously sent PebbleDictionary was not received successfully. To avoid protocol timeouts on the watch, applications _must_ ACK or NACK all received messages.
Parameters:`context` - The context used to send the broadcast.`transactionId` - The transaction id of the message in which the data was received. Valid transaction IDs are between (0, 255).Throws:`IllegalArgumentException` - Thrown if an invalid transaction id is specified.
  - 
### registerPebbleConnectedReceiver

public static&nbsp;android.content.BroadcastReceiver&nbsp;registerPebbleConnectedReceiver(android.content.Context&nbsp;context, android.content.BroadcastReceiver&nbsp;receiver)

A convenience function to assist in programatically registering a broadcast receiver for the 'CONNECTED' intent. To avoid leaking memory, activities registering BroadcastReceivers _must_ unregister them in the Activity's `Activity.onPause()` method.
Parameters:`context` - The context in which to register the BroadcastReceiver.`receiver` - The receiver to be registered.Returns:The registered receiver.See Also:
    - [`Constants.INTENT_PEBBLE_CONNECTED`](/docs/pebblekit-android/com/getpebble/android/kit/Constants.md#INTENT_PEBBLE_CONNECTED)
  - 
### registerPebbleDisconnectedReceiver

public static&nbsp;android.content.BroadcastReceiver&nbsp;registerPebbleDisconnectedReceiver(android.content.Context&nbsp;context, android.content.BroadcastReceiver&nbsp;receiver)

A convenience function to assist in programatically registering a broadcast receiver for the 'DISCONNECTED' intent. Go avoid leaking memory, activities registering BroadcastReceivers _must_ unregister them in the Activity's `Activity.onPause()` method.
Parameters:`context` - The context in which to register the BroadcastReceiver.`receiver` - The receiver to be registered.Returns:The registered receiver.See Also:
    - [`Constants.INTENT_PEBBLE_DISCONNECTED`](/docs/pebblekit-android/com/getpebble/android/kit/Constants.md#INTENT_PEBBLE_DISCONNECTED)
  - 
### registerReceivedDataHandler

public static&nbsp;android.content.BroadcastReceiver&nbsp;registerReceivedDataHandler(android.content.Context&nbsp;context, [PebbleKit.PebbleDataReceiver](/docs/pebblekit-android/com/getpebble/android/kit/PebbleKit.PebbleDataReceiver.md "class in com.getpebble.android.kit")&nbsp;receiver)

A convenience function to assist in programatically registering a broadcast receiver for the 'RECEIVE' intent. To avoid leaking memory, activities registering BroadcastReceivers _must_ unregister them in the Activity's `Activity.onPause()` method.
Parameters:`context` - The context in which to register the BroadcastReceiver.`receiver` - The receiver to be registered.Returns:The registered receiver.See Also:
    - [`Constants.INTENT_APP_RECEIVE`](/docs/pebblekit-android/com/getpebble/android/kit/Constants.md#INTENT_APP_RECEIVE)
  - 
### registerReceivedAckHandler

public static&nbsp;android.content.BroadcastReceiver&nbsp;registerReceivedAckHandler(android.content.Context&nbsp;context, [PebbleKit.PebbleAckReceiver](/docs/pebblekit-android/com/getpebble/android/kit/PebbleKit.PebbleAckReceiver.md "class in com.getpebble.android.kit")&nbsp;receiver)

A convenience function to assist in programatically registering a broadcast receiver for the 'RECEIVE\_ACK' intent. To avoid leaking memory, activities registering BroadcastReceivers _must_ unregister them in the Activity's `Activity.onPause()` method.
Parameters:`context` - The context in which to register the BroadcastReceiver.`receiver` - The receiver to be registered.Returns:The registered receiver.See Also:
    - [`Constants.INTENT_APP_RECEIVE_ACK`](/docs/pebblekit-android/com/getpebble/android/kit/Constants.md#INTENT_APP_RECEIVE_ACK)
  - 
### registerReceivedNackHandler

public static&nbsp;android.content.BroadcastReceiver&nbsp;registerReceivedNackHandler(android.content.Context&nbsp;context, [PebbleKit.PebbleNackReceiver](/docs/pebblekit-android/com/getpebble/android/kit/PebbleKit.PebbleNackReceiver.md "class in com.getpebble.android.kit")&nbsp;receiver)

A convenience function to assist in programatically registering a broadcast receiver for the 'RECEIVE\_NACK' intent. To avoid leaking memory, activities registering BroadcastReceivers _must_ unregister them in the Activity's `Activity.onPause()` method.
Parameters:`context` - The context in which to register the BroadcastReceiver.`receiver` - The receiver to be registered.Returns:The registered receiver.See Also:
    - [`Constants.INTENT_APP_RECEIVE_NACK`](/docs/pebblekit-android/com/getpebble/android/kit/Constants.md#INTENT_APP_RECEIVE_NACK)
  - 
### registerDataLogReceiver

public static&nbsp;android.content.BroadcastReceiver&nbsp;registerDataLogReceiver(android.content.Context&nbsp;context, [PebbleKit.PebbleDataLogReceiver](/docs/pebblekit-android/com/getpebble/android/kit/PebbleKit.PebbleDataLogReceiver.md "class in com.getpebble.android.kit")&nbsp;receiver)

A convenience function to assist in programatically registering a broadcast receiver for the 'DATA\_AVAILABLE' intent. To avoid leaking memory, activities registering BroadcastReceivers _must_ unregister them in the Activity's `Activity.onPause()` method.
Parameters:`context` - The context in which to register the BroadcastReceiver.`receiver` - The receiver to be registered.Returns:The registered receiver.See Also:
    - [`Constants.INTENT_DL_RECEIVE_DATA`](/docs/pebblekit-android/com/getpebble/android/kit/Constants.md#INTENT_DL_RECEIVE_DATA)
  - 
### requestDataLogsForApp

public static&nbsp;void&nbsp;requestDataLogsForApp(android.content.Context&nbsp;context, [UUID](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/util/UUID.html "class or interface in java.util")&nbsp;appUuid)

A convenience function to emit an intent to pebble.apk to request the data logs for a particular app. If data is available, pebble.apk will advertise the data via 'INTENT\_DL\_RECEIVE\_DATA' intents. To avoid leaking memory, activities registering BroadcastReceivers _must_ unregister them in the Activity's `Activity.onPause()` method.
Parameters:`context` - The context in which to register the BroadcastReceiver.`appUuid` - The app for which to request data logs.See Also:
    - [`Constants.INTENT_DL_RECEIVE_DATA`](/docs/pebblekit-android/com/getpebble/android/kit/Constants.md#INTENT_DL_RECEIVE_DATA)
    - [`Constants.INTENT_DL_REQUEST_DATA`](/docs/pebblekit-android/com/getpebble/android/kit/Constants.md#INTENT_DL_REQUEST_DATA)
