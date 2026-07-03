# PBWatchDelegate Protocol Reference

Source: https://developer.repebble.com/docs/pebblekit-ios/Protocols/PBWatchDelegate/

| Conforms to | NSObject |
| Declared in | PBWatch.h |

### –&nbsp;watchDidDisconnect:

Called when the watch got disconnected.

`- (void)watchDidDisconnect:(PBWatch *)watch`

#### Parameters
_watch_The watch that was disconnected.

#### Declared In

`PBWatch.h`

### –&nbsp;watch:handleError:

Called when the watch caught an error.

`- (void)watch:(PBWatch *)watch handleError:(NSError *)error`

#### Parameters
_watch_The watch that caught the error._error_The error catch by the watch.

#### Declared In

`PBWatch.h`

### –&nbsp;watchWillResetSession:

Called when an internal session is about to be reset.

`- (void)watchWillResetSession:(PBWatch *)watch`

#### Parameters
_watch_The watch that will reset its session.

#### Declared In

`PBWatch.h`

### –&nbsp;watchDidOpenSession:

Called when an internal session is opened

`- (void)watchDidOpenSession:(PBWatch *)watch`

#### Parameters
_watch_The watch that opened a session.

#### Declared In

`PBWatch.h`

### –&nbsp;watchDidCloseSession:

Called when an internal EASession is closed

`- (void)watchDidCloseSession:(PBWatch *)watch`

#### Parameters
_watch_The watch that closed its session.

#### Declared In

`PBWatch.h`
