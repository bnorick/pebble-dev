# MenuLayer

Source: https://developer.repebble.com/docs/c/User_Interface/Layers/MenuLayer/index.html

Layer that displays a standard list menu. Data is provided using callbacks.

![](/assets/images/docs/c/aplite/menu_layer.png) ![](/assets/images/docs/c/aplite/menu_layer.png) ![](/assets/images/docs/c/aplite/menu_layer.png) ![](/assets/images/docs/c/aplite/menu_layer.png) ![](/assets/images/docs/c/aplite/menu_layer.png)

### Key Points

- The familiar list-style menu widget, as used throughout the Pebble user interface.

- Built on top of [ScrollLayer](/docs/c/User_Interface/Layers/ScrollLayer/), inheriting all its goodness like animated scrolling, automatic "more content" shadow indicators, etc.

- All data needed to render the menu is requested on-demand via callbacks, to avoid the need to keep a lot of data in memory.

- Support for "sections". A section is a group of items, visually separated by a header with the name at the top of the section.

- Variable heights: each menu item cell and each section header can have its own height. The heights are provided by callbacks.

- Deviation from the Layer system for cell drawing: Each menu item does _not_ have its own Layer (to minimize memory usage). Instead, a drawing callback is set onto the [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/) that is responsible for drawing each menu item. The [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/) will call this callback for each menu item that is visible and needs to be rendered.

- Cell and header drawing can be customized by implementing a custom drawing callback.

- A few "canned" menu cell drawing functions are provided for convenience, which support the default menu cell layout with a title, optional subtitle and icon.

For short, static list menus, consider using [SimpleMenuLayer](/docs/c/User_Interface/Layers/SimpleMenuLayer/).

## Function Documentation

void menu\_cell\_basic\_draw(GContext \* ctx, const Layer \* cell\_layer, const char \* title, const char \* subtitle, GBitmap \* icon)

