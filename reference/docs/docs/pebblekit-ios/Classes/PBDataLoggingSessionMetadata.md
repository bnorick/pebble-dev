# PBDataLoggingSessionMetadata Class Reference

Source: https://developer.repebble.com/docs/pebblekit-ios/Classes/PBDataLoggingSessionMetadata/

| Inherits from | NSObject |
| Conforms to | NSCopying  
NSSecureCoding |
| Declared in | PBDataLoggingService.h |

## Overview

The metadata of a data logging session. Used to identify a session.

### tag

A tag associated with the session.

`@property (nonatomic, readonly) uint32_t tag`

#### Declared In

`PBDataLoggingService.h`

### timestamp

The timestamp of the moment the session was created by the watchapp.

`@property (nonatomic, readonly) uint32_t timestamp`

#### Declared In

`PBDataLoggingService.h`

### type

The type of data stored in this session.

`@property (nonatomic, readonly) PBDataLoggingType type`

#### Declared In

`PBDataLoggingService.h`

### itemSize

The size of a data item.

`@property (nonatomic, readonly) uint16_t itemSize`

#### Declared In

`PBDataLoggingService.h`

### serialNumber

The serial number of the watch that created the sessions.

`@property (nonatomic, copy, readonly) NSString *serialNumber`

#### Declared In

`PBDataLoggingService.h`

### +&nbsp;metadataWithTag:timestamp:type:itemSize:serialNumber:

Creates a new data logging session metadata object, given all its property values. This method is provided to create a metadata object that can be used to compare it with a metadata object that is passed into one of the[PBDataLoggingServiceDelegate](../../Protocols/PBDataLoggingServiceDelegate/) methods.

`+ (instancetype)metadataWithTag:(uint32_t)tag timestamp:(uint32_t)timestamp type:(PBDataLoggingType)type itemSize:(uint16_t)itemSize serialNumber:(NSString *)serialNumber`

#### Parameters
_tag_The tag associated with the session_timestamp_The timestamp of the creation of the session_type_The type of data stored in the session_itemSize_The size of a data item_serialNumber_The serial number of the watch that created the session

#### Return Value

A session metadata object with the specified information

#### Declared In

`PBDataLoggingService.h`

### –&nbsp;isEqual:

Tests the equality of the recipient and the given object.

`- (BOOL)isEqual:(nullable id)object`

#### Parameters
_object_The object to check against.

#### Return Value

`YES` if all the property values of the receiver are equal to the property values of the other object.

#### Discussion

This method can be used to compare two sessions’ metadata objects to check whether they are referring to the same session or not.

#### Declared In

`PBDataLoggingService.h`

### –&nbsp;isEqualToDataLoggingSessionMetadata:

Tests the equality of two data logging sessions’ metadata objects.

`- (BOOL)isEqualToDataLoggingSessionMetadata:(PBDataLoggingSessionMetadata *)sessionMetadata`

#### Parameters
_sessionMetadata_The session metadata to compare against.

#### Return Value

`YES` if all the property values of the receiver are equal to the property values of the given session.

#### Discussion

This method can be used to compare two sessions’ metadata objects to check whether they are referring to the same session or not.

**Note:** Equivalent to [[PBDataLoggingSessionMetadata isEqual:]](#//api/name/isEqual:)

#### Declared In

`PBDataLoggingService.h`
