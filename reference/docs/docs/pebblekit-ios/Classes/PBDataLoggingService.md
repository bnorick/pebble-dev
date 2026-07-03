# PBDataLoggingService Class Reference

Source: https://developer.repebble.com/docs/pebblekit-ios/Classes/PBDataLoggingService/

| Inherits from | NSObject |
| Declared in | PBDataLoggingService.h |

## Overview

The data logging service. Assign a [delegate](#//api/name/delegate) object in order to receive data from your watchapp.

### delegate

The delegate that has the responsility of handling callbacks from the data logging service.

`@property (atomic, readwrite, weak) id<PBDataLoggingServiceDelegate> delegate`

#### Declared In

`PBDataLoggingService.h`

### –&nbsp;setDelegateQueue:

Sets the queue on which [delegate](#//api/name/delegate) methods will be executed. Callbacks are intended to be processed in the order as they come in, so it you must use a serial queue. If set to nil (default) the main queue is used.

`- (void)setDelegateQueue:(dispatch_queue_t)delegateQueue`

#### Parameters
_delegateQueue_The queue on which the delegate methods will be executed.

#### Declared In

`PBDataLoggingService.h`

### –&nbsp;pollForData

Query the latestConnectedWatch for data logging data. ( **Deprecated:** Use pollForDataFromWatch:)

`- (void)pollForData`

#### Declared In

`PBDataLoggingService.h`

### –&nbsp;pollForDataFromWatch:

Query the watch for data logging data.

`- (void)pollForDataFromWatch:(PBWatch *)watch`

#### Parameters
_watch_The watch to query data from.

#### Declared In

`PBDataLoggingService.h`