Section drawing function to draw a basic section cell with the title, subtitle, and icon of the section. Call this function inside the `.draw_row` callback implementation, see [MenuLayerCallbacks](/docs/c/User_Interface/Layers/MenuLayer/#MenuLayerCallbacks). Note that if the size of `cell_layer` is too small to fit all of the cell items specified, not all of them may be drawn.

#### Parameters
 ctx

The destination graphics context

 cell\_layer

The layer of the cell to draw

 title

If non-null, draws a title in larger text (24 points, bold Raster Gothic system font).

 subtitle

If non-null, draws a subtitle in smaller text (18 points, Raster Gothic system font). If `NULL`, the title will be centered vertically inside the menu cell.

 icon

If non-null, draws an icon to the left of the text. If `NULL`, the icon will be omitted and the leftover space is used for the title and subtitle.

void menu\_cell\_title\_draw(GContext \* ctx, const Layer \* cell\_layer, const char \* title)

Cell drawing function to draw a basic menu cell layout with title, subtitle Cell drawing function to draw a menu cell layout with only one big title. Call this function inside the `.draw_row` callback implementation, see [MenuLayerCallbacks](/docs/c/User_Interface/Layers/MenuLayer/#MenuLayerCallbacks).

#### Parameters
 ctx

The destination graphics context

 cell\_layer

The layer of the cell to draw

 title

If non-null, draws a title in larger text (28 points, bold Raster Gothic system font).

void menu\_cell\_basic\_header\_draw(GContext \* ctx, const Layer \* cell\_layer, const char \* title)

Section header drawing function to draw a basic section header cell layout with the title of the section. Call this function inside the `.draw_header` callback implementation, see [MenuLayerCallbacks](/docs/c/User_Interface/Layers/MenuLayer/#MenuLayerCallbacks).

#### Parameters
 ctx

The destination graphics context

 cell\_layer

The layer of the cell to draw

 title

If non-null, draws the title in small text (14 points, bold Raster Gothic system font).

int16\_t menu\_index\_compare(const [MenuIndex](/docs/c/User_Interface/Layers/MenuLayer/#MenuIndex) \* a, const [MenuIndex](/docs/c/User_Interface/Layers/MenuLayer/#MenuIndex) \* b)

Comparator function to determine the order of two [MenuIndex](/docs/c/User_Interface/Layers/MenuLayer/#MenuIndex) values.

#### Parameters
 a

Pointer to the menu index of the first item

 b

Pointer to the menu index of the second item

#### Returns

0 if A and B are equal, 1 if A has a higher section & row combination than B or else -1

MenuLayer \* menu\_layer\_create([GRect](/docs/c/Graphics/Graphics_Types/#GRect) frame)

Creates a new [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/) on the heap and initalizes it with the default values.

- Clips: `true`

- Hidden: `false`

- Content size: `frame.size`

- Content offset: [GPointZero](/docs/c/Graphics/Graphics_Types/#GPointZero)

- Callbacks: None (`NULL` for each one)

- Callback context: `NULL`

- After the relevant callbacks are called to populate the menu, the item at [MenuIndex(0, 0)](/docs/c/User_Interface/Layers/MenuLayer/#MenuIndex) will be selected initially. 

#### Returns

A pointer to the [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/). `NULL` if the [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/) could not be created

void menu\_layer\_destroy(MenuLayer \* menu\_layer)

Destroys a [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/) previously created by menu\_layer\_create.

Layer \* menu\_layer\_get\_layer(const MenuLayer \* menu\_layer)

Gets the "root" Layer of the [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/), which is the parent for the sub- layers used for its implementation.

#### Parameters
 menu\_layer

Pointer to the MenuLayer for which to get the "root" Layer

#### Returns

The "root" Layer of the [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/).

ScrollLayer \* menu\_layer\_get\_scroll\_layer(const MenuLayer \* menu\_layer)

Gets the ScrollLayer of the [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/), which is the layer responsible for the scrolling of the [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/).

#### Parameters
 menu\_layer

Pointer to the [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/) for which to get the ScrollLayer

#### Returns

The ScrollLayer of the [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/).

void menu\_layer\_set\_callbacks(MenuLayer \* menu\_layer, void \* callback\_context, [MenuLayerCallbacks](/docs/c/User_Interface/Layers/MenuLayer/#MenuLayerCallbacks) callbacks)

Sets the callbacks for the MenuLayer.

#### Parameters
 menu\_layer

Pointer to the [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/) for which to set the callbacks and callback context.

 callback\_context

The new callback context. This is passed into each of the callbacks and can be set to point to application provided data.

 callbacks

The new callbacks for the [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/). The storage for this data structure must be long lived. Therefore, it cannot be stack-allocated.

#### See Also
[MenuLayerCallbacks](/docs/c/User_Interface/Layers/MenuLayer/#MenuLayerCallbacks)

void menu\_layer\_set\_click\_config\_onto\_window(MenuLayer \* menu\_layer, struct Window \* window)

Convenience function to set the [ClickConfigProvider](/docs/c/User_Interface/Clicks/#ClickConfigProvider) callback on the given window to the [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/) internal click config provider. This internal click configuration provider, will set up the default UP & DOWN scrolling / menu item selection behavior. This function calls [scroll\_layer\_set\_click\_config\_onto\_window](/docs/c/User_Interface/Layers/ScrollLayer/#scroll_layer_set_click_config_onto_window) to accomplish this.

Click and long click events for the SELECT button can be handled by installing the appropriate callbacks using [menu\_layer\_set\_callbacks()](/docs/c/User_Interface/Layers/MenuLayer/#menu_layer_set_callbacks). This is a deviation from the usual click configuration provider pattern.

#### Parameters
 menu\_layer

The [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/) that needs to receive click events.

 window

The window for which to set the click configuration.

#### See Also
[Clicks](/docs/c/User_Interface/Clicks/)  
[window\_set\_click\_config\_provider\_with\_context()](/docs/c/User_Interface/Window/#window_set_click_config_provider_with_context)  
[scroll\_layer\_set\_click\_config\_onto\_window()](/docs/c/User_Interface/Layers/ScrollLayer/#scroll_layer_set_click_config_onto_window)

void menu\_layer\_set\_selected\_next(MenuLayer \* menu\_layer, bool up, [MenuRowAlign](/docs/c/User_Interface/Layers/MenuLayer/#MenuRowAlign) scroll\_align, bool animated)

Selects the next or previous item, relative to the current selection.

##### Note

If there is no next/previous item, this function is a no-op.

#### Parameters
 menu\_layer

The [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/) for which to select the next item

 up

Supply `false` to select the next item in the list (downwards), or `true` to select the previous item in the list (upwards).

 scroll\_align

The alignment of the new selection

 animated

Supply `true` to animate changing the selection, or `false` to change the selection instantly.

void menu\_layer\_set\_selected\_index(MenuLayer \* menu\_layer, [MenuIndex](/docs/c/User_Interface/Layers/MenuLayer/#MenuIndex) index, [MenuRowAlign](/docs/c/User_Interface/Layers/MenuLayer/#MenuRowAlign) scroll\_align, bool animated)

Selects the item with given [MenuIndex](/docs/c/User_Interface/Layers/MenuLayer/#MenuIndex).

##### Note

If the section and/or row index exceeds the avaible number of sections or resp. rows, the exceeding index/indices will be capped, effectively selecting the last section and/or row, resp.

#### Parameters
 menu\_layer

The [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/) for which to change the selection

 index

The index of the item to select

 scroll\_align

The alignment of the new selection

 animated

Supply `true` to animate changing the selection, or `false` to change the selection instantly.

[MenuIndex](/docs/c/User_Interface/Layers/MenuLayer/#MenuIndex) menu\_layer\_get\_selected\_index(const MenuLayer \* menu\_layer)

Gets the [MenuIndex](/docs/c/User_Interface/Layers/MenuLayer/#MenuIndex) of the currently selected menu item.

##### Note

This function should not be used to determine whether a cell should be highlighted or not. See [menu\_cell\_layer\_is\_highlighted](/docs/c/User_Interface/Layers/MenuLayer/#menu_cell_layer_is_highlighted) for more information.

#### Parameters
 menu\_layer

The [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/) for which to get the current selected index.

#### See Also
[menu\_cell\_layer\_is\_highlighted](/docs/c/User_Interface/Layers/MenuLayer/#menu_cell_layer_is_highlighted)

void menu\_layer\_reload\_data(MenuLayer \* menu\_layer)

Reloads the data of the menu. This causes the menu to re-request the menu item data, by calling the relevant callbacks. The current selection and scroll position will not be changed. See the note with [menu\_layer\_set\_selected\_index()](/docs/c/User_Interface/Layers/MenuLayer/#menu_layer_set_selected_index) for the behavior if the old selection is no longer valid.

#### Parameters
 menu\_layer

The [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/) for which to reload the data.

bool menu\_cell\_layer\_is\_highlighted(const Layer \* cell\_layer)

Returns whether or not the given cell layer is highlighted. Using this for determining highlight behaviour is preferable to using [menu\_layer\_get\_selected\_index](/docs/c/User_Interface/Layers/MenuLayer/#menu_layer_get_selected_index). Row drawing callbacks may be invoked multiple times with a different highlight status on the same cell in order to handle partially highlighted cells during animation.

#### Parameters
 cell\_layer

The [Layers](/docs/c/User_Interface/Layers/) for the cell to check highlight status.

#### Returns

true if the given cell layer is highlighted in the menu.

void menu\_layer\_set\_normal\_colors(MenuLayer \* menu\_layer, GColor background, GColor foreground)

Set the default colors to be used for cells when it is in a normal state (not highlighted). The GContext's text and fill colors will be set appropriately prior to calling the `.draw_row` callback. If this function is not explicitly called on a [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/), it will default to white background with black foreground.

#### Parameters
 menu\_layer

The [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/) for which to set the colors.

 background

The color to be used for the background of the cell.

 foreground

The color to be used for the foreground and text of the cell.

#### See Also
[menu\_layer\_set\_highlight\_colors](/docs/c/User_Interface/Layers/MenuLayer/#menu_layer_set_highlight_colors)

void menu\_layer\_set\_highlight\_colors(MenuLayer \* menu\_layer, GColor background, GColor foreground)

Set the default colors to be used for cells when it is in a highlighted state. The GContext's text and fill colors will be set appropriately prior to calling the `.draw_row` callback. If this function is not explicitly called on a [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/), it will default to black background with white foreground.

#### Parameters
 menu\_layer

The [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/) for which to set the colors.

 background

The color to be used for the background of the cell.

 foreground

The color to be used for the foreground and text of the cell.

#### See Also
[menu\_layer\_set\_normal\_colors](/docs/c/User_Interface/Layers/MenuLayer/#menu_layer_set_normal_colors)

void menu\_layer\_pad\_bottom\_enable(MenuLayer \* menu\_layer, bool enable)

This enables or disables padding at the bottom of the [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/). Padding at the bottom of the layer keeps the bottom item from being at the very bottom of the screen. Padding is turned on by default for all MenuLayers. The color of the padded area will be the background color set using [menu\_layer\_set\_normal\_colors()](/docs/c/User_Interface/Layers/MenuLayer/#menu_layer_set_normal_colors). To color the padding a different color, use [MenuLayerDrawBackgroundCallback](/docs/c/User_Interface/Layers/MenuLayer/#MenuLayerDrawBackgroundCallback).

#### Parameters
 menu\_layer

The menu layer for which to enable or disable the padding.

 enable

True = enable padding, False = disable padding.

bool menu\_layer\_get\_center\_focused(MenuLayer \* menu\_layer)

True, if the [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/) generally scrolls such that the selected row is in the center.

#### See Also
[menu\_layer\_set\_center\_focused](/docs/c/User_Interface/Layers/MenuLayer/#menu_layer_set_center_focused)

void menu\_layer\_set\_center\_focused(MenuLayer \* menu\_layer, bool center\_focused)

Controls if the [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/) generally scrolls such that the selected row is in the center. For platforms with a round display (PBL\_ROUND) the default is true, otherwise false is the default.

#### Parameters
 menu\_layer

The menu layer for which to enable or disable the behavior.

 center\_focused

true = enable the mode, false = disable it.

#### See Also
[menu\_layer\_get\_center\_focused](/docs/c/User_Interface/Layers/MenuLayer/#menu_layer_get_center_focused)

bool menu\_layer\_is\_index\_selected(const MenuLayer \* menu\_layer, [MenuIndex](/docs/c/User_Interface/Layers/MenuLayer/#MenuIndex) \* index)

Returns whether or not the specified cell index is currently selected.

##### Note

This function should not be used to determine whether a cell is highlighted or not. See [menu\_cell\_layer\_is\_highlighted](/docs/c/User_Interface/Layers/MenuLayer/#menu_cell_layer_is_highlighted) for more information.

#### Parameters
 menu\_layer

The [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/) to use when determining if the index is selected.

 index

The [MenuIndex](/docs/c/User_Interface/Layers/MenuLayer/#MenuIndex) of the cell to check for selection.

## Data Structure Documentation

struct MenuCellSpan

#### Data Fields
int16\_t yint16\_t hint16\_t sep[MenuIndex](/docs/c/User_Interface/Layers/MenuLayer/#MenuIndex) index

struct MenuIndex

Data structure to represent an menu item's position in a menu, by specifying the section index and the row index within that section.

#### Data Fields
[uint16\_t](/docs/c/Standard_C/#uint16_t) section

The index of the section.

[uint16\_t](/docs/c/Standard_C/#uint16_t) row

The index of the row within the section with index `.section`

struct MenuLayerCallbacks

Data structure containing all the callbacks of a [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/).

#### Data Fields
[MenuLayerGetNumberOfSectionsCallback](/docs/c/User_Interface/Layers/MenuLayer/#MenuLayerGetNumberOfSectionsCallback) get\_num\_sections

Callback that gets called to get the number of sections in the menu. This can get called at various moments throughout the life of a menu.

##### Note

When `NULL`, the number of sections defaults to 1.

[MenuLayerGetNumberOfRowsInSectionsCallback](/docs/c/User_Interface/Layers/MenuLayer/#MenuLayerGetNumberOfRowsInSectionsCallback) get\_num\_rows

Callback that gets called to get the number of rows in a section. This can get called at various moments throughout the life of a menu.

##### Note

Must be set to a valid callback; `NULL` causes undefined behavior.

[MenuLayerGetCellHeightCallback](/docs/c/User_Interface/Layers/MenuLayer/#MenuLayerGetCellHeightCallback) get\_cell\_height

Callback that gets called to get the height of a cell. This can get called at various moments throughout the life of a menu.

##### Note

When `NULL`, the default height of MENU\_CELL\_BASIC\_CELL\_HEIGHT pixels is used. Developers may wish to use [MENU\_CELL\_ROUND\_FOCUSED\_SHORT\_CELL\_HEIGHT](/docs/c/User_Interface/Layers/MenuLayer/#MENU_CELL_ROUND_FOCUSED_SHORT_CELL_HEIGHT) and [MENU\_CELL\_ROUND\_UNFOCUSED\_SHORT\_CELL\_HEIGHT](/docs/c/User_Interface/Layers/MenuLayer/#MENU_CELL_ROUND_UNFOCUSED_SHORT_CELL_HEIGHT) on a round display to respect the system aesthetic.

[MenuLayerGetHeaderHeightCallback](/docs/c/User_Interface/Layers/MenuLayer/#MenuLayerGetHeaderHeightCallback) get\_header\_height

Callback that gets called to get the height of a section header. This can get called at various moments throughout the life of a menu.

##### Note

When `NULL`, the default height of 0 pixels is used. This disables section headers.

[MenuLayerDrawRowCallback](/docs/c/User_Interface/Layers/MenuLayer/#MenuLayerDrawRowCallback) draw\_row

Callback that gets called to render a menu item. This gets called for each menu item, every time it needs to be re-rendered.

##### Note

Must be set to a valid callback; `NULL` causes undefined behavior.

[MenuLayerDrawHeaderCallback](/docs/c/User_Interface/Layers/MenuLayer/#MenuLayerDrawHeaderCallback) draw\_header

Callback that gets called to render a section header. This gets called for each section header, every time it needs to be re-rendered.

##### Note

Must be set to a valid callback, unless `.get_header_height` is `NULL`. Causes undefined behavior otherwise.

[MenuLayerSelectCallback](/docs/c/User_Interface/Layers/MenuLayer/#MenuLayerSelectCallback) select\_click

Callback that gets called when the user triggers a click with the SELECT button.

##### Note

When `NULL`, click events for the SELECT button are ignored.

[MenuLayerSelectCallback](/docs/c/User_Interface/Layers/MenuLayer/#MenuLayerSelectCallback) select\_long\_click

Callback that gets called when the user triggers a long click with the SELECT button.

##### Note

When `NULL`, long click events for the SELECT button are ignored.

[MenuLayerSelectionChangedCallback](/docs/c/User_Interface/Layers/MenuLayer/#MenuLayerSelectionChangedCallback) selection\_changed

Callback that gets called whenever the selection changes.

##### Note

When `NULL`, selection change events are ignored.

[MenuLayerGetSeparatorHeightCallback](/docs/c/User_Interface/Layers/MenuLayer/#MenuLayerGetSeparatorHeightCallback) get\_separator\_height

Callback that gets called to get the height of a separator This can get called at various moments throughout the life of a menu.

##### Note

When `NULL`, the default height of 0 is used.

[MenuLayerDrawSeparatorCallback](/docs/c/User_Interface/Layers/MenuLayer/#MenuLayerDrawSeparatorCallback) draw\_separator

Callback that gets called to render a separator. This gets called for each separator, every time it needs to be re-rendered.

##### Note

Must be set to a valid callback, unless `.get_separator_height` is `NULL`. Causes undefined behavior otherwise.

[MenuLayerSelectionWillChangeCallback](/docs/c/User_Interface/Layers/MenuLayer/#MenuLayerSelectionWillChangeCallback) selection\_will\_change

Callback that gets called before the selected cell changes. This gets called before the selected item in the MenuLayer is changed, and will allow for the selected cell to be overridden. This allows for skipping cells in the menu, locking selection onto a given item,.

[MenuLayerDrawBackgroundCallback](/docs/c/User_Interface/Layers/MenuLayer/#MenuLayerDrawBackgroundCallback) draw\_background

Callback that gets called before any cells are drawn. This supports two states, either highlighted or not highlighted. If highlighted is specified, it is expected to be colored in the same style as the menu's cells are. If this callback is not specified, it will default to the colors set with [menu\_layer\_set\_normal\_colors](/docs/c/User_Interface/Layers/MenuLayer/#menu_layer_set_normal_colors) and [menu\_layer\_set\_highlight\_colors](/docs/c/User_Interface/Layers/MenuLayer/#menu_layer_set_highlight_colors).

## Enum Documentation

enum MenuRowAlign

Values to specify how a (selected) row should be aligned relative to the visible area of the [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/).

#### Enumerators
MenuRowAlignNone

Don't align or update the scroll offset of the [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/).

MenuRowAlignCenter

Scroll the contents of the [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/) in such way that the selected row is centered relative to the visible area.

MenuRowAlignTop

Scroll the contents of the [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/) in such way that the selected row is at the top of the visible area.

MenuRowAlignBottom

Scroll the contents of the [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/) in such way that the selected row is at the bottom of the visible area.

## Typedef Documentation

 typedef struct MenuLayer MenuLayer

 typedef [uint16\_t](/docs/c/Standard_C/#uint16_t)(\* MenuLayerGetNumberOfSectionsCallback)(struct MenuLayer \*menu\_layer, void \*callback\_context) 

Function signature for the callback to get the number of sections in a menu.

#### Parameters
 menu\_layer

The [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/) for which the data is requested

 callback\_context

The callback context

#### Returns

The number of sections in the menu

#### See Also
[menu\_layer\_set\_callbacks()](/docs/c/User_Interface/Layers/MenuLayer/#menu_layer_set_callbacks)  
[MenuLayerCallbacks](/docs/c/User_Interface/Layers/MenuLayer/#MenuLayerCallbacks)

 typedef [uint16\_t](/docs/c/Standard_C/#uint16_t)(\* MenuLayerGetNumberOfRowsInSectionsCallback)(struct MenuLayer \*menu\_layer, uint16\_t section\_index, void \*callback\_context) 

Function signature for the callback to get the number of rows in a given section in a menu.

#### Parameters
 menu\_layer

The [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/) for which the data is requested

 section\_index

The index of the section of the menu for which the number of items it contains is requested

 callback\_context

The callback context

#### Returns

The number of rows in the given section in the menu

#### See Also
[menu\_layer\_set\_callbacks()](/docs/c/User_Interface/Layers/MenuLayer/#menu_layer_set_callbacks)  
[MenuLayerCallbacks](/docs/c/User_Interface/Layers/MenuLayer/#MenuLayerCallbacks)

 typedef int16\_t(\* MenuLayerGetCellHeightCallback)(struct MenuLayer \*menu\_layer, MenuIndex \*cell\_index, void \*callback\_context) 

Function signature for the callback to get the height of the menu cell at a given index.

#### Parameters
 menu\_layer

The [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/) for which the data is requested

 cell\_index

The [MenuIndex](/docs/c/User_Interface/Layers/MenuLayer/#MenuIndex) for which the cell height is requested

 callback\_context

The callback context

#### Returns

The height of the cell at the given [MenuIndex](/docs/c/User_Interface/Layers/MenuLayer/#MenuIndex)

#### See Also
[menu\_layer\_set\_callbacks()](/docs/c/User_Interface/Layers/MenuLayer/#menu_layer_set_callbacks)  
[MenuLayerCallbacks](/docs/c/User_Interface/Layers/MenuLayer/#MenuLayerCallbacks)

 typedef int16\_t(\* MenuLayerGetHeaderHeightCallback)(struct MenuLayer \*menu\_layer, uint16\_t section\_index, void \*callback\_context) 

Function signature for the callback to get the height of the section header at a given section index.

#### Parameters
 menu\_layer

The [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/) for which the data is requested

 section\_index

The index of the section for which the header height is requested

 callback\_context

The callback context

#### Returns

The height of the section header at the given section index

#### See Also
[menu\_layer\_set\_callbacks()](/docs/c/User_Interface/Layers/MenuLayer/#menu_layer_set_callbacks)  
[MenuLayerCallbacks](/docs/c/User_Interface/Layers/MenuLayer/#MenuLayerCallbacks)

 typedef int16\_t(\* MenuLayerGetSeparatorHeightCallback)(struct MenuLayer \*menu\_layer, MenuIndex \*cell\_index, void \*callback\_context) 

Function signature for the callback to get the height of the separator at a given index.

#### Parameters
 menu\_layer

The [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/) for which the data is requested

 cell\_index

The [MenuIndex](/docs/c/User_Interface/Layers/MenuLayer/#MenuIndex) for which the cell height is requested

 callback\_context

The callback context

#### Returns

The height of the separator at the given [MenuIndex](/docs/c/User_Interface/Layers/MenuLayer/#MenuIndex)

#### See Also
[menu\_layer\_set\_callbacks()](/docs/c/User_Interface/Layers/MenuLayer/#menu_layer_set_callbacks)  
[MenuLayerCallbacks](/docs/c/User_Interface/Layers/MenuLayer/#MenuLayerCallbacks)

 typedef void(\* MenuLayerDrawRowCallback)(GContext \*ctx, const Layer \*cell\_layer, MenuIndex \*cell\_index, void \*callback\_context) 

Function signature for the callback to render the menu cell at a given [MenuIndex](/docs/c/User_Interface/Layers/MenuLayer/#MenuIndex).

##### Note

The `cell_layer` argument is provided to make it easy to re-use an `.update_proc` implementation in this callback. Only the bounds and frame of the `cell_layer` are actually valid and other properties should be ignored.

#### Parameters
 ctx

The destination graphics context to draw into

 cell\_layer

The cell's layer, containing the geometry of the cell

 cell\_index

The [MenuIndex](/docs/c/User_Interface/Layers/MenuLayer/#MenuIndex) of the cell that needs to be drawn

 callback\_context

The callback context

#### See Also
[menu\_layer\_set\_callbacks()](/docs/c/User_Interface/Layers/MenuLayer/#menu_layer_set_callbacks)  
[MenuLayerCallbacks](/docs/c/User_Interface/Layers/MenuLayer/#MenuLayerCallbacks)

 typedef void(\* MenuLayerDrawHeaderCallback)(GContext \*ctx, const Layer \*cell\_layer, uint16\_t section\_index, void \*callback\_context) 

Function signature for the callback to render the section header at a given section index.

##### Note

The `cell_layer` argument is provided to make it easy to re-use an `.update_proc` implementation in this callback. Only the bounds and frame of the `cell_layer` are actually valid and other properties should be ignored.

#### Parameters
 ctx

The destination graphics context to draw into

 cell\_layer

The header cell's layer, containing the geometry of the header cell

 section\_index

The section index of the section header that needs to be drawn

 callback\_context

The callback context

#### See Also
[menu\_layer\_set\_callbacks()](/docs/c/User_Interface/Layers/MenuLayer/#menu_layer_set_callbacks)  
[MenuLayerCallbacks](/docs/c/User_Interface/Layers/MenuLayer/#MenuLayerCallbacks)

 typedef void(\* MenuLayerDrawSeparatorCallback)(GContext \*ctx, const Layer \*cell\_layer, MenuIndex \*cell\_index, void \*callback\_context) 

Function signature for the callback to render the separator at a given [MenuIndex](/docs/c/User_Interface/Layers/MenuLayer/#MenuIndex).

##### Note

The `cell_layer` argument is provided to make it easy to re-use an `.update_proc` implementation in this callback. Only the bounds and frame of the `cell_layer` are actually valid and other properties should be ignored.

#### Parameters
 ctx

The destination graphics context to draw into

 cell\_layer

The cell's layer, containing the geometry of the cell

 cell\_index

The [MenuIndex](/docs/c/User_Interface/Layers/MenuLayer/#MenuIndex) of the separator that needs to be drawn

 callback\_context

The callback context

#### See Also
[menu\_layer\_set\_callbacks()](/docs/c/User_Interface/Layers/MenuLayer/#menu_layer_set_callbacks)  
[MenuLayerCallbacks](/docs/c/User_Interface/Layers/MenuLayer/#MenuLayerCallbacks)

 typedef void(\* MenuLayerSelectCallback)(struct MenuLayer \*menu\_layer, MenuIndex \*cell\_index, void \*callback\_context) 

Function signature for the callback to handle the event that a user hits the SELECT button.

#### Parameters
 menu\_layer

The [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/) for which the selection event occured

 cell\_index

The [MenuIndex](/docs/c/User_Interface/Layers/MenuLayer/#MenuIndex) of the cell that is selected

 callback\_context

The callback context

#### See Also
[menu\_layer\_set\_callbacks()](/docs/c/User_Interface/Layers/MenuLayer/#menu_layer_set_callbacks)  
[MenuLayerCallbacks](/docs/c/User_Interface/Layers/MenuLayer/#MenuLayerCallbacks)

 typedef void(\* MenuLayerSelectionChangedCallback)(struct MenuLayer \*menu\_layer, MenuIndex new\_index, MenuIndex old\_index, void \*callback\_context) 

Function signature for the callback to handle a change in the current selected item in the menu.

#### Parameters
 menu\_layer

The [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/) for which the selection event occured

 new\_index

The [MenuIndex](/docs/c/User_Interface/Layers/MenuLayer/#MenuIndex) of the new item that is selected now

 old\_index

The [MenuIndex](/docs/c/User_Interface/Layers/MenuLayer/#MenuIndex) of the old item that was selected before

 callback\_context

The callback context

#### See Also
[menu\_layer\_set\_callbacks()](/docs/c/User_Interface/Layers/MenuLayer/#menu_layer_set_callbacks)  
[MenuLayerCallbacks](/docs/c/User_Interface/Layers/MenuLayer/#MenuLayerCallbacks)

 typedef void(\* MenuLayerSelectionWillChangeCallback)(struct MenuLayer \*menu\_layer, MenuIndex \*new\_index, MenuIndex old\_index, void \*callback\_context) 

Function signature for the callback which allows or changes selection behavior of the menu. In order to change the cell that should be selected, modify the passed in new\_index. Preventing the selection from changing, new\_index can be assigned the value of old\_index.

##### Note

[menu\_layer\_set\_selected\_index](/docs/c/User_Interface/Layers/MenuLayer/#menu_layer_set_selected_index) will not trigger this callback when the selection changes, but [menu\_layer\_set\_selected\_next](/docs/c/User_Interface/Layers/MenuLayer/#menu_layer_set_selected_next) will.

#### Parameters
 menu\_layer

The [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/) for which the selection event that occured

 new\_index

Pointer to the index that the MenuLayer is going to change selection to.

 old\_index

The index that is being unselected.

 callback\_context

The callback context

 typedef void(\* MenuLayerDrawBackgroundCallback)(GContext \*ctx, const Layer \*bg\_layer, bool highlight, void \*callback\_context) 

Function signature for the callback which draws the menu's background. The background is underneath the cells of the menu, and is visible in the padding below the bottom cell, or if a cell's background color is set to GColorClear.

#### Parameters
 ctx

The destination graphics context to draw into.

 bg\_layer

The background's layer, containing the geometry of the background.

 highlight

Whether this should be rendered as highlighted or not. Highlight style should match the highlight style of cells, since this color can be used for animating selection.

## Macro Definition Documentation

#define MENU\_CELL\_BASIC\_HEADER\_HEIGHT ((const int16\_t) 16)

Default section header height in pixels.

#define MENU\_INDEX\_NOT\_FOUND ((const [uint16\_t](/docs/c/Standard_C/#uint16_t)) ~0)

#define MenuIndex ( section, row)

Macro to create a [MenuIndex](/docs/c/User_Interface/Layers/MenuLayer/#MenuIndex).

#define MENU\_CELL\_ROUND\_FOCUSED\_SHORT\_CELL\_HEIGHT ((const int16\_t) 68)

Constant value representing [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/) short cell height when this item is the selected item on a round display.

#define MENU\_CELL\_ROUND\_UNFOCUSED\_SHORT\_CELL\_HEIGHT ((const int16\_t) 24)

Constant value representing [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/) short cell height when this item is not the selected item on a round display.

#define MENU\_CELL\_ROUND\_FOCUSED\_TALL\_CELL\_HEIGHT ((const int16\_t) 84)

Constant value representing [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/) tall cell height when this item is the selected item on a round display.

#define MENU\_CELL\_ROUND\_UNFOCUSED\_TALL\_CELL\_HEIGHT ((const int16\_t) 32)

Constant value representing [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/) tall cell height when this item is not the selected item on a round display.
