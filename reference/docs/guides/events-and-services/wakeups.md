# Wakeups

Source: https://developer.repebble.com/guides/events-and-services/wakeups/

The [`Wakeup`](/docs/c/Foundation/Wakeup/ "Wakeup") API allows developers to schedule an app launch in the future, even if the app itself is closed in the meantime. A wakeup event is scheduled in a similar manner to a [`Timer`](/docs/c/Foundation/Timer/ "Timer") with a future timestamp calculated beforehand.

## Calculating Timestamps

To schedule a wakeup event, first determine the timestamp of the desired wakeup time as a `time_t` variable. Most uses of the [`Wakeup`](/docs/c/Foundation/Wakeup/ "Wakeup") API will fall into three distinct scenarios discussed below.

### A Future Time

Call [`time()`](/docs/c/Standard_C/Time/ "Time") and add the offset, measured in seconds. For example, for 30 minutes in the future:

```
// 30 minutes from nowtime\_t timestamp = time(NULL) + (30 \* SECONDS\_PER\_MINUTE);
```

### A Specific Time

Use [`clock_to_timestamp()`](/docs/c/Foundation/Wall_Time/#clock_to_timestamp "clock\_to\_timestamp") to obtain a `time_t` timestamp by specifying a day of the week and hours and minutes (in 24 hour format). For example, for the next occuring Monday at 5 PM:

```
// Next occuring monday at 17:00 time\_t timestamp = clock\_to\_timestamp(MONDAY, 17, 0);
```

### Using a Timestamp Provided by a Web Service

The timestamp will need to be translated using the [`getTimezoneOffset()`](http://www.w3schools.com/jsref/jsref_gettimezoneoffset.asp) method available in PebbleKit JS or with any timezone information given by the web service.

## Scheduling a Wakeup

Once a `time_t` timestamp has been calculated, the wakeup event can be scheduled:

```
// Let the timestamp be 30 minutes from nowconst time\_t future\_timestamp = time() + (30 \* SECONDS\_PER\_MINUTE);// Choose a 'cookie' value representing the reason for the wakeupconst int cookie = 0;// If true, the user will be notified if they missed the wakeup // (i.e. their watch was off)const bool notify\_if\_missed = true;// Schedule wakeup eventWakeupId id = wakeup\_schedule(future\_timestamp, cookie, notify\_if\_missed);// Check the scheduling was successfulif(id \>= 0) {// Persist the ID so that a future launch can query itconst wakeup\_id\_key = 43;persist\_write\_int(wakeup\_id\_key, id);}
```

After scheduling a wakeup event it is possible to perform some interaction with it. For example, reading the timestamp for when the event will occur using the[`WakeupId`](/docs/c/Foundation/Wakeup/#WakeupId "WakeupId") with [`wakeup_query()`](/docs/c/Foundation/Wakeup/#wakeup_query "wakeup\_query"), and then perform simple arithmetic to get the time remaining:

```
// This will be set by wakeup\_query()time\_t wakeup\_timestamp = 0;// Is the wakeup still scheduled?if(wakeup\_query(id, &wakeup\_timestamp)) {// Get the time remainingint seconds\_remaining = wakeup\_timestamp - time(NULL);APP\_LOG(APP\_LOG\_LEVEL\_INFO, "%d seconds until wakeup", seconds\_remaining);}
```

To cancel a scheduled event, use the [`WakeupId`](/docs/c/Foundation/Wakeup/#WakeupId "WakeupId") obtained when it was scheduled:

```
// Cancel a wakeupwakeup\_cancel(id);
```

To cancel all scheduled wakeup events:

```
// Cancel all wakeupswakeup\_cancel\_all();
```

## Limitations

There are three limitations that should be taken into account when using the Wakeup API:

- There can be no more than 8 scheduled wakeup events per app at any one time.

- Wakeup events cannot be scheduled within 30 seconds of the current time.

- Wakeup events are given a one minute window either side of the wakeup time. In this time no app may schedule an event. The return [`StatusCode`](/docs/c/Foundation/Storage/#StatusCode "StatusCode") of[`wakeup_schedule()`](/docs/c/Foundation/Wakeup/#wakeup_schedule "wakeup\_schedule") should be checked to determine whether the scheduling of the new event should be reattempted. A negative value indicates that the wakeup could not be scheduled successfully.

The possible [`StatusCode`](/docs/c/Foundation/Storage/#StatusCode "StatusCode") values are detailed below:

| StatusCode | Value | Description |
| --- | --- | --- |
| `E_RANGE` | `-8` | The wakeup event cannot be scheduled due to another event in that period. |
| `E_INVALID_ARGUMENT` | `-4` | The time requested is in the past. |
| `E_OUT_OF_RESOURCES` | `-7` | The application has already scheduled all 8 wakeup events. |
| `E_INTERNAL` | `-3` | A system error occurred during scheduling. |

## Handling Wakeup Events

A wakeup event can occur at two different times - when the app is closed, and when it is already launched and in the foreground.

If the app is launched due to a previously scheduled wakeup event, check the[`AppLaunchReason`](/docs/c/Foundation/Launch_Reason/#AppLaunchReason "AppLaunchReason") and load the app accordingly:

```
static void init() {if(launch\_reason() == APP\_LAUNCH\_WAKEUP) {// The app was started by a wakeup event.WakeupId id = 0;int32\_t reason = 0;// Get details and handle the event appropriatelywakeup\_get\_launch\_event(&id, &reason);}/\* other init code \*/}
```

If the app is expecting a wakeup to occur while it is open, use a subscription to the wakeup service to be notified of such events:

```
static void wakeup\_handler(WakeupId id, int32\_t reason) {// A wakeup event has occurred while the app was already open}
```

```
// Subscribe to wakeup servicewakeup\_service\_subscribe(wakeup\_handler);
```

The two approaches can also be combined for a unified response to being woken up, not depenent on the state of the app:

```
// Get details of the wakeupwakeup\_get\_launch\_event(&id, &reason);// Manually handle using the handlerwakeup\_handler(id, reason);
```
