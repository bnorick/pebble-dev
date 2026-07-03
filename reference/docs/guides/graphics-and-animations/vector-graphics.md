# Vector Graphics

Source: https://developer.repebble.com/guides/graphics-and-animations/vector-graphics/

This is an overview of drawing vector images using Pebble Draw Command files. See the [_Vector Animations_](/tutorials/advanced/vector-animations.md) tutorial for more information.

## Vector Graphics on Pebble

As opposed to bitmaps which contain data for every pixel to be drawn, a vector file contains only instructions about points contained in the image and how to draw lines connecting them up. Instructions such as fill color, stroke color, and stroke width are also included.

Vector images on Pebble are implemented using the [`Draw Commands`](/docs/c/Graphics/Draw_Commands/ "Draw Commands") API, which allows apps to load and display PDC (Pebble Draw Command) images and sequences that contain sets of these instructions. An example is the weather icon used in weather timeline pins. The benefit of using vector graphics for this icon is that is allows the image to stretch in the familiar manner as it moves between the timeline view and the pin detail view:

![weather](/assets/images/tutorials/advanced/weather.png)

The main benefits of vectors over bitmaps for simple images and icons are:

- Smaller resource size - instructions for joining points are less memory expensive than per-pixel bitmap data.

- Flexible rendering - vector images can be rendered as intended, or manipulated at runtime to move the individual points around. This allows icons to appear more organic and life-like than static PNG images. Scaling and distortion is also made possible.

However, there are also some drawbacks to choosing vector images in certain cases:

- Vector files require more specialized tools to create than bitmaps, and so are harder to produce.

- Complicated vector files may take more time to render than if they were simply drawn per-pixel as a bitmap, depending on the drawing implementation.

## Creating Compatible Files

The file format of vector image files on Pebble is the PDC (Pebble Draw Command) format, which includes all the instructions necessary to allow drawing of vectors. These files are created from compatible SVG (Scalar Vector Graphics) files. Read [_Converting SVG to PDC_](/guides/app-resources/converting-svg-to-pdc.md) for more information.

Pebble Draw Command files can only be used from app resources, and cannot be created at runtime.

## Drawing Vector Graphics

Add the PDC file to the project resources in `package.json` with the 'type' field to `raw`:

```
"media": [{"type": "raw","name": "EXAMPLE\_IMAGE","file": "example\_image.pdc"}]
```

Drawing a Pebble Draw Command image is just as simple as drawing a normal PNG image to a graphics context, requiring only one draw call. First, load the`.pdc` file from resources as shown below.

First, declare a pointer of type [`GDrawCommandImage`](/docs/c/Graphics/Draw_Commands/#GDrawCommandImage "GDrawCommandImage") at the top of the file:

```
static GDrawCommandImage \*s\_command\_image;
```

Create and assign the [`GDrawCommandImage`](/docs/c/Graphics/Draw_Commands/#GDrawCommandImage "GDrawCommandImage") in `init()`, before calling`window_stack_push()`:

```
// Create the object from resource files\_command\_image = gdraw\_command\_image\_create\_with\_resource(RESOURCE\_ID\_EXAMPLE\_IMAGE);
```

Next, define the [`LayerUpdateProc`](/docs/c/User_Interface/Layers/#LayerUpdateProc "LayerUpdateProc") that will be used to draw the PDC image:

```
static void update\_proc(Layer \*layer, GContext \*ctx) {// Set the origin offset from the context for drawing the imageGPoint origin = GPoint(10, 20);// Draw the GDrawCommandImage to the GContextgdraw\_command\_image\_draw(ctx, s\_command\_image, origin);}
```

Next, create a [`Layer`](/docs/c/User_Interface/Layers/#Layer "Layer") to display the image:

```
static Layer \*s\_canvas\_layer;
```

Assign the [`LayerUpdateProc`](/docs/c/User_Interface/Layers/#LayerUpdateProc "LayerUpdateProc") that will do the rendering to the canvas[`Layer`](/docs/c/User_Interface/Layers/#Layer "Layer") and add it to the desired [`Window`](/docs/c/User_Interface/Window/ "Window") during `window_load()`:

```
// Create the canvas Layers\_canvas\_layer = layer\_create(GRect(30, 30, bounds.size.w, bounds.size.h));// Set the LayerUpdateProclayer\_set\_update\_proc(s\_canvas\_layer, update\_proc);// Add to parent Windowlayer\_add\_child(window\_layer, s\_canvas\_layer);
```

Finally, don't forget to free the memory used by the sub-components of the[`Window`](/docs/c/User_Interface/Window/ "Window") in `main_window_unload()`:

```
// Destroy the canvas Layerlayer\_destroy(s\_canvas\_layer);// Destroy the PDC imagegdraw\_command\_image\_destroy(s\_command\_image);
```

When run, the PDC image will be loaded, and rendered in the [`LayerUpdateProc`](/docs/c/User_Interface/Layers/#LayerUpdateProc "LayerUpdateProc"). To put the image into contrast, optionally change the [`Window`](/docs/c/User_Interface/Window/ "Window") background color after `window_create()`:

```
window\_set\_background\_color(s\_main\_window, GColorBlueMoon);
```

The result will look similar to the example shown below.

![weather-image](/assets/images/tutorials/advanced/weather-image.png)
