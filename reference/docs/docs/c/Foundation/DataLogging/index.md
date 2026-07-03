# DataLogging

Source: https://developer.repebble.com/docs/c/Foundation/DataLogging/index.html

Enables logging data asynchronously to a mobile app

In Pebble OS, data logging is a data storage and transfer subsystem that allows watchapps to save data on non-volatile storage devices when the phone is not available to process it. The API provides your watchapp with a mechanism for short-term data buffering for asynchronous data transmission to a mobile app.

Using this API, your Pebble watchapp can create an arbitrary number of logs, but you’re limited in the amount of storage space you can use. Note that approximately 640K is available for data logging, which is shared among all watchapps that use it. This value is subject to change in the future. When the data spool is full, an app will start overwriting its own data. An app cannot overwrite another apps's data. However, the other app might have 0 bytes for data logging.

Your app can log data to a session. Every new block of data is appended to the session. The data is then sent to the associated phone application at the earliest convenience. If a phone is available, the data is sent directly to the phone. Otherwise, it is saved to the watch storage until the watch is connected to a phone.

For example:

To create a data logging session for 4-byte unsigned integers with a tag of 0x1234, you would do this:

```
DataLoggingSessionRef logging\_session = data\_logging\_create(0x1234, DATA\_LOGGING\_UINT, 4,false);// Fake creating some data and logging it to the session.uint32\_t data[] = { 1, 2, 3};data\_logging\_log(logging\_session, &data, 3);// Fake creating more data and logging that as well.uint32\_t data2[] = { 1, 2 };data\_logging\_log(logging\_session, &data, 2);// When we don't need to log anything else, we can close off the session.data\_logging\_finish(logging\_session);
```

## Function Documentation

DataLoggingSessionRef data\_logging\_create([uint32\_t](/docs/c/Standard_C/#uint32_t) tag, [DataLoggingItemType](/docs/c/Foundation/DataLogging/#DataLoggingItemType) item\_type, [uint16\_t](/docs/c/Standard_C/#uint16_t) item\_length, bool resume)

Create a new data logging session.

#### Parameters
 tag

A tag associated with the logging session.

 item\_type

The type of data stored in this logging session

 item\_length

The size of a single data item in bytes

 resume

True if we want to look for a logging session of the same tag and resume logging to it. If this is false and a session with the specified tag exists, that session will be closed and a new session will be opened.

#### Returns

An opaque reference to the data logging session

void data\_logging\_finish(DataLoggingSessionRef logging\_session)

Finish up a data logging\_session. Logging data is kept until it has successfully been transferred over to the phone, but no data may be added to the session after this function is called.

#### Parameters
 logging\_session

a reference to the data logging session previously allocated using data\_logging\_create

[DataLoggingResult](/docs/c/Foundation/DataLogging/#DataLoggingResult) data\_logging\_log(DataLoggingSessionRef logging\_session, const void \* data, [uint32\_t](/docs/c/Standard_C/#uint32_t) num\_items)

Add data to the data logging session. If a phone is available, the data is sent directly to the phone. Otherwise, it is saved to the watch storage until the watch is connected to a phone.

#### Parameters
 logging\_session

a reference to the data logging session you want to add the data to

 data

a pointer to the data buffer that contains multiple items

 num\_items

the number of items to log. This means data must be at least (num\_items \* item\_length) long in bytes

#### Returns

DATA\_LOGGING\_SUCCESS on success

DATA\_LOGGING\_NOT\_FOUND if the logging session is invalid

DATA\_LOGGING\_CLOSED if the sesion is not active

DATA\_LOGGING\_BUSY if the sesion is not available for writing

DATA\_LOGGING\_INVALID\_PARAMS if num\_items is 0 or data is NULL

## Enum Documentation

enum DataLoggingItemType

The different types of session data that Pebble supports. This type describes the type of a singular item in the data session. Every item in a given session is the same type and size.

#### Enumerators
DATA\_LOGGING\_BYTE\_ARRAY

Array of bytes. Remember that this is the type of a single item in the logging session, so using this type means you'll be logging multiple byte arrays (each a fixed length described by item\_length) for the duration of the session.

DATA\_LOGGING\_UINT

Unsigned integer. This may be a 1, 2, or 4 byte integer depending on the item\_length parameter.

DATA\_LOGGING\_INT

Signed integer. This may be a 1, 2, or 4 byte integer depending on the item\_length parameter.

enum DataLoggingResult

Enumerated values describing the possible outcomes of data logging operations.

#### Enumerators
DATA\_LOGGING\_SUCCESS

Successful operation.

DATA\_LOGGING\_BUSY

Someone else is writing to this logging session.

DATA\_LOGGING\_FULL

No more space to save data.

DATA\_LOGGING\_NOT\_FOUND

The logging session does not exist.

DATA\_LOGGING\_CLOSED

The logging session was made inactive.

DATA\_LOGGING\_INVALID\_PARAMS

An invalid parameter was passed to one of the functions.

DATA\_LOGGING\_INTERNAL\_ERR

An internal error occurred.

## Typedef Documentation

 typedef void \* DataLoggingSessionRef
