# AccelerometerService

Source: https://developer.repebble.com/docs/c/Foundation/Event_Service/AccelerometerService/index.html

Using the Pebble accelerometer

The AccelerometerService enables the Pebble accelerometer to detect taps, perform measures at a given frequency, and transmit samples in batches to save CPU time and processing.

For available code samples, see the [feature-accel-discs](https://github.com/pebble-examples/feature-accel-discs/) example app.

## Function Documentation

int accel\_service\_peek([AccelData](/docs/c/Foundation/Event_Service/AccelerometerService/#AccelData) \* data)

Peek at the last recorded reading.

##### Note

Cannot be used when subscribed to accelerometer data events.

#### Parameters
 data (out)

a pointer to a pre-allocated [AccelData](/docs/c/Foundation/Event_Service/AccelerometerService/#AccelData) item

#### Returns

-1 if the accel is not running

-2 if subscribed to accelerometer events.

int accel\_service\_set\_sampling\_rate([AccelSamplingRate](/docs/c/Foundation/Event_Service/AccelerometerService/#AccelSamplingRate) rate)

Change the accelerometer sampling rate.

#### Parameters
 rate

The sampling rate in Hz (10Hz, 25Hz, 50Hz, and 100Hz possible)

int accel\_service\_set\_samples\_per\_update([uint32\_t](/docs/c/Standard_C/#uint32_t) num\_samples)

Change the number of samples buffered between each accelerometer data event.

#### Parameters
 num\_samples

the number of samples to buffer, between 0 and 25.

void accel\_data\_service\_subscribe([uint32\_t](/docs/c/Standard_C/#uint32_t) samples\_per\_update, [AccelDataHandler](/docs/c/Foundation/Event_Service/AccelerometerService/#AccelDataHandler) handler)

Subscribe to the accelerometer data event service. Once subscribed, the handler gets called every time there are new accelerometer samples available.

##### Note

Cannot use [accel\_service\_peek()](/docs/c/Foundation/Event_Service/AccelerometerService/#accel_service_peek) when subscribed to accelerometer data events.

#### Parameters
 handler

A callback to be executed on accelerometer data events

 samples\_per\_update

the number of samples to buffer, between 0 and 25.

void accel\_data\_service\_unsubscribe(void)

Unsubscribe from the accelerometer data event service. Once unsubscribed, the previously registered handler will no longer be called.

void accel\_tap\_service\_subscribe([AccelTapHandler](/docs/c/Foundation/Event_Service/AccelerometerService/#AccelTapHandler) handler)

Subscribe to the accelerometer tap event service. Once subscribed, the handler gets called on every tap event emitted by the accelerometer.

#### Parameters
 handler

A callback to be executed on tap event

void accel\_tap\_service\_unsubscribe(void)

Unsubscribe from the accelerometer tap event service. Once unsubscribed, the previously registered handler will no longer be called.

void accel\_raw\_data\_service\_subscribe([uint32\_t](/docs/c/Standard_C/#uint32_t) samples\_per\_update, [AccelRawDataHandler](/docs/c/Foundation/Event_Service/AccelerometerService/#AccelRawDataHandler) handler)

Subscribe to the accelerometer raw data event service. Once subscribed, the handler gets called every time there are new accelerometer samples available.

##### Note

Cannot use [accel\_service\_peek()](/docs/c/Foundation/Event_Service/AccelerometerService/#accel_service_peek) when subscribed to accelerometer data events.

#### Parameters
 handler

A callback to be executed on accelerometer data events

 samples\_per\_update

the number of samples to buffer, between 0 and 25.

## Data Structure Documentation

struct AccelData

A single accelerometer sample for all three axes including timestamp and vibration rumble status.

#### Data Fields
int16\_t x

acceleration along the x axis

int16\_t y

acceleration along the y axis

int16\_t z

acceleration along the z axis

bool did\_vibrate

true if the watch vibrated when this sample was collected

uint64\_t timestamp

timestamp, in milliseconds

struct AccelRawData

A single accelerometer sample for all three axes.

#### Data Fields
int16\_t x

acceleration along the x axis

int16\_t y

acceleration along the y axis

int16\_t z

acceleration along the z axis

## Enum Documentation

enum AccelAxisType

Enumerated values defining the three accelerometer axes.

#### Enumerators
ACCEL\_AXIS\_X

Accelerometer's X axis. The positive direction along the X axis goes toward the right of the watch.

ACCEL\_AXIS\_Y

Accelerometer's Y axis. The positive direction along the Y axis goes toward the top of the watch.

ACCEL\_AXIS\_Z

Accelerometer's Z axis. The positive direction along the Z axis goes vertically out of the watchface.

enum AccelSamplingRate

Valid accelerometer sampling rates, in Hz.

#### Enumerators
ACCEL\_SAMPLING\_10HZ

10 HZ sampling rate

ACCEL\_SAMPLING\_25HZ

25 HZ sampling rate [Default]

ACCEL\_SAMPLING\_50HZ

50 HZ sampling rate

ACCEL\_SAMPLING\_100HZ

100 HZ sampling rate

## Typedef Documentation

 typedef void(\* AccelDataHandler)(AccelData \*data, uint32\_t num\_samples) 

Callback type for accelerometer data events.

#### Parameters
 data

Pointer to the collected accelerometer samples.

 num\_samples

the number of samples stored in data.

 typedef void(\* AccelRawDataHandler)(AccelRawData \*data, uint32\_t num\_samples, uint64\_t timestamp) 

Callback type for accelerometer raw data events.

#### Parameters
 data

Pointer to the collected accelerometer samples.

 num\_samples

the number of samples stored in data.

 timestamp

the timestamp, in ms, of the first sample.

 typedef void(\* AccelTapHandler)(AccelAxisType axis, int32\_t direction) 

Callback type for accelerometer tap events.

#### Parameters
 axis

the axis on which a tap was registered (x, y, or z)

 direction

the direction (-1 or +1) of the tap
