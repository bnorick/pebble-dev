# RotBitmapLayer

Source: https://developer.repebble.com/docs/c/User_Interface/Layers/RotBitmapLayer/index.html

Layer that displays a rotated bitmap image.

A RotBitmapLayer is like a [BitmapLayer](/docs/c/User_Interface/Layers/BitmapLayer/) but has the ability to be rotated (by default, around its center). The amount of rotation is specified using [rot\_bitmap\_layer\_set\_angle()](/docs/c/User_Interface/Layers/RotBitmapLayer/#rot_bitmap_layer_set_angle) or [rot\_bitmap\_layer\_increment\_angle()](/docs/c/User_Interface/Layers/RotBitmapLayer/#rot_bitmap_layer_increment_angle). The rotation argument to those functions is specified as an amount of clockwise rotation, where the value 0x10000 represents a full 360 degree rotation and 0 represent no rotation, and it scales linearly between those values, just like [sin\_lookup](/docs/c/Foundation/Math/#sin_lookup).

The center of rotation in the source bitmap is always placed at the center of the RotBitmapLayer and the size of the RotBitmapLayer is automatically calculated so that the entire Bitmap can fit in at all rotation angles.

For example, if the image is 10px wide and high, the RotBitmapLayer will be 14px wide ( sqrt(10^2+10^2) ).

By default, the center of rotation in the source bitmap is the center of the bitmap but you can call [rot\_bitmap\_set\_src\_ic()](/docs/c/User_Interface/Layers/RotBitmapLayer/#rot_bitmap_set_src_ic) to change the center of rotation.

## Function Documentation

RotBitmapLayer \* rot\_bitmap\_layer\_create(GBitmap \* bitmap)

Creates a new RotBitmapLayer on the heap and initializes it with the default values:

- Angle: 0

- Compositing mode: GCompOpAssign

- Corner clip color: GColorClear

#### Parameters
 bitmap

The bitmap to display in this RotBitmapLayer

#### Returns

A pointer to the RotBitmapLayer. `NULL` if the RotBitmapLayer could not be created

void rot\_bitmap\_layer\_destroy(RotBitmapLayer \* bitmap)

Destroys a RotBitmapLayer and frees all associated memory.

##### Note

It is the developer responsibility to free the GBitmap.

#### Parameters
 bitmap

The RotBitmapLayer to destroy.

void rot\_bitmap\_layer\_set\_corner\_clip\_color(RotBitmapLayer \* bitmap, GColor color)

Defines what color to use in areas that are not covered by the source bitmap. By default this is GColorClear.

#### Parameters
 bitmap

The RotBitmapLayer on which to change the corner clip color

 color

The corner clip color

void rot\_bitmap\_layer\_set\_angle(RotBitmapLayer \* bitmap, int32\_t angle)

Sets the rotation angle of this RotBitmapLayer.

#### Parameters
 bitmap

The RotBitmapLayer on which to change the rotation

 angle

Rotation is an integer between 0 (no rotation) and 0x10000 (360 degree rotation).

#### See Also
[sin\_lookup()](/docs/c/Foundation/Math/#sin_lookup)

void rot\_bitmap\_layer\_increment\_angle(RotBitmapLayer \* bitmap, int32\_t angle\_change)

Change the rotation angle of this RotBitmapLayer.

#### Parameters
 bitmap

The RotBitmapLayer on which to change the rotation

 angle\_change

The rotation angle change

void rot\_bitmap\_set\_src\_ic(RotBitmapLayer \* bitmap, [GPoint](/docs/c/Graphics/Graphics_Types/#GPoint) ic)

Defines the only point that will not be affected by the rotation in the source bitmap.

For example, if you pass [GPoint(0, 0)](/docs/c/Graphics/Graphics_Types/#GPoint), the image will rotate around the top-left corner.

This point is always projected at the center of the RotBitmapLayer. Calling this function automatically adjusts the width and height of the RotBitmapLayer so that the entire bitmap can fit inside the layer at all rotation angles.

#### Parameters
 bitmap

The RotBitmapLayer on which to change the rotation

 ic

The only point in the original image that will not be affected by the rotation.

- [SDK 3](javascript:void(0);)
- [SDK 4](javascript:void(0);)
- [SDK 4.9+](javascript:void(0);)

void rot\_bitmap\_set\_compositing\_mode(RotBitmapLayer \* bitmap, [GCompOp](/docs/c/Graphics/Graphics_Types/#GCompOp) mode)

Sets the compositing mode of how the bitmap image is composited onto what has been drawn beneath the RotBitmapLayer. By default this is GCompOpAssign. The RotBitmapLayer is automatically marked dirty after this operation.

#### Parameters
 bitmap

The RotBitmapLayer on which to change the rotation

 mode

The compositing mode to set

#### See Also
[GCompOp](/docs/c/Graphics/Graphics_Types/#GCompOp)

void rot\_bitmap\_set\_compositing\_mode(RotBitmapLayer \* bitmap, [GCompOp](/docs/c/Graphics/Graphics_Types/#GCompOp) mode)

Sets the compositing mode of how the bitmap image is composited onto what has been drawn beneath the RotBitmapLayer. By default this is GCompOpAssign. The RotBitmapLayer is automatically marked dirty after this operation.

#### Parameters
 bitmap

The RotBitmapLayer on which to change the rotation

 mode

The compositing mode to set

#### See Also
[GCompOp](/docs/c/Graphics/Graphics_Types/#GCompOp)

void rot\_bitmap\_set\_compositing\_mode(RotBitmapLayer \* bitmap, [GCompOp](/docs/c/Graphics/Graphics_Types/#GCompOp) mode)

Sets the compositing mode of how the bitmap image is composited onto what has been drawn beneath the RotBitmapLayer. By default this is GCompOpAssign, i.e. transparency disabled. The RotBitmapLayer is automatically marked dirty after this operation.

#### Parameters
 bitmap

The RotBitmapLayer on which to change the rotation

 mode

The compositing mode to set

#### See Also
[GCompOp](/docs/c/Graphics/Graphics_Types/#GCompOp)

Layer \* rot\_bitmap\_layer\_get\_layer(const RotBitmapLayer \* rot\_bitmap\_layer)

Gets the "root" Layer of the RotBitmapLayer, which is the parent for the sub- layers used for its implementation.

#### Parameters
 rot\_bitmap\_layer

Pointer to the RotBitmapLayer for which to get the "root" Layer

#### Returns

The "root" Layer of the RotBitmapLayer.

## Typedef Documentation

 typedef struct RotBitmapLayer RotBitmapLayer
