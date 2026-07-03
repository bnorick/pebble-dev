# Vector Animations

Source: https://developer.repebble.com/tutorials/advanced/vector-animations/

# Vector Animations

**PLATFORM NOTICE**  
 This guide only applies for apps built to run on the Basalt platform (Pebble Time watches).

Some of the best Pebble apps make good use of the [`Animation`](/docs/c/User_Interface/Animation/ "Animation") and the[`Graphics Context`](/docs/c/Graphics/ "Graphics") to create beautiful and eye-catching user interfaces that look better than those created with just the standard [`Layer`](/docs/c/User_Interface/Layers/#Layer "Layer")types.

Taking a good design a step further may involve using the [`Draw Commands`](/docs/c/Graphics/Draw_Commands/ "Draw Commands") API to load vector icons and images, and to animate them on a point-by-point basis at runtime. An additional capability of the [`Draw Commands`](/docs/c/Graphics/Draw_Commands/ "Draw Commands") API is the draw command sequence, allowing multiple frames to be incorporated into a single resource and played out frame by frame.

This tutorial will guide you through the process of using these types of image files in your own projects.

## What Are Vector Images?

As opposed to bitmaps which contain data for every pixel to be drawn, a vector file contains only instructions about points contained in the image and how to draw lines connecting them up. Instructions such as fill color, stroke color, and stroke width are also included.

Vector images on Pebble are implemented using the [`Draw Commands`](/docs/c/Graphics/Draw_Commands/ "Draw Commands") APIs, which load and display PDC (Pebble Draw Command) images and sequences that contain sets of these instructions. An example is the weather icon used in weather timeline pins. The benefit of using vector graphics for this icon is that is allows the image to stretch in the familiar manner as it moves between the timeline view and the pin detail view:

![weather](/assets/images/tutorials/advanced/weather.png)

By including two or more vector images in a single file, an animation can be created to enable fast and detailed animated sequences to be played. Examples can be seen in the Pebble system UI, such as when an action is completed:

![action-completed](/assets/images/tutorials/advanced/action-completed.gif)

The main benefits of vectors over bitmaps for simple images and icons are:

- Smaller resource size - instructions for joining points are less memory expensive than per-pixel bitmap data.

- Flexible rendering - vector images can be rendered as intended, or manipulated at runtime to move the individual points around. This allows icons to appear more organic and life-like than static PNG images. Scaling and distortion is also made possible.

- Longer animations - a side benefit of taking up less space is the ability to make animations longer.

However, there are also some drawbacks to choosing vector images in certain cases:

- Vector files require more specialized tools to create than bitmaps, and so are harder to produce.

- Complicated vector files may take more time to render than if they were simply drawn per-pixel as a bitmap, depending on the drawing implementation.

## Creating Compatible Files

The file format of vector image files on Pebble is the PDC (Pebble Draw Command) format, which includes all the instructions necessary to allow drawing of vectors. These files are created from compatible SVG (Scalar Vector Graphics) files using the[`svg2pdc`](https://github.com/pebble-examples/cards-example/blob/master/tools/svg2pdc.py)tool.

Pebble Draw Command files can only be used from app resources, and cannot be created at runtime.

To convert an SVG file to a PDC image of the same name:

```
$ python svg2pdc.py image.svg
```

To create a PDCS (Pebble Draw Command Sequence) from individual SVG frames, specify the directory containing the frames with the `--sequence` flag when running `svg2pdc`:

```
$ ls frames/1.svg2.svg3.svg4.svg5.svg

$ python svg2pdc.py --sequence frames/
```

In the example above, this will create an output file in the `frames` directory called `frames.pdc` that contains draw command data for the complete animation.

**Limitations**

The `svg2pdc` tool currently supports SVG files that use **only** the following elements: `g`, `layer`, `path`, `rect`, `polyline`, `polygon`, `line`, `circle`.

We recommend using Adobe Illustrator to create compatible SVG icons and images.

For simplicity, compatible image and sequence files will be provided for you to use in your own project.

### PDC icons

Example PDC image files are available for the icons listed in[_App Assets_](/guides/app-resources/app-assets.md). These are ideal for use in many common types of apps, such as notification or weather apps.

[Download PDC icon files](https://developer-assets.getpebble.com/assets/other/pebble-timeline-icons-pdc.zip)

## Getting Started

Begin a new project using `pebble new-project` and create a simple app that pushes a blank [`Window`](/docs/c/User_Interface/Window/ "Window"), such as the example below:

```
#include \<pebble.h\>static Window \*s\_main\_window;static void main\_window\_load(Window \*window) {Layer \*window\_layer = window\_get\_root\_layer(window);GRect bounds = layer\_get\_bounds(window\_layer);}static void main\_window\_unload(Window \*window) {}static void init() {s\_main\_window = window\_create();window\_set\_window\_handlers(s\_main\_window, (WindowHandlers) {.load = main\_window\_load,.unload = main\_window\_unload,});window\_stack\_push(s\_main\_window, true);}static void deinit() {window\_destroy(s\_main\_window);}int main() {init();app\_event\_loop();deinit();}
```

## Drawing a PDC Image

For this tutorial, use the example[`weather_image.pdc`](/assets/other/weather_image.pdc) file provided.

Add the PDC file to your project resources in `package.json` as shown below. Set the 'name' field to `WEATHER_IMAGE`, and the 'type' field to `raw`. The file is assumed to be called `weather_image.pdc`:

```
"media": [{"type": "raw","name": "WEATHER\_IMAGE","file": "weather\_image.pdc"}]
```

Drawing a Pebble Draw Command image is just as simple as drawing a normal PNG image to a graphics context, requiring only one draw call. First, load the`.pdc` file from resources, for example with the `name` defined as`WEATHER_IMAGE`, as shown below.

Declare a pointer of type [`GDrawCommandImage`](/docs/c/Graphics/Draw_Commands/#GDrawCommandImage "GDrawCommandImage") at the top of the file:

```
static GDrawCommandImage \*s\_command\_image;
```

Create and assign the [`GDrawCommandImage`](/docs/c/Graphics/Draw_Commands/#GDrawCommandImage "GDrawCommandImage") in `init()`, before calling`window_stack_push()`:

```
static void init() {/\* ... \*/// Create the object from resource files\_command\_image = gdraw\_command\_image\_create\_with\_resource(RESOURCE\_ID\_WEATHER\_IMAGE);/\* ... \*/}
```

Next, define the [`LayerUpdateProc`](/docs/c/User_Interface/Layers/#LayerUpdateProc "LayerUpdateProc") that will be used to draw the PDC image:

```
static void update\_proc(Layer \*layer, GContext \*ctx) {// Set the origin offset from the context for drawing the imageGPoint origin = GPoint(10, 20);// Draw the GDrawCommandImage to the GContextgdraw\_command\_image\_draw(ctx, s\_command\_image, origin);}
```

Next, create a [`Layer`](/docs/c/User_Interface/Layers/#Layer "Layer") to display the image:

```
static Layer \*s\_canvas\_layer;
```

Next, set the [`LayerUpdateProc`](/docs/c/User_Interface/Layers/#LayerUpdateProc "LayerUpdateProc") that will do the rendering and add it to the desired [`Window`](/docs/c/User_Interface/Window/ "Window"):

```
static void main\_window\_load(Window \*window) {/\* ... \*/// Create the canvas Layers\_canvas\_layer = layer\_create(GRect(30, 30, bounds.size.w, bounds.size.h));// Set the LayerUpdateProclayer\_set\_update\_proc(s\_canvas\_layer, update\_proc);// Add to parent Windowlayer\_add\_child(window\_layer, s\_canvas\_layer);}
```

Finally, don't forget to free the memory used by the [`Window`](/docs/c/User_Interface/Window/ "Window")'s sub-components in `main_window_unload()`:

```
static void main\_window\_unload(Window \*window) {layer\_destroy(s\_canvas\_layer);gdraw\_command\_image\_destroy(s\_command\_image);}
```

When run, the PDC image will be loaded, and rendered in the [`LayerUpdateProc`](/docs/c/User_Interface/Layers/#LayerUpdateProc "LayerUpdateProc"). To put the image into contrast, we will finally change the [`Window`](/docs/c/User_Interface/Window/ "Window") background color after `window_create()`:

```
window\_set\_background\_color(s\_main\_window, GColorBlueMoon);
```

The result will look similar to the example shown below.

![weather-image](/assets/images/tutorials/advanced/weather-image.png)

## Playing a PDC Sequence

The [`GDrawCommandSequence`](/docs/c/Graphics/Draw_Commands/#GDrawCommandSequence "GDrawCommandSequence") API allows developers to use vector graphics as individual frames in a larger animation. Just like [`GDrawCommandImage`](/docs/c/Graphics/Draw_Commands/#GDrawCommandImage "GDrawCommandImage")s, each[`GDrawCommandFrame`](/docs/c/Graphics/Draw_Commands/#GDrawCommandFrame "GDrawCommandFrame") is drawn to a graphics context in a [`LayerUpdateProc`](/docs/c/User_Interface/Layers/#LayerUpdateProc "LayerUpdateProc").

For this tutorial, use the example[`clock_sequence.pdc`](/assets/other/clock_sequence.pdc) file provided.

Begin a new app, with a C file containing the [template](#getting-started) provided above.

Next, add the file as a `raw` resource in the same way as for a PDC image, for example with the `name` field specified in `package.json` as`CLOCK_SEQUENCE`.

```
"media": [{"type": "raw","name": "CLOCK\_SEQUENCE","file": "clock\_sequence.pdc"}]
```

Load the PDCS in your app by first declaring a [`GDrawCommandSequence`](/docs/c/Graphics/Draw_Commands/#GDrawCommandSequence "GDrawCommandSequence") pointer:

```
static GDrawCommandSequence \*s\_command\_seq;
```

Next, initialize the object in `init()` before calling `window_stack_push()`:

```
static void init() {/\* ... \*/// Load the sequences\_command\_seq = gdraw\_command\_sequence\_create\_with\_resource(RESOURCE\_ID\_CLOCK\_SEQUENCE);/\* ... \*/}
```

Get the next frame and draw it in the [`LayerUpdateProc`](/docs/c/User_Interface/Layers/#LayerUpdateProc "LayerUpdateProc"). Then register a timer to draw the next frame:

```
// Milliseconds between frames#define DELTA 13static int s\_index = 0;/\* ... \*/static void next\_frame\_handler(void \*context) {// Draw the next framelayer\_mark\_dirty(s\_canvas\_layer);// Continue the sequenceapp\_timer\_register(DELTA, next\_frame\_handler, NULL);}static void update\_proc(Layer \*layer, GContext \*ctx) {// Get the next frameGDrawCommandFrame \*frame = gdraw\_command\_sequence\_get\_frame\_by\_index(s\_command\_seq, s\_index);// If another frame was found, draw itif (frame) {gdraw\_command\_frame\_draw(ctx, s\_command\_seq, frame, GPoint(0, 30));}// Advance to the next frame, wrapping if neccessaryint num\_frames = gdraw\_command\_sequence\_get\_num\_frames(s\_command\_seq);s\_index++;if (s\_index == num\_frames) {s\_index = 0;}}
```

Next, create a new [`Layer`](/docs/c/User_Interface/Layers/#Layer "Layer") to utilize the [`LayerUpdateProc`](/docs/c/User_Interface/Layers/#LayerUpdateProc "LayerUpdateProc") and add it to the desired [`Window`](/docs/c/User_Interface/Window/ "Window").

Create the `Window` pointer:

```
static Layer \*s\_canvas\_layer;
```

Next, create the [`Layer`](/docs/c/User_Interface/Layers/#Layer "Layer") and assign it to the new pointer. Set its update procedure and add it to the [`Window`](/docs/c/User_Interface/Window/ "Window"):

```
static void main\_window\_load(Window \*window) {// Get Window informationLayer \*window\_layer = window\_get\_root\_layer(window);GRect bounds = layer\_get\_bounds(window\_layer);// Create the canvas Layers\_canvas\_layer = layer\_create(GRect(30, 30, bounds.size.w, bounds.size.h));// Set the LayerUpdateProclayer\_set\_update\_proc(s\_canvas\_layer, update\_proc);// Add to parent Windowlayer\_add\_child(window\_layer, s\_canvas\_layer);}
```

Start the animation loop using a timer at the end of initialization:

```
// Start the animationapp\_timer\_register(DELTA, next\_frame\_handler, NULL);
```

Finally, remember to destroy the [`GDrawCommandSequence`](/docs/c/Graphics/Draw_Commands/#GDrawCommandSequence "GDrawCommandSequence") and [`Layer`](/docs/c/User_Interface/Layers/#Layer "Layer") in`main_window_unload()`:

```
static void main\_window\_unload(Window \*window) {layer\_destroy(s\_canvas\_layer);gdraw\_command\_sequence\_destroy(s\_command\_seq);}
```

When run, the animation will be played by the timer at a framerate dictated by`DELTA`, looking similar to the example shown below:

![pdcs-example](/assets/images/tutorials/advanced/pdcs-example.gif)

## What's Next?

You have now learned how to add vector images and animations to your apps. Complete examples for these APIs are available under the `pebble-examples`GitHub organization:

- [`pdc-image`](https://github.com/pebble-examples/pdc-image) - Example implementation of a Pebble Draw Command Image.

- [`pdc-sequence`](https://github.com/pebble-examples/pdc-sequence) - Example implementation of a Pebble Draw Command Sequence animated icon.

More advanced tutorials will be added here in the future, so keep checking back!
