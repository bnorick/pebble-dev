# Round App UI

Source: https://developer.repebble.com/guides/user-interfaces/round-app-ui/

**PLATFORM NOTICE**  
 This guide only applies for apps built to run on the Chalk platform (Pebble Time Round watches).

> This guide is about creating round apps in code. For advice on designing a round app, read [_Round App Design_](/guides/design-and-interaction/in-the-round.md).

With the addition of Pebble Time Round (the Chalk platform) to the Pebble family, developers face a new challenge - circular apps! With this display shape, traditional layouts will not display properly due to the obscuring of the corners. Another potential issue is the increased display resolution. Any UI elements that were not previously centered correctly (or drawn with hardcoded coordinates) will also display incorrectly.

However, the Pebble SDK provides additions and functionality to help developers cope with this way of thinking. In many cases, a round display can be an aesthetic advantage. An example of this is the traditional circular dial watchface, which has been emulated on Pebble many times, but also wastes corner space. With a round display, these watchfaces can look better than ever.

![time-dots](/assets/images/guides/pebble-apps/display-animations/time-dots.png)

## Detecting Display Shape

The first step for any app wishing to correctly support both display shapes is to use the available compiler directives to conditionally create the UI. This can be done as shown below:

```
#if defined(PBL\_RECT)printf("This code is run on a rectangular display!");/\* Rectangular UI code \*/#elif defined(PBL\_ROUND)printf("This code is run on a round display!");/\* Round UI code \*/#endif
```

