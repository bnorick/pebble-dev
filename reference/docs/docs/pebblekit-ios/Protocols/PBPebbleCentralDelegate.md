# PBPebbleCentralDelegate Protocol Reference

Source: https://developer.repebble.com/docs/pebblekit-ios/Protocols/PBPebbleCentralDelegate/

| Conforms to | NSObject |
| Declared in | PBPebbleCentral.h |

### –&nbsp;pebbleCentral:watchDidConnect:isNew:

The Pebble Central responsible for calling the delegate method.

`- (void)pebbleCentral:(PBPebbleCentral *)central watchDidConnect:(PBWatch *)watch isNew:(BOOL)isNew`

#### Parameters
_central_The Pebble Central responsible for calling the delegate method._watch_The PBWatch object representing the watch that was connected._isNew_YES if the watch has been connected for the first time since the app has been installed or NO if not.

#### Declared In

`PBPebbleCentral.h`

### –&nbsp;pebbleCentral:watchDidDisconnect:

The Pebble Central responsible for calling the delegate method.

`- (void)pebbleCentral:(PBPebbleCentral *)central watchDidDisconnect:(PBWatch *)watch`

#### Parameters
_central_The Pebble Central responsible for calling the delegate method._watch_The PBWatch object representing the watch that was disconnected.

#### Declared In

`PBPebbleCentral.h`
