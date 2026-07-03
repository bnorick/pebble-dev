# PBResourceMetadata Class Reference

Source: https://developer.repebble.com/docs/pebblekit-ios/Classes/PBResourceMetadata/

| Inherits from | NSObject |
| Declared in | PBResourceMetadata.h |

## Overview

Instances of PBResourceMetadata describe (system) resources.

### timestamp

The version of the resources as the Epoch timestamp of the Git commit.

`@property (nonatomic, readonly) uint32_t timestamp`

#### Declared In

`PBResourceMetadata.h`

### crc

The checksum of the resources.

`@property (nonatomic, readonly) uint32_t crc`

#### Declared In

`PBResourceMetadata.h`
