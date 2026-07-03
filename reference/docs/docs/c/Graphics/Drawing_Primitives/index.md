# Drawing Primitives

Source: https://developer.repebble.com/docs/c/Graphics/Drawing_Primitives/index.html

Functions to draw into a graphics context

Use these drawing functions inside a Layer's `.update_proc` drawing callback. A `GContext` is passed into this callback as an argument. This `GContext` can then be used with all of the drawing functions which are documented below. See [Graphics Context](/docs/c/Graphics/Graphics_Context/) for more information about the graphics context.

Refer to

[User Interface Layers chapter in the Pebble Developer Guides](https://developer.getpebble.com/guides/pebble-apps/display-and-animations/layers/)
 (chapter "Layers" and "Graphics") for a conceptual overview of the drawing system, Layers and relevant code examples.

Other drawing functions and related documentation:

- [Drawing Text](/docs/c/Graphics/Drawing_Text/)

- [Drawing Paths](/docs/c/Graphics/Drawing_Paths/)

- [Graphics Types](/docs/c/Graphics/Graphics_Types/) 

## Function Documentation

void graphics\_draw\_pixel(GContext \* ctx, [GPoint](/docs/c/Graphics/Graphics_Types/#GPoint) point)

Draws a pixel at given point in the current stroke color.

#### Parameters
 ctx

The destination graphics context in which to draw

 point

The point at which to draw the pixel

void graphics\_draw\_line(GContext \* ctx, [GPoint](/docs/c/Graphics/Graphics_Types/#GPoint) p0, [GPoint](/docs/c/Graphics/Graphics_Types/#GPoint) p1)

Draws line in the current stroke color, current stroke width and AA flag.

#### Parameters
 ctx

The destination graphics context in which to draw

 p0

The starting point of the line

 p1

The ending point of the line

void graphics\_draw\_rect(GContext \* ctx, [GRect](/docs/c/Graphics/Graphics_Types/#GRect) rect)

Draws a 1-pixel wide rectangle outline in the current stroke color.

#### Parameters
 ctx

The destination graphics context in which to draw

 rect

The rectangle for which to draw the outline

void graphics\_fill\_rect(GContext \* ctx, [GRect](/docs/c/Graphics/Graphics_Types/#GRect) rect, [uint16\_t](/docs/c/Standard_C/#uint16_t) corner\_radius, [GCornerMask](/docs/c/Graphics/Drawing_Primitives/#GCornerMask) corner\_mask)

Fills a rectangle with the current fill color, optionally rounding all or a selection of its corners.

#### Parameters
 ctx

The destination graphics context in which to draw

 rect

The rectangle to fill

 corner\_radius

The rounding radius of the corners in pixels (maximum is 8 pixels)

 corner\_mask

Bitmask of the corners that need to be rounded.

#### See Also
[GCornerMask](/docs/c/Graphics/Drawing_Primitives/#GCornerMask)

void graphics\_draw\_circle(GContext \* ctx, [GPoint](/docs/c/Graphics/Graphics_Types/#GPoint) p, [uint16\_t](/docs/c/Standard_C/#uint16_t) radius)

Draws the outline of a circle in the current stroke color.

#### Parameters
 ctx

The destination graphics context in which to draw

 p

The center point of the circle

 radius

The radius in pixels

void graphics\_fill\_circle(GContext \* ctx, [GPoint](/docs/c/Graphics/Graphics_Types/#GPoint) p, [uint16\_t](/docs/c/Standard_C/#uint16_t) radius)

Fills a circle in the current fill color.

#### Parameters
 ctx

The destination graphics context in which to draw

 p

The center point of the circle

 radius

The radius in pixels

void graphics\_draw\_round\_rect(GContext \* ctx, [GRect](/docs/c/Graphics/Graphics_Types/#GRect) rect, [uint16\_t](/docs/c/Standard_C/#uint16_t) radius)

Draws the outline of a rounded rectangle in the current stroke color.

#### Parameters
 ctx

The destination graphics context in which to draw

 rect

The rectangle defining the dimensions of the rounded rectangle to draw

 radius

The corner radius in pixels

void graphics\_draw\_bitmap\_in\_rect(GContext \* ctx, const GBitmap \* bitmap, [GRect](/docs/c/Graphics/Graphics_Types/#GRect) rect)

Draws a bitmap into the graphics context, inside the specified rectangle.

##### Note

If the size of `rect` is smaller than the size of the bitmap, the bitmap will be clipped on right and bottom edges. If the size of `rect` is larger than the size of the bitmap, the bitmap will be tiled automatically in both horizontal and vertical directions, effectively drawing a repeating pattern.

#### Parameters
 ctx

The destination graphics context in which to draw the bitmap

 bitmap

The bitmap to draw

 rect

The rectangle in which to draw the bitmap

#### See Also

GBitmap

  

GContext

GBitmap \* graphics\_capture\_frame\_buffer(GContext \* ctx)

A shortcut to capture the framebuffer in the native format of the watch.

#### See Also
[graphics\_capture\_frame\_buffer\_format](/docs/c/Graphics/Drawing_Primitives/#graphics_capture_frame_buffer_format)

GBitmap \* graphics\_capture\_frame\_buffer\_format(GContext \* ctx, [GBitmapFormat](/docs/c/Graphics/Graphics_Types/#GBitmapFormat) format)

Captures the frame buffer for direct access, using the given format. Graphics functions will not affect the frame buffer while it is captured. The frame buffer is released when `graphics_release_frame_buffer` is called. The frame buffer must be released before the end of a layer's `.update_proc` for the layer to be drawn properly.

While the frame buffer is captured calling `graphics_capture_frame_buffer` will fail and return `NULL`.

##### Note

When writing to the frame buffer, you should respect the visible boundaries of a window on the screen. Use layer\_get\_frame(window\_get\_root\_layer(window)).origin to obtain its position relative to the frame buffer. For example, drawing to (5, 5) in the frame buffer while the window is transitioning to the left with its origin at (-20, 0) would effectively draw that point at (25, 5) relative to the window. For this reason you should consider the window's root layer frame when calculating drawing coordinates.

#### Parameters
 ctx

The graphics context providing the frame buffer

 format

The format in which the framebuffer should be captured. Supported formats are GBitmapFormat1Bit and GBitmapFormat8Bit.

#### Returns

A pointer to the frame buffer. `NULL` if failed.

#### See Also

GBitmap

  
[GBitmapFormat](/docs/c/Graphics/Graphics_Types/#GBitmapFormat)  
[layer\_get\_frame](/docs/c/User_Interface/Layers/#layer_get_frame)  
[window\_get\_root\_layer](/docs/c/User_Interface/Window/#window_get_root_layer)

bool graphics\_release\_frame\_buffer(GContext \* ctx, GBitmap \* buffer)

Releases the frame buffer. Must be called before the end of a layer's `.update_proc` for the layer to be drawn properly.

If `buffer` does not point to the address previously returned by `graphics_capture_frame_buffer` the frame buffer will not be released.

#### Parameters
 ctx

The graphics context providing the frame buffer

 buffer

The pointer to frame buffer

#### Returns

True if the frame buffer was released successfully

bool graphics\_frame\_buffer\_is\_captured(GContext \* ctx)

Whether or not the frame buffer has been captured by `graphics_capture_frame_buffer`. Graphics functions will not affect the frame buffer until it has been released by `graphics_release_frame_buffer`.

#### Parameters
 ctx

The graphics context providing the frame buffer

#### Returns

True if the frame buffer has been captured

void graphics\_draw\_rotated\_bitmap(GContext \* ctx, GBitmap \* src, [GPoint](/docs/c/Graphics/Graphics_Types/#GPoint) src\_ic, int rotation, [GPoint](/docs/c/Graphics/Graphics_Types/#GPoint) dest\_ic)

Draws a rotated bitmap with a memory-sensitive 2x anti-aliasing technique (using ray-finding instead of super-sampling), which is thresholded into a b/w bitmap for 1-bit and color blended for 8-bit.

##### Note

This API has performance limitations that can degrade user experience. Use sparingly.

#### Parameters
 ctx

The destination graphics context in which to draw

 src

The source bitmap to draw

 src\_ic

Instance center (single point unaffected by rotation) relative to source bitmap

 rotation

Angle of rotation. Rotation is an integer between 0 (no rotation) and TRIG\_MAX\_ANGLE (360 degree rotation). Use [DEG\_TO\_TRIGANGLE](/docs/c/Foundation/Math/#DEG_TO_TRIGANGLE) to easily convert degrees to the appropriate value.

 dest\_ic

Where to draw the instance center of the rotated bitmap in the context.

void graphics\_draw\_arc(GContext \* ctx, [GRect](/docs/c/Graphics/Graphics_Types/#GRect) rect, [GOvalScaleMode](/docs/c/Graphics/Drawing_Primitives/#GOvalScaleMode) scale\_mode, int32\_t angle\_start, int32\_t angle\_end)

Draws a line arc clockwise between `angle_start` and `angle_end`, where 0° is the top of the circle. If the difference between `angle_start` and `angle_end` is greater than 360°, a full circle will be drawn.

#### Parameters
 ctx

The destination graphics context in which to draw using the current stroke color and antialiasing setting.

 rect

The reference rectangle to derive the center point and radius (see scale\_mode).

 scale\_mode

Determines how rect will be used to derive the center point and radius.

 angle\_start

Radial starting angle. Use [DEG\_TO\_TRIGANGLE](/docs/c/Foundation/Math/#DEG_TO_TRIGANGLE) to easily convert degrees to the appropriate value.

 angle\_end

Radial finishing angle. If smaller than `angle_start`, nothing will be drawn.

void graphics\_fill\_radial(GContext \* ctx, [GRect](/docs/c/Graphics/Graphics_Types/#GRect) rect, [GOvalScaleMode](/docs/c/Graphics/Drawing_Primitives/#GOvalScaleMode) scale\_mode, [uint16\_t](/docs/c/Standard_C/#uint16_t) inset\_thickness, int32\_t angle\_start, int32\_t angle\_end)

Fills a circle clockwise between `angle_start` and `angle_end`, where 0° is the top of the circle. If the difference between `angle_start` and `angle_end` is greater than 360°, a full circle will be drawn and filled. If `angle_start` is greater than `angle_end` nothing will be drawn.

##### Note

A simple example is drawing a 'Pacman' shape, with a starting angle of -225°, and ending angle of 45°. By setting `inset_thickness` to a non-zero value (such as 30) this example will produce the letter C.

#### Parameters
 ctx

The destination graphics context in which to draw using the current fill color and antialiasing setting.

 rect

The reference rectangle to derive the center point and radius (see scale).

 scale\_mode

Determines how rect will be used to derive the center point and radius.

 inset\_thickness

Describes how thick in pixels the radial will be drawn towards its center measured from the outside.

 angle\_start

Radial starting angle. Use [DEG\_TO\_TRIGANGLE](/docs/c/Foundation/Math/#DEG_TO_TRIGANGLE) to easily convert degrees to the appropriate value.

 angle\_end

Radial finishing angle. If smaller than `angle_start`, nothing will be drawn.

[GPoint](/docs/c/Graphics/Graphics_Types/#GPoint) gpoint\_from\_polar([GRect](/docs/c/Graphics/Graphics_Types/#GRect) rect, [GOvalScaleMode](/docs/c/Graphics/Drawing_Primitives/#GOvalScaleMode) scale\_mode, int32\_t angle)

Calculates a [GPoint](/docs/c/Graphics/Graphics_Types/#GPoint) located at the angle provided on the perimeter of a circle defined by the provided [GRect](/docs/c/Graphics/Graphics_Types/#GRect).

#### Parameters
 rect

The reference rectangle to derive the center point and radius (see scale\_mode).

 scale\_mode

Determines how rect will be used to derive the center point and radius.

 angle

The angle at which the point on the circle's perimeter should be calculated. Use [DEG\_TO\_TRIGANGLE](/docs/c/Foundation/Math/#DEG_TO_TRIGANGLE) to easily convert degrees to the appropriate value.

#### Returns

The point on the circle's perimeter.

[GRect](/docs/c/Graphics/Graphics_Types/#GRect) grect\_centered\_from\_polar([GRect](/docs/c/Graphics/Graphics_Types/#GRect) rect, [GOvalScaleMode](/docs/c/Graphics/Drawing_Primitives/#GOvalScaleMode) scale\_mode, int32\_t angle, [GSize](/docs/c/Graphics/Graphics_Types/#GSize) size)

Calculates a rectangle centered on the perimeter of a circle at a given angle. Use this to construct rectangles that follow the perimeter of a circle as an input for graphics\_fill\_radial\_internal or graphics\_draw\_arc\_internal, e.g. to draw circles every 30 degrees on a watchface.

#### Parameters
 rect

The reference rectangle to derive the circle's center point and radius (see scale\_mode).

 scale\_mode

Determines how rect will be used to derive the circle's center point and radius.

 angle

The angle at which the point on the circle's perimeter should be calculated. Use [DEG\_TO\_TRIGANGLE](/docs/c/Foundation/Math/#DEG_TO_TRIGANGLE) to easily convert degrees to the appropriate value.

 size

Width and height of the desired rectangle.

#### Returns

The rectangle centered on the circle's perimeter.

## Enum Documentation

enum GCornerMask

Bit mask values to specify the corners of a rectangle. The values can be combines using binary OR (`|`), For example: the mask to indicate top left and bottom right corners can: be created as follows: `(GCornerTopLeft | GCornerBottomRight)`

#### Enumerators
GCornerNone

No corners.

GCornerTopLeft

Top-Left corner.

GCornerTopRight

Top-Right corner.

GCornerBottomLeft

Bottom-Left corner.

GCornerBottomRight

Bottom-Right corner.

GCornersAll

All corners.

GCornersTop

Top corners.

GCornersBottom

Bottom corners.

GCornersLeft

Left corners.

GCornersRight

Right corners.

enum GOvalScaleMode

Values to specify how a given rectangle should be used to derive an oval shape.

graphics\_fill\_radial\_internal graphics\_draw\_arc\_internal gpoint\_from\_polar\_internal grect\_centered\_from\_polar

#### Enumerators
GOvalScaleModeFitCircle

Places a circle at the center of the rectangle, with a diameter that matches the rectangle's shortest side.

GOvalScaleModeFillCircle

Places a circle at the center of the rectangle, with a diameter that matches the rectangle's longest side. The circle may overflow the bounds of the rectangle.
