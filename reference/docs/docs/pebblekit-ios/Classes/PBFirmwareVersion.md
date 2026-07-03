# PBFirmwareVersion Class Reference

Source: https://developer.repebble.com/docs/pebblekit-ios/Classes/PBFirmwareVersion/

| Inherits from | [PBSemanticVersion](../../Classes/PBSemanticVersion/) : NSObject |
| Conforms to | NSCopying |
| Declared in | PBFirmwareVersion.h |

## Overview

PBFirmwareVersion is a helper class that is able to parse the versionTag string into its components ([major](#//api/name/major), [minor](#//api/name/minor), revision, suffix) and facilitate comparisons between versions.

Valid versions follow the following format:`(v)MAJORVERSION(.MINORVERSION(.REVISIONVERSION(-SUFFIX)))`

Where the fields MAJOR, MINOR, REVISION are positive, decimal integer numbers and SUFFIX an arbitrary string. MINOR, REVISION, and SUFFIX are optional (nested optionality).

Examples of valid versions:

- `1`
- `v2`
- `v3.4-foo`
- `v4.1234.99-alpha-beta-gamma`

**Note:** For legacy uses in which the legacy properties below are used, the version format is:`(v)OS(.MAJOR(.MINOR(-SUFFIX)))`

## Other Methods

### timestamp

The version timestamp.

`@property (nonatomic, readonly) uint32_t timestamp`

#### Discussion

The timestamp is in the final comparison equation, in the -compare: method, after evaluating [major](#//api/name/major), [minor](#//api/name/minor), and revision components.

#### Declared In

`PBFirmwareVersion.h`

### commitHash

The version’s git commit hash.

`@property (nonatomic, readonly, copy, nullable) NSString *commitHash`

#### Discussion

The commit hash is not used in the -compare: method.

#### Declared In

`PBFirmwareVersion.h`

### tag

The version’s git tag.

`@property (nonatomic, readonly, copy) NSString *tag`

#### Declared In

`PBFirmwareVersion.h`

### +&nbsp;firmwareVersionWithString:

Creates a PBFirmwareVersion object given a [tag](#//api/name/tag) string.

`+ (nullable instancetype)firmwareVersionWithString:(NSString *)tag`

#### Parameters
_tag_The firmware version string to parse.

#### Declared In

`PBFirmwareVersion.h`

### +&nbsp;firmwareVersionWithTag:commitHash:timestamp:

Creates a PBFirmwareVersion object given a [tag](#//api/name/tag) string and [timestamp](#//api/name/timestamp).

`+ (nullable instancetype)firmwareVersionWithTag:(NSString *)tag commitHash:(nullable NSString *)commitHash timestamp:(uint32_t)timestamp`

#### Parameters
_tag_The firmare version string to parse._commitHash_A version’s commit hash. Can be nil._timestamp_The version timestamp.

#### Declared In

`PBFirmwareVersion.h`

### +&nbsp;firmwareVersionWithMajor:minor:revision:suffix:commitHash:timestamp:

Creates a PBFirmwareVersion object given its components.

`+ (instancetype)firmwareVersionWithMajor:(NSInteger)major minor:(NSInteger)minor revision:(NSInteger)revision suffix:(nullable NSString *)suffix commitHash:(nullable NSString *)commitHash timestamp:(uint32_t)timestamp`

#### Parameters
_major_The version major number._minor_The version minor number._revision_The version revision number._suffix_The version suffix. Can be nil._commitHash_A version’s commit hash. Can be nil._timestamp_The version timestamp.

#### Discussion

The [tag](#//api/name/tag) string will be set to the canonical format vMAJOR.MINOR.REVISION(-SUFFIX).

#### Declared In

`PBFirmwareVersion.h`

## Legacy Methods

### os

The OS version component. ( **Deprecated:** Use [PBSemanticVersion majorVersion])

`@property (nonatomic, readonly) NSInteger os`

#### Declared In

`PBFirmwareVersion+Legacy.h`

### major

The major version component. ( **Deprecated:** Use [PBSemanticVersion minorVersion])

`@property (nonatomic, readonly) NSInteger major`

#### Discussion

**Note:** If a version [tag](#//api/name/tag) string does not contain a major component, it will be set to 0.

#### Declared In

`PBFirmwareVersion+Legacy.h`

### minor

The minor version component. ( **Deprecated:** Use [PBSemanticVersion revisionVersion])

`@property (nonatomic, readonly) NSInteger minor`

#### Discussion

**Note:** If a version [tag](#//api/name/tag) string does not contain a [major](#//api/name/major) component, it will be set to 0.

#### Declared In

`PBFirmwareVersion+Legacy.h`

### +&nbsp;firmwareVersionWithOS:major:minor:suffix:commitHash:timestamp:

Creates a PBFirmwareVersion object given its components. ( **Deprecated:** Use +[PBFirmwareVersion firmwareVersionWithMajor:minor:revision:suffix:commitHash:timestamp:])

`+ (nullable instancetype)firmwareVersionWithOS:(NSInteger)os major:(NSInteger)major minor:(NSInteger)minor suffix:(nullable NSString *)suffix commitHash:(nullable NSString *)commitHash timestamp:(uint32_t)timestamp`

#### Parameters
_os_The version major number._major_The version minor number._minor_The version revision number._suffix_The version suffix. Can be nil._commitHash_A version’s commit hash. Can be nil._timestamp_The version timestamp.

#### Discussion

The [tag](#//api/name/tag) string will be set to the canonical format vMAJOR.MINOR.REVISION(-SUFFIX).

#### Declared In

`PBFirmwareVersion+Legacy.h`
