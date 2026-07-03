# PBSportsUpdate Class Reference

Source: https://developer.repebble.com/docs/pebblekit-ios/Classes/PBSportsUpdate/

| Inherits from | NSObject |
| Declared in | PBWatch+Sports.h |

## Overview

Packages a UI update of the sports app.

This container class includes new values of time, distance, pace or speed, heart rate, and a custom label/value. To send the values to the watch use [[PBSportsUpdate updateWatch:completion:]](#//api/name/updateWatch:completion:).

The class is mutable, so consumers can update the values and send the same instance again. Modifying the values of this class will not send the values. The consumer needs to invoke [[PBSportsUpdate updateWatch:completion:]](#//api/name/updateWatch:completion:) every[time](#//api/name/time) the UI needs to be updated.

## Other Methods

### time

The current time in seconds.

`@property (nonatomic) NSTimeInterval time`

#### Discussion

The possible range is currently limited from -35999 to 35999, inclusive (±9h 59min 59sec). Values larger or smaller than the limits will be transformed into the maximum or minimum, respectively.

It will be presented as a duration string in the UI. Hours, minutes and seconds will be separated by colons. The hours value will only appear if the value is more than 1 hour. The decimal part will be discarded for the presentation.

#### Declared In

`PBWatch+Sports.h`

### distance

The current distance in kilometers or miles.

`@property (nonatomic) float distance`

#### Discussion

The possible range is currently limited from -99.9 to 99.9, inclusive. Values larger or smaller than the limits will be transformed into the maximum or minimum, respectively.

It will be presented as a decimal number in the UI. The decimal part will be rounded to one digit.

The unit of distance is dependent on the current unit setting.

#### See Also

- `[PBWatch sportsAppSetMetric:onSent:]`

#### Declared In

`PBWatch+Sports.h`

### pace

The current pace in seconds per kilometer or seconds per mile.

`@property (nonatomic) NSTimeInterval pace`

#### Discussion

The possible range is currently limited from -3599 to 3599, inclusive (±59min 59sec). Values larger or smaller than the limits will be transformed into the maximum or minimum, respectively.

It will be presented as a duration string in the UI. Minutes and seconds will be separated by colons. The decimal part will be discarded for the presentation.

Currently pace and [speed](#//api/name/speed) cannot be presented at the same [time](#//api/name/time). Setting [speed](#//api/name/speed)will discard the value set through pace.

#### Declared In

`PBWatch+Sports.h`

### speed

The current speed in kilometers per hour or miles per hour.

`@property (nonatomic) float speed`

#### Discussion

The possible range is currently limited from -99.9 to 99.9, inclusive. Values larger or smaller than the limits will be transformed into the maximum or minimum, respectively.

It will be presented as a decimal number in the UI. The decimal part will be rounded to one digit.

Currently [pace](#//api/name/pace) and speed cannot be presented at the same [time](#//api/name/time). Setting [pace](#//api/name/pace)will discard the value set through speed.

#### Declared In

`PBWatch+Sports.h`

### heartRate

The current heart rate in beats per minute.

`@property (nonatomic) uint8_t heartRate`

#### Discussion

Currently there’s no way to stop sending heart rate values if one heart rate value was sent. The last value will be shown in the UI.

If the heart rate has never been set before, this property will return zero.

#### Declared In

`PBWatch+Sports.h`

### customLabel

A custom label to show in the sports UI.

`@property (nonatomic, copy, nullable) NSString *customLabel`

#### Discussion

The maximum number of characters is ~10, but this maximum is not enforced. The label will be sent in upper case to the watch.

To be sent, both customLabel and [customValue](#//api/name/customValue) have to be set to non-nil values.

#### Declared In

`PBWatch+Sports.h`

### customValue

A custom value to show in the sports UI.

`@property (nonatomic, copy, nullable) NSString *customValue`

#### Discussion

The maximum number of characters is ~8, but the maximum is not enforced.

To be sent, both customValue and [customLabel](#//api/name/customLabel) have to be set to non-nil values.

#### Declared In

`PBWatch+Sports.h`

### appMessageDictionary

Creates an update [dictionary](#//api/name/dictionary) from the receiver, that can be used with[`[PBWatch sportsAppUpdate:onSent:]`](../../Classes/PBWatch/#//api/name/sportsAppUpdate:onSent:).

`@property (nonatomic, readonly) NSDictionary<NSNumber*id> *appMessageDictionary`

#### Discussion

You should prefer using [`[PBSportsUpdate updateWatch:completion:]`](#//api/name/updateWatch:completion:).

#### See Also

- `[PBWatch sportsAppUpdate:onSent:]`

#### Declared In

`PBWatch+Sports.h`

### –&nbsp;updateWatch:completion:

Sends an update to the watch.

`- (void)updateWatch:(PBWatch *)watch completion:(void ( ^ __nullable ) ( NSError *__nullable error ))completion`

#### Parameters
_watch_The watch to send the update to._completion_Block that will be called when the update either succeeds or fails. error: nil if the operation was successful, or else an NSError with more information on why it failed.

#### Discussion

The method tries to send the minimal set of changes since the last [time](#//api/name/time) the method was used, to try to minimize communication with the watch.

#### Declared In

`PBWatch+Sports.h`

### +&nbsp;timeStringFromSeconds:

Creates a formatted [time](#//api/name/time) string from a total seconds value, formatted as “h:mm:ss”.

`+ (NSString *)timeStringFromSeconds:(NSTimeInterval)seconds`

#### Parameters
_seconds_The number of seconds from which to create the time string.

#### Return Value

Formatted [time](#//api/name/time) as “h:mm:ss”

#### Discussion

For example, supplying the value 3930.0f seconds will return @“1:05:30”.

#### Declared In

`PBWatch+Sports.h`

### +&nbsp;decimalStringFromFloat:

Creates a formatted decimal string with one decimal number.

`+ (NSString *)decimalStringFromFloat:(float)decimal`

#### Parameters
_decimal_The decimal number to format as a string.

#### Return Value

The formatted decimal number.

#### Discussion

For example, supplying the value 13.42f will return @“13.4”.

#### Declared In

`PBWatch+Sports.h`

## Deprecated Methods

### data

General purpose data variable. ( **Deprecated:** Prefer either `pace` or `speed`.)

`@property (nonatomic) float data`

#### Discussion

**Note:** The original property design is very broken and it has been deprecated in favor of both [pace](#//api/name/pace) and [speed](#//api/name/speed). This value will act as [pace](#//api/name/pace) from now on.

The possible range is currently limited from -3599 to 3599, inclusive (±59min 59sec). Values larger or smaller than the limits will be transformed into the maximum or minimum, respectively.

It will be presented as a duration string in the UI. Minutes and seconds will be separated by colons. The decimal part will be discarded for the presentation.

Setting a value in either [pace](#//api/name/pace) or [speed](#//api/name/speed) will discard the value set through data.

#### See Also

- `[PBWatch sportsAppSetLabel:onSent:]`

#### Declared In

`PBWatch+Sports.h`

### +&nbsp;updateWithTime:distance:data:

Creates a new `PBSportsUpdate` with the given [time](#//api/name/time), [distance](#//api/name/distance) and [data](#//api/name/data). ( **Deprecated:** Prefer -[PBSportsUpdate init] and filling the properties.)

`+ (instancetype)updateWithTime:(NSTimeInterval)time distance:(float)distance data:(float)data`

#### Parameters
_time_The current time in seconds._distance_The current distance in kilometers or miles._data_General purpose data variable.

#### Return Value

A new `PBSportsUpdate` with the given [time](#//api/name/time), [distance](#//api/name/distance) and [data](#//api/name/data).

#### Declared In

`PBWatch+Sports.h`

### –&nbsp;dictionary

Creates an update dictionary from the receiver that can be used with[`[PBWatch sportsAppUpdate:onSent:]`](../../Classes/PBWatch/#//api/name/sportsAppUpdate:onSent:). ( **Deprecated:** Prefer using -[PBSportsUpdate appMessageDictionary].)

`- (NSDictionary *)dictionary`

#### See Also

- `[PBWatch sportsAppUpdate:onSent:]`

#### Declared In

`PBWatch+Sports.h`

### +&nbsp;timeStringFromFloat:

Creates a formatted [time](#//api/name/time) string from a total seconds value, formatted as “h:mm:ss”. ( **Deprecated:** Prefer +[PBSportsUpdate timeStringFromSeconds:].)

`+ (NSString *)timeStringFromFloat:(float)seconds`

#### Parameters
_seconds_The number of seconds from which to create the time string.

#### Return Value

Formatted [time](#//api/name/time) as “h:mm:ss”

#### Discussion

For example, supplying the value 3930.0f seconds will return @“1:05:30”.

#### Declared In

`PBWatch+Sports.h`
