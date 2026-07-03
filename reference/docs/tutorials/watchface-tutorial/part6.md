# Adding a settings page

Source: https://developer.repebble.com/tutorials/watchface-tutorial/part6/

# Adding a settings page

This page contains some instructions that are different if you're using CloudPebble or if you're using the SDK locally on your computer.

Select whether you're using CloudPebble or the SDK below to show the relevant instructions!

[![](/assets/images/sdk/cloud.svg)
#### CloudPebble
](javascript:void();)[![](/assets/images/sdk/sdk-box.svg)
#### SDK
](javascript:void();)

![](/assets/images/sdk/cloud.svg) Showing instructions for CloudPebble. [Not using CloudPebble?](javascript:%20void();)

![](/assets/images/sdk/sdk-box.svg) Showing instructions for the SDK. [Using CloudPebble?](javascript:%20void();)

The finishing touch for any great watchface is letting users make it their own. In this final part we will add a configuration page using[Clay for Pebble](https://github.com/pebble-dev/clay), which generates a settings UI on the phone from a simple JSON definition. Users will be able to pick colors, choose temperature units, and toggle the date display.

Here is an example of a customized watchface:

#### aplite

#### basalt

#### chalk

#### diorite

#### emery

#### gabbro

 ![](/assets/images/tutorials/watchface-tutorial/part6~aplite.png)

 ![](/assets/images/tutorials/watchface-tutorial/part6~basalt.png)

 ![](/assets/images/tutorials/watchface-tutorial/part6~chalk.png)

 ![](/assets/images/tutorials/watchface-tutorial/part6~diorite.png)

 ![](/assets/images/tutorials/watchface-tutorial/part6~emery.png)

 ![](/assets/images/tutorials/watchface-tutorial/part6~gabbro.png)

This section continues from[_Part 5_](/tutorials/watchface-tutorial/part5.md).

## Installing Clay

In CloudPebble, go to the **Dependencies** section in the left sidebar and add`@rebble/clay` as a NPM Dependency.

Clay is available as a Pebble Package. Install it from your project directory:

```
$ pebble package install @rebble/clay
```

This adds `@rebble/clay` to the `dependencies` in `package.json`.

## Enabling Configuration

In CloudPebble, go to **Settings** and add `configurable` to the **Capabilities** list so the gear icon appears next to your watchface in the phone app.

For the gear icon to appear next to your watchface in the phone app, add`configurable` to the `capabilities` array in `package.json`:

```
"capabilities": ["location","configurable"]
```

## Defining Message Keys

In CloudPebble, go to **Settings** and add the following message keys in the **PebbleKit JS Message Keys** section: `BackgroundColor`, `TextColor`,`TemperatureUnit`, and `ShowDate`.

We need message keys for each setting. Add these to the `messageKeys` array, alongside the existing weather keys:

```
"messageKeys": ["TEMPERATURE","CONDITIONS","REQUEST\_WEATHER","BackgroundColor","TextColor","TemperatureUnit","ShowDate"]
```

These become `MESSAGE_KEY_BackgroundColor`, `MESSAGE_KEY_TextColor`, etc. in C.

## Creating the Clay Configuration

Click **Add New** next to **Source Files** in the left sidebar, select **JavaScript file** , and name it `config.js`. Clay uses a simple JSON array of sections and fields:

Create `src/pkjs/config.js` with the configuration definition. Clay uses a simple JSON array of sections and fields:

```
module.exports = [{"type": "heading","defaultValue": "Watchface Settings"},{"type": "text","defaultValue": "Customize your watchface appearance and preferences."},{"type": "section","items": [{"type": "heading","defaultValue": "Colors"},{"type": "color","messageKey": "BackgroundColor","defaultValue": "0x000000","label": "Background Color"},{"type": "color","messageKey": "TextColor","defaultValue": "0xFFFFFF","label": "Text Color"}]},{"type": "section","items": [{"type": "heading","defaultValue": "Preferences"},{"type": "toggle","messageKey": "TemperatureUnit","label": "Use Fahrenheit","defaultValue": false},{"type": "toggle","messageKey": "ShowDate","label": "Show Date","defaultValue": true}]},{"type": "submit","defaultValue": "Save Settings"}];
```

Each `messageKey` matches a key in `package.json`. The `color` type provides a color picker, `toggle` gives a switch.

## Initializing Clay in JavaScript

Add three lines at the top of `src/pkjs/index.js`, before any other code:

```
var Clay = require('@rebble/clay');var clayConfig = require('./config');var clay = new Clay(clayConfig);
```

Clay automatically handles the `showConfiguration` and `webviewClosed` events. Your existing weather code works alongside Clay without changes.

## Persisting Settings on the Watch

On the C side, define a struct to hold all settings and use persistent storage to save them across app restarts.

At the top of the file:

```
#define SETTINGS\_KEY 1typedef struct ClaySettings {GColor BackgroundColor;GColor TextColor;bool TemperatureUnit; // false = Celsius, true = Fahrenheitbool ShowDate;} ClaySettings;static ClaySettings settings;
```

Add helper functions for defaults, save, and load:

```
static void prv\_default\_settings() {settings.BackgroundColor = GColorBlack;settings.TextColor = GColorWhite;settings.TemperatureUnit = false;settings.ShowDate = true;}static void prv\_save\_settings() {persist\_write\_data(SETTINGS\_KEY, &settings, sizeof(settings));}static void prv\_load\_settings() {prv\_default\_settings();persist\_read\_data(SETTINGS\_KEY, &settings, sizeof(settings));}
```

`prv_load_settings()` sets defaults first, then overwrites with any saved data. This ensures new fields always have valid defaults.

Call `prv_load_settings()` at the start of `init()`, before creating the window:

```
static void init() {prv\_load\_settings();// ... rest of init}
```

## Applying Settings to the UI

Create a function that updates all visual elements based on current settings:

```
static void prv\_update\_display() {window\_set\_background\_color(s\_main\_window, settings.BackgroundColor);text\_layer\_set\_text\_color(s\_time\_layer, settings.TextColor);text\_layer\_set\_text\_color(s\_date\_layer, settings.TextColor);text\_layer\_set\_text\_color(s\_weather\_layer, settings.TextColor);// Show/hide date based on settinglayer\_set\_hidden(text\_layer\_get\_layer(s\_date\_layer), !settings.ShowDate);layer\_mark\_dirty(s\_battery\_layer);}
```

Call this at the end of `main_window_load()` to apply saved settings on startup.

We also need to update the battery drawing. The color-coded levels from Part 3 stay the same on color platforms, but we use `settings.TextColor` for the border and as the monochrome fallback so the bar respects the user's color choice:

```
static void battery\_update\_proc(Layer \*layer, GContext \*ctx) {GRect bounds = layer\_get\_bounds(layer);// Find the width of the bar (inside the border)int bar\_width = ((s\_battery\_level \* (bounds.size.w - 4)) / 100);// Draw the border using the text colorgraphics\_context\_set\_stroke\_color(ctx, settings.TextColor);graphics\_draw\_round\_rect(ctx, bounds, 2);// Choose color based on battery levelGColor bar\_color;if (s\_battery\_level \<= 20) {bar\_color = PBL\_IF\_COLOR\_ELSE(GColorRed, settings.TextColor);} else if (s\_battery\_level \<= 40) {bar\_color = PBL\_IF\_COLOR\_ELSE(GColorChromeYellow, settings.TextColor);} else {bar\_color = PBL\_IF\_COLOR\_ELSE(GColorGreen, settings.TextColor);}// Draw the filled bar inside the bordergraphics\_context\_set\_fill\_color(ctx, bar\_color);graphics\_fill\_rect(ctx, GRect(2, 2, bar\_width, bounds.size.h - 4), 1, GCornerNone);}
```

## Handling Settings in the Inbox

The tricky part: our `inbox_received_callback` now handles two types of messages - weather data AND configuration changes. We differentiate by checking which keys are present:

```
static void inbox\_received\_callback(DictionaryIterator \*iterator, void \*context) {// Check for weather dataTuple \*temp\_tuple = dict\_find(iterator, MESSAGE\_KEY\_TEMPERATURE);Tuple \*conditions\_tuple = dict\_find(iterator, MESSAGE\_KEY\_CONDITIONS);if (temp\_tuple && conditions\_tuple) {static char temperature\_buffer[8];static char conditions\_buffer[32];static char weather\_layer\_buffer[42];int temp\_value = (int)temp\_tuple-\>value-\>int32;// Convert to Fahrenheit if setting is enabledif (settings.TemperatureUnit) {temp\_value = (temp\_value \* 9 / 5) + 32;snprintf(temperature\_buffer, sizeof(temperature\_buffer), "%d°F", temp\_value);} else {snprintf(temperature\_buffer, sizeof(temperature\_buffer), "%d°C", temp\_value);}snprintf(conditions\_buffer, sizeof(conditions\_buffer), "%s", conditions\_tuple-\>value-\>cstring);snprintf(weather\_layer\_buffer, sizeof(weather\_layer\_buffer), "%s %s", temperature\_buffer, conditions\_buffer);text\_layer\_set\_text(s\_weather\_layer, weather\_layer\_buffer);}// Check for Clay settingsTuple \*bg\_color\_t = dict\_find(iterator, MESSAGE\_KEY\_BackgroundColor);if (bg\_color\_t) {settings.BackgroundColor = GColorFromHEX(bg\_color\_t-\>value-\>int32);}Tuple \*text\_color\_t = dict\_find(iterator, MESSAGE\_KEY\_TextColor);if (text\_color\_t) {settings.TextColor = GColorFromHEX(text\_color\_t-\>value-\>int32);}Tuple \*temp\_unit\_t = dict\_find(iterator, MESSAGE\_KEY\_TemperatureUnit);if (temp\_unit\_t) {settings.TemperatureUnit = temp\_unit\_t-\>value-\>int32 == 1;}Tuple \*show\_date\_t = dict\_find(iterator, MESSAGE\_KEY\_ShowDate);if (show\_date\_t) {settings.ShowDate = show\_date\_t-\>value-\>int32 == 1;}// Save and apply if any settings were changedif (bg\_color\_t || text\_color\_t || temp\_unit\_t || show\_date\_t) {prv\_save\_settings();prv\_update\_display();// Refetch weather if the temperature unit changed so the display updatesif (temp\_unit\_t) {DictionaryIterator \*iter;app\_message\_outbox\_begin(&iter);dict\_write\_uint8(iter, MESSAGE\_KEY\_REQUEST\_WEATHER, 1);app\_message\_outbox\_send();}}}
```

Weather messages contain `TEMPERATURE` and `CONDITIONS` keys. Clay messages contain `BackgroundColor`, `TextColor`, etc. Both can be handled independently in the same callback.

Notice that when the temperature unit changes we immediately request a weather refresh. Without this, the display would keep showing the old unit until the next scheduled 30-minute update.

Also increase the AppMessage buffer sizes in `init()` to accommodate the larger Clay messages:

```
const int inbox\_size = 256;const int outbox\_size = 256;
```

## Trying It Out

Click the **play** button to compile and install, then tap the gear icon in the emulator to open the settings page.

Build and install your watchface, then use `pebble emu-app-config` to open the settings page in your browser:

```
$ pebble build && pebble install --emulator emery$ pebble emu-app-config
```

Try changing the background color, text color, and toggling the date and temperature unit - you should see the watchface update immediately.

![Settings page on phone](/assets/images/tutorials/watchface-tutorial/part6-settings.gif)

## Updating Timeline Peek for Settings

Since our Timeline Peek handlers reposition layers rather than hiding them, no changes are needed there for Clay settings. The ShowDate toggle is handled entirely in `prv_update_display()` - when the date is hidden, it simply stays hidden regardless of the obstruction state.

## Conclusion

Congratulations! You have built a complete, feature-rich Pebble watchface. Here is everything it includes:

1. **Digital time display** with a custom font.
2. **Date display** that can be toggled on/off.
3. **Live weather** from Open-Meteo (no API key needed).
4. **Battery meter** drawn with custom graphics.
5. **Bluetooth disconnect** icon and vibration alert.
6. **Timeline Peek** support with smooth animations.
7. **Clay configuration** for colors and preferences.
8. **Persistent settings** that survive app restarts.

In this final part we learned how to:

- Install and configure Clay for Pebble.
- Define a settings page with color pickers and toggles.
- Persist settings on the watch with [`persist_write_data()`](/docs/c/Foundation/Storage/#persist_write_data "persist\_write\_data").
- Handle mixed message types (weather + config) in a single inbox callback.
- Apply settings dynamically to all UI elements.

Check your code against[the source for this part](https://github.com/coredevices/c-watchface-tutorial/tree/main/part6). Now it is time to[publish your watchface](https://developer.repebble.com/dashboard)and share it with the world!
