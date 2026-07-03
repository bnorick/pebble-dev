# Pebble

Source: https://developer.repebble.com/docs/pebblekit-js/Pebble/

The Pebble namespace is where all of the Pebble specific methods and properties exist. This class contains methods belonging to PebbleKit JS and allows bi-directional communication with a C or JavaScript watchapp, as well as managing the user's timeline subscriptions, creating AppGlance slices and obtaining information about the currently connected watch.

### Methods

 Pebble.addEventListener(type, callback) 

Adds a listener for PebbleKit JS events, such as when an `AppMessage` is received or the configuration view is opened or closed.

#### 

Event Type Options

Possible values:

- `ready` - The watchapp has been launched and the PebbleKit JS component is now ready to receive events.

- `appmessage` - The watch sent an `AppMessage` to PebbleKit JS. The AppMessage `Dictionary` is contained in the payload property (i.e: `event.payload`). The payload consists of key-value pairs, where the keys are strings containing integers (e.g: "0"), or aliases for keys defined in package.json (e.g: "KEY\_EXAMPLE"). Values should be integers, strings or byte arrays (arrays of characters). This event is not available to [Rocky.js](/docs/rockyjs.md) applications, and attempting to register it will throw an exception.

- `showConfiguration` - The user has requested the app's configuration webview to be displayed. This can occur either upon the app's initial install or when the user taps 'Settings' in the 'My Pebble' view within the phone app.

- `webviewclosed` - The configuration webview was closed by the user. If the webview had a response, it will be contained in the response property (i.e: `event.response`). This response can be used to feed back user preferences to the watchapp.

