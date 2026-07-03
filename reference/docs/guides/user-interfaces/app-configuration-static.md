# App Configuration (manual setup)

Source: https://developer.repebble.com/guides/user-interfaces/app-configuration-static/

> This guide provides the steps to manually create an app configuration page. The preferred approach is to use[_Clay for Pebble_](/guides/user-interfaces/app-configuration.md) instead.

Many watchfaces and apps in the Pebble appstore include the ability to customize their behavior or appearance through the use of a configuration page. This mechanism consists of an HTML form that passes the user's chosen configuration data to PebbleKit JS, which in turn relays it to the watchface or watchapp.

The HTML page created needs to be hosted online, so that it is accessible to users via the Pebble application. If you do not want to host your own HTML page, you should follow the[_Clay guide_](/guides/user-interfaces/app-configuration.md) to create a local config page.

App configuration pages are powered by PebbleKit JS. To find out more about PebbleKit JS,[_read the guide_](/guides/communication/using-pebblekit-js.md).

## Adding Configuration

For an app to be configurable, it must marked as 'configurable' in the app's [_`package.json`_](/guides/tools-and-resources/app-metadata.md)`capabilities` array. The presence of this value tells the mobile app to display a gear icon next to the app, allowing users to access the configuration page.

```
"capabilities": ["configurable"]
```

## Choosing Key Values

Since the config page must transmit the user's preferred options to the watchapp, the first step is to decide upon the [`AppMessage`](/docs/c/Foundation/AppMessage/ "AppMessage") keys defined in`package.json` that will be used to represent the chosen value for each option on the config page:

```
"messageKeys": ["BackgroundColor","ForegroundColor","SecondTick","Animations"]
```

These keys will automatically be available both in C on the watch and in PebbleKit JS on the phone.

