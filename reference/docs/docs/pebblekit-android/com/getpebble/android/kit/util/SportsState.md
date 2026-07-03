# SportsState

Source: https://developer.repebble.com/docs/pebblekit-android/com/getpebble/android/kit/util/SportsState/

[java.lang.Object](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/Object.html "class or interface in java.lang")
com.getpebble.android.kit.util.SportsState

* * *

public class SportsStateextends [Object](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/Object.html "class or interface in java.lang")

This container class includes new values of time, distance, and pace or speed. To send the values to the watch use `synchronize`. This class is mutable, so consumers can update the values and synchronize the same instance again. Modifying the values of this class will not send the values. The consumer needs to invoke `synchronize` every time the UI needs to be updated.

- 
## Constructor Summary

Constructors

Constructor

Description

`SportsState()`

&nbsp;

- 
## Method Summary

All MethodsInstance MethodsConcrete Methods

Modifier and Type

Method

Description

`String`

`getCustomLabel()`

The custom label to show in the sports UI.

`String`

`getCustomValue()`

The custom value to show in the sports UI.

`float`

`getDistance()`

The current distance in kilometers or miles.

`byte`

`getHeartBPM()`

The current heart rate in beats per minute.

`int`

`getPaceInSec()`

The current pace in seconds per kilometer or seconds per mile.

`float`

`getSpeed()`

The current speed in kilometers per hour or miles per hour.

`int`

`getTimeInSec()`

The current time in seconds.

`void`

`setCustomLabel(String customLabel)`

Set the custom label to show in the sports UI.

`void`

`setCustomValue(String customValue)`

Set the custom value to show in the sports UI.

`void`

`setDistance(float distance)`

Set the current distance in kilometers or miles.

`void`

`setHeartBPM(byte heartBPM)`

Set the current heart rate in beats per minute.

`void`

`setPaceInSec(int paceInSec)`

Set the current pace in seconds per kilometer or seconds per mile.

`void`

`setSpeed(float speed)`

Set the current speed in kilometers per hour or miles per hour.

`void`

`setTimeInSec(int timeInSec)`

Set the current time in seconds.

`void`

`synchronize(android.content.Context context)`

Synchronizes the current state of the Sports App to the connected watch.

### Methods inherited from class&nbsp;java.lang.[Object](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/Object.html "class or interface in java.lang")
`clone, equals, finalize, getClass, hashCode, notify, notifyAll, toString, wait, wait, wait`

- 
## Constructor Details

  - 
### SportsState

public&nbsp;SportsState()
- 
## Method Details

  - 
### getTimeInSec

public&nbsp;int&nbsp;getTimeInSec()

The current time in seconds.
Returns:the current activity duration in seconds
  - 
### setTimeInSec

public&nbsp;void&nbsp;setTimeInSec(int&nbsp;timeInSec)

Set the current time in seconds. The possible range is currently limited from 0 to 35999, inclusive (9h 59min 59sec). Values larger or smaller than the limits will be transformed into the maximum or minimum, respectively. It will be presented as a duration string in the UI. Hours, minutes and seconds will be separated by colons. The hours value will only appear if the value is more than 1 hour.
Parameters:`timeInSec` - The current time to set, in seconds.
  - 
### getDistance

public&nbsp;float&nbsp;getDistance()

The current distance in kilometers or miles.
Returns:the current distance
  - 
### setDistance

public&nbsp;void&nbsp;setDistance(float&nbsp;distance)

Set the current distance in kilometers or miles. The possible range is currently limited from 0 to 99.9, inclusive. Values larger or smaller than the limits will be transformed into the maximum or minimum, respectively. It will be presented as a decimal number in the UI. The decimal part will be rounded to one digit. The unit of distance is dependent on the current unit setting.
Parameters:`distance` - The current distance to set, in kilometers or miles.
  - 
### getPaceInSec

public&nbsp;int&nbsp;getPaceInSec()

The current pace in seconds per kilometer or seconds per mile.
Returns:the current pace
  - 
### setPaceInSec

public&nbsp;void&nbsp;setPaceInSec(int&nbsp;paceInSec)

Set the current pace in seconds per kilometer or seconds per mile. The possible range is currently limited from 0 to 3599, inclusive (59min 59sec). Values larger or smaller than the limits will be transformed into the maximum or minimum, respectively. It will be presented as a duration string in the UI. Minutes and seconds will be separated by colons. Currently pace and speed cannot be presented at the same time. Setting speed will discard the value set through pace.
Parameters:`paceInSec` - The pace to set, in seconds per kilometer or seconds per mile.
  - 
### getSpeed

public&nbsp;float&nbsp;getSpeed()

The current speed in kilometers per hour or miles per hour.
Returns:the current speed
  - 
### setSpeed

public&nbsp;void&nbsp;setSpeed(float&nbsp;speed)

Set the current speed in kilometers per hour or miles per hour. The possible range is currently limited from 0 to 99.9, inclusive. Values larger or smaller than the limits will be transformed into the maximum or minimum, respectively. It will be presented as a decimal number in the UI. The decimal part will be rounded to one digit. Currently pace and speed cannot be presented at the same time. Setting pace will discard the value set through speed.
Parameters:`speed` - The current speed to set, in kilometers per hour or miles per hour.
  - 
### getHeartBPM

public&nbsp;byte&nbsp;getHeartBPM()

The current heart rate in beats per minute. If the heart rate has never been set before, this property will return zero.
Returns:the current heart rate
  - 
### setHeartBPM

public&nbsp;void&nbsp;setHeartBPM(byte&nbsp;heartBPM)

Set the current heart rate in beats per minute. Currently there is no way to stop sending heart rate values if one heart rate value was sent. The last value will be shown in the UI.
Parameters:`heartBPM` - The current heart rate to set, in beats per minute.
  - 
### getCustomLabel

public&nbsp;[String](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/String.html "class or interface in java.lang")&nbsp;getCustomLabel()

The custom label to show in the sports UI.
Returns:the custom label
  - 
### setCustomLabel

public&nbsp;void&nbsp;setCustomLabel([String](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/String.html "class or interface in java.lang")&nbsp;customLabel)

Set the custom label to show in the sports UI. The maximum number of characters is ~10, but this maximum is not enforced. The label will be sent in upper case to the watch. To be sent, both customLabel and customValue have to be set to non-null values.
Parameters:`customLabel` - The custom label to set.
  - 
### getCustomValue

public&nbsp;[String](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/String.html "class or interface in java.lang")&nbsp;getCustomValue()

The custom value to show in the sports UI.
Returns:the custom value
  - 
### setCustomValue

public&nbsp;void&nbsp;setCustomValue([String](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/String.html "class or interface in java.lang")&nbsp;customValue)

Set the custom value to show in the sports UI. The maximum number of characters is ~8, but the maximum is not enforced. To be sent, both customValue and customLabel have to be set to non-null values.
Parameters:`customValue` - The custom value to set.
  - 
### synchronize

public&nbsp;void&nbsp;synchronize(android.content.Context&nbsp;context)

Synchronizes the current state of the Sports App to the connected watch. The method tries to send the minimal set of changes since the last time the method was used, to try to minimize communication with the watch.
Parameters:`context` - The context used to send the broadcast.
