# Customizing Your Watchface

Source: https://developer.repebble.com/tutorials/watchface-tutorial/part2/

# Customizing Your Watchface

This page contains some instructions that are different if you're using CloudPebble or if you're using the SDK locally on your computer.

Select whether you're using CloudPebble or the SDK below to show the relevant instructions!

[![](/assets/images/sdk/cloud.svg)
#### CloudPebble
](javascript:void();)[![](/assets/images/sdk/sdk-box.svg)
#### SDK
](javascript:void();)

![](/assets/images/sdk/cloud.svg) Showing instructions for CloudPebble. [Not using CloudPebble?](javascript:%20void();)

![](/assets/images/sdk/sdk-box.svg) Showing instructions for the SDK. [Using CloudPebble?](javascript:%20void();)

In the previous part we created a basic watchface that displays the time and date using system fonts. It works, but it looks like every other watchface out there. Let's fix that by adding a custom font.

By the end of this part, your watchface will look something like this:

#### aplite

#### basalt

#### chalk

#### diorite

#### emery

#### gabbro

 ![](/assets/images/tutorials/watchface-tutorial/part2~aplite.png)

 ![](/assets/images/tutorials/watchface-tutorial/part2~basalt.png)

 ![](/assets/images/tutorials/watchface-tutorial/part2~chalk.png)

 ![](/assets/images/tutorials/watchface-tutorial/part2~diorite.png)

 ![](/assets/images/tutorials/watchface-tutorial/part2~emery.png)

 ![](/assets/images/tutorials/watchface-tutorial/part2~gabbro.png)

## How Resources Work

App resources - fonts, images, and other data files - are managed through the **Resources** section in the left sidebar. Click **Add New** next to Resources to upload files and configure their type and identifier.

App resources - fonts, images, and other data files - are managed through the`media` array in `package.json`. Each entry specifies the resource type, a name to reference it in code, and the path to the file.

All resource files must be placed inside the `resources/` directory of your project.

## Adding a Custom Font

