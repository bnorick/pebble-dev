# PebbleDictionary

Source: https://developer.repebble.com/docs/pebblekit-android/com/getpebble/android/kit/util/PebbleDictionary/

[java.lang.Object](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/Object.html "class or interface in java.lang")
com.getpebble.android.kit.util.PebbleDictionary

All Implemented Interfaces:`Iterable<PebbleTuple>`
* * *

public class PebbleDictionaryextends [Object](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/Object.html "class or interface in java.lang")implements [Iterable](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/Iterable.html "class or interface in java.lang")\<[PebbleTuple](/docs/pebblekit-android/com/getpebble/android/kit/util/PebbleTuple.md "class in com.getpebble.android.kit.util")\>

A collection of key-value pairs of heterogeneous types. PebbleDictionaries are the primary structure used to exchange data between the phone and watch. To accommodate the mixed-types contained within a PebbleDictionary, an internal JSON representation is used when exchanging the dictionary between Android processes.

- 
## Nested Class Summary

Nested Classes

Modifier and Type

Class

Description

`static class `

`PebbleDictionary.PebbleDictTypeException`

&nbsp;

`static class `

`PebbleDictionary.TupleOverflowException`

&nbsp;

- 
## Field Summary

Fields

Modifier and Type

Field

Description

`protected final Map<Integer,PebbleTuple>`

`tuples`

&nbsp;

- 
## Constructor Summary

Constructors

Constructor

Description

`PebbleDictionary()`

&nbsp;

- 
## Method Summary

All MethodsStatic MethodsInstance MethodsConcrete Methods

Modifier and Type

Method

Description

`void`

`addBytes(int key,
 byte[] bytes)`

Associate the specified byte array with the provided key in the dictionary.

`void`

`addInt16(int key,
 short s)`

Associate the specified signed short with the provided key in the dictionary.

`void`

`addInt32(int key,
 int i)`

Associate the specified signed int with the provided key in the dictionary.

`void`

`addInt8(int key,
 byte b)`

Associate the specified signed byte with the provided key in the dictionary.

`void`

`addString(int key,
 String value)`

Associate the specified String with the provided key in the dictionary.

`protected void`

`addTuple(PebbleTuple tuple)`

&nbsp;

`void`

`addUint16(int key,
 short s)`

Associate the specified unsigned short with the provided key in the dictionary.

`void`

`addUint32(int key,
 int i)`

Associate the specified unsigned int with the provided key in the dictionary.

`void`

`addUint8(int key,
 byte b)`

Associate the specified unsigned byte with the provided key in the dictionary.

`boolean`

`contains(int key)`

Returns true if this dictionary contains a mapping for the specified key.

`static PebbleDictionary`

`fromJson(String jsonString)`

Deserializes a JSON representation of a PebbleDictionary.

`byte[]`

`getBytes(int key)`

Returns the byte array to which the specified key is mapped, or null if the key does not exist in this dictionary.

`Long`

`getInteger(int key)`

Returns the signed integer to which the specified key is mapped, or null if the key does not exist in this dictionary.

`String`

`getString(int key)`

Returns the string to which the specified key is mapped, or null if the key does not exist in this dictionary.

`Long`

`getUnsignedIntegerAsLong(int key)`

Returns the unsigned integer as a long to which the specified key is mapped, or null if the key does not exist in this dictionary.

`Iterator<PebbleTuple>`

`iterator()`

`void`

`remove(int key)`

Removes the mapping for a key from this map if it is present.

`int`

`size()`

Returns the number of key-value pairs in this dictionary.

`String`

`toJsonString()`

Returns a JSON representation of this dictionary.

### Methods inherited from class&nbsp;java.lang.[Object](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/Object.html "class or interface in java.lang")
`clone, equals, finalize, getClass, hashCode, notify, notifyAll, toString, wait, wait, wait`

### Methods inherited from interface&nbsp;java.lang.[Iterable](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/Iterable.html "class or interface in java.lang")
`forEach, spliterator`

- 
## Field Details

  - 
### tuples

protected final&nbsp;[Map](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/util/Map.html "class or interface in java.util")\<[Integer](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/Integer.html "class or interface in java.lang"),[PebbleTuple](/docs/pebblekit-android/com/getpebble/android/kit/util/PebbleTuple.md "class in com.getpebble.android.kit.util")\>&nbsp;tuples
- 
## Constructor Details

  - 
### PebbleDictionary

public&nbsp;PebbleDictionary()
- 
## Method Details

  - 
### iterator

public&nbsp;[Iterator](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/util/Iterator.html "class or interface in java.util")\<[PebbleTuple](/docs/pebblekit-android/com/getpebble/android/kit/util/PebbleTuple.md "class in com.getpebble.android.kit.util")\>&nbsp;iterator()
Specified by:`iterator`&nbsp;in interface&nbsp;`Iterable<PebbleTuple>`
  - 
### size

public&nbsp;int&nbsp;size()

Returns the number of key-value pairs in this dictionary.
Returns:the number of key-value pairs in this dictionary
  - 
### contains

public&nbsp;boolean&nbsp;contains(int&nbsp;key)

Returns true if this dictionary contains a mapping for the specified key.
Parameters:`key` - key whose presence in this dictionary is to be testedReturns:true if this dictionary contains a mapping for the specified key
  - 
### remove

public&nbsp;void&nbsp;remove(int&nbsp;key)

