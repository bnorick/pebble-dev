# Memory

Source: https://developer.repebble.com/docs/c/Standard_C/Memory/index.html

Standard memory functions.

## Function Documentation

void \* malloc([size\_t](/docs/c/Standard_C/Memory/#size_t) size)

Allocates a requested amount of memory.

#### Parameters
 size

The number of bytes to allocate

#### Returns

A pointer to the allocated memory or NULL on error.

void \* calloc([size\_t](/docs/c/Standard_C/Memory/#size_t) count, [size\_t](/docs/c/Standard_C/Memory/#size_t) size)

Allocates space for count objects that are size bytes and fills the memory with bytes of value 0.

#### Parameters
 count

The number of objects to allocate space for

 size

The size of the object type being allocated

#### Returns

A pointer to the allocated memory or NULL on error.

void \* realloc(void \* ptr, [size\_t](/docs/c/Standard_C/Memory/#size_t) size)

Takes the memory allocated at ptr and changes the length of its allocation to the size specified.

Copies the smaller of the length of the original allocation or the new size into the newly allocated buffer.

#### Parameters
 ptr

The memory allocation to be changed

 size

The size to change the ptr allocation to

#### Returns

A pointer to the new allocated memory or NULL on error

void free(void \* ptr)

Frees previously allocated memory.

#### Parameters
 ptr

The memory buffer to free.

int memcmp(const void \* ptr1, const void \* ptr2, [size\_t](/docs/c/Standard_C/Memory/#size_t) n)

Compares the first n bytes of memory regions ptr1 and ptr2.

#### Parameters
 ptr1

The pointer to the first memory region to compare

 ptr2

The pointer to the second memory region to compare

 n

The number of bytes to compare

#### Returns

0 if the first n bytes of ptr1 and ptr 2 match. Otherwise, the sign is determined by the sign of the difference between the first pair of bytes that differ in ptr1 and ptr2.

void \* memcpy(void \* dest, const void \* src, [size\_t](/docs/c/Standard_C/Memory/#size_t) n)

Copies n bytes from src to dest.

#### Parameters
 dest

The pointer to the destination memory region

 src

The pointer to the source memory region

 n

The number of bytes to copy

void \* memmove(void \* dest, const void \* src, [size\_t](/docs/c/Standard_C/Memory/#size_t) n)

Copies n bytes from src to dest by first copying to a temporary area first, allowing dest and src to potentially overlap.

This can be used to move data to a location that overlaps its previous location.

#### Parameters
 dest

The pointer to the destination memory region

 src

The pointer to the source memory region

 n

The number of bytes to copy

void \* memset(void \* dest, int c, [size\_t](/docs/c/Standard_C/Memory/#size_t) n)

Sets n bytes to c starting at dest.

This can be used to clear a memory region for example if c is 0.

#### Parameters
 dest

The pointer to the destination memory region

 c

The integer used as an unsigned char to assign to each byte

 n

The number of bytes to set

## Typedef Documentation

 typedef unsigned int size\_t

size as an unsigned integer
