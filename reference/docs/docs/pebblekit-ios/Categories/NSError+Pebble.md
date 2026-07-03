# NSError(Pebble) Category Reference

Source: https://developer.repebble.com/docs/pebblekit-ios/Categories/NSError+Pebble/

| Declared in | PBErrors.h |

### +&nbsp;pebbleErrorWithCode:underLyingError:

Convenience method to create an NSError object with error domain and a given [PBErrorCode](../../Constants/PBErrorCode/) and with an underlying NSError object.

`+ (NSError *)pebbleErrorWithCode:(PBErrorCode)code underLyingError:(NSError *__nullable)error`

#### Parameters
_code_The error code for which to create the error_error_The underlying error

#### Declared In

`PBErrors.h`

### +&nbsp;pebbleErrorWithCode:

Convenience method to create an NSError object with error domain and a given [PBErrorCode](../../Constants/PBErrorCode/).

`+ (NSError *)pebbleErrorWithCode:(PBErrorCode)code`

#### Parameters
_code_The error code for which to create the error

#### Declared In

`PBErrors.h`
