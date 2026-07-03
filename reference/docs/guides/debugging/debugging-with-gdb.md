# Debugging with GDB

Source: https://developer.repebble.com/guides/debugging/debugging-with-gdb/

As of SDK 3.10 (and [Pebble Tool](/guides/tools-and-resources/pebble-tool.md) 4.2), developers can use the powerful [GDB](https://www.gnu.org/software/gdb/)debugging tool to find and fix errors in Pebble apps while they are running in an emulator. GDB allows the user to observe the state of the app at any point in time, including the value of global and local variables, as well as current function parameters and a backtrace. Strategically placing breakpoints and observing these values can quickly reveal the source of a bug.

**Notice**  

GDB cannot be used to debug an app running on a real watch.

## Starting GDB

To begin using GDB, start an emulator and install an app:

```
$ pebble install --emulator basalt
```

Once the app is installed, begin using GDB:

```
$ pebble gdb --emulator basalt
```

Once the `(gdb)` prompt appears, the app is paused by GDB for observation. To resume execution, use the `continue` (or `c`) command. Similarly, the app can be paused for debugging by pressing `control + c`.

```
(gdb) c
Continuing.
```

A short list of useful commands (many more are available) can be also be obtained from the `pebble` tool. Read the [_Emulator Interaction_](/guides/tools-and-resources/pebble-tool.md#gdb) section of the [_Command Line Tool_](/guides/tools-and-resources/pebble-tool.md) guide for more details on this list.

```
$ pebble gdb --help
```

## Observing App State

To see the value of variables and parameters at any point, set a breakpoint by using the `break` (or `b`) command and specifying either a function name, or file name with a line number. For example, the snippet below shows a typical[`TickHandler`](/docs/c/Foundation/Event_Service/TickTimerService/#TickHandler "TickHandler") implementation with line numbers in comments:

```
/\* 58 \*/static void tick\_handler(struct tm \*tick\_time, TimeUnits changed) {/\* 59 \*/int hours = tick\_time-\>tm\_hour;/\* 60 \*/int mins = tick\_time-\>tm\_min;/\* 61 \*//\* 62 \*/if(hours \< 10) {/\* 63 \*//\* other code \*//\* 64 \*/}/\* 65 \*/}
```

To observe the values of `hours` and `mins`, a breakpoint is set in this file at line 61:

```
(gdb) b main.c:61
Breakpoint 2 at 0x200204d6: file ../src/main.c, line 61.
```

> Use `info break` to see a list of all breakpoints currently registered. Each can be deleted with `delete n`, where `n` is the breakpoint number.

With this breakpoint set, use the `c` command to let the app continue until it encounters the breakpoint:

```
$ c
Continuing.
```

When execution arrives at the breakpoint, the next line will be displayed along with the state of the function's parameters:

```
Breakpoint 2, tick_handler (tick_time=0x20018770, units_changed=(SECOND_UNIT | MINUTE_UNIT))
    at ../src/main.c:62
62 if(hours < 10) {
```

The value of `hours` and `mins` can be found using the `info locals` command:

```
(gdb) info locals
hours = 13
mins = 23
```

GDB can be further used here to view the state of variables using the `p`command, such as other parts of the `tm` object beyond those being used to assign values to `hours` and `mins`. For example, the day of the month:

```
(gdb) p tick_time->tm_mday
$2 = 14
```

A backtrace can be generated that describes the series of function calls that got the app to the breakpoint using the `bt` command:

```
(gdb) bt
#0 segment_logic (this=0x200218a0) at ../src/drawable/segment.c:18
#1 0x2002033c in digit_logic (this=0x20021858) at ../src/drawable/digit.c:141
#2 0x200204c4 in pge_logic () at ../src/main.c:29
#3 0x2002101a in draw_frame_update_proc (layer=<optimized out>, ctx=<optimized out>)
    at ../src/pge/pge.c:190
#4 0x0802627c in ?? ()
#5 0x0805ecaa in ?? ()
#6 0x0801e1a6 in ?? ()
#7 0x0801e24c in app_event_loop ()
#8 0x2002108a in main () at ../src/pge/pge.c:34
#9 0x080079de in ?? ()
#10 0x00000000 in ?? ()
```

> Lines that include '??' denote a function call in the firmware. Building the app with `pebble build --debug` will disable some optimizations and can produce more readable output from GDB. However, this can increase code size which may break apps that are pushing the heap space limit.

## Fixing a Crash

When an app is paused for debugging, the developer can manually advance each statement and precisely follow the path taken through the code and observe how the state of each variable changes over time. This is very useful for tracking down bugs caused by unusual input to functions that do not adequately check them. For example, a `NULL` pointer.

The app code below demonstrates a common cause of an app crash, caused by a misunderstanding of how the [`Window`](/docs/c/User_Interface/Window/ "Window") stack works. The [`TextLayer`](/docs/c/User_Interface/Layers/TextLayer/ "TextLayer") is created in the `.load` handler, but this is not called until the [`Window`](/docs/c/User_Interface/Window/ "Window") is pushed onto the stack. The attempt to set the time to the [`TextLayer`](/docs/c/User_Interface/Layers/TextLayer/ "TextLayer") by calling`update_time()` before it is displayed will cause the app to crash.

```
#include \<pebble.h\>static Window \*s\_window;static TextLayer \*s\_time\_layer;static void window\_load(Window \*window) {Layer \*window\_layer = window\_get\_root\_layer(window);GRect bounds = layer\_get\_bounds(window\_layer);s\_time\_layer = text\_layer\_create(bounds);text\_layer\_set\_text(s\_time\_layer, "00:00");text\_layer\_set\_text\_alignment(s\_time\_layer, GTextAlignmentCenter);layer\_add\_child(window\_layer, text\_layer\_get\_layer(s\_time\_layer));}static void update\_time() {time\_t now = time(NULL);struct tm \*tick\_time = localtime(&now);static char s\_buffer[8];strftime(s\_buffer, sizeof(s\_buffer), "%H:%M", tick\_time);text\_layer\_set\_text(s\_time\_layer, s\_buffer);}static void init() {s\_window = window\_create();window\_set\_window\_handlers(s\_window, (WindowHandlers) {.load = window\_load});update\_time();window\_stack\_push(s\_window, true);}static void deinit() {window\_destroy(s\_window);}int main() {init();app\_event\_loop();deinit();}
```

Supposing the cause of this crash was not obvious from the order of execution, GDB can be used to identify the cause of the crash with ease. It is known that the app crashes on launch, so the first breakpoint is placed at the beginning of`init()`. After continuing execution, the app will pause at this location:

```
(gdb) b init
Breakpoint 2 at 0x2002010c: file ../src/main.c, line 26.
(gdb) c
Continuing.

Breakpoint 2, main () at ../src/main.c:41
41 init();
```

Using the `step` command (or Enter key), the developer can step through all the statements that occur during app initialization until the crash is found (and the `app_crashed` breakpoint is encountered. Alternatively, `bt full` can be used after the crash occurs to inspect the local variables at the time of the crash:

```
(gdb) c
Continuing.

Breakpoint 1, 0x0804af6c in app_crashed ()
(gdb) bt full
#0 0x0804af6c in app_crashed ()
No symbol table info available.
#1 0x0800bfe2 in ?? ()
No symbol table info available.
#2 0x0800c078 in ?? ()
No symbol table info available.
#3 0x0804c306 in ?? ()
No symbol table info available.
#4 0x080104f0 in ?? ()
No symbol table info available.
#5 0x0804c5c0 in ?? ()
No symbol table info available.
#6 0x0805e6ea in text_layer_set_text ()
No symbol table info available.
#7 0x20020168 in update_time () at ../src/main.c:22
        now = 2076
        tick_time = <optimized out>
        s_buffer = "10:38\000\000"
#8 init () at ../src/main.c:31
No locals.
#9 main () at ../src/main.c:41
No locals.
#10 0x080079de in ?? ()
No symbol table info available.
#11 0x00000000 in ?? ()
No symbol table info available.
```

The last statement to be executed before the crash is a call to`text_layer_set_text()`, which implies that one of its input variables was bad. It is easy to determine which by printing local variable values with the `p`command:

```
Breakpoint 4, update_time () at ../src/main.c:22
22 text_layer_set_text(s_time_layer, s_buffer);
(gdb) p s_time_layer
$1 = (TextLayer *) 0x0 <__pbl_app_info>
```

In this case, GDB displays `0x0` (`NULL`) for the value of `s_time_layer`, which shows it has not yet been allocated, and so will cause `text_layer_set_text()`to crash. And thus, the source of the crash has been methodically identified. A simple fix here is to swap `update_time()` and [`window_stack_push()`](/docs/c/User_Interface/Window_Stack/#window_stack_push "window\_stack\_push") around so that `init()` now becomes:

```
static void init() {// Create a Windows\_window = window\_create();window\_set\_window\_handlers(s\_window, (WindowHandlers) {.load = window\_load});// Display the Windowwindow\_stack\_push(s\_window, true);// Set the timeupdate\_time();}
```

In this new version of the code the [`Window`](/docs/c/User_Interface/Window/ "Window") will be pushed onto the stack, calling its `.load` handler in the process, and the [`TextLayer`](/docs/c/User_Interface/Layers/TextLayer/ "TextLayer") will be allocated and available for use once execution subsequently reaches`update_time()`.