A custom font must be a [TrueType](http://en.wikipedia.org/wiki/TrueType) font in the `.ttf` file format. For this tutorial we will use[Jersey 10](https://fonts.google.com/specimen/Jersey+10) from Google Fonts, but you can use any `.ttf` font you like.

In CloudPebble, click **Add New** next to **Resources** in the left sidebar. Upload your `.ttf` font file, set the **Resource Type** to **TrueType Font** , and set the **Identifier** to `FONT_JERSEY_56`. Then add the same font file again with the identifier `FONT_JERSEY_24`. We register the same font twice at different sizes - one large size for the time, and a smaller one for the date.

Place your font file in `resources/fonts/` and add entries to the `media` array in `package.json`. We will register the same font twice at different sizes - one large size for the time, and a smaller one for the date:

```
"resources": {"media": [{"type": "font","name": "FONT\_JERSEY\_56","file": "fonts/Jersey10-Regular.ttf","compatibility": "2.7"},{"type": "font","name": "FONT\_JERSEY\_24","file": "fonts/Jersey10-Regular.ttf","compatibility": "2.7"}]}
```

The `name` field becomes a constant you can reference in C code, prefixed with`RESOURCE_ID_`. The number at the end of the name (56, 24) is just part of the name you chose - it serves as a reminder of the intended font size.

## Loading Custom Fonts in C

Back in `main.c`, declare two [`GFont`](/docs/c/Graphics/Fonts/#GFont "GFont") variables at the top of the file to hold our loaded fonts:

```
static GFont s\_time\_font;static GFont s\_date\_font;
```

Load them in `main_window_load()` using [`fonts_load_custom_font()`](/docs/c/Graphics/Fonts/#fonts_load_custom_font "fonts\_load\_custom\_font") and[`resource_get_handle()`](/docs/c/Foundation/Resources/#resource_get_handle "resource\_get\_handle"):

```
// Load custom fontss\_time\_font = fonts\_load\_custom\_font(resource\_get\_handle(RESOURCE\_ID\_FONT\_JERSEY\_56));s\_date\_font = fonts\_load\_custom\_font(resource\_get\_handle(RESOURCE\_ID\_FONT\_JERSEY\_24));
```

## Centering the Layout

While we're here, let's properly center the time and date on screen. The date starts 56 pixels below the time and its layer is 30 pixels tall, giving us a total block height. We center the block by subtracting half its height from the screen center:

```
// Center the time + date block verticallyint date\_height = 30;int block\_height = 56 + date\_height;int time\_y = (bounds.size.h / 2) - (block\_height / 2) - 10;int date\_y = time\_y + 56;
```

Notice the `- 10` offset at the end of the `time_y` calculation. Custom fonts often include internal padding (ascent space above the tallest glyph) that shifts the rendered text lower than the calculated position. Subtracting a small offset compensates for this and keeps the block visually centered on screen. You may need to adjust this value depending on the font you choose.

Use `time_y` and `date_y` in the [`text_layer_create()`](/docs/c/User_Interface/Layers/TextLayer/#text_layer_create "text\_layer\_create") calls instead of the old [`PBL_IF_ROUND_ELSE()`](/docs/c/Graphics/Graphics_Types/#PBL_IF_ROUND_ELSE "PBL\_IF\_ROUND\_ELSE") values:

```
s\_time\_layer = text\_layer\_create(GRect(0, time\_y, bounds.size.w, 60));
```

Now replace the system font calls with our custom fonts. Change the[`text_layer_set_font()`](/docs/c/User_Interface/Layers/TextLayer/#text_layer_set_font "text\_layer\_set\_font") calls for both layers:

```
// For the time layer (was FONT\_KEY\_BITHAM\_42\_BOLD)text\_layer\_set\_font(s\_time\_layer, s\_time\_font);// For the date layer (was FONT\_KEY\_GOTHIC\_24\_BOLD)text\_layer\_set\_font(s\_date\_layer, s\_date\_font);
```

## Cleaning Up

Custom fonts must be unloaded when no longer needed. Add the cleanup calls to`main_window_unload()`, after destroying the [`TextLayer`](/docs/c/User_Interface/Layers/TextLayer/ "TextLayer")s:

```
// Unload custom fontsfonts\_unload\_custom\_font(s\_time\_font);fonts\_unload\_custom\_font(s\_date\_font);
```

> Always destroy layers before unloading the fonts they use. The layer may try to access the font during destruction.

Click the **play** button to compile and install. You should see your watchface now uses the custom font, giving it a much more distinctive look.

Compile and install with `pebble build && pebble install`. You should see your watchface now uses the custom font, giving it a much more distinctive look.

## Experimenting

Here are some things you can try:

- Use a different font file. There are many free `.ttf` fonts available online at sites like [dafont.com](http://www.dafont.com) and[Google Fonts](https://fonts.google.com).
- Adjust the font sizes by changing the `name` values in `package.json`.
- Try different Y-positions in [`text_layer_create()`](/docs/c/User_Interface/Layers/TextLayer/#text_layer_create "text\_layer\_create") to adjust the layout.

> **Tip** : Not all fonts render well at small sizes on the Pebble display. Pixel-style and bitmap fonts tend to look the sharpest.

## Conclusion

In this part we learned how to:

1. Register font resources in `package.json`.
2. Load custom fonts with [`fonts_load_custom_font()`](/docs/c/Graphics/Fonts/#fonts_load_custom_font "fonts\_load\_custom\_font") and[`resource_get_handle()`](/docs/c/Foundation/Resources/#resource_get_handle "resource\_get\_handle").
3. Apply fonts to [`TextLayer`](/docs/c/User_Interface/Layers/TextLayer/ "TextLayer")s.
4. Clean up font resources properly.

Your watchface now has a unique visual identity. Check your code against[the source for this part](https://github.com/coredevices/c-watchface-tutorial/tree/main/part2)if you run into any issues.

## What's Next?

In the next part we will add a battery meter and Bluetooth disconnect alerts to give users useful information at a glance.

[Go to Part 3 →](/tutorials/watchface-tutorial/part3.md)
