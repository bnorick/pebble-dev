# PBBitmap Class Reference

Source: https://developer.repebble.com/docs/pebblekit-ios/Classes/PBBitmap/

| Inherits from | NSObject |
| Declared in | PBBitmap.h |

## Overview

Helper class to convert a UIImage to Pebble bitmap pixel data and GBitmap metadata. Refer to the documentation of Pebble’s native watch app SDK on the GBitmap format.

### pixelData

The pixel data of the bitmap. This corresponds to the data as pointed to by GBitmap’s `addr` field.

`@property (nonatomic, readonly, strong) NSData *pixelData`

#### Declared In

`PBBitmap.h`

### rowSizeBytes

The number of bytes per row. Always a multiple of 4 bytes.

`@property (nonatomic, readonly, assign) uint16_t rowSizeBytes`

#### Declared In

`PBBitmap.h`

### infoFlags

Bitfield of metadata flags. This corresponds to GBitmap’s `info_flags` field.

`@property (nonatomic, readonly, assign) uint16_t infoFlags`

#### Declared In

`PBBitmap.h`

### bounds

The box of bits inside [`pixelData`](#//api/name/pixelData), that contains the actual image data to use. This corresponds to GBitmap’s `bounds` field.

`@property (nonatomic, readonly, assign) GRect bounds`

#### Declared In

`PBBitmap.h`

### +&nbsp;pebbleBitmapWithUIImage:

Factory method to create a PBBitmap from a UIImage instance.

`+ (PBBitmap *)pebbleBitmapWithUIImage:(UIImage *)image`

#### Parameters
_image_The UIImage from which to create the PBBitmap

#### Declared In

`PBBitmap.h`
