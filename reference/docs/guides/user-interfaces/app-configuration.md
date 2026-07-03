# App Configuration

Source: https://developer.repebble.com/guides/user-interfaces/app-configuration/

Many watchfaces and watchapps in the Pebble appstore include the ability to customize their behavior or appearance through the use of a configuration page.

[Clay for Pebble](https://github.com/pebble-dev/clay) is the recommended approach for creating configuration pages, and is what will be covered in this guide. If you need to host your own configuration pages, please follow our[_Manual Setup_](/guides/user-interfaces/app-configuration-static.md) guide.

![Clay Sample](/assets/images/guides/user-interfaces/app-configuration/clay-sample.png)

Clay for Pebble dramatically simplifies the process of creating a configuration page, by allowing developers to define their application settings using a simple [JSON](https://en.wikipedia.org/wiki/JSON) file. Clay processes the JSON file and then dynamically generates a configuration page which matches the existing style of the Pebble mobile application, and it even works without an Internet connection.

## Enabling Configuration

For an app to be configurable, it must include the 'configurable' item in`package.json`.

```
"capabilities": ["configurable"]
```

The presence of this value tells the mobile app to display the gear icon that is associated with the ability to launch the config page next to the app itself.

## Installing Clay

Clay is available as a [_Pebble Package_](/guides/pebble-packages.md), so it takes minimal effort to install.

Within your project folder, just type:

```
$ pebble package install @rebble/clay
```

## Choosing messageKeys

When passing data between the configuration page and the watch application, we define `messageKeys` to help us easily identify the different values.

In this example, we're going to allow users to control the background color, foreground color, whether the watchface ticks on seconds and whether any animations are displayed.

We define `messageKeys` in the `package.json` file for each configuration setting in our application:

```
"messageKeys": ["BackgroundColor","ForegroundColor","SecondTick","Animations"]
```

## Creating the Clay Configuration

The Clay configuration file (`config.js`) should be created in your`src/pkjs/` folder. It allows the easy definition of each type of HTML form entity that is required. These types include:

- [Section](https://github.com/pebble-dev/clay#section)
- [Heading](https://github.com/pebble-dev/clay#heading)
- [Text](https://github.com/pebble-dev/clay#text)
- [Input](https://github.com/pebble-dev/clay#input)
- [Toggle](https://github.com/pebble-dev/clay#toggle)
- [Select](https://github.com/pebble-dev/clay#select)
- [Color Picker](https://github.com/pebble-dev/clay#color-picker)
- [Radio Group](https://github.com/pebble-dev/clay#radio-group)
- [Checkbox Group](https://github.com/pebble-dev/clay#checkbox-group)
- [Generic Button](https://github.com/pebble-dev/clay#generic-button)
- [Range Slider](https://github.com/pebble-dev/clay#range-slider)
- [Submit Button](https://github.com/pebble-dev/clay#submit)

In our example configuration page, we will add some introductory text, and group our fields into two sections. All configuration pages must have a submit button at the end, which is used to send the JSON data back to the watch.

![Clay](/assets/images/guides/user-interfaces/app-configuration/clay-actual.png)

Now start populating the configuration file with the sections you require, then add the required elements to each section. Be sure to assign the correct`messageKey` to each field.

```
module.exports = [{"type": "heading","defaultValue": "App Configuration"},{"type": "text","defaultValue": "Here is some introductory text."},{"type": "section","items": [{"type": "heading","defaultValue": "Colors"},{"type": "color","messageKey": "BackgroundColor","defaultValue": "0x000000","label": "Background Color"},{"type": "color","messageKey": "ForegroundColor","defaultValue": "0xFFFFFF","label": "Foreground Color"}]},{"type": "section","items": [{"type": "heading","defaultValue": "More Settings"},{"type": "toggle","messageKey": "SecondTick","label": "Enable Seconds","defaultValue": false},{"type": "toggle","messageKey": "Animations","label": "Enable Animations","defaultValue": false}]},{"type": "submit","defaultValue": "Save Settings"}];
```

## Initializing Clay

To initialize Clay, all you need to do is add the following JavaScript into your `index.js` file.

```
// Import the Clay packagevar Clay = require('@rebble/clay');// Load our Clay configuration filevar clayConfig = require('./config');// Initialize Clayvar clay = new Clay(clayConfig);
```

> When using the local SDK, it is possible to use a pure JSON configuration file (`config.json`). If this is the case, you must not include the `module.exports = []` in your configuration file, and you need to`var clayConfig = require('./config.json');`

## Receiving Config Data

Within our watchapp we need to open a connection with [`AppMessage`](/docs/c/Foundation/AppMessage/ "AppMessage") to begin listening for data from Clay, and also provide a handler to process the data once it has been received.

```
void prv\_init(void) {// ...// Open AppMessage connectionapp\_message\_register\_inbox\_received(prv\_inbox\_received\_handler);app\_message\_open(128, 128);// ...}
```

Once triggered, our handler will receive a [`DictionaryIterator`](/docs/c/Foundation/Dictionary/#DictionaryIterator "DictionaryIterator") containing[`Tuple`](/docs/c/Foundation/Dictionary/#Tuple "Tuple") objects for each `messageKey`. Note that the key names need to be prefixed with `MESSAGE_KEY_`.

```
static void prv\_inbox\_received\_handler(DictionaryIterator \*iter, void \*context) {// Read color preferencesTuple \*bg\_color\_t = dict\_find(iter, MESSAGE\_KEY\_BackgroundColor);if(bg\_color\_t) {GColor bg\_color = GColorFromHEX(bg\_color\_t-\>value-\>int32);}Tuple \*fg\_color\_t = dict\_find(iter, MESSAGE\_KEY\_ForegroundColor);if(fg\_color\_t) {GColor fg\_color = GColorFromHEX(fg\_color\_t-\>value-\>int32);}// Read boolean preferencesTuple \*second\_tick\_t = dict\_find(iter, MESSAGE\_KEY\_SecondTick);if(second\_tick\_t) {bool second\_ticks = second\_tick\_t-\>value-\>int32 == 1;}Tuple \*animations\_t = dict\_find(iter, MESSAGE\_KEY\_Animations);if(animations\_t) {bool animations = animations\_t-\>value-\>int32 == 1;}}
```

## Persisting Settings

By default, Clay will persist your settings in localStorage within the mobile application. It is common practice to also save settings within the persistent storage on the watch. This creates a seemless experience for users launching your application, as their settings can be applied on startup. This means there isn't an initial delay while the settings are loaded from the phone.

You could save each individual value within the persistent storage, or you could create a struct to hold all of your settings, and save that entire object. This has the benefit of simplicity, and because writing to persistent storage is slow, it also provides improved performance.

```
// Persistent storage key#define SETTINGS\_KEY 1// Define our settings structtypedef struct ClaySettings {GColor BackgroundColor;GColor ForegroundColor;bool SecondTick;bool Animations;} ClaySettings;// An instance of the structstatic ClaySettings settings;// AppMessage receive handlerstatic void prv\_inbox\_received\_handler(DictionaryIterator \*iter, void \*context) {// Assign the values to our structTuple \*bg\_color\_t = dict\_find(iter, MESSAGE\_KEY\_BackgroundColor);if (bg\_color\_t) {settings.BackgroundColor = GColorFromHEX(bg\_color\_t-\>value-\>int32);}// ...prv\_save\_settings();}// Save the settings to persistent storagestatic void prv\_save\_settings() {persist\_write\_data(SETTINGS\_KEY, &settings, sizeof(settings));}
```

You can see a complete implementation of persisting a settings struct in the[Pebble Clay Example](https://github.com/pebble-examples/clay-example).

## What's Next

If you're thinking that Clay won't be as flexible as hand crafting your own configuration pages, you're mistaken.

Developers can extend the functionality of Clay in a number of ways:

- Define a[custom function](https://github.com/pebble-dev/clay#custom-function) to enhance the interactivity of the page.
- [Override events](https://github.com/pebble-dev/clay#handling-the-showconfiguration-and-webviewclosed-events-manually)and transform the format of the data before it's transferred to the watch.
- Create and share your own[custom components](https://github.com/pebble-dev/clay#custom-components).

Why not find out more about [Clay for Pebble](https://github.com/pebble-dev/clay)and perhaps even[contribute](https://github.com/pebble-dev/clay/blob/master/CONTRIBUTING.md) to the project, it's open source!
