# CompassService

Source: https://developer.repebble.com/docs/c/Foundation/Event_Service/CompassService/index.html

The Compass Service combines information from Pebble's accelerometer and magnetometer to automatically calibrate the compass and transform the raw magnetic field information into a [CompassHeading](/docs/c/Foundation/Event_Service/CompassService/#CompassHeading), that is an angle to north. It also provides magnetic north and information about its status and accuracy through the [CompassHeadingData](/docs/c/Foundation/Event_Service/CompassService/#CompassHeadingData) structure. The API is designed to also provide true north in a future release.

Note that not all platforms have compasses. To check for the presence of a compass at compile time for the current platform use the `PBL_COMPASS` define.

To learn more about the Compass Service and how to use it, read the [Determining Direction](https://developer.getpebble.com/guides/pebble-apps/sensors/magnetometer/) guide.

For available code samples, see the [feature-compass](https://github.com/pebble-examples/feature-compass) example.

## Function Documentation

int compass\_service\_set\_heading\_filter([CompassHeading](/docs/c/Foundation/Event_Service/CompassService/#CompassHeading) filter)

Set the minimum angular change required to generate new compass heading events. The angular distance is measured relative to the last delivered heading event. Use 0 to be notified of all movements. Negative values and values \> TRIG\_MAX\_ANGLE / 2 are not valid. The default value of this property is TRIG\_MAX\_ANGLE / 360.

#### Returns

0, success.

Non-Zero, if filter is invalid.

#### See Also
[compass\_service\_subscribe](/docs/c/Foundation/Event_Service/CompassService/#compass_service_subscribe)

void compass\_service\_subscribe([CompassHeadingHandler](/docs/c/Foundation/Event_Service/CompassService/#CompassHeadingHandler) handler)

Subscribe to the compass heading event service. Once subscribed, the handler gets called every time the angular distance relative to the previous value exceeds the configured filter.

#### Parameters
 handler

A callback to be executed on heading events

#### See Also
[compass\_service\_set\_heading\_filter](/docs/c/Foundation/Event_Service/CompassService/#compass_service_set_heading_filter)  
[compass\_service\_unsubscribe](/docs/c/Foundation/Event_Service/CompassService/#compass_service_unsubscribe)

void compass\_service\_unsubscribe(void)

Unsubscribe from the compass heading event service. Once unsubscribed, the previously registered handler will no longer be called.

#### See Also
[compass\_service\_subscribe](/docs/c/Foundation/Event_Service/CompassService/#compass_service_subscribe)

int compass\_service\_peek([CompassHeadingData](/docs/c/Foundation/Event_Service/CompassService/#CompassHeadingData) \* data)

Peek at the last recorded reading.

#### Parameters
 data (out)

a pointer to a pre-allocated [CompassHeadingData](/docs/c/Foundation/Event_Service/CompassService/#CompassHeadingData)

#### Returns

Always returns 0 to indicate success.

## Data Structure Documentation

struct CompassHeadingData

Structure containing a single heading towards magnetic and true north.

#### Data Fields
[CompassHeading](/docs/c/Foundation/Event_Service/CompassService/#CompassHeading) magnetic\_heading

Measured angle that increases counter-clockwise from magnetic north (use `int clockwise_heading = TRIG_MAX_ANGLE - heading_data.magnetic_heading;` for example to find your heading clockwise from magnetic north).

[CompassHeading](/docs/c/Foundation/Event_Service/CompassService/#CompassHeading) true\_heading

Currently same value as magnetic\_heading (reserved for future implementation).

[CompassStatus](/docs/c/Foundation/Event_Service/CompassService/#CompassStatus) compass\_status

Indicates the current state of the Compass Service calibration.

bool is\_declination\_valid

Currently always false (reserved for future implementation).

## Enum Documentation

enum CompassStatus

Enum describing the current state of the Compass Service.

#### Enumerators
CompassStatusUnavailable

The Compass Service is unavailable.

CompassStatusDataInvalid

Compass is calibrating: data is invalid and should not be used Data will become valid once calibration is complete.

CompassStatusCalibrating

Compass is calibrating: the data is valid but the calibration is still being refined.

CompassStatusCalibrated

Compass data is valid and the calibration has completed.

## Typedef Documentation

 typedef int32\_t CompassHeading

Represents an angle relative to get to a reference direction, e.g. (magnetic) north. The angle value is scaled linearly, such that a value of TRIG\_MAX\_ANGLE corresponds to 360 degrees or 2 PI radians. Thus, if heading towards north, north is 0, west is TRIG\_MAX\_ANGLE/4, south is TRIG\_MAX\_ANGLE/2, and so on.

 typedef void(\* CompassHeadingHandler)(CompassHeadingData heading) 

Callback type for compass heading events.

#### Parameters
 heading

copy of last recorded heading
