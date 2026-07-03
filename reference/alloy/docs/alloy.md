# Alloy // Pebble Developers
Alloy is a JavaScript framework for building Pebble apps, based on the [Moddable SDK](https://www.moddable.com/). Alloy provides developers a mix of standard Web APIs, standard Embedded JavaScript APIs from ECMA-419, and dedicated Pebble OS APIs. It allows you to write apps using modern JavaScript (ES2025, ES6++) with powerful UI frameworks and access to Pebble hardware features.

> **Platform Support**: Alloy currently supports Emery (Pebble Time 2) and Gabbro (Pebble Round 2).

Key Features
------------

*   **Modern JavaScript**: Write apps using ES modules, classes, async/await, and other modern JavaScript features
*   **Two UI Frameworks**: Choose between Piu (declarative, component-based) or Poco (procedural, low-level graphics)
*   **Hardware Access**: Full access to accelerometer, battery, buttons, compass, and other Pebble sensors
*   **Network Communication**: Built-in support for HTTP requests, WebSockets, and watch-phone messaging
*   **Persistent Storage**: Simple APIs for storing data locally using `localStorage`, key-value storage, or files

Getting Started
---------------

To create a new Alloy project:

```
$ pebble new-project --alloy my-app

```


This creates a new project with the standard Alloy structure:

```
my-app/
  src/
    embeddedjs/
      main.js           # Watch code (runs on Pebble)
    pkjs/
      index.js          # Phone code (for networking, location)
    c/
      mdbl.c            # C code as entry point for embeddedjs (usually no need to modify)
  resources/            # App resources (images, fonts)
  package.json          # App manifest

```


Alloy apps have two JavaScript environments: **embeddedjs** runs on the watch, while **pkjs** runs on the connected phone for network and location services.

Hello World
-----------

The simplest Alloy app:

```
console.log("Hello, Pebble!");

```


Guides
------

*   [**Advanced Networking**](https://developer.repebble.com/guides/alloy/advanced-networking/) - Low-level HTTP and WebSocket clients for advanced networking needs.
    
*   [**Animations**](https://developer.repebble.com/guides/alloy/animations/) - Create smooth animations using Timeline and easing functions.
    
*   [**App Messages**](https://developer.repebble.com/guides/alloy/app-messages/) - Send and receive messages between the watch and the phone.
    
*   [**Getting Started with Alloy**](https://developer.repebble.com/guides/alloy/getting-started/) - Learn how to create your first Alloy app for Pebble.
    
*   [**Networking**](https://developer.repebble.com/guides/alloy/networking/) - Make HTTP requests and use WebSockets via the phone proxy.
    
*   [**Piu UI Framework**](https://developer.repebble.com/guides/alloy/piu-guide/) - Build declarative user interfaces with the Piu framework.
    
*   [**Poco Graphics**](https://developer.repebble.com/guides/alloy/poco-guide/) - Low-level graphics rendering with the Poco framework.
    
*   [**Port (Custom Drawing)**](https://developer.repebble.com/guides/alloy/port-drawing/) - Combine Piu's declarative UI with custom drawing using Port.
    
*   [**Sensors and Input**](https://developer.repebble.com/guides/alloy/sensors-and-input/) - Access Pebble sensors and handle button input in Alloy apps.
    
*   [**Storage**](https://developer.repebble.com/guides/alloy/storage/) - Persist data between app launches using localStorage, key-value storage, or files.
    
*   [**Watchfaces**](https://developer.repebble.com/guides/alloy/watchfaces/) - Build custom watchfaces with Alloy.
    

Example Apps
------------

The [Moddable Pebble Examples](https://github.com/Moddable-OpenSource/pebble-examples) repository contains a collection of examples covering all aspects of Alloy development. Here's a categorized overview:

### Fundamentals


|Example        |Description                                 |
|---------------|--------------------------------------------|
|hellopebble    |"Hello, world" - the simplest starting point|
|hellotimer     |Using setTimeout                            |
|hellomodule    |Loading multiple modules                    |
|hellotypescript|TypeScript with the Pebble Button class     |


### Storage


|Example          |Description                                     |
|-----------------|------------------------------------------------|
|hellokeyvalue    |ECMA-419 Key-Value Storage for persistent data  |
|hellolocalstorage|Web standard localStorage for persisting strings|
|hellofiles       |File system storage                             |


### Sensors & Input


|Example           |Description                          |
|------------------|-------------------------------------|
|helloaccelerometer|Subscribing to accelerometer readings|
|hellobattery      |Battery and charging status          |
|hellolocation     |GPS location via phone               |
|hellobutton       |Pebble button events                 |


### Piu UI Framework


|Example                |Description                              |
|-----------------------|-----------------------------------------|
|hellopiu-text          |Dynamic text layout with different fonts |
|hellopiu-pebbletext    |Text using Pebble built-in fonts         |
|hellopiu-balls         |Classic bouncing balls demo              |
|hellopiu-coloredsquares|Drawing colored squares                  |
|hellopiu-gbitmap       |Pebble GBitmap PNG images as Piu textures|
|hellopiu-jsicon        |Moddable SDK bitmaps as Piu textures     |
|hellopiu-port          |Animated graph using Piu Port            |
|hellopiu-timeline      |Easing equations with Timeline animation |


### Piu Watchfaces


|Example  |Description                              |
|---------|-----------------------------------------|
|cupertino|Classic macOS watch cursor as a watchface|
|london   |Big Ben (color watches only)             |
|helsinki |Minimal design with per-model assets     |
|redmond  |Classic Windows clock                    |
|zurich   |Iconic Swiss railway clock               |


### Poco Renderer


|Example                 |Description                              |
|------------------------|-----------------------------------------|
|hellopoco-text          |Text rendering with Moddable SDK fonts   |
|hellopoco-pebbletext    |Text rendering with Pebble built-in fonts|
|hellopoco-gbitmap       |Rendering GBitmap resources              |
|hellopoco-pebblegraphics|Lines, round rectangles, and circles     |
|hellopoco-qrcode        |Dynamic QR code generation               |
|hellopoco-pdc           |Rendering PDC (SVG) images               |
|hellopoco-pdc-rotate    |Spinning a PDC image                     |
|hellopoco-pdc-scale     |Animated PDC scaling with easing         |
|hellopoco-pdc-sequence  |PDC image sequence animation             |
|hellowatchface          |Simple watchface app                     |


### Communication


|Example             |Description                              |
|--------------------|-----------------------------------------|
|hellomessage        |Watch-phone messaging via app_message    |
|helloconnected      |Phone connection status notifications    |
|hellofetch          |HTTP requests using the fetch() API      |
|hellohttpclient     |HTTP requests using ECMA-419 HTTP Client |
|hellowebsocket      |WebSocket using the Web standard API     |
|hellowebsocketclient|WebSocket using ECMA-419 WebSocket Client|


### Sensor Visualizations (Piu)


|Example|Description                             |
|-------|----------------------------------------|
|compass|Compass visualization (Emery only)      |
|gravity|Accelerometer visualization (Emery only)|


Additional Resources
--------------------

*   [Moddable SDK Documentation](https://www.moddable.com/documentation/readme) - Comprehensive documentation for Piu, Poco, and other modules
