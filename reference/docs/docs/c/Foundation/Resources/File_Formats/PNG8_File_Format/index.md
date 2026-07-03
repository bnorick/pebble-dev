# PNG8 File Format

Source: https://developer.repebble.com/docs/c/Foundation/Resources/File_Formats/PNG8_File_Format/index.html

Pebble supports both a PBIs (uncompressed bitmap images) as well as PNG8 images. PNG images are compressed allowing for storage savings up to 90%. PNG8 is a PNG that uses palette-based or grayscale images with 1, 2, 4 or 8 bits per pixel. For palette-based images the pixel data represents the index into the palette, such that each pixel only needs to be large enough to represent the palette size, so

- `1-bit` supports up to 2 colors, 

- `2-bit` supports up to 4 colors, 

- `4-bit` supports up to 16 colors, 

- `8-bit` supports up to 256 colors.

There are 2 parts to the palette: the RGB24 color-mapping palette ("PLTE"), and the optional 8-bit transparency palette ("tRNs"). A pixel's color index maps to both tables, combining to allow the pixel to have both color as well as transparency.

For grayscale images, the pixel data represents the luminosity (or shade of gray).

- `1-bit` supports black and white 

- `2-bit` supports black, dark\_gray, light\_gray and white 

- `4-bit` supports black, white and 14 shades of gray 

- `8-bit` supports black, white and 254 shades of gray

Optionally, grayscale images allow for 1 fully transparent color, which is removed from the fully-opaque colors above (e.g. a 2 bit grayscale image can have black, white, dark\_gray and a transparent color).

The Basalt Platform provides for 2-bits per color channel, so images are optimized by the SDK tooling when loaded as a resource-type "png" to the Pebble's 64-colors with 4 levels of transparency. This optimization also handles mapping unsupported colors to the nearest supported color, and reducing the pixel depth to the number of bits required to support the optimized number of colors. PNG8 images from other sources are supported, with the colors truncated to match supported colors at runtime.
