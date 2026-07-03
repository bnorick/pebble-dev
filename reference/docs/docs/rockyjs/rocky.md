# rocky

Source: https://developer.repebble.com/docs/rockyjs/rocky/

Provides an interface for interacting with application context and events. Developers can access the Rocky object with the following line of code:

`var rocky = require('rocky');`

### Methods

 rocky.on(type, callback) 

Attaches an event handler to the specified events. You may subscribe with multiple handlers, but at present there is no way to unsubscribe.

`rocky.on('minutechange', function() {...});`

#### 

Event Type Options

Possible values:

- `draw` - Provide a [RockyDrawCallback](#RockyDrawCallback) as the callback. The draw event is being emitted after each call to [requestDraw](#requestDraw) but at most once for each screen update, even if [requestDraw](#requestDraw) is called frequently the 'draw' event might also fire at other meaningful times (e.g. upon launch).

- `secondchange` - Provide a [RockyTickCallback](#RockyTickCallback) as the callback. The secondchange event is emitted every time the clock's second changes.

- `minutechange` - Provide a [RockyTickCallback](#RockyTickCallback) as the callback. The minutechange event is emitted every time the clock's minute changes.

- `hourchange` - Provide a [RockyTickCallback](#RockyTickCallback) as the callback. The hourchange event is emitted every time the clock's hour changes.

- `daychange` - Provide a [RockyTickCallback](#RockyTickCallback) as the callback. The daychange event is emitted every time the clock's day changes.

- `memorypressure` - Provides a [RockyMemoryPressureCallback](#RockyMemoryPressureCallback). The event is emitted every time there is a notable change in available system memory. You can see an example implementation of memory pressure handling [here](https://github.com/pebble-examples/rocky-memorypressure).

- `message` - Provide a [RockyMessageCallback](#RockyMessageCallback) as the callback. The message event is emitted every time the application receives a [postMessage](#postMessage) from the mobile companion.

- `postmessageconnected` - Provide a [RockyPostMessageConnectedCallback](#RockyPostMessageConnectedCallback) as the callback. The event may be emitted immediately upon subscription, if the subsystem is already connected. It is also emitted when connectivity is established.

- `postmessagedisconnected` - Provide a [RockyPostMessageDisconnectedCallback](#RockyPostMessageDisconnectedCallback) as the callback. The event may be emitted immediately upon subscription, if the subsystem is already disconnected. It is also emitted when connectivity is lost.

- `postmessageerror` - Provide a [RockyPostMessageErrorCallback](#RockyPostMessageErrorCallback) as the callback. The event is emitted when a transmission error occurrs. The type of error is not provided, but the message has not been delivered.

#### Parameters
String type

The event being subscribed to.

Function callback

A callback function that will be executed when the event occurs. See below for more details.

 rocky.addEventListener(type, callback) 

Attaches an event handler to the specified events. Synonymous with [rocky.on()](#on).

`rocky.addEventListener(type, callback);`

#### Parameters
String type

The event being subscribed to.

Function callback

A callback function that will be executed when the event occurs. See below for more details.

 rocky.removeEventListener(type, callback) 

Remove an existing event listener previously registered with [rocky.on()](#on) or [rocky.addEventListener()](#addEventListener).

#### Parameters
String type

The type of the event listener to be removed. See [rocky.on()](#on) for a list of available event types.

Function callback

The existing developer-defined function that was previously registered.

 rocky.off(type, callback) 

Remove an existing event handler from the specified events. Synonymous with [rocky.removeEventListener()](#removeEventListener).

`rocky.off(type, callback);`

#### Parameters
String type

The type of the event listener to be removed. See [rocky.on()](#on) for a list of available event types.

Function callback

The existing developer-defined function that was previously registered.

 rocky.postMessage(data) 

Sends a message to the mobile companion component. Please be aware that messages should be kept concise. Each message is queued, so `postMessage()` can be called multiple times immediately. If there is a momentary loss of connectivity, queued messages may still be delivered, or automatically removed from the queue after a few seconds of failed connectivity. Any transmission failures, or out of memory errors will be raised via the `postmessageerror` event.

`rocky.postMessage({cmd: 'fetch'});`

#### Parameters
Object data

An object containing the data to deliver to the mobile device. This will be received in the `data` field of the `event` delivered to the `on('message', ...)` handler.

 rocky.requestDraw() 

Flags the canvas (display) as requiring a redraw. Invoking this method will cause the [draw event](#on) to be emitted. Only 1 draw event will occur, regardless of how many times the redraw is requested before the next draw event.

`rocky.on('secondchange', function(e) {  rocky.requestDraw();});`

### Members

 rocky.watchInfo

A [WatchInfo](#WatchInfo) object containing information about the connected Pebble smartwatch.

`console.log(rocky.watchInfo.model);> pebble_2_hr_lime`

 rocky.userPreferences

A [UserPreferences](#UserPreferences) object access to user related settings from the currently connected Pebble smartwatch.

`console.log(rocky.userPreferences.contentSize);> medium`

### Typedefs

 rocky.RockyPostMessageErrorCallback(event) 

The callback function signature to be used with the `postmessageerror`[event](#on).

#### Parameters
Object event

An object containing information about the event:

- `type` - The type of event which was triggered.

- `data` - The data failed to send within the message.

 rocky.RockyPostMessageConnectedCallback(event) 

The callback function signature to be used with the `postmessageconnected`[event](#on).

#### Parameters
Object event

An object containing information about the event:

- `type` - The type of event which was triggered.

WatchInfo

Provides information about the currently connected Pebble smartwatch.

#### Properties
 model

The name of the Pebble model. (e.g. pebble\_time\_round\_silver\_20mm)

 platform

The name of the Pebble platform. (e.g. basalt)

 language

Not available yet.

 firmware

An object with the following fields:

- `major` - The major version of the smartwatch's firmware.

- `minor` - The minor version of the smartwatch's firmware.

- `patch` - The patch version of the smartwatch's firmware.

- `suffix` - The suffix of the smartwatch's firmware. (e.g. beta3)

 rocky.RockyMemoryPressureCallback(event) 

The callback function signature to be used with the `memorypressure`[event](#on).

#### Parameters
Object event

An object containing information about the event:

- `level` (String) - The current level of memory pressure.

 rocky.RockyPostMessageDisconnectedCallback(event) 

The callback function signature to be used with the `postmessagedisconnected`[event](#on).

#### Parameters
Object event

An object containing information about the event:

- `type` - The type of event which was triggered.

UserPreferences

Provides access to user related settings from the currently connected Pebble smartwatch. The size itself will vary between platforms, see the [ContentSize guide](/guides/user-interfaces/content-size.md) for more information.

#### Properties
 contentSize

Pebble \> System \> Notifications \> Text Size:

- `small` - Not available on Emery.

- `medium` - The default setting.

- `large` - The default setting on Emery.

- `x-large` - Only available on Emery.

 rocky.RockyDrawCallback(event) 

The callback function signature to be used with the draw [event](#on).

#### Parameters
Object event

An object containing information about the event:

- `context` - A [CanvasRenderingContext2D](/docs/rockyjs/CanvasRenderingContext2D.md) object that can be used to draw information on the disply.

 rocky.RockyMessageCallback(event) 

The callback function signature to be used with the `message`[event](#on).

#### Parameters
Object event

An object containing information about the event:

- `type` - The type of event which was triggered.

- `data` - The data sent within the message.

 rocky.RockyTickCallback(event) 

The callback function signature to be used with the `secondchange`, `minutechange`, `hourchange` and `daychange` [events](#on).

In addition to firing these tick events at the appropriate time change, they are also emitted when the application starts.

#### Parameters
Object event

An object containing information about the event:

- `date` - A JavaScript [date](http://www.w3schools.com/jsref/jsref_obj_date.asp) object representing the current time.
