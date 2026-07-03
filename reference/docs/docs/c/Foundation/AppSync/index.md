# AppSync

Source: https://developer.repebble.com/docs/c/Foundation/AppSync/index.html

UI synchronization layer for AppMessage

AppSync is a convenience layer that resides on top of [AppMessage](/docs/c/Foundation/AppMessage/), and serves as a UI synchronization layer for AppMessage. In so doing, AppSync makes it easier to drive the information displayed in the watchapp UI with messages sent by a phone app.

AppSync maintains and updates a Dictionary, and provides your app with a callback ([AppSyncTupleChangedCallback](/docs/c/Foundation/AppSync/#AppSyncTupleChangedCallback)) routine that is called whenever the Dictionary changes and the app's UI is updated. Note that the app UI is not updated automatically. To update the UI, you need to implement the callback.

Pebble OS provides support for data serialization utilities, like Dictionary, [Tuple](/docs/c/Foundation/Dictionary/#Tuple) and [Tuplet](/docs/c/Foundation/Dictionary/#Tuplet) data structures and their accompanying functions. You use Tuplets to create a Dictionary with [Tuple](/docs/c/Foundation/Dictionary/#Tuple) structures.

AppSync manages the storage and bookkeeping chores of the current [Tuple](/docs/c/Foundation/Dictionary/#Tuple) values. AppSync copies incoming AppMessage Tuples into this "current" Dictionary, so that the key/values remain available for the UI to use. For example, it is safe to use a C-string value provided by AppSync and use it directly in a [text\_layer\_set\_text()](/docs/c/User_Interface/Layers/TextLayer/#text_layer_set_text) call.

Your app needs to supply the buffer that AppSync uses for the "current" Dictionary when initializing AppSync.

Refer to the [Synchronizing App UI](https://developer.getpebble.com/guides/pebble-apps/communications/appsync/) guide for a conceptual overview and code usage.

## Function Documentation

void app\_sync\_init(struct AppSync \* s, uint8\_t \* buffer, const [uint16\_t](/docs/c/Standard_C/#uint16_t) buffer\_size, const [Tuplet](/docs/c/Foundation/Dictionary/#Tuplet) \*const keys\_and\_initial\_values, const uint8\_t count, [AppSyncTupleChangedCallback](/docs/c/Foundation/AppSync/#AppSyncTupleChangedCallback) tuple\_changed\_callback, [AppSyncErrorCallback](/docs/c/Foundation/AppSync/#AppSyncErrorCallback) error\_callback, void \* context)

Initialized an AppSync system with specific buffer size and initial keys and values. The `callback.value_changed` callback will be called **asynchronously** with the initial keys and values, as to avoid duplicating code to update your app's UI.

##### Note

Only updates for the keys specified in this initial array will be accepted by AppSync, updates for other keys that might come in will just be ignored.

#### Parameters
 s

The AppSync context to initialize

 buffer

The buffer that AppSync should use

 buffer\_size

The size of the backing storage of the "current" dictionary. Use [dict\_calc\_buffer\_size\_from\_tuplets()](/docs/c/Foundation/Dictionary/#dict_calc_buffer_size_from_tuplets) to estimate the size you need.

 keys\_and\_initial\_values

An array of Tuplets with the initial keys and values.

 count

The number of Tuplets in the `keys_and_initial_values` array.

 tuple\_changed\_callback

The callback that will handle changed key/value pairs

 error\_callback

The callback that will handle errors

 context

Pointer to app specific data that will get passed into calls to the callbacks

void app\_sync\_deinit(struct AppSync \* s)

Cleans up an AppSync system. It frees the buffer allocated by an [app\_sync\_init()](/docs/c/Foundation/AppSync/#app_sync_init) call and deregisters itself from the [AppMessage](/docs/c/Foundation/AppMessage/) subsystem.

#### Parameters
 s

The AppSync context to deinit.

[AppMessageResult](/docs/c/Foundation/AppMessage/#AppMessageResult) app\_sync\_set(struct AppSync \* s, const [Tuplet](/docs/c/Foundation/Dictionary/#Tuplet) \*const keys\_and\_values\_to\_update, const uint8\_t count)

Updates key/value pairs using an array of Tuplets.

##### Note

The call will attempt to send the updated keys and values to the application on the other end. Only after the other end has acknowledged the update, the `.value_changed` callback will be called to confirm the update has completed and your application code can update its user interface.

#### Parameters
 s

The AppSync context

 keys\_and\_values\_to\_update

An array of Tuplets with the keys and values to update. The data in the Tuplets are copied during the call, so the array can be stack-allocated.

 count

The number of Tuplets in the `keys_and_values_to_update` array.

#### Returns

The result code from the [AppMessage](/docs/c/Foundation/AppMessage/) subsystem. Can be APP\_MSG\_OK, APP\_MSG\_BUSY or APP\_MSG\_INVALID\_ARGS

const [Tuple](/docs/c/Foundation/Dictionary/#Tuple) \* app\_sync\_get(const struct AppSync \* s, const [uint32\_t](/docs/c/Standard_C/#uint32_t) key)

Finds and gets a tuple in the "current" dictionary.

#### Parameters
 s

The AppSync context

 key

The key for which to find a [Tuple](/docs/c/Foundation/Dictionary/#Tuple)

#### Returns

Pointer to a found [Tuple](/docs/c/Foundation/Dictionary/#Tuple), or NULL if there was no [Tuple](/docs/c/Foundation/Dictionary/#Tuple) with the specified key.

## Data Structure Documentation

struct AppSync

#### Data Fields
[DictionaryIterator](/docs/c/Foundation/Dictionary/#DictionaryIterator) current\_iterunion AppSync [uint16\_t](/docs/c/Standard_C/#uint16_t) buffer\_sizestruct AppSync callback

## Typedef Documentation

 typedef void(\* AppSyncTupleChangedCallback)(const uint32\_t key, const Tuple \*new\_tuple, const Tuple \*old\_tuple, void \*context) 

Called whenever a [Tuple](/docs/c/Foundation/Dictionary/#Tuple) changes. This does not necessarily mean the value in the [Tuple](/docs/c/Foundation/Dictionary/#Tuple) has changed. When the internal "current" dictionary gets updated, existing Tuples might get shuffled around in the backing buffer, even though the values stay the same. In this callback, the client code gets the chance to remove the old reference and start using the new one. In this callback, your application MUST clean up any references to the `old_tuple` of a PREVIOUS call to this callback (and replace it with the `new_tuple` that is passed in with the current call).

#### Parameters
 key

The key for which the [Tuple](/docs/c/Foundation/Dictionary/#Tuple) was changed.

 new\_tuple

The new tuple. The tuple points to the actual, updated "current" dictionary, as backed by the buffer internal to the AppSync struct. Therefore the [Tuple](/docs/c/Foundation/Dictionary/#Tuple) can be used after the callback returns, until the AppSync is deinited. In case there was an error (e.g. storage shortage), this `new_tuple` can be `NULL_TUPLE`.

 old\_tuple

The values that will be replaced with `new_tuple`. The key, value and type will be equal to the previous tuple in the old destination dictionary; however, the `old_tuple` points to a stack-allocated copy of the old data. This value will be `NULL_TUPLE` when the initial values are being set.

 context

Pointer to application specific data, as set using [app\_sync\_init()](/docs/c/Foundation/AppSync/#app_sync_init)

#### See Also
[app\_sync\_init()](/docs/c/Foundation/AppSync/#app_sync_init)

 typedef void(\* AppSyncErrorCallback)(DictionaryResult dict\_error, AppMessageResult app\_message\_error, void \*context) 

Called whenever there was an error.

#### Parameters
 dict\_error

The dictionary result error code, if the error was dictionary related.

 app\_message\_error

The app\_message result error code, if the error was app\_message related.

 context

Pointer to application specific data, as set using [app\_sync\_init()](/docs/c/Foundation/AppSync/#app_sync_init)

#### See Also
[app\_sync\_init()](/docs/c/Foundation/AppSync/#app_sync_init)
