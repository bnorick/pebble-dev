# Your First Watchface

Source: https://developer.repebble.com/tutorials/watchface-tutorial/part1/

# Your First Watchface

This page contains some instructions that are different if you're using CloudPebble or if you're using the SDK locally on your computer.

Select whether you're using CloudPebble or the SDK below to show the relevant instructions!

[![](/assets/images/sdk/cloud.svg)
#### CloudPebble
](javascript:void();)[![](/assets/images/sdk/sdk-box.svg)
#### SDK
](javascript:void();)

![](/assets/images/sdk/cloud.svg) Showing instructions for CloudPebble. [Not using CloudPebble?](javascript:%20void();)

![](/assets/images/sdk/sdk-box.svg) Showing instructions for the SDK. [Using CloudPebble?](javascript:%20void();)

> The complete source code for this tutorial is[available on GitHub](https://github.com/coredevices/c-watchface-tutorial).

In this tutorial series we will build a fully-featured digital watchface from scratch using Pebble's C API. By the end you will have a watchface with weather support, user configuration, and more. But first, we need to start with the basics.

When we are done with this first part, you should have a working watchface that looks something like this:

#### aplite

#### basalt

#### chalk

#### diorite

#### emery

#### gabbro

 ![](/assets/images/tutorials/watchface-tutorial/part1~aplite.png)

 ![](/assets/images/tutorials/watchface-tutorial/part1~basalt.png)

 ![](/assets/images/tutorials/watchface-tutorial/part1~chalk.png)

 ![](/assets/images/tutorials/watchface-tutorial/part1~diorite.png)

 ![](/assets/images/tutorials/watchface-tutorial/part1~emery.png)

 ![](/assets/images/tutorials/watchface-tutorial/part1~gabbro.png)

> The screenshots above show the watchface on each Pebble platform. **Aplite** is the original Pebble and Pebble Steel, **Basalt** is the Pebble Time, **Chalk** is the Pebble Time Round, **Diorite** is the Pebble 2, **Emery** is the Pebble Time 2, **Flint** is Pebble 2 Duo, and **Gabbro** is the Pebble Round 2.
> 
> Each platform has different screen dimensions and color capabilities, so it is good practice to test your watchface on all of them.
> 
> **Note** : Flint is not pictured because it is basically identical to Diorite, except for some extra features that we won't be using in this tutorial.

## Creating a New Project

Go to [CloudPebble](https://cloudpebble.repebble.com/) and click **Create** to start a new project. Choose **C** as the project type, name it "watchface", and select the **Empty project** template. Then go to **Settings** on the left and set **App Kind** to **Watchface**.

Before we begin, make sure you have the Pebble SDK installed. If you haven't done this yet, head over to the [download page](/sdk.md) to get set up.

Once you are ready, navigate to a directory of your choosing and create a new project:

```
$ pebble new-project --simple watchface
```

The `--simple` flag gives us a clean starting point without any sample code.

Open `package.json` in the project root and set the `watchapp` object to indicate this is a watchface:

```
"watchapp": {"watchface": true}
```

The key difference between a watchface and a watchapp is that watchfaces serve as the default display on the watch. The Up and Down buttons are reserved for the Pebble timeline, so they are not available for custom behavior.

Set an `author` of your choosing, and we are ready to write some code!

## The App Structure

Every Pebble C app follows the same basic structure. Click **Add New** next to **Source Files** in the left sidebar to create a new C file, or open the existing `main.c`. Start with the required include and three core functions:

Every Pebble C app follows the same basic structure. Open `src/c/main.c` and start with the required include and three core functions:

```
#include \<pebble.h\>static void init() {}static void deinit() {}int main(void) {init();app\_event\_loop();deinit();}
```

`main()` is the entry point. It calls `init()` to set things up,`app_event_loop()` to let the watchface wait for system events, and `deinit()`to clean up when the app exits.

## Creating a Window

Every Pebble app needs at least one [`Window`](/docs/c/User_Interface/Window/ "Window"). Declare a static pointer at the top of the file, below `#include`:

```
static Window \*s\_main\_window;
```

> We prefix static variables with `s_` as a naming convention to indicate they are file-scoped.

We also need two handler functions that the system will call when the [`Window`](/docs/c/User_Interface/Window/ "Window")is being loaded and unloaded. Create these above `init()`:

```
static void main\_window\_load(Window \*window) {}static void main\_window\_unload(Window \*window) {}
```

Now fill in `init()` to create the [`Window`](/docs/c/User_Interface/Window/ "Window"), assign the handlers, set a background color, and push it onto the window stack:

```
static void init() {// Create main Window element and assign to pointers\_main\_window = window\_create();// Set the background colorwindow\_set\_background\_color(s\_main\_window, GColorBlack);// Set handlers to manage the elements inside the Windowwindow\_set\_window\_handlers(s\_main\_window, (WindowHandlers) {.load = main\_window\_load,.unload = main\_window\_unload});// Show the Window on the watch, with animated=truewindow\_stack\_push(s\_main\_window, true);}
```

Every `_create()` call must be matched with a `_destroy()` call to free memory. Add this to `deinit()`:

```
static void deinit() {// Destroy Windowwindow\_destroy(s\_main\_window);}
```

If you click the **play** button on the right side of the toolbar now, your project will compile and install on the emulator. You will see a black screen. Not very exciting yet, but it confirms everything is working!

If you run `pebble build && pebble install` now, you will see a black screen. Not very exciting yet, but it confirms everything is working!

## Displaying the Time

To show the time, we will use a [`TextLayer`](/docs/c/User_Interface/Layers/TextLayer/ "TextLayer"). Declare it below the [`Window`](/docs/c/User_Interface/Window/ "Window")pointer:

```
static TextLayer \*s\_time\_layer;
```

Create the [`TextLayer`](/docs/c/User_Interface/Layers/TextLayer/ "TextLayer") inside `main_window_load()`. We use[`PBL_IF_ROUND_ELSE()`](/docs/c/Graphics/Graphics_Types/#PBL_IF_ROUND_ELSE "PBL\_IF\_ROUND\_ELSE") to position the layer differently on round vs rectangular displays:

```
static void main\_window\_load(Window \*window) {// Get information about the WindowLayer \*window\_layer = window\_get\_root\_layer(window);GRect bounds = layer\_get\_bounds(window\_layer);// Create the time TextLayers\_time\_layer = text\_layer\_create(GRect(0, PBL\_IF\_ROUND\_ELSE(58, 52), bounds.size.w, 50));text\_layer\_set\_background\_color(s\_time\_layer, GColorClear);text\_layer\_set\_text\_color(s\_time\_layer, GColorWhite);text\_layer\_set\_font(s\_time\_layer, fonts\_get\_system\_font(FONT\_KEY\_BITHAM\_42\_BOLD));text\_layer\_set\_text\_alignment(s\_time\_layer, GTextAlignmentCenter);// Add it as a child layer to the Window's root layerlayer\_add\_child(window\_layer, text\_layer\_get\_layer(s\_time\_layer));}
```

And destroy it in `main_window_unload()`:

```
static void main\_window\_unload(Window \*window) {text\_layer\_destroy(s\_time\_layer);}
```

The [`TextLayer`](/docs/c/User_Interface/Layers/TextLayer/ "TextLayer") is in place, but it has no text yet. We need the[`TickTimerService`](/docs/c/Foundation/Event_Service/TickTimerService/ "TickTimerService") to get the current time.

## Using the TickTimerService

The [`TickTimerService`](/docs/c/Foundation/Event_Service/TickTimerService/ "TickTimerService") calls a function whenever the time changes. Create a handler above `main_window_load()` matching the required signature:

```
static void tick\_handler(struct tm \*tick\_time, TimeUnits units\_changed) {update\_time();}
```

This calls `update_time()`, which we will create next. The function uses`strftime()` to format the current time into a buffer. The buffer is declared`static` so it persists across calls - the [`TextLayer`](/docs/c/User_Interface/Layers/TextLayer/ "TextLayer") only stores a pointer to the text, not a copy:

```
static void update\_time() {// Get a tm structuretime\_t temp = time(NULL);struct tm \*tick\_time = localtime(&temp);// Write the current hours and minutes into a bufferstatic char s\_time\_buffer[8];strftime(s\_time\_buffer, sizeof(s\_time\_buffer), clock\_is\_24h\_style() ?"%H:%M" : "%I:%M", tick\_time);// Display this time on the TextLayertext\_layer\_set\_text(s\_time\_layer, s\_time\_buffer);}
```

`clock_is_24h_style()` respects the user's preference for 12-hour or 24-hour format.

Register the tick handler and display the initial time in `init()`, after pushing the window:

```
// Make sure the time is displayed from the startupdate\_time();// Register with TickTimerServicetick\_timer\_service\_subscribe(MINUTE\_UNIT, tick\_handler);
```

`MINUTE_UNIT` means we get a callback every minute. You could use `SECOND_UNIT`for a seconds display, but that costs extra battery.

Click the **play** button to compile and install - you should now see the current time!

Build and install - you should now see the current time!

## Adding the Date

Let's add a second [`TextLayer`](/docs/c/User_Interface/Layers/TextLayer/ "TextLayer") for the date. Declare it at the top:

```
static TextLayer \*s\_date\_layer;
```

Create it in `main_window_load()`, after the time layer:

```
// Create the date TextLayers\_date\_layer = text\_layer\_create(GRect(0, PBL\_IF\_ROUND\_ELSE(110, 104), bounds.size.w, 30));text\_layer\_set\_background\_color(s\_date\_layer, GColorClear);text\_layer\_set\_text\_color(s\_date\_layer, GColorWhite);text\_layer\_set\_font(s\_date\_layer, fonts\_get\_system\_font(FONT\_KEY\_GOTHIC\_24\_BOLD));text\_layer\_set\_text\_alignment(s\_date\_layer, GTextAlignmentCenter);// Add to Windowlayer\_add\_child(window\_layer, text\_layer\_get\_layer(s\_date\_layer));
```

Destroy it in `main_window_unload()`:

```
text\_layer\_destroy(s\_date\_layer);
```

Update `update_time()` to also set the date. Add this after the time formatting:

```
// Write the current date into a bufferstatic char s\_date\_buffer[16];strftime(s\_date\_buffer, sizeof(s\_date\_buffer), "%a %b %d", tick\_time);// Display the datetext\_layer\_set\_text(s\_date\_layer, s\_date\_buffer);
```

The format string `"%a %b %d"` produces output like "Mon Jan 01". See the[strftime documentation](http://www.cplusplus.com/reference/ctime/strftime/)for all available format specifiers.

## Conclusion

That is the basic process for creating a Pebble watchface! To recap, we:

1. Created a new Pebble project configured as a watchface.
2. Set up the basic app structure with `init()`, `deinit()`, and `main()`.
3. Created a [`Window`](/docs/c/User_Interface/Window/ "Window") with load/unload handlers.
4. Added a [`TextLayer`](/docs/c/User_Interface/Layers/TextLayer/ "TextLayer") to display the time.
5. Subscribed to the [`TickTimerService`](/docs/c/Foundation/Event_Service/TickTimerService/ "TickTimerService") to keep the time updated.
6. Added a second [`TextLayer`](/docs/c/User_Interface/Layers/TextLayer/ "TextLayer") for the date.

If you have problems with your code, check it against[the source code for this part](https://github.com/coredevices/c-watchface-tutorial/tree/main/part1).

## What's Next?

The design is functional but plain. In the next part we will spice things up by adding a custom font to give the watchface some personality.

[Go to Part 2 →](/tutorials/watchface-tutorial/part2.md)
