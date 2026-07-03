# Math

Source: https://developer.repebble.com/docs/c/Foundation/Math/index.html

Math routines.

Below is a code example that uses the trigonometry functions to calculate the coordinate at which the second hand of a watch ends, using seconds from the system time.

```
GPoint secondHand;GPoint center;struct tm \*tick\_time = ...;int32\_t secondHandLength = ...;...int32\_t second\_angle = TRIG\_MAX\_ANGLE \* tick\_time-\>tm\_sec / 60;secondHand.y = (-cos\_lookup(second\_angle) \* secondHandLength / TRIG\_MAX\_RATIO) + center.y;secondHand.x = (sin\_lookup(second\_angle) \* secondHandLength / TRIG\_MAX\_RATIO) + center.x;
```

## Function Documentation

int32\_t sin\_lookup(int32\_t angle)

Look-up the sine of the given angle from a pre-computed table.

#### Parameters
 angle

The angle for which to compute the cosine. The angle value is scaled linearly, such that a value of 0x10000 corresponds to 360 degrees or 2 PI radians.

int32\_t cos\_lookup(int32\_t angle)

Look-up the cosine of the given angle from a pre-computed table. This is equivalent to calling `sin_lookup(angle + TRIG_MAX_ANGLE / 4)`.

#### Parameters
 angle

The angle for which to compute the cosine. The angle value is scaled linearly, such that a value of 0x10000 corresponds to 360 degrees or 2 PI radians.

int32\_t atan2\_lookup(int16\_t y, int16\_t x)

Look-up the arctangent of a given x, y pair The angle value is scaled linearly, such that a value of 0x10000 corresponds to 360 degrees or 2 PI radians.

## Macro Definition Documentation

#define TRIG\_MAX\_RATIO 0xffff

The largest value that can result from a call to [sin\_lookup](/docs/c/Foundation/Math/#sin_lookup) or [cos\_lookup](/docs/c/Foundation/Math/#cos_lookup). For a code example, see the detailed description at the top of this chapter: [Math](/docs/c/Foundation/Math/).

#define TRIG\_MAX\_ANGLE 0x10000

Angle value that corresponds to 360 degrees or 2 PI radians.

#### See Also
[sin\_lookup](/docs/c/Foundation/Math/#sin_lookup)  
[cos\_lookup](/docs/c/Foundation/Math/#cos_lookup)

#define TRIGANGLE\_TO\_DEG ( trig\_angle)

Converts from a fixed point value representation to the equivalent value in degrees.

#### See Also
[DEG\_TO\_TRIGANGLE](/docs/c/Foundation/Math/#DEG_TO_TRIGANGLE)  
[TRIG\_MAX\_ANGLE](/docs/c/Foundation/Math/#TRIG_MAX_ANGLE)

#define DEG\_TO\_TRIGANGLE ( angle)

Converts from an angle in degrees to the equivalent fixed point value representation.

#### See Also
[TRIGANGLE\_TO\_DEG](/docs/c/Foundation/Math/#TRIGANGLE_TO_DEG)  
[TRIG\_MAX\_ANGLE](/docs/c/Foundation/Math/#TRIG_MAX_ANGLE)
