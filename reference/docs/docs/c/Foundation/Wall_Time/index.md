# Wall Time

Source: https://developer.repebble.com/docs/c/Foundation/Wall_Time/index.html

Functions, data structures and other things related to wall clock time.

This module contains utilities to get the current time and create strings with formatted dates and times.

## Function Documentation

void clock\_copy\_time\_string(char \* buffer, uint8\_t size)

Copies a time string into the buffer, formatted according to the user's time display preferences (such as 12h/24h time). Example results: "7:30" or "15:00".

##### Note

AM/PM are also outputted with the time if the user's preference is 12h time.

#### Parameters
 buffer (out)

A pointer to the buffer to copy the time string into

 size

The maximum size of buffer

bool clock\_is\_24h\_style(void)

Gets the user's 12/24h clock style preference.

#### Returns

`true` if the user prefers 24h-style time display or `false` if the user prefers 12h-style time display.

- [SDK 3](javascript:void(0);)
- [SDK 4](javascript:void(0);)
- [SDK 4.9+](javascript:void(0);)

[time\_t](/docs/c/Standard_C/Time/#time_t) clock\_to\_timestamp([WeekDay](/docs/c/Foundation/Wall_Time/#WeekDay) day, int hour, int minute)

Converts a (day, hour, minute) specification to a UTC timestamp occurring in the future Always returns a timestamp for the next occurring instance, example: specifying TODAY@14:30 when it is 14:40 will return a timestamp for 7 days from now at 14:30.

##### Note

This function does not support Daylight Saving Time (DST) changes, events scheduled during a DST change will be off by an hour.

#### Parameters
 day

[WeekDay](/docs/c/Foundation/Wall_Time/#WeekDay) day of week including support for specifying TODAY

 hour

hour specified in 24-hour format [0-23]

 minute

minute [0-59]

[time\_t](/docs/c/Standard_C/Time/#time_t) clock\_to\_timestamp([WeekDay](/docs/c/Foundation/Wall_Time/#WeekDay) day, int hour, int minute)

Converts a (day, hour, minute) specification to a UTC timestamp occurring in the future Always returns a timestamp for the next occurring instance, example: specifying TODAY@14:30 when it is 14:40 will return a timestamp for 7 days from now at 14:30.

##### Note

This function does not support Daylight Saving Time (DST) changes, events scheduled during a DST change will be off by an hour.

#### Parameters
 day

[WeekDay](/docs/c/Foundation/Wall_Time/#WeekDay) day of week including support for specifying TODAY

 hour

hour specified in 24-hour format [0-23]

 minute

minute [0-59]

[time\_t](/docs/c/Standard_C/Time/#time_t) clock\_to\_timestamp([WeekDay](/docs/c/Foundation/Wall_Time/#WeekDay) day, int hour, int minute)

Converts a (day, hour, minute) specification to a UTC timestamp occurring in the future Always returns a timestamp for the next occurring instance, example: specifying TODAY@14:30 when it is 14:40 will return a timestamp for 7 days from now at 14:30.

#### Parameters
 day

[WeekDay](/docs/c/Foundation/Wall_Time/#WeekDay) day of week including support for specifying TODAY

 hour

hour specified in 24-hour format [0-23]

 minute

minute [0-59]

bool clock\_is\_timezone\_set(void)

Checks if timezone is currently set, otherwise gmtime == localtime.

#### Returns

`true` if timezone has been set, false otherwise

void clock\_get\_timezone(char \* timezone, const [size\_t](/docs/c/Standard_C/Memory/#size_t) buffer\_size)

If timezone is set, copies the current timezone long name (e.g. America/Chicago) to user-provided buffer.

##### Note

timezone buffer should be at least TIMEZONE\_NAME\_LENGTH bytes

#### Parameters
 timezone

A pointer to the buffer to copy the timezone long name into

 buffer\_size

Size of the allocated buffer to copy the timezone long name into

## Enum Documentation

enum WeekDay

Weekday values.

#### Enumerators
TODAY

Today.

SUNDAY

Sunday.

MONDAY

Monday.

TUESDAY

Tuesday.

WEDNESDAY

Wednesday.

THURSDAY

Thursday.

FRIDAY

Friday.

SATURDAY

Saturday.

## Macro Definition Documentation

#define TIMEZONE\_NAME\_LENGTH 32

The maximum length for a timezone full name (e.g. America/Chicago)
