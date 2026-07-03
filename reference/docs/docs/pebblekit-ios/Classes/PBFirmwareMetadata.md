# PBFirmwareMetadata Class Reference

Source: https://developer.repebble.com/docs/pebblekit-ios/Classes/PBFirmwareMetadata/

| Inherits from | NSObject |
| Declared in | PBFirmwareMetadata.h |

## Overview

Metainformation about a firmware running in a watch.

The information contains the firmware [version](#//api/name/version), the firmware hardware platform, and other values.

### version

The version of the firmware.

`@property (nonatomic, readonly) PBFirmwareVersion *version`

#### See Also

- `PBFirmwareVersion`

#### Declared In

`PBFirmwareMetadata.h`

### isRecoveryFirmware

YES if the firmware is a recovery firmware, NO if it is a regular firmware.

`@property (nonatomic, readonly) BOOL isRecoveryFirmware`

#### Declared In

`PBFirmwareMetadata.h`

### hardwarePlatform

The hardware platform variant with which the firmware is compatible.

`@property (nonatomic, readonly) FirmwareMetadataPlatform hardwarePlatform`

#### Declared In

`PBFirmwareMetadata.h`

### +&nbsp;hardwarePlatformToString:

Converts a [FirmwareMetadataPlatform](../../Constants/FirmwareMetadataPlatform/) value to a string.

`+ (NSString *)hardwarePlatformToString:(FirmwareMetadataPlatform)hardwarePlatform`

#### Parameters
_hardwarePlatform_The hardware platform value to convert

#### Return Value

A string of the hardware platform

#### Declared In

`PBFirmwareMetadata.h`

### +&nbsp;stringToHardwarePlatform:

Converts an NSString hardware platform string to the corresponding[FirmwareMetadataPlatform](../../Constants/FirmwareMetadataPlatform/) value.

`+ (FirmwareMetadataPlatform)stringToHardwarePlatform:(NSString *)hardwarePlatformString`

#### Parameters
_hardwarePlatformString_The string representing the hardware platform.

#### Return Value

The hardware platform enum value

#### Declared In

`PBFirmwareMetadata.h`
