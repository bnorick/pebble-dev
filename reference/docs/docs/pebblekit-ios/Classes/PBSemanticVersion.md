# PBSemanticVersion Class Reference

Source: https://developer.repebble.com/docs/pebblekit-ios/Classes/PBSemanticVersion/

| Inherits from | NSObject |
| Declared in | PBSemanticVersion.h |

## Overview

A version number that follows the rules of semantic versioning.

The version number is supposed to have three components and an optional[suffix](#//api/name/suffix).

### majorVersion

The version major number

`@property (nonatomic, assign, readonly) NSUInteger majorVersion`

#### Declared In

`PBSemanticVersion.h`

### minorVersion

The version minor number

`@property (nonatomic, assign, readonly) NSUInteger minorVersion`

#### Declared In

`PBSemanticVersion.h`

### revisionVersion

The version revision number

`@property (nonatomic, assign, readonly) NSUInteger revisionVersion`

#### Declared In

`PBSemanticVersion.h`

### suffix

The version suffix string.

`@property (nonatomic, copy, readonly) NSString *suffix`

#### Discussion

**Note:** If a version tag string does not contain a suffix, it will be set to an empty string.

The release suffix is not used in the [compare:](#//api/name/compare:) or -isEqual: methods.

#### Declared In

`PBSemanticVersion.h`

### –&nbsp;initWithVersionString:

Returns a new instance by parsing the input.

`- (nullable instancetype)initWithVersionString:(NSString *)versionString`

#### Parameters
_versionString_Expected format: major.minor.revision-sffix. Example: “2.0.1-rc2” If a parsing error occurs, nil will be returned.

#### Return Value

A version or `nil` if some error happen.

#### Declared In

`PBSemanticVersion.h`

### –&nbsp;initWithMajor:minor:revision:suffix:

Returns a new instance by using the given components.

`- (instancetype)initWithMajor:(NSUInteger)major minor:(NSUInteger)minor revision:(NSUInteger)revision suffix:(nullable NSString *)suffix`

#### Parameters
_major_The version major number._minor_The version minor number._revision_The version revision number._suffix_The version suffix. Can be nil.

#### Declared In

`PBSemanticVersion.h`

### –&nbsp;compare:

Compares the receiver to another version object.

`- (NSComparisonResult)compare:(PBSemanticVersion *)aVersion`

#### Parameters
_aVersion_The version to compare with the receiver.

#### Return Value

`NSOrderedAscending` if the value of aVersion is greater than the receiver’s, `NSOrderedSame` if they’re equal, and`NSOrderedDescending` if the value of `aVersion` is less than the receiver’s.

#### Declared In

`PBSemanticVersion.h`

### –&nbsp;isEqualOrNewer:

Returns if the the receiver is equal or newer than the given version.

`- (BOOL)isEqualOrNewer:(PBSemanticVersion *)other`

#### Parameters
_other_Version number to compare against.

#### Return Value

`YES` if the receiver is equal or newer. `NO` otherwise.

#### Declared In

`PBSemanticVersion.h`

### –&nbsp;isNewer:

Returns if the receiver is strictly newer than the given version.

`- (BOOL)isNewer:(PBSemanticVersion *)other`

#### Parameters
_other_Version number to compare against.

#### Return Value

`YES` if the receiver is stricly newer. `NO` otherwise.

#### Declared In

`PBSemanticVersion.h`
