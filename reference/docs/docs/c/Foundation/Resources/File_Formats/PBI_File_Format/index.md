# PBI File Format

Source: https://developer.repebble.com/docs/c/Foundation/Resources/File_Formats/PBI_File_Format/index.html

PBIs are uncompressed bitmap images with support for color-mapping palettes. PBIs store images either as raw image pixels (1-bit black and white, or 8-bit ARGB) or as palette-based images with 1, 2, or 4 bits per pixel. For palette-based images the pixel data represents the index into the palette, such that each pixel only needs to be large enough to represent the palette size, so

- `1-bit` supports up to 2 colors, 

- `2-bit` supports up to 4 colors, 

- `4-bit` supports up to 16 colors.

The metadata describes how long each row of pixels is in the buffer (the stride). The following restrictions on stride are in place for different formats:

- GBitmapFormat1Bit: Each row must be a multiple of 32 pixels (4 bytes). Using the `bounds` field, the area that is actually relevant can be specified. For example, when the image is 29 by 5 pixels (width by height) and the first bit of image data is the pixel at (0, 0), then the bounds.size would be `GSize(29, 5)` and bounds.origin would be `GPoint(0, 0)`. ![](/assets/images/docs/c/aplite/gbitmap.png) ![](/assets/images/docs/c/aplite/gbitmap.png) ![](/assets/images/docs/c/aplite/gbitmap.png) ![](/assets/images/docs/c/aplite/gbitmap.png) ![](/assets/images/docs/c/aplite/gbitmap.png)

- GBitmapFormat8Bit: Each pixel in the bitmap is represented by 1 byte. The color value of that byte correspends to a GColor.argb value. There is no restriction on row\_size\_bytes / stride.

- GBitmapFormat1BitPalette, GBitmapFormat2BitPalette, GBitmapFormat4BitPalette: Each pixel in the bitmap is represented by the number of bits the format specifies. Pixels must be packed. For example, in GBitmapFormat2BitPalette, each pixel uses 2 bits. This means 4 pixels / byte. Rows need to be byte-aligned, meaning that there can be up to 3 unused pixels at the end of each line. If the image is 5 pixels wide and 4 pixels tall, row\_size\_bytes = 2, and each row in the bitmap must take 2 bytes, so the bitmap data is 8 bytes in total.

Palettized bitmaps also need to have a palette. The palette must be of the correct size, which is specified by the format. For example, GBitmapFormat4BitPalette uses 4 bits per pixel, meaning that there must be 2^4 = 16 colors in the palette.

The Basalt Platform provides for 2-bits per color channel, so images are optimized by the SDK tooling when loaded as a resource-type "pbi" to the Pebble's 64-colors with 4 levels of transparency. This optimization also handles mapping unsupported colors to the nearest supported color, and reducing the pixel depth to the number of bits required to support the optimized number of colors.
