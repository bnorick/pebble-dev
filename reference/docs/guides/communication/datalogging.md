# Datalogging

Source: https://developer.repebble.com/guides/communication/datalogging/

In addition to the more realtime [`AppMessage`](/docs/c/Foundation/AppMessage/ "AppMessage") API, the Pebble SDK also includes the [`Datalogging`](/docs/c/Foundation/DataLogging/ "DataLogging") API. This is useful for applications where data can be sent in batches at time intervals that make the most sense (for example, to save battery power by allowing the watch to spend more time sleeping).

Datalogging also allows upto 640 kB of data to be buffered on the watch until a connection is available, instead of requiring a connection be present at all times. If data is logged while the watch is disconnected, it will be transferred to the Pebble mobile app in batches for processing at the next opportunity. The data is then passed on to any [_PebbleKit Android_](/guides/communication/using-pebblekit-android.md) or [_PebbleKit iOS_](/guides/communication/using-pebblekit-ios.md) companion app that wishes to process it.

## Collecting Data

Datalogging can capture any values that are compatible with one of the[`DataLoggingItemType`](/docs/c/Foundation/DataLogging/#DataLoggingItemType "DataLoggingItemType") `enum` (byte array, unsigned integer, and integer) values, with common sources including accelerometer data or compass data.

### Creating a Session

Data is logged to a 'session' with a unique identifier or tag, which allows a single app to have multiple data logs for different types of data. First, define the identifier(s) that should be used where appropriate:

```
// The log's ID. Only one required in this example#define TIMESTAMP\_LOG 1
```

Next, a session must first be created before any data can be logged to it. This should be done during app initialization, or just before the first time an app needs to log some data:

```
// The session reference variablestatic DataLoggingSessionRef s\_session\_ref;
```

```
static void init() {// Begin the sessions\_session\_ref = data\_logging\_create(TIMESTAMP\_LOG, DATA\_LOGGING\_INT, sizeof(int), true);/\* ... \*/}
```

> Note: The final parameter of [`data_logging_create()`](/docs/c/Foundation/DataLogging/#data_logging_create "data\_logging\_create") allows a previous log session to be continued, instead of starting from screatch on each app launch.

### Logging Data

Once the log has been created or resumed, data collection can proceed. Each call to [`data_logging_log()`](/docs/c/Foundation/DataLogging/#data_logging_log "data\_logging\_log") will add a new entry to the log indicated by the[`DataLoggingSessionRef`](/docs/c/Foundation/DataLogging/#DataLoggingSessionRef "DataLoggingSessionRef") variable provided. The success of each logging operation can be checked using the [`DataLoggingResult`](/docs/c/Foundation/DataLogging/#DataLoggingResult "DataLoggingResult") returned:

```
const int value = 16;const uint32\_t num\_values = 1;// Log a single valueDataLoggingResult result = data\_logging\_log(s\_session\_ref, &value, num\_values);// Was the value successfully stored? If it failed, print the reasonif(result != DATA\_LOGGING\_SUCCESS) {APP\_LOG(APP\_LOG\_LEVEL\_ERROR, "Error logging data: %d", (int)result);}
```

### Finishing a Session

Once all data has been logged or the app is exiting, the session must be finished to signify that the data is to be either transferred to the connected phone (if available), or stored for later transmission.

```
// Finish the session and sync data if appropriatedata\_logging\_finish(s\_session\_ref);
```

> Note: Once a session has been finished, data cannot be logged to its[`DataLoggingSessionRef`](/docs/c/Foundation/DataLogging/#DataLoggingSessionRef "DataLoggingSessionRef") until it is resumed or began anew.

## Receiving Data

> Note: Datalogging data cannot be received via PebbleKit JS.

Data collected with the [`Datalogging`](/docs/c/Foundation/DataLogging/ "DataLogging") API can be received and processed in a mobile companion app using PebbleKit Android or PebbleKit iOS. This enables it to be used in a wide range of general applications, such as detailed analysis of accelerometer data for health research, or transmission to a third-party web service.

### With PebbleKit Android

PebbleKit Android allows collection of data by registering a`PebbleDataLogReceiver` within your `Activity` or `Service`. When creating a receiver, be careful to provide the correct UUID to match that of the watchapp that is doing that data collection. For example:

```
// The UUID of the watchappprivate UUID APP\_UUID = UUID.fromString("64fcb54f-76f0-418a-bd7d-1fc1c07c9fc1");
```

Use the following overridden methods to collect data and determine when the session has been finished by the watchapp. In the example below, each new integer received represents the uptime of the watchapp, and is displayed in an Android `TextView`:

```
// Create a receiver to collect logged dataPebbleKit.PebbleDataLogReceiver dataLogReceiver = new PebbleKit.PebbleDataLogReceiver(APP\_UUID) {@Overridepublic void receiveData(Context context, UUID logUuid, Long timestamp, Long tag, int data) {// super() (removed from IDE-generated stub to avoid exception)Log.i(TAG, "New data for session " + tag + "!");// Cumulatively add the new data item to a TextView's current textString current = dataView.getText().toString();current += timestamp.toString() + ": " + data + "s since watchapp launch.\n";dataView.setText(current);}@Overridepublic void onFinishSession(Context context, UUID logUuid, Long timestamp, Long tag) {Log.i(TAG, "Session " + tag + " finished!");}};// Register the receiverPebbleKit.registerDataLogReceiver(getApplicationContext(), dataLogReceiver);
```

**Important**

If your Java IDE automatically adds a line of code to call super() when you create the method, the code will result in an UnsupportedOperationException. Ensure you remove this line to avoid the exception.

Once the `Activity` or `Service` is closing, you should attempt to unregister the receiver. However, this is not always required (and will cause an exception to be thrown if invoked when not required), so use a `try, catch` statement:

```
@Overrideprotected void onPause() {super.onPause();try {unregisterReceiver(dataLogReceiver);} catch(Exception e) {Log.w(TAG, "Receiver did not need to be unregistered");}}
```

### With PebbleKit iOS

The process of collecing data via a PebbleKit iOS companion mobile app is similar to that of using PebbleKit Android. Once your app is a delegate of[`PBDataLoggingServiceDelegate`](/docs/pebblekit-ios/Protocols/PBDataLoggingServiceDelegate.md "PBDataLoggingServiceDelegate") (see [_PebbleKit iOS_](/guides/communication/using-pebblekit-ios.md) for details), simply register the class as a datalogging delegate:

```
// Get datalogging data by becoming the delegate[[PBPebbleCentral defaultCentral] dataLoggingServiceForAppUUID:myAppUUID].delegate = self;
```

Being a datalogging delegate allows the class to receive two additional[callbacks](/docs/pebblekit-ios/Protocols/PBDataLoggingServiceDelegate.md) for when new data is available, and when the session has been finished by the watch. Implement these callbacks to read the new data:

```
-(BOOL)dataLoggingService:(PBDataLoggingService \*)servicehasSInt32s:(const SInt32 [])datanumberOfItems:(UInt16)numberOfItemsforDataLog:(PBDataLoggingSessionMetadata \*)log {NSLog(@"New data received!");// Append newest data to displayed stringNSString \*current = self.dataView.text;NSString \*newString = [NSString stringWithFormat:@"New item: %d", data[0]];current = [current stringByAppendingString:newString];self.dataView.text = current;return YES;}-(void)dataLoggingService:(PBDataLoggingService \*)servicelogDidFinish:(PBDataLoggingSessionMetadata \*)log {NSLog(@"Finished data log: %@", log);}
```

### Special Considerations for iOS Apps

- The logic to deal with logs with the same type of data (i.e., the same tag/type) but from different sessions (different timestamps) must be created by the developer using the delegate callbacks.

- To check whether the data belongs to the same log or not, use `-isEqual:` on`PBDataLoggingSessionMetadata`. For convenience,`PBDataLoggingSessionMetadata` can be serialized using `NSCoding`.

- Using multiple logs in parallel (for example to transfer different kinds of information) will require extra logic to re-associate the data from these different logs, which must also be implemented by the developer.
