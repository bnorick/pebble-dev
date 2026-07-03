# Pebble App Development
This monorepo focuses on app development for Pebble devices. There are two type of apps: apps written in C using the Pebble SDK and and apps written in JavaScript using the Alloy framework, based on Moddable.

## Alloy
Alloy is a JavaScript framework for building Pebble apps, based on the [Moddable SDK](https://www.moddable.com/). Alloy provides developers a mix of standard Web APIs, standard Embedded JavaScript APIs from ECMA-419, and dedicated Pebble OS APIs. It allows you to write apps using modern JavaScript (ES2025, ES6++) with powerful UI frameworks and access to Pebble hardware features.

> **Platform Support**: Alloy currently supports Emery (Pebble Time 2) and Gabbro (Pebble Round 2).


### Key Features
- **Modern JavaScript**: Write apps using ES modules, classes, async/await, and other modern JavaScript features
- **Two UI Frameworks**: Choose between Piu (declarative, component-based) or Poco (procedural, low-level graphics)
- **Hardware Access**: Full access to accelerometer, battery, buttons, compass, and other Pebble sensors
- **Network Communication**: Built-in support for HTTP requests, WebSockets, and watch-phone messaging
- **Persistent Storage**: Simple APIs for storing data locally using `localStorage`, key-value storage, or files

Alloy apps have two JavaScript environments: **embeddedjs** runs on the watch, while **pkjs** runs on the connected phone for network and location services.

#### Deep dives
- [**Advanced Networking**](./reference/alloy/docs/advanced-networking.md) - Low-level HTTP and WebSocket clients for advanced networking needs.
- [**Animations**](./reference/alloy/docs/animations.md) - Create smooth animations using Timeline and easing functions.
- [**App Messages**](./reference/alloy/docs/app-messages.md) - Send and receive messages between the watch and the phone.
- [**Getting Started with Alloy**](./reference/alloy/docs/getting-started.md) - Learn how to create your first Alloy app for Pebble.
- [**Networking**](./reference/alloy/docs/networking.md) - Make HTTP requests and use WebSockets via the phone proxy.
- [**Piu UI Framework**](./reference/alloy/docs/piu-guide.md) - Build declarative user interfaces with the Piu framework.
- [**Poco Graphics**](./reference/alloy/docs/poco-guide.md) - Low-level graphics rendering with the Poco framework.
- [**Port (Custom Drawing)**](./reference/alloy/docs/port-drawing.md) - Combine Piu's declarative UI with custom drawing using Port.
- [**Sensors and Input**](./reference/alloy/docs/sensors-and-input.md) - Access Pebble sensors and handle button input in Alloy apps.
- [**Storage**](./reference/alloy/docs/storage.md) - Persist data between app launches using localStorage, key-value storage, or files.
- [**Watchfaces**](./reference/alloy/docs/watchfaces.md) - Build custom watchfaces with Alloy.


#### Example Apps
Example apps exist in the [Moddable Pebble Examples](https://github.com/Moddable-OpenSource/pebble-examples) repository, which contains a collection of examples covering all aspects of Alloy development. The repository is available locally at [reference/alloy/pebble-examples](./reference/alloy/pebble-examples/).

Only refer to these example apps if the deep dives don't cover enough detail to understand a particular topic in your implementation.

Here's a categorized overview:

##### Fundamentals
|Example        |Description                                 |
|---------------|--------------------------------------------|
|hellopebble    |"Hello, world" - the simplest starting point|
|hellotimer     |Using setTimeout                            |
|hellomodule    |Loading multiple modules                    |
|hellotypescript|TypeScript with the Pebble Button class     |


##### Storage
|Example          |Description                                     |
|-----------------|------------------------------------------------|
|hellokeyvalue    |ECMA-419 Key-Value Storage for persistent data  |
|hellolocalstorage|Web standard localStorage for persisting strings|
|hellofiles       |File system storage                             |


##### Sensors & Input
|Example           |Description                          |
|------------------|-------------------------------------|
|helloaccelerometer|Subscribing to accelerometer readings|
|hellobattery      |Battery and charging status          |
|hellolocation     |GPS location via phone               |
|hellobutton       |Pebble button events                 |


##### Piu UI Framework
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


##### Piu Watchfaces
|Example  |Description                              |
|---------|-----------------------------------------|
|cupertino|Classic macOS watch cursor as a watchface|
|london   |Big Ben (color watches only)             |
|helsinki |Minimal design with per-model assets     |
|redmond  |Classic Windows clock                    |
|zurich   |Iconic Swiss railway clock               |


##### Poco Renderer
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


##### Communication
|Example             |Description                              |
|--------------------|-----------------------------------------|
|hellomessage        |Watch-phone messaging via app_message    |
|helloconnected      |Phone connection status notifications    |
|hellofetch          |HTTP requests using the fetch() API      |
|hellohttpclient     |HTTP requests using ECMA-419 HTTP Client |
|hellowebsocket      |WebSocket using the Web standard API     |
|hellowebsocketclient|WebSocket using ECMA-419 WebSocket Client|


##### Sensor Visualizations (Piu)
|Example|Description                             |
|-------|----------------------------------------|
|compass|Compass visualization (Emery only)      |
|gravity|Accelerometer visualization (Emery only)|


#### Additional Resources
*   [Moddable SDK Documentation](https://www.moddable.com/documentation/readme) - Comprehensive documentation for Piu, Poco, and other modules


## Pebble SDK
Details on the Pebble SDK and its use from C can be found in [reference/c/docs](./reference/c/docs/), where there are three deep dives:
- [**Animation Patterns**](./reference/c/docs/animation-patterns.md) - A collection of common animation patterns.
- [**Drawing Guide**](./reference/c/docs/drawing-guide.md) - A guide to drawing.
- [**API Reference**](./reference/c/docs/pebble-api-reference.md) - A reference for the Pebble SDK.