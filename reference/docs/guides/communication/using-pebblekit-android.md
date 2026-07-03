# PebbleKit Android

Source: https://developer.repebble.com/guides/communication/using-pebblekit-android/

# PebbleKit Android 2

Currently recommended way of communicating with the watch is to use PebbleKit Android 2. See [its documentation](https://github.com/pebble-dev/PebbleKitAndroid2) for more information.

# Legacy PebbleKit Android 1

[PebbleKit Android](https://github.com/pebble/pebble-android-sdk/) is a Java library that works with the Pebble SDK and can be embedded in any Android application. Using the classes and methods in this library, an Android companion app can find and exchange data with a Pebble watch.

This section assumes that the reader is familiar with basic Android development and Android Studio as an integrated development environment. Refer to the[Android Documentation](http://developer.android.com/sdk/index.html) for more information on installing the Android SDK.

Most PebbleKit Android methods require a `Context` parameter. An app can use`getApplicationContext()`, which is available from any `Activity`implementation.

### Setting Up PebbleKit Android

Add PebbleKit Android to an Android Studio project in the`app/build.gradle` file:

```
dependencies {
  compile 'com.getpebble:pebblekit:4.0.1'
}
```

### Sending Messages from Android

Since Android apps are built separately from their companion Pebble apps, there is no way for the build system to automatically create matching appmessage keys. You must therefore manually specify them in `package.json`, like so:

```
{"ContactName": 0,"Age": 1}
```

These numeric values can then be used as appmessage keys in your Android app.

Messages are constructed with the `PebbleDictionary` class and sent to a C watchapp or watchface using the `PebbleKit` class. The first step is to create a`PebbleDictionary` object:

```
// Create a new dictionaryPebbleDictionary dict = new PebbleDictionary();
```

Data items are added to the [`PebbleDictionary`](/docs/pebblekit-android/com/getpebble/android/kit/util/PebbleDictionary.md) using key-value pairs with the methods made available by the object, such as`addString()` and `addInt32()`. An example is shown below:

```
// The key representing a contact name is being transmittedfinal int AppKeyContactName = 0;final int AppKeyAge = 1;// Get data from the appfinal String contactName = getContact();final int age = getAge();// Add data to the dictionarydict.addString(AppKeyContactName, contactName);dict.addInt32(AppKeyAge, age);
```

Finally, the dictionary is sent to the C app by calling `sendDataToPebble()`with a UUID matching that of the C app that will receive the data:

```
final UUID appUuid = UUID.fromString("EC7EE5C6-8DDF-4089-AA84-C3396A11CC95");// Send the dictionaryPebbleKit.sendDataToPebble(getApplicationContext(), appUuid, dict);
```

Once delivered, this dictionary will be available in the C app via the[`AppMessageInboxReceived`](/docs/c/Foundation/AppMessage/#AppMessageInboxReceived "AppMessageInboxReceived") callback, as detailed in[_Sending and Receiving Data_](/guides/communication/sending-and-receiving-data.md#inbox-received).

### Receiving Messages on Android

Receiving messages from Pebble in a PebbleKit Android app requires a listener to be registered in the form of a `PebbleDataReceiver` object, which extends`BroadcastReceiver`:

```
// Create a new receiver to get AppMessages from the C appPebbleDataReceiver dataReceiver = new PebbleDataReceiver(appUuid) {@Overridepublic void receiveData(Context context, int transaction\_id,PebbleDictionary dict) {// A new AppMessage was received, tell PebblePebbleKit.sendAckToPebble(context, transaction\_id);}};
```

**Important**

PebbleKit apps **must** manually send an acknowledgement (Ack) to Pebble to inform it that the message was received successfully. Failure to do this will cause timeouts.

Once created, this receiver should be registered in `onResume()`, overridden from `Activity`:

```
@Overridepublic void onResume() {super.onResume();// Register the receiverPebbleKit.registerReceivedDataHandler(getApplicationContext(), dataReceiver);}
```

> Note: To avoid getting callbacks after the `Activity` or `Service` has exited, apps should attempt to unregister the receiver in `onPause()` with`unregisterReceiver()`.

With a receiver in place, data can be read from the provided [`PebbleDictionary`](/docs/pebblekit-android/com/getpebble/android/kit/util/PebbleDictionary.md)using analogous methods such as `getString()` and `getInteger()`. Before reading the value of a key, the app should first check that it exists using a `!= null`check.

The example shown below shows how to read an integer from the message, in the scenario that the watch is sending an age value to the Android companion app:

```
@Overridepublic void receiveData(Context context, int transaction\_id,PebbleDictionary dict) {// If the tuple is present...Long ageValue = dict.getInteger(AppKeyAge);if(ageValue != null) {// Read the integer valueint age = ageValue.intValue();}}
```

### Other Capabilities

In addition to sending and receiving messages, PebbleKit Android also allows more intricate interactions with Pebble. See the[PebbleKit Android Documentation](/docs/pebblekit-android/com/getpebble/android/kit/PebbleKit.md) for a complete list of available methods. Some examples are shown below of what is possible:

- Checking if the watch is connected:

- Registering for connection events with `registerPebbleConnectedReceiver()` and`registerPebbleDisconnectedReceiver()`, and a suitable `BroadcastReceiver`.

- Registering for Ack/Nack events with `registerReceivedAckHandler()` and`registerReceivedNackHandler()`.

- Launching and killing the watchapp with `startAppOnPebble()` and`closeAppOnPebble()`.
