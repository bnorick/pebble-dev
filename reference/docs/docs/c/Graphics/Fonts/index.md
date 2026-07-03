# Fonts

Source: https://developer.repebble.com/docs/c/Graphics/Fonts/index.html

Custom and system fonts.

Pebble OS provides you with a wide range of system fonts that you can use when you need to display and render text or numbers in your Pebble watchface or watchapp.

If you want to use a system font, you call [fonts\_get\_system\_font()](/docs/c/Graphics/Fonts/#fonts_get_system_font) and simply pass it the name of the system font you want.

To use a custom font, call [fonts\_load\_custom\_font()](/docs/c/Graphics/Fonts/#fonts_load_custom_font). The sample code feature\_custom\_font shows how you can do this programmatically, using a font resource to convert a TrueType font into a rasterized version of that font at a specified font size.

For example:

```
GFont custom\_font = fonts\_load\_custom\_font(resource\_get\_handle(RESOURCE\_ID\_FONT\_OSP\_DIN\_44));
```

Raster Gothic Condensed is the font used throughout the Pebble system, largely because it is optimized for monochromatic displays. Pebble selected this font because it allows a relatively large number of characters to be displayed on a single line, also because the font has an excellent readability vs. size ratio.

Refer to the chapter

[App Resources in the Pebble Developer Guides](https://developer.getpebble.com/guides/pebble-apps/resources/)
 which explains how to work with font resources and embed a font into your app.

## Function Documentation

[GFont](/docs/c/Graphics/Fonts/#GFont) fonts\_get\_system\_font(const char \* font\_key)

Loads a system font corresponding to the specified font key.

##### Note

This may load a font from the flash peripheral into RAM.

#### Parameters
 font\_key

The string key of the font to load. See [System Fonts](/guides/app-resources/system-fonts.md) guide for a list of system fonts.

#### Returns

An opaque pointer to the loaded font, or, a pointer to the default (fallback) font if the specified font cannot be loaded.

[GFont](/docs/c/Graphics/Fonts/#GFont) fonts\_load\_custom\_font([ResHandle](/docs/c/Foundation/Resources/#ResHandle) handle)

Loads a custom font.

##### Note

this may load a font from the flash peripheral into RAM.

#### Parameters
 handle

The resource handle of the font to load. See resource\_ids.auto.h for a list of resource IDs, and use [resource\_get\_handle()](/docs/c/Foundation/Resources/#resource_get_handle) to obtain the resource handle.

#### Returns

An opaque pointer to the loaded font, or a pointer to the default (fallback) font if the specified font cannot be loaded.

#### See Also

Read the [App Resources](http://developer.getpebble.com/guides/pebble-apps/resources/) guide on how to embed a font into your app.

void fonts\_unload\_custom\_font([GFont](/docs/c/Graphics/Fonts/#GFont) font)

Unloads the specified custom font and frees the memory that is occupied by it.

##### Note

When an application exits, the system automatically unloads all fonts that have been loaded.

#### Parameters
 font

The font to unload.

## Typedef Documentation

 typedef struct FontInfo FontInfo

 typedef FontInfo \* GFont

Pointer to opaque font data structure.

#### See Also
[fonts\_load\_custom\_font()](/docs/c/Graphics/Fonts/#fonts_load_custom_font)  
[text\_layer\_set\_font()](/docs/c/User_Interface/Layers/TextLayer/#text_layer_set_font)  
[graphics\_draw\_text()](/docs/c/Graphics/Drawing_Text/#graphics_draw_text)
