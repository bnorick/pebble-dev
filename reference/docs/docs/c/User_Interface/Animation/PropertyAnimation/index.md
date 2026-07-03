# PropertyAnimation

Source: https://developer.repebble.com/docs/c/User_Interface/Animation/PropertyAnimation/index.html

A ProperyAnimation animates the value of a "property" of a "subject" over time.

### Animating a Layer's frame property

Currently there is only one specific type of property animation offered off-the-shelf, namely one to change the frame (property) of a layer (subject), see [property\_animation\_create\_layer\_frame()](/docs/c/User_Interface/Animation/PropertyAnimation/#property_animation_create_layer_frame).

### Implementing a custom PropertyAnimation

It is fairly simple to create your own variant of a PropertyAnimation.

Please refer to

[User Interface Layers chapter in the Pebble Developer Guides](https://developer.getpebble.com/guides/pebble-apps/display-and-animations/layers/)
 (chapter "Property Animations") for a conceptual overview of the animation framework and make sure you understand the underlying [Animation](/docs/c/User_Interface/Animation/), in case you are not familiar with it, before trying to implement a variation on PropertyAnimation.

To implement a custom property animation, use [property\_animation\_create()](/docs/c/User_Interface/Animation/PropertyAnimation/#property_animation_create) and provide a function pointers to the accessors (getter and setter) and setup, update and teardown callbacks in the implementation argument. Note that the type of property to animate with [PropertyAnimation](/docs/c/User_Interface/Animation/PropertyAnimation/) is limited to int16\_t, [GPoint](/docs/c/Graphics/Graphics_Types/#GPoint) or [GRect](/docs/c/Graphics/Graphics_Types/#GRect).

For each of these types, there are implementations provided for the necessary `.update` handler of the animation: see [property\_animation\_update\_int16()](/docs/c/User_Interface/Animation/PropertyAnimation/#property_animation_update_int16), [property\_animation\_update\_gpoint()](/docs/c/User_Interface/Animation/PropertyAnimation/#property_animation_update_gpoint) and [property\_animation\_update\_grect()](/docs/c/User_Interface/Animation/PropertyAnimation/#property_animation_update_grect). These update functions expect the `.accessors` to conform to the following interface: Any getter needs to have the following function signature: ` __type__ getter(void *subject);` Any setter needs to have to following function signature: `void setter(void *subject,
__type__ value);` See [Int16Getter](/docs/c/User_Interface/Animation/PropertyAnimation/#Int16Getter), [Int16Setter](/docs/c/User_Interface/Animation/PropertyAnimation/#Int16Setter), [GPointGetter](/docs/c/User_Interface/Animation/PropertyAnimation/#GPointGetter), [GPointSetter](/docs/c/User_Interface/Animation/PropertyAnimation/#GPointSetter), [GRectGetter](/docs/c/User_Interface/Animation/PropertyAnimation/#GRectGetter), [GRectSetter](/docs/c/User_Interface/Animation/PropertyAnimation/#GRectSetter) for the typedefs that accompany the update fuctions.

```
static const PropertyAnimationImplementation my\_implementation = {.base = {// using the "stock" update callback:.update = (AnimationUpdateImplementation) property\_animation\_update\_gpoint,},.accessors = {// my accessors that get/set a GPoint from/onto my subject:.setter = { .gpoint = my\_layer\_set\_corner\_point, },.getter = { .gpoint = (const GPointGetter) my\_layer\_get\_corner\_point, },},};static PropertyAnimation\* s\_my\_animation\_ptr = NULL;static GPoint s\_to\_point = GPointZero;...// Use NULL as 'from' value, this will make the animation framework call the getter// to get the current value of the property and use that as the 'from' value:s\_my\_animation\_ptr = property\_animation\_create(&my\_implementation, my\_layer, NULL, &s\_to\_point);animation\_schedule(property\_animation\_get\_animation(s\_my\_animation\_ptr));
```

## Function Documentation

PropertyAnimation \* property\_animation\_create\_layer\_frame(struct Layer \* layer, [GRect](/docs/c/Graphics/Graphics_Types/#GRect) \* from\_frame, [GRect](/docs/c/Graphics/Graphics_Types/#GRect) \* to\_frame)

Convenience function to create and initialize a property animation that animates the frame of a Layer. It sets up the PropertyAnimation to use [layer\_set\_frame()](/docs/c/User_Interface/Layers/#layer_set_frame) and [layer\_get\_frame()](/docs/c/User_Interface/Layers/#layer_get_frame) as accessors and uses the `layer` parameter as the subject for the animation. The same defaults are used as with [animation\_create()](/docs/c/User_Interface/Animation/#animation_create).

##### Note

Pass in `NULL` as one of the frame arguments to have it set automatically to the layer's current frame. This will result in a call to [layer\_get\_frame()](/docs/c/User_Interface/Layers/#layer_get_frame) to get the current frame of the layer.

#### Parameters
 layer

the layer that will be animated

 from\_frame

the frame that the layer should animate from

 to\_frame

the frame that the layer should animate to

#### Returns

A handle to the property animation. `NULL` if animation could not be created

PropertyAnimation \* property\_animation\_create\_bounds\_origin(struct Layer \* layer, [GPoint](/docs/c/Graphics/Graphics_Types/#GPoint) \* from, [GPoint](/docs/c/Graphics/Graphics_Types/#GPoint) \* to)

Convenience function to create and initialize a property animation that animates the bound's origin of a Layer. It sets up the PropertyAnimation to use [layer\_set\_bounds()](/docs/c/User_Interface/Layers/#layer_set_bounds) and [layer\_get\_bounds()](/docs/c/User_Interface/Layers/#layer_get_bounds) as accessors and uses the `layer` parameter as the subject for the animation. The same defaults are used as with [animation\_create()](/docs/c/User_Interface/Animation/#animation_create).

#### Parameters
 layer

the layer that will be animated

 from\_origin

the origin that the bounds should animate from

 to\_origin

the origin that the layer should animate to

#### Returns

A handle to the property animation. `NULL` if animation could not be created

PropertyAnimation \* property\_animation\_create(const [PropertyAnimationImplementation](/docs/c/User_Interface/Animation/PropertyAnimation/#PropertyAnimationImplementation) \* implementation, void \* subject, void \* from\_value, void \* to\_value)

Creates a new PropertyAnimation on the heap and and initializes it with the specified values. The same defaults are used as with [animation\_create()](/docs/c/User_Interface/Animation/#animation_create). If the `from_value` or the `to_value` is `NULL`, the getter accessor will be called to get the current value of the property and be used instead.

##### Note

Pass in `NULL` as one of the value arguments to have it set automatically to the subject's current property value, as returned by the getter function. Also note that passing in `NULL` for both `from_value` and `to_value`, will result in the animation having the same from- and to- values, effectively not doing anything.

#### Parameters
 implementation

Pointer to the implementation of the animation. In most cases, it makes sense to pass in a `static const` struct pointer.

 subject

Pointer to the "subject" being animated. This will be passed in when the getter/ setter accessors are called, see [PropertyAnimationAccessors](/docs/c/User_Interface/Animation/PropertyAnimation/#PropertyAnimationAccessors), [GPointSetter](/docs/c/User_Interface/Animation/PropertyAnimation/#GPointSetter), and friends. The value of this pointer will be copied into the `.subject` field of the PropertyAnimation struct.

 from\_value

Pointer to the value that the subject should animate from

 to\_value

Pointer to the value that the subject should animate to

#### Returns

A handle to the property animation. `NULL` if animation could not be created

void property\_animation\_destroy(PropertyAnimation \* property\_animation)

Destroy a property animation allocated by [property\_animation\_create()](/docs/c/User_Interface/Animation/PropertyAnimation/#property_animation_create) or relatives.

#### Parameters
 property\_animation

the return value from property\_animation\_create

void property\_animation\_update\_int16(PropertyAnimation \* property\_animation, const [uint32\_t](/docs/c/Standard_C/#uint32_t) distance\_normalized)

Default update callback for a property animations to update a property of type int16\_t. Assign this function to the `.base.update` callback field of your [PropertyAnimationImplementation](/docs/c/User_Interface/Animation/PropertyAnimation/#PropertyAnimationImplementation), in combination with a `.getter` and `.setter` accessors of types [Int16Getter](/docs/c/User_Interface/Animation/PropertyAnimation/#Int16Getter) and [Int16Setter](/docs/c/User_Interface/Animation/PropertyAnimation/#Int16Setter). The implementation of this function will calculate the next value of the animation and call the setter to set the new value upon the subject.

##### Note

This function is not supposed to be called "manually", but will be called automatically when the animation is being run.

#### Parameters
 property\_animation

The property animation for which the update is requested.

 distance\_normalized

The current normalized distance. See [AnimationUpdateImplementation](/docs/c/User_Interface/Animation/#AnimationUpdateImplementation)

void property\_animation\_update\_uint32(PropertyAnimation \* property\_animation, const [uint32\_t](/docs/c/Standard_C/#uint32_t) distance\_normalized)

Default update callback for a property animations to update a property of type [uint32\_t](/docs/c/Standard_C/#uint32_t). Assign this function to the `.base.update` callback field of your [PropertyAnimationImplementation](/docs/c/User_Interface/Animation/PropertyAnimation/#PropertyAnimationImplementation), in combination with a `.getter` and `.setter` accessors of types [UInt32Getter](/docs/c/User_Interface/Animation/PropertyAnimation/#UInt32Getter) and [UInt32Setter](/docs/c/User_Interface/Animation/PropertyAnimation/#UInt32Setter). The implementation of this function will calculate the next value of the animation and call the setter to set the new value upon the subject.

##### Note

This function is not supposed to be called "manually", but will be called automatically when the animation is being run.

#### Parameters
 property\_animation

The property animation for which the update is requested.

 distance\_normalized

The current normalized distance. See [AnimationUpdateImplementation](/docs/c/User_Interface/Animation/#AnimationUpdateImplementation)

void property\_animation\_update\_gpoint(PropertyAnimation \* property\_animation, const [uint32\_t](/docs/c/Standard_C/#uint32_t) distance\_normalized)

Default update callback for a property animations to update a property of type [GPoint](/docs/c/Graphics/Graphics_Types/#GPoint). Assign this function to the `.base.update` callback field of your [PropertyAnimationImplementation](/docs/c/User_Interface/Animation/PropertyAnimation/#PropertyAnimationImplementation), in combination with a `.getter` and `.setter` accessors of types [GPointGetter](/docs/c/User_Interface/Animation/PropertyAnimation/#GPointGetter) and [GPointSetter](/docs/c/User_Interface/Animation/PropertyAnimation/#GPointSetter). The implementation of this function will calculate the next point of the animation and call the setter to set the new point upon the subject.

##### Note

This function is not supposed to be called "manually", but will be called automatically when the animation is being run.

#### Parameters
 property\_animation

The property animation for which the update is requested.

 distance\_normalized

The current normalized distance. See [AnimationUpdateImplementation](/docs/c/User_Interface/Animation/#AnimationUpdateImplementation)

void property\_animation\_update\_grect(PropertyAnimation \* property\_animation, const [uint32\_t](/docs/c/Standard_C/#uint32_t) distance\_normalized)

Default update callback for a property animations to update a property of type [GRect](/docs/c/Graphics/Graphics_Types/#GRect). Assign this function to the `.base.update` callback field of your [PropertyAnimationImplementation](/docs/c/User_Interface/Animation/PropertyAnimation/#PropertyAnimationImplementation), in combination with a `.getter` and `.setter` accessors of types [GRectGetter](/docs/c/User_Interface/Animation/PropertyAnimation/#GRectGetter) and [GRectSetter](/docs/c/User_Interface/Animation/PropertyAnimation/#GRectSetter). The implementation of this function will calculate the next rectangle of the animation and call the setter to set the new rectangle upon the subject.

##### Note

This function is not supposed to be called "manually", but will be called automatically when the animation is being run.

#### Parameters
 property\_animation

The property animation for which the update is requested.

 distance\_normalized

The current normalized distance. See [AnimationUpdateImplementation](/docs/c/User_Interface/Animation/#AnimationUpdateImplementation)

void property\_animation\_update\_gcolor8(PropertyAnimation \* property\_animation, const [uint32\_t](/docs/c/Standard_C/#uint32_t) distance\_normalized)

Default update callback for a property animations to update a property of type GColor8. Assign this function to the `.base.update` callback field of your [PropertyAnimationImplementation](/docs/c/User_Interface/Animation/PropertyAnimation/#PropertyAnimationImplementation), in combination with a `.getter` and `.setter` accessors of types [GColor8Getter](/docs/c/User_Interface/Animation/PropertyAnimation/#GColor8Getter) and [GColor8Setter](/docs/c/User_Interface/Animation/PropertyAnimation/#GColor8Setter). The implementation of this function will calculate the next rectangle of the animation and call the setter to set the new value upon the subject.

##### Note

This function is not supposed to be called "manually", but will be called automatically when the animation is being run.

#### Parameters
 property\_animation

The property animation for which the update is requested.

 distance\_normalized

The current normalized distance. See [AnimationUpdateImplementation](/docs/c/User_Interface/Animation/#AnimationUpdateImplementation)

Animation \* property\_animation\_get\_animation(PropertyAnimation \* property\_animation)

Convenience function to retrieve an animation instance from a property animation instance.

#### Parameters
 property\_animation

The property animation

#### Returns

The [Animation](/docs/c/User_Interface/Animation/) within this PropertyAnimation

bool property\_animation\_subject(PropertyAnimation \* property\_animation, void \*\* subject, bool set)

Helper function used by the property\_animation\_get|set\_subject macros.

#### Parameters
 property\_animation

Handle to the property animation

 subject

The subject to get or set.

 set

true to set new subject, false to retrieve existing value

#### Returns

true if successful, false on failure (usually a bad animation\_h)

bool property\_animation\_from(PropertyAnimation \* property\_animation, void \* from, [size\_t](/docs/c/Standard_C/Memory/#size_t) size, bool set)

Helper function used by the property\_animation\_get|set\_from\_.\* macros.

#### Parameters
 property\_animation

Handle to the property animation

 from

Pointer to the value

 size

Size of the from value

 set

true to set new value, false to retrieve existing one

#### Returns

true if successful, false on failure (usually a bad animation\_h)

bool property\_animation\_to(PropertyAnimation \* property\_animation, void \* to, [size\_t](/docs/c/Standard_C/Memory/#size_t) size, bool set)

Helper function used by the property\_animation\_get|set\_to\_.\* macros.

#### Parameters
 property\_animation

handle to the property animation

 to

Pointer to the value

 size

Size of the to value

 set

true to set new value, false to retrieve existing one

#### Returns

true if successful, false on failure (usually a bad animation\_h)

## Data Structure Documentation

struct PropertyAnimationAccessors

Data structure containing the setter and getter function pointers that the property animation should use. The specified setter function will be used by the animation's update callback.   
 Based on the type of the property (int16\_t, [GPoint](/docs/c/Graphics/Graphics_Types/#GPoint) or [GRect](/docs/c/Graphics/Graphics_Types/#GRect)), the accompanying update callback should be used, see [property\_animation\_update\_int16()](/docs/c/User_Interface/Animation/PropertyAnimation/#property_animation_update_int16), [property\_animation\_update\_gpoint()](/docs/c/User_Interface/Animation/PropertyAnimation/#property_animation_update_gpoint) and [property\_animation\_update\_grect()](/docs/c/User_Interface/Animation/PropertyAnimation/#property_animation_update_grect).   
 The getter function is used when the animation is initialized, to assign the current value of the subject's property as "from" or "to" value, see [property\_animation\_create()](/docs/c/User_Interface/Animation/PropertyAnimation/#property_animation_create).

#### Data Fields
union [PropertyAnimationAccessors](/docs/c/User_Interface/Animation/PropertyAnimation/#PropertyAnimationAccessors) setter

Function pointer to the implementation of the function that **sets** the updated property value. This function will be called repeatedly for each animation frame.

union [PropertyAnimationAccessors](/docs/c/User_Interface/Animation/PropertyAnimation/#PropertyAnimationAccessors) getter

Function pointer to the implementation of the function that **gets** the current property value. This function will be called during [property\_animation\_create()](/docs/c/User_Interface/Animation/PropertyAnimation/#property_animation_create), to get the current property value, in case the `from_value` or `to_value` argument is `NULL`.

struct PropertyAnimationImplementation

Data structure containing a collection of function pointers that form the implementation of the property animation. See the code example at the top ([PropertyAnimation](/docs/c/User_Interface/Animation/PropertyAnimation/)).

#### Data Fields
[AnimationImplementation](/docs/c/User_Interface/Animation/#AnimationImplementation) base

The "inherited" fields from the Animation "base class".

[PropertyAnimationAccessors](/docs/c/User_Interface/Animation/PropertyAnimation/#PropertyAnimationAccessors) accessors

The accessors to set/get the property to be animated.

## Typedef Documentation

 typedef struct PropertyAnimation PropertyAnimation

 typedef [GPoint](/docs/c/Graphics/Graphics_Types/#GPoint) GPointReturn

Work-around for function pointer return type [GPoint](/docs/c/Graphics/Graphics_Types/#GPoint) to avoid tripping the pre-processor to use the equally named [GPoint](/docs/c/Graphics/Graphics_Types/#GPoint) define.

 typedef [GRect](/docs/c/Graphics/Graphics_Types/#GRect) GRectReturn

Work-around for function pointer return type [GRect](/docs/c/Graphics/Graphics_Types/#GRect) to avoid tripping the pre-processor to use the equally named [GRect](/docs/c/Graphics/Graphics_Types/#GRect) define.

 typedef void(\* Int16Setter)(void \*subject, int16\_t int16) 

Function signature of a setter function to set a property of type int16\_t onto the subject.

#### See Also
[property\_animation\_update\_int16()](/docs/c/User_Interface/Animation/PropertyAnimation/#property_animation_update_int16)  
[PropertyAnimationAccessors](/docs/c/User_Interface/Animation/PropertyAnimation/#PropertyAnimationAccessors)

 typedef int16\_t(\* Int16Getter)(void \*subject) 

Function signature of a getter function to get the current property of type int16\_t of the subject.

#### See Also
[property\_animation\_create()](/docs/c/User_Interface/Animation/PropertyAnimation/#property_animation_create)  
[PropertyAnimationAccessors](/docs/c/User_Interface/Animation/PropertyAnimation/#PropertyAnimationAccessors)

 typedef void(\* UInt32Setter)(void \*subject, uint32\_t uint32) 

Function signature of a setter function to set a property of type [uint32\_t](/docs/c/Standard_C/#uint32_t) onto the subject.

#### See Also
[property\_animation\_update\_int16()](/docs/c/User_Interface/Animation/PropertyAnimation/#property_animation_update_int16)  
[PropertyAnimationAccessors](/docs/c/User_Interface/Animation/PropertyAnimation/#PropertyAnimationAccessors)

 typedef [uint32\_t](/docs/c/Standard_C/#uint32_t)(\* UInt32Getter)(void \*subject) 

Function signature of a getter function to get the current property of type [uint32\_t](/docs/c/Standard_C/#uint32_t) of the subject.

#### See Also
[property\_animation\_create()](/docs/c/User_Interface/Animation/PropertyAnimation/#property_animation_create)  
[PropertyAnimationAccessors](/docs/c/User_Interface/Animation/PropertyAnimation/#PropertyAnimationAccessors)

 typedef void(\* GPointSetter)(void \*subject, GPoint gpoint) 

Function signature of a setter function to set a property of type [GPoint](/docs/c/Graphics/Graphics_Types/#GPoint) onto the subject.

#### See Also
[property\_animation\_update\_gpoint()](/docs/c/User_Interface/Animation/PropertyAnimation/#property_animation_update_gpoint)  
[PropertyAnimationAccessors](/docs/c/User_Interface/Animation/PropertyAnimation/#PropertyAnimationAccessors)

 typedef [GPointReturn](/docs/c/User_Interface/Animation/PropertyAnimation/#GPointReturn)(\* GPointGetter)(void \*subject) 

Function signature of a getter function to get the current property of type [GPoint](/docs/c/Graphics/Graphics_Types/#GPoint) of the subject.

#### See Also
[property\_animation\_create()](/docs/c/User_Interface/Animation/PropertyAnimation/#property_animation_create)  
[PropertyAnimationAccessors](/docs/c/User_Interface/Animation/PropertyAnimation/#PropertyAnimationAccessors)

 typedef void(\* GRectSetter)(void \*subject, GRect grect) 

Function signature of a setter function to set a property of type [GRect](/docs/c/Graphics/Graphics_Types/#GRect) onto the subject.

#### See Also
[property\_animation\_update\_grect()](/docs/c/User_Interface/Animation/PropertyAnimation/#property_animation_update_grect)  
[PropertyAnimationAccessors](/docs/c/User_Interface/Animation/PropertyAnimation/#PropertyAnimationAccessors)

 typedef [GRectReturn](/docs/c/User_Interface/Animation/PropertyAnimation/#GRectReturn)(\* GRectGetter)(void \*subject) 

Function signature of a getter function to get the current property of type [GRect](/docs/c/Graphics/Graphics_Types/#GRect) of the subject.

#### See Also
[property\_animation\_create()](/docs/c/User_Interface/Animation/PropertyAnimation/#property_animation_create)  
[PropertyAnimationAccessors](/docs/c/User_Interface/Animation/PropertyAnimation/#PropertyAnimationAccessors)

 typedef void(\* GColor8Setter)(void \*subject, GColor8 gcolor) 

Function signature of a setter function to set a property of type GColor8 onto the subject.

#### See Also
[property\_animation\_update\_gcolor8()](/docs/c/User_Interface/Animation/PropertyAnimation/#property_animation_update_gcolor8)  
[PropertyAnimationAccessors](/docs/c/User_Interface/Animation/PropertyAnimation/#PropertyAnimationAccessors)

 typedef GColor8(\* GColor8Getter)(void \*subject) 

Function signature of a getter function to get the current property of type GColor8 of the subject.

#### See Also
[property\_animation\_create()](/docs/c/User_Interface/Animation/PropertyAnimation/#property_animation_create)  
[PropertyAnimationAccessors](/docs/c/User_Interface/Animation/PropertyAnimation/#PropertyAnimationAccessors)

## Macro Definition Documentation

#define property\_animation\_clone ( property\_animation)

Convenience function to clone a property animation instance.

#### Parameters
 property\_animation

The property animation

#### Returns

A clone of the original Animation

#define property\_animation\_get\_from\_grect ( property\_animation, value\_ptr)

Convenience function to retrieve the 'from' [GRect](/docs/c/Graphics/Graphics_Types/#GRect) value from property animation handle.

#### Parameters
 property\_animation

The PropertyAnimation to be accessed

 value\_ptr

The value will be retrieved into this pointer

#### Returns

true on success, false on failure

#define property\_animation\_set\_from\_grect ( property\_animation, value\_ptr)

Convenience function to set the 'from' [GRect](/docs/c/Graphics/Graphics_Types/#GRect) value of property animation handle.

#### Parameters
 property\_animation

The PropertyAnimation to be accessed

 value\_ptr

Pointer to the new value

#### Returns

true on success, false on failure

#define property\_animation\_get\_from\_gpoint ( property\_animation, value\_ptr)

Convenience function to retrieve the 'from' [GPoint](/docs/c/Graphics/Graphics_Types/#GPoint) value from property animation handle.

#### Parameters
 property\_animation

The PropertyAnimation to be accessed

 value\_ptr

The value will be retrieved into this pointer

#### Returns

true on success, false on failure

#define property\_animation\_set\_from\_gpoint ( property\_animation, value\_ptr)

Convenience function to set the 'from' [GPoint](/docs/c/Graphics/Graphics_Types/#GPoint) value of property animation handle.

#### Parameters
 property\_animation

The PropertyAnimation to be accessed

 value\_ptr

Pointer to the new value

#### Returns

true on success, false on failure

#define property\_animation\_get\_from\_int16 ( property\_animation, value\_ptr)

Convenience function to retrieve the 'from' int16\_t value from property animation handle.

#### Parameters
 property\_animation

The PropertyAnimation to be accessed

 value\_ptr

The value will be retrieved into this pointer

#### Returns

true on success, false on failure

#define property\_animation\_set\_from\_int16 ( property\_animation, value\_ptr)

Convenience function to set the 'from' int16\_t value of property animation handle.

#### Parameters
 property\_animation

The PropertyAnimation to be accessed

 value\_ptr

Pointer to the new value

#### Returns

true on success, false on failure

#define property\_animation\_get\_to\_grect ( property\_animation, value\_ptr)

Convenience function to retrieve the 'to' [GRect](/docs/c/Graphics/Graphics_Types/#GRect) value from property animation handle.

#### Parameters
 property\_animation

The PropertyAnimation to be accessed

 value\_ptr

The value will be retrieved into this pointer

#### Returns

true on success, false on failure

#define property\_animation\_set\_to\_grect ( property\_animation, value\_ptr)

Convenience function to set the 'to' [GRect](/docs/c/Graphics/Graphics_Types/#GRect) value of property animation handle.

#### Parameters
 property\_animation

The PropertyAnimation to be accessed

 value\_ptr

Pointer to the new value

#### Returns

true on success, false on failure

#define property\_animation\_get\_to\_gpoint ( property\_animation, value\_ptr)

Convenience function to retrieve the 'to' [GPoint](/docs/c/Graphics/Graphics_Types/#GPoint) value from property animation handle.

#### Parameters
 property\_animation

The PropertyAnimation to be accessed

 value\_ptr

The value will be retrieved into this pointer

#### Returns

true on success, false on failure

#define property\_animation\_set\_to\_gpoint ( property\_animation, value\_ptr)

Convenience function to set the 'to' [GPoint](/docs/c/Graphics/Graphics_Types/#GPoint) value of property animation handle.

#### Parameters
 property\_animation

The PropertyAnimation to be accessed

 value\_ptr

Pointer to the new value

#### Returns

true on success, false on failure

#define property\_animation\_get\_to\_int16 ( property\_animation, value\_ptr)

Convenience function to retrieve the 'to' int16\_t value from property animation handle.

#### Parameters
 property\_animation

The PropertyAnimation to be accessed

 value\_ptr

The value will be retrieved into this pointer

#### Returns

true on success, false on failure

#define property\_animation\_set\_to\_int16 ( property\_animation, value\_ptr)

Convenience function to set the 'to' int16\_t value of property animation handle.

#### Parameters
 property\_animation

The PropertyAnimation to be accessed

 value\_ptr

Pointer to the new value

#### Returns

true on success, false on failure

#define property\_animation\_get\_subject ( property\_animation, value\_ptr)

Retrieve the subject of a property animation.

#### Parameters
 property\_animation

The PropertyAnimation to be accessed

 value\_ptr

Pointer used to store the subject of this property animation

#### Returns

The subject of this PropertyAnimation

#define property\_animation\_set\_subject ( property\_animation, value\_ptr)

Set the subject of a property animation.

#### Parameters
 property\_animation

The PropertyAnimation to be accessed

 value\_ptr

Pointer to the new subject value
