# Accelerometer

Source: https://developer.repebble.com/guides/events-and-services/accelerometer/

The acceleromter sensor is included in every Pebble watch, and allows collection of acceleration and orientation data in watchapps and watchfaces. Data is available in two ways, each suitable to different types of watchapp:

- Taps events - Fires an event whenever a significant tap or shake of the watch occurs. Useful to 'shake to view' features.

- Data batches - Allows collection of data in batches at specific intervals. Useful for general accelerometer data colleciton.

As a significant source of regular callbacks, the accelerometer should be used as sparingly as possible to allow the watch to sleep and conserve power. For example, receiving data in batches once per second is more power efficient than receiving a single sample 25 times per second.

## About the Pebble Accelerometer

The Pebble accelerometer is oriented according to the diagram below, showing the direction of each of the x, y, and z axes.

![accel-axes](/assets/images/guides/pebble-apps/sensors/accel.png)

In the API, each axis value contained in an [`AccelData`](/docs/c/Foundation/Event_Service/AccelerometerService/#AccelData "AccelData") sample is measured in milli-Gs. The accelerometer is calibrated to measure a maximum acceleration of ±4G. Therefore, the range of possible values for each axis is -4000 to +4000.

The [`AccelData`](/docs/c/Foundation/Event_Service/AccelerometerService/#AccelData "AccelData") sample object also contains a `did_vibrate` field, set to`true` if the vibration motor was active during the sample collection. This could possibly contaminate those samples due to onboard vibration, so they should be discarded. Lastly, the `timestamp` field allows tracking of obtained accelerometer data over time.

## Using Taps

Adding a subscription to tap events allows a developer to react to any time the watch is tapped or experiences a shake along one of three axes. Tap events are received by registering an [`AccelTapHandler`](/docs/c/Foundation/Event_Service/AccelerometerService/#AccelTapHandler "AccelTapHandler") function, such as the one below:

```
static void accel\_tap\_handler(AccelAxisType axis, int32\_t direction) {// A tap event occured}
```

The `axis` parameter describes which axis the tap was detected along. The`direction` parameter is set to `1` for the positive direction, and `-1` for the negative direction.

A subscription can be added or removed at any time. While subscribed,`accel_tap_handler` will be called whenever a tap event is fired by the accelerometer. Adding a subscription is simple:

```
// Subscribe to tap eventsaccel\_tap\_service\_subscribe(accel\_tap\_handler);
```

```
// Unsubscribe from tap eventsaccel\_tap\_service\_unsubscribe();
```

## Using Data Batches

Accelerometer data can be received in batches at a chosen sampling rate by subscribing to the Accelerometer Data Service at any time:

```
uint32\_t num\_samples = 3;// Number of samples per batch/callback// Subscribe to batched data eventsaccel\_data\_service\_subscribe(num\_samples, accel\_data\_handler);
```

The [`AccelDataHandler`](/docs/c/Foundation/Event_Service/AccelerometerService/#AccelDataHandler "AccelDataHandler") function (called `accel_data_handler` in the example above) is called when a new batch of data is ready for consumption by the watchapp. The rate at which these occur is dictated by two things:

- The sampling rate - The number of samples the accelerometer device measures per second. One value chosen from the [`AccelSamplingRate`](/docs/c/Foundation/Event_Service/AccelerometerService/#AccelSamplingRate "AccelSamplingRate") `enum`.

- The number of samples per batch.

Some simple math will determine how often the callback will occur. For example, at the [`ACCEL_SAMPLING_50HZ`](/docs/c/Foundation/Event_Service/AccelerometerService/#ACCEL_SAMPLING_50HZ "ACCEL\_SAMPLING\_50HZ") sampling rate, and specifying 10 samples per batch will result in five calls per second.

When an event occurs, the acceleromater data can be read from the [`AccelData`](/docs/c/Foundation/Event_Service/AccelerometerService/#AccelData "AccelData")pointer provided in the callback. An example reading the first set of values is shown below:

```
static void accel\_data\_handler(AccelData \*data, uint32\_t num\_samples) {// Read sample 0's x, y, and z valuesint16\_t x = data[0].x;int16\_t y = data[0].y;int16\_t z = data[0].z;// Determine if the sample occured during vibration, and when it occuredbool did\_vibrate = data[0].did\_vibrate;uint64\_t timestamp = data[0].timestamp;if(!did\_vibrate) {// Print it outAPP\_LOG(APP\_LOG\_LEVEL\_INFO, "t: %llu, x: %d, y: %d, z: %d",timestamp, x, y, z);} else {// Discard with a warningAPP\_LOG(APP\_LOG\_LEVEL\_WARNING, "Vibration occured during collection");}}
```

The code above will output the first sample in each batch to app logs, which will look similar to the following:

```
[15:33:18] -data-service.c:21> t: 1449012797098, x: -111, y: -280, z: -1153
[15:33:18] -data-service.c:21> t: 1449012797305, x: -77, y: 40, z: -1014
[15:33:18] -data-service.c:21> t: 1449012797507, x: -60, y: 4, z: -1080
[15:33:19] -data-service.c:21> t: 1449012797710, x: -119, y: -55, z: -921
[15:33:19] -data-service.c:21> t: 1449012797914, x: 628, y: 64, z: -506
```
