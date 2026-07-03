# Drawing Paths

Source: https://developer.repebble.com/docs/c/Graphics/Drawing_Paths/index.html

Functions to draw polygons into a graphics context

Code example:

```
static GPath \*s\_my\_path\_ptr = NULL;static const GPathInfo BOLT\_PATH\_INFO = {.num\_points = 6,.points = (GPoint []) {{21, 0}, {14, 26}, {28, 26}, {7, 60}, {14, 34}, {0, 34}}};// .update\_proc of my\_layer:void my\_layer\_update\_proc(Layer \*my\_layer, GContext\* ctx) {// Fill the path:graphics\_context\_set\_fill\_color(ctx, GColorWhite);gpath\_draw\_filled(ctx, s\_my\_path\_ptr);// Stroke the path:graphics\_context\_set\_stroke\_color(ctx, GColorBlack);gpath\_draw\_outline(ctx, s\_my\_path\_ptr);}void setup\_my\_path(void) {s\_my\_path\_ptr = gpath\_create(&BOLT\_PATH\_INFO);// Rotate 15 degrees:gpath\_rotate\_to(s\_my\_path\_ptr, TRIG\_MAX\_ANGLE / 360 \* 15);// Translate by (5, 5):gpath\_move\_to(s\_my\_path\_ptr, GPoint(5, 5));}// For brevity, the setup of my\_layer is not written out...
```

## Function Documentation

[GPath](/docs/c/Graphics/Drawing_Paths/#GPath) \* gpath\_create(const [GPathInfo](/docs/c/Graphics/Drawing_Paths/#GPathInfo) \* init)

Creates a new [GPath](/docs/c/Graphics/Drawing_Paths/#GPath) on the heap based on a series of points described by a [GPathInfo](/docs/c/Graphics/Drawing_Paths/#GPathInfo).

Values after initialization:

- `num_points` and `points` pointer: copied from the [GPathInfo](/docs/c/Graphics/Drawing_Paths/#GPathInfo).

- `rotation`: 0

- `offset`: (0, 0) 

#### Returns

A pointer to the [GPath](/docs/c/Graphics/Drawing_Paths/#GPath). `NULL` if the [GPath](/docs/c/Graphics/Drawing_Paths/#GPath) could not be created

void gpath\_destroy([GPath](/docs/c/Graphics/Drawing_Paths/#GPath) \* gpath)

Free a dynamically allocated gpath created with [gpath\_create()](/docs/c/Graphics/Drawing_Paths/#gpath_create)

void gpath\_draw\_filled(GContext \* ctx, [GPath](/docs/c/Graphics/Drawing_Paths/#GPath) \* path)

Draws the fill of a path into a graphics context, using the current fill color, relative to the drawing area as set up by the layering system.

#### Parameters
 ctx

The graphics context to draw into

 path

The path to fill

#### See Also
[graphics\_context\_set\_fill\_color()](/docs/c/Graphics/Graphics_Context/#graphics_context_set_fill_color)

void gpath\_draw\_outline(GContext \* ctx, [GPath](/docs/c/Graphics/Drawing_Paths/#GPath) \* path)

Draws the outline of a path into a graphics context, using the current stroke color and width, relative to the drawing area as set up by the layering system. The first and last points in the path do have a line between them.

#### Parameters
 ctx

The graphics context to draw into

 path

The path to draw

#### See Also
[graphics\_context\_set\_stroke\_color()](/docs/c/Graphics/Graphics_Context/#graphics_context_set_stroke_color)  
[gpath\_draw\_outline\_open()](/docs/c/Graphics/Drawing_Paths/#gpath_draw_outline_open)

void gpath\_rotate\_to([GPath](/docs/c/Graphics/Drawing_Paths/#GPath) \* path, int32\_t angle)

Sets the absolute rotation of the path. The current rotation will be replaced by the specified angle.

##### Note

Setting a rotation does not affect the points in the path directly. The rotation is applied on-the-fly during drawing, either using [gpath\_draw\_filled()](/docs/c/Graphics/Drawing_Paths/#gpath_draw_filled) or [gpath\_draw\_outline()](/docs/c/Graphics/Drawing_Paths/#gpath_draw_outline).

#### Parameters
 path

The path onto which to set the rotation

 angle

The absolute angle of the rotation. The angle is represented in the same way that is used with [sin\_lookup()](/docs/c/Foundation/Math/#sin_lookup). See [TRIG\_MAX\_ANGLE](/docs/c/Foundation/Math/#TRIG_MAX_ANGLE) for more information.

void gpath\_move\_to([GPath](/docs/c/Graphics/Drawing_Paths/#GPath) \* path, [GPoint](/docs/c/Graphics/Graphics_Types/#GPoint) point)

Sets the absolute offset of the path. The current translation will be replaced by the specified offset.

##### Note

Setting a translation does not affect the points in the path directly. The translation is applied on-the-fly during drawing, either using [gpath\_draw\_filled()](/docs/c/Graphics/Drawing_Paths/#gpath_draw_filled) or [gpath\_draw\_outline()](/docs/c/Graphics/Drawing_Paths/#gpath_draw_outline).

#### Parameters
 path

The path onto which to set the translation

 point

The point which is used as the vector for the translation.

void gpath\_draw\_outline\_open(GContext \* ctx, [GPath](/docs/c/Graphics/Drawing_Paths/#GPath) \* path)

Draws an open outline of a path into a graphics context, using the current stroke color and width, relative to the drawing area as set up by the layering system. The first and last points in the path do not have a line between them.

#### Parameters
 ctx

The graphics context to draw into

 path

The path to draw

#### See Also
[graphics\_context\_set\_stroke\_color()](/docs/c/Graphics/Graphics_Context/#graphics_context_set_stroke_color)  
[gpath\_draw\_outline()](/docs/c/Graphics/Drawing_Paths/#gpath_draw_outline)

## Data Structure Documentation

struct GPath

Data structure describing a path, plus its rotation and translation.

##### Note

See the remark with [GPathInfo](/docs/c/Graphics/Drawing_Paths/#GPathInfo)

#### Data Fields
[uint32\_t](/docs/c/Standard_C/#uint32_t) num\_points

The number of points in the `points` array.

[GPoint](/docs/c/Graphics/Graphics_Types/#GPoint) \* points

Pointer to an array of points.

int32\_t rotation

The rotation that will be used when drawing the path with [gpath\_draw\_filled()](/docs/c/Graphics/Drawing_Paths/#gpath_draw_filled) or [gpath\_draw\_outline()](/docs/c/Graphics/Drawing_Paths/#gpath_draw_outline)

[GPoint](/docs/c/Graphics/Graphics_Types/#GPoint) offset

The translation that will to be used when drawing the path with [gpath\_draw\_filled()](/docs/c/Graphics/Drawing_Paths/#gpath_draw_filled) or [gpath\_draw\_outline()](/docs/c/Graphics/Drawing_Paths/#gpath_draw_outline)

struct GPathInfo

Data structure describing a naked path.

##### Note

Note that this data structure only refers to an array of points; the points are not stored inside this data structure itself. In most cases, one cannot use a stack-allocated array of GPoints. Instead one often needs to provide longer-lived (static or "global") storage for the points.

#### Data Fields
[uint32\_t](/docs/c/Standard_C/#uint32_t) num\_points

The number of points in the `points` array.

[GPoint](/docs/c/Graphics/Graphics_Types/#GPoint) \* points

Pointer to an array of points.
