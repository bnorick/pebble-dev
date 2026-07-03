# Battery Meter and Bluetooth Alerts

Source: https://developer.repebble.com/tutorials/watchface-tutorial/part3/

# Battery Meter and Bluetooth Alerts

This page contains some instructions that are different if you're using CloudPebble or if you're using the SDK locally on your computer.

Select whether you're using CloudPebble or the SDK below to show the relevant instructions!

[![](/assets/images/sdk/cloud.svg)
#### CloudPebble
](javascript:void();)[![](/assets/images/sdk/sdk-box.svg)
#### SDK
](javascript:void();)

![](/assets/images/sdk/cloud.svg) Showing instructions for CloudPebble. [Not using CloudPebble?](javascript:%20void();)

![](/assets/images/sdk/sdk-box.svg) Showing instructions for the SDK. [Using CloudPebble?](javascript:%20void();)

Our watchface tells the time with style, but a great watchface also gives useful information at a glance. In this part we will add two popular features: a battery meter and a Bluetooth disconnect alert.

By the end of this part, your watchface will look something like this:

#### aplite

#### basalt

#### chalk

#### diorite

#### emery

#### gabbro

 ![](/assets/images/tutorials/watchface-tutorial/part3~aplite.png)

 ![](/assets/images/tutorials/watchface-tutorial/part3~basalt.png)

 ![](/assets/images/tutorials/watchface-tutorial/part3~chalk.png)

 ![](/assets/images/tutorials/watchface-tutorial/part3~diorite.png)

 ![](/assets/images/tutorials/watchface-tutorial/part3~emery.png)

 ![](/assets/images/tutorials/watchface-tutorial/part3~gabbro.png)

This section continues from[_Part 2_](/tutorials/watchface-tutorial/part2.md), so be sure to re-use your code or start with that finished project.

## The Battery Meter

### Subscribing to Battery Events

The battery level is obtained using the [`BatteryStateService`](/docs/c/Foundation/Event_Service/BatteryStateService/ "BatteryStateService"). Like the[`TickTimerService`](/docs/c/Foundation/Event_Service/TickTimerService/ "TickTimerService"), it works by calling a function whenever the battery state changes.

Start by declaring a variable to store the current charge level at the top of your file:

```
static Layer \*s\_battery\_layer;static int s\_battery\_level;
```

Create a callback that stores the new level and triggers a redraw:

```
static void battery\_callback(BatteryChargeState state) {// Record the new battery levels\_battery\_level = state.charge\_percent;// Update the meterlayer\_mark\_dirty(s\_battery\_layer);}
```

