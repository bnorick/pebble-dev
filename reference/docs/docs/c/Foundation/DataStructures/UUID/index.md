# UUID

Source: https://developer.repebble.com/docs/c/Foundation/DataStructures/UUID/index.html

## Function Documentation

bool uuid\_equal(const Uuid \* uu1, const Uuid \* uu2)

Compares two UUIDs.

#### Returns

True if the two UUIDs are equal, false if they are not.

void uuid\_to\_string(const Uuid \* uuid, char \* buffer)

Writes UUID in a string form into buffer that looks like the following... {12345678-1234-5678-1234-567812345678} or {NULL UUID} if NULL was passed.

#### Parameters
 uuid

The Uuid to write into the buffer as human-readable string

 buffer

Memory to write the string to. Must be at least [UUID\_STRING\_BUFFER\_LENGTH](/docs/c/Foundation/DataStructures/UUID/#UUID_STRING_BUFFER_LENGTH) bytes long.

## Data Structure Documentation

struct Uuid

#### Data Fields
uint8\_t byte0uint8\_t byte1uint8\_t byte2uint8\_t byte3uint8\_t byte4uint8\_t byte5uint8\_t byte6uint8\_t byte7uint8\_t byte8uint8\_t byte9uint8\_t byte10uint8\_t byte11uint8\_t byte12uint8\_t byte13uint8\_t byte14uint8\_t byte15

## Macro Definition Documentation

#define UUID\_SIZE 16

#define UuidMake ( p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15)

Make a Uuid object from sixteen bytes.

#### Returns

A Uuid structure representing the bytes p0 to p15.

#define UuidMakeFromBEBytes ( b)

Creates a Uuid from an array of bytes with 16 bytes in Big Endian order.

#### Returns

The created Uuid

#define UuidMakeFromLEBytes ( b)

Creates a Uuid from an array of bytes with 16 bytes in Little Endian order.

#### Returns

The created Uuid

#define UUID\_STRING\_BUFFER\_LENGTH (32 + 4 + 2 + 1)

The minimum required length of a string used to hold a uuid (including null).
