# PBVersionInfo Class Reference

Source: https://developer.repebble.com/docs/pebblekit-ios/Classes/PBVersionInfo/

| Inherits from | NSObject |
| Declared in | PBVersionInfo.h |

## Overview

An instance of PBVersionInfo describes all the different system software (Pebble OS) on a Pebble watch and other auxiliary information.

### runningFirmwareMetadata

The metadata of the firmware that is running.

`@property (nonatomic, readonly, strong, nullable) PBFirmwareMetadata *runningFirmwareMetadata`

#### Declared In

`PBVersionInfo.h`

### recoveryFirmwareMetadata

The metadata of the recovery firmware that is in storage.

`@property (nonatomic, readonly, strong, nullable) PBFirmwareMetadata *recoveryFirmwareMetadata`

#### Declared In

`PBVersionInfo.h`

### systemResources

The metadata of the system resources.

`@property (nonatomic, readonly, strong) PBResourceMetadata *systemResources`

#### Declared In

`PBVersionInfo.h`

### bootloaderVersion

The version of the bootloader.

`@property (nonatomic, readonly) UInt32 bootloaderVersion`

#### Declared In

`PBVersionInfo.h`

### hardwareVersion

The version of the hardware.

`@property (nonatomic, readonly, strong) NSString *hardwareVersion`

#### Declared In

`PBVersionInfo.h`

### serialNumber

The serial number.

`@property (nonatomic, readonly, strong) NSString *serialNumber`

#### Declared In

`PBVersionInfo.h`

### deviceAddress

The current Bluetooth device address.

`@property (nonatomic, readonly, strong) NSData *deviceAddress`

#### Declared In

`PBVersionInfo.h`

### remoteProtocolCapabilitiesFlags

Flags for the supported protocol features of the watch.

`@property (nonatomic, readonly, assign) PBRemoteProtocolCapabilitiesFlags remoteProtocolCapabilitiesFlags`

#### Declared In

`PBVersionInfo.h`

### hasBeenUnfaithful

Indicates if the previous connection for the watch was to this device.

`@property (nonatomic, readonly, assign) BOOL hasBeenUnfaithful`

#### Discussion

If the watch has been connected to this device, but connects to other device before connecting again to this device, the value will be YES.

#### Declared In

`PBVersionInfo.h`

### –&nbsp;hasRecoveryFirmware

YES if valid recovery firmware is installed, NO if not.

`- (BOOL)hasRecoveryFirmware`

#### Declared In

`PBVersionInfo.h`

### –&nbsp;hasSystemResources

YES if valid system resources are installed, NO if not.

`- (BOOL)hasSystemResources`

#### Declared In

`PBVersionInfo.h`

### –&nbsp;appMessagesSupported

YES if app messages are supported, NO if not.

`- (BOOL)appMessagesSupported`

#### Declared In

`PBVersionInfo.h`
