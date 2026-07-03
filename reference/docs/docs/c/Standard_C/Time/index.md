# Time

Source: https://developer.repebble.com/docs/c/Standard_C/Time/index.html

Standard system time functions

This module contains standard time functions and formatters for printing. Note that Pebble now supports both local time and UTC time (including timezones and daylight savings time). Most of these functions are part of the C standard library which is documented at [https://sourceware.org/newlib/libc.html#Timefns](https://sourceware.org/newlib/libc.html#Timefns)

## Function Documentation

- [SDK 3](javascript:void(0);)
- [SDK 4](javascript:void(0);)
- [SDK 4.9+](javascript:void(0);)

int strftime(char \* s, [size\_t](/docs/c/Standard_C/Memory/#size_t) maxsize, const char \* format, const struct tm \* tm\_p)

Format the time value at tm according to fmt and place the result in a buffer s of size max.

#### Parameters
 s

A preallocation char array of size max

 maxsize

the size of the array s

 format

a formatting string

 tm\_p

A pointer to a struct tm containing a broken out time value

#### Returns

The number of bytes placed in the array s, not including the null byte, 0 if the value does not fit.

int strftime(char \* s, [size\_t](/docs/c/Standard_C/Memory/#size_t) maxsize, const char \* format, const struct tm \* tm\_p)

Format the time value at tm according to fmt and place the result in a buffer s of size max.

#### Parameters
 s

A preallocation char array of size max

 maxsize

the size of the array s

 format

a formatting string

 tm\_p

A pointer to a struct tm containing a broken out time value

#### Returns

The number of bytes placed in the array s, not including the null byte, 0 if the value does not fit.

[size\_t](/docs/c/Standard_C/Memory/#size_t) strftime(char \* s, [size\_t](/docs/c/Standard_C/Memory/#size_t) maxsize, const char \* format, const struct tm \* tm\_p)

Format the time value at tm according to fmt and place the result in a buffer s of size max.

#### Parameters
 s

A preallocation char array of size max

 maxsize

the size of the array s

 format

a formatting string

 tm\_p

A pointer to a struct tm containing a broken out time value

#### Returns

The number of bytes placed in the array s, not including the null byte, 0 if the value does not fit.

struct tm \* localtime(const [time\_t](/docs/c/Standard_C/Time/#time_t) \* timep)

convert the time value pointed at by clock to a struct tm which contains the time adjusted for the local timezone

#### Parameters
 timep

A pointer to an object of type [time\_t](/docs/c/Standard_C/Time/#time_t) that contains a time value

#### Returns

A pointer to a struct tm containing the broken out time value adjusted for the local timezone

struct tm \* gmtime(const [time\_t](/docs/c/Standard_C/Time/#time_t) \* timep)

convert the time value pointed at by clock to a struct tm which contains the time expressed in Coordinated Universal Time (UTC)

#### Parameters
 timep

A pointer to an object of type [time\_t](/docs/c/Standard_C/Time/#time_t) that contains a time value

#### Returns

A pointer to a struct tm containing Coordinated Universal Time (UTC)

[time\_t](/docs/c/Standard_C/Time/#time_t) mktime(struct tm \* tb)

convert the broken-down time structure to a timestamp expressed in Coordinated Universal Time (UTC)

#### Parameters
 tb

A pointer to an object of type tm that contains broken-down time

#### Returns

The number of seconds since epoch, January 1st 1970

[time\_t](/docs/c/Standard_C/Time/#time_t) time([time\_t](/docs/c/Standard_C/Time/#time_t) \* tloc)

Obtain the number of seconds since epoch. Note that the epoch is not adjusted for Timezones and Daylight Savings.

#### Parameters
 tloc

Optionally points to an address of a [time\_t](/docs/c/Standard_C/Time/#time_t) variable to store the time in. If you only want to use the return value, you may pass NULL into tloc instead

#### Returns

The number of seconds since epoch, January 1st 1970

double difftime([time\_t](/docs/c/Standard_C/Time/#time_t) end, [time\_t](/docs/c/Standard_C/Time/#time_t) beginning)

Obtain the number of seconds elapsed between beginning and end represented as a double.

##### Note

Pebble uses software floating point emulation. Including this function which returns a double will significantly increase the size of your binary. We recommend directly subtracting both timestamps to calculate a time difference.

```
int difference = ts1 - ts2;
```

#### Parameters
 end

A [time\_t](/docs/c/Standard_C/Time/#time_t) variable representing some number of seconds since epoch, January 1st 1970

 beginning

A [time\_t](/docs/c/Standard_C/Time/#time_t) variable representing some number of seconds since epoch, January 1st 1970. Note that end should be greater than beginning, but this is not enforced.

#### Returns

The number of seconds elapsed between beginning and end.

[uint16\_t](/docs/c/Standard_C/#uint16_t) time\_ms([time\_t](/docs/c/Standard_C/Time/#time_t) \* t\_utc, [uint16\_t](/docs/c/Standard_C/#uint16_t) \* out\_ms)

Obtain the number of seconds and milliseconds part since the epoch. This is a non-standard C function provided for convenience.

#### Parameters
 tloc

Optionally points to an address of a [time\_t](/docs/c/Standard_C/Time/#time_t) variable to store the time in. You may pass NULL into tloc if you don't need a [time\_t](/docs/c/Standard_C/Time/#time_t) variable to be set with the seconds since the epoch

 out\_ms

Optionally points to an address of a [uint16\_t](/docs/c/Standard_C/#uint16_t) variable to store the number of milliseconds since the last second in. If you only want to use the return value, you may pass NULL into out\_ms instead

#### Returns

The number of milliseconds since the last second

[time\_t](/docs/c/Standard_C/Time/#time_t) time\_start\_of\_today(void)

Return the UTC time that corresponds to the start of today (midnight).

#### Returns

the UTC time corresponding to the start of today (midnight)

## Typedef Documentation

 typedef unsigned int time\_t

time in seconds since the epoch, January 1st 1970

## Macro Definition Documentation

#define TZ\_LEN 6

#define SECONDS\_PER\_MINUTE (60)

#define MINUTES\_PER\_HOUR (60)

#define SECONDS\_PER\_HOUR (SECONDS\_PER\_MINUTE \* MINUTES\_PER\_HOUR)

#define HOURS\_PER\_DAY (24)

#define MINUTES\_PER\_DAY (HOURS\_PER\_DAY \* MINUTES\_PER\_HOUR)

#define SECONDS\_PER\_DAY (MINUTES\_PER\_DAY \* SECONDS\_PER\_MINUTE)
