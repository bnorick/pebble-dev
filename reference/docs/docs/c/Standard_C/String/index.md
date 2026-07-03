# String

Source: https://developer.repebble.com/docs/c/Standard_C/String/index.html

Standard C-string manipulation.

## Function Documentation

int strcmp(const char \* str1, const char \* str2)

Compares the null terminated strings str1 and str2 to each other.

#### Parameters
 str1

The first C string to compare

 str2

The second C string to compare

#### Returns

The difference of the first differing pair of bytes or 0 if the strings are identical

int strncmp(const char \* str1, const char \* str2, [size\_t](/docs/c/Standard_C/Memory/#size_t) n)

Compares the null terminated strings str1 and str2 to each other for up to n bytes.

Comparison ends when a null is read or when n bytes are read, whichever happens first.

#### Parameters
 str1

The first C string to compare

 str2

The second C string to compare

 n

The maximum number of bytes to compare

#### Returns

The difference of the first differing pair of bytes or the final pair of bytes read or 0 if the portions of the strings read are identical

char \* strcpy(char \* dest, const char \* src)

Copies the string in src into dest and null terminates dest.

There should be no overlap of dest and src in memory.

#### Parameters
 dest

The destination buffer with enough space for src

 src

The source C string

#### Returns

The destination buffer dest

char \* strncpy(char \* dest, const char \* src, [size\_t](/docs/c/Standard_C/Memory/#size_t) n)

Copies up to n bytes from the string in src into dest and null terminates dest.

If dest is null terminated before n bytes have been written, null bytes will continue to be written until n bytes total were written. There should be no overlap of dest and src in memory.

#### Parameters
 dest

The destination buffer with enough space for n bytes

 src

The source string

 n

The number of bytes to copy

#### Returns

The destination buffer dest

char \* strcat(char \* dest, const char \* src)

Concatenates the string in src to the end of the string pointed by dest and null terminates dest.

There should be no overlap of dest and src.

#### Parameters
 dest

The destination buffer with enough space for src beyond the null character

 src

The source C string

#### Returns

The destination buffer dest

char \* strncat(char \* dest, const char \* src, [size\_t](/docs/c/Standard_C/Memory/#size_t) n)

Concatenates up to n bytes from the string in src to the end of the string pointed by dest and null terminates dest.

There should be no overlap of dest and src in memeory.

#### Parameters
 dest

The destination buffer with enough space for src beyond the null character

 src

The source string

 n

The maximum number of bytes to copy

#### Returns

The destination buffer dest

[size\_t](/docs/c/Standard_C/Memory/#size_t) strlen(const char \* str)

Calculates the length of a null terminated string.

#### Parameters
 str

The C string.

#### Returns

The length of the C string str.
