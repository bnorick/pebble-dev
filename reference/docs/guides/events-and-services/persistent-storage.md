# Persistent Storage

Source: https://developer.repebble.com/guides/events-and-services/persistent-storage/

Developers can use the [`Storage`](/docs/c/Foundation/Storage/ "Storage") API to persist multiple types of data between app launches, enabling apps to remember information previously entered by the user. A common use-case of this API is to enable the app to remember configuration data chosen in an app's configuration page, removing the tedious need to enter the information on the phone every time the watchapp is launched. Other use cases include to-to lists, stat trackers, game highscores etc.

Read [_App Configuration_](/guides/user-interfaces/app-configuration.md) for more information on implementing an app configuration page.

## Persistent Storage Model

Every app is allocated 4 kB of persistent storage space and can write values to storage using a key, similar to [`AppMessage`](/docs/c/Foundation/AppMessage/ "AppMessage") dictionaries or the web`localStorage` API. To recall values, the app simply queries the API using the associated key . Keys are specified in the `uint32_t` type, and each value can have a size up to [`PERSIST_DATA_MAX_LENGTH`](/docs/c/Foundation/Storage/#PERSIST_DATA_MAX_LENGTH "PERSIST\_DATA\_MAX\_LENGTH") (currently 256 bytes).

When an app is updated the values saved using the [`Storage`](/docs/c/Foundation/Storage/ "Storage") API will be persisted, but if it is uninstalled they will be removed.

Apps that make large use of the [`Storage`](/docs/c/Foundation/Storage/ "Storage") API may experience small pauses due to underlying housekeeping operations. Therefore it is recommended to read and write values when an app is launching or exiting, or during a time the user is waiting for some other action to complete.

## Types of Data

Values can be stored as boolean, integer, string, or arbitrary data structure types. Before retrieving a value, the app should check that it has been previously persisted. If it has not, a default value should be chosen as appropriate.

```
uint32\_t key = 0;int num\_items = 0;if (persist\_exists(key)) {// Read persisted valuenum\_items = persist\_read\_int(key);} else {// Choose a default valuenum\_items = 10;// Remember the default value until the user chooses their own valuepersist\_write\_int(key, num\_items);}
```

The API provides a 'read' and 'write' function for each of these types, with builtin data types retrieved through assignment, and complex ones into a buffer provided by the app. Examples of each are shown below.

### Booleans

```
uint32\_t key = 0;bool large\_font\_size = true;
```

```
// Write a boolean valuepersist\_write\_bool(key, large\_font\_size);
```

```
// Read the boolean valuebool large\_font\_size = persist\_read\_bool(key);
```

### Integers

```
uint32\_t key = 1;int highscore = 432;
```

```
// Write an integerpersist\_write\_int(key, highscore);
```

```
// Read the integer valueint highscore = persist\_read\_int(key);
```

### Strings

```
uint32\_t key = 2;char \*string = "Remember this!";
```

```
// Write the stringpersist\_write\_string(key, string);
```

```
// Read the stringchar buffer[32];persist\_read\_string(key, buffer, sizeof(buffer));
```

### Data Structures

```
typedef struct {int a;int b;} Data;uint32\_t key = 3;Data data = (Data) {.a = 32,.b = 45};
```

```
// Write the data structurepersist\_write\_data(key, &data, sizeof(Data));
```

```
// Read the data structurepersist\_read\_data(key, &data, sizeof(Data));
```

> Note: If a persisted data structure's field layout changes between app versions, the data read may no longer be compatible (see below).

## Versioning Persisted Data

As already mentioned, automatic app updates will persist data between app versions. However, if the format of persisted data changes in a new app version (or keys change), developers should version their storage scheme and correctly handle version changes appropriately.

One way to do this is to use an extra persisted integer as the storage scheme's version number. If the scheme changes, simply update the version number and migrate existing data as required. If old data cannot be migrated it should be deleted and replaced with fresh data in the correct scheme from the user. An example is shown below:

```
const uint32\_t storage\_version\_key = 786;const int current\_storage\_version = 2;
```

```
// Store the current storage scheme version numberpersist\_write\_int(storage\_version\_key, current\_storage\_version);
```

In this example, data stored in a key of `12` is now stored in a key of `13` due to a new key being inserted higher up the list of key values.

```
// The scheme has changed, increment the version numberconst int current\_storage\_version = 3;
```

```
static void migrate\_storage\_data() {// Check the last storage scheme version the app usedint last\_storage\_version = persist\_read\_int(storage\_version\_key);if (last\_storage\_version == current\_storage\_version) {// No migration necessaryreturn;}// Migrate dataswitch(last\_storage\_version) {case 0:// ...break;case 1:// ...break;case 2: {uint32\_t old\_highscore\_key = 12;uint32\_t new\_highscore\_key = 13;// Migrate to scheme version 3int highscore = persist\_read\_int(old\_highscore\_key);persist\_write\_int(new\_highscore\_key, highscore);// Delete old datapersist\_delete(old\_highscore\_key);break;}// Migration is complete, store the current storage scheme version numberpersist\_write\_int(storage\_version\_key, current\_storage\_version);}
```

## Alternative Method

In addition to the [`Storage`](/docs/c/Foundation/Storage/ "Storage") API, data can also be persisted using the`localStorage` API in PebbleKit JS, and communicated with the watch over[`AppMessage`](/docs/c/Foundation/AppMessage/ "AppMessage") when the app is lanched. However, this method uses more power and fails if the watch is not connected to the phone.
