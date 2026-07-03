# NSData(Pebble) Category Reference

Source: https://developer.repebble.com/docs/pebblekit-ios/Categories/NSData+Pebble/

| Declared in | NSDictionary+Pebble.h |

### –&nbsp;pb\_dictionaryFromPebbleDictionaryDataWithError:

Interprets the receiver as Pebble dict data and deserializes it into an NSDictionary.

`- (nullable NSDictionary *)pb_dictionaryFromPebbleDictionaryDataWithError:(NSError *__autoreleasing *)error`

#### Parameters
_error_Pointer to an NSError \* that will be set after the method has returned in case there was an error. Possible error codes: PBErrorCodeDictionaryInternalConsistency

#### See Also

- `[NSDictionary(Pebble) pb_pebbleDictionaryData:]`

#### Declared In

`NSDictionary+Pebble.h`
