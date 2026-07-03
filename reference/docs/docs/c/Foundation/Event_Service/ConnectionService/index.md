# ConnectionService

Source: https://developer.repebble.com/docs/c/Foundation/Event_Service/ConnectionService/index.html

Determine what the Pebble watch is connected to

The ConnectionService allows your app to learn about the apps the Pebble watch is connected to. You can ask the system for this information at a given time or you can register to receive events every time connection or disconnection events occur.

It allows you to determine whether the watch is connected to the Pebble mobile app by subscribing to the pebble\_app\_connection\_handler or by calling the connection\_service\_peek\_pebble\_app\_connection function. Note that when the Pebble app is connected, you can assume PebbleKit JS apps will also be running correctly.

The service also allows you to determine if the Pebble watch can establish a connection to a PebbleKit companion app by subscribing to the pebblekit\_connection\_handler or by calling the connection\_service\_peek\_pebblekit\_connection function. Today, due to architectural differences between iOS and Android, this will return true for Android anytime a connection with the Pebble mobile app is established (since PebbleKit messages are routed through the Android app). For iOS, this will return true when any PebbleKit companion app has established a connection with the Pebble watch (since companion app messages are routed directly to the watch)

## Function Documentation

bool connection\_service\_peek\_pebble\_app\_connection(void)

Query the bluetooth connection service for the current Pebble app connection status.

#### Returns

true if the Pebble app is connected, false otherwise

bool connection\_service\_peek\_pebblekit\_connection(void)

Query the bluetooth connection service for the current PebbleKit connection status.

#### Returns

true if a PebbleKit companion app is connected, false otherwise

void connection\_service\_subscribe(ConnectionHandlers conn\_handlers)

Subscribe to the connection event service. Once subscribed, the appropriate handler gets called based on the type of connection event and user provided handlers.

#### Parameters
 ConnectionHandlers

A struct populated with the handlers to be called when the specified connection event occurs. If a given handler is NULL, no function will be called.

void connection\_service\_unsubscribe(void)

Unsubscribe from the bluetooth event service. Once unsubscribed, the previously registered handler will no longer be called.

bool bluetooth\_connection\_service\_peek(void)

DeprecatedBackward compatibility function for connection\_service\_peek\_pebble\_app\_connection. New code should use connection\_service\_peek\_pebble\_app\_connection directly. This will be removed in a future version of the Pebble SDK

void bluetooth\_connection\_service\_subscribe(ConnectionHandler handler)

DeprecatedBackward compatibility function for connection\_service\_subscribe. New code should use connection\_service\_subscribe directly. This will be removed in a future version of the Pebble SDK

void bluetooth\_connection\_service\_unsubscribe(void)

DeprecatedBackward compatibility function for connection\_service\_unsubscribe. New code should use connection\_service\_unsubscribe directly. This will be removed in a future version of the Pebble SDK

## Data Structure Documentation

struct ConnectionHandlers

#### Data Fields
ConnectionHandler pebble\_app\_connection\_handler

callback to be executed when the connection state between the watch and the phone app has changed. Note, if the phone App is connected, PebbleKit JS apps will also be working correctly

ConnectionHandler pebblekit\_connection\_handler

ID for callback to be executed on PebbleKit connection event.

## Typedef Documentation

 typedef void(\* ConnectionHandler)(bool connected) 

 typedef ConnectionHandler BluetoothConnectionHandler

DeprecatedBackwards compatibility typedef for ConnectionHandler. New code should use ConnectionHandler directly. This will be removed in a future version of the Pebble SDK.
