# NumberWindow

Source: https://developer.repebble.com/docs/c/User_Interface/Window/NumberWindow/index.html

A ready-made Window prompting the user to pick a number

![](/assets/images/docs/c/aplite/number_window.png) ![](/assets/images/docs/c/aplite/number_window.png) ![](/assets/images/docs/c/aplite/number_window.png) ![](/assets/images/docs/c/aplite/number_window.png) ![](/assets/images/docs/c/aplite/number_window.png)

## Function Documentation

NumberWindow \* number\_window\_create(const char \* label, [NumberWindowCallbacks](/docs/c/User_Interface/Window/NumberWindow/#NumberWindowCallbacks) callbacks, void \* callback\_context)

Creates a new NumberWindow on the heap and initalizes it with the default values.

##### Note

The number window is not pushed to the window stack. Use [window\_stack\_push()](/docs/c/User_Interface/Window_Stack/#window_stack_push) to do this.

#### Parameters
 label

The title or prompt to display in the NumberWindow. Must be long-lived and cannot be stack-allocated.

 callbacks

The callbacks

 callback\_context

Pointer to application specific data that is passed

#### Returns

A pointer to the NumberWindow. `NULL` if the NumberWindow could not be created

void number\_window\_destroy(NumberWindow \* number\_window)

Destroys a NumberWindow previously created by number\_window\_create.

void number\_window\_set\_label(NumberWindow \* numberwindow, const char \* label)

Sets the text of the title or prompt label.

#### Parameters
 numberwindow

Pointer to the NumberWindow for which to set the label text

 label

The new label text. Must be long-lived and cannot be stack-allocated.

void number\_window\_set\_max(NumberWindow \* numberwindow, int32\_t max)

Sets the maximum value this field can hold.

#### Parameters
 numberwindow

Pointer to the NumberWindow for which to set the maximum value

 max

The maximum value

void number\_window\_set\_min(NumberWindow \* numberwindow, int32\_t min)

Sets the minimum value this field can hold.

#### Parameters
 numberwindow

Pointer to the NumberWindow for which to set the minimum value

 min

The minimum value

void number\_window\_set\_value(NumberWindow \* numberwindow, int32\_t value)

Sets the current value of the field.

#### Parameters
 numberwindow

Pointer to the NumberWindow for which to set the current value

 value

The new current value

void number\_window\_set\_step\_size(NumberWindow \* numberwindow, int32\_t step)

Sets the amount by which to increment/decrement by on a button click.

#### Parameters
 numberwindow

Pointer to the NumberWindow for which to set the step increment

 step

The new step increment

int32\_t number\_window\_get\_value(const NumberWindow \* numberwindow)

Gets the current value.

#### Parameters
 numberwindow

Pointer to the NumberWindow for which to get the current value

#### Returns

The current value

Window \* number\_window\_get\_window(NumberWindow \* numberwindow)

Gets the "root" Window of the number window.

#### Parameters
 numberwindow

Pointer to the NumberWindow for which to get the "root" Window

#### Returns

The "root" Window of the number window.

## Data Structure Documentation

struct NumberWindowCallbacks

Data structure containing all the callbacks for a NumberWindow.

#### Data Fields
[NumberWindowCallback](/docs/c/User_Interface/Window/NumberWindow/#NumberWindowCallback) incremented

Callback that gets called as the value is incremented. Optional, leave `NULL` if unused.

[NumberWindowCallback](/docs/c/User_Interface/Window/NumberWindow/#NumberWindowCallback) decremented

Callback that gets called as the value is decremented. Optional, leave `NULL` if unused.

[NumberWindowCallback](/docs/c/User_Interface/Window/NumberWindow/#NumberWindowCallback) selected

Callback that gets called as the value is confirmed, in other words the SELECT button is clicked. Optional, leave `NULL` if unused.

## Typedef Documentation

 typedef struct NumberWindow NumberWindow

 typedef void(\* NumberWindowCallback)(struct NumberWindow \*number\_window, void \*context) 

Function signature for NumberWindow callbacks.
