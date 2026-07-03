# Heart Rate Monitor

Source: https://developer.repebble.com/guides/events-and-services/hrm/

The Pebble Time 2 and Pebble 2 (excluding SE model)[_devices_](/guides/tools-and-resources/hardware-information.md) include a heart rate monitor. This guide will demonstrate how to use the [`HealthService`](/docs/c/Foundation/Event_Service/HealthService/ "HealthService")API to retrieve information about the user's current, and historical heart rates.

If you aren't already familiar with the [`HealthService`](/docs/c/Foundation/Event_Service/HealthService/ "HealthService"), we recommended that you read the [_Health guide_](/guides/events-and-services/health.md)before proceeding.

## Enable Health Data

Before your application is able to access the heart rate information, you will need to add `heath` to the `capabilities` array in your applications`package.json` file.

```
{..."pebble": {..."capabilities": ["health"],...}}
```

## Data Quality

Heart rate sensors aren't perfect, and their readings can be affected by improper positioning, environmental factors and excessive movement. The raw data from the HRM sensor contains a metric to indicate the quality of the readings it receives.

The HRM API provides a raw BPM reading ([`HealthMetricHeartRateRawBPM`](/docs/c/Foundation/Event_Service/HealthService/#HealthMetricHeartRateRawBPM "HealthMetricHeartRateRawBPM")) and a filtered reading ([`HealthMetricHeartRateBPM`](/docs/c/Foundation/Event_Service/HealthService/#HealthMetricHeartRateBPM "HealthMetricHeartRateBPM")). This filtered value minimizes the effect of hand movement and improper sensor placement, by removing the bad quality readings. This filtered data makes it easy for developers to integrate in their applications, without needing to filter the data themselves.

## Obtaining the Current Heart Rate

To obtain the current heart rate, you should first check whether the[`HealthMetricHeartRateBPM`](/docs/c/Foundation/Event_Service/HealthService/#HealthMetricHeartRateBPM "HealthMetricHeartRateBPM") is available by using the[`health_service_metric_accessible`](/docs/c/Foundation/Event_Service/HealthService/#health_service_metric_accessible "health\_service\_metric\_accessible") method.

Then you can obtain the current heart rate using the[`health_service_peek_current_value`](/docs/c/Foundation/Event_Service/HealthService/#health_service_peek_current_value "health\_service\_peek\_current\_value") method:

```
HealthServiceAccessibilityMask hr = health\_service\_metric\_accessible(HealthMetricHeartRateBPM, time(NULL), time(NULL));if (hr & HealthServiceAccessibilityMaskAvailable) {HealthValue val = health\_service\_peek\_current\_value(HealthMetricHeartRateBPM);if(val \> 0) {// Display HRM valuestatic char s\_hrm\_buffer[8];snprintf(s\_hrm\_buffer, sizeof(s\_hrm\_buffer), "%lu BPM", (uint32\_t)val);text\_layer\_set\_text(s\_hrm\_layer, s\_hrm\_buffer);}}
```

> **Note** this value is averaged from readings taken over the past minute, but due to the [sampling rate](#heart-rate-sample-periods) and our data filters, this value could be several minutes old. Use `HealthMetricHeartRateRawBPM` for the raw, unfiltered value.

## Subscribing to Heart Rate Updates

The user's heart rate can also be monitored via an event subscription, in a similar way to the other health metrics. If you wanted your watchface to update the displayed heart rate every time the HRM takes a new reading, you could use the [`health_service_events_subscribe`](/docs/c/Foundation/Event_Service/HealthService/#health_service_events_subscribe "health\_service\_events\_subscribe") method.

```
static void prv\_on\_health\_data(HealthEventType type, void \*context) {// If the update was from the Heart Rate Monitor, query itif (type == HealthEventHeartRateUpdate) {HealthValue value = health\_service\_peek\_current\_value(HealthMetricHeartRateBPM);// Display the heart rate}}static void prv\_init(void) {// Subscribe to health event handlerhealth\_service\_events\_subscribe(prv\_on\_health\_data, NULL);// ...}
```

> **Note** The frequency of these updates does not directly correlate to the sensor sampling rate.

## Heart Rate Sample Periods

The default sample period is 10 minutes, but the system automatically controls the HRM sample rate based on the level of user activity. It increases the sampling rate during intense activity and reduces it again during inactivity. This aims to provide the optimal battery usage.

### Battery Considerations

Like all active sensors, accelerometer, backlight etc, the HRM sensor will have a negative affect on battery life. It's important to consider this when using the APIs within your application.

By default the system will automatically control the heart rate sampling period for the optimal balance between update frequency and battery usage. In addition, the APIs have been designed to allow developers to retrieve values for the most common use cases with minimal impact on battery life.

### Altering the Sampling Period

Developers can request a specific sampling rate using the[`health_service_set_heart_rate_sample_period`](/docs/c/Foundation/Event_Service/HealthService/#health_service_set_heart_rate_sample_period "health\_service\_set\_heart\_rate\_sample\_period") method. The system will use this value as a suggestion, but does not guarantee that value will be used. The actual sampling period may be greater or less due to other apps that require input from the sensor, or data quality issues.

The shortest period you can currently specify is `1` second, and the longest period you can specify is `600` seconds (10 minutes).

In this example, we will sample the heart rate monitor every second:

```
// Set the heart rate monitor to sample every secondbool success = health\_service\_set\_heart\_rate\_sample\_period(1);
```

> **Note** This does not mean that you can peek the current value every second, only that the sensor will capture more samples.

### Resetting the Sampling Period

Developers **must** reset the heart rate sampling period when their application exits. Failing to do so may result in the heart rate monitor continuing at the increased rate for a period of time, even after your application closes. This is fundamentally different to other Pebble sensors and was designed so that applications which a reliant upon high sampling rates can be temporarily interupted for notifications, or music, without affecting the sensor data.

```
// Reset the heart rate sampling period to automatichealth\_service\_set\_heart\_rate\_sample\_period(0);
```

## Obtaining Historical Data

If your application is using heart rate information, it may also want to obtain historical data to compare it against. In this section we'll look at how you can use the `health_service_aggregate` functions to obtain relevant historic data.

Before requesting historic/aggregate data for a specific time period, you should ensure that it is available using the[`health_service_metric_accessible`](/docs/c/Foundation/Event_Service/HealthService/#health_service_metric_accessible "health\_service\_metric\_accessible") method.

Then we'll use the [`health_service_aggregate_averaged`](/docs/c/Foundation/Event_Service/HealthService/#health_service_aggregate_averaged "health\_service\_aggregate\_averaged") method to obtain the average daily heart rate over the last 7 days.

```
// Obtain history for last 7 daystime\_t end\_time = time(NULL);time\_t start\_time = end\_time - (7 \* SECONDS\_PER\_DAY);HealthServiceAccessibilityMask hr = health\_service\_metric\_accessible(HealthMetricHeartRateBPM, start\_time, end\_time);if (hr & HealthServiceAccessibilityMaskAvailable) {uint32\_t weekly\_avg\_hr = health\_service\_aggregate\_averaged(HealthMetricHeartRateBPM,start\_time, end\_time,HealthAggregationAvg, HealthServiceTimeScopeDaily);}
```

You can also query the average `min` and `max` heart rates, but only within the past two hours (maximum). This limitation is due to very limited storage capacity on the device, but the implementation may change in the future.

```
// Obtain history for last 1 hourtime\_t end\_time = time(NULL);time\_t start\_time = end\_time - SECONDS\_PER\_HOUR;HealthServiceAccessibilityMask hr = health\_service\_metric\_accessible(HealthMetricHeartRateBPM, start\_time, end\_time);if (hr & HealthServiceAccessibilityMaskAvailable) {uint32\_t min\_hr = health\_service\_aggregate\_averaged(HealthMetricHeartRateBPM,start\_time, end\_time,HealthAggregationMin, HealthServiceTimeScopeOnce);uint32\_t max\_hr = health\_service\_aggregate\_averaged(HealthMetricHeartRateBPM,start\_time, end\_time,HealthAggregationMax, HealthServiceTimeScopeOnce);}
```

## Read Per-Minute History

The [`HealthMinuteData`](/docs/c/Foundation/Event_Service/HealthService/#HealthMinuteData "HealthMinuteData") structure contains multiple types of activity-related data that are recorded in a minute-by-minute fashion. Although this structure now contains HRM readings, it does not contain information about the quality of those readings.

> **Note** Please refer to the[_Health Guide_](/guides/events-and-services/health.md#read-per-minute-history)for futher information.

## Next Steps

This guide covered the basics of how to interact with realtime and historic heart information. We encourage you to further explore the [`HealthService`](/docs/c/Foundation/Event_Service/HealthService/ "HealthService")documentation, and integrate it into your next project.
