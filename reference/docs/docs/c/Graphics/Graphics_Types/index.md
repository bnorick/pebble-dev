# Graphics Types

Source: https://developer.repebble.com/docs/c/Graphics/Graphics_Types/index.html

Basic graphics types (point, rect, size, color, bitmaps, etc.) and utility functions.

## Modules

#### [Color Definitions](/docs/c/Graphics/Graphics_Types/Color_Definitions/)

A list of all of the named colors available with links to the color map on the Pebble Developer website.

## Function Documentation

bool gcolor\_equal(GColor8 x, GColor8 y)

True if both colors are identical or both are invisible (i.e. both have alpha values of .a=0).

GColor8 gcolor\_legible\_over(GColor8 background\_color)

This method assists in improving the legibility of text on various background colors. It takes the background color for the region in question and computes a color for maximum legibility.

#### Parameters
 background\_color

Background color for the region in question

#### Returns

A legible color for the given background color

bool gpoint\_equal(const [GPoint](/docs/c/Graphics/Graphics_Types/#GPoint) \*const point\_a, const [GPoint](/docs/c/Graphics/Graphics_Types/#GPoint) \*const point\_b)

Tests whether 2 points are equal.

#### Parameters
 point\_a

Pointer to the first point

 point\_b

Pointer to the second point

#### Returns

`true` if both points are equal, `false` if not.

bool gsize\_equal(const [GSize](/docs/c/Graphics/Graphics_Types/#GSize) \* size\_a, const [GSize](/docs/c/Graphics/Graphics_Types/#GSize) \* size\_b)

Tests whether 2 sizes are equal.

#### Parameters
 size\_a

Pointer to the first size

 size\_b

Pointer to the second size

#### Returns

`true` if both sizes are equal, `false` if not.

bool grect\_equal(const [GRect](/docs/c/Graphics/Graphics_Types/#GRect) \*const rect\_a, const [GRect](/docs/c/Graphics/Graphics_Types/#GRect) \*const rect\_b)

Tests whether 2 rectangles are equal.

#### Parameters
 rect\_a

Pointer to the first rectangle

 rect\_b

Pointer to the second rectangle

#### Returns

`true` if both rectangles are equal, `false` if not.

bool grect\_is\_empty(const [GRect](/docs/c/Graphics/Graphics_Types/#GRect) \*const rect)

Tests whether the size of the rectangle is (0, 0).

##### Note

If the width and/or height of a rectangle is negative, this function will return `true`!

#### Parameters
 rect

Pointer to the rectangle

#### Returns

`true` if the rectangle its size is (0, 0), or `false` if not.

void grect\_standardize([GRect](/docs/c/Graphics/Graphics_Types/#GRect) \* rect)

Converts a rectangle's values so that the components of its size (width and/or height) are both positive. In the width and/or height are negative, the origin will offset, so that the final rectangle overlaps with the original. For example, a [GRect](/docs/c/Graphics/Graphics_Types/#GRect) with size (-10, -5) and origin (20, 20), will be standardized to size (10, 5) and origin (10, 15).

#### Parameters
 rect (in)

The rectangle to convert.

 rect (out)

The standardized rectangle.

void grect\_clip([GRect](/docs/c/Graphics/Graphics_Types/#GRect) \*const rect\_to\_clip, const [GRect](/docs/c/Graphics/Graphics_Types/#GRect) \*const rect\_clipper)

Trim one rectangle using the edges of a second rectangle.

#### Parameters
 rect\_to\_clip (in)

The rectangle that needs to be clipped (in place).

 rect\_to\_clip (out)

The clipped rectangle.

 rect\_clipper

The rectangle of which the edges will serve as "scissors" in order to trim `rect_to_clip`.

bool grect\_contains\_point(const [GRect](/docs/c/Graphics/Graphics_Types/#GRect) \* rect, const [GPoint](/docs/c/Graphics/Graphics_Types/#GPoint) \* point)

Tests whether a rectangle contains a point.

#### Parameters
 rect

The rectangle

 point

The point

#### Returns

`true` if the rectangle contains the point, or `false` if it does not.

[GPoint](/docs/c/Graphics/Graphics_Types/#GPoint) grect\_center\_point(const [GRect](/docs/c/Graphics/Graphics_Types/#GRect) \* rect)

Convenience function to compute the center-point of a given rectangle. This is equal to `(rect->x + rect->width / 2, rect->y + rect->height / 2)`.

#### Parameters
 rect

The rectangle for which to calculate the center point.

#### Returns

The point at the center of `rect`

[GRect](/docs/c/Graphics/Graphics_Types/#GRect) grect\_crop([GRect](/docs/c/Graphics/Graphics_Types/#GRect) rect, const int32\_t crop\_size\_px)

Reduce the width and height of a rectangle by insetting each of the edges with a fixed inset. The returned rectangle will be centered relative to the input rectangle.

##### Note

The function will trip an assertion if the crop yields a rectangle with negative width or height.

#### Parameters
 rect

The rectangle that will be inset

 crop\_size\_px

The inset by which each of the rectangle will be inset. A positive inset value results in a smaller rectangle, while negative inset value results in a larger rectangle.

#### Returns

The cropped rectangle.

[uint16\_t](/docs/c/Standard_C/#uint16_t) gbitmap\_get\_bytes\_per\_row(const GBitmap \* bitmap)

Get the number of bytes per row in the bitmap data for the given GBitmap. On rectangular displays, this can be used as a safe way of iterating over the rows in the bitmap, since bytes per row should be set according to format. On circular displays with pixel format of GBitmapFormat8BitCircular this will return 0, and should not be used for iteration over frame buffer pixels. Instead, use [GBitmapDataRowInfo](/docs/c/Graphics/Graphics_Types/#GBitmapDataRowInfo), which provides safe minimum and maximum x values for a given row's y value.

#### Parameters
 bitmap

A pointer to the GBitmap to get the bytes per row

#### Returns

The number of bytes per row of the GBitmap

#### See Also
[gbitmap\_get\_data](/docs/c/Graphics/Graphics_Types/#gbitmap_get_data)

[GBitmapFormat](/docs/c/Graphics/Graphics_Types/#GBitmapFormat) gbitmap\_get\_format(const GBitmap \* bitmap)

Get the [GBitmapFormat](/docs/c/Graphics/Graphics_Types/#GBitmapFormat) for the GBitmap.

#### Parameters
 bitmap

A pointer to the GBitmap to get the format

#### Returns

The format of the given GBitmap.

uint8\_t \* gbitmap\_get\_data(const GBitmap \* bitmap)

Get a pointer to the raw image data section of the given GBitmap as specified by the format of the bitmap.

#### Parameters
 bitmap

A pointer to the GBitmap to get the data

#### Returns

pointer to the raw image data for the GBitmap

#### See Also
[gbitmap\_get\_bytes\_per\_row](/docs/c/Graphics/Graphics_Types/#gbitmap_get_bytes_per_row)  

GBitmap

void gbitmap\_set\_data(GBitmap \* bitmap, uint8\_t \* data, [GBitmapFormat](/docs/c/Graphics/Graphics_Types/#GBitmapFormat) format, [uint16\_t](/docs/c/Standard_C/#uint16_t) row\_size\_bytes, bool free\_on\_destroy)

Set the bitmap data for the given GBitmap.

#### Parameters
 bitmap

A pointer to the GBitmap to set data to

 data

A pointer to the bitmap data

 format

the format of the bitmap data. If this is a palettized format, make sure that there is an accompanying call to [gbitmap\_set\_palette](/docs/c/Graphics/Graphics_Types/#gbitmap_set_palette).

 row\_size\_bytes

How many bytes a single row takes. For example, bitmap data of format GBitmapFormat1Bit must have a row size as a multiple of 4 bytes.

 free\_on\_destroy

Set whether the data should be freed when the GBitmap is destroyed.

#### See Also
[gbitmap\_destroy](/docs/c/Graphics/Graphics_Types/#gbitmap_destroy)

[GRect](/docs/c/Graphics/Graphics_Types/#GRect) gbitmap\_get\_bounds(const GBitmap \* bitmap)

Gets the bounds of the content for the GBitmap. This is set when loading the image or if changed by [gbitmap\_set\_bounds](/docs/c/Graphics/Graphics_Types/#gbitmap_set_bounds).

#### Parameters
 bitmap

A pointer to the GBitmap to get the bounding box from.

#### Returns

The bounding box for the GBitmap.

#### See Also
[gbitmap\_set\_bounds](/docs/c/Graphics/Graphics_Types/#gbitmap_set_bounds)

void gbitmap\_set\_bounds(GBitmap \* bitmap, [GRect](/docs/c/Graphics/Graphics_Types/#GRect) bounds)

Set the bounds of the given GBitmap.

#### Parameters
 bitmap

A pointer to the GBitmap to set the bounding box.

 bounds

The bounding box to set.

#### See Also
[gbitmap\_get\_bounds](/docs/c/Graphics/Graphics_Types/#gbitmap_get_bounds)

GColor \* gbitmap\_get\_palette(const GBitmap \* bitmap)

Get the palette for the given GBitmap.

#### Parameters
 bitmap

A pointer to the GBitmap to get the palette from.

#### Returns

Pointer to a GColor array containing the palette colors.

#### See Also
[gbitmap\_set\_palette](/docs/c/Graphics/Graphics_Types/#gbitmap_set_palette)

void gbitmap\_set\_palette(GBitmap \* bitmap, GColor \* palette, bool free\_on\_destroy)

Set the palette for the given GBitmap.

#### Parameters
 bitmap

A pointer to the GBitmap to set the palette to

 palette

The palette to be used. Make sure that the palette is large enough for the bitmap's format.

 free\_on\_destroy

Set whether the palette data should be freed when the GBitmap is destroyed or when another palette is set.

#### See Also
[gbitmap\_get\_format](/docs/c/Graphics/Graphics_Types/#gbitmap_get_format)  
[gbitmap\_destroy](/docs/c/Graphics/Graphics_Types/#gbitmap_destroy)  
[gbitmap\_set\_palette](/docs/c/Graphics/Graphics_Types/#gbitmap_set_palette)

GBitmap \* gbitmap\_create\_with\_resource([uint32\_t](/docs/c/Standard_C/#uint32_t) resource\_id)

Creates a new GBitmap on the heap using a Pebble image file stored as a resource. The resulting GBitmap must be destroyed using [gbitmap\_destroy()](/docs/c/Graphics/Graphics_Types/#gbitmap_destroy).

#### Parameters
 resource\_id

The ID of the bitmap resource to load

#### Returns

A pointer to the GBitmap. `NULL` if the GBitmap could not be created

GBitmap \* gbitmap\_create\_with\_data(const uint8\_t \* data)

Creates a new GBitmap on the heap initialized with the provided Pebble image data.

The resulting GBitmap must be destroyed using [gbitmap\_destroy()](/docs/c/Graphics/Graphics_Types/#gbitmap_destroy) but the image data will not be freed automatically. The developer is responsible for keeping the image data in memory as long as the bitmap is used and releasing it after the bitmap is destroyed.

##### Note

One way to generate Pebble image data is to use bitmapgen.py in the Pebble SDK to generate a .pbi file.

#### Parameters
 data

The Pebble image data. Must not be NULL. The function assumes the data to be correct; there are no sanity checks performed on the data. The data will not be copied and the pointer must remain valid for the lifetime of this GBitmap.

#### Returns

A pointer to the GBitmap. `NULL` if the GBitmap could not be created

GBitmap \* gbitmap\_create\_as\_sub\_bitmap(const GBitmap \* base\_bitmap, [GRect](/docs/c/Graphics/Graphics_Types/#GRect) sub\_rect)

Create a new GBitmap on the heap as a sub-bitmap of a 'base' GBitmap, using a [GRect](/docs/c/Graphics/Graphics_Types/#GRect) to indicate what portion of the base to use. The sub-bitmap will just reference the image data and palette of the base bitmap. No deep-copying occurs as a result of calling this function, thus the caller is responsible for making sure the base bitmap and palette will remain available when using the sub-bitmap. Note that you should not destroy the parent bitmap until the sub\_bitmap has been destroyed. The resulting GBitmap must be destroyed using [gbitmap\_destroy()](/docs/c/Graphics/Graphics_Types/#gbitmap_destroy).

#### Parameters
 base\_bitmap (in)

The bitmap that the sub-bitmap of which the image data will be used by the sub-bitmap

 sub\_rect

The rectangle within the image data of the base bitmap. The bounds of the base bitmap will be used to clip `sub_rect`.

#### Returns

A pointer to the GBitmap. `NULL` if the GBitmap could not be created

GBitmap \* gbitmap\_create\_from\_png\_data(const uint8\_t \* png\_data, [size\_t](/docs/c/Standard_C/Memory/#size_t) png\_data\_size)

Create a GBitmap based on raw PNG data. The resulting GBitmap must be destroyed using [gbitmap\_destroy()](/docs/c/Graphics/Graphics_Types/#gbitmap_destroy). The developer is responsible for freeing png\_data following this call.

##### Note

PNG decoding currently supports 1,2,4 and 8 bit palettized and grayscale images.

#### Parameters
 png\_data

PNG image data.

 png\_data\_size

PNG image size in bytes.

#### Returns

A pointer to the GBitmap. `NULL` if the GBitmap could not be created

GBitmap \* gbitmap\_create\_blank([GSize](/docs/c/Graphics/Graphics_Types/#GSize) size, [GBitmapFormat](/docs/c/Graphics/Graphics_Types/#GBitmapFormat) format)

Creates a new blank GBitmap on the heap initialized to zeroes. In the case that the format indicates a palettized bitmap, a palette of appropriate size will also be allocated on the heap. The resulting GBitmap must be destroyed using [gbitmap\_destroy()](/docs/c/Graphics/Graphics_Types/#gbitmap_destroy).

#### Parameters
 size

The Pebble image dimensions as a [GSize](/docs/c/Graphics/Graphics_Types/#GSize).

 format

The [GBitmapFormat](/docs/c/Graphics/Graphics_Types/#GBitmapFormat) the created image should be in.

#### Returns

A pointer to the GBitmap. `NULL` if the GBitmap could not be created

GBitmap \* gbitmap\_create\_blank\_with\_palette([GSize](/docs/c/Graphics/Graphics_Types/#GSize) size, [GBitmapFormat](/docs/c/Graphics/Graphics_Types/#GBitmapFormat) format, GColor \* palette, bool free\_on\_destroy)

Creates a new blank GBitmap on the heap, initialized to zeroes, and assigns it the given palette. No deep-copying of the palette occurs, so the caller is responsible for making sure the palette remains available when using the resulting bitmap. Management of that memory can be handed off to the system with the free\_on\_destroy argument.

#### Parameters
 size

The Pebble image dimensions as a [GSize](/docs/c/Graphics/Graphics_Types/#GSize).

 format

the [GBitmapFormat](/docs/c/Graphics/Graphics_Types/#GBitmapFormat) the created image and palette should be in.

 palette

a pointer to a palette that is to be used for this GBitmap. The palette should be large enough to hold enough colors for the specified format. For example, GBitmapFormat2BitPalette should have 4 colors, since 2^2 = 4.

 free\_on\_destroy

Set whether the palette data should be freed along with the bitmap data when the GBitmap is destroyed.

#### Returns

A Pointer to the GBitmap. `NULL` if the GBitmap could not be created.

GBitmap \* gbitmap\_create\_palettized\_from\_1bit(const GBitmap \* src\_bitmap)

Given a 1-bit GBitmap, create a new bitmap of format GBitmapFormat1BitPalette. The new data buffer is allocated on the heap, and a 2-color palette is allocated as well.

##### Note

The new bitmap does not depend on any data from src\_bitmap, so src\_bitmap can be freed without worry.

#### Parameters
 src\_bitmap

A GBitmap of format GBitmapFormat1Bit which is to be copied into a newly created GBitmap of format GBitmapFormat1BitPalettized.

#### Returns

The newly created 1-bit palettized GBitmap, or NULL if there is not sufficient space.

void gbitmap\_destroy(GBitmap \* bitmap)

Destroy a GBitmap. This must be called for every bitmap that's been created with gbitmap\_create\_\*.

This function will also free the memory of the bitmap data (bitmap-\>addr) if the bitmap was created with [gbitmap\_create\_blank()](/docs/c/Graphics/Graphics_Types/#gbitmap_create_blank) or [gbitmap\_create\_with\_resource()](/docs/c/Graphics/Graphics_Types/#gbitmap_create_with_resource).

If the GBitmap was created with [gbitmap\_create\_with\_data()](/docs/c/Graphics/Graphics_Types/#gbitmap_create_with_data), you must release the memory after calling [gbitmap\_destroy()](/docs/c/Graphics/Graphics_Types/#gbitmap_destroy).

GBitmapSequence \* gbitmap\_sequence\_create\_with\_resource([uint32\_t](/docs/c/Standard_C/#uint32_t) resource\_id)

Creates a GBitmapSequence from the specified resource (APNG/PNG files)

#### Parameters
 resource\_id

Resource to load and create GBitmapSequence from.

#### Returns

GBitmapSequence pointer if the resource was loaded, NULL otherwise

bool gbitmap\_sequence\_update\_bitmap\_next\_frame(GBitmapSequence \* bitmap\_sequence, GBitmap \* bitmap, [uint32\_t](/docs/c/Standard_C/#uint32_t) \* delay\_ms)

Updates the contents of the bitmap sequence to the next frame and optionally returns the delay in milliseconds until the next frame.

##### Note

GBitmap must be large enough to accommodate the bitmap\_sequence image [gbitmap\_sequence\_get\_bitmap\_size](/docs/c/Graphics/Graphics_Types/#gbitmap_sequence_get_bitmap_size)

#### Parameters
 bitmap\_sequence

Pointer to loaded bitmap sequence

 bitmap

Pointer to the initialized GBitmap in which to render the bitmap sequence

 delay\_ms (out)

If not NULL, returns the delay in milliseconds until the next frame.

#### Returns

True if frame was rendered. False if all frames (and loops) have been rendered for the sequence. Will also return false if frame could not be rendered (includes out of memory errors).

bool gbitmap\_sequence\_update\_bitmap\_by\_elapsed(GBitmapSequence \* bitmap\_sequence, GBitmap \* bitmap, [uint32\_t](/docs/c/Standard_C/#uint32_t) elapsed\_ms)

Updates the contents of the bitmap sequence to the frame at elapsed in the sequence. For looping animations this accounts for the loop, for example an animation of 1 second that is configured to loop 2 times updated to 1500 ms elapsed time will display the sequence frame at 500 ms. Elapsed time is the time from the start of the animation, and will be ignored if it is for a time earlier than the last rendered frame.

##### Notes

GBitmap must be large enough to accommodate the bitmap\_sequence image [gbitmap\_sequence\_get\_bitmap\_size](/docs/c/Graphics/Graphics_Types/#gbitmap_sequence_get_bitmap_size)

This function is disabled for play\_count 0

#### Parameters
 bitmap\_sequence

Pointer to loaded bitmap sequence

 bitmap

Pointer to the initialized GBitmap in which to render the bitmap sequence

 elapsed\_ms

Elapsed time in milliseconds in the sequence relative to start

#### Returns

True if a frame was rendered. False if all frames (and loops) have already been rendered for the sequence. Will also return false if frame could not be rendered (includes out of memory errors).

void gbitmap\_sequence\_destroy(GBitmapSequence \* bitmap\_sequence)

Deletes the GBitmapSequence structure and frees any allocated memory/decoder\_data.

#### Parameters
 bitmap\_sequence

Pointer to the bitmap sequence to free (delete)

bool gbitmap\_sequence\_restart(GBitmapSequence \* bitmap\_sequence)

Restarts the GBitmapSequence to the first frame [gbitmap\_sequence\_update\_bitmap\_next\_frame](/docs/c/Graphics/Graphics_Types/#gbitmap_sequence_update_bitmap_next_frame).

#### Parameters
 bitmap\_sequence

Pointer to loaded bitmap sequence

#### Returns

True if sequence was restarted, false otherwise

int32\_t gbitmap\_sequence\_get\_current\_frame\_idx(GBitmapSequence \* bitmap\_sequence)

This function gets the current frame number for the bitmap sequence.

#### Parameters
 bitmap\_sequence

Pointer to loaded bitmap sequence

#### Returns

index of current frame in the current loop of the bitmap sequence

[uint32\_t](/docs/c/Standard_C/#uint32_t) gbitmap\_sequence\_get\_total\_num\_frames(GBitmapSequence \* bitmap\_sequence)

This function sets the total number of frames for the bitmap sequence.

#### Parameters
 bitmap\_sequence

Pointer to loaded bitmap sequence

#### Returns

number of frames contained in a single loop of the bitmap sequence

[uint32\_t](/docs/c/Standard_C/#uint32_t) gbitmap\_sequence\_get\_play\_count(GBitmapSequence \* bitmap\_sequence)

This function gets the play count (number of times to repeat) the bitmap sequence.

##### Note

This value is initialized by the bitmap sequence data, and is modified by [gbitmap\_sequence\_set\_play\_count](/docs/c/Graphics/Graphics_Types/#gbitmap_sequence_set_play_count)

#### Parameters
 bitmap\_sequence

Pointer to loaded bitmap sequence

#### Returns

Play count of bitmap sequence, PLAY\_COUNT\_INFINITE for infinite looping

void gbitmap\_sequence\_set\_play\_count(GBitmapSequence \* bitmap\_sequence, [uint32\_t](/docs/c/Standard_C/#uint32_t) play\_count)

This function sets the play count (number of times to repeat) the bitmap sequence.

#### Parameters
 bitmap\_sequence

Pointer to loaded bitmap sequence

 play\_count

Number of times to repeat the bitmap sequence with 0 disabling update\_by\_elapsed and update\_next\_frame, and PLAY\_COUNT\_INFINITE for infinite looping of the animation

[GSize](/docs/c/Graphics/Graphics_Types/#GSize) gbitmap\_sequence\_get\_bitmap\_size(GBitmapSequence \* bitmap\_sequence)

This function gets the minimum required size (dimensions) necessary to render the bitmap sequence to a GBitmap using the /ref gbitmap\_sequence\_update\_bitmap\_next\_frame.

#### Parameters
 bitmap\_sequence

Pointer to loaded bitmap sequence

#### Returns

Dimensions required to render the bitmap sequence to a GBitmap

[GBitmapDataRowInfo](/docs/c/Graphics/Graphics_Types/#GBitmapDataRowInfo) gbitmap\_get\_data\_row\_info(const GBitmap \* bitmap, [uint16\_t](/docs/c/Standard_C/#uint16_t) y)

Provides information about a pixel data row.

##### Note

This function does not respect the bitmap's bounds but purely operates on the pixel data. This function works with every bitmap format including GBitmapFormat1Bit. The result of the function for invalid rows is undefined.

#### Parameters
 bitmap

A pointer to the GBitmap to get row info

 y

Absolute row number in the pixel data, independent from the bitmap's bounds

#### Returns

Description of the row

#### See Also
[gbitmap\_get\_data](/docs/c/Graphics/Graphics_Types/#gbitmap_get_data)

void grect\_align([GRect](/docs/c/Graphics/Graphics_Types/#GRect) \* rect, const [GRect](/docs/c/Graphics/Graphics_Types/#GRect) \* inside\_rect, const [GAlign](/docs/c/Graphics/Graphics_Types/#GAlign) alignment, const bool clip)

Aligns one rectangle within another rectangle, using an alignment parameter. The relative coordinate systems of both rectangles are assumed to be the same. When clip is true, `rect` is also clipped by the constraint.

#### Parameters
 rect (in)

The rectangle to align (in place)

 rect (out)

The aligned and optionally clipped rectangle

 inside\_rect

The rectangle in which to align `rect`

 alignment

Determines the alignment of `rect` within `inside_rect` by specifying what edges of should overlap.

 clip

Determines whether `rect` should be trimmed using the edges of `inside_rect` in case `rect` extends outside of the area that `inside_rect` covers after the alignment.

[GRect](/docs/c/Graphics/Graphics_Types/#GRect) grect\_inset([GRect](/docs/c/Graphics/Graphics_Types/#GRect) rect, [GEdgeInsets](/docs/c/Graphics/Graphics_Types/#GEdgeInsets) insets)

Returns a rectangle that is shrinked or expanded by the given edge insets.

##### Notes

The rectangle is standardized and then the inset parameters are applied. If the resulting rectangle would have a negative height or width, a GRectZero is returned.

Use this function in together with the [GEdgeInsets](/docs/c/Graphics/Graphics_Types/#GEdgeInsets) macro

```
GRect r\_inset\_all\_sides = grect\_inset(r, GEdgeInsets(10));GRect r\_inset\_vertical\_horizontal = grect\_inset(r, GEdgeInsets(10, 20));GRect r\_expand\_top\_right\_shrink\_bottom\_left = grect\_inset(r, GEdgeInsets(-10, -10, 10, 10));
```

#### Parameters
 rect

The rectangle that will be inset

 insets

The insets that will be applied

#### Returns

The resulting rectangle

## Data Structure Documentation

struct GBitmapDataRowInfo

Description of a single data row in the pixel data of a bitmap.

##### Note

This data type describes the actual pixel data of a bitmap and does not respect the bitmap's bounds.

#### Data Fields
uint8\_t \* data

Address of the byte at column 0 of a given data row in a bitmap. Use this to calculate the memory address of a pixel. For GBitmapFormat8BitCircular or GBitmapFormat8Bit this would be: `uint8_t *pixel_addr = row_info.addr + x`. Note that this byte can be outside of the valid range for this row. For example: The first valid pixel (`min_x=76`) of a row might start at 76 bytes after the given data pointer (assuming that 1 pixel is represented as 1 byte as in GBitmapFormat8BitCircular or GBitmapFormat8Bit).

int16\_t min\_x

The absolute column of a first valid pixel for a given data row.

int16\_t max\_x

The absolute column of the last valid pixel for a given data row. For optimization reasons the result can be anywhere between grect\_get\_max\_x(bitmap\_bounds) - 1 and the physical data boundary.

#### See Also
[gbitmap\_get\_data\_row\_info](/docs/c/Graphics/Graphics_Types/#gbitmap_get_data_row_info)  
[gbitmap\_get\_data](/docs/c/Graphics/Graphics_Types/#gbitmap_get_data)  
[gbitmap\_get\_bounds](/docs/c/Graphics/Graphics_Types/#gbitmap_get_bounds)

struct GEdgeInsets

Represents insets for four sides. Negative values mean a side extends.

#### Data Fields
int16\_t top

The inset at the top of an object.

int16\_t right

The inset at the right of an object.

int16\_t bottom

The inset at the bottom of an object.

int16\_t left

The inset at the left of an object.

#### See Also
[grect\_inset](/docs/c/Graphics/Graphics_Types/#grect_inset)

struct GPoint

Represents a point in a 2-dimensional coordinate system.

##### Note

Conventionally, the origin of Pebble's 2D coordinate system is in the upper, lefthand corner its x-axis extends to the right and its y-axis extends to the bottom of the screen.

#### Data Fields
int16\_t x

The x-coordinate.

int16\_t y

The y-coordinate.

struct GRect

Represents a rectangle and defining it using the origin of the upper-lefthand corner and its size.

#### Data Fields
[GPoint](/docs/c/Graphics/Graphics_Types/#GPoint) origin

The coordinate of the upper-lefthand corner point of the rectangle.

[GSize](/docs/c/Graphics/Graphics_Types/#GSize) size

The size of the rectangle.

struct GSize

Represents a 2-dimensional size.

#### Data Fields
int16\_t w

The width.

int16\_t h

The height.

## Union Documentation

struct GColor8

#### Data Fields
uint8\_t argbstruct GColor8 

## Enum Documentation

enum GBitmapFormat

The format of a GBitmap can either be 1-bit or 8-bit.

#### Enumerators
GBitmapFormat1BitGBitmapFormat8BitGBitmapFormat1BitPaletteGBitmapFormat2BitPaletteGBitmapFormat4BitPaletteGBitmapFormat8BitCircular

enum GAlign

Values to specify how two things should be aligned relative to each other.

![](/assets/images/docs/c/aplite/galign.png) ![](/assets/images/docs/c/aplite/galign.png) ![](/assets/images/docs/c/aplite/galign.png) ![](/assets/images/docs/c/aplite/galign.png) ![](/assets/images/docs/c/aplite/galign.png)

bitmap\_layer\_set\_alignment()

#### Enumerators
GAlignCenter

Align by centering.

GAlignTopLeft

Align by making the top edges overlap and left edges overlap.

GAlignTopRight

Align by making the top edges overlap and left edges overlap.

GAlignTop

Align by making the top edges overlap and centered horizontally.

GAlignLeft

Align by making the left edges overlap and centered vertically.

GAlignBottom

Align by making the bottom edges overlap and centered horizontally.

GAlignRight

Align by making the right edges overlap and centered vertically.

GAlignBottomRight

Align by making the bottom edges overlap and right edges overlap.

GAlignBottomLeft

Align by making the bottom edges overlap and left edges overlap.

enum GCompOp

Values to specify how the source image should be composited onto the destination image.

![](/assets/images/docs/c/aplite/compops.png) ![](/assets/images/docs/c/aplite/compops.png) ![](/assets/images/docs/c/aplite/compops.png) ![](/assets/images/docs/c/aplite/compops.png) ![](/assets/images/docs/c/aplite/compops.png)

Contrived example of how the different compositing modes affect drawing. Often, the "destination image" is the render buffer and thus contains the image of what has been drawn before or "underneath".

For color displays, only two compositing modes are supported, GCompOpAssign and GCompOpSet. The behavior of other compositing modes are undefined and may change in the future. Transparency can be achieved using GCompOpSet and requires pixel values with alpha value .a \< 3. bitmap\_layer\_set\_compositing\_mode() graphics\_context\_set\_compositing\_mode() graphics\_draw\_bitmap\_in\_rect() graphics\_draw\_rotated\_bitmap()

#### Enumerators
GCompOpAssign

Assign the pixel values of the source image to the destination pixels, effectively replacing the previous values for those pixels. For color displays, when drawing a palettized or 8-bit GBitmap image, the opacity value is ignored.

GCompOpAssignInverted

##### Note

For bitmaps with a format different from GBitmapFormat1Bit, this mode is not supported and the resulting behavior is undefined.

Assign the **inverted** pixel values of the source image to the destination pixels, effectively replacing the previous values for those pixels.

GCompOpOr

##### Note

For bitmaps with a format different from GBitmapFormat1Bit, this mode is not supported and the resulting behavior is undefined.

Use the boolean operator `OR` to composite the source and destination pixels. The visual result of this compositing mode is the source's white pixels are painted onto the destination and the source's black pixels are treated as clear.

GCompOpAnd

##### Note

For bitmaps with a format different from GBitmapFormat1Bit, this mode is not supported and the resulting behavior is undefined.

Use the boolean operator `AND` to composite the source and destination pixels. The visual result of this compositing mode is the source's black pixels are painted onto the destination and the source's white pixels are treated as clear.

GCompOpClear

##### Note

For bitmaps with a format different from GBitmapFormat1Bit, this mode is not supported and the resulting behavior is undefined.

Clears the bits in the destination image, using the source image as mask. The visual result of this compositing mode is that for the parts where the source image is white, the destination image will be painted black. Other parts will be left untouched.

GCompOpSet

##### Note

For bitmaps of the format GBitmapFormat1Bit, the visual result of this compositing mode is that for the parts where the source image is black, the destination image will be painted white. Other parts will be left untouched.

Sets the bits in the destination image, using the source image as mask. This mode is required to apply any transparency of your bitmap.

## Typedef Documentation

 typedef GColor8 GColor

 typedef struct GBitmap GBitmap

 typedef struct GBitmapSequence GBitmapSequence

 typedef struct GContext GContext

## Macro Definition Documentation

#define GColorFromRGBA ( red, green, blue, alpha)

Convert RGBA to GColor.

#### Parameters
 red

Red value from 0 - 255

 green

Green value from 0 - 255

 blue

Blue value from 0 - 255

 alpha

Alpha value from 0 - 255

#### Returns

GColor created from the RGB values

#define GColorFromRGB ( red, green, blue)

Convert RGB to GColor.

#### Parameters
 red

Red value from 0 - 255

 green

Green value from 0 - 255

 blue

Blue value from 0 - 255

#### Returns

GColor created from the RGB values

#define GColorFromHEX ( v)

Convert hex integer to GColor.

#### Parameters
 v

Integer hex value (e.g. 0x64ff46)

#### Returns

GColor created from the hex value

- [SDK 3](javascript:void(0);)
- [SDK 4](javascript:void(0);)
- [SDK 4.9+](javascript:void(0);)

#define COLOR\_FALLBACK ( color, bw)

Convenience macro allowing use of a fallback color for black and white platforms. On color platforms, the first expression will be chosen, the second otherwise.

#define COLOR\_FALLBACK ( color, bw)

Convenience macro allowing use of a fallback color for black and white platforms. On color platforms, the first expression will be chosen, the second otherwise.

#define COLOR\_FALLBACK ( color, bw)

Convenience macro allowing use of a fallback color for black and white platforms. On color platforms, the first expression will be chosen, the second otherwise.

#define PBL\_IF\_RECT\_ELSE ( if\_true, if\_false)

Convenience macro to switch between two expression depending on the screen of the platform. On platforms with rectangular screen, the first expression will be chosen, the second otherwise.

#define PBL\_IF\_ROUND\_ELSE ( if\_true, if\_false)

Convenience macro to switch between two expression depending on the screen of the platform. On platforms with round screen, the first expression will be chosen, the second otherwise.

- [SDK 3](javascript:void(0);)
- [SDK 4](javascript:void(0);)
- [SDK 4.9+](javascript:void(0);)

#define PBL\_IF\_BW\_ELSE ( if\_true, if\_false)

Convenience macro to switch between two expression depending on the screen of the platform. On black& white platforms, the first expression will be chosen, the second otherwise.

#define PBL\_IF\_BW\_ELSE ( if\_true, if\_false)

Convenience macro to switch between two expression depending on the screen of the platform. On black& white platforms, the first expression will be chosen, the second otherwise.

#define PBL\_IF\_BW\_ELSE ( if\_true, if\_false)

Convenience macro to switch between two expression depending on the screen of the platform. On black& white platforms, the first expression will be chosen, the second otherwise.

- [SDK 3](javascript:void(0);)
- [SDK 4](javascript:void(0);)
- [SDK 4.9+](javascript:void(0);)

#define PBL\_IF\_COLOR\_ELSE ( if\_true, if\_false)

Convenience macro to switch between two expression depending on the screen of the platform. On color platforms, the first expression will be chosen, the second otherwise.

#define PBL\_IF\_COLOR\_ELSE ( if\_true, if\_false)

Convenience macro to switch between two expression depending on the screen of the platform. On color platforms, the first expression will be chosen, the second otherwise.

#define PBL\_IF\_COLOR\_ELSE ( if\_true, if\_false)

Convenience macro to switch between two expression depending on the screen of the platform. On color platforms, the first expression will be chosen, the second otherwise.

#define GPoint ( x, y)

Convenience macro to make a [GPoint](/docs/c/Graphics/Graphics_Types/#GPoint).

#define GPointZero [GPoint](/docs/c/Graphics/Graphics_Types/#GPoint)(0, 0)

Convenience macro to make a [GPoint](/docs/c/Graphics/Graphics_Types/#GPoint) at (0, 0).

#define GSize ( w, h)

Convenience macro to make a [GSize](/docs/c/Graphics/Graphics_Types/#GSize).

#define GSizeZero [GSize](/docs/c/Graphics/Graphics_Types/#GSize)(0, 0)

Convenience macro to make a [GSize](/docs/c/Graphics/Graphics_Types/#GSize) of (0, 0).

#define GRect ( x, y, w, h)

Convenience macro to make a [GRect](/docs/c/Graphics/Graphics_Types/#GRect).

#define GRectZero [GRect](/docs/c/Graphics/Graphics_Types/#GRect)(0, 0, 0, 0)

Convenience macro to make a [GRect](/docs/c/Graphics/Graphics_Types/#GRect) of ((0, 0), (0, 0)).

#define PLAY\_COUNT\_INFINITE UINT32\_MAX

Repeat Sequence or animation indefinitely.

#define PLAY\_DURATION\_INFINITE UINT32\_MAX

Duration of Sequence or animation is infinite.

#define GEdgeInsets4 ( t, r, b, l)

helper for [GEdgeInsets](/docs/c/Graphics/Graphics_Types/#GEdgeInsets) macro

#define GEdgeInsets3 ( t, rl, b)

helper for [GEdgeInsets](/docs/c/Graphics/Graphics_Types/#GEdgeInsets) macro

#define GEdgeInsets2 ( tb, rl)

helper for [GEdgeInsets](/docs/c/Graphics/Graphics_Types/#GEdgeInsets) macro

#define GEdgeInsets1 ( trbl)

helper for [GEdgeInsets](/docs/c/Graphics/Graphics_Types/#GEdgeInsets) macro

#define GEdgeInsetsN ( \_1, \_2, \_3, \_4, NAME, ...)

helper for [GEdgeInsets](/docs/c/Graphics/Graphics_Types/#GEdgeInsets) macro

#define GEdgeInsets ( ...)

Convenience macro to make a [GEdgeInsets](/docs/c/Graphics/Graphics_Types/#GEdgeInsets) This macro follows the CSS shorthand notation where you can call it with.

- just one value [GEdgeInsets(v1)](/docs/c/Graphics/Graphics_Types/#GEdgeInsets) to configure all edges with v1 ([GEdgeInsets](/docs/c/Graphics/Graphics_Types/#GEdgeInsets)){.top = v1, .right = v1, .bottom = v1, .left = v1}

- two values v1, v2 to configure a vertical and horizontal inset as ([GEdgeInsets](/docs/c/Graphics/Graphics_Types/#GEdgeInsets)){.top = v1, .right = v2, .bottom = v1, .left = v2}

- three values v1, v2, v3 to configure it with ([GEdgeInsets](/docs/c/Graphics/Graphics_Types/#GEdgeInsets)){.top = v1, .right = v2, .bottom = v3, .left = v2}

- four values v1, v2, v3, v4 to configure it with ([GEdgeInsets](/docs/c/Graphics/Graphics_Types/#GEdgeInsets)){.top = v1, .right = v2, .bottom = v3, .left = v4} 

#### See Also

grect\_insets
