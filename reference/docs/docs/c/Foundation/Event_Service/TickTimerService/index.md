# TickTimerService

Source: https://developer.repebble.com/docs/c/Foundation/Event_Service/TickTimerService/index.html

Handling time components

The TickTimerService allows your app to be called every time one Time component has changed. This is extremely important for watchfaces. Your app can choose on which time component change a tick should occur. Time components are defined by a [TimeUnits](/docs/c/Foundation/Event_Service/TickTimerService/#TimeUnits) enum bitmask.

## Function Documentation

void tick\_timer\_service\_subscribe([TimeUnits](/docs/c/Foundation/Event_Service/TickTimerService/#TimeUnits) tick\_units, [TickHandler](/docs/c/Foundation/Event_Service/TickTimerService/#TickHandler) handler)

Subscribe to the tick timer event service. Once subscribed, the handler gets called on every requested unit change. Calling this function multiple times will override the units and handler (i.e., only&nbsp; the&nbsp;last&nbsp;tick\_units and&nbsp;handler passed&nbsp;will&nbsp;be&nbsp;used).

#### Parameters
 handler

The callback to be executed on tick events

 tick\_units

a bitmask of all the units that have changed

void tick\_timer\_service\_unsubscribe(void)

Unsubscribe from the tick timer event service. Once unsubscribed, the previously registered handler will no longer be called.

## Enum Documentation

enum TimeUnits

Time unit flags that can be used to create a bitmask for use in [tick\_timer\_service\_subscribe()](/docs/c/Foundation/Event_Service/TickTimerService/#tick_timer_service_subscribe). This will also be passed to [TickHandler](/docs/c/Foundation/Event_Service/TickTimerService/#TickHandler).

#### Enumerators
SECOND\_UNIT

Flag to represent the "seconds" time unit.

MINUTE\_UNIT

Flag to represent the "minutes" time unit.

HOUR\_UNIT

Flag to represent the "hours" time unit.

DAY\_UNIT

Flag to represent the "days" time unit.

MONTH\_UNIT

Flag to represent the "months" time unit.

YEAR\_UNIT

Flag to represent the "years" time unit.

## Typedef Documentation

 typedef void(\* TickHandler)(struct tm \*tick\_time, TimeUnits units\_changed) 

Callback type for tick timer events.

#### Parameters
 tick\_time

the time at which the tick event was triggered

 units\_changed

which unit change triggered this tick event
