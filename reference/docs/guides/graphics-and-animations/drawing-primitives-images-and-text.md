# Drawing Primitives, Images and Text

Source: https://developer.repebble.com/guides/graphics-and-animations/drawing-primitives-images-and-text/

While [`Layer`](/docs/c/User_Interface/Layers/#Layer "Layer") types such as [`TextLayer`](/docs/c/User_Interface/Layers/TextLayer/ "TextLayer") and [`BitmapLayer`](/docs/c/User_Interface/Layers/BitmapLayer/ "BitmapLayer") allow easy rendering of text and bitmaps, more precise drawing can be achieved through the use of the [`Graphics Context`](/docs/c/Graphics/Graphics_Context/ "Graphics Context") APIs. Custom drawing of primitive shapes such as line, rectangles, and circles is also supported. Clever use of these functions can remove the need to pre-prepare bitmap images for many UI elements and icons.

## Obtaining a Drawing Context

All custom drawing requires a [`GContext`](/docs/c/Graphics/Graphics_Types/#GContext "GContext") instance. These cannot be created, and are only available inside a [`LayerUpdateProc`](/docs/c/User_Interface/Layers/#LayerUpdateProc "LayerUpdateProc"). This update procedure is simply a function that is called when a [`Layer`](/docs/c/User_Interface/Layers/#Layer "Layer") is to be rendered, and is defined by the developer as opposed to the system. For example, a[`BitmapLayer`](/docs/c/User_Interface/Layers/BitmapLayer/ "BitmapLayer") is simply a [`Layer`](/docs/c/User_Interface/Layers/#Layer "Layer") with a [`LayerUpdateProc`](/docs/c/User_Interface/Layers/#LayerUpdateProc "LayerUpdateProc") abstracted away for convenience by the SDK.

First, create the [`Layer`](/docs/c/User_Interface/Layers/#Layer "Layer") that will have a custom drawing procedure:

```
static Layer \*s\_canvas\_layer;
```

Allocate the [`Layer`](/docs/c/User_Interface/Layers/#Layer "Layer") during [`Window`](/docs/c/User_Interface/Window/ "Window") creation:

```
GRect bounds = layer\_get\_bounds(window\_get\_root\_layer(window));// Create canvas layers\_canvas\_layer = layer\_create(bounds);
```

Next, define the [`LayerUpdateProc`](/docs/c/User_Interface/Layers/#LayerUpdateProc "LayerUpdateProc") according to the function specification:

```
static void canvas\_update\_proc(Layer \*layer, GContext \*ctx) {// Custom drawing happens here!}
```

Assign this procedure to the canvas layer and add it to the [`Window`](/docs/c/User_Interface/Window/ "Window") to make it visible:

```
// Assign the custom drawing procedurelayer\_set\_update\_proc(s\_canvas\_layer, canvas\_update\_proc);// Add to Windowlayer\_add\_child(window\_get\_root\_layer(window), s\_canvas\_layer);
```

From now on, every time the [`Layer`](/docs/c/User_Interface/Layers/#Layer "Layer") needs to be redrawn (for example, if other layer geometry changes), the [`LayerUpdateProc`](/docs/c/User_Interface/Layers/#LayerUpdateProc "LayerUpdateProc") will be called to allow the developer to draw it. It can also be explicitly marked for redrawing at the next opportunity:

```
// Redraw this as soon as possiblelayer\_mark\_dirty(s\_canvas\_layer);
```

## Drawing Primitive Shapes

The [`Graphics Context`](/docs/c/Graphics/Graphics_Context/ "Graphics Context") API allows drawing and filling of lines, rectangles, circles, and arbitrary paths. For each of these, the colors of the output can be set using the appropriate function:

```
// Set the line colorgraphics\_context\_set\_stroke\_color(ctx, GColorRed);// Set the fill colorgraphics\_context\_set\_fill\_color(ctx, GColorBlue);
```

In addition, the stroke width and antialiasing mode can also be changed:

```
// Set the stroke width (must be an odd integer value)graphics\_context\_set\_stroke\_width(ctx, 5);// Disable antialiasing (enabled by default where available)graphics\_context\_set\_antialiased(ctx, false);
```

### Lines

Drawing a simple line requires only the start and end positions, expressed as[`GPoint`](/docs/c/Graphics/Graphics_Types/#GPoint "GPoint") values:

```
GPoint start = GPoint(10, 10);GPoint end = GPoint(40, 60);// Draw a linegraphics\_draw\_line(ctx, start, end);
```

### Rectangles

Drawing a rectangle requires a bounding [`GRect`](/docs/c/Graphics/Graphics_Types/#GRect "GRect"), as well as other parameters if it is to be filled:

```
GRect rect\_bounds = GRect(10, 10, 40, 60);// Draw a rectanglegraphics\_draw\_rect(ctx, rect\_bounds);// Fill a rectangle with rounded cornersint corner\_radius = 10;graphics\_fill\_rect(ctx, rect\_bounds, corner\_radius, GCornersAll);
```

It is also possible to draw a rounded unfilled rectangle:

```
// Draw outline of a rounded rectanglegraphics\_draw\_round\_rect(ctx, rect\_bounds, corner\_radius);
```

### Circles

Drawing a circle requries its center [`GPoint`](/docs/c/Graphics/Graphics_Types/#GPoint "GPoint") and radius:

```
GPoint center = GPoint(25, 25);uint16\_t radius = 50;// Draw the outline of a circlegraphics\_draw\_circle(ctx, center, radius);// Fill a circlegraphics\_fill\_circle(ctx, center, radius);
```

In addition, it is possble to draw and fill arcs. In these cases, the[`GOvalScaleMode`](/docs/c/Graphics/Drawing_Primitives/#GOvalScaleMode "GOvalScaleMode") determines how the shape is adjusted to fill the rectangle, and the cartesian angle values are transformed to preserve accuracy:

```
int32\_t angle\_start = DEG\_TO\_TRIGANGLE(0);int32\_t angle\_end = DEG\_TO\_TRIGANGLE(45);// Draw an arcgraphics\_draw\_arc(ctx, rect\_bounds, GOvalScaleModeFitCircle, angle\_start, angle\_end);
```

Lastly, a filled circle with a sector removed can also be drawn in a similar manner. The value of `inset_thickness` determines the inner inset size that is removed from the full circle:

```
uint16\_t inset\_thickness = 10; // Fill a radial section of a circlegraphics\_fill\_radial(ctx, rect\_bounds, GOvalScaleModeFitCircle, inset\_thickness,angle\_start, angle\_end);
```

For more guidance on using round elements in apps, watch the presentation given at the 2015 Developer Retreat on [developing for Pebble Time Round](https://www.youtube.com/watch?v=3a1V4n9HDvY).

## Bitmaps

Manually drawing [`GBitmap`](/docs/c/Graphics/Graphics_Types/#GBitmap "GBitmap") images with the [`Graphics Context`](/docs/c/Graphics/Graphics_Context/ "Graphics Context") API is a simple task, and has much in common with the alternative approach of using a[`BitmapLayer`](/docs/c/User_Interface/Layers/BitmapLayer/ "BitmapLayer") (which provides additional convenience funcionality).

The first step is to load the image data from resources (read [_Images_](/guides/app-resources/images.md) to learn how to include images in a Pebble project):

```
static GBitmap \*s\_bitmap;
```

```
// Load the image datas\_bitmap = gbitmap\_create\_with\_resource(RESOURCE\_ID\_EXAMPLE\_IMAGE);
```

When the appropriate [`LayerUpdateProc`](/docs/c/User_Interface/Layers/#LayerUpdateProc "LayerUpdateProc") is called, draw the image inside the desired rectangle:

> Note: Unlike [`BitmapLayer`](/docs/c/User_Interface/Layers/BitmapLayer/ "BitmapLayer"), the image will be drawn relative to the[`Layer`](/docs/c/User_Interface/Layers/#Layer "Layer")'s origin, and not centered.

```
// Get the bounds of the imageGRect bitmap\_bounds = gbitmap\_get\_bounds(s\_bitmap);// Set the compositing mode (GCompOpSet is required for transparency)graphics\_context\_set\_compositing\_mode(ctx, GCompOpSet);// Draw the imagegraphics\_draw\_bitmap\_in\_rect(ctx, s\_bitmap, bitmap\_bounds);
```

Once the image is no longer needed (i.e.: the app is exiting), free the data:

```
// Destroy the image datagbitmap\_destroy(s\_bitmap);
```

## Drawing Text

Similar to the [`TextLayer`](/docs/c/User_Interface/Layers/TextLayer/ "TextLayer") UI component, a [`LayerUpdateProc`](/docs/c/User_Interface/Layers/#LayerUpdateProc "LayerUpdateProc") can also be used to draw text. Advantages can include being able to draw in multiple fonts with only one [`Layer`](/docs/c/User_Interface/Layers/#Layer "Layer") and combining text with other drawing operations.

The first operation to perform inside the [`LayerUpdateProc`](/docs/c/User_Interface/Layers/#LayerUpdateProc "LayerUpdateProc") is to get or load the font to be used for drawing and set the text's color:

```
// Load the fontGFont font = fonts\_get\_system\_font(FONT\_KEY\_GOTHIC\_24\_BOLD);// Set the colorgraphics\_context\_set\_text\_color(ctx, GColorBlack);
```

Next, determine the bounds that will guide the text's position and overflow behavior. This can either be the size of the [`Layer`](/docs/c/User_Interface/Layers/#Layer "Layer"), or a more precise bounds of the text itself. This information can be useful for drawing multiple text items after one another with automatic spacing.

```
char \*text = "Example test string for the Developer Website guide!";// Determine a reduced bounding boxGRect layer\_bounds = layer\_get\_bounds(layer);GRect bounds = GRect(layer\_bounds.origin.x, layer\_bounds.origin.y,layer\_bounds.size.w / 2, layer\_bounds.size.h);// Calculate the size of the text to be drawn, with restricted spaceGSize text\_size = graphics\_text\_layout\_get\_content\_size(text, font, bounds,GTextOverflowModeWordWrap, GTextAlignmentCenter);
```

Finally, the text can be drawn into the appropriate bounding rectangle:

```
// Draw the textgraphics\_draw\_text(ctx, text, font, bounds, GTextOverflowModeWordWrap, GTextAlignmentCenter, NULL);
```
