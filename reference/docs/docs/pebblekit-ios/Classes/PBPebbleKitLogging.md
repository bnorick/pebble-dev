# PBPebbleKitLogging Class Reference

Source: https://developer.repebble.com/docs/pebblekit-ios/Classes/PBPebbleKitLogging/

| Inherits from | NSObject |
| Declared in | PBLog+Public.h |

## Overview

Every log produced by PebbleKit will be sent through this type.

By default the logs are simply sent to `NSLog`, but the callback can be overriden to send the logs to another logging facility.

The maximum log level can be also modified. The default callback handles the log level automatically, but any customized logging callbacks will need to handle the log level themselves.

It is advised to call these methods before making any other calls to PebbleKit, for example in your AppDelegate’s`application:willFinishLaunchingWithOptions:` before state restoration happens.

### +&nbsp;setLogLevel:

Configures which events should be logged.

`+ (void)setLogLevel:(PBPebbleKitLogLevel)logLevel`

#### Parameters
_logLevel_One of the values in PBPebbleKitLogLevel, which will be the maximum level that will be logged. You can use PBPebbleKitLogLevelOff to disable all logging.

#### Declared In

`PBLog+Public.h`

### +&nbsp;setLoggingCallback:

Sets a [new](#//api/name/new) logging callback that will be invoked for each of the log records emitted by PebbleKit.

`+ (void)setLoggingCallback:(nullable PBPebbleKitLoggingCallback)loggingCallback`

#### Parameters
_loggingCallback_A block that will be invoked for each of the log records emitted by PebbleKit. Set this value to nil to return to the default NSLog logging.

#### Declared In

`PBLog+Public.h`

### +&nbsp;new

You should not create instances of this type.

`+ (instancetype)new`

#### Discussion

**Note:** You should not create instances of this type.

#### Declared In

`PBLog+Public.h`

### –&nbsp;init

You should not create instances of this type.

`- (instancetype)init`

#### Discussion

**Note:** You should not create instances of this type.

#### Declared In

`PBLog+Public.h`
