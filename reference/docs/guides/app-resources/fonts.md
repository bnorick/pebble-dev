# Fonts

Source: https://developer.repebble.com/guides/app-resources/fonts/

## Using Fonts

Text drawn in a Pebble app can be drawn using a variety of built-in fonts or a custom font specified as a project resource.

Custom font resources must be in the `.ttf` (TrueType font) format. When the app is built, the font file is processed by the SDK according to the `compatibility`(See [_Font Compatibility_](#font-compatibility)) and `characterRegex`fields (see [_Choosing Font Characters_](#choosing-font-characters)), the latter of which is a standard Python regex describing the character set of the resulting font.

## System Fonts

All of the built-in system fonts are available to use with[`fonts_get_system_font()`](/docs/c/Graphics/Fonts/#fonts_get_system_font "fonts\_get\_system\_font"). See [_System Fonts_](/guides/app-resources/system-fonts.md) for a complete list with sample images. Examples of using a built-in system font in code are [shown below](#using-a-system-font).

### Limitations

There are limitations to the Bitham, Roboto, Droid and LECO fonts, owing to the memory space available on Pebble, which only contain a subset of the default character set.

- Roboto 49 Bold Subset - contains digits and a colon.
- Bitham 34/42 Medium Numbers - contain digits and a colon.
- Bitham 18/34 Light Subset - only contains a few characters and is not suitable for displaying general text.
- LECO Number sets - suitable for number-only usage.

## Using a System Font

Using a system font is the easiest choice when displaying simple text. For more advanced cases, a custom font may be advantageous. A system font can be obtained at any time, and the developer is not responsible for destroying it when they are done with it. Fonts can be used in two modes:

```
// Use a system font in a TextLayertext\_layer\_set\_font(s\_text\_layer, fonts\_get\_system\_font(FONT\_KEY\_GOTHIC\_24));
```

```
// Use a system font when drawing text manuallygraphics\_draw\_text(ctx, text, fonts\_get\_system\_font(FONT\_KEY\_GOTHIC\_24), bounds,GTextOverflowModeWordWrap, GTextAlignmentCenter, NULL);
```

## Adding a Custom Font

After placing the font file in the project's `resources` directory, the custom font can be added to a project as `font` `type` item in the `media` array in`package.json`. The `name` field's contents will be made available at compile time with `RESOURCE_ID_` at the front, and must end with the desired font size. For example:

```
"resources": {"media": [{"type": "font","name": "EXAMPLE\_FONT\_20","file": "example\_font.ttf"}]}
```

**Important**  

The maximum recommended font size is 48.

## Using a Custom Font

Unlike a system font, a custom font must be loaded and unloaded by the developer. Once this has been done, the font can easily be used in a similar manner.

When the app initializes, load the font from resources using the generated`RESOURCE_ID`:

```
// Declare a file-scope variablestatic GFont s\_font;
```

```
// Load the custom fonts\_font = fonts\_load\_custom\_font(resource\_get\_handle(RESOURCE\_ID\_EXAMPLE\_FONT\_20));
```

The font can now be used in two modes - with a [`TextLayer`](/docs/c/User_Interface/Layers/TextLayer/ "TextLayer"), or when drawing text manually in a [`LayerUpdateProc`](/docs/c/User_Interface/Layers/#LayerUpdateProc "LayerUpdateProc"):

```
// Use a custom font in a TextLayertext\_layer\_set\_font(s\_text\_layer, s\_font);
```

```
// Use a custom font when drawing text manuallygraphics\_draw\_text(ctx, text, s\_font, bounds, GTextOverflowModeWordWrap,GTextAlignmentCenter, NULL);
```

## Font Compatibility

The font rendering process was improved in SDK 2.8. However, in some cases this may cause the appearance of custom fonts to change slightly. To revert to the old rendering process, add `"compatibility": "2.7"` to your font's object in the`media` array (shown above) in `package.json`.

## Choosing Font Characters

By default, the maximum number of supported characters is generated for a font resource. In most cases this will be far too many, and can bloat the size of the app. To optimize the size of your font resources you can use a standard regular expression (or 'regex') string to limit the number of characters to only those you require.

The table below outlines some example regular expressions to use for limiting font character sets in common watchapp scenarios:

| Expression | Result |
| --- | --- |
| `[-~]` | ASCII characters only. |
| `[0-9]` | Numbers only. |
| `[0-9]` | Numbers and spaces only. |
| `[a-zA-Z]` | Letters only. |
| `[a-zA-Z]` | Letters and spaces only. |
| `[0-9:APM]` | Time strings only (e.g.: "12:45 AM"). |
| `[0-9:A-Za-z]` | Time and date strings (e.g.: "12:43 AM Wednesday 3rd March 2015". |
| `[0-9:A-Za-z°]` | Time, date, and degree symbol for temperature gauges. |
| `[0-9°CF]` | Numbers and degree symbol with 'C' and 'F' for temperature gauges. |

Add the `characterRegex` key to any font objects in `package.json`'s`media` array.

```
"media": [{"characterRegex": "[:0-9]","type": "font","name": "EXAMPLE\_FONT","file": "example\_font.ttf"}]
```

Check out[regular-expressions.info](http://www.regular-expressions.info/tutorial.html)to learn more about how to use regular expressions.
