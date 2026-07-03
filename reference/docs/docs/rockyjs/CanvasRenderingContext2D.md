# CanvasRenderingContext2D

Source: https://developer.repebble.com/docs/rockyjs/CanvasRenderingContext2D/

The CanvasRenderingContext2D interface is used for drawing rectangles, text, images and other objects onto the canvas element. It provides the 2D rendering context for the drawing on the device's display.

The canvas uses a standard x and y [coordinate system](https://developer.mozilla.org/en-US/docs/Web/API/Canvas_API/Tutorial/Drawing_shapes).

The `CanvasRenderingContext2D` object is obtained as a parameter in the [rocky.on('draw', ...)](/docs/rockyjs/rocky.md#on) event.

`rocky.on('draw', function(drawEvent) {  var ctx = drawEvent.context;});`

The state of pixels is maintained between each draw, so developers are responsible for clearing an area, before drawing again.

Please note that this API is still in development and there may be some limitations, which are documented below. We will also be adding support for more common APIs in future releases.

### Methods

 CanvasRenderingContext2D.clearRect(x, y, width, height) 

Sets all pixels in the rectangle at (`x`,`y`) with size (`width`, `height`) to black, erasing any previously drawn content.

`ctx.clearRect(0, 0, 144, 168);`

#### Parameters
Number x

The x-axis coordinate of the rectangle's starting point

Number y

The y-axis coordinate of the rectangle's starting point

Number width

The rectangle's width

Number height

The rectangle's height

 CanvasRenderingContext2D.fillRect(x, y, width, height) 

Draws a filled rectangle at (`x`,`y`) with size (`width`, `height`), using the current fill style.

`ctx.fillRect(0, 30, 144, 30);`

#### Parameters
Number x

The x-axis coordinate of the rectangle's starting point

Number y

The y-axis coordinate of the rectangle's starting point

Number width

The rectangle's width

Number height

The rectangle's height

 CanvasRenderingContext2D.strokeRect(x, y, width, height) 

Paints a rectangle at (`x`,`y`) with size (`width`, `height`), using the current stroke style.

`ctx.strokeRect(0, 30, 144, 30);`

#### Parameters
Number x

The x-axis coordinate of the rectangle's starting point

Number y

The y-axis coordinate of the rectangle's starting point

Number width

The rectangle's width

Number height

The rectangle's height

 CanvasRenderingContext2D.fillText(text, x, y, maxWidth) 

Draws (fills) `text` at the given (`x`,`y`) position.

`ctx.fillText('Hello World', 0, 30, 144);`

#### Parameters
String text

The text to draw

Number x

The x-axis coordinate of the text's starting point

Number y

The y-axis coordinate of the text's starting point

Number maxWidth

(Optional) Maximum width to draw. If specified, and the string is wider than the width, the font is adjusted to use a smaller font.

 CanvasRenderingContext2D.measureText(text) 

Returns a [TextMetrics](#TextMetrics) object containing information about `text`.

`var dimensions = ctx.measureText('Hello World');`

#### Parameters
String text

The text to measure

#### Returns

A `TextMetrics` object with information about the measured text

 CanvasRenderingContext2D.beginPath() 

Starts a new path by emptying the list of sub-paths. Call this method when you want to create a new path.

`ctx.beginPath();`

 CanvasRenderingContext2D.closePath() 

Causes the point of the pen to move back to the start of the current sub-path. It tries to add a straight line (but does not actually draw it) from the current point to the start. If the shape has already been closed or has only one point, this function does nothing.

`ctx.closePath();`

 CanvasRenderingContext2D.moveTo(x, y) 

Moves the starting point of a new sub-path to the (`x`,`y`) coordinates.

`ctx.moveTo(10, 20);`

#### Parameters
Number x

The destination point on the x-axis

Number y

The destination point on the y-axis

 CanvasRenderingContext2D.lineTo(x, y) 

Connects the last point of the sub-path to the (`x`,`y`) coordinates with a straight line.

`ctx.lineTo(10, 20);`

#### Parameters
Number x

The destination point on the x-axis

Number y

The destination point on the y-axis

 CanvasRenderingContext2D.arc(x, y, r, startAngle, endAngle, anticlockwise) 

Adds an arc to the path which is centered at (`x`,`y`) position with radius `r` starting at `startAngle` and ending at `endAngle` going in the direction determined by the `anticlockwise` parameter (defaulting to clockwise).

If `startAngle` \> `endAngle` nothing will be drawn, and if the difference between `startAngle` and `endAngle` exceeds 2π, a full circle will be drawn.

`// Draw a full circle outlinectx.strokeStyle = 'white';ctx.beginPath();ctx.arc(72, 84, 40, 0, 2 * Math.PI, false);ctx.stroke();`

Please note this function does not work with `.fill`, you must use [CanvasRenderingContext2D.rockyFillRadial](#rockyFillRadial) instead.

#### Parameters
Number x

The x-axis coordinate of the arc's center

Number y

The y-axis coordinate of the arc's center

Number r

The radius of the arc

Number startAngle

The angle at which the arc starts, measured clockwise from the positive x axis and expressed in radians.

Number endAngle

The angle at which the arc ends, measured clockwise from the positive x axis and expressed in radians.

 anticlockwise

(Optional) `Boolean` which, if `true`, causes the arc to be drawn counter-clockwise between the two angles (`false` by default)

 CanvasRenderingContext2D.rect(x, y, width, height) 

Creates a path for a rectangle at position (`x`,`y`) with a size that is determined by `width` and `height`. Those four points are connected by straight lines and the sub-path is marked as closed, so that you can fill or stroke this rectangle.

`ctx.rect(0, 30, 144, 50);`

#### Parameters
Number x

The x-axis coordinate of the rectangle's starting point

Number y

The y-axis coordinate of the rectangle's starting point

Number width

The rectangle's width

Number height

The rectangle's height

 CanvasRenderingContext2D.fill() 

Fills the current path with the current [fillStyle](#fillStyle).

`ctx.fill();`

 CanvasRenderingContext2D.stroke() 

Strokes the current path with the current [strokeStyle](#strokeStyle).

`ctx.stroke();`

 CanvasRenderingContext2D.save() 

Saves the entire state of the canvas by pushing the current state onto a stack.

`ctx.save();`

 CanvasRenderingContext2D.restore() 

Restores the most recently saved canvas state by popping the top entry in the drawing state stack. If there is no saved state, this method does nothing.

`ctx.restore();`

 CanvasRenderingContext2D.rockyFillRadial(x, y, innerRadius, outerRadius, startAngle, endAngle) 

Fills a circle clockwise between startAngle and endAngle where 0 is the start of the circle beginning at the 3 o'clock position on a watchface.

If `startAngle` \> `endAngle` nothing will be drawn, and if the difference between `startAngle` and `endAngle` exceeds 2π, a full circle will be drawn.

`// Draw a filled circlectx.fillStyle = 'white';ctx.rockyFillRadial(72, 84, 0, 30, 0, 2 * Math.PI);`

#### Parameters
Number x

The x-axis coordinate of the radial's center point

Number y

The y-axis coordinate of the radial's center point

Number innerRadius

The inner radius of the circle. Use 0 for a full circle

Number outerRadius

The outer radius of the circle

Number startAngle

Radial starting angle

Number endAngle

Radial finishing angle. If smaller than `startAngle` nothing is drawn

### Members

 CanvasRenderingContext2D.fillStyle

Specifies the color to use inside shapes. The default is `#000` (black).

#### 

Options

Possible values:

- Most (but not all) CSS color names. e.g. `blanchedalmond`

- Pebble color names. e.g. `shockingpink`

- Hex color codes, short and long. e.g. `#FFFFFF` or `#FFF`

Please note that we currently only support solid colors. You may specifiy `transparent` or `clear` for transparency, but we do do not support partial transparency or the `#RRGGBBAA` notation yet.

`ctx.fillStyle = 'white';`

 CanvasRenderingContext2D.strokeStyle

Specifies the color to use for lines around shapes. The default is `#000` (black).

#### 

Options

Possible values:

- Most (but not all) CSS color names. e.g. `blanchedalmond`

- Pebble color names. e.g. `shockingpink`

- Hex color codes, short and long. e.g. `#FFFFFF` or `#FFF`

Please note that we currently only support solid colors. You may specifiy `transparent` or `clear` for transparency, but we do do not support partial transparency or the `#RRGGBBAA` notation yet.

`ctx.strokeStyle = 'red';`

 CanvasRenderingContext2D.canvas

A [Canvas](#Canvas) object containing information about the system's canvas (display).

 CanvasRenderingContext2D.lineWidth

The width of lines drawn (to the nearest integer) with the context (`1.0` by default).

`ctx.lineWidth = 8;`

 CanvasRenderingContext2D.font

Specifies the current text style being used when drawing text. Although this string uses the same syntax as a CSS font specifier, you cannot specifiy arbitrary values and you must only use one of the values below.

The default font is `14px bold Gothic`.

`ctx.font = '28px bold Droid-serif';`

#### 

Options

Possible values:

- `18px bold Gothic`

- `14px Gothic`

- `14px bold Gothic`

- `18px Gothic`

- `24px Gothic`

- `24px bold Gothic`

- `28px Gothic`

- `28px bold Gothic`

- `30px bolder Bitham`

- `42px bold Bitham`

- `42px light Bitham`

- `42px Bitham-numeric`

- `34px Bitham-numeric`

- `21px Roboto`

- `49px Roboto-subset`

- `28px bold Droid-serif`

- `20px bold Leco-numbers`

- `26px bold Leco-numbers-am-pm`

- `32px bold numbers Leco-numbers`

- `36px bold numbers Leco-numbers`

- `38px bold numbers Leco-numbers`

- `42px bold numbers Leco-numbers`

- `28px light numbers Leco-numbers`

 CanvasRenderingContext2D.textAlign

Specifies the current text alignment being used when drawing text. Beware that the alignment is based on the x-axis coordinate value of the [CanvasRenderingContext2D.fillText](#fillText) method.

`ctx.textAlign = 'center';`

#### 

Options

Possible values:

- `left` - The text is left-aligned

- `right` - The text is right-aligned

- `center` - The text is center-aligned

- `start` (default) - The text is aligned left, unless using a right-to-left language. Currently only left-to-right is supported.

- `end` - The text is aligned right, unless using a right-to-left language. Currently only left-to-right is supported.

### Typedefs

TextMetrics

The TextMetrics interface represents the dimensions of a text in the canvas (display), as created by [measureText](#measureText).

#### Properties
 width

Calculated width of text in pixels.

 height

Calculated height of text in pixels.

Canvas

Provides information about the device's canvas (display). This is not actually a DOM element, it is provided for standards compliance only.

`rocky.on('draw', function(drawEvent) {  var ctx = drawEvent.context;  var h = ctx.canvas.unobstructedHeight;});`

#### Properties
 clientWidth

The full width of the canvas.

 clientHeight

The full height of the canvas.

 unobstructedWidth

The width of the canvas that is not obstructed by system overlays (Timeline Quick View).

 unobstructedHeight

The height of the canvas that is not obstructed by system overlays (Timeline Quick View).
