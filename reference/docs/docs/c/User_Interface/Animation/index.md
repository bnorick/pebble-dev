# Animation

Source: https://developer.repebble.com/docs/c/User_Interface/Animation/index.html

Abstract framework to create arbitrary animations

The Animation framework provides your Pebble app with an base layer to create arbitrary animations. The simplest way to work with animations is to use the layer frame [PropertyAnimation](/docs/c/User_Interface/Animation/PropertyAnimation/), which enables you to move a Layer around on the screen. Using [animation\_set\_implementation()](/docs/c/User_Interface/Animation/#animation_set_implementation), you can implement a custom animation.

Refer to the

[User Interface Layers chapter in the Pebble Developer Guides](https://developer.getpebble.com/guides/pebble-apps/display-and-animations/layers/)
 (chapter "Animation") for a conceptual overview of the animation framework and on how to write custom animations. 
## Modules

#### [PropertyAnimation](/docs/c/User_Interface/Animation/PropertyAnimation/)

A ProperyAnimation animates the value of a "property" of a "subject" over time.

## Function Documentation

Animation \* animation\_create(void)

Creates a new Animation on the heap and initalizes it with the default values.

- Duration: 250ms,

- Curve: AnimationCurveEaseInOut (ease-in-out),

- Delay: 0ms,

- Handlers: `{NULL, NULL}` (none),

- Context: `NULL` (none),

- Implementation: `NULL` (no implementation),

- Scheduled: no 

#### Returns

A pointer to the animation. `NULL` if the animation could not be created

bool animation\_destroy(Animation \* animation)

Destroys an Animation previously created by animation\_create.

#### Returns

true if successful, false on failure

Animation \* animation\_clone(Animation \* from)

Animation \* animation\_sequence\_create(Animation \* animation\_a, Animation \* animation\_b, Animation \* animation\_c, ...)

Create a new sequence animation from a list of 2 or more other animations. The returned animation owns the animations that were provided as arguments and no further write operations on those handles are allowed. The variable length argument list must be terminated with a NULL ptr.

##### Note

the maximum number of animations that can be supplied to this method is 20

#### Parameters
 animation\_a

the first required component animation

 animation\_b

the second required component animation

 animation\_c

either the third component, or NULL if only adding 2 components

#### Returns

The newly created sequence animation

Animation \* animation\_sequence\_create\_from\_array(Animation \*\* animation\_array, [uint32\_t](/docs/c/Standard_C/#uint32_t) array\_len)

An alternate form of [animation\_sequence\_create()](/docs/c/User_Interface/Animation/#animation_sequence_create) that accepts an array of other animations.

##### Note

the maximum number of elements allowed in animation\_array is 256

#### Parameters
 animation\_array

an array of component animations to include

 array\_len

the number of elements in the animation\_array

#### Returns

The newly created sequence animation

Animation \* animation\_spawn\_create(Animation \* animation\_a, Animation \* animation\_b, Animation \* animation\_c, ...)

Create a new spawn animation from a list of 2 or more other animations. The returned animation owns the animations that were provided as arguments and no further write operations on those handles are allowed. The variable length argument list must be terminated with a NULL ptr.

##### Note

the maximum number of animations that can be supplied to this method is 20

#### Parameters
 animation\_a

the first required component animation

 animation\_b

the second required component animation

 animation\_c

either the third component, or NULL if only adding 2 components

#### Returns

The newly created spawn animation or NULL on failure

Animation \* animation\_spawn\_create\_from\_array(Animation \*\* animation\_array, [uint32\_t](/docs/c/Standard_C/#uint32_t) array\_len)

An alternate form of [animation\_spawn\_create()](/docs/c/User_Interface/Animation/#animation_spawn_create) that accepts an array of other animations.

##### Note

the maximum number of elements allowed in animation\_array is 256

#### Parameters
 animation\_array

an array of component animations to include

 array\_len

the number of elements in the animation\_array

#### Returns

The newly created spawn animation or NULL on failure

bool animation\_set\_elapsed(Animation \* animation, [uint32\_t](/docs/c/Standard_C/#uint32_t) elapsed\_ms)

Seek to a specific location in the animation. Only forward seeking is allowed. Returns true if successful, false if the passed in seek location is invalid.

#### Parameters
 animation

the animation for which to set the elapsed.

 elapsed\_ms

the new elapsed time in milliseconds

#### Returns

true if successful, false if the requested elapsed is invalid.

bool animation\_get\_elapsed(Animation \* animation, int32\_t \* elapsed\_ms)

Get the current location in the animation.

##### Note

The animation must be scheduled to get the elapsed time. If it is not schedule, this method will return false.

#### Parameters
 animation

The animation for which to fetch the elapsed.

 elapsed\_ms (out)

pointer to variable that will contain the elapsed time in milliseconds

#### Returns

true if successful, false on failure

bool animation\_set\_reverse(Animation \* animation, bool reverse)

Set an animation to run in reverse (or forward)

##### Note

Trying to set an attribute when an animation is immutable will return false (failure). An animation is immutable once it has been added to a sequence or spawn animation or has been scheduled.

#### Parameters
 animation

the animation to operate on

 reverse

set to true to run in reverse, false to run forward

#### Returns

true if successful, false on failure

bool animation\_get\_reverse(Animation \* animation)

Get the reverse setting of an animation.

#### Parameters
 animation

The animation for which to get the setting

#### Returns

the reverse setting

bool animation\_set\_play\_count(Animation \* animation, [uint32\_t](/docs/c/Standard_C/#uint32_t) play\_count)

Set an animation to play N times. The default is 1.

##### Note

Trying to set an attribute when an animation is immutable will return false (failure). An animation is immutable once it has been added to a sequence or spawn animation or has been scheduled.

#### Parameters
 animation

the animation to set the play count of

 play\_count

number of times to play this animation. Set to ANIMATION\_PLAY\_COUNT\_INFINITE to make an animation repeat indefinitely.

#### Returns

true if successful, false on failure

[uint32\_t](/docs/c/Standard_C/#uint32_t) animation\_get\_play\_count(Animation \* animation)

Get the play count of an animation.

#### Parameters
 animation

The animation for which to get the setting

#### Returns

the play count

bool animation\_set\_duration(Animation \* animation, [uint32\_t](/docs/c/Standard_C/#uint32_t) duration\_ms)

Sets the time in milliseconds that an animation takes from start to finish.

##### Note

Trying to set an attribute when an animation is immutable will return false (failure). An animation is immutable once it has been added to a sequence or spawn animation or has been scheduled.

#### Parameters
 animation

The animation for which to set the duration.

 duration\_ms

The duration in milliseconds of the animation. This excludes any optional delay as set using [animation\_set\_delay()](/docs/c/User_Interface/Animation/#animation_set_delay).

#### Returns

true if successful, false on failure

[uint32\_t](/docs/c/Standard_C/#uint32_t) animation\_get\_duration(Animation \* animation, bool include\_delay, bool include\_play\_count)

Get the static duration of an animation from start to end (ignoring how much has already played, if any).

#### Parameters
 animation

The animation for which to get the duration

 include\_delay

if true, include the delay time

 include\_play\_count

if true, incorporate the play\_count

#### Returns

the duration, in milliseconds. This includes any optional delay a set using [animation\_set\_delay](/docs/c/User_Interface/Animation/#animation_set_delay).

bool animation\_set\_delay(Animation \* animation, [uint32\_t](/docs/c/Standard_C/#uint32_t) delay\_ms)

Sets an optional delay for the animation.

##### Note

Trying to set an attribute when an animation is immutable will return false (failure). An animation is immutable once it has been added to a sequence or spawn animation or has been scheduled.

#### Parameters
 animation

The animation for which to set the delay.

 delay\_ms

The delay in milliseconds that the animation system should wait from the moment the animation is scheduled to starting the animation.

#### Returns

true if successful, false on failure

[uint32\_t](/docs/c/Standard_C/#uint32_t) animation\_get\_delay(Animation \* animation)

Get the delay of an animation in milliseconds.

#### Parameters
 animation

The animation for which to get the setting

#### Returns

the delay in milliseconds

bool animation\_set\_curve(Animation \* animation, [AnimationCurve](/docs/c/User_Interface/Animation/#AnimationCurve) curve)

Sets the animation curve for the animation.

##### Note

Trying to set an attribute when an animation is immutable will return false (failure). An animation is immutable once it has been added to a sequence or spawn animation or has been scheduled.

#### Parameters
 animation

The animation for which to set the curve.

 curve

The type of curve.

#### Returns

true if successful, false on failure

#### See Also
[AnimationCurve](/docs/c/User_Interface/Animation/#AnimationCurve)

[AnimationCurve](/docs/c/User_Interface/Animation/#AnimationCurve) animation\_get\_curve(Animation \* animation)

Gets the animation curve for the animation.

#### Parameters
 animation

The animation for which to get the curve.

#### Returns

The type of curve.

bool animation\_set\_custom\_curve(Animation \* animation, [AnimationCurveFunction](/docs/c/User_Interface/Animation/#AnimationCurveFunction) curve\_function)

Sets a custom animation curve function.

##### Note

Trying to set an attribute when an animation is immutable will return false (failure). An animation is immutable once it has been added to a sequence or spawn animation or has been scheduled.

#### Parameters
 animation

The animation for which to set the curve.

 curve\_function

The custom animation curve function.

#### Returns

true if successful, false on failure

#### See Also
[AnimationCurveFunction](/docs/c/User_Interface/Animation/#AnimationCurveFunction)

[AnimationCurveFunction](/docs/c/User_Interface/Animation/#AnimationCurveFunction) animation\_get\_custom\_curve(Animation \* animation)

Gets the custom animation curve function for the animation.

#### Parameters
 animation

The animation for which to get the curve.

#### Returns

The custom animation curve function for the given animation. NULL if not set.

bool animation\_set\_handlers(Animation \* animation, [AnimationHandlers](/docs/c/User_Interface/Animation/#AnimationHandlers) callbacks, void \* context)

Sets the callbacks for the animation. Often an application needs to run code at the start or at the end of an animation. Using this function is possible to register callback functions with an animation, that will get called at the start and end of the animation.

##### Note

Trying to set an attribute when an animation is immutable will return false (failure). An animation is immutable once it has been added to a sequence or spawn animation or has been scheduled.

#### Parameters
 animation

The animation for which to set up the callbacks.

 callbacks

The callbacks.

 context

A pointer to application specific data, that will be passed as an argument by the animation subsystem when a callback is called.

#### Returns

true if successful, false on failure

void \* animation\_get\_context(Animation \* animation)

Gets the application-specific callback context of the animation. This `void` pointer is passed as an argument when the animation system calls [AnimationHandlers](/docs/c/User_Interface/Animation/#AnimationHandlers) callbacks. The context pointer can be set to point to any application specific data using [animation\_set\_handlers()](/docs/c/User_Interface/Animation/#animation_set_handlers).

#### Parameters
 animation

The animation.

#### See Also
[animation\_set\_handlers](/docs/c/User_Interface/Animation/#animation_set_handlers)

bool animation\_schedule(Animation \* animation)

Schedules the animation. Call this once after configuring an animation to get it to start running.

If the animation's implementation has a `.setup` callback it will get called before this function returns.

##### Note

If the animation was already scheduled, it will first unschedule it and then re-schedule it again. Note that in that case, the animation's `.stopped` handler, the implementation's `.teardown` and `.setup` will get called, due to the unscheduling and scheduling.

#### Parameters
 animation

The animation to schedule.

#### Returns

true if successful, false on failure

#### See Also
[animation\_unschedule()](/docs/c/User_Interface/Animation/#animation_unschedule)

bool animation\_unschedule(Animation \* animation)

Unschedules the animation, which in effect stops the animation.

##### Notes

If the animation was not yet finished, unscheduling it will cause its `.stopped` handler to get called, with the "finished" argument set to false.

If the animation is not scheduled or NULL, calling this routine is effectively a no-op

#### Parameters
 animation

The animation to unschedule.

#### Returns

true if successful, false on failure

#### See Also
[animation\_schedule()](/docs/c/User_Interface/Animation/#animation_schedule)

void animation\_unschedule\_all(void)

Unschedules all animations of the application.

#### See Also
[animation\_unschedule](/docs/c/User_Interface/Animation/#animation_unschedule)

bool animation\_is\_scheduled(Animation \* animation)

##### Note

An animation will be scheduled when it is running and not finished yet. An animation that has finished is automatically unscheduled. For convenience, passing in a NULL animation argument will simply return false

#### Parameters
 animation

The animation for which to get its scheduled state.

#### Returns

True if the animation was scheduled, or false if it was not.

#### See Also
[animation\_schedule](/docs/c/User_Interface/Animation/#animation_schedule)  
[animation\_unschedule](/docs/c/User_Interface/Animation/#animation_unschedule)

bool animation\_set\_implementation(Animation \* animation, const [AnimationImplementation](/docs/c/User_Interface/Animation/#AnimationImplementation) \* implementation)

Sets the implementation of the custom animation. When implementing custom animations, use this function to specify what functions need to be called to for the setup, frame update and teardown of the animation.

##### Note

Trying to set an attribute when an animation is immutable will return false (failure). An animation is immutable once it has been added to a sequence or spawn animation or has been scheduled.

#### Parameters
 animation

The animation for which to set the implementation.

 implementation

The structure with function pointers to the implementation of the setup, update and teardown functions.

#### Returns

true if successful, false on failure

#### See Also
[AnimationImplementation](/docs/c/User_Interface/Animation/#AnimationImplementation)

const [AnimationImplementation](/docs/c/User_Interface/Animation/#AnimationImplementation) \* animation\_get\_implementation(Animation \* animation)

Gets the implementation of the custom animation.

#### Parameters
 animation

The animation for which to get the implementation.

#### Returns

NULL if animation implementation has not been setup.

#### See Also
[AnimationImplementation](/docs/c/User_Interface/Animation/#AnimationImplementation)

## Data Structure Documentation

struct AnimationHandlers

The handlers that will get called when an animation starts and stops. See documentation with the function pointer types for more information.

#### Data Fields
[AnimationStartedHandler](/docs/c/User_Interface/Animation/#AnimationStartedHandler) started

The handler that will be called when an animation is started.

[AnimationStoppedHandler](/docs/c/User_Interface/Animation/#AnimationStoppedHandler) stopped

The handler that will be called when an animation is stopped.

#### See Also
[animation\_set\_handlers](/docs/c/User_Interface/Animation/#animation_set_handlers)

struct AnimationImplementation

The 3 callbacks that implement a custom animation. Only the `.update` callback is mandatory, `.setup` and `.teardown` are optional. See the documentation with the function pointer typedefs for more information.

The diagram below illustrates the order in which callbacks can be expected to get called over the life cycle of an animation. It also illustrates where the implementation of different animation callbacks are intended to be “living”. ![](/assets/images/docs/c/aplite/animations.png) ![](/assets/images/docs/c/aplite/animations.png) ![](/assets/images/docs/c/aplite/animations.png) ![](/assets/images/docs/c/aplite/animations.png) ![](/assets/images/docs/c/aplite/animations.png)

##### Note

The `.setup` callback is called immediately after scheduling the animation, regardless if there is a delay set for that animation using [animation\_set\_delay()](/docs/c/User_Interface/Animation/#animation_set_delay).

#### Data Fields
[AnimationSetupImplementation](/docs/c/User_Interface/Animation/#AnimationSetupImplementation) setup

Called by the animation system when an animation is scheduled, to prepare it for running. This callback is optional and can be left `NULL` when not needed.

[AnimationUpdateImplementation](/docs/c/User_Interface/Animation/#AnimationUpdateImplementation) update

Called by the animation system when the animation needs to calculate the next animation frame. This callback is mandatory and should not be left `NULL`.

[AnimationTeardownImplementation](/docs/c/User_Interface/Animation/#AnimationTeardownImplementation) teardown

Called by the animation system when an animation is unscheduled, to clean up after it has run. This callback is optional and can be left `NULL` when not needed.

#### See Also
[AnimationSetupImplementation](/docs/c/User_Interface/Animation/#AnimationSetupImplementation)  
[AnimationUpdateImplementation](/docs/c/User_Interface/Animation/#AnimationUpdateImplementation)  
[AnimationTeardownImplementation](/docs/c/User_Interface/Animation/#AnimationTeardownImplementation)

## Enum Documentation

enum AnimationCurve

Values that are used to indicate the different animation curves, which determine the speed at which the animated value(s) change(s).

#### Enumerators
AnimationCurveLinear

Linear curve: the velocity is constant.

AnimationCurveEaseIn

Bicubic ease-in: accelerate from zero velocity.

AnimationCurveEaseOut

Bicubic ease-in: decelerate to zero velocity.

AnimationCurveEaseInOut

Bicubic ease-in-out: accelerate from zero velocity, decelerate to zero velocity.

AnimationCurveDefaultAnimationCurveCustomFunction

Custom (user-provided) animation curve.

AnimationCurveCustomInterpolationFunction

User-provided interpolation function.

AnimationCurve\_Reserved1AnimationCurve\_Reserved2

## Typedef Documentation

 typedef struct Animation Animation

 typedef int32\_t AnimationProgress

The type used to represent how far an animation has progressed. This is passed to the animation's update handler.

 typedef [AnimationProgress](/docs/c/User_Interface/Animation/#AnimationProgress)(\* AnimationCurveFunction)(AnimationProgress linear\_distance) 

The function pointer type of a custom animation curve.

#### Parameters
 linear\_distance

The linear normalized animation distance to be curved.

#### See Also
[animation\_set\_custom\_curve](/docs/c/User_Interface/Animation/#animation_set_custom_curve)

 typedef void(\* AnimationStartedHandler)(Animation \*animation, void \*context) 

The function pointer type of the handler that will be called when an animation is started, just before updating the first frame of the animation.

##### Note

This is called after any optional delay as set by [animation\_set\_delay()](/docs/c/User_Interface/Animation/#animation_set_delay) has expired.

#### Parameters
 animation

The animation that was started.

 context

The pointer to custom, application specific data, as set using [animation\_set\_handlers()](/docs/c/User_Interface/Animation/#animation_set_handlers)

#### See Also
[animation\_set\_handlers](/docs/c/User_Interface/Animation/#animation_set_handlers)

 typedef void(\* AnimationStoppedHandler)(Animation \*animation, bool finished, void \*context) 

The function pointer type of the handler that will be called when the animation is stopped.

##### Note

This animation (i.e.: the `animation` parameter) may be destroyed here. It is not recommended to unschedule or destroy a **different** Animation within this Animation's `stopped` handler.

#### Parameters
 animation

The animation that was stopped.

 finished

True if the animation was stopped because it was finished normally, or False if the animation was stopped prematurely, because it was unscheduled before finishing.

 context

The pointer to custom, application specific data, as set using [animation\_set\_handlers()](/docs/c/User_Interface/Animation/#animation_set_handlers)

#### See Also
[animation\_set\_handlers](/docs/c/User_Interface/Animation/#animation_set_handlers)

 typedef void(\* AnimationSetupImplementation)(Animation \*animation) 

Pointer to function that (optionally) prepares the animation for running. This callback is called when the animation is added to the scheduler.

#### Parameters
 animation

The animation that needs to be set up.

#### See Also
[animation\_schedule](/docs/c/User_Interface/Animation/#animation_schedule)  
[AnimationTeardownImplementation](/docs/c/User_Interface/Animation/#AnimationTeardownImplementation)

 typedef void(\* AnimationUpdateImplementation)(Animation \*animation, const AnimationProgress progress) 

Pointer to function that updates the animation according to the given normalized progress. This callback will be called repeatedly by the animation scheduler whenever the animation needs to be updated.

#### Parameters
 animation

The animation that needs to update; gets passed in by the animation framework.

 progress

The current normalized progress; gets passed in by the animation framework for each animation frame. The value [ANIMATION\_NORMALIZED\_MIN](/docs/c/User_Interface/Animation/#ANIMATION_NORMALIZED_MIN) represents the start and [ANIMATION\_NORMALIZED\_MAX](/docs/c/User_Interface/Animation/#ANIMATION_NORMALIZED_MAX) represents the end. Values outside this range (generated by a custom curve function) can be used to implement features like a bounce back effect, where the progress exceeds the desired final value before returning to complete the animation. When using a system provided curve function, each frame during the animation will have a progress value between [ANIMATION\_NORMALIZED\_MIN](/docs/c/User_Interface/Animation/#ANIMATION_NORMALIZED_MIN) and [ANIMATION\_NORMALIZED\_MAX](/docs/c/User_Interface/Animation/#ANIMATION_NORMALIZED_MAX) based on the animation duration and the [AnimationCurve](/docs/c/User_Interface/Animation/#AnimationCurve). For example, say an animation was scheduled at t = 1.0s, has a delay of 1.0s, a duration of 2.0s and a curve of AnimationCurveLinear. Then the .update callback will get called on t = 2.0s with distance\_normalized = [ANIMATION\_NORMALIZED\_MIN](/docs/c/User_Interface/Animation/#ANIMATION_NORMALIZED_MIN). For each frame thereafter until t = 4.0s, the update callback will get called where distance\_normalized is ([ANIMATION\_NORMALIZED\_MIN](/docs/c/User_Interface/Animation/#ANIMATION_NORMALIZED_MIN)

- ((([ANIMATION\_NORMALIZED\_MAX](/docs/c/User_Interface/Animation/#ANIMATION_NORMALIZED_MAX) - [ANIMATION\_NORMALIZED\_MIN](/docs/c/User_Interface/Animation/#ANIMATION_NORMALIZED_MIN)) \* t) / duration)). Other system animation curve functions will result in a non-linear relation between distance\_normalized and time. 

 typedef void(\* AnimationTeardownImplementation)(Animation \*animation) 

Pointer to function that (optionally) cleans up the animation. This callback is called when the animation is removed from the scheduler. In case the `.setup` implementation allocated any memory, this is a good place to release that memory again.

#### Parameters
 animation

The animation that needs to be teared down.

#### See Also
[animation\_unschedule](/docs/c/User_Interface/Animation/#animation_unschedule)  
[AnimationSetupImplementation](/docs/c/User_Interface/Animation/#AnimationSetupImplementation)

## Macro Definition Documentation

#define ANIMATION\_DURATION\_INFINITE UINT32\_MAX

Constant to indicate "infinite" duration. This can be used with [animation\_set\_duration()](/docs/c/User_Interface/Animation/#animation_set_duration) to indicate that the animation should run indefinitely. This is useful when implementing for example a frame-by-frame simulation that does not have a clear ending (e.g. a game).

##### Notes

Note that `distance_normalized` parameter that is passed into the `.update` implementation is meaningless in when an infinite duration is used.

This can be returned by animation\_get\_duration (if the play count is infinite)

#define ANIMATION\_PLAY\_COUNT\_INFINITE UINT32\_MAX

Constant to indicate infinite play count. Can be passed to [animation\_set\_play\_count()](/docs/c/User_Interface/Animation/#animation_set_play_count) to repeat indefinitely.

##### Note

This can be returned by [animation\_get\_play\_count()](/docs/c/User_Interface/Animation/#animation_get_play_count).

#define ANIMATION\_NORMALIZED\_MIN 0

The normalized distance at the start of the animation.

#define ANIMATION\_NORMALIZED\_MAX 65535

The normalized distance at the end of the animation.