Each of these keys will apply to the appropriate input element on the config page, with the user's chosen value transmitted to the watchapp's[`AppMessageInboxReceived`](/docs/c/Foundation/AppMessage/#AppMessageInboxReceived "AppMessageInboxReceived") handler once the page is submitted.

## Showing the Config Page

Once an app is marked as `configurable`, the PebbleKit JS component must implement `Pebble.openURL()` in the `showConfiguration` event handler in`index.js` to present the developer's HTML page when the user wants to configure the app:

```
Pebble.addEventListener('showConfiguration', function() {var url = 'http://example.com/config.html';Pebble.openURL(url);});
```

## Creating the Config Page

The basic structure of an HTML config page begins with a template HTML file:

> Note: This page will be plain and unstyled. CSS styling must be performed separately, and is not covered here.

```
\<!DOCTYPE html\>\<html\>\<head\>\<title\>Example Configuration\</title\>\</head\>\<body\>\<p\>This is an example HTML forms configuration page.\</p\>\</body\>\</html\>
```

The various UI elements the user will interact with to choose their preferences must be placed within the `body` tag, and will most likely take the form of HTML `input` elements. For example, a text input field for each of the example color options will look like the following:

```
\<inputid='background\_color\_input'type='text'value='#000000'\>Background Color\</input\>\<inputid='foreground\_color\_input'type='text'value='#000000'\>Foreground Color\</input\>
```

Other components include checkboxes, such as the two shown below for each of the example boolean options:

```
\<inputid='second\_tick\_checkbox'type='checkbox'\>Enable Second Ticks\</input\>\<inputid='animations\_checkbox'type='checkbox'\>Show Animations\</input\>
```

The final element should be the 'Save' button, used to trigger the sending of the user's preferences back to PebbleKit JS.

```
\<inputid='submit\_button'type='button'value='Save'\>
```

## Submitting Config Data

Once the 'Save' button is pressed, the values of all the input elements should be encoded and included in the return URL as shown below:

```
\<script\>// Get a handle to the button's HTML elementvar submitButton = document.getElementById('submit\_button');// Add a 'click' listenersubmitButton.addEventListener('click', function() {// Get the config data from the UI elementsvar backgroundColor = document.getElementById('background\_color\_input');var foregroundColor = document.getElementById('foreground\_color\_input');var secondTickCheckbox = document.getElementById('second\_tick\_checkbox');var animationsCheckbox = document.getElementById('animations\_checkbox');// Make a data object to be sent, coercing value types to integersvar options = {'background\_color': parseInt(backgroundColor.value, 16),'foreground\_color': parseInt(foregroundColor.value, 16),'second\_ticks': secondTickCheckbox.checked == 'true' ? 1 : 0,'animations': animationsCheckbox.checked == 'true' ? 1 : 0};// Determine the correct return URL (emulator vs real watch)function getQueryParam(variable, defaultValue) {var query = location.search.substring(1);var vars = query.split('&');for (var i = 0; i \< vars.length; i++) {var pair = vars[i].split('=');if (pair[0] === variable) {return decodeURIComponent(pair[1]);}}return defaultValue || false;}var return\_to = getQueryParam('return\_to', 'pebblejs://close#');// Encode and send the data when the page closesdocument.location = return\_to + encodeURIComponent(JSON.stringify(options));});\</script\>
```

> Note: Remember to use `encodeURIComponent()` and `decodeURIComponent()` to ensure the JSON data object is transmitted without error.

## Hosting the Config Page

In order for users to access your configuration page, it needs to be hosted online somewhere. One potential free service to host your configuration page is Github Pages:

[Github Pages](https://pages.github.com/) allow you to host your HTML, CSS and JavaScript files and directly access them from a special branch within your Github repo. This also has the added advantage of encouraging the use of version control.

## Relaying Data through PebbleKit JS

When the user submits the HTML form, the page will close and the result is passed to the `webviewclosed` event handler in the PebbleKit JS `index.js` file:

```
Pebble.addEventListener('webviewclosed', function(e) {// Decode the user's preferencesvar configData = JSON.parse(decodeURIComponent(e.response));}
```

The data from the config page should be converted to the appropriate keys and value types expected by the watchapp, and sent via [`AppMessage`](/docs/c/Foundation/AppMessage/ "AppMessage"):

```
// Send to the watchapp via AppMessagevar dict = {'BackgroundColor': configData.background\_color,'ForegroundColor': configData.foreground\_color,'SecondTick': configData.second\_ticks,'Animations': configData.animations};// Send to the watchappPebble.sendAppMessage(dict, function() {console.log('Config data sent successfully!');}, function(e) {console.log('Error sending config data!');});
```

## Receiving Config Data

Once the watchapp has called [`app_message_open()`](/docs/c/Foundation/AppMessage/#app_message_open "app\_message\_open") and registered an[`AppMessageInboxReceived`](/docs/c/Foundation/AppMessage/#AppMessageInboxReceived "AppMessageInboxReceived") handler, that handler will be called once the data has arrived on the watch. This occurs once the user has pressed the submit button.

To obtain the example keys and values shown in this guide, simply look for and read the keys as [`Tuple`](/docs/c/Foundation/Dictionary/#Tuple "Tuple") objects using the [`DictionaryIterator`](/docs/c/Foundation/Dictionary/#DictionaryIterator "DictionaryIterator") provided:

```
static void inbox\_received\_handler(DictionaryIterator \*iter, void \*context) {// Read color preferencesTuple \*bg\_color\_t = dict\_find(iter, MESSAGE\_KEY\_BackgroundColor);if(bg\_color\_t) {GColor bg\_color = GColorFromHEX(bg\_color\_t-\>value-\>int32);}Tuple \*fg\_color\_t = dict\_find(iter, MESSAGE\_KEY\_ForegroundColor);if(fg\_color\_t) {GColor fg\_color = GColorFromHEX(fg\_color\_t-\>value-\>int32);}// Read boolean preferencesTuple \*second\_tick\_t = dict\_find(iter, MESSAGE\_KEY\_SecondTick);if(second\_tick\_t) {bool second\_ticks = second\_tick\_t-\>value-\>int32 == 1;}Tuple \*animations\_t = dict\_find(iter, MESSAGE\_KEY\_Animations);if(animations\_t) {bool animations = animations\_t-\>value-\>int32 == 1;}// App should now update to take the user's preferences into accountreload\_config();}
```

Read the [_Communication_](/guides/communication.md) guides for more information about using the [`AppMessage`](/docs/c/Foundation/AppMessage/ "AppMessage") API.

If you're looking for a simpler option, we recommend using[_Clay for Pebble_](/guides/user-interfaces/app-configuration.md) instead.
