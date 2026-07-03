# TouchService

Source: https://developer.repebble.com/docs/c/Foundation/Event_Service/TouchService/index.html

The APIs on this page will only work with SDK 4.9+.

## Function Documentation

void touch\_service\_subscribe([TouchServiceHandler](/docs/c/Foundation/Event_Service/TouchService/#TouchServiceHandler) handler, void \* context)

Subscribe to touch events. The touch sensor is enabled while subscribed.

#### Parameters
 handler

Callback invoked for each touch event

 context

User context passed to the callback

void touch\_service\_unsubscribe(void)

Unsubscribe from touch events. The touch sensor is disabled if no other subscribers remain.

bool touch\_service\_is\_enabled(void)

#### Returns

true if touch input is currently being delivered to apps. Returns false on platforms without a touchscreen, or when touch has been disabled system-wide (future feature). Apps can poll this (for example on window appear) to avoid looking broken when touch is unavailable.

## Data Structure Documentation

struct TouchEvent

Touch event data, carried directly in PebbleTouchEvent.

#### Data Fields
[TouchEventType](/docs/c/Foundation/Event_Service/TouchService/#TouchEventType) typeint16\_t xint16\_t y

## Enum Documentation

enum TouchEventType

Touch event type.

#### Enumerators
TouchEvent\_TouchdownTouchEvent\_LiftoffTouchEvent\_PositionUpdate

## Typedef Documentation

 typedef void(\* TouchServiceHandler)(const TouchEvent \*event, void \*context) 

Callback for touch events.

#### Parameters
 event

The touch event data

 context

User-provided context
