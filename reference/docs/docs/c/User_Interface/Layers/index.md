# Layers

Source: https://developer.repebble.com/docs/c/User_Interface/Layers/index.html

User interface layers for displaying graphic components

Layers are objects that can be displayed on a Pebble watchapp window, enabling users to see visual objects, like text or images. Each layer stores the information about its state necessary to draw or redraw the object that it represents and uses graphics routines along with this state to draw itself when asked. Layers can be used to display various graphics.

Layers are the basic building blocks for your application UI. Layers can be nested inside each other. Every window has a root layer which is always the topmost layer. You provide a function that is called to draw the content of the layer when needed; or you can use standard layers that are provided by the system, such as text layer, image layer, menu layer, action bar layer, and so on.

The Pebble layer hierarchy is the list of things that need to be drawn to the screen. Multiple layers can be arranged into a hierarchy. This enables ordering (front to back), layout and hierarchy. Through relative positioning, visual objects that are grouped together by adding them into the same layer can be moved all at once. This means that the child layers will move accordingly. If a parent layer has clipping enabled, all the children will be clipped to the frame of the parent.

Pebble OS provides convenience layers with built-in logic for displaying different graphic components, like text and bitmap layers.

Refer to the

[User Interface Layers chapter in the Pebble Developer Guides](https://developer.getpebble.com/guides/pebble-apps/display-and-animations/layers/)
 (chapter "Layers") for a conceptual overview of Layers and relevant code examples.

The Modules listed here contain what can be thought of conceptually as subclasses of Layer. The listed types can be safely type-casted to `Layer` (or `Layer *` in case of a pointer). The `layer_...` functions can then be used with the data structures of these subclasses.   
For example, the following is legal:

```
TextLayer \*text\_layer;...layer\_set\_hidden((Layer \*)text\_layer, true);
```

## Modules

#### [ActionBarLayer](/docs/c/User_Interface/Layers/ActionBarLayer/)

Vertical, bar-shaped control widget on the right edge of the window

#### [BitmapLayer](/docs/c/User_Interface/Layers/BitmapLayer/)

Layer that displays a bitmap image.

#### [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/)

Layer that displays a standard list menu. Data is provided using callbacks.

#### [RotBitmapLayer](/docs/c/User_Interface/Layers/RotBitmapLayer/)

Layer that displays a rotated bitmap image.

#### [ScrollLayer](/docs/c/User_Interface/Layers/ScrollLayer/)

Layer that scrolls its contents, animated.

#### [SimpleMenuLayer](/docs/c/User_Interface/Layers/SimpleMenuLayer/)

Wrapper around [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/), that uses static data to display a list menu.

#### [StatusBarLayer](/docs/c/User_Interface/Layers/StatusBarLayer/)

Layer that serves as a configurable status bar.

#### [TextLayer](/docs/c/User_Interface/Layers/TextLayer/)

Layer that displays and formats a text string.

## Function Documentation

Layer \* layer\_create([GRect](/docs/c/Graphics/Graphics_Types/#GRect) frame)

Creates a layer on the heap and sets its frame and bounds. Default values:

- `bounds` : origin (0, 0) and a size equal to the frame that is passed in.

- `clips` : `true`

- `hidden` : `false`

- `update_proc` : `NULL` (draws nothing) 

#### Parameters
 frame

The frame at which the layer should be initialized.

#### Returns

A pointer to the layer. `NULL` if the layer could not be created

#### See Also
[layer\_set\_frame()](/docs/c/User_Interface/Layers/#layer_set_frame)  
[layer\_set\_bounds()](/docs/c/User_Interface/Layers/#layer_set_bounds)

Layer \* layer\_create\_with\_data([GRect](/docs/c/Graphics/Graphics_Types/#GRect) frame, [size\_t](/docs/c/Standard_C/Memory/#size_t) data\_size)

Creates a layer on the heap with extra space for callback data, and set its frame andbounds. Default values:

- `bounds` : origin (0, 0) and a size equal to the frame that is passed in.

- `clips` : `true`

- `hidden` : `false`

- `update_proc` : `NULL` (draws nothing) 

#### Parameters
 frame

The frame at which the layer should be initialized.

 data\_size

The size (in bytes) of memory to allocate for callback data.

#### Returns

A pointer to the layer. `NULL` if the layer could not be created

#### See Also
[layer\_create()](/docs/c/User_Interface/Layers/#layer_create)  
[layer\_set\_frame()](/docs/c/User_Interface/Layers/#layer_set_frame)  
[layer\_set\_bounds()](/docs/c/User_Interface/Layers/#layer_set_bounds)

void layer\_destroy(Layer \* layer)

Destroys a layer previously created by layer\_create.

void layer\_mark\_dirty(Layer \* layer)

Marks the complete layer as "dirty", awaiting to be asked by the system to redraw itself. Typically, this function is called whenever state has changed that affects what the layer is displaying.

- The layer's `.update_proc` will not be called before this function returns, but will be called asynchronously, shortly.

- Internally, a call to this function will schedule a re-render of the window that the layer belongs to. In effect, all layers in that window's layer hierarchy will be asked to redraw.

- If an earlier re-render request is still pending, this function is a no-op. 

#### Parameters
 layer

The layer to mark dirty

void layer\_set\_update\_proc(Layer \* layer, [LayerUpdateProc](/docs/c/User_Interface/Layers/#LayerUpdateProc) update\_proc)

Sets the layer's render function. The system will call the `update_proc` automatically when the layer needs to redraw itself, see also [layer\_mark\_dirty()](/docs/c/User_Interface/Layers/#layer_mark_dirty).

#### Parameters
 layer

Pointer to the layer structure.

 update\_proc

Pointer to the function that will be called when the layer needs to be rendered. Typically, one performs a series of drawing commands in the implementation of the `update_proc`, see [Drawing Primitives](/docs/c/Graphics/Drawing_Primitives/), [Drawing Paths](/docs/c/Graphics/Drawing_Paths/) and [Drawing Text](/docs/c/Graphics/Drawing_Text/).

void layer\_set\_frame(Layer \* layer, [GRect](/docs/c/Graphics/Graphics_Types/#GRect) frame)

Sets the frame of the layer, which is it's bounding box relative to the coordinate system of its parent layer. The size of the layer's bounds will be extended automatically, so that the bounds cover the new frame.

#### Parameters
 layer

The layer for which to set the frame

 frame

The new frame

#### See Also
[layer\_set\_bounds()](/docs/c/User_Interface/Layers/#layer_set_bounds)

[GRect](/docs/c/Graphics/Graphics_Types/#GRect) layer\_get\_frame(const Layer \* layer)

Gets the frame of the layer, which is it's bounding box relative to the coordinate system of its parent layer. If the frame has changed, [layer\_mark\_dirty()](/docs/c/User_Interface/Layers/#layer_mark_dirty) will be called automatically.

#### Parameters
 layer

The layer for which to get the frame

#### Returns

The frame of the layer

#### See Also
[layer\_set\_frame](/docs/c/User_Interface/Layers/#layer_set_frame)

void layer\_set\_bounds(Layer \* layer, [GRect](/docs/c/Graphics/Graphics_Types/#GRect) bounds)

Sets the bounds of the layer, which is it's bounding box relative to its frame. If the bounds has changed, [layer\_mark\_dirty()](/docs/c/User_Interface/Layers/#layer_mark_dirty) will be called automatically.

#### Parameters
 layer

The layer for which to set the bounds

 bounds

The new bounds

#### See Also
[layer\_set\_frame()](/docs/c/User_Interface/Layers/#layer_set_frame)

[GRect](/docs/c/Graphics/Graphics_Types/#GRect) layer\_get\_bounds(const Layer \* layer)

Gets the bounds of the layer.

#### Parameters
 layer

The layer for which to get the bounds

#### Returns

The bounds of the layer

#### See Also
[layer\_set\_bounds](/docs/c/User_Interface/Layers/#layer_set_bounds)

[GRect](/docs/c/Graphics/Graphics_Types/#GRect) layer\_get\_unobstructed\_bounds(const Layer \* layer)

Get the largest unobstructed bounds rectangle of a layer.

#### Parameters
 layer

The layer for which to get the unobstructed bounds.

#### Returns

The unobstructed bounds of the layer.

#### See Also
[UnobstructedArea](/docs/c/User_Interface/UnobstructedArea/)

[GPoint](/docs/c/Graphics/Graphics_Types/#GPoint) layer\_convert\_point\_to\_screen(const Layer \* layer, [GPoint](/docs/c/Graphics/Graphics_Types/#GPoint) point)

Converts a point from the layer's local coordinate system to screen coordinates.

##### Note

If the layer isn't part of the view hierarchy the result is undefined.

#### Parameters
 layer

The view whose coordinate system will be used to convert the value to the screen.

 point

A point specified in the local coordinate system (bounds) of the layer.

#### Returns

The point converted to the coordinate system of the screen.

[GRect](/docs/c/Graphics/Graphics_Types/#GRect) layer\_convert\_rect\_to\_screen(const Layer \* layer, [GRect](/docs/c/Graphics/Graphics_Types/#GRect) rect)

Converts a rectangle from the layer's local coordinate system to screen coordinates.

##### Note

If the layer isn't part of the view hierarchy the result is undefined.

#### Parameters
 layer

The view whose coordinate system will be used to convert the value to the screen.

 rect

A rectangle specified in the local coordinate system (bounds) of the layer.

#### Returns

The rectangle converted to the coordinate system of the screen.

struct Window \* layer\_get\_window(const Layer \* layer)

Gets the window that the layer is currently attached to.

#### Parameters
 layer

The layer for which to get the window

#### Returns

The window that this layer is currently attached to, or `NULL` if it has not been added to a window's layer hierarchy.

#### See Also
[window\_get\_root\_layer()](/docs/c/User_Interface/Window/#window_get_root_layer)  
[layer\_add\_child()](/docs/c/User_Interface/Layers/#layer_add_child)

void layer\_remove\_from\_parent(Layer \* child)

Removes the layer from its current parent layer If removed successfully, the child's parent layer will be marked dirty automatically.

#### Parameters
 child

The layer to remove

void layer\_remove\_child\_layers(Layer \* parent)

Removes child layers from given layer If removed successfully, the child's parent layer will be marked dirty automatically.

#### Parameters
 parent

The layer from which to remove all child layers

void layer\_add\_child(Layer \* parent, Layer \* child)

Adds the child layer to a given parent layer, making it appear in front of its parent and in front of any existing child layers of the parent. If the child layer was already part of a layer hierarchy, it will be removed from its old parent first. If added successfully, the parent (and children) will be marked dirty automatically.

#### Parameters
 parent

The layer to which to add the child layer

 child

The layer to add to the parent layer

void layer\_insert\_below\_sibling(Layer \* layer\_to\_insert, Layer \* below\_sibling\_layer)

Inserts the layer as a sibling behind another layer. If the layer to insert was already part of a layer hierarchy, it will be removed from its old parent first. The below\_layer has to be a child of a parent layer, otherwise this function will be a noop. If inserted successfully, the parent (and children) will be marked dirty automatically.

#### Parameters
 layer\_to\_insert

The layer to insert into the hierarchy

 below\_sibling\_layer

The layer that will be used as the sibling layer above which the insertion will take place

void layer\_insert\_above\_sibling(Layer \* layer\_to\_insert, Layer \* above\_sibling\_layer)

Inserts the layer as a sibling in front of another layer. The above\_layer has to be a child of a parent layer, otherwise this function will be a noop. If inserted successfully, the parent (and children) will be marked dirty automatically.

#### Parameters
 layer\_to\_insert

The layer to insert into the hierarchy

 above\_sibling\_layer

The layer that will be used as the sibling layer below which the insertion will take place

void layer\_set\_hidden(Layer \* layer, bool hidden)

Sets the visibility of the layer. If the visibility has changed, [layer\_mark\_dirty()](/docs/c/User_Interface/Layers/#layer_mark_dirty) will be called automatically on the parent layer.

#### Parameters
 layer

The layer for which to set the visibility

 hidden

Supply `true` to make the layer hidden, or `false` to make it non-hidden.

bool layer\_get\_hidden(const Layer \* layer)

Gets the visibility of the layer.

#### Parameters
 layer

The layer for which to get the visibility

#### Returns

True if the layer is hidden, false if it is not hidden.

void layer\_set\_clips(Layer \* layer, bool clips)

Sets whether clipping is enabled for the layer. If enabled, whatever the layer _and its children_ will draw using their `.update_proc` callbacks, will be clipped by the this layer's frame. If the clipping has changed, [layer\_mark\_dirty()](/docs/c/User_Interface/Layers/#layer_mark_dirty) will be called automatically.

#### Parameters
 layer

The layer for which to set the clipping property

 clips

Supply `true` to make the layer clip to its frame, or `false` to make it non-clipping.

bool layer\_get\_clips(const Layer \* layer)

Gets whether clipping is enabled for the layer. If enabled, whatever the layer _and its children_ will draw using their `.update_proc` callbacks, will be clipped by the this layer's frame.

#### Parameters
 layer

The layer for which to get the clipping property

#### Returns

True if clipping is enabled for the layer, false if clipping is not enabled for the layer.

void \* layer\_get\_data(const Layer \* layer)

Gets the data from a layer that has been created with an extra data region.

#### Parameters
 layer

The layer to get the data region from.

#### Returns

A void pointer to the data region.

## Typedef Documentation

 typedef struct Layer Layer

 typedef void(\* LayerUpdateProc)(struct Layer \*layer, GContext \*ctx) 

Function signature for a Layer's render callback (the name of the type is derived from the words 'update procedure'). The system will call the `.update_proc` callback whenever the Layer needs to be rendered.

#### Parameters
 layer

The layer that needs to be rendered

 ctx

The destination graphics context to draw into

#### See Also
[Graphics](/docs/c/Graphics/)  
[layer\_set\_update\_proc()](/docs/c/User_Interface/Layers/#layer_set_update_proc)
