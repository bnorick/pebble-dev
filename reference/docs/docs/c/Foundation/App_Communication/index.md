# App Communication

Source: https://developer.repebble.com/docs/c/Foundation/App_Communication/index.html

API for interacting with the Pebble communication subsystem.

## Function Documentation

void app\_comm\_set\_sniff\_interval(const [SniffInterval](/docs/c/Foundation/App_Communication/#SniffInterval) interval)

Set the Bluetooth module's sniff interval. The sniff interval will be restored to normal by the OS after the app's de-init handler is called. Set the sniff interval to normal whenever possible.

[SniffInterval](/docs/c/Foundation/App_Communication/#SniffInterval) app\_comm\_get\_sniff\_interval(void)

Get the Bluetooth module's sniff interval.

#### Returns

The [SniffInterval](/docs/c/Foundation/App_Communication/#SniffInterval) value corresponding to the current interval

## Enum Documentation

enum SniffInterval

Intervals during which the Bluetooth module may enter a low power mode. The sniff interval defines the period during which the Bluetooth module may not exchange (ACL) packets. The longer the sniff interval, the more time the Bluetooth module may spend in a low power mode. It may be necessary to reduce the sniff interval if an app requires reduced latency when sending messages.

These settings have a dramatic effect on the Pebble's energy consumption. Use the normal sniff interval whenever possible. Note, however, that switching between modes increases power consumption during the process. Frequent switching between modes is thus discouraged. Ensure you do not drop to normal frequently. The Bluetooth module is a major consumer of the Pebble's energy.

#### Enumerators
SNIFF\_INTERVAL\_NORMAL

Set the sniff interval to normal (power-saving) mode.

SNIFF\_INTERVAL\_REDUCED

Reduce the sniff interval to increase the responsiveness of the radio at the expense of increasing Bluetooth energy consumption by a multiple of 2-5 (very significant)
