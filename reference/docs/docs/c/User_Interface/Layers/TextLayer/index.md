# TextLayer

Source: https://developer.repebble.com/docs/c/User_Interface/Layers/TextLayer/index.html

Layer that displays and formats a text string.

![](/assets/images/docs/c/aplite/text_layer.png) ![](/assets/images/docs/c/aplite/text_layer.png) ![](/assets/images/docs/c/aplite/text_layer.png) ![](/assets/images/docs/c/aplite/text_layer.png) ![](/assets/images/docs/c/aplite/text_layer.png)

The geometric information (bounds, frame) of the Layer is used as the "box" in which the text is drawn. The [TextLayer](/docs/c/User_Interface/Layers/TextLayer/) also has a number of other properties that influence how the text is drawn. Most important of these properties are: a pointer to the string to draw itself, the font, the text color, the background color of the layer, the overflow mode and alignment of the text inside the layer.

## Function Documentation

TextLayer \* text\_layer\_create([GRect](/docs/c/Graphics/Graphics_Types/#GRect) frame)

Creates a new TextLayer on the heap and initializes it with the default values.

- Font: Raster Gothic 14-point Boldface (system font)

- Text Alignment: GTextAlignmentLeft

- Text color: [GColorBlack](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorBlack)

- Background color: [GColorWhite](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorWhite)

- Clips: `true`

- Hidden: `false`

- Caching: `false`

The text layer is automatically marked dirty after this operation.

#### Parameters
 frame

The frame with which to initialze the TextLayer

#### Returns

A pointer to the TextLayer. `NULL` if the TextLayer could not be created

void text\_layer\_destroy(TextLayer \* text\_layer)

Destroys a TextLayer previously created by text\_layer\_create.

Layer \* text\_layer\_get\_layer(TextLayer \* text\_layer)

Gets the "root" Layer of the text layer, which is the parent for the sub- layers used for its implementation.

#### Parameters
 text\_layer

Pointer to the TextLayer for which to get the "root" Layer

#### Returns

The "root" Layer of the text layer.

void text\_layer\_set\_text(TextLayer \* text\_layer, const char \* text)

Sets the pointer to the string where the TextLayer is supposed to find the text at a later point in time, when it needs to draw itself.

##### Note

The string is not copied, so its buffer most likely cannot be stack allocated, but is recommended to be a buffer that is long-lived, at least as long as the TextLayer is part of a visible Layer hierarchy.

#### Parameters
 text\_layer

The TextLayer of which to set the text

 text

The new text to set onto the TextLayer. This must be a null-terminated and valid UTF-8 string!

#### See Also
[text\_layer\_get\_text](/docs/c/User_Interface/Layers/TextLayer/#text_layer_get_text)

const char \* text\_layer\_get\_text(TextLayer \* text\_layer)

Gets the pointer to the string that the TextLayer is using.

#### Parameters
 text\_layer

The TextLayer for which to get the text

#### See Also
[text\_layer\_set\_text](/docs/c/User_Interface/Layers/TextLayer/#text_layer_set_text)

void text\_layer\_set\_background\_color(TextLayer \* text\_layer, GColor color)

Sets the background color of the bounding box that will be drawn behind the text.

#### Parameters
 text\_layer

The TextLayer of which to set the background color

 color

The new GColor to set the background to

#### See Also
[text\_layer\_set\_text\_color](/docs/c/User_Interface/Layers/TextLayer/#text_layer_set_text_color)

void text\_layer\_set\_text\_color(TextLayer \* text\_layer, GColor color)

Sets the color of text that will be drawn.

#### Parameters
 text\_layer

The TextLayer of which to set the text color

 color

The new GColor to set the text color to

#### See Also
[text\_layer\_set\_background\_color](/docs/c/User_Interface/Layers/TextLayer/#text_layer_set_background_color)

void text\_layer\_set\_overflow\_mode(TextLayer \* text\_layer, [GTextOverflowMode](/docs/c/Graphics/Drawing_Text/#GTextOverflowMode) line\_mode)

Sets the line break mode of the TextLayer.

#### Parameters
 text\_layer

The TextLayer of which to set the overflow mode

 line\_mode

The new [GTextOverflowMode](/docs/c/Graphics/Drawing_Text/#GTextOverflowMode) to set

void text\_layer\_set\_font(TextLayer \* text\_layer, [GFont](/docs/c/Graphics/Fonts/#GFont) font)

Sets the font of the TextLayer.

#### Parameters
 text\_layer

The TextLayer of which to set the font

 font

The new [GFont](/docs/c/Graphics/Fonts/#GFont) for the TextLayer

#### See Also
[fonts\_get\_system\_font](/docs/c/Graphics/Fonts/#fonts_get_system_font)  
[fonts\_load\_custom\_font](/docs/c/Graphics/Fonts/#fonts_load_custom_font)

void text\_layer\_set\_text\_alignment(TextLayer \* text\_layer, [GTextAlignment](/docs/c/Graphics/Drawing_Text/#GTextAlignment) text\_alignment)

Sets the alignment of the TextLayer.

#### Parameters
 text\_layer

The TextLayer of which to set the alignment

 text\_alignment

The new text alignment for the TextLayer

#### See Also
[GTextAlignment](/docs/c/Graphics/Drawing_Text/#GTextAlignment)

void text\_layer\_enable\_screen\_text\_flow\_and\_paging(TextLayer \* text\_layer, uint8\_t inset)

Enables text flow following the boundaries of the screen and pagination that introduces extra line spacing at page breaks to avoid partially clipped lines for the TextLayer. If the TextLayer is part of a [ScrollLayer](/docs/c/User_Interface/Layers/ScrollLayer/) the ScrollLayer's frame will be used to configure paging.

##### Note

Make sure the TextLayer is part of the view hierarchy before calling this function. Otherwise it has no effect.

#### Parameters
 text\_layer

The TextLayer for which to enable text flow and paging

 inset

Additional amount of pixels to inset to the inside of the screen for text flow

#### See Also
[text\_layer\_restore\_default\_text\_flow\_and\_paging](/docs/c/User_Interface/Layers/TextLayer/#text_layer_restore_default_text_flow_and_paging)  
[graphics\_text\_attributes\_enable\_screen\_text\_flow](/docs/c/Graphics/Drawing_Text/#graphics_text_attributes_enable_screen_text_flow)  
[graphics\_text\_attributes\_enable\_paging](/docs/c/Graphics/Drawing_Text/#graphics_text_attributes_enable_paging)

void text\_layer\_restore\_default\_text\_flow\_and\_paging(TextLayer \* text\_layer)

Restores text flow and paging for the TextLayer to the rectangular defaults.

#### Parameters
 text\_layer

The TextLayer for which to restore text flow and paging

#### See Also
[text\_layer\_enable\_screen\_text\_flow\_and\_paging](/docs/c/User_Interface/Layers/TextLayer/#text_layer_enable_screen_text_flow_and_paging)  
[graphics\_text\_attributes\_restore\_default\_text\_flow](/docs/c/Graphics/Drawing_Text/#graphics_text_attributes_restore_default_text_flow)  
[graphics\_text\_attributes\_restore\_default\_paging](/docs/c/Graphics/Drawing_Text/#graphics_text_attributes_restore_default_paging)

[GSize](/docs/c/Graphics/Graphics_Types/#GSize) text\_layer\_get\_content\_size(TextLayer \* text\_layer)

Calculates the size occupied by the current text of the TextLayer.

#### Parameters
 text\_layer

the TextLayer for which to calculate the text's size

#### Returns

The size occupied by the current text of the TextLayer

void text\_layer\_set\_size(TextLayer \* text\_layer, const [GSize](/docs/c/Graphics/Graphics_Types/#GSize) max\_size)

Update the size of the text layer This is a convenience function to update the frame of the TextLayer.

#### Parameters
 text\_layer

The TextLayer of which to set the size

 max\_size

The new size for the TextLayer

## Typedef Documentation

 typedef struct TextLayer TextLayer
