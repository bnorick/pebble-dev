# BitmapLayer

Source: https://developer.repebble.com/docs/c/User_Interface/Layers/BitmapLayer/index.html

Layer that displays a bitmap image.

![](/assets/images/docs/c/aplite/bitmap_layer.png) ![](/assets/images/docs/c/aplite/bitmap_layer.png) ![](/assets/images/docs/c/aplite/bitmap_layer.png) ![](/assets/images/docs/c/aplite/bitmap_layer.png) ![](/assets/images/docs/c/aplite/bitmap_layer.png)

BitmapLayer is a Layer subtype that draws a GBitmap within its frame. It uses an alignment property to specify how to position the bitmap image within its frame. Optionally, when the background color is not GColorClear, it draws a solid background color behind the bitmap image, filling areas of the frame that are not covered by the bitmap image. Lastly, using the compositing mode property of the BitmapLayer, determines the way the bitmap image is drawn on top of what is underneath it (either the background color, or the layers beneath it).

### Inside the Implementation

The implementation of BitmapLayer is fairly straightforward and relies heavily on the functionality as exposed by the core drawing functions (see [Drawing Primitives](/docs/c/Graphics/Drawing_Primitives/)). [BitmapLayer](/docs/c/User_Interface/Layers/BitmapLayer/)'s drawing callback uses [graphics\_draw\_bitmap\_in\_rect()](/docs/c/Graphics/Drawing_Primitives/#graphics_draw_bitmap_in_rect) to perform the actual drawing of the GBitmap. It uses [grect\_align()](/docs/c/Graphics/Graphics_Types/#grect_align) to perform the layout of the image and it uses [graphics\_fill\_rect()](/docs/c/Graphics/Drawing_Primitives/#graphics_fill_rect) to draw the background plane.

## Function Documentation

