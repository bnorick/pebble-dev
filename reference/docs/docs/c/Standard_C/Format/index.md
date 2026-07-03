# Format

Source: https://developer.repebble.com/docs/c/Standard_C/Format/index.html

Standard formatting.

If you're looking for input/output functions, check out the [Logging](/docs/c/Foundation/Logging/) API.

## Function Documentation

int snprintf(char \* str, [size\_t](/docs/c/Standard_C/Memory/#size_t) n, const \* fmt, ...)

Format a string into a buffer.

The Pebble-supported format specifiers are displayed below.

| Specifier | Output | Example |
| --- | --- | --- |
| d or i | Signed decimal integer | 294  
 |
| u | Unsigned decimal integer | 7235 |
| o | Unsigned octal | 610 |
| x | Unsigned hexadecimal integer | 8b2 |
| X | Unsigned hexadecimal integer (uppercase) | 8B2 |
| c | Character | h |
| s | Null-terminated string of characters | pebble |
| p | Pointer address | 0xb8000000 |
| % | A % followed by another % character will write a single % to the stream. | % |
  

Length specifiers can also be combined with the format specifiers above:

| | u o x X | c | s | p | n |
| --- | --- | --- | --- | --- | --- |
| (none) | unsigned int | int | char\* | void\* | int\* |
| h | unsigned short int | | | | short int\* |
| l | unsigned long int | wint\_t | wchar\_t\* | | long int\* |

#### Parameters
 str

The string buffer to write the formatted string into

 n

The maximum size of the buffer

 fmt

The C formatting string

#### Returns

The number of bytes written
