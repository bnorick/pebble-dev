# Color Select Lib

Source: https://developer.repebble.com/community/libraries/color-select-lib/

## Description

This library opens a seperate window for color selections. Useful for converting existing apps to color.

## Usage

#### 1. Add color\_sel\_lib.h and color\_sel\_lib.c to your Pebble project.

```
#include "color\_sel\_lib.h"
```

#### 2. Define a handler to use the selected color:

```
void handle\_CS\_close(int color\_argb) {GColor color = (GColor){.argb = color\_argb};// Do something// or use directlytext\_layer\_set\_background\_color(text\_layer\_name, (GColor){.argb = color\_argb});}
```

#### 3. Create the window and show it:

```
CSWindow \* myCSWindow = cswindow\_create(default\_color, false, (CSCloseHandler)handle\_CS\_close);cswindow\_show(myCSWindow, true);
```

| Parameter | Description |
| --- | --- |
| **default\_color** | The default color that the window will try to match. |
| **full\_palette** | true to use all 64 color, false to use a subset of 11 main colors. The user can switch between the two palettes by holding the select button. |
| **closeHandler** | The CSCloseHandler to fire when the keyboard closes. |