Another approach for single value selection is the [`PBL_IF_RECT_ELSE()`](/docs/c/Graphics/Graphics_Types/#PBL_IF_RECT_ELSE "PBL\_IF\_RECT\_ELSE") and[`PBL_IF_ROUND_ELSE()`](/docs/c/Graphics/Graphics_Types/#PBL_IF_ROUND_ELSE "PBL\_IF\_ROUND\_ELSE") macros, which accept two parameters for each of the respective round and rectangular cases. For example, [`PBL_IF_RECT_ELSE()`](/docs/c/Graphics/Graphics_Types/#PBL_IF_RECT_ELSE "PBL\_IF\_RECT\_ELSE") will compile the first parameter on a rectangular display, and the second one otherwise:

```
// Conditionally print out the shape of the displayprintf("This is a %s display!", PBL\_IF\_RECT\_ELSE("rectangular", "round"));
```

## Circular Drawing

In addition to the older [`graphics_draw_circle()`](/docs/c/Graphics/Drawing_Primitives/#graphics_draw_circle "graphics\_draw\_circle") and[`graphics_fill_circle()`](/docs/c/Graphics/Drawing_Primitives/#graphics_fill_circle "graphics\_fill\_circle") functions, the Pebble SDK for the chalk platform contains additional functions to help draw shapes better suited for a round display. These include:

- [`graphics_draw_arc()`](/docs/c/Graphics/Drawing_Primitives/#graphics_draw_arc "graphics\_draw\_arc") - Draws a line arc clockwise between two angles within a given [`GRect`](/docs/c/Graphics/Graphics_Types/#GRect "GRect") area, where 0° is the top of the circle.

- [`graphics_fill_radial()`](/docs/c/Graphics/Drawing_Primitives/#graphics_fill_radial "graphics\_fill\_radial") - Fills a circle clockwise between two angles within a given [`GRect`](/docs/c/Graphics/Graphics_Types/#GRect "GRect") area, with adjustable inner inset radius allowing the creation of 'doughnut-esque' shapes.

- [`gpoint_from_polar()`](/docs/c/Graphics/Drawing_Primitives/#gpoint_from_polar "gpoint\_from\_polar") - Returns a [`GPoint`](/docs/c/Graphics/Graphics_Types/#GPoint "GPoint") object describing a point given by a specified angle within a centered [`GRect`](/docs/c/Graphics/Graphics_Types/#GRect "GRect").

In the Pebble SDK angles between `0` and `360` degrees are specified as values scaled between `0` and [`TRIG_MAX_ANGLE`](/docs/c/Foundation/Math/#TRIG_MAX_ANGLE "TRIG\_MAX\_ANGLE") to preserve accuracy and avoid floating point math. These are most commonly used when dealing with drawing circles. To help with this conversion, developers can use the[`DEG_TO_TRIGANGLE()`](/docs/c/Foundation/Math/#DEG_TO_TRIGANGLE "DEG\_TO\_TRIGANGLE") macro.

An example function to draw the letter 'C' in a yellow color is shown below for use in a [`LayerUpdateProc`](/docs/c/User_Interface/Layers/#LayerUpdateProc "LayerUpdateProc").

```
static void draw\_letter\_c(GRect bounds, GContext \*ctx) {GRect frame = grect\_inset(bounds, GEdgeInsets(30));graphics\_context\_set\_fill\_color(ctx, GColorYellow);graphics\_fill\_radial(ctx, frame, GOvalScaleModeFitCircle, 30,DEG\_TO\_TRIGANGLE(-225), DEG\_TO\_TRIGANGLE(45));}
```

This produces the expected result, drawn with a smooth antialiased filled circle arc between the specified angles.

![letter-c](/assets/images/guides/pebble-apps/display-animations/letter-c.png)

## Adaptive Layouts

With not only a difference in display shape, but also in resolution, it is very important that an app's layout not be created using hardcoded coordinates. Consider the examples below, designed to create a child [`Layer`](/docs/c/User_Interface/Layers/#Layer "Layer") to fill the size of the parent layer.

```
// Bad - only works on Aplite and Basalt rectangular displaysLayer \*layer = layer\_create(GRect(0, 0, 144, 168));// Better - uses the native display sizeGRect bounds = layer\_get\_bounds(parent\_layer);Layer \*layer = layer\_create(bounds);
```

Using this style, the child layer will always fill the parent layer, regardless of its actual dimensions.

In a similar vein, when working with the Pebble Time Round display it can be important that the layout is centered correctly. A set of layout values that are in the center of the classic 144 x 168 pixel display will not be centered when displayed on a 180 x 180 display. The undesirable effect of this can be seen in the example shown below:

![cut-corners](/assets/images/guides/pebble-apps/display-animations/cut-corners.png)

By using the technique described above, the layout's [`GRect`](/docs/c/Graphics/Graphics_Types/#GRect "GRect") objects can specify their `origin` and `size` as a function of the dimensions of the layer they are drawn into, solving this problem.

![centered](/assets/images/guides/pebble-apps/display-animations/centered.png)

## Text Flow and Pagination

A chief concern when working with a circular display is the rendering of large amounts of text. As demonstrated by an animation in[_Round App Design_](/guides/design-and-interaction/in-the-round.md#pagination), continuous reflowing of text makes it much harder to read.

A solution to this problem is to render text while flowing within the constraints of the shape of the display, and to scroll/animate it one page at a time. There are three approaches to this available to developers, which are detailed below. For full examples of each, see the[`text-flow-techniques`](https://github.com/pebble-examples/text-flow-techniques)example app.

### Using TextLayer

Additions to the [`TextLayer`](/docs/c/User_Interface/Layers/TextLayer/ "TextLayer") API allow text rendered within it to be automatically flowed according to the curve of the display, and paged correctly when the layer is moved or animated further. After a [`TextLayer`](/docs/c/User_Interface/Layers/TextLayer/ "TextLayer") is created in the usual way, text flow can then be enabled:

```
// Create TextLayerTextLayer \*s\_text\_layer = text\_layer\_create(bounds);/\* other properties set up \*/// Add to parent Windowlayer\_add\_child(window\_layer, text\_layer\_get\_layer(s\_text\_layer));// Enable paging and text flow with an inset of 5 pixelstext\_layer\_enable\_screen\_text\_flow\_and\_paging(s\_text\_layer, 5);
```

> Note: The [`text_layer_enable_screen_text_flow_and_paging()`](/docs/c/User_Interface/Layers/TextLayer/#text_layer_enable_screen_text_flow_and_paging "text\_layer\_enable\_screen\_text\_flow\_and\_paging") function must be called **after** the [`TextLayer`](/docs/c/User_Interface/Layers/TextLayer/ "TextLayer") is added to the view heirachy (i.e.: after using [`layer_add_child()`](/docs/c/User_Interface/Layers/#layer_add_child "layer\_add\_child")), or else it will have no effect.

An example of two [`TextLayer`](/docs/c/User_Interface/Layers/TextLayer/ "TextLayer") elements flowing their text within the constraints of the display shape is shown below:

![text-flow](/assets/images/guides/pebble-apps/display-animations/text-flow.png)

### Using ScrollLayer

The [`ScrollLayer`](/docs/c/User_Interface/Layers/ScrollLayer/ "ScrollLayer") UI component also contains round-friendly functionality, allowing it to scroll its child [`Layer`](/docs/c/User_Interface/Layers/#Layer "Layer") elements in pages of the same height as its frame (usually the size of the parent [`Window`](/docs/c/User_Interface/Window/ "Window")). This allows consuming long content to be a more consistent experience, whether it is text, images, or some other kind of information.

```
// Enable ScrollLayer pagingscroll\_layer\_set\_paging(s\_scroll\_layer, true);
```

When combined with a [`TextLayer`](/docs/c/User_Interface/Layers/TextLayer/ "TextLayer") as the main child layer, it becomes easy to display long pieces of textual content on a round display. The [`TextLayer`](/docs/c/User_Interface/Layers/TextLayer/ "TextLayer") can be set up to handle the reflowing of text to follow the display shape, and the[`ScrollLayer`](/docs/c/User_Interface/Layers/ScrollLayer/ "ScrollLayer") handles the paginated scrolling.

```
// Add the TextLayer and ScrollLayer to the view heirachyscroll\_layer\_add\_child(s\_scroll\_layer, text\_layer\_get\_layer(s\_text\_layer));layer\_add\_child(window\_layer, scroll\_layer\_get\_layer(s\_scroll\_layer));// Set the ScrollLayer's content size to the total size of the textscroll\_layer\_set\_content\_size(s\_scroll\_layer,text\_layer\_get\_content\_size(s\_text\_layer));// Enable TextLayer text flow and pagingconst int inset\_size = 2;text\_layer\_enable\_screen\_text\_flow\_and\_paging(s\_text\_layer, inset\_size);// Enable ScrollLayer pagingscroll\_layer\_set\_paging(s\_scroll\_layer, true);
```

### Manual Text Drawing

The drawing of text into a [`Graphics Context`](/docs/c/Graphics/Drawing_Text/ "Drawing Text") can also be performed with awareness of text flow and paging preferences. This can be used to emulate the behavior of the two previous approaches, but with more flexibility. This approach involves the use of the [`GTextAttributes`](/docs/c/Graphics/Drawing_Text/#GTextAttributes "GTextAttributes") object, which is given to the Graphics API to allow it to flow text and paginate when being animated.

When initializing the [`Window`](/docs/c/User_Interface/Window/ "Window") that will do the drawing:

```
// Create the attributes object used for text renderingGTextAttributes \*s\_attributes = graphics\_text\_attributes\_create();// Enable text flow with an inset of 5 pixelsgraphics\_text\_attributes\_enable\_screen\_text\_flow(s\_attributes, 5);// Enable pagination with a fixed reference point and bounds, used for animatinggraphics\_text\_attributes\_enable\_paging(s\_attributes, bounds.origin, bounds);
```

When drawing some text in a [`LayerUpdateProc`](/docs/c/User_Interface/Layers/#LayerUpdateProc "LayerUpdateProc"):

```
static void update\_proc(Layer \*layer, GContext \*ctx) {GRect bounds = layer\_get\_bounds(layer);// Calculate size of the text to be drawn with current attribute settingsGSize text\_size = graphics\_text\_layout\_get\_content\_size\_with\_attributes(s\_sample\_text, fonts\_get\_system\_font(FONT\_KEY\_GOTHIC\_24\_BOLD), bounds,GTextOverflowModeWordWrap, GTextAlignmentCenter, s\_attributes);// Draw the text in this box with the current attribute settingsgraphics\_context\_set\_text\_color(ctx, GColorBlack);graphics\_draw\_text(ctx, s\_sample\_text, fonts\_get\_system\_font(FONT\_KEY\_GOTHIC\_24\_BOLD),GRect(bounds.origin.x, bounds.origin.y, text\_size.w, text\_size.h),GTextOverflowModeWordWrap, GTextAlignmentCenter, s\_attributes);}
```

Once this setup is complete, the text will display correctly when moved or scrolled via a [`PropertyAnimation`](/docs/c/User_Interface/Animation/PropertyAnimation/ "PropertyAnimation"), such as one that moves the [`Layer`](/docs/c/User_Interface/Layers/#Layer "Layer") that draws the text upwards, and at the same time extending its height to display subsequent pages. An example animation is shown below:

```
GRect window\_bounds = layer\_get\_bounds(window\_get\_root\_layer(s\_main\_window));const int duration\_ms = 1000;// Animate the Layer upwards, lengthening it to allow the next page to be drawnGRect start = layer\_get\_frame(s\_layer);GRect finish = GRect(start.origin.x, start.origin.y - window\_bounds.size.h,start.size.w, start.size.h \* 2);// Create and scedule the PropertyAnimationPropertyAnimation \*prop\_anim = property\_animation\_create\_layer\_frame(s\_layer, &start, &finish);Animation \*animation = property\_animation\_get\_animation(prop\_anim);animation\_set\_duration(animation, duration\_ms);animation\_schedule(animation);
```

## Working With a Circular Framebuffer

The traditional rectangular Pebble app framebuffer is a single continuous memory segment that developers could access with [`gbitmap_get_data()`](/docs/c/Graphics/Graphics_Types/#gbitmap_get_data "gbitmap\_get\_data"). With a round display, Pebble saves memory by clipping sections of each line of difference between the display area and the rectangle it occupies. The resulting masking pattern looks like this:

![mask](/assets/images/guides/pebble-apps/display-animations/mask.png)

> Download this mask by saving the PNG image above, or get it as a[Photoshop PSD layer](/assets/images/guides/pebble-apps/display-animations/round-mask-layer.psd).

This has an important implication - the memory segment of the framebuffer can no longer be accessed using classic `y * row_width + x` formulae. Instead, developers should use the [`gbitmap_get_data_row_info()`](/docs/c/Graphics/Graphics_Types/#gbitmap_get_data_row_info "gbitmap\_get\_data\_row\_info") API. When used with a given y coordinate, this will return a [`GBitmapDataRowInfo`](/docs/c/Graphics/Graphics_Types/#GBitmapDataRowInfo "GBitmapDataRowInfo") object containing a pointer to the row's data, as well as values for the minumum and maximum visible values of x coordinate on that row. For example:

```
static void round\_update\_proc(Layer \*layer, GContext \*ctx) {// Get framebufferGBitmap \*fb = graphics\_capture\_frame\_buffer(ctx);GRect bounds = layer\_get\_bounds(layer);// Write a value to all visible pixelsfor(int y = 0; y \< bounds.size.h; y++) {// Get the min and max x values for this rowGBitmapDataRowInfo info = gbitmap\_get\_data\_row\_info(fb, y);// Iterate over visible pixels in that rowfor(int x = info.min\_x; x \< info.max\_x; x++) {// Set the pixel to blackmemset(&info.data[x], GColorBlack.argb, 1);}}// Release framebuffergraphics\_release\_frame\_buffer(ctx, fb);}
```

## Displaying More Content

When more content is available than fits on the screen at any one time, the user should be made aware using visual clues. The best way to do this is to use the[`ContentIndicator`](/docs/c/User_Interface/Layers/ScrollLayer/#ContentIndicator "ContentIndicator") UI component.

![content-indicator](/assets/images/guides/design-and-interaction/content-indicator.png)

A [`ContentIndicator`](/docs/c/User_Interface/Layers/ScrollLayer/#ContentIndicator "ContentIndicator") can be obtained in two ways. It can be created from scratch with [`content_indicator_create()`](/docs/c/User_Interface/Layers/ScrollLayer/#content_indicator_create "content\_indicator\_create") and manually managed to determine when the arrows should be shown, or a built-in instance can be obtained from a[`ScrollLayer`](/docs/c/User_Interface/Layers/ScrollLayer/ "ScrollLayer"), as shown below:

```
// Get the ContentIndicator from the ScrollLayers\_indicator = scroll\_layer\_get\_content\_indicator(s\_scroll\_layer);
```

In order to draw the arrows indicating more information in each direction, the[`ContentIndicator`](/docs/c/User_Interface/Layers/ScrollLayer/#ContentIndicator "ContentIndicator") must be supplied with two new [`Layer`](/docs/c/User_Interface/Layers/#Layer "Layer") elements that will be used to do the drawing. These should also be added as children to the main[`Window`](/docs/c/User_Interface/Window/ "Window") root [`Layer`](/docs/c/User_Interface/Layers/#Layer "Layer") such that they are visible on top of all other[`Layer`](/docs/c/User_Interface/Layers/#Layer "Layer") elements:

```
static void window\_load(Window \*window) {Layer \*window\_layer = window\_get\_root\_layer(window);GRect bounds = layer\_get\_bounds(window\_layer);/\* ... \*/// Create two Layers to draw the arrowss\_indicator\_up\_layer = layer\_create(GRect(0, 0, bounds.size.w, STATUS\_BAR\_LAYER\_HEIGHT));s\_indicator\_down\_layer = layer\_create(GRect(0, bounds.size.h - STATUS\_BAR\_LAYER\_HEIGHT,bounds.size.w, STATUS\_BAR\_LAYER\_HEIGHT));/\* ... \*/// Add these Layers as children after all other components to appear belowlayer\_add\_child(window\_layer, s\_indicator\_up\_layer);layer\_add\_child(window\_layer, s\_indicator\_down\_layer);}
```

Once the indicator [`Layer`](/docs/c/User_Interface/Layers/#Layer "Layer") elements have been created, each of the up and down directions for conventional vertical scrolling must be configured with data to control its behavior. Aspects such as the color of the arrows and background, whether or not the arrows time out after being brought into view, and the alignment of the drawn arrow within the [`Layer`](/docs/c/User_Interface/Layers/#Layer "Layer") itself are configured with a`const` [`ContentIndicatorConfig`](/docs/c/User_Interface/Layers/ScrollLayer/#ContentIndicatorConfig "ContentIndicatorConfig") object when each direction is being configured:

```
// Configure the properties of each indicatorconst ContentIndicatorConfig up\_config = (ContentIndicatorConfig) {.layer = s\_indicator\_up\_layer,.times\_out = false,.alignment = GAlignCenter,.colors = {.foreground = GColorBlack,.background = GColorWhite}};content\_indicator\_configure\_direction(s\_indicator, ContentIndicatorDirectionUp,&up\_config);const ContentIndicatorConfig down\_config = (ContentIndicatorConfig) {.layer = s\_indicator\_down\_layer,.times\_out = false,.alignment = GAlignCenter,.colors = {.foreground = GColorBlack,.background = GColorWhite}};content\_indicator\_configure\_direction(s\_indicator, ContentIndicatorDirectionDown,&down\_config);
```

Unless the [`ContentIndicator`](/docs/c/User_Interface/Layers/ScrollLayer/#ContentIndicator "ContentIndicator") has been retrieved from another [`Layer`](/docs/c/User_Interface/Layers/#Layer "Layer") type that includes an instance, it should be destroyed along with its parent[`Window`](/docs/c/User_Interface/Window/ "Window"):

```
// Destroy a manually created ContentIndicatorcontent\_indicator\_destroy(s\_indicator);
```

For layouts that use the [`StatusBarLayer`](/docs/c/User_Interface/Layers/StatusBarLayer/ "StatusBarLayer"), the [`ContentIndicatorDirectionUp`](/docs/c/User_Interface/Layers/ScrollLayer/#ContentIndicatorDirectionUp "ContentIndicatorDirectionUp")`.layer` in the [`ContentIndicatorConfig`](/docs/c/User_Interface/Layers/ScrollLayer/#ContentIndicatorConfig "ContentIndicatorConfig") object can be given the status bar's[`Layer`](/docs/c/User_Interface/Layers/#Layer "Layer") with [`status_bar_layer_get_layer()`](/docs/c/User_Interface/Layers/StatusBarLayer/#status_bar_layer_get_layer "status\_bar\_layer\_get\_layer"), and the drawing routines for each will be managed automatically.
