# UnobstructedArea

Source: https://developer.repebble.com/docs/c/User_Interface/UnobstructedArea/index.html

## Function Documentation

void unobstructed\_area\_service\_subscribe(UnobstructedAreaHandlers handlers, void \* context)

Subscribe to be notified when the app's unobstructed area changes. When an unobstructed area begins changing, the `will_change` handler will be called, and every `will_change` call is always paired with a `did_change` call that occurs when it is done changing given that the `will_change` and `did_change` handlers are set. When subscribing while the unobstructed area is changing, the `will_change` handler will be called after subscription in the next event loop.

#### Parameters
 handlers

The handlers that should be called when the unobstructed area changes.

 context

A user-provided context that will be passed to the callback handlers.

#### See Also
[layer\_get\_unobstructed\_bounds](/docs/c/User_Interface/Layers/#layer_get_unobstructed_bounds)

void unobstructed\_area\_service\_unsubscribe(void)

Unsubscribe from notifications about changes to the app's unobstructed area.

## Data Structure Documentation

struct UnobstructedAreaHandlers

#### Data Fields
[UnobstructedAreaWillChangeHandler](/docs/c/User_Interface/UnobstructedArea/#UnobstructedAreaWillChangeHandler) will\_change

Handler that will be called just before the unobstructed area will begin changing.

[UnobstructedAreaChangeHandler](/docs/c/User_Interface/UnobstructedArea/#UnobstructedAreaChangeHandler) change

Handler that will be called every time the unobstructed area changes.

[UnobstructedAreaDidChangeHandler](/docs/c/User_Interface/UnobstructedArea/#UnobstructedAreaDidChangeHandler) did\_change

Handler that will be called after the unobstructed area has finished changing.

## Typedef Documentation

 typedef void(\* UnobstructedAreaWillChangeHandler)(GRect final\_unobstructed\_screen\_area, void \*context) 

Handler that will be called just before the unobstructed area will begin changing.

#### Parameters
 final\_unobstructed\_screen\_area

The final unobstructed screen area after the unobstructed area has finished changing.

 context

A user-provided context.

 typedef void(\* UnobstructedAreaChangeHandler)(AnimationProgress progress, void \*context) 

Handler that will be called every time the unobstructed area changes.

#### Parameters
 progress

The progress of the animation changing the unobstructed area.

 context

A user-provided context.

 typedef void(\* UnobstructedAreaDidChangeHandler)(void \*context) 

Handler that will be called after the unobstructed area has finished changing.

#### Parameters
 context

A user-provided context.
