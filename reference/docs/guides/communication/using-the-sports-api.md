# Sports API

Source: https://developer.repebble.com/guides/communication/using-the-sports-api/

Every Pebble watch has two built-in system watchapps called the Sports app, and the Golf app. These apps are hidden from the launcher until launched via PebbleKit Android or PebbleKit iOS.

Both are designed to be generic apps that display sports-related data in common formats. The goal is to allow fitness and golf mobile apps to integrate with Pebble to show the wearer data about their activity without needing to create and maintain an additional app for Pebble. An example of a popular app that uses this approach is the[Runkeeper](http://apps.repebble.com/application/52e05bd5d8561de307000039)app.

The Sports and Golf apps are launched, closed, and controlled by PebbleKit in an Android or iOS app, shown by example in each section below. In both cases, the data fields that are available to be populated are different, but data is pushed in the same way.

## Available Data Fields

### Sports

#### aplite

#### basalt

#### chalk

 ![](/assets/images/guides/design-and-interaction/sports~aplite.png)

 ![](/assets/images/guides/design-and-interaction/sports~basalt.png)

 ![](/assets/images/guides/design-and-interaction/sports~chalk.png)

The sports app displays activity duration and distance which can apply to a wide range of sports, such as cycling or running. A configurable third field is also available that displays pace or speed, depending on the app's preference. The Sports API also allows the app to be configured to display the labels of each field in metric (the default) or imperial units.

The action bar is used to prompt the user to use the Select button to pause and resume their activity session. The companion app is responsible for listening for these events and implementing the pause/resume operation as appropriate.

### Golf

#### aplite

#### basalt

#### chalk

 ![](/assets/images/guides/design-and-interaction/golf~aplite.png)

 ![](/assets/images/guides/design-and-interaction/golf~basalt.png)

 ![](/assets/images/guides/design-and-interaction/golf~chalk.png)

The Golf app is specialized to displaying data relevant to golf games, including par and hole numbers, as well as front, mid, and rear yardage.

Similar to the Sports app, the action bar is used to allow appropriate feedback to the companion app. In this case the actions are an 'up', 'ball' and 'down' events which the companion should handle as appropriate.

## With PebbleKit Android

Once an Android app has set up[_PebbleKit Android_](/guides/communication/using-pebblekit-android.md), the Sports and Golf apps can be launched and customized as appropriate.

### Launching Sports and Golf

To launch one of the Sports API apps, simply call `startAppOnPebble()` and supply the UUID from the `Constants` class:

```
// Launch the Sports appPebbleKit.startAppOnPebble(getApplicationContext(), Constants.SPORTS\_UUID);
```

### Customizing Sports

To choose which unit type is used, construct and send a `PebbleDictionary`containing the desired value from the `Constants` class. Either`SPORTS_UNITS_IMPERIAL` or `SPORTS_UNITS_METRIC` can be used:

```
PebbleDictionary dict = new PebbleDictionary();// Display imperial unitsdict.addUint8(Constants.SPORTS\_UNITS\_KEY, Constants.SPORTS\_UNITS\_IMPERIAL);PebbleKit.sendDataToPebble(getApplicationContext(), Constants.SPORTS\_UUID, dict);
```

To select between 'pace' or 'speed' as the label for the third field, construct and send a `PebbleDictionary` similar to the example above. This can be done in the same message as unit selection:

```
PebbleDictionary dict = new PebbleDictionary();// Display speed instead of pacedict.addUint8(Constants.SPORTS\_LABEL\_KEY, Constants.SPORTS\_DATA\_SPEED);PebbleKit.sendDataToPebble(getApplicationContext(), Constants.SPORTS\_UUID, dict);
```

> Note: The Golf app does not feature any customizable fields.

### Displaying Data

Data about the current activity can be sent to either of the Sports API apps using a `PebbleDictionary`. For example, to show a value for duration and distance in the Sports app:

```
PebbleDictionary dict = new PebbleDictionary();// Show a value for duration and distancedict.addString(Constants.SPORTS\_TIME\_KEY, "12:52");dict.addString(Constants.SPORTS\_DISTANCE\_KEY, "23.8");PebbleKit.sendDataToPebble(getApplicationContext(), Constants.SPORTS\_UUID, dict);
```

Read the [`Constants`](/docs/pebblekit-android/com/getpebble/android/kit/Constants.md)documentation to learn about all the available parameters that can be used for customization.

### Handling Button Events

When a button event is generated from one of the Sports API apps, a message is sent to the Android companion app, which can be processed using a`PebbleDataReceiver`. For example, to listen for a change in the state of the Sports app, search for `Constants.SPORTS_STATE_KEY` in the received`PebbleDictionary`. The user is notified in the example below through the use of an Android[`Toast`](http://developer.android.com/guide/topics/ui/notifiers/toasts.html):

```
// Create a receiver for when the Sports app state changesPebbleDataReceiver reciever = new PebbleKit.PebbleDataReceiver(Constants.SPORTS\_UUID) {@Overridepublic void receiveData(Context context, int id, PebbleDictionary data) {// Always ACKnowledge the last message to prevent timeoutsPebbleKit.sendAckToPebble(getApplicationContext(), id);// Get action and display as ToastLong value = data.getUnsignedIntegerAsLong(Constants.SPORTS\_STATE\_KEY);if(value != null) {int state = value.intValue();String text = (state == Constants.SPORTS\_STATE\_PAUSED)? "Resumed!" : "Paused!";Toast.makeText(getApplicationContext(), text, Toast.LENGTH\_SHORT).show();}}};// Register the receiverPebbleKit.registerReceivedDataHandler(getApplicationContext(), receiver);
```

## With PebbleKit iOS

Once an iOS app has set up [_PebbleKit iOS_](/guides/communication/using-pebblekit-ios.md), the Sports and Golf apps can be launched and customized as appropriate. The companion app should set itself as a delegate of `PBPebbleCentralDelegate`, and assign a `PBWatch` property once `watchDidConnect:` has fired. This `PBWatch`object will then be used to manipulate the Sports API apps.

Read _Becoming a Delegate_ in the[_PebbleKit iOS_](/guides/communication/using-pebblekit-ios.md) guide to see how this is done.

### Launching Sports and Golf

To launch one of the Sports API apps, simply call `sportsAppLaunch:` or`golfAppLaunch:` as appropriate:

```
[self.watch sportsAppLaunch:^(PBWatch \* \_Nonnull watch,NSError \* \_Nullable error) {NSLog(@"Sports app was launched");}];
```

### Customizing Sports

To choose which unit type is used, call `sportsAppSetMetric:` with the desired`isMetric` `BOOL`:

```
BOOL isMetric = YES;[self.watch sportsAppSetMetric:isMetric onSent:^(PBWatch \* \_Nonnull watch,NSError \* \_Nonnull error) {if (!error) {NSLog(@"Successfully sent message.");} else {NSLog(@"Error sending message: %@", error);}}];
```

To select between 'pace' or 'speed' as the label for the third field, call`sportsAppSetLabel:` with the desired `isPace` `BOOL`:

```
BOOL isPace = YES;[self.watch sportsAppSetLabel:isPace onSent:^(PBWatch \* \_Nonnull watch,NSError \* \_Nullable error) {if (!error) {NSLog(@"Successfully sent message.");} else {NSLog(@"Error sending message: %@", error);}}];
```

> Note: The Golf app does not feature any customizable fields.

### Displaying Data

Data about the current activity can be sent to either the Sports or Golf app using `sportsAppUpdate:` or `golfAppUpdate:`. For example, to show a value for duration and distance in the Sports app:

```
// Construct a dictionary of dataNSDictionary \*update = @{ PBSportsTimeKey: @"12:34",PBSportsDistanceKey: @"6.23" };// Send the data to the Sports app[self.watch sportsAppUpdate:update onSent:^(PBWatch \* \_Nonnull watch,NSError \* \_Nullable error) {if (!error) {NSLog(@"Successfully sent message.");} else {NSLog(@"Error sending message: %@", error);}}];
```

Read the [`PBWatch`](/docs/pebblekit-ios/Classes/PBWatch.md) documentation to learn about all the available methods and values for customization.

### Handling Button Events

When a button event is generated from one of the Sports API apps, a message is sent to the Android companion app, which can be processed using`sportsAppAddReceiveUpdateHandler` and supplying a block to be run when a message is received. For example, to listen for change in state of the Sports app, check the value of the provided `SportsAppActivityState`:

```
// Register to get state updates from the Sports app[self.watch sportsAppAddReceiveUpdateHandler:^BOOL(PBWatch \*watch,SportsAppActivityState state) {// Display the new state of the watchappswitch (state) {case SportsAppActivityStateRunning:NSLog(@"Watchapp now running.");break;case SportsAppActivityStatePaused:NSLog(@"Watchapp now paused.");break;default: break;}// Finallyreturn YES;}];
```
