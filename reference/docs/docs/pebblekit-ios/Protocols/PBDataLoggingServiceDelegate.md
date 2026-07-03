# PBDataLoggingServiceDelegate Protocol Reference

Source: https://developer.repebble.com/docs/pebblekit-ios/Protocols/PBDataLoggingServiceDelegate/

| Conforms to | NSObject |
| Declared in | PBDataLoggingService.h |

## Overview

Data logging delegate protocol. The object that implements this protocol is responsible for handling incoming data.

### –&nbsp;dataLoggingService:hasByteArrays:numberOfItems:forDataLoggingSession:

Called by the service every time there is data available that has not been consumed yet.

`- (BOOL)dataLoggingService:(PBDataLoggingService *)service hasByteArrays:(const uint8_t *const)bytes numberOfItems:(uint16_t)numberOfItems forDataLoggingSession:(PBDataLoggingSessionMetadata *)session`

#### Parameters
_service_The data logging service._bytes_Pointer to the array of bytes. The array contains (numberOfItems \* session.itemSize) bytes._numberOfItems_The number of items that the array contains._session_The metadata of the session.

#### Return Value

YES if the data was consumed and the service can discard the data. Return NO if the data was not be consumed after the method returned. If NO is returned, the next time this callback is invoked for the session, the data argument will (also) contain the data of the items of the previous invocation of the callback.

#### Declared In

`PBDataLoggingService.h`

### –&nbsp;dataLoggingService:hasUInt8s:numberOfItems:forDataLoggingSession:

Called by the service every time there is data available that has not been consumed yet.

`- (BOOL)dataLoggingService:(PBDataLoggingService *)service hasUInt8s:(const uint8_t [])data numberOfItems:(uint16_t)numberOfItems forDataLoggingSession:(PBDataLoggingSessionMetadata *)session`

#### Parameters
_service_The data logging service._data_Pointer to the array of UInt8`s._numberOfItems_The number of items that the array contains._session_The metadata of the session.

#### Return Value

YES if the data was consumed and the service can discard the data. Return NO if the data was not be consumed after the method returned. If NO is returned, the next time this callback is invoked for the session, the data argument will (also) contain the data of the items of the previous invocation of the callback.

#### Declared In

`PBDataLoggingService.h`

### –&nbsp;dataLoggingService:hasUInt16s:numberOfItems:forDataLoggingSession:

Called by the service every time there is data available that has not been consumed yet.

`- (BOOL)dataLoggingService:(PBDataLoggingService *)service hasUInt16s:(const uint16_t [])data numberOfItems:(uint16_t)numberOfItems forDataLoggingSession:(PBDataLoggingSessionMetadata *)session`

#### Parameters
_service_The data logging service._data_Pointer to the array of UInt16`s._numberOfItems_The number of items that the array contains._session_The metadata of the session.

#### Return Value

YES if the data was consumed and the service can discard the data. Return NO if the data was not be consumed after the method returned. If NO is returned, the next time this callback is invoked for the session, the data argument will (also) contain the data of the items of the previous invocation of the callback.

#### Declared In

`PBDataLoggingService.h`

### –&nbsp;dataLoggingService:hasUInt32s:numberOfItems:forDataLoggingSession:

Called by the service every time there is data available that has not been consumed yet.

`- (BOOL)dataLoggingService:(PBDataLoggingService *)service hasUInt32s:(const uint32_t [])data numberOfItems:(uint16_t)numberOfItems forDataLoggingSession:(PBDataLoggingSessionMetadata *)session`

#### Parameters
_service_The data logging service._data_Pointer to the array of UInt32`s._numberOfItems_The number of items that the array contains._session_The metadata of the session.

#### Return Value

YES if the data was consumed and the service can discard the data. Return NO if the data was not be consumed after the method returned. If NO is returned, the next time this callback is invoked for the session, the data argument will (also) contain the data of the items of the previous invocation of the callback.

#### Declared In

`PBDataLoggingService.h`

### –&nbsp;dataLoggingService:hasSInt8s:numberOfItems:forDataLoggingSession:

Called by the service every time there is data available that has not been consumed yet.

`- (BOOL)dataLoggingService:(PBDataLoggingService *)service hasSInt8s:(const int8_t [])data numberOfItems:(uint16_t)numberOfItems forDataLoggingSession:(PBDataLoggingSessionMetadata *)session`

#### Parameters
_service_The data logging service._data_Pointer to the array of SInt8`s._numberOfItems_The number of items that the array contains._session_The metadata of the session.

#### Return Value

YES if the data was consumed and the service can discard the data. Return NO if the data was not be consumed after the method returned. If NO is returned, the next time this callback is invoked for the session, the data argument will (also) contain the data of the items of the previous invocation of the callback.

#### Declared In

`PBDataLoggingService.h`

### –&nbsp;dataLoggingService:hasSInt16s:numberOfItems:forDataLoggingSession:

Called by the service every time there is data available that has not been consumed yet.

`- (BOOL)dataLoggingService:(PBDataLoggingService *)service hasSInt16s:(const int16_t [])data numberOfItems:(uint16_t)numberOfItems forDataLoggingSession:(PBDataLoggingSessionMetadata *)session`

#### Parameters
_service_The data logging service._data_Pointer to the array of SInt16`s._numberOfItems_The number of items that the array contains._session_The metadata of the session.

#### Return Value

YES if the data was consumed and the service can discard the data. Return NO if the data was not be consumed after the method returned. If NO is returned, the next time this callback is invoked for the session, the data argument will (also) contain the data of the items of the previous invocation of the callback.

#### Declared In

`PBDataLoggingService.h`

### –&nbsp;dataLoggingService:hasSInt32s:numberOfItems:forDataLoggingSession:

Called by the service every time there is data available that has not been consumed yet.

`- (BOOL)dataLoggingService:(PBDataLoggingService *)service hasSInt32s:(const int32_t [])data numberOfItems:(uint16_t)numberOfItems forDataLoggingSession:(PBDataLoggingSessionMetadata *)session`

#### Parameters
_service_The data logging service._data_Pointer to the array of SInt32`s._numberOfItems_The number of items that the array contains._session_The metadata of the session.

#### Return Value

YES if the data was consumed and the service can discard the data. Return NO if the data was not be consumed after the method returned. If NO is returned, the next time this callback is invoked for the session, the data argument will (also) contain the data of the items of the previous invocation of the callback.

#### Declared In

`PBDataLoggingService.h`

### –&nbsp;dataLoggingService:sessionDidFinish:

Called by the service every time a session is finished. This is guaranteed to be called only after all data has been received and consumed by the application.

`- (void)dataLoggingService:(PBDataLoggingService *)service sessionDidFinish:(PBDataLoggingSessionMetadata *)session`

#### Parameters
_service_The data logging service._session_The metadata of the session.

#### Declared In

`PBDataLoggingService.h`