Removes the mapping for a key from this map if it is present.
Parameters:`key` - key to be removed from the dictionary
  - 
### addBytes

public&nbsp;void&nbsp;addBytes(int&nbsp;key, byte[]&nbsp;bytes)

Associate the specified byte array with the provided key in the dictionary. If another key-value pair with the same key is already present in the dictionary, it will be replaced.
Parameters:`key` - key with which the specified value is associated`bytes` - value to be associated with the specified key
  - 
### addString

public&nbsp;void&nbsp;addString(int&nbsp;key, [String](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/String.html "class or interface in java.lang")&nbsp;value)

Associate the specified String with the provided key in the dictionary. If another key-value pair with the same key is already present in the dictionary, it will be replaced.
Parameters:`key` - key with which the specified value is associated`value` - value to be associated with the specified key
  - 
### addInt8

public&nbsp;void&nbsp;addInt8(int&nbsp;key, byte&nbsp;b)

Associate the specified signed byte with the provided key in the dictionary. If another key-value pair with the same key is already present in the dictionary, it will be replaced.
Parameters:`key` - key with which the specified value is associated`b` - value to be associated with the specified key
  - 
### addUint8

public&nbsp;void&nbsp;addUint8(int&nbsp;key, byte&nbsp;b)

Associate the specified unsigned byte with the provided key in the dictionary. If another key-value pair with the same key is already present in the dictionary, it will be replaced.
Parameters:`key` - key with which the specified value is associated`b` - value to be associated with the specified key
  - 
### addInt16

public&nbsp;void&nbsp;addInt16(int&nbsp;key, short&nbsp;s)

Associate the specified signed short with the provided key in the dictionary. If another key-value pair with the same key is already present in the dictionary, it will be replaced.
Parameters:`key` - key with which the specified value is associated`s` - value to be associated with the specified key
  - 
### addUint16

public&nbsp;void&nbsp;addUint16(int&nbsp;key, short&nbsp;s)

Associate the specified unsigned short with the provided key in the dictionary. If another key-value pair with the same key is already present in the dictionary, it will be replaced.
Parameters:`key` - key with which the specified value is associated`s` - value to be associated with the specified key
  - 
### addInt32

public&nbsp;void&nbsp;addInt32(int&nbsp;key, int&nbsp;i)

Associate the specified signed int with the provided key in the dictionary. If another key-value pair with the same key is already present in the dictionary, it will be replaced.
Parameters:`key` - key with which the specified value is associated`i` - value to be associated with the specified key
  - 
### addUint32

public&nbsp;void&nbsp;addUint32(int&nbsp;key, int&nbsp;i)

Associate the specified unsigned int with the provided key in the dictionary. If another key-value pair with the same key is already present in the dictionary, it will be replaced.
Parameters:`key` - key with which the specified value is associated`i` - value to be associated with the specified key
  - 
### getInteger

public&nbsp;[Long](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/Long.html "class or interface in java.lang")&nbsp;getInteger(int&nbsp;key)

Returns the signed integer to which the specified key is mapped, or null if the key does not exist in this dictionary.
Parameters:`key` - key whose associated value is to be returnedReturns:value to which the specified key is mapped
  - 
### getUnsignedIntegerAsLong

public&nbsp;[Long](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/Long.html "class or interface in java.lang")&nbsp;getUnsignedIntegerAsLong(int&nbsp;key)

Returns the unsigned integer as a long to which the specified key is mapped, or null if the key does not exist in this dictionary. We are using the Long type here so that we can remove the guava dependency. This is done so that we dont have incompatibility issues with the UnsignedInteger class from the Holo application, which uses a newer version of Guava.
Parameters:`key` - key whose associated value is to be returnedReturns:value to which the specified key is mapped
  - 
### getBytes

public&nbsp;byte[]&nbsp;getBytes(int&nbsp;key)

Returns the byte array to which the specified key is mapped, or null if the key does not exist in this dictionary.
Parameters:`key` - key whose associated value is to be returnedReturns:value to which the specified key is mapped
  - 
### getString

public&nbsp;[String](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/String.html "class or interface in java.lang")&nbsp;getString(int&nbsp;key)

Returns the string to which the specified key is mapped, or null if the key does not exist in this dictionary.
Parameters:`key` - key whose associated value is to be returnedReturns:value to which the specified key is mapped
  - 
### addTuple

protected&nbsp;void&nbsp;addTuple([PebbleTuple](/docs/pebblekit-android/com/getpebble/android/kit/util/PebbleTuple.md "class in com.getpebble.android.kit.util")&nbsp;tuple)
  - 
### toJsonString

public&nbsp;[String](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/String.html "class or interface in java.lang")&nbsp;toJsonString()

Returns a JSON representation of this dictionary.
Returns:a JSON representation of this dictionary
  - 
### fromJson

public static&nbsp;[PebbleDictionary](/docs/pebblekit-android/com/getpebble/android/kit/util/PebbleDictionary.md "class in com.getpebble.android.kit.util")&nbsp;fromJson([String](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/String.html "class or interface in java.lang")&nbsp;jsonString) throws org.json.JSONException

Deserializes a JSON representation of a PebbleDictionary.
Parameters:`jsonString` - the JSON representation to be deserializedThrows:`org.json.JSONException` - thrown if the specified JSON representation cannot be parsed
