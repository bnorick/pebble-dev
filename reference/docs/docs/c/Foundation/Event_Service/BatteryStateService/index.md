# BatteryStateService

Source: https://developer.repebble.com/docs/c/Foundation/Event_Service/BatteryStateService/index.html

Determines when the battery state changes

The BatteryStateService API lets you know when the battery state changes, that is, its current charge level, whether it is plugged and charging. It uses the [BatteryChargeState](/docs/c/Foundation/Event_Service/BatteryStateService/#BatteryChargeState) structure to describe the current power state of Pebble.

Refer to the [classio-battery-connection](https://github.com/pebble-examples/classio-battery-connection) example, which demonstrates using the battery state service in a watchface.

## Function Documentation

void battery\_state\_service\_subscribe([BatteryStateHandler](/docs/c/Foundation/Event_Service/BatteryStateService/#BatteryStateHandler) handler)

Subscribe to the battery state event service. Once subscribed, the handler gets called on every battery state change.

#### Parameters
 handler

A callback to be executed on battery state change event

void battery\_state\_service\_unsubscribe(void)

Unsubscribe from the battery state event service. Once unsubscribed, the previously registered handler will no longer be called.

[BatteryChargeState](/docs/c/Foundation/Event_Service/BatteryStateService/#BatteryChargeState) battery\_state\_service\_peek(void)

Peek at the last known battery state.

#### Returns

a [BatteryChargeState](/docs/c/Foundation/Event_Service/BatteryStateService/#BatteryChargeState) containing the last known data

## Data Structure Documentation

struct BatteryChargeState

Structure for retrieval of the battery charge state.

#### Data Fields
uint8\_t charge\_percent

A percentage (0-100) of how full the battery is.

bool is\_charging

True if the battery is currently being charged. False if not.

bool is\_plugged

True if the charger cable is connected. False if not.

## Typedef Documentation

 typedef void(\* BatteryStateHandler)(BatteryChargeState charge) 

Callback type for battery state change events.

#### Parameters
 charge

the state of the battery [BatteryChargeState](/docs/c/Foundation/Event_Service/BatteryStateService/#BatteryChargeState)
