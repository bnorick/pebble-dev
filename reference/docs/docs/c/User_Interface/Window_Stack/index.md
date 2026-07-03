# Window Stack

Source: https://developer.repebble.com/docs/c/User_Interface/Window_Stack/index.html

The multiple window manager

In Pebble OS, the window stack serves as the global manager of what window is presented, ensuring that input events are forwarded to the topmost window. The navigation model of Pebble centers on the concept of a vertical “stack” of windows, similar to mobile app interactions.

In working with the Window Stack API, the basic operations include push and pop. When an app wants to display a new window, it pushes a new window onto the stack. This appears like a window sliding in from the right. As an app is closed, the window is popped off the stack and disappears.

For more complicated operations, involving multiple windows, you can determine which windows reside on the stack, using [window\_stack\_contains\_window()](/docs/c/User_Interface/Window_Stack/#window_stack_contains_window) and remove any specific window, using [window\_stack\_remove()](/docs/c/User_Interface/Window_Stack/#window_stack_remove).

Refer to the

[User Interface Layers chapter in the Pebble Developer Guides](https://developer.getpebble.com/guides/pebble-apps/display-and-animations/layers/)
 (chapter "Window Stack") for a conceptual overview of the window stack and relevant code examples.

Also see the [WindowHandlers](/docs/c/User_Interface/Window/#WindowHandlers) of a [Window](/docs/c/User_Interface/Window/) for the callbacks that can be added to a window in order to act upon window stack transitions.

## Function Documentation

void window\_stack\_push(Window \* window, bool animated)

Pushes the given window on the window navigation stack, on top of the current topmost window of the app.

#### Parameters
 window

The window to push on top

 animated

Pass in `true` to animate the push using a sliding animation, or `false` to skip the animation.

Window \* window\_stack\_pop(bool animated)

Pops the topmost window on the navigation stack.

#### Parameters
 animated

See [window\_stack\_remove()](/docs/c/User_Interface/Window_Stack/#window_stack_remove)

#### Returns

The window that is popped, or NULL if there are no windows to pop.

void window\_stack\_pop\_all(const bool animated)

Pops all windows. See [window\_stack\_remove()](/docs/c/User_Interface/Window_Stack/#window_stack_remove) for a description of the `animated` parameter and notes.

bool window\_stack\_remove(Window \* window, bool animated)

Removes a given window from the window stack that belongs to the app task.

##### Note

If there are no windows for the app left on the stack, the app will be killed by the system, shortly. To avoid this, make sure to push another window shortly after or before removing the last window.

#### Parameters
 window

The window to remove. If the window is NULL or if it is not on the stack, this function is a no-op.

 animated

Pass in `true` to animate the removal of the window using a side-to-side sliding animation to reveal the next window. This is only used in case the window happens to be on top of the window stack (thus visible).

#### Returns

True if window was successfully removed, false otherwise.

Window \* window\_stack\_get\_top\_window(void)

Gets the topmost window on the stack that belongs to the app.

#### Returns

The topmost window on the stack that belongs to the app or NULL if no app window could be found.

bool window\_stack\_contains\_window(Window \* window)

Checks if the window is on the window stack.

#### Parameters
 window

The window to look for on the window stack

#### Returns

true if the window is currently on the window stack.
