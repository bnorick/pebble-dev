# Timeline Peek

Source: https://developer.repebble.com/tutorials/watchface-tutorial/part5/

# Timeline Peek

This page contains some instructions that are different if you're using CloudPebble or if you're using the SDK locally on your computer.

Select whether you're using CloudPebble or the SDK below to show the relevant instructions!

[![](/assets/images/sdk/cloud.svg)
#### CloudPebble
](javascript:void();)[![](/assets/images/sdk/sdk-box.svg)
#### SDK
](javascript:void();)

![](/assets/images/sdk/cloud.svg) Showing instructions for CloudPebble. [Not using CloudPebble?](javascript:%20void();)

![](/assets/images/sdk/sdk-box.svg) Showing instructions for the SDK. [Using CloudPebble?](javascript:%20void();)

Pebble's Timeline Quick View can appear at the bottom of the screen to show upcoming events. When it does, it covers part of your watchface. In this part we will use the [`UnobstructedArea`](/docs/c/User_Interface/UnobstructedArea/ "UnobstructedArea") API to gracefully adapt our layout - repositioning the time, date, and weather to fit in the remaining space.

Here is what the transition looks like:

#### basalt

#### diorite

#### emery

 ![](/assets/images/tutorials/watchface-tutorial/part5~basalt.gif)

 ![](/assets/images/tutorials/watchface-tutorial/part5~diorite.gif)

 ![](/assets/images/tutorials/watchface-tutorial/part5~emery.gif)

This section continues from[_Part 4_](/tutorials/watchface-tutorial/part4.md), so be sure to re-use your code or start with that finished project.

## How Timeline Quick View Works

Timeline Quick View is a system overlay that obstructs the bottom ~51 pixels of the screen (including a 2px border). Your watchface is not required to handle this, but with the [`UnobstructedArea`](/docs/c/User_Interface/UnobstructedArea/ "UnobstructedArea") API you can detect the change and rearrange your layers for a better experience.

> **Note** : Timeline Quick View is not currently supported for the Round platforms (chalk and gabbro), but writing compatible code ensures your watchface handles it gracefully on all platforms.

## Getting Unobstructed Bounds

