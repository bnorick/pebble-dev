# Wakeup

Source: https://developer.repebble.com/docs/c/Foundation/Wakeup/index.html

Allows applications to schedule to be launched even if they are not running.

## Function Documentation

- [SDK 3](javascript:void(0);)
- [SDK 4](javascript:void(0);)
- [SDK 4.9+](javascript:void(0);)

void wakeup\_service\_subscribe([WakeupHandler](/docs/c/Foundation/Wakeup/#WakeupHandler) handler)

Registers a [WakeupHandler](/docs/c/Foundation/Wakeup/#WakeupHandler) to be called when wakeup events occur.

#### Parameters
 handler

The callback that gets called when the wakeup event occurs

void wakeup\_service\_subscribe([WakeupHandler](/docs/c/Foundation/Wakeup/#WakeupHandler) handler)

Registers a [WakeupHandler](/docs/c/Foundation/Wakeup/#WakeupHandler) to be called when wakeup events occur.

#### Parameters
 handler

The callback that gets called when the wakeup event occurs

void wakeup\_service\_subscribe([WakeupHandler](/docs/c/Foundation/Wakeup/#WakeupHandler) handler)

Registers a [WakeupHandler](/docs/c/Foundation/Wakeup/#WakeupHandler) to be called when wakeup events occur.

##### Note

The handler is only called for wakeup events which occur while the app is already running; use [launch\_reason()](/docs/c/Foundation/Launch_Reason/#launch_reason) === APP\_LAUNCH\_WAKEUP to detect when the app was launched by a wakeup event.

#### Parameters
 handler

The callback that gets called when the wakeup event occurs

[WakeupId](/docs/c/Foundation/Wakeup/#WakeupId) wakeup\_schedule([time\_t](/docs/c/Standard_C/Time/#time_t) timestamp, int32\_t cookie, bool notify\_if\_missed)

Registers a wakeup event that triggers a callback at the specified time. Applications may only schedule up to 8 wakeup events. Wakeup events are given a 1 minute duration window, in that no application may schedule a wakeup event with 1 minute of a currently scheduled wakeup event.

#### Parameters
 timestamp

The requested time (UTC) for the wakeup event to occur

 cookie

The application specific reason for the wakeup event

 notify\_if\_missed

On powering on Pebble, will alert user when notifications were missed due to Pebble being off.

#### Returns

negative values indicate errors ([StatusCode](/docs/c/Foundation/Storage/#StatusCode)) E\_RANGE if the event cannot be scheduled due to another event in that period. E\_INVALID\_ARGUMENT if the time requested is in the past. E\_OUT\_OF\_RESOURCES if the application has already scheduled all 8 wakeup events. E\_INTERNAL if a system error occurred during scheduling.

void wakeup\_cancel([WakeupId](/docs/c/Foundation/Wakeup/#WakeupId) wakeup\_id)

Cancels a wakeup event.

#### Parameters
 wakeup\_id

Wakeup event to cancel

void wakeup\_cancel\_all(void)

Cancels all wakeup event for the app.

bool wakeup\_get\_launch\_event([WakeupId](/docs/c/Foundation/Wakeup/#WakeupId) \* wakeup\_id, int32\_t \* cookie)

Retrieves the wakeup event info for an app that was launched by a wakeup\_event (ie. [launch\_reason()](/docs/c/Foundation/Launch_Reason/#launch_reason) === APP\_LAUNCH\_WAKEUP) so that an app may display information regarding the wakeup event.

#### Parameters
 wakeup\_id

[WakeupId](/docs/c/Foundation/Wakeup/#WakeupId) for the wakeup event that caused the app to wakeup

 cookie

App provided reason for the wakeup event

#### Returns

True if app was launched due to a wakeup event, false otherwise

bool wakeup\_query([WakeupId](/docs/c/Foundation/Wakeup/#WakeupId) wakeup\_id, [time\_t](/docs/c/Standard_C/Time/#time_t) \* timestamp)

Checks if the current [WakeupId](/docs/c/Foundation/Wakeup/#WakeupId) is still scheduled and therefore valid.

#### Parameters
 wakeup\_id

Wakeup event to query for validity and scheduled time

 timestamp

Optionally points to an address of a [time\_t](/docs/c/Standard_C/Time/#time_t) variable to store the time that the wakeup event is scheduled to occur. (The time is in UTC, but local time when [clock\_is\_timezone\_set](/docs/c/Foundation/Wall_Time/#clock_is_timezone_set) returns false). You may pass NULL instead if you do not need it.

#### Returns

True if [WakeupId](/docs/c/Foundation/Wakeup/#WakeupId) is still scheduled, false if it doesn't exist or has already occurred

## Typedef Documentation

 typedef int32\_t WakeupId

[WakeupId](/docs/c/Foundation/Wakeup/#WakeupId) is an identifier for a wakeup event.

 typedef void(\* WakeupHandler)(WakeupId wakeup\_id, int32\_t cookie) 

The type of function which can be called when a wakeup event occurs.   
 The arguments will be the id of the wakeup event that occurred, as well as the scheduled cookie provided to [wakeup\_schedule](/docs/c/Foundation/Wakeup/#wakeup_schedule).
