# Dictionary

Source: https://developer.repebble.com/docs/c/Foundation/Dictionary/index.html

Data serialization utilities

Data residing in different parts of Pebble memory (RAM) may need to be gathered and assembled into a single continuous block for transport over the network via Bluetooth. The process of gathering and assembling this continuous block of data is called serialization.

You use data serialization utilities, like Dictionary, [Tuple](/docs/c/Foundation/Dictionary/#Tuple) and [Tuplet](/docs/c/Foundation/Dictionary/#Tuplet) data structures and accompanying functions, to accomplish this task. No transformations are performed on the actual data, however. These Pebble utilities simply help assemble the data into one continuous buffer according to a specific format.

[AppMessage](/docs/c/Foundation/AppMessage/) uses these utilities-in particular, Dictionary-to send information between mobile and Pebble watchapps.

### Writing key/value pairs

To write two key/value pairs, without using Tuplets, you would do this:

```
// Byte array + key:static const uint32\_t SOME\_DATA\_KEY = 0xb00bf00b;static const uint8\_t data[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};// CString + key:static const uint32\_t SOME\_STRING\_KEY = 0xabbababe;static const char \*string = "Hello World";// Calculate the buffer size that is needed for the final Dictionary:const uint8\_t key\_count = 2;const uint32\_t size = dict\_calc\_buffer\_size(key\_count, sizeof(data),strlen(string) + 1);// Stack-allocated buffer in which to create the Dictionary:uint8\_t buffer[size];// Iterator variable, keeps the state of the creation serialization process:DictionaryIterator iter;// Begin:dict\_write\_begin(&iter, buffer, sizeof(buffer));// Write the Data:dict\_write\_data(&iter, SOME\_DATA\_KEY, data, sizeof(data));// Write the CString:dict\_write\_cstring(&iter, SOME\_STRING\_KEY, string);// End:const uint32\_t final\_size = dict\_write\_end(&iter);// buffer now contains the serialized information
```

### Reading key/value pairs

To iterate over the key/value pairs in the dictionary that was created in the previous example code, you would do this:

```
Tuple \*tuple = dict\_read\_begin\_from\_buffer(&iter, buffer, final\_size);while (tuple) {switch (tuple-\>key) {case SOME\_DATA\_KEY:foo(tuple-\>value-\>data, tuple-\>length);break;case SOME\_STRING\_KEY:bar(tuple-\>value-\>cstring);break;}tuple = dict\_read\_next(&iter);}
```

### Tuple and Tuplet data structures

To understand the difference between [Tuple](/docs/c/Foundation/Dictionary/#Tuple) and [Tuplet](/docs/c/Foundation/Dictionary/#Tuplet) data structures: [Tuple](/docs/c/Foundation/Dictionary/#Tuple) is the header for a serialized key/value pair, while [Tuplet](/docs/c/Foundation/Dictionary/#Tuplet) is a helper data structure that references the value you want to serialize. This data structure exists to make the creation of a Dictionary easier to write. Use this mnemonic to remember the difference: TupleT(emplate), the [Tuplet](/docs/c/Foundation/Dictionary/#Tuplet) being a template to create a Dictionary with [Tuple](/docs/c/Foundation/Dictionary/#Tuple) structures.

For example:

```
Tuplet pairs[] = {TupletInteger(WEATHER\_ICON\_KEY, (uint8\_t) 1),TupletCString(WEATHER\_TEMPERATURE\_KEY, "1234 Fahrenheit"),};uint8\_t buffer[256];uint32\_t size = sizeof(buffer);dict\_serialize\_tuplets\_to\_buffer(pairs, ARRAY\_LENGTH(pairs), buffer, &size);// buffer now contains the serialized information
```

## Function Documentation

[uint32\_t](/docs/c/Standard_C/#uint32_t) dict\_calc\_buffer\_size(const uint8\_t tuple\_count, ...)

Calculates the number of bytes that a dictionary will occupy, given one or more value lengths that need to be stored in the dictionary.

##### Note

The formula to calculate the size of a Dictionary in bytes is:

```
1 + (n * 7) + D1 + ... + Dn
```
 Where `n` is the number of Tuples in the Dictionary and `Dx` are the sizes of the values in the Tuples. The size of the Dictionary header is 1 byte. The size of the header for each [Tuple](/docs/c/Foundation/Dictionary/#Tuple) is 7 bytes. 

#### Parameters
 tuple\_count

The total number of key/value pairs in the dictionary.

 ...

The sizes of each of the values that need to be stored in the dictionary.

#### Returns

The total number of bytes of storage needed.

[uint32\_t](/docs/c/Standard_C/#uint32_t) dict\_size([DictionaryIterator](/docs/c/Foundation/Dictionary/#DictionaryIterator) \* iter)

Calculates the size of data that has been written to the dictionary. AKA, the "dictionary size". Note that this is most likely different than the size of the backing storage/backing buffer.

#### Parameters
 iter

The dictionary iterator

#### Returns

The total number of bytes which have been written to the dictionary.

[DictionaryResult](/docs/c/Foundation/Dictionary/#DictionaryResult) dict\_write\_begin([DictionaryIterator](/docs/c/Foundation/Dictionary/#DictionaryIterator) \* iter, uint8\_t \*const buffer, const [uint16\_t](/docs/c/Standard_C/#uint16_t) size)

Initializes the dictionary iterator with a given buffer and size, resets and empties it, in preparation of writing key/value tuples.

#### Parameters
 iter

The dictionary iterator

 buffer

The storage of the dictionary

 size

The storage size of the dictionary

#### Returns

DICT\_OK, DICT\_NOT\_ENOUGH\_STORAGE or DICT\_INVALID\_ARGS

#### See Also
[dict\_calc\_buffer\_size](/docs/c/Foundation/Dictionary/#dict_calc_buffer_size)  
[dict\_write\_end](/docs/c/Foundation/Dictionary/#dict_write_end)

[DictionaryResult](/docs/c/Foundation/Dictionary/#DictionaryResult) dict\_write\_data([DictionaryIterator](/docs/c/Foundation/Dictionary/#DictionaryIterator) \* iter, const [uint32\_t](/docs/c/Standard_C/#uint32_t) key, const uint8\_t \*const data, const [uint16\_t](/docs/c/Standard_C/#uint16_t) size)

Adds a key with a byte array value pair to the dictionary.

##### Notes

The data will be copied into the backing storage of the dictionary.

There is _no_ checking for duplicate keys.

#### Parameters
 iter

The dictionary iterator

 key

The key

 data

Pointer to the byte array

 size

Length of the byte array

#### Returns

DICT\_OK, DICT\_NOT\_ENOUGH\_STORAGE or DICT\_INVALID\_ARGS

[DictionaryResult](/docs/c/Foundation/Dictionary/#DictionaryResult) dict\_write\_cstring([DictionaryIterator](/docs/c/Foundation/Dictionary/#DictionaryIterator) \* iter, const [uint32\_t](/docs/c/Standard_C/#uint32_t) key, const char \*const cstring)

Adds a key with a C string value pair to the dictionary.

##### Notes

The string will be copied into the backing storage of the dictionary.

There is _no_ checking for duplicate keys.

#### Parameters
 iter

The dictionary iterator

 key

The key

 cstring

Pointer to the zero-terminated C string

#### Returns

DICT\_OK, DICT\_NOT\_ENOUGH\_STORAGE or DICT\_INVALID\_ARGS

[DictionaryResult](/docs/c/Foundation/Dictionary/#DictionaryResult) dict\_write\_int([DictionaryIterator](/docs/c/Foundation/Dictionary/#DictionaryIterator) \* iter, const [uint32\_t](/docs/c/Standard_C/#uint32_t) key, const void \* integer, const uint8\_t width\_bytes, const bool is\_signed)

Adds a key with an integer value pair to the dictionary.

##### Note

There is _no_ checking for duplicate keys. [dict\_write\_int()](/docs/c/Foundation/Dictionary/#dict_write_int) is only for serializing a single integer. width\_bytes can only be 1, 2, or 4.

#### Parameters
 iter

The dictionary iterator

 key

The key

 integer

Pointer to the integer value

 width\_bytes

The width of the integer value

 is\_signed

Whether the integer's type is signed or not

#### Returns

DICT\_OK, DICT\_NOT\_ENOUGH\_STORAGE or DICT\_INVALID\_ARGS

[DictionaryResult](/docs/c/Foundation/Dictionary/#DictionaryResult) dict\_write\_uint8([DictionaryIterator](/docs/c/Foundation/Dictionary/#DictionaryIterator) \* iter, const [uint32\_t](/docs/c/Standard_C/#uint32_t) key, const uint8\_t value)

Adds a key with an unsigned, 8-bit integer value pair to the dictionary.

##### Notes

There is _no_ checking for duplicate keys.

There are counterpart functions for different signedness and widths, `dict_write_uint16()`, `dict_write_uint32()`, `dict_write_int8()`, `dict_write_int16()` and `dict_write_int32()`. The documentation is not repeated for brevity's sake.

#### Parameters
 iter

The dictionary iterator

 key

The key

 value

The unsigned, 8-bit integer value

#### Returns

DICT\_OK, DICT\_NOT\_ENOUGH\_STORAGE or DICT\_INVALID\_ARGS

[DictionaryResult](/docs/c/Foundation/Dictionary/#DictionaryResult) dict\_write\_uint16([DictionaryIterator](/docs/c/Foundation/Dictionary/#DictionaryIterator) \* iter, const [uint32\_t](/docs/c/Standard_C/#uint32_t) key, const [uint16\_t](/docs/c/Standard_C/#uint16_t) value)

[DictionaryResult](/docs/c/Foundation/Dictionary/#DictionaryResult) dict\_write\_uint32([DictionaryIterator](/docs/c/Foundation/Dictionary/#DictionaryIterator) \* iter, const [uint32\_t](/docs/c/Standard_C/#uint32_t) key, const [uint32\_t](/docs/c/Standard_C/#uint32_t) value)

[DictionaryResult](/docs/c/Foundation/Dictionary/#DictionaryResult) dict\_write\_int8([DictionaryIterator](/docs/c/Foundation/Dictionary/#DictionaryIterator) \* iter, const [uint32\_t](/docs/c/Standard_C/#uint32_t) key, const int8\_t value)

[DictionaryResult](/docs/c/Foundation/Dictionary/#DictionaryResult) dict\_write\_int16([DictionaryIterator](/docs/c/Foundation/Dictionary/#DictionaryIterator) \* iter, const [uint32\_t](/docs/c/Standard_C/#uint32_t) key, const int16\_t value)

[DictionaryResult](/docs/c/Foundation/Dictionary/#DictionaryResult) dict\_write\_int32([DictionaryIterator](/docs/c/Foundation/Dictionary/#DictionaryIterator) \* iter, const [uint32\_t](/docs/c/Standard_C/#uint32_t) key, const int32\_t value)

[uint32\_t](/docs/c/Standard_C/#uint32_t) dict\_write\_end([DictionaryIterator](/docs/c/Foundation/Dictionary/#DictionaryIterator) \* iter)

End a series of writing operations to a dictionary. This must be called before reading back from the dictionary.

#### Parameters
 iter

The dictionary iterator

#### Returns

The size in bytes of the finalized dictionary, or 0 if the parameters were invalid.

[Tuple](/docs/c/Foundation/Dictionary/#Tuple) \* dict\_read\_begin\_from\_buffer([DictionaryIterator](/docs/c/Foundation/Dictionary/#DictionaryIterator) \* iter, const uint8\_t \*const buffer, const [uint16\_t](/docs/c/Standard_C/#uint16_t) size)

Initializes the dictionary iterator with a given buffer and size, in preparation of reading key/value tuples.

#### Parameters
 iter

The dictionary iterator

 buffer

The storage of the dictionary

 size

The storage size of the dictionary

#### Returns

The first tuple in the dictionary, or NULL in case the dictionary was empty or if there was a parsing error.

[Tuple](/docs/c/Foundation/Dictionary/#Tuple) \* dict\_read\_next([DictionaryIterator](/docs/c/Foundation/Dictionary/#DictionaryIterator) \* iter)

Progresses the iterator to the next key/value pair.

#### Parameters
 iter

The dictionary iterator

#### Returns

The next tuple in the dictionary, or NULL in case the end has been reached or if there was a parsing error.

[Tuple](/docs/c/Foundation/Dictionary/#Tuple) \* dict\_read\_first([DictionaryIterator](/docs/c/Foundation/Dictionary/#DictionaryIterator) \* iter)

Resets the iterator back to the same state as a call to [dict\_read\_begin\_from\_buffer()](/docs/c/Foundation/Dictionary/#dict_read_begin_from_buffer) would do.

#### Parameters
 iter

The dictionary iterator

#### Returns

The first tuple in the dictionary, or NULL in case the dictionary was empty or if there was a parsing error.

[DictionaryResult](/docs/c/Foundation/Dictionary/#DictionaryResult) dict\_serialize\_tuplets([DictionarySerializeCallback](/docs/c/Foundation/Dictionary/#DictionarySerializeCallback) callback, void \* context, const [Tuplet](/docs/c/Foundation/Dictionary/#Tuplet) \*const tuplets, const uint8\_t tuplets\_count)

Utility function that takes a list of Tuplets from which a dictionary will be serialized, ready to transmit or store.

##### Note

The callback will be called before the function returns, so the data that that `context` points to, can be stack allocated.

#### Parameters
 callback

The callback that will be called with the serialized data of the generated dictionary.

 context

Pointer to any application specific data that gets passed into the callback.

 tuplets

An array of Tuplets that need to be serialized into the dictionary.

 tuplets\_count

The number of tuplets that follow.

#### Returns

DICT\_OK, DICT\_NOT\_ENOUGH\_STORAGE or DICT\_INVALID\_ARGS

[DictionaryResult](/docs/c/Foundation/Dictionary/#DictionaryResult) dict\_serialize\_tuplets\_to\_buffer(const [Tuplet](/docs/c/Foundation/Dictionary/#Tuplet) \*const tuplets, const uint8\_t tuplets\_count, uint8\_t \* buffer, [uint32\_t](/docs/c/Standard_C/#uint32_t) \* size\_in\_out)

Utility function that takes an array of Tuplets and serializes them into a dictionary with a given buffer and size.

#### Parameters
 tuplets

The array of tuplets

 tuplets\_count

The number of tuplets in the array

 buffer

The buffer in which to write the serialized dictionary

 size\_in\_out (in)

The available buffer size in bytes

 size\_in\_out (out)

The number of bytes written

#### Returns

DICT\_OK, DICT\_NOT\_ENOUGH\_STORAGE or DICT\_INVALID\_ARGS

[DictionaryResult](/docs/c/Foundation/Dictionary/#DictionaryResult) dict\_serialize\_tuplets\_to\_buffer\_with\_iter([DictionaryIterator](/docs/c/Foundation/Dictionary/#DictionaryIterator) \* iter, const [Tuplet](/docs/c/Foundation/Dictionary/#Tuplet) \*const tuplets, const uint8\_t tuplets\_count, uint8\_t \* buffer, [uint32\_t](/docs/c/Standard_C/#uint32_t) \* size\_in\_out)

Serializes an array of Tuplets into a dictionary with a given buffer and size.

#### Parameters
 iter

The dictionary iterator

 tuplets

The array of tuplets

 tuplets\_count

The number of tuplets in the array

 buffer

The buffer in which to write the serialized dictionary

 size\_in\_out (in)

The available buffer size in bytes

 size\_in\_out (out)

The number of bytes written

#### Returns

DICT\_OK, DICT\_NOT\_ENOUGH\_STORAGE or DICT\_INVALID\_ARGS

[DictionaryResult](/docs/c/Foundation/Dictionary/#DictionaryResult) dict\_write\_tuplet([DictionaryIterator](/docs/c/Foundation/Dictionary/#DictionaryIterator) \* iter, const [Tuplet](/docs/c/Foundation/Dictionary/#Tuplet) \*const tuplet)

Serializes a [Tuplet](/docs/c/Foundation/Dictionary/#Tuplet) and writes the resulting [Tuple](/docs/c/Foundation/Dictionary/#Tuple) into a dictionary.

#### Parameters
 iter

The dictionary iterator

 tuplet

The [Tuplet](/docs/c/Foundation/Dictionary/#Tuplet) describing the key/value pair to write

#### Returns

DICT\_OK, DICT\_NOT\_ENOUGH\_STORAGE or DICT\_INVALID\_ARGS

[uint32\_t](/docs/c/Standard_C/#uint32_t) dict\_calc\_buffer\_size\_from\_tuplets(const [Tuplet](/docs/c/Foundation/Dictionary/#Tuplet) \*const tuplets, const uint8\_t tuplets\_count)

Calculates the number of bytes that a dictionary will occupy, given one or more Tuplets that need to be stored in the dictionary.

##### Note

See [dict\_calc\_buffer\_size()](/docs/c/Foundation/Dictionary/#dict_calc_buffer_size) for the formula for the calculation.

#### Parameters
 tuplets

An array of Tuplets that need to be stored in the dictionary.

 tuplets\_count

The total number of Tuplets that follow.

#### Returns

The total number of bytes of storage needed.

#### See Also
[Tuplet](/docs/c/Foundation/Dictionary/#Tuplet)

[DictionaryResult](/docs/c/Foundation/Dictionary/#DictionaryResult) dict\_merge([DictionaryIterator](/docs/c/Foundation/Dictionary/#DictionaryIterator) \* dest, [uint32\_t](/docs/c/Standard_C/#uint32_t) \* dest\_max\_size\_in\_out, [DictionaryIterator](/docs/c/Foundation/Dictionary/#DictionaryIterator) \* source, const bool update\_existing\_keys\_only, const [DictionaryKeyUpdatedCallback](/docs/c/Foundation/Dictionary/#DictionaryKeyUpdatedCallback) key\_callback, void \* context)

Merges entries from another "source" dictionary into a "destination" dictionary. All Tuples from the source are written into the destination dictionary, while updating the exsting Tuples with matching keys.

#### Parameters
 dest

The destination dictionary to update

 dest\_max\_size\_in\_out (inout)

In: the maximum size of buffer backing `dest`. Out: the final size of the updated dictionary.

 source

The source dictionary of which its Tuples will be used to update dest.

 update\_existing\_keys\_only

Specify True if only the existing keys in `dest` should be updated.

 key\_callback

The callback that will be called for each [Tuple](/docs/c/Foundation/Dictionary/#Tuple) in the merged destination dictionary.

 context

Pointer to app specific data that will get passed in when `update_key_callback` is called.

#### Returns

DICT\_OK, DICT\_INVALID\_ARGS, DICT\_NOT\_ENOUGH\_STORAGE

[Tuple](/docs/c/Foundation/Dictionary/#Tuple) \* dict\_find(const [DictionaryIterator](/docs/c/Foundation/Dictionary/#DictionaryIterator) \* iter, const [uint32\_t](/docs/c/Standard_C/#uint32_t) key)

Tries to find a [Tuple](/docs/c/Foundation/Dictionary/#Tuple) with specified key in a dictionary.

#### Parameters
 iter

Iterator to the dictionary to search in.

 key

The key for which to find a [Tuple](/docs/c/Foundation/Dictionary/#Tuple)

#### Returns

Pointer to a found [Tuple](/docs/c/Foundation/Dictionary/#Tuple), or NULL if there was no [Tuple](/docs/c/Foundation/Dictionary/#Tuple) with the specified key.

## Data Structure Documentation

struct DictionaryIterator

An iterator can be used to iterate over the key/value tuples in an existing dictionary, using [dict\_read\_begin\_from\_buffer()](/docs/c/Foundation/Dictionary/#dict_read_begin_from_buffer), [dict\_read\_first()](/docs/c/Foundation/Dictionary/#dict_read_first) and [dict\_read\_next()](/docs/c/Foundation/Dictionary/#dict_read_next). An iterator can also be used to append key/value tuples to a dictionary, for example using [dict\_write\_data()](/docs/c/Foundation/Dictionary/#dict_write_data) or [dict\_write\_cstring()](/docs/c/Foundation/Dictionary/#dict_write_cstring).

#### Data Fields
Dictionary \* dictionary

The dictionary being iterated.

const void \* end

Points to the first memory address after the last byte of the dictionary Points to the next [Tuple](/docs/c/Foundation/Dictionary/#Tuple) in the dictionary. Given the end of the Dictionary has not yet been reached: when writing, the next key/value pair will be written at the cursor. When reading, the next call to [dict\_read\_next()](/docs/c/Foundation/Dictionary/#dict_read_next) will return the cursor.

[Tuple](/docs/c/Foundation/Dictionary/#Tuple) \* cursor

struct Tuple

Data structure for one serialized key/value tuple.

##### Note

The structure is variable length! The length depends on the value data that the tuple contains.

#### Data Fields
[uint32\_t](/docs/c/Standard_C/#uint32_t) key

The key.

[TupleType](/docs/c/Foundation/Dictionary/#TupleType) type

The type of data that the `.value` fields contains.

[uint16\_t](/docs/c/Standard_C/#uint16_t) length

The length of `.value` in bytes.

union [Tuple](/docs/c/Foundation/Dictionary/#Tuple) value

The value itself.

The different union fields are provided for convenience, avoiding the need for manual casts.

##### Notes

The array length is of incomplete length on purpose, to facilitate variable length data and because a data length of zero is valid.

**Important: The integers are little endian!**

struct Tuplet

Non-serialized, template data structure for a key/value pair. For strings and byte arrays, it only has a pointer to the actual data. For integers, it provides storage for integers up to 32-bits wide. The [Tuplet](/docs/c/Foundation/Dictionary/#Tuplet) data structure is useful when creating dictionaries from values that are already stored in arbitrary buffers. See also [Tuple](/docs/c/Foundation/Dictionary/#Tuple), with is the header of a serialized key/value pair.

#### Data Fields
[TupleType](/docs/c/Foundation/Dictionary/#TupleType) type

The type of the [Tuplet](/docs/c/Foundation/Dictionary/#Tuplet). This determines which of the struct fields in the anonymomous union are valid.

[uint32\_t](/docs/c/Standard_C/#uint32_t) key

The key.

union [Tuplet](/docs/c/Foundation/Dictionary/#Tuplet) 

Anonymous union containing the reference to the [Tuplet](/docs/c/Foundation/Dictionary/#Tuplet)'s value, being either a byte array, c-string or integer. See documentation of `.bytes`, `.cstring` and `.integer` fields.

See documentation of `.bytes`, `.cstring` and `.integer` fields.

## Enum Documentation

enum DictionaryResult

Return values for dictionary write/conversion functions.

#### Enumerators
DICT\_OK

The operation returned successfully.

DICT\_NOT\_ENOUGH\_STORAGE

There was not enough backing storage to complete the operation.

DICT\_INVALID\_ARGS

One or more arguments were invalid or uninitialized.

DICT\_INTERNAL\_INCONSISTENCY

The lengths and/or count of the dictionary its tuples are inconsistent.

DICT\_MALLOC\_FAILED

A requested operation required additional memory to be allocated, but the allocation failed, likely due to insufficient remaining heap memory.

enum TupleType

Values representing the type of data that the `value` field of a [Tuple](/docs/c/Foundation/Dictionary/#Tuple) contains.

#### Enumerators
TUPLE\_BYTE\_ARRAY

The value is an array of bytes.

TUPLE\_CSTRING

The value is a zero-terminated, UTF-8 C-string.

TUPLE\_UINT

The value is an unsigned integer. The tuple's `.length` field is used to determine the size of the integer (1, 2, or 4 bytes).

TUPLE\_INT

The value is a signed integer. The tuple's `.length` field is used to determine the size of the integer (1, 2, or 4 bytes).

## Typedef Documentation

 typedef struct Dictionary Dictionary

 typedef void(\* DictionarySerializeCallback)(const uint8\_t \*const data, const uint16\_t size, void \*context) 

Callback for [dict\_serialize\_tuplets()](/docs/c/Foundation/Dictionary/#dict_serialize_tuplets) utility.

#### Parameters
 data

The data of the serialized dictionary

 size

The size of data

 context

The context pointer as passed in to [dict\_serialize\_tuplets()](/docs/c/Foundation/Dictionary/#dict_serialize_tuplets)

#### See Also
[dict\_serialize\_tuplets](/docs/c/Foundation/Dictionary/#dict_serialize_tuplets)

 typedef void(\* DictionaryKeyUpdatedCallback)(const uint32\_t key, const Tuple \*new\_tuple, const Tuple \*old\_tuple, void \*context) 

Type of the callback used in [dict\_merge()](/docs/c/Foundation/Dictionary/#dict_merge)

#### Parameters
 key

The key that is being updated.

 new\_tuple

The new tuple. The tuple points to the actual, updated destination dictionary or NULL\_TUPLE in case there was an error (e.g. backing buffer was too small). Therefore the [Tuple](/docs/c/Foundation/Dictionary/#Tuple) can be used after the callback returns, until the destination dictionary storage is free'd (by the application itself).

 old\_tuple

The values that will be replaced with `new_tuple`. The key, value and type will be equal to the previous tuple in the old destination dictionary, however the `old_tuple points to a stack-allocated copy of the old data. @param context Pointer to application specific data The storage backing `old\_tuple` can only be used during the callback and will no longer be valid after the callback returns.

#### See Also
[dict\_merge](/docs/c/Foundation/Dictionary/#dict_merge)

## Macro Definition Documentation

#define TupletBytes ( \_key, \_data, \_length)

Macro to create a [Tuplet](/docs/c/Foundation/Dictionary/#Tuplet) with a byte array value.

#### Parameters
 \_key

The key

 \_data

Pointer to the bytes

 \_length

Length of the buffer

#define TupletCString ( \_key, \_cstring)

Macro to create a [Tuplet](/docs/c/Foundation/Dictionary/#Tuplet) with a c-string value.

#### Parameters
 \_key

The key

 \_cstring

The c-string value

#define TupletInteger ( \_key, \_integer)

Macro to create a [Tuplet](/docs/c/Foundation/Dictionary/#Tuplet) with an integer value.

#### Parameters
 \_key

The key

 \_integer

The integer value
