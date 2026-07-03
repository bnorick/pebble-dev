# NSDictionary(Pebble) Category Reference

Source: https://developer.repebble.com/docs/pebblekit-ios/Categories/NSDictionary+Pebble/

| Declared in | NSDictionary+Pebble.h |

### –&nbsp;pb\_pebbleDictionaryData:

Serializes the receiver into a Pebble dict.

`- (nullable NSData *)pb_pebbleDictionaryData:(NSError *__autoreleasing *)error`

#### Parameters
_error_Pointer to an NSError \* that will be set in case there was an error creating the dictionary. Possible error codes: PBErrorCodeDictionaryUnsupportedKeyClass PBErrorCodeDictionaryUnsupportedValueClass PBErrorCodeDictionaryUnsupportedValueClass

#### Discussion

The receiver dictionary must comply to the following constraints:

- The keys must be instances of `NSNumber`. Their `-unsignedLongValue`return value will be used as final key.
- The values must be instances of either `NSString`, `NSData` or`NSNumber`. Use the `NSNumber (stdint)` category to specify the signedness and width of `NSNumber`.

#### See Also

- `[NSData(Pebble) pb_dictionaryFromPebbleDictionaryDataWithError:]`

#### Declared In

`NSDictionary+Pebble.h`