[`layer_mark_dirty()`](/docs/c/User_Interface/Layers/#layer_mark_dirty "layer\_mark\_dirty") tells the system to redraw the layer at the next opportunity.

Subscribe to battery events in `init()`:

```
// Register for battery level updatesbattery\_state\_service\_subscribe(battery\_callback);// Ensure battery level is displayed from the startbattery\_callback(battery\_state\_service\_peek());
```

[`battery_state_service_peek()`](/docs/c/Foundation/Event_Service/BatteryStateService/#battery_state_service_peek "battery\_state\_service\_peek") returns the current state immediately, so we have a value to display right away.

### Drawing the Battery Bar

For the meter we will use a plain [`Layer`](/docs/c/User_Interface/Layers/#Layer "Layer") with a [`LayerUpdateProc`](/docs/c/User_Interface/Layers/#LayerUpdateProc "LayerUpdateProc") - a callback that handles all the drawing for that layer. This gives us full control over how the bar looks.

Our battery bar will have a white rounded-rectangle border and a filled bar inside that changes color based on the charge level - green when healthy, yellow when getting low, red when critical:

```
static void battery\_update\_proc(Layer \*layer, GContext \*ctx) {GRect bounds = layer\_get\_bounds(layer);// Find the width of the bar (inside the border)int bar\_width = ((s\_battery\_level \* (bounds.size.w - 4)) / 100);// Draw the bordergraphics\_context\_set\_stroke\_color(ctx, GColorWhite);graphics\_draw\_round\_rect(ctx, bounds, 2);// Choose color based on battery levelGColor bar\_color;if (s\_battery\_level \<= 20) {bar\_color = PBL\_IF\_COLOR\_ELSE(GColorRed, GColorWhite);} else if (s\_battery\_level \<= 40) {bar\_color = PBL\_IF\_COLOR\_ELSE(GColorChromeYellow, GColorWhite);} else {bar\_color = PBL\_IF\_COLOR\_ELSE(GColorGreen, GColorWhite);}// Draw the filled bar inside the bordergraphics\_context\_set\_fill\_color(ctx, bar\_color);graphics\_fill\_rect(ctx, GRect(2, 2, bar\_width, bounds.size.h - 4), 1, GCornerNone);}
```

> **Note** : [`PBL_IF_COLOR_ELSE()`](/docs/c/Graphics/Graphics_Types/#PBL_IF_COLOR_ELSE "PBL\_IF\_COLOR\_ELSE") lets us use colors on color-capable platforms (Basalt, Chalk, Emery) while falling back to white on the monochrome Aplite and Diorite.

Create the layer in `main_window_load()` and assign the update proc. We center it horizontally and place it near the top of the screen:

```
// Create battery meter Layer - visible bar near the topint bar\_width = bounds.size.w / 2;int bar\_x = (bounds.size.w - bar\_width) / 2;int bar\_y = PBL\_IF\_ROUND\_ELSE(bounds.size.h / 8, bounds.size.h / 28);s\_battery\_layer = layer\_create(GRect(bar\_x, bar\_y, bar\_width, 8));layer\_set\_update\_proc(s\_battery\_layer, battery\_update\_proc);// Add to Windowlayer\_add\_child(window\_layer, s\_battery\_layer);
```

Clean up in `main_window_unload()`:

```
layer\_destroy(s\_battery\_layer);
```

## Bluetooth Disconnect Alert

### Subscribing to Connection Events

The [`ConnectionService`](/docs/c/Foundation/Event_Service/ConnectionService/ "ConnectionService") notifies us when the Bluetooth connection changes. We will show an icon when disconnected and vibrate to alert the user.

Create a callback:

```
static void bluetooth\_callback(bool connected) {// Show icon if disconnectedlayer\_set\_hidden(bitmap\_layer\_get\_layer(s\_bt\_icon\_layer), connected);if (!connected) {// Issue a vibrating alertvibes\_double\_pulse();}}
```

When `connected` is `true`, the icon is hidden. When `false`, it is shown and the watch vibrates with a double pulse.

Subscribe in `init()`:

```
// Register for Bluetooth connection updatesconnection\_service\_subscribe((ConnectionHandlers) {.pebble\_app\_connection\_handler = bluetooth\_callback});
```

### Adding the Disconnect Icon

We need a small bitmap image to show when disconnected. Here is the icon we will use:

![](/assets/images/tutorials/intermediate/bt-icon.png)

In CloudPebble, click **Add New** next to **Resources** , upload the image, set the **Resource Type** to **Bitmap** , and set the **Identifier** to`IMAGE_BT_ICON`.

Save this image to `resources/images/bt-icon.png` in your project.

Add it to the `media` array in `package.json`:

```
{"type": "bitmap","name": "IMAGE\_BT\_ICON","file": "images/bt-icon.png"}
```

Declare the [`GBitmap`](/docs/c/Graphics/Graphics_Types/#GBitmap "GBitmap") and [`BitmapLayer`](/docs/c/User_Interface/Layers/BitmapLayer/ "BitmapLayer") at the top of your file:

```
static BitmapLayer \*s\_bt\_icon\_layer;static GBitmap \*s\_bt\_icon\_bitmap;
```

Create both in `main_window_load()`:

```
// Create the Bluetooth icon GBitmaps\_bt\_icon\_bitmap = gbitmap\_create\_with\_resource(RESOURCE\_ID\_IMAGE\_BT\_ICON);// Create the BitmapLayer to display the GBitmap - below the battery bar, centeredint bt\_y = bar\_y + 12;s\_bt\_icon\_layer = bitmap\_layer\_create(GRect((bounds.size.w - 30) / 2, bt\_y, 30, 30));bitmap\_layer\_set\_bitmap(s\_bt\_icon\_layer, s\_bt\_icon\_bitmap);bitmap\_layer\_set\_compositing\_mode(s\_bt\_icon\_layer, GCompOpSet);// Add to Windowlayer\_add\_child(window\_get\_root\_layer(window), bitmap\_layer\_get\_layer(s\_bt\_icon\_layer));
```

Show the correct initial state at the end of `main_window_load()`:

```
// Show the correct state of the BT connection from the startbluetooth\_callback(connection\_service\_peek\_pebble\_app\_connection());
```

Clean up in `main_window_unload()`:

```
gbitmap\_destroy(s\_bt\_icon\_bitmap);bitmap\_layer\_destroy(s\_bt\_icon\_layer);
```

## Testing in the Emulator

Click the **play** button to compile and install your watchface in the CloudPebble emulator.

Build and install your watchface as usual:

```
pebble build && pebble install --emulator emery
```

Once the watchface is running, you can test the battery and Bluetooth features without needing a real watch:

### Setting the Battery Level

In the CloudPebble emulator, use the gear menu to adjust the battery level. Try a few different values to see the bar color change.

Use `pebble emu-battery` to change the simulated battery level. Try a few different values to see the bar color change:

```
pebble emu-battery --percent 80
pebble emu-battery --percent 30
pebble emu-battery --percent 10
```

You should see the bar go from green to yellow to red as the level decreases.

### Toggling Bluetooth

In the CloudPebble emulator, use the gear menu to toggle the Bluetooth connection on and off.

Use `pebble emu-bt-connection` to simulate a Bluetooth disconnect and reconnect:

```
pebble emu-bt-connection --connected no
pebble emu-bt-connection --connected yes
```

When you disconnect, the Bluetooth icon should appear and the watch should vibrate. When you reconnect, the icon should disappear.

> **Note** : The emulator might take a few seconds before it realizes the connection has been lost. This is normal. Just wait a moment and the icon will appear.

## Conclusion

In this part we learned how to:

1. Subscribe to the [`BatteryStateService`](/docs/c/Foundation/Event_Service/BatteryStateService/ "BatteryStateService") for charge level updates.
2. Draw custom graphics using a [`Layer`](/docs/c/User_Interface/Layers/#Layer "Layer") with a [`LayerUpdateProc`](/docs/c/User_Interface/Layers/#LayerUpdateProc "LayerUpdateProc").
3. Use color-coded battery levels with [`PBL_IF_COLOR_ELSE()`](/docs/c/Graphics/Graphics_Types/#PBL_IF_COLOR_ELSE "PBL\_IF\_COLOR\_ELSE").
4. Subscribe to the [`ConnectionService`](/docs/c/Foundation/Event_Service/ConnectionService/ "ConnectionService") for Bluetooth events.
5. Show/hide layers and trigger vibration alerts.
6. Test battery and Bluetooth features using the emulator.

Your watchface now shows the battery level and alerts you when the phone disconnects. Check your code against[the source for this part](https://github.com/coredevices/c-watchface-tutorial/tree/main/part3).

## What's Next?

In the next part we will add weather information by fetching data from the Open-Meteo API - our first foray into phone-watch communication.

[Go to Part 4 →](/tutorials/watchface-tutorial/part4.md)
