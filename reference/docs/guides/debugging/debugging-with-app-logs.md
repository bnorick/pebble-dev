# Debugging with App Logs

Source: https://developer.repebble.com/guides/debugging/debugging-with-app-logs/

When apps in development do not behave as expected the developer can use app logs to find out what is going wrong. The C SDK and PebbleKit JS can both output messages and values to the console to allow developers to get realtime information on the state of their app.

This guide describes how to log information from both the C and JS parts of a watchapp or watchface and also how to read that information for debugging purposes.

## Logging in C

The C SDK includes the [`APP_LOG()`](/docs/c/Foundation/Logging/#app_log "app\_log") macro function which allows an app to log a string containing information to the console:

```
static int s\_buffer[5];for(int i = 0; i \< 10; i++) {// Store loop value in arrays\_buffer[i] = i;APP\_LOG(APP\_LOG\_LEVEL\_DEBUG, "Loop index now %d", i);}
```

This will result in the following output before crashing:

```
[INFO] D main.c:20 Loop index now 0
[INFO] D main.c:20 Loop index now 1
[INFO] D main.c:20 Loop index now 2
[INFO] D main.c:20 Loop index now 3
[INFO] D main.c:20 Loop index now 4
```

In this way it will be possible to tell the state of the loop index value if the app encounters a problem and crashes (such as going out of array bounds in the above example).

## Logging in JS

Information can be logged in PebbleKit JS and Pebble.js using the standard JavaScript console, which will then be passed on to the log output view. An example of this is to use the optional callbacks when using`Pebble.sendAppMessage()` to know if a message was sent successfully to the watch:

```
console.log('Sending data to Pebble...');Pebble.sendAppMessage({'KEY': value}, function(e) {console.log('Send successful!');}, function(e) {console.log('Send FAILED!');});
```

## Viewing Log Data

When viewing app logs, both the C and JS files' output are shown in the same view.

The `pebble` [_Command Line Tool_](/guides/tools-and-resources/pebble-tool.md) will output any logs from C and JS files after executing the `pebble logs` command and supplying the phone's IP address:

```
pebble logs --phone=192.168.1.25
```

> Note: You can also use `pebble install --logs' to combine both of these operations into one command.

## Memory Usage Information

In addition to the log output from developer apps, statistics about memory usage are also included in the C app logs when an app exits:

```
[INFO] process_manager.c:289: Heap Usage for App compass-ex: Total Size <22980B> Used <164B> Still allocated <0B>
```

This piece of information reports the total heap size of the app, the amount of memory allocated as a result of execution, and the amount of memory still allocated when it exited. This last number can alert any forgotten deallocations (for example, forgetting [`window_destroy()`](/docs/c/User_Interface/Window/#window_destroy "window\_destroy") after [`window_create()`](/docs/c/User_Interface/Window/#window_create "window\_create")). A small number such as `28B` is acceptable, provided it remains the same after subsequent executions. If it increases after each app exit it may indicate a memory leak.

For more information on system memory usage, checkout the[Size presentation from the 2014 Developer Retreat](https://www.youtube.com/watch?v=8tOhdUXcSkw).

## Alloy Instrumentation Logging

Alloy apps can enable instrumentation logging to get detailed output from the JavaScript runtime. This is useful for profiling and understanding what the XS engine is doing under the hood.

To enable instrumentation logging, modify the `src/c/mdbl.c` file in your Alloy project. Instead of passing `NULL` to `moddable_createMachine()`, pass a[`ModdableCreationRecord`](/docs/c/Foundation/Alloy/#ModdableCreationRecord "ModdableCreationRecord") with the`kModdableCreationFlagLogInstrumentation` flag:

```
#include \<pebble.h\>int main(void) {Window \*w = window\_create();window\_stack\_push(w, true);ModdableCreationRecord creation = {.recordSize = sizeof(ModdableCreationRecord),.flags = kModdableCreationFlagLogInstrumentation,};moddable\_createMachine(&creation);window\_destroy(w);}
```

The key changes from the default `mdbl.c` are:

1. Create a [`ModdableCreationRecord`](/docs/c/Foundation/Alloy/#ModdableCreationRecord "ModdableCreationRecord") struct, setting `recordSize` to`sizeof(ModdableCreationRecord)` for version compatibility.
2. Set `flags` to `kModdableCreationFlagLogInstrumentation`.
3. Pass a pointer to the creation record to `moddable_createMachine()` instead of `NULL`.

The instrumentation output will appear alongside regular app logs.

> **Note** : Instrumentation logging adds overhead and produces verbose output. Disable it for release builds by reverting to `moddable_createMachine(NULL)`.

## Avoid Excessive Logging

As noted in the [API documentation](/docs/c/Foundation/Logging/ "Logging"), logging over Bluetooth can be a power-hungry operation if an end user has the Developer Connection enabled and is currently viewing app logs.

In addition, frequent (multiple times per second) logging can interfere with frequent use of [`AppMessage`](/docs/c/Foundation/AppMessage/ "AppMessage"), as the two mechanisms share the same channel for communication. If an app is logging sent/received AppMessage events or values while doing this sending, it could experience slow or dropped messages. Be sure to disable this logging when frequently sending messages.
