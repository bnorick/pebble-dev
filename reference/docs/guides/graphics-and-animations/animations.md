# Animations

Source: https://developer.repebble.com/guides/graphics-and-animations/animations/

The [`Animation`](/docs/c/User_Interface/Animation/ "Animation") API allows a variety of different types of value to be smoothly animated from an initial value to a new value over time. Animations can also use built-in easing curves to affect how the transition behaves.

## Using PropertyAnimations

The most common use of animations is to move a [`Layer`](/docs/c/User_Interface/Layers/#Layer "Layer") (or similar) around the display. For example, to show or hide some information or animate the time changing in a watchface.

The simplest method of animating a [`Layer`](/docs/c/User_Interface/Layers/#Layer "Layer") (such as a [`TextLayer`](/docs/c/User_Interface/Layers/TextLayer/ "TextLayer")) is to use a [`PropertyAnimation`](/docs/c/User_Interface/Animation/PropertyAnimation/ "PropertyAnimation"), which animates a property of the target object. In this example, the target is the frame property, which is a [`GRect`](/docs/c/Graphics/Graphics_Types/#GRect "GRect") To animate the this property, [`property_animation_create_layer_frame()`](/docs/c/User_Interface/Animation/PropertyAnimation/#property_animation_create_layer_frame "property\_animation\_create\_layer\_frame") is used, which is a convenience [`PropertyAnimation`](/docs/c/User_Interface/Animation/PropertyAnimation/ "PropertyAnimation") implementation provided by the SDK.

```
static Layer \*s\_layer;
```

Create the Layer during [`Window`](/docs/c/User_Interface/Window/ "Window") initialization:

```
// Create the Layers\_layer = layer\_create(some\_bounds);
```

Determine the start and end values of the [`Layer`](/docs/c/User_Interface/Layers/#Layer "Layer")'s frame. These are the 'from' and 'to' locations and sizes of the [`Layer`](/docs/c/User_Interface/Layers/#Layer "Layer") before and after the animation takes place:

```
// The start and end frames - move the Layer 40 pixels to the rightGRect start = GRect(10, 10, 20, 20);GRect finish = GRect(50, 10, 20, 20);
```

At the appropriate time, create a [`PropertyAnimation`](/docs/c/User_Interface/Animation/PropertyAnimation/ "PropertyAnimation") to animate the[`Layer`](/docs/c/User_Interface/Layers/#Layer "Layer"), specifying the `start` and `finish` values as parameters:

```
// Animate the LayerPropertyAnimation \*prop\_anim = property\_animation\_create\_layer\_frame(s\_layer, &start, &finish);
```

Configure the attributes of the [`Animation`](/docs/c/User_Interface/Animation/ "Animation"), such as the delay before starting, and total duration (in milliseconds):

```
// Get the AnimationAnimation \*anim = property\_animation\_get\_animation(prop\_anim);// Choose parametersconst int delay\_ms = 1000;const int duration\_ms = 500;// Configure the Animation's curve, delay, and durationanimation\_set\_curve(anim, AnimationCurveEaseOut);animation\_set\_delay(anim, delay\_ms);animation\_set\_duration(anim, duration\_ms);
```

Finally, schedule the [`Animation`](/docs/c/User_Interface/Animation/ "Animation") to play at the next possible opportunity (usually immediately):

```
// Play the animationanimation\_schedule(anim);
```

If the app requires knowledge of the start and end times of an [`Animation`](/docs/c/User_Interface/Animation/ "Animation"), it is possible to register [`AnimationHandlers`](/docs/c/User_Interface/Animation/#AnimationHandlers "AnimationHandlers") to be notified of these events. The handlers should be created with the signature of these examples shown below:

```
static void anim\_started\_handler(Animation \*animation, void \*context) {APP\_LOG(APP\_LOG\_LEVEL\_DEBUG, "Animation started!");}static void anim\_stopped\_handler(Animation \*animation, bool finished, void \*context) {APP\_LOG(APP\_LOG\_LEVEL\_DEBUG, "Animation stopped!");}
```

Register the handlers with an optional third context parameter **before** scheduling the [`Animation`](/docs/c/User_Interface/Animation/ "Animation"):

```
// Set some handlersanimation\_set\_handlers(anim, (AnimationHandlers) {.started = anim\_started\_handler,.stopped = anim\_stopped\_handler}, NULL);
```

With the handlers registered, the start and end times of the [`Animation`](/docs/c/User_Interface/Animation/ "Animation") can be detected by the app and used as appropriate.

### Other Types of PropertyAnimation

In addition to [`property_animation_create_layer_frame()`](/docs/c/User_Interface/Animation/PropertyAnimation/#property_animation_create_layer_frame "property\_animation\_create\_layer\_frame"), it is also possible to animate the origin of a [`Layer`](/docs/c/User_Interface/Layers/#Layer "Layer")'s bounds using[`property_animation_create_bounds_origin()`](/docs/c/User_Interface/Animation/PropertyAnimation/#property_animation_create_bounds_origin "property\_animation\_create\_bounds\_origin"). Animation of more types of data can be achieved using custom implementations and one the following provided update implementations and the associated [getters and setters](/docs/c/User_Interface/Animation/PropertyAnimation/#property_animation_update_int16 "property\_animation\_update\_int16"):

- [`property_animation_update_int16`](/docs/c/User_Interface/Animation/PropertyAnimation/#property_animation_update_int16 "property\_animation\_update\_int16") - Animate an `int16`.
- [`property_animation_update_uint32`](/docs/c/User_Interface/Animation/PropertyAnimation/#property_animation_update_uint32 "property\_animation\_update\_uint32") - Animate a `uint32`.
- [`property_animation_update_gpoint`](/docs/c/User_Interface/Animation/PropertyAnimation/#property_animation_update_gpoint "property\_animation\_update\_gpoint") - Animate a [`GPoint`](/docs/c/Graphics/Graphics_Types/#GPoint "GPoint").
- [`property_animation_update_grect`](/docs/c/User_Interface/Animation/PropertyAnimation/#property_animation_update_grect "property\_animation\_update\_grect") - Animate a [`GRect`](/docs/c/Graphics/Graphics_Types/#GRect "GRect")
- [`property_animation_update_gcolor8`](/docs/c/User_Interface/Animation/PropertyAnimation/#property_animation_update_gcolor8 "property\_animation\_update\_gcolor8") - Animate a [`GColor8`](/docs/c/Graphics/Graphics_Types/#GColor8 "GColor8").

## Custom Animation Implementations

Beyond the convenience functions provided by the SDK, apps can implement their own [`Animation`](/docs/c/User_Interface/Animation/ "Animation") by using custom callbacks for each stage of the animation playback process. A [`PropertyAnimation`](/docs/c/User_Interface/Animation/PropertyAnimation/ "PropertyAnimation") is an example of such an implementation.

The callbacks to implement are the `.setup`, `.update`, and `.teardown` members of an [`AnimationImplementation`](/docs/c/User_Interface/Animation/#AnimationImplementation "AnimationImplementation") object. Some example implementations are shown below. It is in the `.update` callback where the value of `progress` can be used to modify the custom target of the animation. For example, some percentage of completion:

```
static void implementation\_setup(Animation \*animation) {APP\_LOG(APP\_LOG\_LEVEL\_INFO, "Animation started!");}static void implementation\_update(Animation \*animation, const AnimationProgress progress) {// Animate some completion variables\_animation\_percent = ((int)progress \* 100) / ANIMATION\_NORMALIZED\_MAX;APP\_LOG(APP\_LOG\_LEVEL\_INFO, "Animation progress: %d%%", s\_animation\_percent);}static void implementation\_teardown(Animation \*animation) {APP\_LOG(APP\_LOG\_LEVEL\_INFO, "Animation finished!");}// This needs to exist while the event loop runsstatic const AnimationImplementation s\_implementation = {.setup = implementation\_setup,.update = implementation\_update,.teardown = implementation\_teardown};
```

Once these are in place, create a new [`Animation`](/docs/c/User_Interface/Animation/ "Animation") , specifying the new custom implementation as a `const` object pointer at the appropriate time:

```
// Create a new AnimationAnimation \*animation = animation\_create();animation\_set\_delay(animation, 1000);animation\_set\_duration(animation, 1000);// Create the AnimationImplementationanimation\_set\_implementation(animation, &s\_implementation);// Play the Animationanimation\_schedule(animation);
```

The output of the example above will look like the snippet shown below (edited for brevity). Note the effect of the easing [`AnimationCurve`](/docs/c/User_Interface/Animation/#AnimationCurve "AnimationCurve") on the progress value:

```
[13:42:33] main.c:11> Animation started!
[13:42:34] main.c:19> Animation progress: 0%
[13:42:34] main.c:19> Animation progress: 0%
[13:42:34] main.c:19> Animation progress: 0%
[13:42:34] main.c:19> Animation progress: 2%
[13:42:34] main.c:19> Animation progress: 3%
[13:42:34] main.c:19> Animation progress: 5%
[13:42:34] main.c:19> Animation progress: 7%
[13:42:34] main.c:19> Animation progress: 10%
[13:42:34] main.c:19> Animation progress: 14%
[13:42:35] main.c:19> Animation progress: 17%
[13:42:35] main.c:19> Animation progress: 21%
[13:42:35] main.c:19> Animation progress: 26%

...

[13:42:35] main.c:19> Animation progress: 85%
[13:42:35] main.c:19> Animation progress: 88%
[13:42:35] main.c:19> Animation progress: 91%
[13:42:35] main.c:19> Animation progress: 93%
[13:42:35] main.c:19> Animation progress: 95%
[13:42:35] main.c:19> Animation progress: 97%
[13:42:35] main.c:19> Animation progress: 98%
[13:42:35] main.c:19> Animation progress: 99%
[13:42:35] main.c:19> Animation progress: 99%
[13:42:35] main.c:19> Animation progress: 100%
[13:42:35] main.c:23> Animation finished!
```

## Timers

[`AppTimer`](/docs/c/Foundation/Timer/ "Timer") objects can be used to schedule updates to variables and objects at a later time. They can be used to implement frame-by-frame animations as an alternative to using the [`Animation`](/docs/c/User_Interface/Animation/ "Animation") API. They can also be used in a more general way to schedule events to occur at some point in the future (such as UI updates) while the app is open.

A thread-blocking alternative for small pauses is [`psleep()`](/docs/c/Foundation/Timer/#psleep "psleep"), but this is **not** recommended for use in loops updating UI (such as a counter), or for scheduling [`AppMessage`](/docs/c/Foundation/AppMessage/ "AppMessage") messages, which rely on the event loop to do their work.

> Note: To create timed events in the future that persist after an app is closed, check out the [`Wakeup`](/docs/c/Foundation/Wakeup/ "Wakeup") API.

When a timer elapses, it will call a developer-defined [`AppTimerCallback`](/docs/c/Foundation/Timer/#AppTimerCallback "AppTimerCallback"). This is where the code to be executed after the timed interval should be placed. The callback will only be called once, so use this opportunity to re-register the timer if it should repeat.

```
static void timer\_callback(void \*context) {APP\_LOG(APP\_LOG\_LEVEL\_INFO, "Timer elapsed!");}
```

Schedule the timer with a specific `delay` interval, the name of the callback to fire, and an optional context pointer:

```
const int delay\_ms = 5000;// Schedule the timerapp\_timer\_register(delay\_ms, timer\_callback, NULL);
```

If the timer may need to be cancelled or rescheduled at a later time, ensure a reference to it is kept for later use:

```
static AppTimer \*s\_timer;
```

```
// Register the timer, and keep a handle to its\_timer = app\_timer\_register(delay\_ms, timer\_callback, NULL);
```

If the timer needs to be cancelled, use the previous reference. If it has already elapsed, nothing will occur:

```
// Cancel the timerapp\_timer\_cancel(s\_timer);
```

## Sequence and Spawn Animations

The Pebble SDK also includes the capability to build up composite animations built from other [`Animation`](/docs/c/User_Interface/Animation/ "Animation") objects. There are two types: a sequence animation and a spawn animation.

- A sequence animation is a set of two or more other animations that are played out in **series** (one after another). For example, a pair of timed animations to show and hide a [`Layer`](/docs/c/User_Interface/Layers/#Layer "Layer").

- A spawn animation is a set of two or more other animations that are played out in **parallel**. A spawn animation acts the same as creating and starting two or more animations at the same time, but has the advantage that it can be included as part of a sequence animation.

> Note: Composite animations can be composed of other composite animations.

### Important Considerations

When incorporating an [`Animation`](/docs/c/User_Interface/Animation/ "Animation") into a sequence or spawn animation, there are a couple of points to note:

- Any single animation cannot appear more than once in the list of animations used to create a more complex animation.

- A composite animation assumes ownership of its component animations once it has been created.

- Once an animation has been added to a composite animation, it becomes immutable. This means it can only be read, and not written to. Attempts to modify such an animation after it has been added to a composite animation will fail.

- Once an animation has been added to a composite animation, it cannot then be used to build a different composite animation.

### Creating a Sequence Animation

To create a sequence animation, first create the component [`Animation`](/docs/c/User_Interface/Animation/ "Animation") objects that will be used to build it.

```
// Create the first AnimationPropertyAnimation \*prop\_anim = property\_animation\_create\_layer\_frame(s\_layer, &start, &finish);Animation \*animation\_a = property\_animation\_get\_animation(prop\_anim);// Set some propertiesanimation\_set\_delay(animation\_a, 1000);animation\_set\_duration(animation\_a, 500);// Clone the first, modify the duration and reverse it.Animation \*animation\_b = animation\_clone(animation\_a);animation\_set\_reverse(animation\_b, true);animation\_set\_duration(animation\_b, 1000);
```

Use these component animations to create the sequence animation. You can either specify the components as a list or pass an array. Both approaches are shown below.

#### Using a List

You can specify up to 20 [`Animation`](/docs/c/User_Interface/Animation/ "Animation") objects as parameters to`animation_sequence_create()`. The list must always be terminated with `NULL` to mark the end.

```
// Create the sequenceAnimation \*sequence = animation\_sequence\_create(animation\_a, animation\_b, NULL);// Play the sequenceanimation\_schedule(sequence);
```

#### Using an Array

You can also specify the component animations using a dynamically allocated array. Give this to `animation_sequence_create_from_array()` along with the size of the array.

```
const uint32\_t array\_length = 2;// Create the arrayAnimation \*\*arr = (Animation\*\*)malloc(array\_length \* sizeof(Animation\*));arr[0] = animation\_a;arr[1] = animation\_b;// Create the sequence, set to loop foreverAnimation \*sequence = animation\_sequence\_create\_from\_array(arr, array\_length);animation\_set\_play\_count(sequence, ANIMATION\_DURATION\_INFINITE);// Play the sequenceanimation\_schedule(sequence);// Destroy the arrayfree(arr);
```

### Creating a Spawn Animation

Creating a spawn animation is done in a very similiar way to a sequence animation. The animation is built up from component animations which are then all started at the same time. This simplifies the task of precisely timing animations that are designed to coincide.

The first step is the same as for sequence animations, which is to create a number of component animations to be spawned together.

```
// Create the first animationAnimation \*animation\_a = animation\_create();animation\_set\_duration(animation\_a, 1000);// Clone the first, modify the duration and reverse it.Animation \*animation\_b = animation\_clone(animation\_a);animation\_set\_reverse(animation\_b, true);animation\_set\_duration(animation\_b, 300);
```

Next, the spawn animation is created in a similar manner to the sequence animation with a `NULL` terminated list of parameters:

```
// Create the spawn animationAnimation \*spawn = animation\_spawn\_create(animation\_a, animation\_b, NULL);// Play the animationanimation\_schedule(spawn);
```

Alternatively the spawn animation can be created with an array of [`Animation`](/docs/c/User_Interface/Animation/ "Animation")objects.

```
const uint32\_t array\_length = 2;// Create the arrayAnimation \*\*arr = (Animation\*\*)malloc(array\_length \* sizeof(Animation\*));arr[0] = animation\_a;arr[1] = animation\_b;// Create the sequence and set the play count to 3Animation \*spawn = animation\_spawn\_create\_from\_array(arr, array\_length);animation\_set\_play\_count(spawn, 3);// Play the spawn animationanimation\_schedule(spawn);// Destroy the arrayfree(arr);
```
