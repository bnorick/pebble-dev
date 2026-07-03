# Compass

Source: https://developer.repebble.com/guides/events-and-services/compass/

The [`CompassService`](/docs/c/Foundation/Event_Service/CompassService/ "CompassService") combines data from Pebble's accelerometer and magnetometer to automatically calibrate the compass and produce a[`CompassHeading`](/docs/c/Foundation/Event_Service/CompassService/#CompassHeading "CompassHeading"), containing an angle measured relative to magnetic north.

The compass service provides magnetic north and information about its status and accuracy through the [`CompassHeadingData`](/docs/c/Foundation/Event_Service/CompassService/#CompassHeadingData "CompassHeadingData") structure.

## Calibration

The compass service requires an initial calibration before it can return accurate results. Calibration is performed automatically by the system when first required. The [`compass_status`](/docs/c/Foundation/Event_Service/CompassService/#CompassHeadingData "CompassHeadingData") field indicates whether the compass service is calibrating. To help the calibration process, the app should show a message to the user asking them to move their wrists in different directions.

Refer to the [compass example](https://github.com/pebble-examples/feature-compass) for an example of how to implement this screen.

Calibration only runs while at least one app is subscribed to the compass service. If all apps unsubscribe before calibration is complete, the calibration is discarded and will start again from scratch the next time an app subscribes. Once calibration succeeds, it is saved for future reuse by all apps without recalibration. Putting the pebble on charge deletes any saved calibration.

## Magnetic North and True North

Depending on the user's location on Earth, the measured heading towards magnetic north and true north can significantly differ. This is due to magnetic variation, also known as 'declination'.

Pebble does not automatically correct the magnetic heading to return a true heading, but the API is designed so that this feature can be added in the future and the app will be able to automatically take advantage of it.

For a more precise heading, use the `magnetic_heading` field of[`CompassHeadingData`](/docs/c/Foundation/Event_Service/CompassService/#CompassHeadingData "CompassHeadingData") and use a webservice to retrieve the declination at the user's current location. Otherwise, use the `true_heading` field. This field will contain the `magnetic_heading` if declination is not available, or the true heading if declination is available. The field `is_declination_valid` will be true when declination is available. Use this information to tell the user whether the app is showing magnetic north or true north.

![Declination illustrated](/assets/images/guides/pebble-apps/sensors/declination.gif)

> To see the true extent of declination, see how declination has[changed over time](http://maps.ngdc.noaa.gov/viewers/historical_declination/).

## Battery Considerations

Using the compass will turn on both Pebble's magnetometer and accelerometer. Those two devices will have a slight impact on battery life. A much more significant battery impact will be caused by redrawing the screen too often or performing CPU-intensive work every time the compass heading is updated.

Use [`compass_service_subscribe()`](/docs/c/Foundation/Event_Service/CompassService/#compass_service_subscribe "compass\_service\_subscribe") if the app only needs to update its UI when new compass data is available, or else use [`compass_service_peek()`](/docs/c/Foundation/Event_Service/CompassService/#compass_service_peek "compass\_service\_peek") if this happens much less frequently.

## Defining "Up" on Pebble

Compass readings are always relative to the current orientation of Pebble. Using the accelerometer, the compass service figures out which direction the user is facing.

![Compass Orientation](/assets/images/guides/pebble-apps/sensors/compass-orientation.png)

The best orientation to encourage users to adopt while using a compass-enabled watchapp is with the top of the watch parallel to the ground. If the watch is raised so that the screen is facing the user, the plane will now be perpedicular to the screen, but still parallel to the ground.

## Angles and Degrees

The magnetic heading value is presented as a number between 0 and TRIG\_MAX\_ANGLE (65536). This range is used to give a higher level of precision for drawing commands, which is preferable to using only 360 degrees.

If you imagine an analogue clock face on your Pebble, the angle 0 is always at the 12 o'clock position, and the magnetic heading angle is calculated in a counter clockwise direction from 0.

This can be confusing to grasp at first, as it’s opposite of how direction is measured on a compass, but it's simple to convert the values into a clockwise direction:

```
int clockwise\_angle = TRIG\_MAX\_ANGLE - heading\_data.magnetic\_heading;
```

Once you have an angle relative to North, you can convert that to degrees using the helper function [`TRIGANGLE_TO_DEG()`](/docs/c/Foundation/Math/#TRIGANGLE_TO_DEG "TRIGANGLE\_TO\_DEG"):

```
int degrees = TRIGANGLE\_TO\_DEG(TRIG\_MAX\_ANGLE - heading\_data.magnetic\_heading);
```

## Subscribing to Compass Data

Compass heading events can be received in a watchapp by subscribing to the[`CompassService`](/docs/c/Foundation/Event_Service/CompassService/ "CompassService"):

```
// Subscribe to compass heading updatescompass\_service\_subscribe(compass\_heading\_handler);
```

The provided [`CompassHeadingHandler`](/docs/c/Foundation/Event_Service/CompassService/#CompassHeadingHandler "CompassHeadingHandler") function (called`compass_heading_handler` above) can be used to read the state of the compass, and the current heading if it is available. This value is given in the range of`0` to [`TRIG_MAX_ANGLE`](/docs/c/Foundation/Math/#TRIG_MAX_ANGLE "TRIG\_MAX\_ANGLE") to preserve precision, and so it can be converted using the [`TRIGANGLE_TO_DEG()`](/docs/c/Foundation/Math/#TRIGANGLE_TO_DEG "TRIGANGLE\_TO\_DEG") macro:

```
static void compass\_heading\_handler(CompassHeadingData heading\_data) {// Is the compass calibrated?switch(heading\_data.compass\_status) {case CompassStatusDataInvalid:APP\_LOG(APP\_LOG\_LEVEL\_INFO, "Not yet calibrated.");break;case CompassStatusCalibrating:APP\_LOG(APP\_LOG\_LEVEL\_INFO, "Calibration in progress. Heading is %ld",TRIGANGLE\_TO\_DEG(TRIG\_MAX\_ANGLE - heading\_data.magnetic\_heading));break;case CompassStatusCalibrated:APP\_LOG(APP\_LOG\_LEVEL\_INFO, "Calibrated! Heading is %ld",TRIGANGLE\_TO\_DEG(TRIG\_MAX\_ANGLE - heading\_data.magnetic\_heading));break;}}
```

By default, the callback will be triggered whenever the heading changes by one degree. To reduce the frequency of updates, change the threshold for heading changes by setting a heading filter:

```
// Only notify me when the heading has changed by more than 5 degrees.compass\_service\_set\_heading\_filter(DEG\_TO\_TRIGANGLE(5));
```

## Unsubscribing From Compass Data

When the app is done using the compass, stop receiving callbacks by unsubscribing:

```
compass\_service\_unsubscribe();
```

## Peeking at Compass Data

To fetch a compass heading, simply peek to get a single sample:

```
// Peek to get dataCompassHeadingData data;compass\_service\_peek(&data);
```

If not already subscribed, this temporarily subscribes the app to the compass service without a handler.

WARNING: Regardless of if you were already subscribed with a handler or not, calling `compass_service_peek()` sets a timer to unsubscribe after 11 seconds (refreshed on each call).

> Similar to the subscription-provided data, the app should examine the peeked[`CompassHeadingData`](/docs/c/Foundation/Event_Service/CompassService/#CompassHeadingData "CompassHeadingData") to determine if it is valid (i.e. the compass is calibrated). Note that as calibration requires an active subscription, and calibration can take longer than 11 seconds, to calibrate while only using peek you must keep calling `compass_service_peek()` over time to refresh its unsubscribe timer until calibration is successful.
