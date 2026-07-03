# NSNumber(PBStandardIntegerExtensions) Category Reference

Source: https://developer.repebble.com/docs/pebblekit-ios/Categories/NSNumber+PBStandardIntegerExtensions/

| Declared in | NSNumber+stdint.h |

## Overview

This category exposes the capabilities the underlying CFNumber to explicitely store the signedness and the width of the storage.

### pb\_uint32Value

Interprets the receiver as a 32-bits wide, unsigned integer.

`@property (readonly) uint32_t pb_uint32Value`

#### Declared In

`NSNumber+stdint.h`

### pb\_uint16Value

Interprets the receiver as a 16-bits wide, unsigned integer.

`@property (readonly) uint16_t pb_uint16Value`

#### Declared In

`NSNumber+stdint.h`

### pb\_uint8Value

Interprets the receiver as a 8-bits wide, unsigned integer.

`@property (readonly) uint8_t pb_uint8Value`

#### Declared In

`NSNumber+stdint.h`

### pb\_int32Value

Interprets the receiver as a 32-bits wide, signed integer.

`@property (readonly) int32_t pb_int32Value`

#### Declared In

`NSNumber+stdint.h`

### pb\_int16Value

Interprets the receiver as a 16-bits wide, signed integer.

`@property (readonly) int16_t pb_int16Value`

#### Declared In

`NSNumber+stdint.h`

### pb\_int8Value

Interprets the receiver as a 8-bits wide, signed integer.

`@property (readonly) int8_t pb_int8Value`

#### Declared In

`NSNumber+stdint.h`

### pb\_float

Gets whether the number that is stored by the receiver should be interpreted as a floating pointer number or not.

`@property (readonly, getter=pb_isFloat) BOOL pb_float`

#### Declared In

`NSNumber+stdint.h`

### pb\_signed

Gets whether the number that is stored by the receiver should be interpreted as a signed integer or not.

`@property (readonly, getter=pb_isSigned) BOOL pb_signed`

#### Declared In

`NSNumber+stdint.h`

### pb\_byteWidth

Gets the width in bytes of the integer that is stored by the receiver.

`@property (readonly) uint8_t pb_byteWidth`

#### Declared In

`NSNumber+stdint.h`

### +&nbsp;pb\_numberWithUint32:

Creates an NSNumber with a 32-bits wide, unsigned integer.

`+ (NSNumber *)pb_numberWithUint32:(uint32_t)value`

#### Parameters
_value_The value for the created number.

#### Declared In

`NSNumber+stdint.h`

### +&nbsp;pb\_numberWithUint16:

Creates an NSNumber with a 16-bits wide, unsigned integer.

`+ (NSNumber *)pb_numberWithUint16:(uint16_t)value`

#### Parameters
_value_The value for the created number.

#### Declared In

`NSNumber+stdint.h`

### +&nbsp;pb\_numberWithUint8:

Creates an NSNumber with a 8-bits wide, unsigned integer.

`+ (NSNumber *)pb_numberWithUint8:(uint8_t)value`

#### Parameters
_value_The value for the created number.

#### Declared In

`NSNumber+stdint.h`

### +&nbsp;pb\_numberWithInt32:

Creates an NSNumber with a 32-bits wide, signed integer.

`+ (NSNumber *)pb_numberWithInt32:(int32_t)value`

#### Parameters
_value_The value for the created number.

#### Declared In

`NSNumber+stdint.h`

### +&nbsp;pb\_numberWithInt16:

Creates an NSNumber with a 16-bits wide, signed integer.

`+ (NSNumber *)pb_numberWithInt16:(int16_t)value`

#### Parameters
_value_The value for the created number.

#### Declared In

`NSNumber+stdint.h`

### +&nbsp;pb\_numberWithInt8:

Creates an NSNumber with a 8-bits wide, signed integer.

`+ (NSNumber *)pb_numberWithInt8:(int8_t)value`

#### Parameters
_value_The value for the created number.

#### Declared In

`NSNumber+stdint.h`
