# HealthService

Source: https://developer.repebble.com/docs/c/Foundation/Event_Service/HealthService/index.html

Get access to health information like step count, sleep totals, etc.

The HealthService provides your app access to the step count and sleep activity of the user.

## Function Documentation

[HealthValue](/docs/c/Foundation/Event_Service/HealthService/#HealthValue) health\_service\_sum([HealthMetric](/docs/c/Foundation/Event_Service/HealthService/#HealthMetric) metric, [time\_t](/docs/c/Standard_C/Time/#time_t) time\_start, [time\_t](/docs/c/Standard_C/Time/#time_t) time\_end)

Return the sum of a [HealthMetric](/docs/c/Foundation/Event_Service/HealthService/#HealthMetric)'s values over a time range. The `time_start` and `time_end` parameters define the range of time you want the sum for.

##### Note

The value returned will be based on daily totals, weighted for the length of the specified time range. This may change in the future.

#### Parameters
 metric

The metric to query for data.

 time\_start

UTC time of the earliest data item to incorporate into the sum.

 time\_end

UTC time of the most recent data item to incorporate into the sum.

#### Returns

The sum of that metric over the given time range, if available.

[HealthValue](/docs/c/Foundation/Event_Service/HealthService/#HealthValue) health\_service\_sum\_today([HealthMetric](/docs/c/Foundation/Event_Service/HealthService/#HealthMetric) metric)

Convenience wrapper for [health\_service\_sum()](/docs/c/Foundation/Event_Service/HealthService/#health_service_sum) that returns the sum for today.

#### Parameters
 metric

The metric to query.

#### Returns

The sum of that metric's data for today, if available.

[HealthValue](/docs/c/Foundation/Event_Service/HealthService/#HealthValue) health\_service\_peek\_current\_value([HealthMetric](/docs/c/Foundation/Event_Service/HealthService/#HealthMetric) metric)

Convenience function for peeking at the current value of a metric. This is useful for metrics like HealthMetricHeartRateBPM that represent instantaneous values. It is NOT applicable for metrics like HealthMetricStepCount that must be accumulated over time (it will return 0 if passed that type of metric). This call is equivalent to calling `health_service_aggregate_averaged(metric, time(NULL), time(NULL), HealthAggregationAvg, HealthServiceTimeScopeOnce)`

#### Parameters
 metric

The metric to query.

#### Returns

The current value of that metric, if available.

[HealthValue](/docs/c/Foundation/Event_Service/HealthService/#HealthValue) health\_service\_sum\_averaged([HealthMetric](/docs/c/Foundation/Event_Service/HealthService/#HealthMetric) metric, [time\_t](/docs/c/Standard_C/Time/#time_t) time\_start, [time\_t](/docs/c/Standard_C/Time/#time_t) time\_end, [HealthServiceTimeScope](/docs/c/Foundation/Event_Service/HealthService/#HealthServiceTimeScope) scope)

Return the value of a metric's sum over a given time range between `time_start` and `time_end`. Using this call you can specify the time range that you are interested in getting the average for, as well as a `scope` specifier on how to compute an average of the sum. For example, if you want to get the average number of steps taken from 12 AM (midnight) to 9 AM across all days you would specify:

```
time\_t time\_start = time\_start\_of\_today();time\_t time\_end = time\_start + (9 \* SECONDS\_PER\_HOUR);HealthValue value = health\_service\_sum\_averaged(HealthMetricStepCount, time\_start,time\_end, HealthServiceTimeScopeDaily);
```

 If you want the average number of steps taken on a weekday (Monday to Friday) and today is a Monday (in the local timezone) you would specify: 

```
time\_start = time\_start\_of\_today();time\_end = time\_start + SECONDS\_PER\_DAY;HealthValue value = health\_service\_sum\_averaged(HealthMetricStepCount, time\_start,time\_end, HealthServiceTimeScopeDailyWeekdayOrWeekend);
```

Note that this call is the same as calling `health_service_aggregate_averaged(metric,
time_start, time_end, HealthAggregationSum, scope)`

#### Parameters
 metric

Which [HealthMetric](/docs/c/Foundation/Event_Service/HealthService/#HealthMetric) to query.

 time\_start

UTC time of the start of the query interval.

 time\_end

UTC time of the end of the query interval.

 scope

[HealthServiceTimeScope](/docs/c/Foundation/Event_Service/HealthService/#HealthServiceTimeScope) value describing how the average should be computed.

#### Returns

The average of the sum of the given metric over the given time range, if available.

[HealthValue](/docs/c/Foundation/Event_Service/HealthService/#HealthValue) health\_service\_aggregate\_averaged([HealthMetric](/docs/c/Foundation/Event_Service/HealthService/#HealthMetric) metric, [time\_t](/docs/c/Standard_C/Time/#time_t) time\_start, [time\_t](/docs/c/Standard_C/Time/#time_t) time\_end, [HealthAggregation](/docs/c/Foundation/Event_Service/HealthService/#HealthAggregation) aggregation, [HealthServiceTimeScope](/docs/c/Foundation/Event_Service/HealthService/#HealthServiceTimeScope) scope)

Return the value of an aggregated metric over a given time range. This call is more flexible than health\_service\_sum\_averaged because it lets you specify which aggregation function to perform.

The aggregation function `aggregation` is applied to the metric `metric` over the given time range `time_start` to `time_end` first, and then an average is computed based on the passed in `scope`.

For example, if you want to get the average number of steps taken from 12 AM (midnight) to 9 AM across all days you would specify:

```
time\_t time\_start = time\_start\_of\_today();time\_t time\_end = time\_start + (9 \* SECONDS\_PER\_HOUR);HealthValue value = health\_service\_aggregate\_averaged(HealthMetricStepCount, time\_start,time\_end, HealthAggregationSum, HealthServiceTimeScopeDaily);
```

If you want to compute the average heart rate on Mondays and today is a Monday, you would specify:

```
time\_t time\_start = time\_start\_of\_today(),time\_t time\_end = time\_start + SECONDS\_PER\_DAY,HealthValue value = health\_service\_aggregate\_averaged(HealthMetricHeartRateBPM, time\_start,time\_end, HealthAggregationAvg, HealthServiceTimeScopeWeekly);
```

To get the average of the minimum heart rate seen on Mondays for example, you would instead pass in `HealthAggregationMin`

Certain [HealthAggregation](/docs/c/Foundation/Event_Service/HealthService/#HealthAggregation) operations are only applicable to certain types of metrics. See the notes above on [HealthAggregation](/docs/c/Foundation/Event_Service/HealthService/#HealthAggregation) for details. Use [health\_service\_metric\_aggregate\_averaged\_accessible](/docs/c/Foundation/Event_Service/HealthService/#health_service_metric_aggregate_averaged_accessible) to check for applicability at run time.

#### Parameters
 metric

Which [HealthMetric](/docs/c/Foundation/Event_Service/HealthService/#HealthMetric) to query.

 time\_start

UTC time of the start of the query interval.

 time\_end

UTC time of the end of the query interval.

 aggregation

the aggregation function to perform on the metric. This operation is performed across the passed in time range `time_start` to `time_end`.

 scope

[HealthServiceTimeScope](/docs/c/Foundation/Event_Service/HealthService/#HealthServiceTimeScope) value describing how the average should be computed. Use `HealthServiceTimeScopeOnce` to not compute an average.

#### Returns

The average of the aggregation performed on the given metric over the given time range, if available.

[HealthActivityMask](/docs/c/Foundation/Event_Service/HealthService/#HealthActivityMask) health\_service\_peek\_current\_activities(void)

Return a [HealthActivityMask](/docs/c/Foundation/Event_Service/HealthService/#HealthActivityMask) containing a set of bits, one set for each activity that is currently active.

#### Returns

A bitmask with zero or more [HealthActivityMask](/docs/c/Foundation/Event_Service/HealthService/#HealthActivityMask) bits set as appropriate.

void health\_service\_activities\_iterate([HealthActivityMask](/docs/c/Foundation/Event_Service/HealthService/#HealthActivityMask) activity\_mask, [time\_t](/docs/c/Standard_C/Time/#time_t) time\_start, [time\_t](/docs/c/Standard_C/Time/#time_t) time\_end, [HealthIterationDirection](/docs/c/Foundation/Event_Service/HealthService/#HealthIterationDirection) direction, [HealthActivityIteratorCB](/docs/c/Foundation/Event_Service/HealthService/#HealthActivityIteratorCB) callback, void \* context)

Iterates backwards or forward within a given time span to list all recorded activities. For example, this can be used to find the last recorded sleep phase or all deep sleep phases in a given time range. Any activity that overlaps with `time_start` and `time_end` will be included, even if the start time starts before `time_start` or end time ends after `time_end`.

#### Parameters
 activity\_mask

A bitmask containing set of activities you are interested in.

 time\_start

UTC time of the earliest time you are interested in.

 time\_end

UTC time of the latest time you are interested in.

 direction

The direction in which to iterate.

 callback

Developer-supplied callback that is called for each activity iterated over.

 context

Developer-supplied context pointer that is passed to the callback.

[HealthServiceAccessibilityMask](/docs/c/Foundation/Event_Service/HealthService/#HealthServiceAccessibilityMask) health\_service\_metric\_accessible([HealthMetric](/docs/c/Foundation/Event_Service/HealthService/#HealthMetric) metric, [time\_t](/docs/c/Standard_C/Time/#time_t) time\_start, [time\_t](/docs/c/Standard_C/Time/#time_t) time\_end)

Check if a certain combination of metric and time span is accessible using [health\_service\_sum](/docs/c/Foundation/Event_Service/HealthService/#health_service_sum) by returning a value of [HealthServiceAccessibilityMask](/docs/c/Foundation/Event_Service/HealthService/#HealthServiceAccessibilityMask). Developers should check if the return value is HealthServiceAccessibilityMaskAvailable before calling [health\_service\_sum](/docs/c/Foundation/Event_Service/HealthService/#health_service_sum).

Note that this call is the same as calling `health_service_metric_averaged_accessible(metric,
time_start, time_end, HealthServiceTimeScopeOnce)`

#### Parameters
 metric

The metric to query for data.

 time\_start

Earliest UTC time you are interested in.

 time\_end

Latest UTC time you are interested in.

#### Returns

A [HealthServiceAccessibilityMask](/docs/c/Foundation/Event_Service/HealthService/#HealthServiceAccessibilityMask) representing the accessible metrics in this time range.

[HealthServiceAccessibilityMask](/docs/c/Foundation/Event_Service/HealthService/#HealthServiceAccessibilityMask) health\_service\_metric\_averaged\_accessible([HealthMetric](/docs/c/Foundation/Event_Service/HealthService/#HealthMetric) metric, [time\_t](/docs/c/Standard_C/Time/#time_t) time\_start, [time\_t](/docs/c/Standard_C/Time/#time_t) time\_end, [HealthServiceTimeScope](/docs/c/Foundation/Event_Service/HealthService/#HealthServiceTimeScope) scope)

Check if a certain combination of metric, time span, and scope is accessible for calculating summed, averaged data by returning a value of [HealthServiceAccessibilityMask](/docs/c/Foundation/Event_Service/HealthService/#HealthServiceAccessibilityMask). Developers should check if the return value is HealthServiceAccessibilityMaskAvailable before calling [health\_service\_sum\_averaged](/docs/c/Foundation/Event_Service/HealthService/#health_service_sum_averaged).

Note that this call is the same as calling `health_service_metric_aggregate_averaged_accessible(metric, time_start, time_end,
 HealthAggregationSum, HealthServiceTimeScopeOnce)`

#### Parameters
 metric

The metric to query for averaged data.

 time\_start

Earliest UTC time you are interested in.

 time\_end

Latest UTC time you are interested in.

 scope

[HealthServiceTimeScope](/docs/c/Foundation/Event_Service/HealthService/#HealthServiceTimeScope) value describing how the average should be computed.

#### Returns

A \HealthServiceAccessibilityMask value decribing whether averaged data is available.

[HealthServiceAccessibilityMask](/docs/c/Foundation/Event_Service/HealthService/#HealthServiceAccessibilityMask) health\_service\_metric\_aggregate\_averaged\_accessible([HealthMetric](/docs/c/Foundation/Event_Service/HealthService/#HealthMetric) metric, [time\_t](/docs/c/Standard_C/Time/#time_t) time\_start, [time\_t](/docs/c/Standard_C/Time/#time_t) time\_end, [HealthAggregation](/docs/c/Foundation/Event_Service/HealthService/#HealthAggregation) aggregation, [HealthServiceTimeScope](/docs/c/Foundation/Event_Service/HealthService/#HealthServiceTimeScope) scope)

Check if a certain combination of metric, time span, aggregation operation, and scope is accessible for calculating aggregated, averaged data by returning a value of [HealthServiceAccessibilityMask](/docs/c/Foundation/Event_Service/HealthService/#HealthServiceAccessibilityMask). Developers should check if the return value is HealthServiceAccessibilityMaskAvailable before calling [health\_service\_aggregate\_averaged](/docs/c/Foundation/Event_Service/HealthService/#health_service_aggregate_averaged).

#### Parameters
 metric

The metric to query for averaged data.

 time\_start

Earliest UTC time you are interested in.

 time\_end

Latest UTC time you are interested in.

 aggregation

The aggregation to perform

 scope

[HealthServiceTimeScope](/docs/c/Foundation/Event_Service/HealthService/#HealthServiceTimeScope) value describing how the average should be computed.

#### Returns

A \HealthServiceAccessibilityMask value decribing whether averaged data is available.

[HealthServiceAccessibilityMask](/docs/c/Foundation/Event_Service/HealthService/#HealthServiceAccessibilityMask) health\_service\_any\_activity\_accessible([HealthActivityMask](/docs/c/Foundation/Event_Service/HealthService/#HealthActivityMask) activity\_mask, [time\_t](/docs/c/Standard_C/Time/#time_t) time\_start, [time\_t](/docs/c/Standard_C/Time/#time_t) time\_end)

Check if a certain combination of metric, [HealthActivityMask](/docs/c/Foundation/Event_Service/HealthService/#HealthActivityMask) and time span is accessible. Developers should check if the return value is HealthServiceAccessibilityMaskAvailable before calling any other HealthService APIs that involve the given activities.

#### Parameters
 activity\_mask

A bitmask of activities you are interested in.

 time\_start

Earliest UTC time you are interested in.

 time\_end

Latest UTC time you are interested in.

#### Returns

A [HealthServiceAccessibilityMask](/docs/c/Foundation/Event_Service/HealthService/#HealthServiceAccessibilityMask) representing which of the passed [HealthActivityMask](/docs/c/Foundation/Event_Service/HealthService/#HealthActivityMask) values are available under the given constraints.

bool health\_service\_events\_subscribe([HealthEventHandler](/docs/c/Foundation/Event_Service/HealthService/#HealthEventHandler) handler, void \* context)

Subscribe to HealthService events. This allocates a cache on the application's heap of up to 2048 bytes that will be de-allocated if you call [health\_service\_events\_unsubscribe()](/docs/c/Foundation/Event_Service/HealthService/#health_service_events_unsubscribe). If there's not enough heap available, this function will return `false` and will not subscribe to any events.

#### Parameters
 handler

Developer-supplied event handler function.

 context

Developer-supplied context pointer.

#### Returns

`true` on success, `false` on failure.

bool health\_service\_events\_unsubscribe(void)

Unsubscribe from HealthService events.

#### Returns

`true` on success, `false` on failure.

bool health\_service\_set\_heart\_rate\_sample\_period([uint16\_t](/docs/c/Standard_C/#uint16_t) interval\_sec)

Set the desired sampling period for heart rate readings. Normally, the system will sample the heart rate using a sampling period that is automatically chosen to provide useful information without undue battery drain (it automatically samples more often during periods of intense activity, and less often when the user is idle). If desired though, an application can request a specific sampling period using this call. The system will use this as a suggestion, but does not guarantee that the requested period will be used. The actual sampling period may be greater or less due to system needs or heart rate sensor reading quality issues.

Each time a new heart rate reading becomes available, a `HealthEventHeartRateUpdate` event will be sent to the application's `HealthEventHandler`. The sample period request will remain in effect the entire time the app is running unless it is explicitly cancelled (by calling this method again with 0 as the desired interval). If the app exits without first cancelling the request, it will remain in effect even for a limited time afterwards. To determine how long it will remain active after the app exits, use `health_service_get_heart_rate_sample_period_expiration_sec`.

Unless the app explicitly needs to access to historical high-resolution heart rate data, it is best practice to always cancel the sample period request before exiting in order to maximize battery life. Historical heart rate data can be accessed using the `health_service_get_minute_history` call.

#### Parameters
 interval\_sec

desired interval between heart rate reading updates. Pass 0 to go back to automatically chosen intervals.

#### Returns

`true` on success, `false` on failure

[uint16\_t](/docs/c/Standard_C/#uint16_t) health\_service\_get\_heart\_rate\_sample\_period\_expiration\_sec(void)

Return how long a heart rate sample period request (sent via `health_service_set_heart_rate_sample_period`) will remain active after the app exits. If there is no current request by this app, this call will return 0.

#### Returns

The number of seconds the heart rate sample period request will remain active after the app exits, or 0 if there is no active request by this app.

[HealthMetricAlert](/docs/c/Foundation/Event_Service/HealthService/#HealthMetricAlert) \* health\_service\_register\_metric\_alert([HealthMetric](/docs/c/Foundation/Event_Service/HealthService/#HealthMetric) metric, [HealthValue](/docs/c/Foundation/Event_Service/HealthService/#HealthValue) threshold)

Register for an alert when a metric crosses the given threshold. When the metric crosses this threshold (either goes above or below it), a HealthEventMetricAlert event will be generated. To cancel this registration, pass the returned [HealthMetricAlert](/docs/c/Foundation/Event_Service/HealthService/#HealthMetricAlert) value to [health\_service\_cancel\_metric\_alert](/docs/c/Foundation/Event_Service/HealthService/#health_service_cancel_metric_alert). The only metric currently supported by this call is HealthMetricHeartRateBPM, but future versions may support additional metrics. To see if a specific metric is supported by this call, use:

```
time\_t now = time(NULL);HealthServiceAccessibilityMask accessible =health\_service\_metric\_aggregate\_averaged\_accessible(metric, now, now, HealthAggregationAvg,HealthServiceTimeScopeOnce);bool alert\_supported = (accessible & HealthServiceAccessibilityMaskAvailable);
```

In the current implementation, only one alert per metric can be registered at a time. Future implementations may support two or more simulataneous alert registrations per metric. To change the alert threshold in the current implementation, cancel the original registration using `health_service_cancel_metric_alert` before registering the new threshold.

#### Parameters
 metric

Which [HealthMetric](/docs/c/Foundation/Event_Service/HealthService/#HealthMetric) to query.

 threshold

The threshold value.

#### Returns

handle to the alert registration on success, NULL on failure

bool health\_service\_cancel\_metric\_alert([HealthMetricAlert](/docs/c/Foundation/Event_Service/HealthService/#HealthMetricAlert) \* alert)

Cancel an metric alert previously created with [health\_service\_register\_metric\_alert](/docs/c/Foundation/Event_Service/HealthService/#health_service_register_metric_alert).

#### Parameters
 alert

the [HealthMetricAlert](/docs/c/Foundation/Event_Service/HealthService/#HealthMetricAlert) previously returned by [health\_service\_register\_metric\_alert](/docs/c/Foundation/Event_Service/HealthService/#health_service_register_metric_alert)

#### Returns

`true` on success, `false` on failure

[uint32\_t](/docs/c/Standard_C/#uint32_t) health\_service\_get\_minute\_history([HealthMinuteData](/docs/c/Foundation/Event_Service/HealthService/#HealthMinuteData) \* minute\_data, [uint32\_t](/docs/c/Standard_C/#uint32_t) max\_records, [time\_t](/docs/c/Standard_C/Time/#time_t) \* time\_start, [time\_t](/docs/c/Standard_C/Time/#time_t) \* time\_end)

Return historical minute data records. This fills in the `minute_data` array parameter with minute by minute statistics of the user's steps, average watch orientation, etc. The data is returned in time order, with the oldest minute data returned at `minute_data[0]`.

##### Note

If the return value is zero, `time_start` and `time_end` are meaningless. It's not guaranteed that all records contain valid data, even if the return value is greater than zero. Check `HealthMinuteData.is_invalid` to see if a given record contains valid data.

#### Parameters
 minute\_data

Pointer to an array of [HealthMinuteData](/docs/c/Foundation/Event_Service/HealthService/#HealthMinuteData) records that will be filled in with the historical minute data.

 max\_records

The maximum number of records the `minute_data` array can hold.

 time\_start (inout)

On entry, the UTC time of the first requested record. On exit, the UTC time of the first second of the first record actually returned. If `time_start` on entry is somewhere in the middle of a minute interval, this function behaves as if the caller passed in the start of that minute.

 time\_end (inout)

On entry, the UTC time of the end of the requested range of records. On exit, the UTC time of the end of the last record actually returned (i.e. start time of last record + 60). If `time_end` on entry is somewhere in the middle of a minute interval, this function behaves as if the caller passed in the end of that minute.

#### Returns

Actual number of records returned. May be less then the maximum requested.

[MeasurementSystem](/docs/c/Foundation/Event_Service/HealthService/#MeasurementSystem) health\_service\_get\_measurement\_system\_for\_display([HealthMetric](/docs/c/Foundation/Event_Service/HealthService/#HealthMetric) metric)

Get the preferred measurement system for a given [HealthMetric](/docs/c/Foundation/Event_Service/HealthService/#HealthMetric), if the user has chosen a preferred system and it is applicable to that metric.

#### Parameters
 metric

A metric value chosen from [HealthMetric](/docs/c/Foundation/Event_Service/HealthService/#HealthMetric).

#### Returns

A value from [MeasurementSystem](/docs/c/Foundation/Event_Service/HealthService/#MeasurementSystem) if applicable, else MeasurementSystemUnknown.

## Data Structure Documentation

struct HealthMinuteData

Structure representing a single minute data record returned by [health\_service\_get\_minute\_history()](/docs/c/Foundation/Event_Service/HealthService/#health_service_get_minute_history). The `orientation` field encodes the angle of the watch in the x-y plane (the "yaw") in the lower 4 bits (360 degrees linearly mapped to 1 of 16 different values) and the angle to the z axis (the "pitch") in the upper 4 bits. The `vmc` value is a measure of the total amount of movement seen by the watch. More vigorous movement yields higher VMC values.

#### Data Fields
uint8\_t steps

Number of steps taken in this minute.

uint8\_t orientation

Quantized average orientation.

[uint16\_t](/docs/c/Standard_C/#uint16_t) vmc

Vector Magnitude Counts (vmc).

bool is\_invalid

`true` if the item doesn't represents actual data and should be ignored.

[AmbientLightLevel](/docs/c/Foundation/Event_Service/HealthService/#AmbientLightLevel) light

Instantaneous light level during this minute.

uint8\_t paddinguint8\_t heart\_rate\_bpm

heart rate in beats per minute

uint8\_t reserved

Reserved for future use.

## Enum Documentation

enum HealthMetric

Health metric values used to retrieve health data. For example, using [health\_service\_sum()](/docs/c/Foundation/Event_Service/HealthService/#health_service_sum).

#### Enumerators
HealthMetricStepCount

The number of steps counted.

HealthMetricActiveSeconds

The number of seconds spent active (i.e. not resting).

HealthMetricWalkedDistanceMeters

The distance walked, in meters.

HealthMetricSleepSeconds

The number of seconds spent sleeping.

HealthMetricSleepRestfulSeconds

The number of sleep seconds in the 'restful' or deep sleep state.

HealthMetricRestingKCalories

The number of kcal (Calories) burned while resting due to resting metabolism.

HealthMetricActiveKCalories

The number of kcal (Calories) burned while active.

HealthMetricHeartRateBPM

The heart rate, in beats per minute. This is a filtered value that is at most 15 minutes old.

HealthMetricHeartRateRawBPM

The raw heart rate value of the most recent sample, in beats per minute.

enum HealthServiceTimeScope

Used by [health\_service\_sum\_averaged()](/docs/c/Foundation/Event_Service/HealthService/#health_service_sum_averaged) to specify how the average is computed.

#### Enumerators
HealthServiceTimeScopeOnce

No average computed. The result is the same as calling [health\_service\_sum()](/docs/c/Foundation/Event_Service/HealthService/#health_service_sum).

HealthServiceTimeScopeWeekly

Compute average using the same day from each week. For example, every Monday if the passed in time range falls on a Monday.

HealthServiceTimeScopeDailyWeekdayOrWeekend

Compute average using either weekdays (Monday to Friday) or weekends (Saturday and Sunday), depending on which day the passed in time range falls.

HealthServiceTimeScopeDaily

Compute average across all days of the week.

enum HealthAggregation

Used by [health\_service\_aggregate\_averaged()](/docs/c/Foundation/Event_Service/HealthService/#health_service_aggregate_averaged) to specify what type of aggregation to perform. This aggregation is applied to the metric before the average is computed.

#### Enumerators
HealthAggregationSum

Sum the metric. The result is the same as calling [health\_service\_sum\_averaged()](/docs/c/Foundation/Event_Service/HealthService/#health_service_sum_averaged). This operation is only applicable for metrics that accumulate, like HealthMetricStepCount, HealthMetricActiveSeconds, etc.

HealthAggregationAvg

Use the average of the metric. This is only applicable for metrics that measure instantaneous values, like HealthMetricHeartRateBPM.

HealthAggregationMin

Use the minimum value of the metric. This is only applicable for metrics that measure instantaneous values, like HealthMetricHeartRateBPM.

HealthAggregationMax

Use the maximum value of the metric. This is only applicable for metrics that measure instantaneous values, like HealthMetricHeartRateBPM.

enum HealthActivity

Health-related activities that can be accessed using.

#### Enumerators
HealthActivityNone

No special activity.

HealthActivitySleep

The 'sleeping' activity.

HealthActivityRestfulSleep

The 'restful sleeping' activity.

HealthActivityWalk

The 'walk' activity.

HealthActivityRun

The 'run' activity.

HealthActivityOpenWorkout

The 'generic' activity.

enum HealthIterationDirection

Iteration direction, passed to [health\_service\_activities\_iterate()](/docs/c/Foundation/Event_Service/HealthService/#health_service_activities_iterate). When iterating backwards (`HealthIterationDirectionPast`), activities that have a greater value for `time_end` come first. When iterating forward (`HealthIterationDirectionFuture`), activities that have a smaller value for `time_start` come first.

#### Enumerators
HealthIterationDirectionPast

Iterate into the past.

HealthIterationDirectionFuture

Iterate into the future.

enum HealthServiceAccessibilityMask

Possible values returned by [health\_service\_metric\_accessible()](/docs/c/Foundation/Event_Service/HealthService/#health_service_metric_accessible). The values are used in combination as a bitmask. For example, to check if any data is available for a given request use: bool any\_data\_available = value & HealthServiceAccessibilityMaskAvailable;.

#### Enumerators
HealthServiceAccessibilityMaskAvailable

Return values are available and represent the collected health information.

HealthServiceAccessibilityMaskNoPermission

The user hasn't granted permission.

HealthServiceAccessibilityMaskNotSupported

The queried combination of time span and [HealthMetric](/docs/c/Foundation/Event_Service/HealthService/#HealthMetric) or [HealthActivityMask](/docs/c/Foundation/Event_Service/HealthService/#HealthActivityMask) is currently unsupported.

HealthServiceAccessibilityMaskNotAvailable

No samples were recorded for the given time span.

enum HealthEventType

Health event enum. Passed into the [HealthEventHandler](/docs/c/Foundation/Event_Service/HealthService/#HealthEventHandler).

#### Enumerators
HealthEventSignificantUpdate

All data is considered as outdated and apps should re-read all health data. This happens after an app is subscribed via [health\_service\_events\_subscribe()](/docs/c/Foundation/Event_Service/HealthService/#health_service_events_subscribe), on a change of the day, or in other cases that significantly change the underlying data.

HealthEventMovementUpdate

Recent values around HealthMetricStepCount, HealthMetricActiveSeconds, or HealthMetricWalkedDistanceMeters have changed.

HealthEventSleepUpdate

Recent values around HealthMetricSleepSeconds, HealthMetricSleepRestfulSeconds, HealthActivitySleep, and HealthActivityRestfulSleep changed.

HealthEventMetricAlert

A metric has crossed the threshold set by [health\_service\_register\_metric\_alert](/docs/c/Foundation/Event_Service/HealthService/#health_service_register_metric_alert).

HealthEventHeartRateUpdate

Value of HealthMetricHeartRateBPM or HealthMetricHeartRateRawBPM has changed.

enum AmbientLightLevel

Light level enum.

#### Enumerators
AmbientLightLevelUnknownAmbientLightLevelVeryDarkAmbientLightLevelDarkAmbientLightLevelLightAmbientLightLevelVeryLight

enum MeasurementSystem

Types of measurement system a [HealthMetric](/docs/c/Foundation/Event_Service/HealthService/#HealthMetric) may be measured in.

#### Enumerators
MeasurementSystemUnknown

The measurement system is unknown, or does not apply to the chosen metric.

MeasurementSystemMetric

The metric measurement system.

MeasurementSystemImperial

The imperial measurement system.

## Typedef Documentation

 typedef int32\_t HealthValue

Type used to represent [HealthMetric](/docs/c/Foundation/Event_Service/HealthService/#HealthMetric) values.

 typedef struct [HealthMetricAlert](/docs/c/Foundation/Event_Service/HealthService/#HealthMetricAlert) HealthMetricAlert

Type used as a handle to a registered metric alert (returned by [health\_service\_register\_metric\_alert](/docs/c/Foundation/Event_Service/HealthService/#health_service_register_metric_alert))

 typedef [uint32\_t](/docs/c/Standard_C/#uint32_t) HealthActivityMask

Expresses a set of [HealthActivity](/docs/c/Foundation/Event_Service/HealthService/#HealthActivity) values as a bitmask.

 typedef bool(\* HealthActivityIteratorCB)(HealthActivity activity, time\_t time\_start, time\_t time\_end, void \*context) 

Callback used by [health\_service\_activities\_iterate()](/docs/c/Foundation/Event_Service/HealthService/#health_service_activities_iterate).

#### Parameters
 activity

Which activity the caller is being informed about.

 time\_start

Start UTC time of the activity.

 time\_end

End UTC time of the activity.

 context

The `context` parameter initially passed to [health\_service\_activities\_iterate()](/docs/c/Foundation/Event_Service/HealthService/#health_service_activities_iterate).

#### Returns

`true` if you are interested in more activities, or `false` to stop iterating.

 typedef void(\* HealthEventHandler)(HealthEventType event, void \*context) 

Developer-supplied event handler, called when a health-related event occurs after subscribing via [health\_service\_events\_subscribe()](/docs/c/Foundation/Event_Service/HealthService/#health_service_events_subscribe);.

#### Parameters
 event

The type of health-related event that occured.

 context

The developer-supplied context pointer.

## Macro Definition Documentation

#define HealthActivityMaskAll ((HealthActivityOpenWorkout \<\< 1) - 1)

A mask value representing all available activities.

- [SDK 3](javascript:void(0);)
- [SDK 4](javascript:void(0);)
- [SDK 4.9+](javascript:void(0);)

#define PBL\_IF\_HEALTH\_ELSE ( if\_true, if\_false)

Convenience macro to switch between two expressions depending on health support. On platforms with health support the first expression will be chosen, the second otherwise.

#define PBL\_IF\_HEALTH\_ELSE ( if\_true, if\_false)

Convenience macro to switch between two expressions depending on health support. On platforms with health support the first expression will be chosen, the second otherwise.

#define PBL\_IF\_HEALTH\_ELSE ( if\_true, if\_false)

Convenience macro to switch between two expressions depending on health support. On platforms with health support the first expression will be chosen, the second otherwise.
