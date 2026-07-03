# Unobstructed Area

Source: https://developer.repebble.com/guides/user-interfaces/unobstructed-area/

The [`UnobstructedArea`](/docs/c/User_Interface/UnobstructedArea/ "UnobstructedArea") API, added in SDK 4.0, allows developers to dynamically adapt their watchface design when an area of the screen is partially obstructed by a system overlay. Currently, the Timeline Quick View feature is the only system overlay.

Developers are not required to adjust their designs to cater for such system overlays, but by using the [`UnobstructedArea`](/docs/c/User_Interface/UnobstructedArea/ "UnobstructedArea") API they can detect changes to the available screen real-estate and then move, scale, or hide their layers to achieve an optimal layout while the screen is partially obscured.

![Unobstructed-watchfaces](/assets/images/guides/user-interfaces/unobstructed-area/01-unobstructed-watchfaces.jpg)

Sample watchfaces with Timeline Quick View overlay

![Obstructed-watchfaces](/assets/images/guides/user-interfaces/unobstructed-area/02-obstructed-watchfaces.jpg)

Potential versions of sample watchfaces using the UnobstructedArea API

### Determining the Unobstructed Bounds

Prior to SDK 4.0, when displaying layers on screen you would calculate the size of the display using [`layer_get_bounds()`](/docs/c/User_Interface/Layers/#layer_get_bounds "layer\_get\_bounds") and then scale and position your layers accordingly. Developers can now calculate the size of a layer, excluding system obstructions, using the new[`layer_get_unobstructed_bounds()`](/docs/c/User_Interface/Layers/#layer_get_unobstructed_bounds "layer\_get\_unobstructed\_bounds").

```
static Layer \*s\_window\_layer;static TextLayer \*s\_text\_layer;static void main\_window\_load(Window \*window) {s\_window\_layer = window\_get\_root\_layer(window);GRect unobstructed\_bounds = layer\_get\_unobstructed\_bounds(s\_window\_layer);s\_text\_layer = text\_layer\_create(GRect(0, unobstructed\_bounds.size.h / 4, unobstructed\_bounds.size.w, 50));}
```

If you still want a fullscreen entities such as a background image, regardless of any obstructions, just combine both techniques as follows:

```
static Layer \*s\_window\_layer;static BitmapLayer \*s\_image\_layer;static TextLayer \*s\_text\_layer;static void main\_window\_load(Window \*window) {s\_window\_layer = window\_get\_root\_layer(window);GRect full\_bounds = layer\_get\_bounds(s\_window\_layer);GRect unobstructed\_bounds = layer\_get\_unobstructed\_bounds(s\_window\_layer);s\_image\_layer = bitmap\_layer\_create(full\_bounds);s\_text\_layer = text\_layer\_create(GRect(0, unobstructed\_bounds.size.h / 4, unobstructed\_bounds.size.w, 50));}
```

The approach outlined above is perfectly fine to use when your watchface is initially launched, but you’re also responsible for handling the obstruction appearing and disappearing while your watchface is running.

### Rendering with LayerUpdateProc

If your application controls its own rendering process using a[`LayerUpdateProc`](/docs/c/User_Interface/Layers/#LayerUpdateProc "LayerUpdateProc") you can just dynamically adjust your rendering each time your layer updates.

In this example, we use [`layer_get_unobstructed_bounds()`](/docs/c/User_Interface/Layers/#layer_get_unobstructed_bounds "layer\_get\_unobstructed\_bounds") instead of[`layer_get_bounds()`](/docs/c/User_Interface/Layers/#layer_get_bounds "layer\_get\_bounds"). The graphics are then positioned or scaled based upon the available screen real-estate, instead of the screen dimensions.

> You must ensure you fill the entire window, not just the unobstructed area, when drawing the screen - failing to do so may cause unexpected graphics to be drawn behind the quick view, during animations.

```
static void hands\_update\_proc(Layer \*layer, GContext \*ctx) {GRect bounds = layer\_get\_unobstructed\_bounds(layer);GPoint center = grect\_center\_point(&bounds);const int16\_t second\_hand\_length = (bounds.size.w / 2);time\_t now = time(NULL);struct tm \*t = localtime(&now);int32\_t second\_angle = TRIG\_MAX\_ANGLE \* t-\>tm\_sec / 60;GPoint second\_hand = {.x = (int16\_t)(sin\_lookup(second\_angle) \* (int32\_t)second\_hand\_length / TRIG\_MAX\_RATIO) + center.x,.y = (int16\_t)(-cos\_lookup(second\_angle) \* (int32\_t)second\_hand\_length / TRIG\_MAX\_RATIO) + center.y,};// second handgraphics\_context\_set\_stroke\_color(ctx, GColorWhite);graphics\_draw\_line(ctx, second\_hand, center);// minute/hour handgraphics\_context\_set\_fill\_color(ctx, GColorWhite);graphics\_context\_set\_stroke\_color(ctx, GColorBlack);gpath\_rotate\_to(s\_minute\_arrow, TRIG\_MAX\_ANGLE \* t-\>tm\_min / 60);gpath\_draw\_filled(ctx, s\_minute\_arrow);gpath\_draw\_outline(ctx, s\_minute\_arrow);gpath\_rotate\_to(s\_hour\_arrow, (TRIG\_MAX\_ANGLE \* (((t-\>tm\_hour % 12) \* 6) +(t-\>tm\_min / 10))) / (12 \* 6));gpath\_draw\_filled(ctx, s\_hour\_arrow);gpath\_draw\_outline(ctx, s\_hour\_arrow);// dot in the middlegraphics\_context\_set\_fill\_color(ctx, GColorBlack);graphics\_fill\_rect(ctx, GRect(bounds.size.w / 2 - 1, bounds.size.h / 2 - 1, 3,3), 0, GCornerNone);}
```

### Using Unobstructed Area Handlers

If you are not overriding the default rendering of a [`Layer`](/docs/c/User_Interface/Layers/#Layer "Layer"), you will need to subscribe to one or more of the [`UnobstructedAreaHandlers`](/docs/c/User_Interface/UnobstructedArea/#UnobstructedAreaHandlers "UnobstructedAreaHandlers") to adjust the sizes and positions of layers.

There are 3 events available using [`UnobstructedAreaHandlers`](/docs/c/User_Interface/UnobstructedArea/#UnobstructedAreaHandlers "UnobstructedAreaHandlers"). These events will notify you when the unobstructed area is: _about to change_,_is currently changing_, or _has finished changing_. You can use these handlers to perform any necessary alterations to your layout.

`.will_change` - an event to inform you that the unobstructed area size is about to change. This provides a [`GRect`](/docs/c/Graphics/Graphics_Types/#GRect "GRect") which lets you know the size of the screen after the change has finished.

`.change` - an event to inform you that the unobstructed area size is currently changing. This event is called several times during the animation of an obstruction appearing or disappearing. [`AnimationProgress`](/docs/c/User_Interface/Animation/#AnimationProgress "AnimationProgress") is provided to let you know the percentage of progress towards completion.

`.did_change` - an event to inform you that the unobstructed area size has finished changing. This is useful for deinitializing or destroying anything created or allocated in the will\_change handler.

These handlers are optional, but at least one must be specified for a valid subscription. In the following example, we subscribe to two of the three available handlers.

> **NOTE** : You must construct the[`UnobstructedAreaHandlers`](/docs/c/User_Interface/UnobstructedArea/#UnobstructedAreaHandlers "UnobstructedAreaHandlers") object _before_ passing it to the[`unobstructed_area_service_subscribe()`](/docs/c/User_Interface/UnobstructedArea/#unobstructed_area_service_subscribe "unobstructed\_area\_service\_subscribe") method.

```
UnobstructedAreaHandlers handlers = {.will\_change = prv\_unobstructed\_will\_change,.did\_change = prv\_unobstructed\_did\_change};unobstructed\_area\_service\_subscribe(handlers, NULL);
```

#### Hiding Layers

In this example, we’re going to hide a [`TextLayer`](/docs/c/User_Interface/Layers/TextLayer/ "TextLayer") containing the current date, while the screen is obstructed.

Just before the Timeline Quick View appears, we’re going to hide the[`TextLayer`](/docs/c/User_Interface/Layers/TextLayer/ "TextLayer") and we’ll show it again after the Timeline Quick View disappears.

```
static Window \*s\_main\_window;static Layer \*s\_window\_layer;static TextLayer \*s\_date\_layer;
```

Subscribe to the `.did_change` and `.will_change` events:

```
static void main\_window\_load(Window \*window) {// Keep a handle on the root layers\_window\_layer = window\_get\_root\_layer(window);// Subscribe to the will\_change and did\_change eventsUnobstructedAreaHandlers handlers = {.will\_change = prv\_unobstructed\_will\_change,.did\_change = prv\_unobstructed\_did\_change};unobstructed\_area\_service\_subscribe(handlers, NULL);}
```

The `will_change` event fires before the size of the unobstructed area changes, so we need to establish whether the screen is already obstructed, or about to become obstructed. If there isn’t a current obstruction, that means the obstruction must be about to appear, so we’ll need to hide our data layer.

```
static void prv\_unobstructed\_will\_change(GRect final\_unobstructed\_screen\_area,void \*context) {// Get the full size of the screenGRect full\_bounds = layer\_get\_bounds(s\_window\_layer);if (!grect\_equal(&full\_bounds, &final\_unobstructed\_screen\_area)) {// Screen is about to become obstructed, hide the datelayer\_set\_hidden(text\_layer\_get\_layer(s\_date\_layer), true);}}
```

The `did_change` event fires after the unobstructed size changes, so we can perform the same check to see whether the screen is already obstructed, or about to become obstructed. If the screen isn’t obstructed when this event fires, then the obstruction must have just cleared and we’ll need to display our date layer again.

```
static void prv\_unobstructed\_did\_change(void \*context) {// Get the full size of the screenGRect full\_bounds = layer\_get\_bounds(s\_window\_layer);// Get the total available screen real-estateGRect bounds = layer\_get\_unobstructed\_bounds(s\_window\_layer);if (grect\_equal(&full\_bounds, &bounds)) {// Screen is no longer obstructed, show the datelayer\_set\_hidden(text\_layer\_get\_layer(s\_date\_layer), false);}}
```

#### Animating Layer Positions

The `.change` event will fire several times while the unobstructed area is changing size. This allows us to use this event to make our layers appear to slide-in or slide-out of their initial positions.

In this example, we’re going to use percentages to position two text layers vertically. One layer at the top of the screen and one layer at the bottom. When the screen is obstructed, these two layers will shift to be closer together. Because we’re using percentages, it doesn’t matter if the unobstructed area is increasing or decreasing, our text layers will always be relatively positioned in the available space.

```
static const uint8\_t s\_offset\_top\_percent = 33;static const uint8\_t s\_offset\_bottom\_percent = 10;
```

A simple helper function to simulate percentage based coordinates:

```
uint8\_t relative\_pixel(int16\_t percent, int16\_t max) {return (max \* percent) / 100;}
```

Subscribe to the change event:

```
static void main\_window\_load(Window \*window) {UnobstructedAreaHandlers handler = {.change = prv\_unobstructed\_change};unobstructed\_area\_service\_subscribe(handler, NULL);}
```

Move the text layer each time the unobstructed area size changes:

```
static void prv\_unobstructed\_change(AnimationProgress progress, void \*context) {// Get the total available screen real-estateGRect bounds = layer\_get\_unobstructed\_bounds(s\_window\_layer);// Get the current position of our top text layerGRect frame = layer\_get\_frame(text\_layer\_get\_layer(s\_top\_text\_layer));// Shift the Y coordinateframe.origin.y = relative\_pixel(s\_offset\_top\_percent, bounds.size.h);// Apply the new locationlayer\_set\_frame(text\_layer\_get\_layer(s\_top\_text\_layer), frame);// Get the current position of our bottom text layerGRect frame2 = layer\_get\_frame(text\_layer\_get\_layer(s\_top\_text\_layer));// Shift the Y coordinateframe2.origin.y = relative\_pixel(s\_offset\_bottom\_percent, bounds.size.h);// Apply the new positionlayer\_set\_frame(text\_layer\_get\_layer(s\_bottom\_text\_layer), frame2);}
```

### Toggling Timeline Quick View

The `pebble` tool which shipped as part of SDK 4.0, allows developers to enable and disable Timeline Quick View, which is incredibly useful for debugging purposes.

![Unobstructed animation](/assets/images/guides/user-interfaces/unobstructed-area/unobstructed-animation.gif)

To enable Timeline Quick View, you can use:

```
$ pebble emu-set-timeline-quick-view on
```

To disable Timeline Quick View, you can use:

```
$ pebble emu-set-timeline-quick-view off
```

### Additional Considerations

If you're scaling or moving layers based on the unobstructed area, you must ensure you fill the entire window, not just the unobstructed area. Failing to do so may cause unexpected graphics to be drawn behind the quick view, during animations.

At present, Timeline Quick View is not currently planned for the Chalk platform.

For design reference, the height of the Timeline Quick View overlay will be_51px_ in total, which includes a 2px border, but this may vary on newer platforms and and the height should always be calculated at runtime.

```
// Calculate the actual height of the Timeline Quick Views\_window\_layer = window\_get\_root\_layer(window);GRect fullscreen = layer\_get\_bounds(s\_window\_layer);GRect unobstructed\_bounds = layer\_get\_unobstructed\_bounds(s\_window\_layer);int16\_t obstruction\_height = fullscreen.size.h - unobstructed\_bounds.size.h;
```
