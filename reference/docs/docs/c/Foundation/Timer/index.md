# Timer

Source: https://developer.repebble.com/docs/c/Foundation/Timer/index.html

Can be used to execute some code at some point in the future.

## Function Documentation

void psleep(int millis)

Waits for a certain amount of milliseconds.

#### Parameters
 millis

The number of milliseconds to wait for

AppTimer \* app\_timer\_register([uint32\_t](/docs/c/Standard_C/#uint32_t) timeout\_ms, [AppTimerCallback](/docs/c/Foundation/Timer/#AppTimerCallback) callback, void \* callback\_data)

Registers a timer that ends up in callback being called some specified time in the future.

#### Parameters
 timeout\_ms

The expiry time in milliseconds from the current time

 callback

The callback that gets called at expiry time

 callback\_data

The data that will be passed to callback

#### Returns

A pointer to an `AppTimer` that can be used to later reschedule or cancel this timer

- [SDK 3](javascript:void(0);)
- [SDK 4](javascript:void(0);)
- [SDK 4.9+](javascript:void(0);)

bool app\_timer\_reschedule(AppTimer \* timer\_handle, [uint32\_t](/docs/c/Standard_C/#uint32_t) new\_timeout\_ms)

Reschedules an already running timer for some point in the future.

#### Parameters
 timer\_handle

The timer to reschedule

 new\_timeout\_ms

The new expiry time in milliseconds from the current time

#### Returns

true if the timer was rescheduled, false if the timer has already elapsed

bool app\_timer\_reschedule(AppTimer \* timer\_handle, [uint32\_t](/docs/c/Standard_C/#uint32_t) new\_timeout\_ms)

Reschedules an already running timer for some point in the future.

#### Parameters
 timer\_handle

The timer to reschedule

 new\_timeout\_ms

The new expiry time in milliseconds from the current time

#### Returns

true if the timer was rescheduled, false if the timer has already elapsed

bool app\_timer\_reschedule(AppTimer \* timer\_handle, [uint32\_t](/docs/c/Standard_C/#uint32_t) new\_timeout\_ms)

Reschedules an already running timer for some point in the future. Elapsed timers cannot be rescheduled.

#### Parameters
 timer\_handle

The timer to reschedule

 new\_timeout\_ms

The new expiry time in milliseconds from the current time

#### Returns

true if the timer was rescheduled, false if the timer has already elapsed

- [SDK 3](javascript:void(0);)
- [SDK 4](javascript:void(0);)
- [SDK 4.9+](javascript:void(0);)

void app\_timer\_cancel(AppTimer \* timer\_handle)

Cancels an already registered timer. Once cancelled the handle may no longer be used for any purpose.

void app\_timer\_cancel(AppTimer \* timer\_handle)

Cancels an already registered timer. Once cancelled the handle may no longer be used for any purpose.

void app\_timer\_cancel(AppTimer \* timer\_handle)

Cancels an already registered timer. Once cancelled the handle may no longer be used for any purpose. Elapsed timers do not need to be cancelled.

## Typedef Documentation

 typedef struct AppTimer AppTimer

 typedef void(\* AppTimerCallback)(void \*data) 

The type of function which can be called when a timer fires. The argument will be the `callback_data` passed to [app\_timer\_register()](/docs/c/Foundation/Timer/#app_timer_register).
