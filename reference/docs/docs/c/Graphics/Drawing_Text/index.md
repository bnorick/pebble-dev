# Drawing Text

Source: https://developer.repebble.com/docs/c/Graphics/Drawing_Text/index.html

Functions to draw text into a graphics context

See [Graphics Context](/docs/c/Graphics/Graphics_Context/) for more information about the graphics context.

Other drawing functions and related documentation:

- [Drawing Primitives](/docs/c/Graphics/Drawing_Primitives/)

- [Drawing Paths](/docs/c/Graphics/Drawing_Paths/)

- [Graphics Types](/docs/c/Graphics/Graphics_Types/) 

## Function Documentation

GTextAttributes \* graphics\_text\_attributes\_create(void)

Creates an instance of GTextAttributes for advanced control when rendering text.

#### Returns

New instance of GTextAttributes

#### See Also
[graphics\_draw\_text](/docs/c/Graphics/Drawing_Text/#graphics_draw_text)

void graphics\_text\_attributes\_destroy(GTextAttributes \* text\_attributes)

Destroys a previously created instance of GTextAttributes.

void graphics\_text\_attributes\_restore\_default\_text\_flow(GTextAttributes \* text\_attributes)

Restores text flow to the rectangular default.

#### Parameters
 text\_attributes

The attributes for which to disable text flow

#### See Also
[graphics\_text\_attributes\_enable\_screen\_text\_flow](/docs/c/Graphics/Drawing_Text/#graphics_text_attributes_enable_screen_text_flow)  
[text\_layer\_restore\_default\_text\_flow\_and\_paging](/docs/c/User_Interface/Layers/TextLayer/#text_layer_restore_default_text_flow_and_paging)

void graphics\_text\_attributes\_enable\_screen\_text\_flow(GTextAttributes \* text\_attributes, uint8\_t inset)

Enables text flow that follows the boundaries of the screen.

#### Parameters
 text\_attributes

The attributes for which text flow should be enabled

 inset

Additional amount of pixels to inset to the inside of the screen for text flow calculation. Can be zero.

#### See Also
[graphics\_text\_attributes\_restore\_default\_text\_flow](/docs/c/Graphics/Drawing_Text/#graphics_text_attributes_restore_default_text_flow)  
[text\_layer\_enable\_screen\_text\_flow\_and\_paging](/docs/c/User_Interface/Layers/TextLayer/#text_layer_enable_screen_text_flow_and_paging)

void graphics\_text\_attributes\_restore\_default\_paging(GTextAttributes \* text\_attributes)

Restores paging and locked content origin to the defaults.

#### Parameters
 text\_attributes

The attributes for which to restore paging and locked content origin

#### See Also
[graphics\_text\_attributes\_enable\_paging](/docs/c/Graphics/Drawing_Text/#graphics_text_attributes_enable_paging)  
[text\_layer\_restore\_default\_text\_flow\_and\_paging](/docs/c/User_Interface/Layers/TextLayer/#text_layer_restore_default_text_flow_and_paging)

void graphics\_text\_attributes\_enable\_paging(GTextAttributes \* text\_attributes, [GPoint](/docs/c/Graphics/Graphics_Types/#GPoint) content\_origin\_on\_screen, [GRect](/docs/c/Graphics/Graphics_Types/#GRect) paging\_on\_screen)

Enables paging and locks the text flow calculation to a fixed point on the screen.

#### Parameters
 text\_attributes

Attributes for which to enable paging and locked content origin

 content\_origin\_on\_screen

Absolute coordinate on the screen where the text content starts before an animation or scrolling takes place. Usually the frame's origin of a layer in screen coordinates.

 paging\_on\_screen

Rectangle in absolute coordinates on the screen that describes where text content pages. Usually the container's absolute frame in screen coordinates.

#### See Also
[graphics\_text\_attributes\_restore\_default\_paging](/docs/c/Graphics/Drawing_Text/#graphics_text_attributes_restore_default_paging)  
[graphics\_text\_attributes\_enable\_screen\_text\_flow](/docs/c/Graphics/Drawing_Text/#graphics_text_attributes_enable_screen_text_flow)  
[text\_layer\_enable\_screen\_text\_flow\_and\_paging](/docs/c/User_Interface/Layers/TextLayer/#text_layer_enable_screen_text_flow_and_paging)  
[layer\_convert\_point\_to\_screen](/docs/c/User_Interface/Layers/#layer_convert_point_to_screen)

void graphics\_draw\_text(GContext \* ctx, const char \* text, [GFont](/docs/c/Graphics/Fonts/#GFont) const font, const [GRect](/docs/c/Graphics/Graphics_Types/#GRect) box, const [GTextOverflowMode](/docs/c/Graphics/Drawing_Text/#GTextOverflowMode) overflow\_mode, const [GTextAlignment](/docs/c/Graphics/Drawing_Text/#GTextAlignment) alignment, GTextAttributes \* text\_attributes)

Draw text into the current graphics context, using the context's current text color. The text will be drawn inside a box with the specified dimensions and configuration, with clipping occuring automatically.

#### Parameters
 ctx

The destination graphics context in which to draw

 text

The zero terminated UTF-8 string to draw

 font

The font in which the text should be set

 box

The bounding box in which to draw the text. The first line of text will be drawn against the top of the box.

 overflow\_mode

The overflow behavior, in case the text is larger than what fits inside the box.

 alignment

The horizontal alignment of the text

 text\_attributes

Optional text attributes to describe the characteristics of the text

[GSize](/docs/c/Graphics/Graphics_Types/#GSize) graphics\_text\_layout\_get\_content\_size(const char \* text, [GFont](/docs/c/Graphics/Fonts/#GFont) const font, const [GRect](/docs/c/Graphics/Graphics_Types/#GRect) box, const [GTextOverflowMode](/docs/c/Graphics/Drawing_Text/#GTextOverflowMode) overflow\_mode, const [GTextAlignment](/docs/c/Graphics/Drawing_Text/#GTextAlignment) alignment)

Obtain the maximum size that a text with given font, overflow mode and alignment occupies within a given rectangular constraint.

#### Parameters
 text

The zero terminated UTF-8 string for which to calculate the size

 font

The font in which the text should be set while calculating the size

 box

The bounding box in which the text should be constrained

 overflow\_mode

The overflow behavior, in case the text is larger than what fits inside the box.

 alignment

The horizontal alignment of the text

#### Returns

The maximum size occupied by the text

#### See Also

app\_graphics\_text\_layout\_get\_content\_size\_with\_attributes

[GSize](/docs/c/Graphics/Graphics_Types/#GSize) graphics\_text\_layout\_get\_content\_size\_with\_attributes(const char \* text, [GFont](/docs/c/Graphics/Fonts/#GFont) const font, const [GRect](/docs/c/Graphics/Graphics_Types/#GRect) box, const [GTextOverflowMode](/docs/c/Graphics/Drawing_Text/#GTextOverflowMode) overflow\_mode, const [GTextAlignment](/docs/c/Graphics/Drawing_Text/#GTextAlignment) alignment, GTextAttributes \* text\_attributes)

Obtain the maximum size that a text with given font, overflow mode and alignment occupies within a given rectangular constraint.

#### Parameters
 text

The zero terminated UTF-8 string for which to calculate the size

 font

The font in which the text should be set while calculating the size

 box

The bounding box in which the text should be constrained

 overflow\_mode

The overflow behavior, in case the text is larger than what fits inside the box.

 alignment

The horizontal alignment of the text

 text\_attributes

Optional text attributes to describe the characteristics of the text

#### Returns

The maximum size occupied by the text

#### See Also

app\_graphics\_text\_layout\_get\_content\_size

## Enum Documentation

enum GTextOverflowMode

Text overflow mode controls the way text overflows when the string that is drawn does not fit inside the area constraint.

graphics\_draw\_text text\_layer\_set\_overflow\_mode

#### Enumerators
GTextOverflowModeWordWrap

On overflow, wrap words to a new line below the current one. Once vertical space is consumed, the last line may be clipped.

GTextOverflowModeTrailingEllipsis

On overflow, wrap words to a new line below the current one. Once vertical space is consumed, truncate as needed to fit a trailing ellipsis (...). Clipping may occur if the vertical space cannot accomodate the first line of text.

GTextOverflowModeFill

Acts like GTextOverflowModeTrailingEllipsis, plus trims leading and trailing newlines, while treating all other newlines as spaces.

enum GTextAlignment

Text aligment controls the way the text is aligned inside the box the text is drawn into.

graphics\_draw\_text text\_layer\_set\_text\_alignment

#### Enumerators
GTextAlignmentLeft

Aligns the text to the left of the drawing box.

GTextAlignmentCenter

Aligns the text centered inside the drawing box.

GTextAlignmentRight

Aligns the text to the right of the drawing box.

## Typedef Documentation

 typedef struct GTextAttributes GTextAttributes
