# ScrollLayer

Source: https://developer.repebble.com/docs/c/User_Interface/Layers/ScrollLayer/index.html

Layer that scrolls its contents, animated.

![](/assets/images/docs/c/aplite/scroll_layer.png) ![](/assets/images/docs/c/aplite/scroll_layer.png) ![](/assets/images/docs/c/aplite/scroll_layer.png) ![](/assets/images/docs/c/aplite/scroll_layer.png) ![](/assets/images/docs/c/aplite/scroll_layer.png)

### Key Points

- Facilitates vertical scrolling of a layer sub-hierarchy zero or more arbitrary layers. The example image shows a scroll layer containing one large TextLayer.

- Shadows to indicate that there is more content are automatically drawn on top of the content. When the end of the scroll layer is reached, the shadow will automatically be retracted.

- Scrolling from one offset to another is animated implicitly by default.

- The scroll layer contains a "content" sub-layer, which is the layer that is actually moved up an down. Any layer that is a child of this "content" sub-layer, will be moved as well. Effectively, an entire layout of layers can be scrolled this way. Use the convenience function [scroll\_layer\_add\_child()](/docs/c/User_Interface/Layers/ScrollLayer/#scroll_layer_add_child) to add child layers to the "content" sub-layer.

- The scroll layer needs to be informed of the total size of the contents, in order to calculate from and to what point it should be able to scroll. Use [scroll\_layer\_set\_content\_size()](/docs/c/User_Interface/Layers/ScrollLayer/#scroll_layer_set_content_size) to set the size of the contents.

- The button behavior is set up, using the convenience function [scroll\_layer\_set\_click\_config\_onto\_window()](/docs/c/User_Interface/Layers/ScrollLayer/#scroll_layer_set_click_config_onto_window). This will associate the UP and DOWN buttons with scrolling up and down.

- The SELECT button can be configured by installing a click configuration provider using [scroll\_layer\_set\_callbacks()](/docs/c/User_Interface/Layers/ScrollLayer/#scroll_layer_set_callbacks).

- To scroll programatically to a certain offset, use [scroll\_layer\_set\_content\_offset()](/docs/c/User_Interface/Layers/ScrollLayer/#scroll_layer_set_content_offset).

- It is possible to get called back for each scrolling increment, by installing the `.content_offset_changed_handler` callback using [scroll\_layer\_set\_callbacks()](/docs/c/User_Interface/Layers/ScrollLayer/#scroll_layer_set_callbacks).

- Only vertical scrolling is supported at the moment. 

## Function Documentation

ScrollLayer \* scroll\_layer\_create([GRect](/docs/c/Graphics/Graphics_Types/#GRect) frame)

Creates a new ScrollLayer on the heap and initalizes it with the default values:

- Clips: `true`

- Hidden: `false`

- Content size: `frame.size`

- Content offset: [GPointZero](/docs/c/Graphics/Graphics_Types/#GPointZero)

- Callbacks: None (`NULL` for each one)

- Callback context: `NULL`

#### Returns

A pointer to the ScrollLayer. `NULL` if the ScrollLayer could not be created

void scroll\_layer\_destroy(ScrollLayer \* scroll\_layer)

Destroys a ScrollLayer previously created by scroll\_layer\_create.

Layer \* scroll\_layer\_get\_layer(const ScrollLayer \* scroll\_layer)

Gets the "root" Layer of the scroll layer, which is the parent for the sub- layers used for its implementation.

#### Parameters
 scroll\_layer

Pointer to the ScrollLayer for which to get the "root" Layer

#### Returns

The "root" Layer of the scroll layer.

void scroll\_layer\_add\_child(ScrollLayer \* scroll\_layer, Layer \* child)

Adds the child layer to the content sub-layer of the ScrollLayer. This will make the child layer part of the scrollable contents. The content sub-layer of the ScrollLayer will become the parent of the child layer.

##### Note

You may need to update the size of the scrollable contents using [scroll\_layer\_set\_content\_size()](/docs/c/User_Interface/Layers/ScrollLayer/#scroll_layer_set_content_size).

#### Parameters
 scroll\_layer

The ScrollLayer to which to add the child layer.

 child

The Layer to add to the content sub-layer of the ScrollLayer.

void scroll\_layer\_set\_click\_config\_onto\_window(ScrollLayer \* scroll\_layer, struct Window \* window)

Convenience function to set the [ClickConfigProvider](/docs/c/User_Interface/Clicks/#ClickConfigProvider) callback on the given window to scroll layer's internal click config provider. This internal click configuration provider, will set up the default UP & DOWN scrolling behavior. This function calls [window\_set\_click\_config\_provider\_with\_context](/docs/c/User_Interface/Window/#window_set_click_config_provider_with_context) to accomplish this.

If you application has set a `.click_config_provider` callback using [scroll\_layer\_set\_callbacks()](/docs/c/User_Interface/Layers/ScrollLayer/#scroll_layer_set_callbacks), this will be called by the internal click config provider, after configuring the UP & DOWN buttons. This allows your application to configure the SELECT button behavior and optionally override the UP & DOWN button behavior. The callback context for the SELECT click recognizer is automatically set to the scroll layer's context (see [scroll\_layer\_set\_context()](/docs/c/User_Interface/Layers/ScrollLayer/#scroll_layer_set_context) ). This context is passed into [ClickHandler](/docs/c/User_Interface/Clicks/#ClickHandler) callbacks. For the UP and DOWN buttons, the scroll layer itself is passed in by default as the callback context in order to deal with those buttons presses to scroll up and down automatically.

#### Parameters
 scroll\_layer

The ScrollLayer that needs to receive click events.

 window

The window for which to set the click configuration.

#### See Also
[Clicks](/docs/c/User_Interface/Clicks/)  
[window\_set\_click\_config\_provider\_with\_context](/docs/c/User_Interface/Window/#window_set_click_config_provider_with_context)

void scroll\_layer\_set\_callbacks(ScrollLayer \* scroll\_layer, [ScrollLayerCallbacks](/docs/c/User_Interface/Layers/ScrollLayer/#ScrollLayerCallbacks) callbacks)

Sets the callbacks that the scroll layer exposes. The `context` as set by [scroll\_layer\_set\_context()](/docs/c/User_Interface/Layers/ScrollLayer/#scroll_layer_set_context) is passed into each of the callbacks. See [ScrollLayerCallbacks](/docs/c/User_Interface/Layers/ScrollLayer/#ScrollLayerCallbacks) for the different callbacks.

##### Note

If the `context` is NULL, a pointer to scroll\_layer is used as context parameter instead when calling callbacks.

#### Parameters
 scroll\_layer

The ScrollLayer for which to assign new callbacks.

 callbacks

The new callbacks.

void scroll\_layer\_set\_context(ScrollLayer \* scroll\_layer, void \* context)

Sets a new callback context. This context is passed into the scroll layer's callbacks and also the [ClickHandler](/docs/c/User_Interface/Clicks/#ClickHandler) for the SELECT button. If `NULL` or not set, the context defaults to a pointer to the ScrollLayer itself.

#### Parameters
 scroll\_layer

The ScrollLayer for which to assign the new callback context.

 context

The new callback context.

#### See Also
[scroll\_layer\_set\_click\_config\_onto\_window](/docs/c/User_Interface/Layers/ScrollLayer/#scroll_layer_set_click_config_onto_window)  
[scroll\_layer\_set\_callbacks](/docs/c/User_Interface/Layers/ScrollLayer/#scroll_layer_set_callbacks)

void scroll\_layer\_set\_content\_offset(ScrollLayer \* scroll\_layer, [GPoint](/docs/c/Graphics/Graphics_Types/#GPoint) offset, bool animated)

Scrolls to the given offset, optionally animated.

##### Notes

When scrolling down, the offset's `.y` decrements. When scrolling up, the offset's `.y` increments. If scrolled completely to the top, the offset is [GPointZero](/docs/c/Graphics/Graphics_Types/#GPointZero).

The `.x` field must be `0`. Horizontal scrolling is not supported.

#### Parameters
 scroll\_layer

The ScrollLayer for which to set the content offset

 offset

The final content offset

 animated

Pass in `true` to animate to the new content offset, or `false` to set the new content offset without animating.

#### See Also
[scroll\_layer\_get\_content\_offset](/docs/c/User_Interface/Layers/ScrollLayer/#scroll_layer_get_content_offset)

[GPoint](/docs/c/Graphics/Graphics_Types/#GPoint) scroll\_layer\_get\_content\_offset(ScrollLayer \* scroll\_layer)

Gets the point by which the contents are offset.

#### Parameters
 scroll\_layer

The ScrollLayer for which to get the content offset

#### See Also
[scroll\_layer\_set\_content\_offset](/docs/c/User_Interface/Layers/ScrollLayer/#scroll_layer_set_content_offset)

void scroll\_layer\_set\_content\_size(ScrollLayer \* scroll\_layer, [GSize](/docs/c/Graphics/Graphics_Types/#GSize) size)

Sets the size of the contents layer. This determines the area that is scrollable. At the moment, this needs to be set "manually" and is not derived from the geometry of the contents layers.

#### Parameters
 scroll\_layer

The ScrollLayer for which to set the content size.

 size

The new content size.

#### See Also
[scroll\_layer\_get\_content\_size](/docs/c/User_Interface/Layers/ScrollLayer/#scroll_layer_get_content_size)

[GSize](/docs/c/Graphics/Graphics_Types/#GSize) scroll\_layer\_get\_content\_size(const ScrollLayer \* scroll\_layer)

Gets the size of the contents layer.

#### Parameters
 scroll\_layer

The ScrollLayer for which to get the content size

#### See Also
[scroll\_layer\_set\_content\_size](/docs/c/User_Interface/Layers/ScrollLayer/#scroll_layer_set_content_size)

void scroll\_layer\_set\_frame(ScrollLayer \* scroll\_layer, [GRect](/docs/c/Graphics/Graphics_Types/#GRect) frame)

Set the frame of the scroll layer and adjusts the internal layers' geometry accordingly. The scroll layer is marked dirty automatically.

#### Parameters
 scroll\_layer

The ScrollLayer for which to set the frame

 frame

The new frame

void scroll\_layer\_scroll\_up\_click\_handler([ClickRecognizerRef](/docs/c/User_Interface/Clicks/#ClickRecognizerRef) recognizer, void \* context)

The click handlers for the UP button that the scroll layer will install as part of [scroll\_layer\_set\_click\_config\_onto\_window()](/docs/c/User_Interface/Layers/ScrollLayer/#scroll_layer_set_click_config_onto_window).

##### Note

This handler is exposed, in case one wants to implement an alternative handler for the UP button, as a way to invoke the default behavior.

#### Parameters
 recognizer

The click recognizer for which the handler is called

 context

A void pointer to the ScrollLayer that is the context of the click event

void scroll\_layer\_scroll\_down\_click\_handler([ClickRecognizerRef](/docs/c/User_Interface/Clicks/#ClickRecognizerRef) recognizer, void \* context)

The click handlers for the DOWN button that the scroll layer will install as part of [scroll\_layer\_set\_click\_config\_onto\_window()](/docs/c/User_Interface/Layers/ScrollLayer/#scroll_layer_set_click_config_onto_window).

##### Note

This handler is exposed, in case one wants to implement an alternative handler for the DOWN button, as a way to invoke the default behavior.

#### Parameters
 recognizer

The click recognizer for which the handler is called

 context

A void pointer to the ScrollLayer that is the context of the click event

void scroll\_layer\_set\_shadow\_hidden(ScrollLayer \* scroll\_layer, bool hidden)

Sets the visibility of the scroll layer shadow. If the visibility has changed, [layer\_mark\_dirty()](/docs/c/User_Interface/Layers/#layer_mark_dirty) will be called automatically on the scroll layer.

#### Parameters
 scroll\_layer

The scroll layer for which to set the shadow visibility

 hidden

Supply `true` to make the shadow hidden, or `false` to make it non-hidden.

bool scroll\_layer\_get\_shadow\_hidden(const ScrollLayer \* scroll\_layer)

Gets the visibility of the scroll layer shadow.

#### Parameters
 scroll\_layer

The scroll layer for which to get the visibility

#### Returns

True if the shadow is hidden, false if it is not hidden.

void scroll\_layer\_set\_paging(ScrollLayer \* scroll\_layer, bool paging\_enabled)

Enables or disables paging of the ScrollLayer (default: disabled). When enabled, every button press will change the scroll offset by the frame's height.

#### Parameters
 scroll\_layer

The scroll layer for which to enable or disable paging

 paging\_enabled

True, if paging should be enabled. False to enable.

bool scroll\_layer\_get\_paging(ScrollLayer \* scroll\_layer)

Check whether or not the ScrollLayer uses paging when pressing buttons.

#### Parameters
 scroll\_layer

The scroll layer for which to get the paging behavior.

#### Returns

True, if paging is enabled; false otherwise.

ContentIndicator \* scroll\_layer\_get\_content\_indicator(ScrollLayer \* scroll\_layer)

Gets the ContentIndicator for a ScrollLayer.

#### Parameters
 scroll\_layer

The ScrollLayer for which to get the ContentIndicator

#### Returns

A pointer to the ContentIndicator, or `NULL` upon failure.

ContentIndicator \* content\_indicator\_create(void)

Creates a ContentIndicator on the heap.

#### Returns

A pointer to the ContentIndicator. `NULL` if the ContentIndicator could not be created.

void content\_indicator\_destroy(ContentIndicator \* content\_indicator)

Destroys a ContentIndicator previously created using [content\_indicator\_create()](/docs/c/User_Interface/Layers/ScrollLayer/#content_indicator_create).

#### Parameters
 content\_indicator

The ContentIndicator to destroy.

bool content\_indicator\_configure\_direction(ContentIndicator \* content\_indicator, [ContentIndicatorDirection](/docs/c/User_Interface/Layers/ScrollLayer/#ContentIndicatorDirection) direction, const [ContentIndicatorConfig](/docs/c/User_Interface/Layers/ScrollLayer/#ContentIndicatorConfig) \* config)

Configures a ContentIndicator for the given direction.

#### Parameters
 content\_indicator

The ContentIndicator to configure.

 direction

The direction for which to configure the ContentIndicator.

 config

The configuration to use to configure the ContentIndicator. If NULL, the data for the specified direction will be reset.

#### Returns

True if the ContentIndicator was successfully configured for the given direction, false otherwise.

bool content\_indicator\_get\_content\_available(ContentIndicator \* content\_indicator, [ContentIndicatorDirection](/docs/c/User_Interface/Layers/ScrollLayer/#ContentIndicatorDirection) direction)

Retrieves the availability status of content in the given direction.

#### Parameters
 content\_indicator

The ContentIndicator for which to get the content availability.

 direction

The direction for which to get the content availability.

#### Returns

True if content is available in the given direction, false otherwise.

void content\_indicator\_set\_content\_available(ContentIndicator \* content\_indicator, [ContentIndicatorDirection](/docs/c/User_Interface/Layers/ScrollLayer/#ContentIndicatorDirection) direction, bool available)

Sets the availability status of content in the given direction.

##### Note

If times\_out is enabled, calling this function resets any previously scheduled timeout timer for the ContentIndicator.

#### Parameters
 content\_indicator

The ContentIndicator for which to set the content availability.

 direction

The direction for which to set the content availability.

 available

Whether or not content is available.

## Data Structure Documentation

struct ContentIndicatorConfig

Struct used to configure directions for ContentIndicator.

#### Data Fields
Layer \* layer

The layer where the arrow indicator will be rendered when content is available.

bool times\_out

Whether the display of the arrow indicator should timeout.

[GAlign](/docs/c/Graphics/Graphics_Types/#GAlign) alignment

The alignment of the arrow within the provided layer.

struct [ContentIndicatorConfig](/docs/c/User_Interface/Layers/ScrollLayer/#ContentIndicatorConfig) colors
#### See Also
[content\_indicator\_configure\_direction](/docs/c/User_Interface/Layers/ScrollLayer/#content_indicator_configure_direction)

struct ScrollLayerCallbacks

All the callbacks that the ScrollLayer exposes for use by applications.

##### Note

The context parameter can be set using [scroll\_layer\_set\_context()](/docs/c/User_Interface/Layers/ScrollLayer/#scroll_layer_set_context) and gets passed in as context with all of these callbacks.

#### Data Fields
[ClickConfigProvider](/docs/c/User_Interface/Clicks/#ClickConfigProvider) click\_config\_provider

Provider function to set up the SELECT button handlers. This will be called after the scroll layer has configured the click configurations for the up/down buttons, so it can also be used to modify the default up/down scrolling behavior.

[ScrollLayerCallback](/docs/c/User_Interface/Layers/ScrollLayer/#ScrollLayerCallback) content\_offset\_changed\_handler

Called every time the the content offset changes. During a scrolling animation, it will be called for each intermediary offset as well.

## Enum Documentation

enum ContentIndicatorDirection

Value to describe directions for ContentIndicator.

content\_indicator\_configure\_direction content\_indicator\_set\_content\_available

#### Enumerators
ContentIndicatorDirectionUp

The up direction.

ContentIndicatorDirectionDown

The down direction.

NumContentIndicatorDirections

The number of supported directions.

## Typedef Documentation

 typedef struct ScrollLayer ScrollLayer

 typedef void(\* ScrollLayerCallback)(struct ScrollLayer \*scroll\_layer, void \*context) 

Function signature for the `.content_offset_changed_handler` callback.

 typedef struct ContentIndicator ContentIndicator
