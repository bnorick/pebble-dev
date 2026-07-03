# Graphics Context

Source: https://developer.repebble.com/docs/c/Graphics/Graphics_Context/index.html

The "canvas" into which an application draws

The Pebble OS graphics engine, inspired by several notable graphics systems, including Apple’s Quartz 2D and its predecessor QuickDraw, provides your app with a canvas into which to draw, namely, the graphics context. A graphics context is the target into which graphics functions can paint, using Pebble drawing routines (see [Drawing Primitives](/docs/c/Graphics/Drawing_Primitives/), [Drawing Paths](/docs/c/Graphics/Drawing_Paths/) and [Drawing Text](/docs/c/Graphics/Drawing_Text/)).

A graphics context holds a reference to the bitmap into which to paint. It also holds the current drawing state, like the current fill color, stroke color, clipping box, drawing box, compositing mode, and so on. The GContext struct is the type representing the graphics context.

For drawing in your Pebble watchface or watchapp, you won't need to create a GContext yourself. In most cases, it is provided by Pebble OS as an argument passed into a render callback (the .update\_proc of a Layer).

Your app can’t call drawing functions at any given point in time: Pebble OS will request your app to render. Typically, your app will be calling out to graphics functions in the .update\_proc callback of a Layer.

## Function Documentation

void graphics\_context\_set\_stroke\_color(GContext \* ctx, GColor color)

Sets the current stroke color of the graphics context.

#### Parameters
 ctx

The graphics context onto which to set the stroke color

 color

The new stroke color

void graphics\_context\_set\_fill\_color(GContext \* ctx, GColor color)

Sets the current fill color of the graphics context.

#### Parameters
 ctx

The graphics context onto which to set the fill color

 color

The new fill color

void graphics\_context\_set\_text\_color(GContext \* ctx, GColor color)

Sets the current text color of the graphics context.

#### Parameters
 ctx

The graphics context onto which to set the text color

 color

The new text color

- [SDK 3](javascript:void(0);)
- [SDK 4](javascript:void(0);)
- [SDK 4.9+](javascript:void(0);)

void graphics\_context\_set\_compositing\_mode(GContext \* ctx, [GCompOp](/docs/c/Graphics/Graphics_Types/#GCompOp) mode)

Sets the current bitmap compositing mode of the graphics context.

##### Note

At the moment, this only affects the bitmaps drawing operations - [graphics\_draw\_bitmap\_in\_rect()](/docs/c/Graphics/Drawing_Primitives/#graphics_draw_bitmap_in_rect), [graphics\_draw\_rotated\_bitmap](/docs/c/Graphics/Drawing_Primitives/#graphics_draw_rotated_bitmap), and anything that uses those APIs -, but it currently does not affect the filling or stroking operations.

#### Parameters
 ctx

The graphics context onto which to set the compositing mode

 mode

The new compositing mode

#### See Also
[GCompOp](/docs/c/Graphics/Graphics_Types/#GCompOp)  
[bitmap\_layer\_set\_compositing\_mode()](/docs/c/User_Interface/Layers/BitmapLayer/#bitmap_layer_set_compositing_mode)

void graphics\_context\_set\_compositing\_mode(GContext \* ctx, [GCompOp](/docs/c/Graphics/Graphics_Types/#GCompOp) mode)

Sets the current bitmap compositing mode of the graphics context.

##### Note

At the moment, this only affects the bitmaps drawing operations - [graphics\_draw\_bitmap\_in\_rect()](/docs/c/Graphics/Drawing_Primitives/#graphics_draw_bitmap_in_rect), [graphics\_draw\_rotated\_bitmap](/docs/c/Graphics/Drawing_Primitives/#graphics_draw_rotated_bitmap), and anything that uses those APIs -, but it currently does not affect the filling or stroking operations.

#### Parameters
 ctx

The graphics context onto which to set the compositing mode

 mode

The new compositing mode

#### See Also
[GCompOp](/docs/c/Graphics/Graphics_Types/#GCompOp)  
[bitmap\_layer\_set\_compositing\_mode()](/docs/c/User_Interface/Layers/BitmapLayer/#bitmap_layer_set_compositing_mode)

void graphics\_context\_set\_compositing\_mode(GContext \* ctx, [GCompOp](/docs/c/Graphics/Graphics_Types/#GCompOp) mode)

Sets the current bitmap compositing mode of the graphics context. The default mode is GCompOpAssign i.e. bitmap transparency disabled.

##### Note

At the moment, this only affects the bitmaps drawing operations - [graphics\_draw\_bitmap\_in\_rect()](/docs/c/Graphics/Drawing_Primitives/#graphics_draw_bitmap_in_rect), [graphics\_draw\_rotated\_bitmap](/docs/c/Graphics/Drawing_Primitives/#graphics_draw_rotated_bitmap), and anything that uses those APIs -, but it currently does not affect the filling or stroking operations.

#### Parameters
 ctx

The graphics context onto which to set the compositing mode

 mode

The new compositing mode

#### See Also
[GCompOp](/docs/c/Graphics/Graphics_Types/#GCompOp)  
[bitmap\_layer\_set\_compositing\_mode()](/docs/c/User_Interface/Layers/BitmapLayer/#bitmap_layer_set_compositing_mode)

void graphics\_context\_set\_antialiased(GContext \* ctx, bool enable)

Sets whether antialiasing is applied to stroke drawing.

##### Note

Default value is true.

#### Parameters
 ctx

The graphics context onto which to set the antialiasing

 enable

True = antialiasing enabled, False = antialiasing disabled

void graphics\_context\_set\_stroke\_width(GContext \* ctx, uint8\_t stroke\_width)

Sets the width of the stroke for drawing routines.

##### Note

If stroke width of zero is passed, it will be ignored and will not change the value stored in GContext. Currently, only odd stroke\_width values are supported. If an even value is passed in, the value will be stored as is, but the drawing routines will round down to the previous integral value when drawing. Default value is 1.

#### Parameters
 ctx

The graphics context onto which to set the stroke width

 stroke\_width

Width in pixels of the stroke.