- `message` - Provide a [PostMessageCallback](#PostMessageCallback) as the callback. The message event is emitted every time PebbleKit JS receives a [postMessage](#postMessage) from the [Rocky.js](/docs/rockyjs.md) application. The payload contains a simple JavaScript object. (i.e. `event.data`). This event type can only be used with [Rocky.js](/docs/rockyjs.md) applications.

- `postmessageconnected` - Provide a [PostMessageConnectedCallback](#PostMessageConnectedCallback) as the callback. The event may be emitted immediately upon subscription, if the subsystem is already connected. It is also emitted when connectivity is established. This event type can only be used with [Rocky.js](/docs/rockyjs.md) applications.

- `postmessagedisconnected` - Provide a [PostMessageDisconnectedCallback](#PostMessageDisconnectedCallback) as the callback. The event may be emitted immediately upon subscription, if the subsystem is already disconnected. It is also emitted when connectivity is lost. This event type can only be used with [Rocky.js](/docs/rockyjs.md) applications.

- `postmessageerror` - Provide a [PostMessageErrorCallback](#PostMessageErrorCallback) as the callback. The event is emitted when a transmission error occurrs. Your message has not been delivered. The type of error is not provided. This event type can only be used with [Rocky.js](/docs/rockyjs.md) applications.

#### Parameters
String type

The type of the event, from the list described above.

EventCallback callback

The developer defined [EventCallback](#EventCallback) to receive any events of the type specified that occur.

 Pebble.on(type, callback) 

Attaches an event handler to the specified events. Synonymous with [Pebble.addEventListener()](#addEventListener). Only applicable to [Rocky.js](/docs/rockyjs.md) applications.

`Pebble.on(type, callback);`

#### Parameters
String type

The type of the event, from the list described above.

EventCallback callback

The developer defined [EventCallback](#EventCallback) to receive any events of the type specified that occur.

 Pebble.removeEventListener(type, callback) 

Remove an existing event listener previously registered with [Pebble.addEventListener()](#addEventListener) or [Pebble.on()](#on).

#### Parameters
String type

The type of the event listener to be removed. See [Pebble.addEventListener()](#addEventListener) for a list of available event types.

Function callback

The existing developer-defined function that was previously registered.

 Pebble.off(type, callback) 

Remove an existing event handler from the specified events. Synonymous with [Pebble.removeEventListener()](#removeEventListener). Only applicable to [Rocky.js](/docs/rockyjs.md) applications.

`Pebble.off(type, callback);`

#### Parameters
String type

The type of the event listener to be removed. See [Pebble.addEventListener()](#addEventListener) for a list of available types.

Function callback

The existing developer-defined function that was previously registered.

 Pebble.showSimpleNotificationOnPebble(title, body) 

Show a simple modal notification on the connected watch.

#### Parameters
String title

The title of the notification

String body

The main content of the notification

 Pebble.sendAppMessage(data, onSuccess, onFailure) 

Send an AppMessage to the app running on the watch. Messages should be in the form of JSON objects containing key-value pairs. See Pebble.sendAppMessage() for valid key and value data types. `Pebble.sendAppMessage = function(data, onSuccess, onFailure) { };` Please note that `sendAppMessage` is `undefined` in [Rocky.js](/docs/rockyjs.md) applications, see [postMessage](#postMessage) instead.

#### Parameters
Object data

A JSON object containing key-value pairs to send to the watch. Values in arrays that are greater then 255 will be mod 255 before sending.

AppMessageAckCallback onSuccess

A developer-defined [AppMessageAckCallback](#AppMessageAckCallback) callback to run if the watch acknowledges (ACK) this message.

AppMessageOnFailure onFailure

A developer-defined [AppMessageNackCallback](#AppMessageNackCallback) callback to run if the watch does NOT acknowledge (NACK) this message.

#### Returns

The transaction id for this message

 Pebble.postMessage(data) 

Sends a message to the [Rocky.js](/docs/rockyjs.md) component. Please be aware that messages should be kept concise. Each message is queued, so `postMessage()` can be called multiple times immediately. If there is a momentary loss of connectivity, queued messages may still be delivered, or automatically removed from the queue after a few seconds of failed connectivity. Any transmission failures, or out of memory errors will be raised via the `postmessageerror` event.

`Pebble.postMessage({temperature: 30, conditions: 'Sunny'});`

#### Parameters
Object data

A [PostMessageCallback](#PostMessageCallback) containing the data to deliver to the watch. This will be received in the `data` field of the `type` delivered to the `on('message', ...)` handler.

 Pebble.getTimelineToken(onSuccess, onFailure) 

Get the user's timeline token for this app. This is a string and is unique per user per app. Note: In order for timeline tokens to be available, the app must be submitted to the Pebble appstore, but does not need to be public. Read more in the [timeline guides](/guides/pebble-timeline/timeline-js.md).

#### Parameters
TimelineTokenCallback onSuccess

A developer-defined [TimelineTokenCallback](#TimelineTokenCallback) callback to handle a successful attempt to get the timeline token.

Function onFailure

A developer-defined callback to handle a failed attempt to get the timeline token.

 Pebble.timelineSubscribe(topic, onSuccess, onFailure) 

Subscribe the user to a timeline topic for your app. This can be used to filter the different pins a user could receive according to their preferences, as well as maintain groups of users.

#### Parameters
String topic

The desired topic to be subscribed to. Users will receive all pins pushed to this topic.

Function onSuccess

A developer-defined callback to handle a successful subscription attempt.

Function onFailure

A developer-defined callback to handle a failed subscription attempt.

 Pebble.timelineUnsubscribe(topic, onSuccess, onFailure) 

Unsubscribe the user from a timeline topic for your app. Once unsubscribed, the user will no longer receive any pins pushed to this topic.

#### Parameters
String topic

The desired topic to be unsubscribed from.

Function onSuccess

A developer-defined callback to handle a successful unsubscription attempt.

Function onFailure

A developer-defined callback to handle a failed unsubscription attempt.

 Pebble.timelineSubscriptions(onSuccess, onFailure) 

Obtain a list of topics that the user is currently subscribed to. The length of the list should be checked to determine whether the user is subscribed to at least one topic.

`Pebble.timelineSubscriptions(function(topics) { console.log(topics); }, function() { console.log('error'); } );`

#### Parameters
TimelineTopicsCallback onSuccess

The developer-defined function to process the retuned list of topic strings.

Function onFailure

The developer-defined function to gracefully handle any errors in obtaining the user's subscriptions.

 Pebble.getActiveWatchInfo() 

Obtain an object containing information on the currently connected Pebble smartwatch.

#### Returns

A [WatchInfo](#WatchInfo) object detailing the currently connected Pebble watch.

 Pebble.getAccountToken() 

Returns a unique account token that is associated with the Pebble account of the current user.

#### Returns

A string that is guaranteed to be identical across devices if the user owns several Pebble or several mobile devices. From the developer's perspective, the account token of a user is identical across platforms and across all the developer's watchapps. If the user is not logged in, this function will return an empty string ('').

 Pebble.getWatchToken() 

Returns a a unique token that can be used to identify a Pebble device.

#### Returns

A string that is is guaranteed to be identical for each Pebble device for the same app across different mobile devices. The token is unique to your app and cannot be used to track Pebble devices across applications.

 Pebble.appGlanceReload(appGlanceSlices, onSuccess, onFailure) 

Triggers a reload of the app glance which first clears any existing slices and then adds the provided slices.

#### Parameters
AppGlanceSlice appGlanceSlices

[AppGlanceSlice](#AppGlanceSlice) JSON objects to add to the app glance.

AppGlanceReloadSuccessCallback onSuccess

The developer-defined callback which is called if the reload operation succeeds.

AppGlanceReloadFailureCallback onFailure

The developer-defined callback which is called if the reload operation fails.

 Pebble.openURL(url) 

When an app is marked as configurable, the PebbleKit JS component must implement `Pebble.openURL()` in the `showConfiguration` event handler. The Pebble mobile app will launch the supplied URL to allow the user to configure the watchapp or watchface. See the [App Configuration guide](/guides/user-interfaces/app-configuration-static.md).

#### Parameters
String url

The URL of the static configuration page.

### Typedefs

 Pebble.TimelineTopicsCallback(List) 

Called when the user's list of subscriptions is available for processing by the developer.

#### Parameters
 List

of topic strings that the user is subscribed to

 Pebble.AppGlanceReloadFailureCallback(AppGlanceSlices) 

Called when AppGlanceReload has failed.

#### Parameters
AppGlanceSlice AppGlanceSlices

An [AppGlanceSlice](#AppGlanceSlice) object containing the app glance slices.

 Pebble.AppMessageAckCallback(data) 

Called when an AppMessage is acknowledged by the watch.

#### Parameters
Object data

An object containing the callback data. This contains the `transactionId` which is the transaction ID of the message.

 Pebble.AppMessageNackCallback(data, error) 

Called when an AppMessage is not acknowledged by the watch.

#### Parameters
Object data

An object containing the callback data. This contains the `transactionId` which is the transaction ID of the message

String error

The error message

 Pebble.EventCallback(event) 

Called when an event of any type previously registered occurs. The parameters are different depending on the type of event, shown in brackets for each parameter listed here.

#### Parameters
Object event

An object containing the event information, including:

- `type` - The type of event fired, from the list in the description of [Pebble.addEventListener()](#addEventListener).

- `payload` - The dictionary sent over `AppMessage` consisting of key-value pairs. 

- `response` - The contents of the URL navigated to when the configuration page was closed, after the anchor. This may be encoded, which will require use of decodeURIComponent() before reading as an object. 

 Pebble.TimelineTokenCallback(token) 

Called when the user's timeline token is available.

#### Parameters
String token

The user's token.

 Pebble.AppGlanceReloadSuccessCallback(AppGlanceSlices) 

Called when AppGlanceReload is successful.

#### Parameters
AppGlanceSlice AppGlanceSlices

An [AppGlanceSlice](#AppGlanceSlice) object containing the app glance slices.

 Pebble.PostMessageCallback(event) 

The callback function signature to be used with the `message`[event](#on).

#### Parameters
Object event

An object containing information about the event:

- `type` - The type of event which was triggered.

- `data` - The data sent within the message.

 Pebble.PostMessageErrorCallback(event) 

The callback function signature to be used with the `postmessageerror`[event](#on).

#### Parameters
Object event

An object containing information about the event:

- `type` - The type of event which was triggered.

- `data` - The data failed to send within the message.

 Pebble.PostMessageConnectedCallback(event) 

The callback function signature to be used with the `postmessageconnected`[event](#on).

#### Parameters
Object event

An object containing information about the event:

- `type` - The type of event which was triggered.

 Pebble.PostMessageDisconnectedCallback(event) 

The callback function signature to be used with the `postmessagedisconnected`[event](#on).

#### Parameters
Object event

An object containing information about the event:

- `type` - The type of event which was triggered.

WatchInfo

Provides information about the connected Pebble smartwatch.

#### Properties
 platform

The hardware platform, such as `basalt` or `emery`.

 model

The watch model, such as `pebble_black`

 language

The user's currently selected language on this watch.

 firmware

An object containing information about the watch's firmware version, including:

- `major` - The major version

- `minor` - The minor version

- `patch` - The patch version

- `suffix` - Any additional version information, such as `beta3`

AppGlanceSlice

The structure of an app glance.

#### Properties
 expirationTime

Optional ISO date-time string of when the entry should expire and no longer be shown in the app glance.

 layout

An object containing:

- `icon` - URI string of the icon to display in the app glance, e.g. system://images/ALARM\_CLOCK.

- `subtitleTemplateString` - Template string that will be displayed in the subtitle of the app glance.
