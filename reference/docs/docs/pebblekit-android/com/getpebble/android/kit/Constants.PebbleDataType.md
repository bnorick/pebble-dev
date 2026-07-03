# Constants.PebbleDataType

Source: https://developer.repebble.com/docs/pebblekit-android/com/getpebble/android/kit/Constants.PebbleDataType/

[java.lang.Object](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/Object.html "class or interface in java.lang")
[java.lang.Enum](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/Enum.html "class or interface in java.lang")\<[Constants.PebbleDataType](/docs/pebblekit-android/com/getpebble/android/kit/Constants.PebbleDataType.md "enum class in com.getpebble.android.kit")\>
com.getpebble.android.kit.Constants.PebbleDataType

All Implemented Interfaces:`Serializable`, `Comparable<Constants.PebbleDataType>`, `Constable`Enclosing class:[Constants](/docs/pebblekit-android/com/getpebble/android/kit/Constants.md "class in com.getpebble.android.kit")
* * *

public static enum Constants.PebbleDataTypeextends [Enum](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/Enum.html "class or interface in java.lang")\<[Constants.PebbleDataType](/docs/pebblekit-android/com/getpebble/android/kit/Constants.PebbleDataType.md "enum class in com.getpebble.android.kit")\>

The Enum PebbleDataType.

- 
## Nested Class Summary

## Nested classes/interfaces inherited from class&nbsp;java.lang.[Enum](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/Enum.html "class or interface in java.lang")
`Enum.EnumDesc<E extends Enum<E>>`
- 
## Enum Constant Summary

Enum Constants

Enum Constant

Description

`BYTES`

The byte[].

`INT`

The Integer.

`INVALID`

The Invalid.

`UINT`

The UnsignedInteger.

- 
## Field Summary

Fields

Modifier and Type

Field

Description

`final byte`

`ord`

The ord.

- 
## Method Summary

All MethodsStatic MethodsConcrete Methods

Modifier and Type

Method

Description

`static Constants.PebbleDataType`

`fromByte(byte b)`

Instantiates a new pebble data type from a byte.

`static Constants.PebbleDataType`

`valueOf(String name)`

Returns the enum constant of this class with the specified name.

`static Constants.PebbleDataType[]`

`values()`

Returns an array containing the constants of this enum class, in the order they are declared.

### Methods inherited from class&nbsp;java.lang.[Enum](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/Enum.html "class or interface in java.lang")
`clone, compareTo, describeConstable, equals, finalize, getDeclaringClass, hashCode, name, ordinal, toString, valueOf`

### Methods inherited from class&nbsp;java.lang.[Object](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/Object.html "class or interface in java.lang")
`getClass, notify, notifyAll, wait, wait, wait`

- 
## Enum Constant Details

  - 
### BYTES

public static final&nbsp;[Constants.PebbleDataType](/docs/pebblekit-android/com/getpebble/android/kit/Constants.PebbleDataType.md "enum class in com.getpebble.android.kit")&nbsp;BYTES

The byte[].
  - 
### UINT

public static final&nbsp;[Constants.PebbleDataType](/docs/pebblekit-android/com/getpebble/android/kit/Constants.PebbleDataType.md "enum class in com.getpebble.android.kit")&nbsp;UINT

The UnsignedInteger.
  - 
### INT

public static final&nbsp;[Constants.PebbleDataType](/docs/pebblekit-android/com/getpebble/android/kit/Constants.PebbleDataType.md "enum class in com.getpebble.android.kit")&nbsp;INT

The Integer.
  - 
### INVALID

public static final&nbsp;[Constants.PebbleDataType](/docs/pebblekit-android/com/getpebble/android/kit/Constants.PebbleDataType.md "enum class in com.getpebble.android.kit")&nbsp;INVALID

The Invalid.
- 
## Field Details

  - 
### ord

public final&nbsp;byte&nbsp;ord

The ord.
- 
## Method Details

  - 
### values

public static&nbsp;[Constants.PebbleDataType](/docs/pebblekit-android/com/getpebble/android/kit/Constants.PebbleDataType.md "enum class in com.getpebble.android.kit")[]&nbsp;values()

Returns an array containing the constants of this enum class, in the order they are declared.
Returns:an array containing the constants of this enum class, in the order they are declared
  - 
### valueOf

public static&nbsp;[Constants.PebbleDataType](/docs/pebblekit-android/com/getpebble/android/kit/Constants.PebbleDataType.md "enum class in com.getpebble.android.kit")&nbsp;valueOf([String](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/String.html "class or interface in java.lang")&nbsp;name)

Returns the enum constant of this class with the specified name. The string must match _exactly_ an identifier used to declare an enum constant in this class. (Extraneous whitespace characters are not permitted.)
Parameters:`name` - the name of the enum constant to be returned.Returns:the enum constant with the specified nameThrows:`IllegalArgumentException` - if this enum class has no constant with the specified name`NullPointerException` - if the argument is null
  - 
### fromByte

public static&nbsp;[Constants.PebbleDataType](/docs/pebblekit-android/com/getpebble/android/kit/Constants.PebbleDataType.md "enum class in com.getpebble.android.kit")&nbsp;fromByte(byte&nbsp;b)

Instantiates a new pebble data type from a byte.
