# Logging

Source: https://developer.repebble.com/docs/c/Foundation/Logging/index.html

Functions related to logging from apps.

This module contains the functions necessary to log messages through Bluetooth.

## Function Documentation

void app\_log(uint8\_t log\_level, const char \* src\_filename, int src\_line\_number, const char \* fmt, ...)

## Enum Documentation

enum AppLogLevel

Suggested log level values.

#### Enumerators
APP\_LOG\_LEVEL\_ERROR

Error level log message.

APP\_LOG\_LEVEL\_WARNING

Warning level log message.

APP\_LOG\_LEVEL\_INFO

Info level log message.

APP\_LOG\_LEVEL\_DEBUG

Debug level log message.

APP\_LOG\_LEVEL\_DEBUG\_VERBOSE

Verbose Debug level log message.

## Macro Definition Documentation

#define APP\_LOG ( level, fmt, args...)

A helper macro that simplifies the use of the app\_log function.

#### Parameters
 level

The log level to log output as

 fmt

A C formatting string

 args

The arguments for the formatting string
