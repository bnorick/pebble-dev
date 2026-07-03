# Custom Status Bar For Pebble

Source: https://developer.repebble.com/community/libraries/custom-status-bar-for-pebble/

A plug and play custom status bar implementation for pebble apps and watch faces. Easily populate 3 [text layers](/docs/c/User_Interface/Layers/TextLayer/ "TextLayer") and/or 5 [bitmap layers](/docs/c/User_Interface/Layers/BitmapLayer/ "BitmapLayer").

Use:

Choose a status bar height and icon size. Icons should be square with a maximum of 28 pixels.

```
#define BAR\_HEIGHT 20#define ICON\_WIDTH\_HEIGHT 15
```

Declare

```
static CustomStatusBarLayer \*custom\_status\_bar;
```

Create

```
custom\_status\_bar = custom\_status\_bar\_layer\_create(BAR\_HEIGHT, GColorBlack, ICON\_WIDTH\_HEIGHT);
```

Set Text and Icons

Text layers, use positions CSB\_TEXT\_LEFT, CSB\_TEXT\_RIGHT, CSB\_TEXT\_CENTER

```
char \*t = ...;custom\_status\_bar\_layer\_set\_text(custom\_status\_bar, CSB\_TEXT\_LEFT, t);
```

Icons, use positions CSB\_ICON\_0 to CSB\_ICON\_4 (positions are left to right, 0 indexed)

```
custom\_status\_bar\_layer\_set\_bitmap(custom\_status\_bar, CSB\_ICON\_4, your\_gbitmap);
```

When you're done, destroy

```
custom\_status\_bar\_layer\_destroy(custom\_status\_bar);
```

One last note! Your window should have a height of `168 - BAR_HEIGHT`.

See the header file for more details. Enjoy!

![](http://rebootsramblings.ca/forumpictures/icons.png "Icons") ![](http://rebootsramblings.ca/forumpictures/textlayers.png "Text")
