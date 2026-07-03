# PebbleTuple

Source: https://developer.repebble.com/docs/pebblekit-android/com/getpebble/android/kit/util/PebbleTuple/

[java.lang.Object](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/Object.html "class or interface in java.lang")
com.getpebble.android.kit.util.PebbleTuple

* * *

public class PebbleTupleextends [Object](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/Object.html "class or interface in java.lang")

A key-value pair stored in a [`PebbleDictionary`](/docs/pebblekit-android/com/getpebble/android/kit/util/PebbleDictionary.md "class in com.getpebble.android.kit.util").

- 
## Nested Class Summary

Nested Classes

Modifier and Type

Class

Description

`static class `

`PebbleTuple.ValueOverflowException`

&nbsp;

- 
## Field Summary

Fields

Modifier and Type

Field

Description

`final int`

`key`

The integer key identifying the tuple.

`final int`

`length`

The length of the tuple's value in bytes.

`final com.getpebble.android.kit.util.PebbleTuple.TupleType`

`type`

The type of value contained in the tuple.

`final Object`

`value`

The value being associated with the tuple's key.

`final com.getpebble.android.kit.util.PebbleTuple.Width`

`width`

The 'width' of the tuple's value; This value will always be 'NONE' for non-integer types.

- 
## Method Summary

### Methods inherited from class&nbsp;java.lang.[Object](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/Object.html "class or interface in java.lang")
`clone, equals, finalize, getClass, hashCode, notify, notifyAll, toString, wait, wait, wait`

- 
## Field Details

  - 
### key

public final&nbsp;int&nbsp;key

The integer key identifying the tuple.
  - 
### type

public final&nbsp;com.getpebble.android.kit.util.PebbleTuple.TupleType&nbsp;type

The type of value contained in the tuple.
  - 
### width

public final&nbsp;com.getpebble.android.kit.util.PebbleTuple.Width&nbsp;width

The 'width' of the tuple's value; This value will always be 'NONE' for non-integer types.
  - 
### length

public final&nbsp;int&nbsp;length

The length of the tuple's value in bytes.
  - 
### value

public final&nbsp;[Object](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/Object.html "class or interface in java.lang")&nbsp;value

The value being associated with the tuple's key.