BitmapLayer \* bitmap\_layer\_create([GRect](/docs/c/Graphics/Graphics_Types/#GRect) frame)

Creates a new bitmap layer on the heap and initalizes it the default values.

- Bitmap: `NULL` (none)

- Background color: GColorClear

- Compositing mode: GCompOpAssign

- Clips: `true`

#### Returns

A pointer to the BitmapLayer. `NULL` if the BitmapLayer could not be created

void bitmap\_layer\_destroy(BitmapLayer \* bitmap\_layer)

Destroys a window previously created by bitmap\_layer\_create.

Layer \* bitmap\_layer\_get\_layer(const BitmapLayer \* bitmap\_layer)

Gets the "root" Layer of the bitmap layer, which is the parent for the sub- layers used for its implementation.

#### Parameters
 bitmap\_layer

Pointer to the BitmapLayer for which to get the "root" Layer

#### Returns

The "root" Layer of the bitmap layer.

const GBitmap \* bitmap\_layer\_get\_bitmap(BitmapLayer \* bitmap\_layer)

Gets the pointer to the bitmap image that the BitmapLayer is using.

#### Parameters
 bitmap\_layer

The BitmapLayer for which to get the bitmap image

#### Returns

A pointer to the bitmap image that the BitmapLayer is using

void bitmap\_layer\_set\_bitmap(BitmapLayer \* bitmap\_layer, const GBitmap \* bitmap)

Sets the bitmap onto the BitmapLayer. The bitmap is set by reference (no deep copy), thus the caller of this function has to make sure the bitmap is kept in memory.

The bitmap layer is automatically marked dirty after this operation.

#### Parameters
 bitmap\_layer

The BitmapLayer for which to set the bitmap image

 bitmap

The new GBitmap to set onto the BitmapLayer

void bitmap\_layer\_set\_alignment(BitmapLayer \* bitmap\_layer, [GAlign](/docs/c/Graphics/Graphics_Types/#GAlign) alignment)

Sets the alignment of the image to draw with in frame of the BitmapLayer. The aligment parameter specifies which edges of the bitmap should overlap with the frame of the BitmapLayer. If the bitmap is smaller than the frame of the BitmapLayer, the background is filled with the background color.

The bitmap layer is automatically marked dirty after this operation.

#### Parameters
 bitmap\_layer

The BitmapLayer for which to set the aligment

 alignment

The new alignment for the image inside the BitmapLayer

- [SDK 3](javascript:void(0);)
- [SDK 4](javascript:void(0);)
- [SDK 4.9+](javascript:void(0);)

void bitmap\_layer\_set\_background\_color(BitmapLayer \* bitmap\_layer, GColor color)

Sets the background color of bounding box that will be drawn behind the image of the BitmapLayer.

The bitmap layer is automatically marked dirty after this operation.

#### Parameters
 bitmap\_layer

The BitmapLayer for which to set the background color

 color

The new GColor to set the background to

void bitmap\_layer\_set\_background\_color(BitmapLayer \* bitmap\_layer, GColor color)

Sets the background color of bounding box that will be drawn behind the image of the BitmapLayer.

The bitmap layer is automatically marked dirty after this operation.

#### Parameters
 bitmap\_layer

The BitmapLayer for which to set the background color

 color

The new GColor to set the background to

void bitmap\_layer\_set\_background\_color(BitmapLayer \* bitmap\_layer, GColor color)

Sets the background color of bounding box that will be drawn behind the image of the BitmapLayer.

The bitmap layer is automatically marked dirty after this operation.

#### Parameters
 bitmap\_layer

The BitmapLayer for which to set the background color

 color

The new GColor to set the background to

#### See Also
[bitmap\_layer\_set\_compositing\_mode](/docs/c/User_Interface/Layers/BitmapLayer/#bitmap_layer_set_compositing_mode)

- [SDK 3](javascript:void(0);)
- [SDK 4](javascript:void(0);)
- [SDK 4.9+](javascript:void(0);)

void bitmap\_layer\_set\_compositing\_mode(BitmapLayer \* bitmap\_layer, [GCompOp](/docs/c/Graphics/Graphics_Types/#GCompOp) mode)

Sets the compositing mode of how the bitmap image is composited onto the BitmapLayer's background plane, or how it is composited onto what has been drawn beneath the BitmapLayer.

The compositing mode only affects the drawing of the bitmap and not the drawing of the background color.

For Aplite, there is no notion of "transparency" in the graphics system. However, the effect of transparency can be created by masking and using compositing modes.

For Basalt, when drawing GBitmap images, GCompOpSet will be required to apply any transparency.

The bitmap layer is automatically marked dirty after this operation.

#### Parameters
 bitmap\_layer

The BitmapLayer for which to set the compositing mode

 mode

The compositing mode to set

#### See Also
[GCompOp](/docs/c/Graphics/Graphics_Types/#GCompOp)

void bitmap\_layer\_set\_compositing\_mode(BitmapLayer \* bitmap\_layer, [GCompOp](/docs/c/Graphics/Graphics_Types/#GCompOp) mode)

Sets the compositing mode of how the bitmap image is composited onto the BitmapLayer's background plane, or how it is composited onto what has been drawn beneath the BitmapLayer.

The compositing mode only affects the drawing of the bitmap and not the drawing of the background color.

For Aplite, there is no notion of "transparency" in the graphics system. However, the effect of transparency can be created by masking and using compositing modes.

For Basalt, when drawing GBitmap images, GCompOpSet will be required to apply any transparency.

The bitmap layer is automatically marked dirty after this operation.

#### Parameters
 bitmap\_layer

The BitmapLayer for which to set the compositing mode

 mode

The compositing mode to set

#### See Also
[GCompOp](/docs/c/Graphics/Graphics_Types/#GCompOp)

void bitmap\_layer\_set\_compositing\_mode(BitmapLayer \* bitmap\_layer, [GCompOp](/docs/c/Graphics/Graphics_Types/#GCompOp) mode)

Sets the compositing mode of how the bitmap image is composited onto the BitmapLayer's background plane, or how it is composited onto what has been drawn beneath the BitmapLayer.

The compositing mode only affects the drawing of the bitmap and not the drawing of the background color.

For black&white platforms, there is no notion of "transparency" in the graphics system. However, the effect of transparency can be created by masking and using compositing modes.

For color platforms, when drawing GBitmap images, GCompOpSet is required to apply any transparency.

The bitmap layer is automatically marked dirty after this operation.

#### Parameters
 bitmap\_layer

The BitmapLayer for which to set the compositing mode

 mode

The compositing mode to set

#### See Also
[GCompOp](/docs/c/Graphics/Graphics_Types/#GCompOp)

## Typedef Documentation

 typedef struct BitmapLayer BitmapLayer
