# PebbleKit iOS

Source: https://developer.repebble.com/guides/communication/using-pebblekit-ios/

> **Important: PebbleKit iOS has been discontinued.** Apple has made it increasingly difficult for third-party smartwatches to provide a competitive experience on iOS. Over the years, Apple has systematically restricted capabilities that were essential to Pebble's functionality, including the ability to reply to notifications, send messages, enable inter-app communication, and properly function when the companion app is in the background. These restrictions have made it nearly impossible to build a smartwatch experience on iOS that matches the capabilities available on Android. We encourage developers to focus on Android development where Pebble can deliver its full potential without artificial platform limitations. Learn more about Apple's restrictions and their impact on third-party wearables in [this blog post](https://ericmigi.com/blog/apple-restricts-pebble-from-being-awesome-with-iphones).

This section assumes that the reader has a basic knowledge of Objective-C, Xcode as an IDE, and the delegate and block patterns.

> PebbleKit iOS should be compatible if your app uses Swift. The framework itself is written in Objective-C to avoid the requirement of the Swift runtime in pure Objective-C apps, and to improve the backwards and forwards compatibility.

### Setting Up PebbleKit iOS

If the project is using [CocoaPods](http://cocoapods.org/) (which is the recommended approach), just add `pod 'PebbleKit'` to the `Podfile` and execute`pod install`.

After installing PebbleKit iOS in the project, perform these final steps:

- If the iOS app needs to run in the background, you should update your target’s “Capabilities” in Xcode. Enable “Background Modes” and select both “Uses Bluetooth LE accessories” and “Acts as a Bluetooth LE accessory”. This should add the keys `bluetooth-peripheral` (“App shares data using CoreBluetooth”) and `bluetooth-central` (“App communicates using CoreBluetooth”) to your target’s `Info.plist` file.
- If you are using Xcode 8 or greater (and recommended for previous versions), you must also add the key `NSBluetoothPeripheralUsageDescription` (“Privacy - Bluetooth Peripheral Usage Description”) to your `Info.plist`.

> To add PebbleKit iOS manually, or some other alternatives follow the steps in the [repository](https://github.com/pebble/pebble-ios-sdk/). The documentation might also include more information that might be useful. Read it carefully.

### Targeting a Companion App

Before an iOS companion app can start communicating or exchange messages with a watchapp on Pebble, it needs to give PebbleKit a way to identify the watchapp. The UUID of your watchapp is used for this purpose.

Set the app UUID associated with the PBPebbleCentral instance. A simple way to create a UUID in standard representation to `NSUUID` is shown here:

```
// Set UUID of watchappNSUUID \*myAppUUID = [[NSUUID alloc] initWithUUIDString:@"226834ae-786e-4302-a52f-6e7efc9f990b"];[PBPebbleCentral defaultCentral].appUUID = myAppUUID;
```

If you are trying to communicate with the built-in Sports or Golf apps, their UUID are available as part of PebbleKit with `PBSportsUUID` and`PBGolfUUID`. You must register those UUID if you intend to communicate with those apps.

### Becoming a Delegate

To communicate with a Pebble watch, the class must implement`PBPebbleCentralDelegate`:

```
@interfaceViewController () \<PBPebbleCentralDelegate\>
```

The `PBPebbleCentral` class should not be instantiated directly. Instead, always use the singleton provided by `[PBPebbleCentral defaultCentral]`. An example is shown below, with the Golf app UUID:

```
central = [PBPebbleCentral defaultCentral];central.appUUID = myAppUUID;[central run];
```

Once this is done, set the class to be the delegate:

```
[PBPebbleCentral defaultCentral].delegate = self;
```

This delegate will get two callbacks: `pebbleCentral:watchDidConnect:isNew:` and`pebbleCentral:watchDidDisconnect:` every time a Pebble connects or disconnects. The app won't get connection callbacks if the Pebble is already connected when the delegate is set.

Implement these to receive the associated connection/disconnection events:

```
-(void)pebbleCentral:(PBPebbleCentral \*)central watchDidConnect:(PBWatch \*)watch isNew:(BOOL)isNew {NSLog(@"Pebble connected: %@", watch.name);// Keep a reference to this watchself.connectedWatch = watch;}-(void)pebbleCentral:(PBPebbleCentral \*)central watchDidDisconnect:(PBWatch \*)watch {NSLog(@"Pebble disconnected: %@", watch.name);// If this was the recently connected watch, forget itif ([watch isEqual:self.connectedWatch]) {self.connectedWatch = nil;}}
```

### Initiating Bluetooth Communication

Once the iOS app is correctly set up to communicate with Pebble, the final step is to actually begin communication. No communication can take place until the following is called:

```
[[PBPebbleCentral defaultCentral] run];
```

> Once this occurs, the user _may_ be shown a dialog asking for confirmation that they want the app to communicate. This means the app should not call`run:` until the appropriate moment in the UI.

### Sending Messages from iOS

Since iOS apps are built separately from their companion Pebble apps, there is no way for the build system to automatically create matching app message keys. You must therefore manually specify them in `package.json`, like so:

```
{"Temperature": 0,"WindSpeed": 1,"WindDirection": 2,"RequestData": 3,"LocationName": 4}
```

These numeric values can then be used as app message keys in your iOS app.

Messages are constructed with the `NSDictionary` class and sent to the C watchapp or watchface by the `PBPebbleCentralDelegate` when the`appMessagesPushUpdate:` function is invoked.

To send a message, prepare an `NSDictionary` object with the data to be sent to the C watchapp. Data items are added to the [`NSDictionary`](https://developer.apple.com/library/mac/documentation/Cocoa/Reference/Foundation/Classes/NSDictionary_Class/)using key-value pairs of standard data types. An example containing a string and an integer is shown below:

```
NSDictionary \*update = @{ @(0):[NSNumber pb\_numberWithUint8:42],@(1):@"a string" };
```

Send this dictionary to the watchapp using `appMessagesPushUpdate:`. The first argument is the update dictionary to send and the second argument is a callback block that will be invoked when the data has been acknowledged by the watch (or if an error occurs).

```
[self.connectedWatch appMessagesPushUpdate:update onSent:^(PBWatch \*watch, NSDictionary \*update, NSError \*error) {if (!error) {NSLog(@"Successfully sent message.");} else {NSLog(@"Error sending message: %@", error);}}];
```

Once delivered, this dictionary will be available in the C app via the[`AppMessageInboxReceived`](/docs/c/Foundation/AppMessage/#AppMessageInboxReceived "AppMessageInboxReceived") callback, as detailed in[_Sending and Receiving Data_](/guides/communication/sending-and-receiving-data.md#inbox-received).

### Receiving Messages on iOS

To receive messages from a watchapp, register a receive handler (a block) with `appMessagesAddReceiveUpdateHandler:`. This block will be invoked with two parameters - a pointer to a `PBWatch` object describing the Pebble that sent the message and an `NSDictionary` with the message received.

```
[self.connectedWatch appMessagesAddReceiveUpdateHandler:^BOOL(PBWatch \*watch, NSDictionary \*update) {NSLog(@"Received message: %@", update);// Send Ack to Pebblereturn YES;}];
```

> Always return `YES` in the handler. This instructs PebbleKit to automatically send an ACK to Pebble, to avoid the message timing out.

Data can be read from the `NSDictionary` by first testing for each key's presence using a `!= nil` check, and reading the value if it is present:

```
NSNumber \*key = @1;// If the key is present in the received dictionaryif (update[key]) {// Read the integer valueint value = [update[key] intValue];}
```

### Other Capabilities

In addition to sending and receiving messages, PebbleKit iOS also allows more intricate interactions with Pebble. See the[PebbleKit iOS Documentation](/docs/pebblekit-ios.md) for more information. Some examples are shown below of what is possible:

- Checking if the watch is connected using the `connected` property of a`PBWatch`.

```
BOOL isConnected = self.watch.connected;
```

- Receiving `watchDidConnect` and `watchDidDisconnect` events through being a`PBDataloggingServiceDelegate`.

### Limitations of PebbleKit on iOS

The iOS platform imposes some restrictions on what apps can do with accessories. It also limits the capabilities of apps that are in the background. It is critical to understand these limitations when developing an app that relies on PebbleKit iOS.

On iOS, all communication between a mobile app and Pebble is managed through a communication session. This communication session is a protocol specific to iOS, with notable limitations that the reader should know and understand when developing an iOS companion app for Pebble.

#### Bluetooth Low Energy (BLE) Connections

For Pebble apps that communicate with Pebble in BLE mode, a session can be created for each app that requires one. This removes the 'one session only' restriction, but only for these BLE apps. Currently, there are several BLE only devices, such as Pebble Time Round, and Pebble 2, but all the devices using a firmware 3.8 or greater can use BLE to communicate with PebbleKit.

For BLE apps, the 'phone must launch' restriction is removed. The iOS companion app can be restarted by the watchapp if it stops working if user force-quits iOS app, or it crashes. Note that the app will not work after rebooting iOS device, which requires it be launched by the iPhone user once after boot.

#### Communication with firmware older than 3.0

PebbleKit iOS 3.1.1 is the last PebbleKit that supports communication with firmwares older than 3.0. PebbleKit iOS 4.0.0 can only communicate with Pebble devices with firmware newer than 3.0.

For newer devices like Pebble Time, Pebble Time Steel, Pebble Time Round, and Pebble 2 there should be no problem. For previous generation devices like Pebble and Pebble Steel it means that their users should upgrade their firmware to the latest firmware available for their devices using the new apps.

This change allows better compatibility and new features to be developed by 3rd parties.
