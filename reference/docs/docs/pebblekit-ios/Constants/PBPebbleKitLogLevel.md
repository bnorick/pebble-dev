# PBPebbleKitLogLevel Constants Reference

Source: https://developer.repebble.com/docs/pebblekit-ios/Constants/PBPebbleKitLogLevel/

| Declared in | PBLog+Public.h |

### PBPebbleKitLogLevel

#### Definition
`typedef NS_ENUM(NSUInteger, PBPebbleKitLogLevel ) {
                            
                               PBPebbleKitLogLevelOff = 0,
                            
                               PBPebbleKitLogLevelError = ( PBPebbleKitLogFlagError ),
                            
                               PBPebbleKitLogLevelWarning = ( PBPebbleKitLogLevelError | PBPebbleKitLogFlagWarning ),
                            
                               PBPebbleKitLogLevelInfo = ( PBPebbleKitLogLevelWarning | PBPebbleKitLogFlagInfo ),
                            
                               PBPebbleKitLogLevelDebug = ( PBPebbleKitLogLevelInfo | PBPebbleKitLogFlagDebug ),
                            
                               PBPebbleKitLogLevelVerbose = ( PBPebbleKitLogLevelDebug | PBPebbleKitLogFlagVerbose ),
                            
                               PBPebbleKitLogLevelAll = 0 xffffffff,
                            
                            };`

#### Constants
`PBPebbleKitLogLevelOff`

Declared In `PBLog+Public.h`.

`PBPebbleKitLogLevelError`

Declared In `PBLog+Public.h`.

`PBPebbleKitLogLevelWarning`

Declared In `PBLog+Public.h`.

`PBPebbleKitLogLevelInfo`

Declared In `PBLog+Public.h`.

`PBPebbleKitLogLevelDebug`

Declared In `PBLog+Public.h`.

`PBPebbleKitLogLevelVerbose`

Declared In `PBLog+Public.h`.

`PBPebbleKitLogLevelAll`

Declared In `PBLog+Public.h`.
