# Communication

Source: https://developer.repebble.com/guides/communication/

All Pebble watchapps and watchfaces have the ability to communicate with the outside world through its connection to the user's phone. The PebbleKit collection of libraries (see below) is available to facilitate this communication between watchapps and phone apps. Examples of additional functionality made possible through PebbleKit include, but are not limited to apps that can:

- Display weather, news, stocks, etc.

- Communicate with other web services.

- Read and control platform APIs and features of the connected phone.

## Contents

- [**Advanced Communication**](/guides/communication/advanced-communication.md) - Details of communication tips and best practices for more advanced scenarios.

- [**Datalogging**](/guides/communication/datalogging.md) - Information on how to collect data batches using the Datalogging API.

- [**PebbleKit Android**](/guides/communication/using-pebblekit-android.md) - How to use PebbleKit to communicate with a watchapp on Android.

- [**PebbleKit JS**](/guides/communication/using-pebblekit-js.md) - How to use PebbleKit JS to communicate with the connected phone's JS environment.

- [**PebbleKit iOS**](/guides/communication/using-pebblekit-ios.md) - How to use PebbleKit to communicate with a watchapp on iOS.

- [**Sending and Receiving Data**](/guides/communication/sending-and-receiving-data.md) - How to send and receive data between your watchapp and phone.

- [**Sports API**](/guides/communication/using-the-sports-api.md) - How to use the PebbleKit Sports API to integrate your mobile sports app with Pebble.

## Communication Model

Pebble communicates with the connected phone via the Bluetooth connection, which is the same connection that delivers notifications and other alerts in normal use. Developers can leverage this connection to send and receive arbitrary data using the [`AppMessage`](/docs/c/Foundation/AppMessage/ "AppMessage") API.

Depending on the requirements of the app, there are three possible ways to receive data sent from Pebble on the connected phone:

- [_PebbleKit JS_](/guides/communication/using-pebblekit-js.md) - A JavaScript environment running within the official Pebble mobile app with web, geolocation, and extended storage access.

- [_PebbleKit Android_](/guides/communication/using-pebblekit-android.md) - A library available to use in Android companion apps that allows them to interact with standard Android platform APIs.

- [_PebbleKit iOS_](/guides/communication/using-pebblekit-ios.md) - As above, but for iOS companion apps.

**Important**

PebbleKit JS cannot be used in conjunction with PebbleKit Android or PebbleKit iOS.

All messages sent from a Pebble watchapp or watchface will be delivered to the appropriate phone app depending on the layout of the developer's project:

- If at least an `index.js` file is present in `src/pkjs/`, the message will be handled by PebbleKit JS.

- If there is no valid JS file present (at least an `index.js`) in the project, the message will be delivered to the official Pebble mobile app. If there is a companion app installed that has registered a listener with the same UUID as the watchapp, the message will be forwarded to that app via PebbleKit Android/iOS.