Prior to SDK 4.0, you would use [`layer_get_bounds()`](/docs/c/User_Interface/Layers/#layer_get_bounds "layer\_get\_bounds") to get the full screen size. The [`UnobstructedArea`](/docs/c/User_Interface/UnobstructedArea/ "UnobstructedArea") API adds[`layer_get_unobstructed_bounds()`](/docs/c/User_Interface/Layers/#layer_get_unobstructed_bounds "layer\_get\_unobstructed\_bounds"), which returns only the area not covered by a system overlay:

```
GRect full\_bounds = layer\_get\_bounds(s\_window\_layer);GRect unobstructed\_bounds = layer\_get\_unobstructed\_bounds(s\_window\_layer);
```

If there is no overlay, both return the same rectangle.

## Keeping a Reference to the Window Layer

We need access to the root layer in our handler function, so store it in a file-level variable:

```
static Layer \*s\_window\_layer;
```

Set it at the start of `main_window_load()`:

```
s\_window\_layer = window\_get\_root\_layer(window);GRect bounds = layer\_get\_bounds(s\_window\_layer);
```

## Subscribing to Unobstructed Area Events

The API provides three event handlers:

- `.will_change` - fires before the obstruction appears or disappears
- `.change` - fires repeatedly during the animation
- `.did_change` - fires after the animation completes

We will use all three to demonstrate the full lifecycle. Subscribe at the end of `main_window_load()`:

```
UnobstructedAreaHandlers handlers = {.will\_change = prv\_unobstructed\_will\_change,.change = prv\_unobstructed\_change,.did\_change = prv\_unobstructed\_did\_change};unobstructed\_area\_service\_subscribe(handlers, NULL);
```

> **Important** : Construct the [`UnobstructedAreaHandlers`](/docs/c/User_Interface/UnobstructedArea/#UnobstructedAreaHandlers "UnobstructedAreaHandlers") struct before passing it to [`unobstructed_area_service_subscribe()`](/docs/c/User_Interface/UnobstructedArea/#unobstructed_area_service_subscribe "unobstructed\_area\_service\_subscribe").

## Implementing the Handlers

We use three handlers to split responsibilities cleanly:

### Before the animation - `.will_change`

This fires once before the overlay starts moving. We hide the Bluetooth disconnect icon during the transition so it does not overlap with repositioning layers:

```
static void prv\_unobstructed\_will\_change(GRect final\_unobstructed\_screen\_area,void \*context) {// Hide BT icon during the transition to reduce clutterlayer\_set\_hidden(bitmap\_layer\_get\_layer(s\_bt\_icon\_layer), true);}
```

Note the different signature - `.will_change` receives the _final_ unobstructed area as a [`GRect`](/docs/c/Graphics/Graphics_Types/#GRect "GRect"), so you could use it to prepare for the target layout.

### During the animation - `.change`

This fires repeatedly as the overlay slides in or out. We recalculate all positions from the current unobstructed bounds so the layers animate smoothly:

```
static void prv\_unobstructed\_change(AnimationProgress progress, void \*context) {GRect bounds = layer\_get\_unobstructed\_bounds(s\_window\_layer);// Reposition time, date, and weather to fit in the available spaceint date\_height = 30;int block\_height = 56 + date\_height;int time\_y = (bounds.size.h / 2) - (block\_height / 2) - 10;int date\_y = time\_y + 56;int weather\_y = bounds.size.h - PBL\_IF\_ROUND\_ELSE(40, 30);GRect time\_frame = layer\_get\_frame(text\_layer\_get\_layer(s\_time\_layer));time\_frame.origin.y = time\_y;layer\_set\_frame(text\_layer\_get\_layer(s\_time\_layer), time\_frame);GRect date\_frame = layer\_get\_frame(text\_layer\_get\_layer(s\_date\_layer));date\_frame.origin.y = date\_y;layer\_set\_frame(text\_layer\_get\_layer(s\_date\_layer), date\_frame);GRect weather\_frame = layer\_get\_frame(text\_layer\_get\_layer(s\_weather\_layer));weather\_frame.origin.y = weather\_y;layer\_set\_frame(text\_layer\_get\_layer(s\_weather\_layer), weather\_frame);}
```

Since we use the same `(bounds.size.h / 2) - (block_height / 2) - 10` formula as in `main_window_load()`, the time+date block stays centered in the available space - as the unobstructed bounds shrink, so does the offset, and all layers naturally slide together.

### After the animation - `.did_change`

This fires once after the overlay finishes moving. If the screen is still obstructed we keep the Bluetooth icon hidden - there is not enough room for it. If the screen is back to full size we restore the icon based on the actual connection state:

```
static void prv\_unobstructed\_did\_change(void \*context) {GRect full\_bounds = layer\_get\_bounds(s\_window\_layer);GRect bounds = layer\_get\_unobstructed\_bounds(s\_window\_layer);bool obstructed = !grect\_equal(&full\_bounds, &bounds);// Keep BT icon hidden when obstructed, otherwise restore based on connectionif (obstructed) {layer\_set\_hidden(bitmap\_layer\_get\_layer(s\_bt\_icon\_layer), true);} else {layer\_set\_hidden(bitmap\_layer\_get\_layer(s\_bt\_icon\_layer),connection\_service\_peek\_pebble\_app\_connection());}}
```

Notice that each handler has a different signature - this is a common pattern in the Pebble SDK.

### Handling Quick View on startup

Timeline Quick View may already be active when the watchface starts. Since the handlers only fire during transitions, we need to apply the correct layout immediately. Call the `.change` and `.did_change` handlers manually before subscribing, replacing the old `bluetooth_callback` call:

```
// Apply correct layout in case Quick View is already activeprv\_unobstructed\_change(0, NULL);prv\_unobstructed\_did\_change(NULL);
```

This repositions the layers and sets the BT icon visibility based on the current obstruction state, so the watchface looks correct from the first frame.

### How it all fits together

As the overlay slides in, the unobstructed bounds shrink, and all three text layers slide up together. The Bluetooth icon hides during the transition and stays hidden while the screen is obstructed. When the overlay goes away, the icon reappears if the phone is disconnected. Everything stays on screen - nothing is hidden, just repositioned.

## Testing Timeline Quick View

You can toggle Timeline Quick View using the emulator controls in CloudPebble.

You can toggle Timeline Quick View in the emulator:

```
$ pebble emu-set-timeline-quick-view on$ pebble emu-set-timeline-quick-view off
```

When enabled, you should see the time, date, and weather squeeze together into the remaining space. The Bluetooth icon hides during the transition and reappears based on connection state once it finishes. When disabled, everything returns to its original position.

## Conclusion

In this part we learned how to:

1. Use [`layer_get_unobstructed_bounds()`](/docs/c/User_Interface/Layers/#layer_get_unobstructed_bounds "layer\_get\_unobstructed\_bounds") to find available screen space.
2. Subscribe to all three [`UnobstructedAreaHandlers`](/docs/c/User_Interface/UnobstructedArea/#UnobstructedAreaHandlers "UnobstructedAreaHandlers") callbacks.
3. Use `.will_change` to prepare, `.change` to animate, and `.did_change` to finalize.
4. Reposition layers dynamically to fit in the unobstructed area.

Your watchface now adapts gracefully to Timeline Quick View. Check your code against[the source for this part](https://github.com/coredevices/c-watchface-tutorial/tree/main/part5).

## What's Next?

In the next part we will add a settings page with Clay - letting users pick colors, toggle the date, and choose temperature units.

[Go to Part 6 →](/tutorials/watchface-tutorial/part6.md)
