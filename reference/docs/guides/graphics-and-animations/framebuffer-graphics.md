# Framebuffer Graphics

Source: https://developer.repebble.com/guides/graphics-and-animations/framebuffer-graphics/

In the context of a Pebble app, the framebuffer is the data region used to store the contents of the what is shown on the display. Using the [`Graphics Context`](/docs/c/Graphics/Graphics_Context/ "Graphics Context")API allows developers to draw primitive shapes and text, but at a slower speed and with a restricted set of drawing patterns. Getting direct access to the framebuffer allows arbitrary transforms, special effects, and other modifications to be applied to the display contents, and allows drawing at a much greater speed than standard SDK APIs.

## Accessing the Framebuffer

Access to the framebuffer can only be obtained during a [`LayerUpdateProc`](/docs/c/User_Interface/Layers/#LayerUpdateProc "LayerUpdateProc"), when redrawing is taking place. When the time comes to update the associated[`Layer`](/docs/c/User_Interface/Layers/#Layer "Layer"), the framebuffer can be obtained as a [`GBitmap`](/docs/c/Graphics/Graphics_Types/#GBitmap "GBitmap"):

```
static void layer\_update\_proc(Layer \*layer, GContext \*ctx) {// Get the framebufferGBitmap \*fb = graphics\_capture\_frame\_buffer(ctx);// Manipulate the image data...// Finally, release the framebuffergraphics\_release\_frame\_buffer(ctx, fb);}
```

> Note: Once obtained, the framebuffer **must** be released back to the app so that it may continue drawing.

The format of the data returned will vary by platform, as will the representation of a single pixel, shown in the table below.

| Platform | Framebuffer Bitmap Format | Pixel Format |
| --- | --- | --- |
| Aplite | [`GBitmapFormat1Bit`](/docs/c/Graphics/Graphics_Types/#GBitmapFormat1Bit "GBitmapFormat1Bit") | One bit (black or white) |
| Basalt | [`GBitmapFormat8Bit`](/docs/c/Graphics/Graphics_Types/#GBitmapFormat8Bit "GBitmapFormat8Bit") | One byte (two bits per color) |
| Chalk | [`GBitmapFormat8BitCircular`](/docs/c/Graphics/Graphics_Types/#GBitmapFormat8BitCircular "GBitmapFormat8BitCircular") | One byte (two bits per color) |
| Diorite | [`GBitmapFormat1Bit`](/docs/c/Graphics/Graphics_Types/#GBitmapFormat1Bit "GBitmapFormat1Bit") | One bit (black or white) |
| Flint | [`GBitmapFormat1Bit`](/docs/c/Graphics/Graphics_Types/#GBitmapFormat1Bit "GBitmapFormat1Bit") | One bit (black or white) |
| Emery | [`GBitmapFormat8Bit`](/docs/c/Graphics/Graphics_Types/#GBitmapFormat8Bit "GBitmapFormat8Bit") | One byte (two bits per color) |
| Gabbro | [`GBitmapFormat8Bit`](/docs/c/Graphics/Graphics_Types/#GBitmapFormat8Bit "GBitmapFormat8Bit") | One byte (two bits per color) |

Note that although Gabbro has a round display, its framebuffer is a regular rectangular [`GBitmapFormat8Bit`](/docs/c/Graphics/Graphics_Types/#GBitmapFormat8Bit "GBitmapFormat8Bit") rather than the packed[`GBitmapFormat8BitCircular`](/docs/c/Graphics/Graphics_Types/#GBitmapFormat8BitCircular "GBitmapFormat8BitCircular") used on Chalk.

## Modifying the Framebuffer Data

Once the framebuffer has been captured, the underlying data can be manipulated on a row-by-row or even pixel-by-pixel basis. This data region can be obtained using [`gbitmap_get_data()`](/docs/c/Graphics/Graphics_Types/#gbitmap_get_data "gbitmap\_get\_data"), but the recommended approach is to make use of[`gbitmap_get_data_row_info()`](/docs/c/Graphics/Graphics_Types/#gbitmap_get_data_row_info "gbitmap\_get\_data\_row\_info") objects to cater for framebuffer formats (such as [`GBitmapFormat8BitCircular`](/docs/c/Graphics/Graphics_Types/#GBitmapFormat8BitCircular "GBitmapFormat8BitCircular") on Chalk) where not every row is of the same width. The [`GBitmapDataRowInfo`](/docs/c/Graphics/Graphics_Types/#GBitmapDataRowInfo "GBitmapDataRowInfo") object helps with this by providing a `min_x`and `max_x` value for each `y` used to build it. Using it on platforms with a regular rectangular framebuffer is still safe — `min_x` and `max_x` will simply span the full row width.

To iterate over all rows and columns, safely avoiding those with irregular start and end indices, use two nested loops as shown below. The implementation of`set_pixel_color()` is shown in [_Getting and Setting Pixels_](#getting-and-setting-pixels):

> Note: it is only necessary to call [`gbitmap_get_data_row_info()`](/docs/c/Graphics/Graphics_Types/#gbitmap_get_data_row_info "gbitmap\_get\_data\_row\_info") once per row. Calling it more often (such as for every pixel) will incur a sigificant speed penalty.

```
GRect bounds = layer\_get\_bounds(layer);// Iterate over all rowsfor(int y = 0; y \< bounds.size.h; y++) {// Get this row's range and dataGBitmapDataRowInfo info = gbitmap\_get\_data\_row\_info(fb, y);// Iterate over all visible columnsfor(int x = info.min\_x; x \<= info.max\_x; x++) {// Manipulate the pixel at x,y...const GColor random\_color = (GColor){ .argb = rand() % 255 };// ...to be a random colorset\_pixel\_color(info, GPoint(x, y), random\_color);}}
```

## Getting and Setting Pixels

To modify a pixel's value, simply set a new value at the appropriate position in the `data` field of that row's [`GBitmapDataRowInfo`](/docs/c/Graphics/Graphics_Types/#GBitmapDataRowInfo "GBitmapDataRowInfo") object. This will modify the underlying data, and update the display once the frame buffer is released.

This process will be different depending on the [`GBitmapFormat`](/docs/c/Graphics/Graphics_Types/#GBitmapFormat "GBitmapFormat") of the captured framebuffer. On a color platform, each pixel is stored as a single byte. However, on black and white platforms this will be one bit per byte. Using[`memset()`](/docs/c/Standard_C/Memory/#memset "memset") to read or modify the correct pixel on a black and white display requires a bit more logic, shown below:

```
static GColor get\_pixel\_color(GBitmapDataRowInfo info, GPoint point) {#if defined(PBL\_COLOR)// Read the single byte color pixelreturn (GColor){ .argb = info.data[point.x] };#elif defined(PBL\_BW)// Read the single bit of the correct byteuint8\_t byte = point.x / 8;uint8\_t bit = point.x % 8; return byte\_get\_bit(&info.data[byte], bit) ? GColorWhite : GColorBlack;#endif}
```

Setting a pixel value is achieved in much the same way, with different logic depending on the format of the framebuffer on each platform:

```
static void set\_pixel\_color(GBitmapDataRowInfo info, GPoint point, GColor color) {#if defined(PBL\_COLOR)// Write the pixel's byte colormemset(&info.data[point.x], color.argb, 1);#elif defined(PBL\_BW)// Find the correct byte, then set the appropriate bituint8\_t byte = point.x / 8;uint8\_t bit = point.x % 8; byte\_set\_bit(&info.data[byte], bit, gcolor\_equal(color, GColorWhite) ? 1 : 0);#endif}
```

The `byte_get_bit()` and `byte_set_bit()` implementations are shown here for convenience:

```
static bool byte\_get\_bit(uint8\_t \*byte, uint8\_t bit) {return ((\*byte) \>\> bit) & 1;}static void byte\_set\_bit(uint8\_t \*byte, uint8\_t bit, uint8\_t value) {\*byte ^= (-value ^ \*byte) & (1 \<\< bit);}
```

## Learn More

To see an example of what can be achieved with direct access to the framebuffer and learn more about the underlying principles, watch the [talk given at the 2014 Developer Retreat](https://www.youtube.com/watch?v=lYoHh19RNy4).
