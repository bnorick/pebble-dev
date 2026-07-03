# Layers

Source: https://developer.repebble.com/guides/user-interfaces/layers/

The [`Layer`](/docs/c/User_Interface/Layers/#Layer "Layer") and associated subclasses (such as [`TextLayer`](/docs/c/User_Interface/Layers/TextLayer/ "TextLayer") and[`BitmapLayer`](/docs/c/User_Interface/Layers/BitmapLayer/ "BitmapLayer")) form the foundation of the UI for every Pebble watchapp or watchface, and are added to a [`Window`](/docs/c/User_Interface/Window/ "Window") to construct the UI's design. Each[`Layer`](/docs/c/User_Interface/Layers/#Layer "Layer") type contains at least three basic elements:

- Frame - contains the position and dimensions of the [`Layer`](/docs/c/User_Interface/Layers/#Layer "Layer"), relative to the parent object.

- Bounds - contains the drawable bounding box within the frame. This allows only a portion of the layer to be visible, and is relative to the [`Layer`](/docs/c/User_Interface/Layers/#Layer "Layer") frame.

- Update procedure - the function that performs the drawing whenever the[`Layer`](/docs/c/User_Interface/Layers/#Layer "Layer") is rendered. The subclasses implement a convenience update procedure with additional data to achieve their specialization.

## Layer Heirachy

Every app must consist of at least one [`Window`](/docs/c/User_Interface/Window/ "Window") in order to successfully launch. Mutiple [`Layer`](/docs/c/User_Interface/Layers/#Layer "Layer") objects are added as children of the [`Window`](/docs/c/User_Interface/Window/ "Window"), which itself contains a [`Layer`](/docs/c/User_Interface/Layers/#Layer "Layer") known as the 'root layer'. When the [`Window`](/docs/c/User_Interface/Window/ "Window") is rendered, each child [`Layer`](/docs/c/User_Interface/Layers/#Layer "Layer") is rendered in the order in which they were added. For example:

```
static Window \*s\_main\_window;static BitmapLayer \*s\_background\_layer;static TextLayer \*s\_time\_layer;
```

```
// Get the Window's root layerLayer \*root\_layer = window\_get\_root\_layer(s\_main\_window);/\* set up BitmapLayer and TextLayer \*/// Add the background layer first, so that it is drawn behind the timelayer\_add\_child(root\_layer, bitmap\_layer\_get\_layer(s\_background\_layer));// Add the time layer secondlayer\_add\_child(root\_layer, text\_layer\_get\_layer(s\_time\_layer));
```

Once added to a [`Window`](/docs/c/User_Interface/Window/ "Window"), the ordering of each [`Layer`](/docs/c/User_Interface/Layers/#Layer "Layer") cannot be modified, but one can be placed at the front by removing and re-adding it to the heirachy:

```
// Bring a layer to the frontlayer\_remove\_from\_parent(s\_some\_layer);layer\_add\_child(root\_layer, s\_some\_layer);
```

## Update Procedures

For creating custom drawing implementations, the basic [`Layer`](/docs/c/User_Interface/Layers/#Layer "Layer") update procedure can be reassigned to one created by a developer. This takes the form of a [`LayerUpdateProc`](/docs/c/User_Interface/Layers/#LayerUpdateProc "LayerUpdateProc"), and provides a [`GContext`](/docs/c/Graphics/Graphics_Context/ "Graphics Context")object which can be used for drawing primitive shapes, paths, text, and images.

> Note: See [_Graphics and Animations_](/guides/graphics-and-animations.md) for more information on drawing with the graphics context.

```
static void layer\_update\_proc(Layer \*layer, GContext \*ctx) {// Custom drawing happens here}
```

This function must then be assigned to the [`Layer`](/docs/c/User_Interface/Layers/#Layer "Layer") that will be drawn with it:

```
// Set this Layer's update procedurelayer\_set\_update\_proc(s\_some\_layer, layer\_update\_proc);
```

The update procedure will be called every time the [`Layer`](/docs/c/User_Interface/Layers/#Layer "Layer") must be redrawn. This is typically when any other [`Layer`](/docs/c/User_Interface/Layers/#Layer "Layer") requests a redraw, the [`Window`](/docs/c/User_Interface/Window/ "Window") is shown/hidden, the heirarchy changes, or a modal (such as a notification) appears. The [`Layer`](/docs/c/User_Interface/Layers/#Layer "Layer") can also be manually marked as 'dirty', and will be redrawn at the next opportunity (usually immediately):

```
// Request a redrawlayer\_mark\_dirty(s\_some\_layer);
```

## Layer Subclasses

For convenience, there are multiple subclasses of [`Layer`](/docs/c/User_Interface/Layers/#Layer "Layer") included in the Pebble SDK to allow developers to easily construct their app's UI. Each should be created when the [`Window`](/docs/c/User_Interface/Window/ "Window") is loading (using the `.load` [`WindowHandler`](/docs/c/User_Interface/Window/#WindowHandler "WindowHandler")) and destroyed when it is unloading (using `.the unload` [`WindowHandler`](/docs/c/User_Interface/Window/#WindowHandler "WindowHandler")).

These are briefly outlined below, alongside a simple usage example split into three code snippets - the element declarations, the setup procedure, and the teardown procedure.

### TextLayer

The [`TextLayer`](/docs/c/User_Interface/Layers/TextLayer/ "TextLayer") is the most commonly used subclass of [`Layer`](/docs/c/User_Interface/Layers/#Layer "Layer"), and allows apps to render text using any available font, with built-in behavior to handle text color, line wrapping, alignment, etc.

```
static TextLayer \*s\_text\_layer;
```

```
// Create a TextLayers\_text\_layer = text\_layer\_create(bounds);// Set some propertiestext\_layer\_set\_text\_color(s\_text\_layer, GColorWhite);text\_layer\_set\_background\_color(s\_text\_layer, GColorBlack);text\_layer\_set\_overflow\_mode(s\_text\_layer, GTextOverflowModeWordWrap);text\_layer\_set\_alignment(s\_text\_layer, GTextAlignmentCenter);// Set the text showntext\_layer\_set\_text(s\_text\_layer, "Hello, World!");// Add to the Windowlayer\_add\_child(root\_layer, text\_layer\_get\_layer(s\_text\_layer));
```

```
// Destroy the TextLayertext\_layer\_destroy(s\_text\_layer);
```

### BitmapLayer

The [`BitmapLayer`](/docs/c/User_Interface/Layers/BitmapLayer/ "BitmapLayer") provides an easy way to show images loaded into [`GBitmap`](/docs/c/Graphics/Graphics_Types/#GBitmap "GBitmap")objects from an image resource. Images shown using a [`BitmapLayer`](/docs/c/User_Interface/Layers/BitmapLayer/ "BitmapLayer") are automatically centered within the bounds provided to [`bitmap_layer_create()`](/docs/c/User_Interface/Layers/BitmapLayer/#bitmap_layer_create "bitmap\_layer\_create"). Read [_Images_](/guides/app-resources/images.md) to learn more about using image resources in apps.

> Note: PNG images with transparency should use `bitmap` resource type, and use the [`GCompOpSet`](/docs/c/Graphics/Graphics_Types/#GCompOpSet "GCompOpSet") compositing mode when being displayed, as shown below.

```
static BitmapLayer \*s\_bitmap\_layer;static GBitmap \*s\_bitmap;
```

```
// Load the images\_bitmap = gbitmap\_create\_with\_resource(RESOURCE\_ID\_EXAMPLE\_IMAGE);// Create a BitmapLayers\_bitmap\_layer = bitmap\_layer\_create(bounds);// Set the bitmap and compositing modebitmap\_layer\_set\_bitmap(s\_bitmap\_layer, s\_bitmap);bitmap\_layer\_set\_compositing\_mode(s\_bitmap\_layer, GCompOpSet);// Add to the Windowlayer\_add\_child(root\_layer, bitmap\_layer\_get\_layer(s\_bitmap\_layer));
```

```
// Destroy the BitmapLayerbitmap\_layer\_destroy(s\_bitmap\_layer);
```

### StatusBarLayer

If a user needs to see the current time inside an app (instead of exiting to the watchface), the [`StatusBarLayer`](/docs/c/User_Interface/Layers/StatusBarLayer/ "StatusBarLayer") component can be used to display this information at the top of the [`Window`](/docs/c/User_Interface/Window/ "Window"). Colors and separator display style can be customized.

```
static StatusBarLayer \*s\_status\_bar;
```

```
// Create the StatusBarLayers\_status\_bar = status\_bar\_layer\_create();// Set propertiesstatus\_bar\_layer\_set\_colors(s\_status\_bar, GColorBlack, GColorBlueMoon);status\_bar\_layer\_set\_separator\_mode(s\_status\_bar, StatusBarLayerSeparatorModeDotted);// Add to Windowlayer\_add\_child(root\_layer, status\_bar\_layer\_get\_layer(s\_status\_bar));
```

```
// Destroy the StatusBarLayerstatus\_bar\_layer\_destroy(s\_status\_bar);
```

### MenuLayer

The [`MenuLayer`](/docs/c/User_Interface/Layers/MenuLayer/ "MenuLayer") allows the user to scroll a list of options using the Up and Down buttons, and select an option to trigger an action using the Select button. It differs from the other [`Layer`](/docs/c/User_Interface/Layers/#Layer "Layer") subclasses in that it makes use of a number of [`MenuLayerCallbacks`](/docs/c/User_Interface/Layers/MenuLayer/#MenuLayerCallbacks "MenuLayerCallbacks") to allow the developer to fully control how it renders and behaves. Some minimum example callbacks are shown below:

```
static MenuLayer \*s\_menu\_layer;
```

```
static uint16\_t get\_num\_rows\_callback(MenuLayer \*menu\_layer, uint16\_t section\_index, void \*context) {const uint16\_t num\_rows = 5;return num\_rows;}static void draw\_row\_callback(GContext \*ctx, const Layer \*cell\_layer, MenuIndex \*cell\_index, void \*context) {static char s\_buff[16];snprintf(s\_buff, sizeof(s\_buff), "Row %d", (int)cell\_index-\>row);// Draw this row's indexmenu\_cell\_basic\_draw(ctx, cell\_layer, s\_buff, NULL, NULL);}static int16\_t get\_cell\_height\_callback(struct MenuLayer \*menu\_layer, MenuIndex \*cell\_index, void \*context) {const int16\_t cell\_height = 44;return cell\_height;}static void select\_callback(struct MenuLayer \*menu\_layer, MenuIndex \*cell\_index, void \*context) {// Do something in response to the button press}
```

```
// Create the MenuLayers\_menu\_layer = menu\_layer\_create(bounds);// Let it receive click eventsmenu\_layer\_set\_click\_config\_onto\_window(s\_menu\_layer, window);// Set the callbacks for behavior and renderingmenu\_layer\_set\_callbacks(s\_menu\_layer, NULL, (MenuLayerCallbacks) {.get\_num\_rows = get\_num\_rows\_callback,.draw\_row = draw\_row\_callback,.get\_cell\_height = get\_cell\_height\_callback,.select\_click = select\_callback,});// Add to the Windowlayer\_add\_child(root\_layer, menu\_layer\_get\_layer(s\_menu\_layer));
```

```
// Destroy the MenuLayermenu\_layer\_destroy(s\_menu\_layer);
```

### ScrollLayer

The [`ScrollLayer`](/docs/c/User_Interface/Layers/ScrollLayer/ "ScrollLayer") provides an easy way to use the Up and Down buttons to scroll large content that does not all fit onto the screen at the same time. The usage of this type differs from the others in that the [`Layer`](/docs/c/User_Interface/Layers/#Layer "Layer") objects that are scrolled are added as children of the [`ScrollLayer`](/docs/c/User_Interface/Layers/ScrollLayer/ "ScrollLayer"), which is then in turn added as a child of the [`Window`](/docs/c/User_Interface/Window/ "Window").

The [`ScrollLayer`](/docs/c/User_Interface/Layers/ScrollLayer/ "ScrollLayer") frame is the size of the 'viewport', while the content size determines how far the user can scroll in each direction. The example below shows a [`ScrollLayer`](/docs/c/User_Interface/Layers/ScrollLayer/ "ScrollLayer") scrolling some long text, the total size of which is calculated with [`graphics_text_layout_get_content_size()`](/docs/c/Graphics/Drawing_Text/#graphics_text_layout_get_content_size "graphics\_text\_layout\_get\_content\_size") and used as the[`ScrollLayer`](/docs/c/User_Interface/Layers/ScrollLayer/ "ScrollLayer") content size.

> Note: The scrolled [`TextLayer`](/docs/c/User_Interface/Layers/TextLayer/ "TextLayer") frame is relative to that of its parent, the[`ScrollLayer`](/docs/c/User_Interface/Layers/ScrollLayer/ "ScrollLayer").

```
static TextLayer \*s\_text\_layer;static ScrollLayer \*s\_scroll\_layer;
```

```
GFont font = fonts\_get\_system\_font(FONT\_KEY\_GOTHIC\_28\_BOLD);// Find the bounds of the scrolling textGRect shrinking\_rect = GRect(0, 0, bounds.size.w, 2000);char \*text = "Example text that is really really really really really \ really really really really really really long";GSize text\_size = graphics\_text\_layout\_get\_content\_size(text, font, shrinking\_rect, GTextOverflowModeWordWrap, GTextAlignmentLeft);GRect text\_bounds = bounds;text\_bounds.size.h = text\_size.h;// Create the TextLayers\_text\_layer = text\_layer\_create(text\_bounds);text\_layer\_set\_overflow\_mode(s\_text\_layer, GTextOverflowModeWordWrap);text\_layer\_set\_font(s\_text\_layer, font);text\_layer\_set\_text(s\_text\_layer, text);// Create the ScrollLayers\_scroll\_layer = scroll\_layer\_create(bounds);// Set the scrolling content sizescroll\_layer\_set\_content\_size(s\_scroll\_layer, text\_size);// Let the ScrollLayer receive click eventsscroll\_layer\_set\_click\_config\_onto\_window(s\_scroll\_layer, window);// Add the TextLayer as a child of the ScrollLayerscroll\_layer\_add\_child(s\_scroll\_layer, text\_layer\_get\_layer(s\_text\_layer));// Add the ScrollLayer as a child of the Windowlayer\_add\_child(root\_layer, scroll\_layer\_get\_layer(s\_scroll\_layer));
```

```
// Destroy the ScrollLayer and TextLayerscroll\_layer\_destroy(s\_scroll\_layer);text\_layer\_destroy(s\_text\_layer);
```

### ActionBarLayer

The [`ActionBarLayer`](/docs/c/User_Interface/Layers/ActionBarLayer/ "ActionBarLayer") allows apps to use the familiar black right-hand bar, featuring icons denoting the action that will occur when each button on the right hand side is pressed. For example, 'previous track', 'more actions', and 'next track' in the built-in Music app.

For three or fewer actions, the [`ActionBarLayer`](/docs/c/User_Interface/Layers/ActionBarLayer/ "ActionBarLayer") can be more appropriate than a [`MenuLayer`](/docs/c/User_Interface/Layers/MenuLayer/ "MenuLayer") for presenting the user with a list of actionable options. Each action's icon must also be loaded into a [`GBitmap`](/docs/c/Graphics/Graphics_Types/#GBitmap "GBitmap") object from app resources. The example below demonstrates show to set up an [`ActionBarLayer`](/docs/c/User_Interface/Layers/ActionBarLayer/ "ActionBarLayer") showing an up, down, and checkmark icon for each of the buttons.

```
static ActionBarLayer \*s\_action\_bar;static GBitmap \*s\_up\_bitmap, \*s\_down\_bitmap, \*s\_check\_bitmap;
```

```
// Load icon bitmapss\_up\_bitmap = gbitmap\_create\_with\_resource(RESOURCE\_ID\_UP\_ICON);s\_down\_bitmap = gbitmap\_create\_with\_resource(RESOURCE\_ID\_DOWN\_ICON);s\_check\_bitmap = gbitmap\_create\_with\_resource(RESOURCE\_ID\_CHECK\_ICON);// Create ActionBarLayers\_action\_bar = action\_bar\_layer\_create();action\_bar\_layer\_set\_click\_config\_provider(s\_action\_bar, click\_config\_provider);// Set the iconsaction\_bar\_layer\_set\_icon(s\_action\_bar, BUTTON\_ID\_UP, s\_up\_bitmap);action\_bar\_layer\_set\_icon(s\_action\_bar, BUTTON\_ID\_DOWN, s\_down\_bitmap);action\_bar\_layer\_set\_icon(s\_action\_bar, BUTTON\_ID\_SELECT, s\_check\_bitmap);// Add to Windowaction\_bar\_layer\_add\_to\_window(s\_action\_bar, window);
```

```
// Destroy the ActionBarLayeraction\_bar\_layer\_destroy(s\_action\_bar);// Destroy the icon GBitmapsgbitmap\_destroy(s\_up\_bitmap);gbitmap\_destroy(s\_down\_bitmap);gbitmap\_destroy(s\_check\_bitmap);
```
