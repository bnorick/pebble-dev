# Adding Weather with Open-Meteo

Source: https://developer.repebble.com/tutorials/watchface-tutorial/part4/

# Adding Weather with Open-Meteo

This page contains some instructions that are different if you're using CloudPebble or if you're using the SDK locally on your computer.

Select whether you're using CloudPebble or the SDK below to show the relevant instructions!

[![](/assets/images/sdk/cloud.svg)
#### CloudPebble
](javascript:void();)[![](/assets/images/sdk/sdk-box.svg)
#### SDK
](javascript:void();)

![](/assets/images/sdk/cloud.svg) Showing instructions for CloudPebble. [Not using CloudPebble?](javascript:%20void();)

![](/assets/images/sdk/sdk-box.svg) Showing instructions for the SDK. [Using CloudPebble?](javascript:%20void();)

Up until now, everything in our watchface has been running entirely on the watch. In this part we take a big step: communicating with the phone to fetch live weather data from the web.

We will use [PebbleKit JS](/guides/communication/using-pebblekit-js.md) to run JavaScript on the connected phone, fetch weather data from the free[Open-Meteo](https://open-meteo.com) API (no API key needed!), and send it to the watch using [`AppMessage`](/docs/c/Foundation/AppMessage/ "AppMessage").

This section continues from[_Part 3_](/tutorials/watchface-tutorial/part3.md).

By the end, our watchface will show the current temperature and weather conditions:

#### aplite

#### basalt

#### chalk

#### diorite

#### emery

#### gabbro

 ![](/assets/images/tutorials/watchface-tutorial/part4~aplite.png)

 ![](/assets/images/tutorials/watchface-tutorial/part4~basalt.png)

 ![](/assets/images/tutorials/watchface-tutorial/part4~chalk.png)

 ![](/assets/images/tutorials/watchface-tutorial/part4~diorite.png)

 ![](/assets/images/tutorials/watchface-tutorial/part4~emery.png)

 ![](/assets/images/tutorials/watchface-tutorial/part4~gabbro.png)

## How PebbleKit JS Works

Pebble watches cannot access the internet directly. Instead, they communicate with a JavaScript environment called **PebbleKit JS** (PKJS) that runs on the connected phone. Your JS code can make HTTP requests, access GPS, and send data back to the watch using [`AppMessage`](/docs/c/Foundation/AppMessage/ "AppMessage").

```
┌─────────────┐ ┌──────────────────┐ ┌──────────────┐
│ Watch │ │ Phone (PKJS) │ │ Internet │
│ │ │ │ │ │
│ C code ──┼── msg ──>│ index.js ──┼── HTTP ─>│ API server │
│ │ │ │ │ │
│ <── msg ───┼──────────┤ <── response ───┼──────────┤ │
│ │ │ │ │ │
│ AppMessage │ │ geolocation │ │ │
│ request ──┼── msg ──>│ → GPS lookup │ │ │
│ <── msg ───┼──────────┤ → sends coords │ │ │
└─────────────┘ └──────────────────┘ └──────────────┘
```

The flow for weather is:

1. The watch sends an [`AppMessage`](/docs/c/Foundation/AppMessage/ "AppMessage") to the phone requesting weather.
2. PKJS uses `navigator.geolocation` to get GPS coordinates.
3. PKJS makes an HTTP request to a weather API.
4. PKJS sends the result back to the watch via [`AppMessage`](/docs/c/Foundation/AppMessage/ "AppMessage").
5. The watch receives the message and updates the display.

All communication between watch and phone uses [`AppMessage`](/docs/c/Foundation/AppMessage/ "AppMessage") - a key-value dictionary system. You define the keys in `package.json` and they become constants in both C and JS.

## Preparing the Layout

We need a new [`TextLayer`](/docs/c/User_Interface/Layers/TextLayer/ "TextLayer") for the weather data. Add the declaration at the top of the file:

```
static TextLayer \*s\_weather\_layer;
```

Create it in `main_window_load()`. We place it at the bottom of the screen so it stays out of the way of the centered time and date block:

```
// Create weather TextLayer - aligned to the bottom of the screenint weather\_y = bounds.size.h - PBL\_IF\_ROUND\_ELSE(40, 30);s\_weather\_layer = text\_layer\_create(GRect(0, weather\_y, bounds.size.w, 25));text\_layer\_set\_background\_color(s\_weather\_layer, GColorClear);text\_layer\_set\_text\_color(s\_weather\_layer, GColorWhite);text\_layer\_set\_font(s\_weather\_layer, fonts\_get\_system\_font(FONT\_KEY\_GOTHIC\_18));text\_layer\_set\_text\_alignment(s\_weather\_layer, GTextAlignmentCenter);text\_layer\_set\_text(s\_weather\_layer, "Loading...");
```

Add it as a child layer and destroy it in `main_window_unload()`:

```
// In main\_window\_load()layer\_add\_child(window\_layer, text\_layer\_get\_layer(s\_weather\_layer));// In main\_window\_unload()text\_layer\_destroy(s\_weather\_layer);
```

## Setting Up AppMessage

[`AppMessage`](/docs/c/Foundation/AppMessage/ "AppMessage") is the communication channel between the watch and phone. Messages are key-value dictionaries.

In CloudPebble, go to **Settings** on the left sidebar. Check **Uses Location** to allow the phone to access GPS. Then scroll down to **PebbleKit JS Message Keys** and add the following keys: `TEMPERATURE`, `CONDITIONS`, and`REQUEST_WEATHER`.

First, define the message keys in `package.json`. Add these to the `pebble`section:

```
"capabilities": ["location"],"messageKeys": ["TEMPERATURE","CONDITIONS","REQUEST\_WEATHER"]
```

The `location` capability allows the phone to access GPS.

The message keys become `MESSAGE_KEY_TEMPERATURE`, `MESSAGE_KEY_CONDITIONS`, and`MESSAGE_KEY_REQUEST_WEATHER` constants in C.

Now create the AppMessage callbacks in your C file. These go above `init()`:

```
static void inbox\_received\_callback(DictionaryIterator \*iterator, void \*context) {}static void inbox\_dropped\_callback(AppMessageResult reason, void \*context) {APP\_LOG(APP\_LOG\_LEVEL\_ERROR, "Message dropped!");}static void outbox\_failed\_callback(DictionaryIterator \*iterator, AppMessageResult reason, void \*context) {APP\_LOG(APP\_LOG\_LEVEL\_ERROR, "Outbox send failed!");}static void outbox\_sent\_callback(DictionaryIterator \*iterator, void \*context) {APP\_LOG(APP\_LOG\_LEVEL\_INFO, "Outbox send success!");}
```

Register the callbacks and open AppMessage in `init()`. It is important to register callbacks _before_ opening AppMessage so no messages are missed:

```
// Register AppMessage callbacksapp\_message\_register\_inbox\_received(inbox\_received\_callback);app\_message\_register\_inbox\_dropped(inbox\_dropped\_callback);app\_message\_register\_outbox\_failed(outbox\_failed\_callback);app\_message\_register\_outbox\_sent(outbox\_sent\_callback);// Open AppMessageconst int inbox\_size = 128;const int outbox\_size = 128;app\_message\_open(inbox\_size, outbox\_size);
```

## Writing the JavaScript

Click **Add New** next to **Source Files** in the left sidebar, select **JavaScript file** , and name it (e.g., `weather.js`). This code runs on the phone whenever the watchface is open.

Create a new file at `src/pkjs/index.js`. This code runs on the phone whenever the watchface is open.

Start with a helper function for making HTTP requests:

```
var xhrRequest = function (url, type, callback) {var xhr = new XMLHttpRequest();xhr.onload = function () {callback(this.responseText);};xhr.open(type, url);xhr.send();};
```

Next, a function to convert Open-Meteo weather codes to readable strings:

```
function weatherCodeToCondition(code) {if (code === 0) return 'Clear';if (code \<= 3) return 'Cloudy';if (code \<= 48) return 'Fog';if (code \<= 55) return 'Drizzle';if (code \<= 57) return 'Fz. Drizzle';if (code \<= 65) return 'Rain';if (code \<= 67) return 'Fz. Rain';if (code \<= 75) return 'Snow';if (code \<= 77) return 'Snow Grains';if (code \<= 82) return 'Showers';if (code \<= 86) return 'Snow Shwrs';if (code === 95) return 'T-Storm';if (code \<= 99) return 'T-Storm';return 'Unknown';}
```

Now the weather fetching logic. We first get the user's location, then call the Open-Meteo API with those coordinates:

```
function locationSuccess(pos) {var url = 'https://api.open-meteo.com/v1/forecast?' +'latitude=' + pos.coords.latitude +'&longitude=' + pos.coords.longitude +'&current=temperature\_2m,weather\_code';xhrRequest(url, 'GET',function(responseText) {var json = JSON.parse(responseText);var temperature = Math.round(json.current.temperature\_2m);var conditions = weatherCodeToCondition(json.current.weather\_code);var dictionary = {'TEMPERATURE': temperature,'CONDITIONS': conditions};Pebble.sendAppMessage(dictionary,function(e) { console.log('Weather info sent!'); },function(e) { console.log('Error sending weather info!'); });});}function locationError(err) {console.log('Error requesting location!');}function getWeather() {navigator.geolocation.getCurrentPosition(locationSuccess,locationError,{ timeout: 15000, maximumAge: 60000 });}
```

> **Why Open-Meteo?** Unlike many weather APIs, Open-Meteo is completely free and requires no API key. The URL is simple and the response is clean JSON.

Finally, set up the event listeners:

```
Pebble.addEventListener('ready',function(e) {console.log('PebbleKit JS ready!');getWeather();});Pebble.addEventListener('appmessage',function(e) {console.log('AppMessage received!');if (e.payload['REQUEST\_WEATHER']) {getWeather();}});
```

When the JS environment starts (`ready`), we fetch weather immediately. The`appmessage` listener checks for the `REQUEST_WEATHER` key before refreshing, so it only fetches weather when the watch explicitly asks for it.

## Processing Weather Data on the Watch

Back in the C file, fill in `inbox_received_callback()` to extract the weather data and display it:

```
static void inbox\_received\_callback(DictionaryIterator \*iterator, void \*context) {Tuple \*temp\_tuple = dict\_find(iterator, MESSAGE\_KEY\_TEMPERATURE);Tuple \*conditions\_tuple = dict\_find(iterator, MESSAGE\_KEY\_CONDITIONS);if (temp\_tuple && conditions\_tuple) {static char temperature\_buffer[8];static char conditions\_buffer[32];static char weather\_layer\_buffer[42];snprintf(temperature\_buffer, sizeof(temperature\_buffer), "%d°C", (int)temp\_tuple-\>value-\>int32);snprintf(conditions\_buffer, sizeof(conditions\_buffer), "%s", conditions\_tuple-\>value-\>cstring);snprintf(weather\_layer\_buffer, sizeof(weather\_layer\_buffer), "%s %s", temperature\_buffer, conditions\_buffer);text\_layer\_set\_text(s\_weather\_layer, weather\_layer\_buffer);}}
```

We use [`dict_find()`](/docs/c/Foundation/Dictionary/#dict_find "dict\_find") to look up each key. Numbers arrive as `int32`, strings as `cstring`.

## Automatic Refresh

To keep the weather current, trigger a refresh every 30 minutes from the tick handler:

```
static void tick\_handler(struct tm \*tick\_time, TimeUnits units\_changed) {update\_time();// Get weather update every 30 minutesif (tick\_time-\>tm\_min % 30 == 0) {DictionaryIterator \*iter;app\_message\_outbox\_begin(&iter);dict\_write\_uint8(iter, MESSAGE\_KEY\_REQUEST\_WEATHER, 1);app\_message\_outbox\_send();}}
```

This sends an AppMessage with the `REQUEST_WEATHER` key to the phone. The JS`appmessage` listener sees this key and calls `getWeather()`.

## Conclusion

In this part we learned how to:

1. Set up [`AppMessage`](/docs/c/Foundation/AppMessage/ "AppMessage") for watch-phone communication.
2. Write PebbleKit JS to run on the phone.
3. Use `navigator.geolocation` to get the user's location.
4. Fetch data from a web API using `XMLHttpRequest`.
5. Parse a JSON response and send data to the watch.
6. Display received data in a [`TextLayer`](/docs/c/User_Interface/Layers/TextLayer/ "TextLayer").
7. Set up automatic refresh via the tick handler.

Your watchface now shows live weather data! Check your code against[the source for this part](https://github.com/coredevices/c-watchface-tutorial/tree/main/part4).

## What's Next?

In the next part we will add Timeline Peek support, so the watchface adapts gracefully when the system overlays part of the screen.

[Go to Part 5 →](/tutorials/watchface-tutorial/part5.md)
