# Storage

Source: https://developer.repebble.com/docs/c/Foundation/Storage/index.html

A mechanism to store persistent application data and state

The Persistent Storage API provides you with a mechanism for performing a variety of tasks, like saving user settings, caching data from the phone app, or counting high scores for Pebble watchapp games.

In Pebble OS, storage is defined by a collection of fields that you can create, modify or delete. In the API, a field is specified as a key with a corresponding value.

Using the Storage API, every app is able to get its own persistent storage space. Each value in that space is associated with a [uint32\_t](/docs/c/Standard_C/#uint32_t) key.

Storage supports saving integers, strings and byte arrays. The maximum size of byte arrays and strings is defined by PERSIST\_DATA\_MAX\_LENGTH (currently set to 256 bytes). You call the function persist\_exists(key), which returns a boolean indicating if the key exists or not. The Storage API enables your app to save its state, and when compared to using [AppMessage](/docs/c/Foundation/AppMessage/) to retrieve values from the phone, it provides you with a much faster way to restore state. In addition, it draws less power from the battery.

Note that the size of all persisted values cannot exceed 4K per app.

## Function Documentation

bool persist\_exists(const [uint32\_t](/docs/c/Standard_C/#uint32_t) key)

Checks whether a value has been set for a given key in persistent storage.

#### Parameters
 key

The key of the field to check.

#### Returns

true if a value exists, otherwise false.

int persist\_get\_size(const [uint32\_t](/docs/c/Standard_C/#uint32_t) key)

Gets the size of a value for a given key in persistent storage.

#### Parameters
 key

The key of the field to lookup the data size.

#### Returns

The size of the value in bytes or E\_DOES\_NOT\_EXIST if there is no field matching the given key.

bool persist\_read\_bool(const [uint32\_t](/docs/c/Standard_C/#uint32_t) key)

Reads a bool value for a given key from persistent storage. If the value has not yet been set, this will return false.

#### Parameters
 key

The key of the field to read from.

#### Returns

The bool value of the key to read from.

int32\_t persist\_read\_int(const [uint32\_t](/docs/c/Standard_C/#uint32_t) key)

Reads an int value for a given key from persistent storage.

##### Note

The int is a signed 32-bit integer. If the value has not yet been set, this will return 0.

#### Parameters
 key

The key of the field to read from.

#### Returns

The int value of the key to read from.

int persist\_read\_data(const [uint32\_t](/docs/c/Standard_C/#uint32_t) key, void \* buffer, const [size\_t](/docs/c/Standard_C/Memory/#size_t) buffer\_size)

Reads a blob of data for a given key from persistent storage into a given buffer. If the value has not yet been set, the given buffer is left unchanged.

#### Parameters
 key

The key of the field to read from.

 buffer

The pointer to a buffer to be written to.

 buffer\_size

The maximum size of the given buffer.

#### Returns

The number of bytes written into the buffer or E\_DOES\_NOT\_EXIST if there is no field matching the given key.

int persist\_read\_string(const [uint32\_t](/docs/c/Standard_C/#uint32_t) key, char \* buffer, const [size\_t](/docs/c/Standard_C/Memory/#size_t) buffer\_size)

Reads a string for a given key from persistent storage into a given buffer. The string will be null terminated. If the value has not yet been set, the given buffer is left unchanged.

#### Parameters
 key

The key of the field to read from.

 buffer

The pointer to a buffer to be written to.

 buffer\_size

The maximum size of the given buffer. This includes the null character.

#### Returns

The number of bytes written into the buffer or E\_DOES\_NOT\_EXIST if there is no field matching the given key.

[status\_t](/docs/c/Foundation/Storage/#status_t) persist\_write\_bool(const [uint32\_t](/docs/c/Standard_C/#uint32_t) key, const bool value)

Writes a bool value flag for a given key into persistent storage.

#### Parameters
 key

The key of the field to write to.

 value

The boolean value to write.

#### Returns

The number of bytes written if successful, a value from [StatusCode](/docs/c/Foundation/Storage/#StatusCode) otherwise.

[status\_t](/docs/c/Foundation/Storage/#status_t) persist\_write\_int(const [uint32\_t](/docs/c/Standard_C/#uint32_t) key, const int32\_t value)

Writes an int value for a given key into persistent storage.

##### Note

The int is a signed 32-bit integer.

#### Parameters
 key

The key of the field to write to.

 value

The int value to write.

#### Returns

The number of bytes written if successful, a value from [StatusCode](/docs/c/Foundation/Storage/#StatusCode) otherwise.

int persist\_write\_data(const [uint32\_t](/docs/c/Standard_C/#uint32_t) key, const void \* data, const [size\_t](/docs/c/Standard_C/Memory/#size_t) size)

Writes a blob of data of a specified size in bytes for a given key into persistent storage. The maximum size is [PERSIST\_DATA\_MAX\_LENGTH](/docs/c/Foundation/Storage/#PERSIST_DATA_MAX_LENGTH).

#### Parameters
 key

The key of the field to write to.

 data

The pointer to the blob of data.

 size

The size in bytes.

#### Returns

The number of bytes written if successful, a value from [StatusCode](/docs/c/Foundation/Storage/#StatusCode) otherwise.

int persist\_write\_string(const [uint32\_t](/docs/c/Standard_C/#uint32_t) key, const char \* cstring)

Writes a string a given key into persistent storage. The maximum size is [PERSIST\_STRING\_MAX\_LENGTH](/docs/c/Foundation/Storage/#PERSIST_STRING_MAX_LENGTH) including the null terminator.

#### Parameters
 key

The key of the field to write to.

 cstring

The pointer to null terminated string.

#### Returns

The number of bytes written if successful, a value from [StatusCode](/docs/c/Foundation/Storage/#StatusCode) otherwise.

- [SDK 3](javascript:void(0);)
- [SDK 4](javascript:void(0);)
- [SDK 4.9+](javascript:void(0);)

[status\_t](/docs/c/Foundation/Storage/#status_t) persist\_delete(const [uint32\_t](/docs/c/Standard_C/#uint32_t) key)

Deletes the value of a key from persistent storage.

#### Parameters
 key

The key of the field to delete from.

[status\_t](/docs/c/Foundation/Storage/#status_t) persist\_delete(const [uint32\_t](/docs/c/Standard_C/#uint32_t) key)

Deletes the value of a key from persistent storage.

#### Parameters
 key

The key of the field to delete from.

[status\_t](/docs/c/Foundation/Storage/#status_t) persist\_delete(const [uint32\_t](/docs/c/Standard_C/#uint32_t) key)

Deletes the value of a key from persistent storage.

#### Parameters
 key

The key of the field to delete from.

#### Returns

S\_TRUE if successful, E\_DOES\_NOT\_EXIST if a value was not set, or another error value from [StatusCode](/docs/c/Foundation/Storage/#StatusCode).

## Enum Documentation

enum StatusCode

Status codes. See [status\_t](/docs/c/Foundation/Storage/#status_t).

#### Enumerators
S\_SUCCESS

Operation completed successfully.

E\_ERROR

An error occurred (no description).

E\_UNKNOWN

No idea what went wrong.

E\_INTERNAL

There was a generic internal logic error.

E\_INVALID\_ARGUMENT

The function was not called correctly.

E\_OUT\_OF\_MEMORY

Insufficient allocatable memory available.

E\_OUT\_OF\_STORAGE

Insufficient long-term storage available.

E\_OUT\_OF\_RESOURCES

Insufficient resources available.

E\_RANGE

Argument out of range (may be dynamic).

E\_DOES\_NOT\_EXIST

Target of operation does not exist.

E\_INVALID\_OPERATION

Operation not allowed (may depend on state).

E\_BUSY

Another operation prevented this one.

E\_AGAIN

Operation not completed; try again.

S\_TRUE

Equivalent of boolean true.

S\_FALSE

Equivalent of boolean false.

S\_NO\_MORE\_ITEMS

For list-style requests. At end of list.

S\_NO\_ACTION\_REQUIRED

No action was taken as none was required.

## Typedef Documentation

 typedef int32\_t status\_t

Return value for system operations. See [StatusCode](/docs/c/Foundation/Storage/#StatusCode) for possible values.

## Macro Definition Documentation

#define PERSIST\_DATA\_MAX\_LENGTH 256

The maximum size of a persist value in bytes.

#define PERSIST\_STRING\_MAX\_LENGTH [PERSIST\_DATA\_MAX\_LENGTH](/docs/c/Foundation/Storage/#PERSIST_DATA_MAX_LENGTH)

The maximum size of a persist string in bytes including the NULL terminator.
