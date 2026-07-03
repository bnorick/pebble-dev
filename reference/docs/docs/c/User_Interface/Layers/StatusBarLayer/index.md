# StatusBarLayer

Source: https://developer.repebble.com/docs/c/User_Interface/Layers/StatusBarLayer/index.html

Layer that serves as a configurable status bar.

## Function Documentation

StatusBarLayer \* status\_bar\_layer\_create(void)

Creates a new StatusBarLayer on the heap and initializes it with the default values.

- Text color: [GColorBlack](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorBlack)

- Background color: [GColorWhite](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorWhite)

- Frame: `GRect(0, 0, screen_width, STATUS_BAR_LAYER_HEIGHT)` The status bar is automatically marked dirty after this operation. You can call [layer\_set\_frame()](/docs/c/User_Interface/Layers/#layer_set_frame) to create a StatusBarLayer of a different width.

```
// Change the status bar width to make space for the action barint16\_t width = layer\_get\_bounds(root\_layer).size.w - ACTION\_BAR\_WIDTH;GRect frame = GRect(0, 0, width, STATUS\_BAR\_LAYER\_HEIGHT);layer\_set\_frame(status\_bar\_layer\_get\_layer(status\_bar), frame);layer\_add\_child(root\_layer, status\_bar\_layer\_get\_layer(status\_bar));
```

#### Returns

A pointer to the StatusBarLayer, which will be allocated to the heap, `NULL` if the StatusBarLayer could not be created

void status\_bar\_layer\_destroy(StatusBarLayer \* status\_bar\_layer)

Destroys a StatusBarLayer previously created by status\_bar\_layer\_create.

#### Parameters
 status\_bar\_layer

The StatusBarLayer to destroy

Layer \* status\_bar\_layer\_get\_layer(StatusBarLayer \* status\_bar\_layer)

Gets the "root" Layer of the status bar, which is the parent for the sub- layers used for its implementation.

##### Note

The result is always equal to `(Layer *) status_bar_layer`.

#### Parameters
 status\_bar\_layer

Pointer to the StatusBarLayer for which to get the "root" Layer

#### Returns

The "root" Layer of the status bar.

GColor status\_bar\_layer\_get\_background\_color(const StatusBarLayer \* status\_bar\_layer)

Gets background color of StatusBarLayer.

#### Parameters
 status\_bar\_layer

The StatusBarLayer of which to get the color

#### Returns

GColor of background color property

GColor status\_bar\_layer\_get\_foreground\_color(const StatusBarLayer \* status\_bar\_layer)

Gets foreground color of StatusBarLayer.

#### Parameters
 status\_bar\_layer

The StatusBarLayer of which to get the color

#### Returns

GColor of foreground color property

void status\_bar\_layer\_set\_colors(StatusBarLayer \* status\_bar\_layer, GColor background, GColor foreground)

Sets the background and foreground colors of StatusBarLayer.

#### Parameters
 status\_bar\_layer

The StatusBarLayer of which to set the colors

 background

The new GColor to set for background

 foreground

The new GColor to set for text and other foreground elements

void status\_bar\_layer\_set\_separator\_mode(StatusBarLayer \* status\_bar\_layer, [StatusBarLayerSeparatorMode](/docs/c/User_Interface/Layers/StatusBarLayer/#StatusBarLayerSeparatorMode) mode)

Sets the mode of the StatusBarLayer separator, to help divide it from content.

#### Parameters
 status\_bar\_layer

The StatusBarLayer of which to set the separator mode

 mode

Determines the separator mode

## Enum Documentation

enum StatusBarLayerSeparatorMode

Values that are used to indicate the different status bar separator modes.

#### Enumerators
StatusBarLayerSeparatorModeNone

The default mode. No separator will be shown.

StatusBarLayerSeparatorModeDotted

A dotted separator at the bottom of the status bar.

## Typedef Documentation

 typedef struct StatusBarLayer StatusBarLayer

## Macro Definition Documentation

#define STATUS\_BAR\_LAYER\_HEIGHT [\_STATUS\_BAR\_LAYER\_HEIGHT](/docs/c/User_Interface/Layers/StatusBarLayer/#_STATUS_BAR_LAYER_HEIGHT)(PBL\_PLATFORM\_TYPE\_CURRENT)

The fixed height of the status bar, including separator height.

- [SDK 3](javascript:void(0);)
- [SDK 4](javascript:void(0);)
- [SDK 4.9+](javascript:void(0);)

#define \_STATUS\_BAR\_LAYER\_HEIGHT ( plat)

The fixed height of the status bar, including separator height, for all platforms.

#define \_STATUS\_BAR\_LAYER\_HEIGHT ( plat)

The fixed height of the status bar, including separator height, for all platforms.

#define \_STATUS\_BAR\_LAYER\_HEIGHT ( plat)

The fixed height of the status bar, including separator height, for all platforms.
