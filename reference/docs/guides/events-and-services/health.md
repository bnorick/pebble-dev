# Pebble Health

Source: https://developer.repebble.com/guides/events-and-services/health/

**PLATFORM NOTICE**  
 This guide does not apply to apps built to run on the Aplite platform (Pebble Classic, Pebble Steel).

[Pebble Health](https://blog.getpebble.com/2015/12/15/health/) provides builtin health data tracking to allow users to improve their activity and sleep habits. With SDK 3.9, the [`HealthService`](/docs/c/Foundation/Event_Service/HealthService/ "HealthService") API opens this data up to developers to include and use within their apps. For example, a watchface could display a brief summary of the user's activity for the day.

## API Availability

In order to use the [`HealthService`](/docs/c/Foundation/Event_Service/HealthService/ "HealthService") (and indeed Pebble Health), the user must enable the 'Pebble Health' app in the 'Apps/Timeline' view of the official Pebble mobile app. If this is not enabled health data will not be available to apps, and API calls will return values to reflect this.

In addition, any app using the [`HealthService`](/docs/c/Foundation/Event_Service/HealthService/ "HealthService") API must declare the 'health' capability in order to be accepted by the[developer dashboard](https://developer.rePebble.com/dashboard). This can be done in `package.json`in the SDK:

```
"capabilities": ["health"]
```

Since Pebble Health is not available on the Aplite platform, developers should check the API return values and hence the lack of [`HealthService`](/docs/c/Foundation/Event_Service/HealthService/ "HealthService") on that platform gracefully. In addition, the `PBL_HEALTH` define and`PBL_IF_HEALTH_ELSE()` macro can be used to selectively omit affected code.

## Available Metrics

The [`HealthMetric`](/docs/c/Foundation/Event_Service/HealthService/#HealthMetric "HealthMetric") `enum` lists the types of data (or 'metrics') that can be read using the API. These are described below:

| Metric | Description |
| --- | --- |
| `HealthMetricStepCount` | The user's step count. |
| `HealthMetricActiveSeconds` | Duration of time the user was considered 'active'. |
| `HealthMetricWalkedDistanceMeters` | Estimation of the distance travelled in meters. |
| `HealthMetricSleepSeconds` | Duration of time the user was considered asleep. |
| `HealthMetricSleepRestfulSeconds` | Duration of time the user was considered in deep restful sleep. |
| `HealthMetricRestingKCalories` | The number of kcal (thousand calories) burned due to resting metabolism. |
| `HealthMetricActiveKCalories` | The number of kcal (thousand calories) burned due to activity. |
| `HealthMetricHeartRateBPM` | The heart rate, in beats per minute. |

## Subscribing to HealthService Events

Like other Event Services, an app can subscribe a handler function to receive a callback when new health data is available. This is useful for showing near-realtime activity updates. The handler must be a suitable implementation of[`HealthEventHandler`](/docs/c/Foundation/Event_Service/HealthService/#HealthEventHandler "HealthEventHandler"). The `event` parameter describes the type of each update, and is one of the following from the [`HealthEventType`](/docs/c/Foundation/Event_Service/HealthService/#HealthEventType "HealthEventType") `enum`:

| Event Type | Value | Description |
| --- | --- | --- |
| `HealthEventSignificantUpdate` | `0` | All data is considered as outdated, apps should re-read all health data. This can happen on a change of the day or in other cases that significantly change the underlying data. |
| `HealthEventMovementUpdate` | `1` | Recent values around `HealthMetricStepCount`, `HealthMetricActiveSeconds`, `HealthMetricWalkedDistanceMeters`, and `HealthActivityMask` changed. |
| `HealthEventSleepUpdate` | `2` | Recent values around `HealthMetricSleepSeconds`, `HealthMetricSleepRestfulSeconds`, `HealthActivitySleep`, and `HealthActivityRestfulSleep` changed. |
| `HealthEventHeartRateUpdate` | `4` | The value of `HealthMetricHeartRateBPM` has changed. |

A simple example handler is shown below, which outputs to app logs the type of event that fired the callback:

```
static void health\_handler(HealthEventType event, void \*context) {// Which type of event occurred?switch(event) {case HealthEventSignificantUpdate:APP\_LOG(APP\_LOG\_LEVEL\_INFO,"New HealthService HealthEventSignificantUpdate event");break;case HealthEventMovementUpdate:APP\_LOG(APP\_LOG\_LEVEL\_INFO,"New HealthService HealthEventMovementUpdate event");break;case HealthEventSleepUpdate:APP\_LOG(APP\_LOG\_LEVEL\_INFO,"New HealthService HealthEventSleepUpdate event");break;case HealthEventHeartRateUpdate:APP\_LOG(APP\_LOG\_LEVEL\_INFO,"New HealthService HealthEventHeartRateUpdate event");break;}}
```

The subscription is then registered in the usual way, optionally providing a`context` parameter that is relayed to each event callback. The return value should be used to determine whether the subscription was successful:

```
#if defined(PBL\_HEALTH)// Attempt to subscribeif(!health\_service\_events\_subscribe(health\_handler, NULL)) {APP\_LOG(APP\_LOG\_LEVEL\_ERROR, "Health not available!");}#elseAPP\_LOG(APP\_LOG\_LEVEL\_ERROR, "Health not available!");#endif
```

## Reading Health Data

Health data is collected in the background as part of Pebble Health regardless of the state of the app using the [`HealthService`](/docs/c/Foundation/Event_Service/HealthService/ "HealthService") API, and is available to apps through various [`HealthService`](/docs/c/Foundation/Event_Service/HealthService/ "HealthService") API functions.

Before reading any health data, it is recommended to check that data is available for the desired time range, if applicable. In addition to the[`HealthServiceAccessibilityMask`](/docs/c/Foundation/Event_Service/HealthService/#HealthServiceAccessibilityMask "HealthServiceAccessibilityMask") value, health-related code can be conditionally compiled using `PBL_HEALTH`. For example, to check whether any data is available for a given time range:

```
#if defined(PBL\_HEALTH)// Use the step count metricHealthMetric metric = HealthMetricStepCount;// Create timestamps for midnight (the start time) and now (the end time)time\_t start = time\_start\_of\_today();time\_t end = time(NULL);// Check step data is availableHealthServiceAccessibilityMask mask = health\_service\_metric\_accessible(metric,start, end);bool any\_data\_available = mask & HealthServiceAccessibilityMaskAvailable;#else// Health data is not available herebool any\_data\_available = false;#endif
```

Most applications will want to read the sum of a metric for the current day's activity. This is the simplest method for accessing summaries of users' health data, and is shown in the example below:

```
HealthMetric metric = HealthMetricStepCount;time\_t start = time\_start\_of\_today();time\_t end = time(NULL);// Check the metric has data available for todayHealthServiceAccessibilityMask mask = health\_service\_metric\_accessible(metric,start, end);if(mask & HealthServiceAccessibilityMaskAvailable) {// Data is available!APP\_LOG(APP\_LOG\_LEVEL\_INFO, "Steps today: %d",(int)health\_service\_sum\_today(metric));} else {// No data recorded yet todayAPP\_LOG(APP\_LOG\_LEVEL\_ERROR, "Data unavailable!");}
```

For more specific data queries, the API also allows developers to request data records and sums of metrics from a specific time range. If data is available, it can be read as a sum of all values recorded between that time range. You can use the convenience constants from [`Time`](/docs/c/Standard_C/Time/ "Time"), such as [`SECONDS_PER_HOUR`](/docs/c/Standard_C/Time/#SECONDS_PER_HOUR "SECONDS\_PER\_HOUR") to adjust a timestamp relative to the current moment returned by [`time()`](/docs/c/Standard_C/Time/ "Time").

> Note: The value returned will be an average since midnight, weighted for the length of the specified time range. This may change in the future.

An example of this process is shown below:

```
// Make a timestamp for nowtime\_t end = time(NULL);// Make a timestamp for the last hour's worth of datatime\_t start = end - SECONDS\_PER\_HOUR;// Check data is availableHealthServiceAccessibilityMask result =health\_service\_metric\_accessible(HealthMetricStepCount, start, end);if(result & HealthServiceAccessibilityMaskAvailable) {// Data is available! Read itHealthValue steps = health\_service\_sum(HealthMetricStepCount, start, end);APP\_LOG(APP\_LOG\_LEVEL\_INFO, "Steps in the last hour: %d", (int)steps);} else {APP\_LOG(APP\_LOG\_LEVEL\_ERROR, "No data available!");}
```

## Representing Health Data

Depending on the locale of the user, the conventional measurement system used to represent distances may vary between metric and imperial. For this reason it is recommended to query the user's preferred [`MeasurementSystem`](/docs/c/Foundation/Event_Service/HealthService/#MeasurementSystem "MeasurementSystem") before formatting distance data from the [`HealthService`](/docs/c/Foundation/Event_Service/HealthService/ "HealthService"):

> Note: This API is currently only meaningful when querying the[`HealthMetricWalkedDistanceMeters`](/docs/c/Foundation/Event_Service/HealthService/#HealthMetricWalkedDistanceMeters "HealthMetricWalkedDistanceMeters") metric. [`MeasurementSystemUnknown`](/docs/c/Foundation/Event_Service/HealthService/#MeasurementSystemUnknown "MeasurementSystemUnknown") will be returned for all other queries.

```
const HealthMetric metric = HealthMetricWalkedDistanceMeters;const HealthValue distance = health\_service\_sum\_today(metric);// Get the preferred measurement systemMeasurementSystem system = health\_service\_get\_measurement\_system\_for\_display(metric);// Format accordinglystatic char s\_buffer[32];switch(system) {case MeasurementSystemMetric:snprintf(s\_buffer, sizeof(s\_buffer), "Walked %d meters", (int)distance);break;case MeasurementSystemImperial: {// Convert to imperial firstint feet = (int)((float)distance \* 3.28F);snprintf(s\_buffer, sizeof(s\_buffer), "Walked %d feet", (int)feet);} break;case MeasurementSystemUnknown:default:APP\_LOG(APP\_LOG\_LEVEL\_INFO, "MeasurementSystem unknown or does not apply");}// Display to user in correct unitstext\_layer\_set\_text(s\_some\_layer, s\_buffer);
```

## Obtaining Averaged Data

The [`HealthService`](/docs/c/Foundation/Event_Service/HealthService/ "HealthService") also allows developers to read average values of a particular [`HealthMetric`](/docs/c/Foundation/Event_Service/HealthService/#HealthMetric "HealthMetric") with varying degrees of scope. This is useful for apps that wish to display an average value (e.g.: as a goal for the user) alongside a summed value.

In this context, the `start` and `end` parameters specify the time period to be used for the daily average calculation. For example, a start time of midnight and an end time ten hours later will return the average value for the specified metric measured until 10 AM on average across the days specified by the scope.

The [`HealthServiceTimeScope`](/docs/c/Foundation/Event_Service/HealthService/#HealthServiceTimeScope "HealthServiceTimeScope") specified when querying for averaged data over a given time range determines how the average is calculated, as detailed in the table below:

| Scope Type | Description |
| --- | --- |
| `HealthServiceTimeScopeOnce` | No average computed. The result is the same as calling [`health_service_sum()`](/docs/c/Foundation/Event_Service/HealthService/#health_service_sum "health\_service\_sum"). |
| `HealthServiceTimeScopeWeekly` | Compute average using the same day from each week (up to four weeks). For example, every Monday if the provided time range falls on a Monday. |
| `HealthServiceTimeScopeDailyWeekdayOrWeekend` | Compute average using either weekdays (Monday to Friday) or weekends (Saturday and Sunday), depending on which day the provided time range falls. |
| `HealthServiceTimeScopeDaily` | Compute average across all days of the week. |

> Note: If the difference between the start and end times is greater than one day, an average will be returned that takes both days into account. Similarly, if the time range crosses between scopes (such as including weekend days and weekdays with [`HealthServiceTimeScopeDailyWeekdayOrWeekend`](/docs/c/Foundation/Event_Service/HealthService/#HealthServiceTimeScopeDailyWeekdayOrWeekend "HealthServiceTimeScopeDailyWeekdayOrWeekend")), the start time will be used to determine which days are used.

Reading averaged data values works in a similar way to reading sums. The example below shows how to read an average step count across all days of the week for a given time range:

```
// Define query parametersconst HealthMetric metric = HealthMetricStepCount;const HealthServiceTimeScope scope = HealthServiceTimeScopeDaily;// Use the average daily value from midnight to the current timeconst time\_t start = time\_start\_of\_today();const time\_t end = time(NULL);// Check that an averaged value is accessibleHealthServiceAccessibilityMask mask =health\_service\_metric\_averaged\_accessible(metric, start, end, scope);if(mask & HealthServiceAccessibilityMaskAvailable) {// Average is available, read itHealthValue average = health\_service\_sum\_averaged(metric, start, end, scope);APP\_LOG(APP\_LOG\_LEVEL\_INFO, "Average step count: %d steps", (int)average);}
```

## Detecting Activities

It is possible to detect when the user is sleeping using a[`HealthActivityMask`](/docs/c/Foundation/Event_Service/HealthService/#HealthActivityMask "HealthActivityMask") value. A useful application of this information could be to disable a watchface's animations or tick at a reduced rate once the user is asleep. This is done by checking certain bits of the returned value:

```
// Get an activities maskHealthActivityMask activities = health\_service\_peek\_current\_activities();// Determine which bits are set, and hence which activity is activeif(activities & HealthActivitySleep) {APP\_LOG(APP\_LOG\_LEVEL\_INFO, "The user is sleeping.");} else if(activities & HealthActivityRestfulSleep) {APP\_LOG(APP\_LOG\_LEVEL\_INFO, "The user is sleeping peacefully.");} else {APP\_LOG(APP\_LOG\_LEVEL\_INFO, "The user is not currently sleeping.");}
```

## Read Per-Minute History

The [`HealthMinuteData`](/docs/c/Foundation/Event_Service/HealthService/#HealthMinuteData "HealthMinuteData") structure contains multiple types of activity-related data that are recorded in a minute-by-minute fashion. This style of data access is best suited to those applications requiring more granular detail (such as creating a new fitness algorithm). Up to seven days worth of data is available with this API.

> See [_Notes on Minute-level Data_](#notes-on-minute-level-data) below for more information on minute-level data.

The data items contained in the [`HealthMinuteData`](/docs/c/Foundation/Event_Service/HealthService/#HealthMinuteData "HealthMinuteData") structure are summarized below:

| Item | Type | Description |
| --- | --- | --- |
| `steps` | `uint8_t` | Number of steps taken in this minute. |
| `orientation` | `uint8_t` | Quantized average orientation, encoding the x-y plane (the "yaw") in the lower 4 bits (360 degrees linearly mapped to 1 of 16 values) and the z axis (the "pitch") in the upper 4 bits. |
| `vmc` | `uint16_t` | Vector Magnitude Counts (VMC). This is a measure of the total amount of movement seen by the watch. More vigorous movement yields higher VMC values. |
| `is_invalid` | `bool` | `true` if the item doesn't represent actual data, and should be ignored. |
| `heart_rate_bpm` | `uint8_t` | Heart rate in beats per minute (if available). |

These data items can be obtained in the following manner, similar to obtaining a sum.

```
// Create an array to store dataconst uint32\_t max\_records = 60;HealthMinuteData \*minute\_data = (HealthMinuteData\*)malloc(max\_records \* sizeof(HealthMinuteData));// Make a timestamp for 15 minutes ago and an hour before thattime\_t end = time(NULL) - (15 \* SECONDS\_PER\_MINUTE);time\_t start = end - SECONDS\_PER\_HOUR;// Obtain the minute-by-minute recordsuint32\_t num\_records = health\_service\_get\_minute\_history(minute\_data,max\_records, &start, &end);APP\_LOG(APP\_LOG\_LEVEL\_INFO, "num\_records: %d", (int)num\_records);// Print the number of steps for each minutefor(uint32\_t i = 0; i \< num\_records; i++) {APP\_LOG(APP\_LOG\_LEVEL\_INFO, "Item %d steps: %d", (int)i,(int)minute\_data[i].steps);}
```

Don't forget to free the array once the data is finished with:

```
// Free the arrayfree(minute\_data);
```

### Notes on Minute-level Data

Missing minute-level records can occur if the watch is reset, goes into low power (watch-only) mode due to critically low battery, or Pebble Health is disabled during the time period requested.

[`health_service_get_minute_history()`](/docs/c/Foundation/Event_Service/HealthService/#health_service_get_minute_history "health\_service\_get\_minute\_history") will return as many **consecutive** minute-level records that are available after the provided `start` timestamp, skipping any missing records until one is found. This API behavior enables one to easily continue reading data after a previous query encountered a missing minute. If there are some minutes with missing data, the API will return all available records up to the last available minute, and no further. Conversely, records returned will begin with the first available record after the provided`start` timestamp, skipping any missing records until one is found. This can be used to continue reading data after a previous query encountered a missing minute.

The code snippet below shows an example function that packs a provided[`HealthMinuteData`](/docs/c/Foundation/Event_Service/HealthService/#HealthMinuteData "HealthMinuteData") array with all available values in a time range, up to an arbitrary maximum number. Any missing minutes are collapsed, so that as much data can be returned as is possible for the allocated array size and time range requested.

> This example shows querying up to 60 records. More can be obtained, but this increases the heap allocation required as well as the time taken to process the query.

```
static uint32\_t get\_available\_records(HealthMinuteData \*array, time\_t query\_start,time\_t query\_end, uint32\_t max\_records) {time\_t next\_start = query\_start;time\_t next\_end = query\_end;uint32\_t num\_records\_found = 0;// Find more records until no more are returnedwhile (num\_records\_found \< max\_records) {int ask\_num\_records = max\_records - num\_records\_found;uint32\_t ret\_val = health\_service\_get\_minute\_history(&array[num\_records\_found],ask\_num\_records, &next\_start, &next\_end);if (ret\_val == 0) {// a 0 return value means no more data is availablereturn num\_records\_found;}num\_records\_found += ret\_val;next\_start = next\_end;next\_end = query\_end;}return num\_records\_found;}static void print\_last\_hours\_steps() {// Query for the last hour, max 60 minute-level records// (except the last 15 minutes)const time\_t query\_end = time(NULL) - (15 \* SECONDS\_PER\_MINUTE);const time\_t query\_start = query\_end - SECONDS\_PER\_HOUR;const uint32\_t max\_records = (query\_end - query\_start) / SECONDS\_PER\_MINUTE;HealthMinuteData \*data =(HealthMinuteData\*)malloc(max\_records \* sizeof(HealthMinuteData));// Populate the arraymax\_records = get\_available\_records(data, query\_start, query\_end, max\_records);// Print the resultsfor(uint32\_t i = 0; i \< max\_records; i++) {if(!data[i].is\_invalid) {APP\_LOG(APP\_LOG\_LEVEL\_INFO, "Record %d contains %d steps.", (int)i,(int)data[i].steps);} else {APP\_LOG(APP\_LOG\_LEVEL\_INFO, "Record %d was not valid.", (int)i);}}free(data);}
```
