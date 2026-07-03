# PBPebbleCentral Class Reference

Source: https://developer.repebble.com/docs/pebblekit-ios/Classes/PBPebbleCentral/

| Inherits from | NSObject |
| Declared in | PBPebbleCentral.h |

## Overview

PebbleCentral plays the central role for client iOS apps (e.g. RunKeeper).

## Other Methods

### connectedWatches

The watches that are currently connected. Do not cache the array because it can change over time.

`@property (nonatomic, readonly, copy) NSArray<PBWatch*> *connectedWatches`

#### Declared In

`PBPebbleCentral.h`

### registeredWatches

The watches that are stored in the user preferences of the application.

`@property (nonatomic, readonly, copy) NSArray<PBWatch*> *registeredWatches`

#### Declared In

`PBPebbleCentral.h`

### delegate

The central’s delegate.

`@property (nonatomic, readwrite, weak) id<PBPebbleCentralDelegate> __nullable delegate`

#### Declared In

`PBPebbleCentral.h`

### appUUID

Identifier of the watch application this companion app communicates with.

`@property (nonatomic, copy) NSUUID *appUUID`

#### Discussion

The identifier is used to make sure that app message and data logging communications arrive to the right companion watch app in the watch (and not to another app).

For most app message methods there is are two variants: one that does not take an UUID parameter and one that does (for example, -appMessagesAddReceiveUpdateHandler: vs -appMessagesAddReceiveUpdateHandler:withUUID:). The methods that do not take an UUID, will use the UUID as set prior to this property.

**Note:** The UUID needs to be set before using either app message or data logging.

#### Declared In

`PBPebbleCentral.h`

### appUUIDs

The list of App-UUIDs this PebbleCentral wants to talk to.

`@property (nonatomic, copy) NSSet<NSUUID*> *appUUIDs`

#### See Also

- `- addAppUUID:`

#### Declared In

`PBPebbleCentral.h`

### –&nbsp;addAppUUID:

Registers a new App-UUID with [appUUIDs](#//api/name/appUUIDs).

`- (void)addAppUUID:(NSUUID *)appUUID`

#### Parameters
_appUUID_The app UUID to register.

#### See Also

- `@property appUUIDs`

#### Declared In

`PBPebbleCentral.h`

### –&nbsp;run

Registers and announces internal Bluetooth services. Might cause a dialog to allow this app to talk to other devices.

`- (void)run`

#### Declared In

`PBPebbleCentral.h`

### –&nbsp;isMobileAppInstalled

Determines if the Pebble iOS app is installed in the device.

`- (BOOL)isMobileAppInstalled`

#### Return Value

`YES` if the Pebble iOS app is installed, `NO` if it is not installed.

#### Discussion

**Note:** Since iOS 9.0 you have to add “pebble” to `LSApplicationQueriesSchemes` in your application `Info.plist` or this method will return `NO` all the time.

#### Declared In

`PBPebbleCentral.h`

### –&nbsp;installMobileApp

Redirects to Pebble in the App Store, so the user can install the app.

`- (void)installMobileApp`

#### Declared In

`PBPebbleCentral.h`

### –&nbsp;unregisterAllWatches

Wipes out the data associated with the registered watches, that is stored on the phone.

`- (void)unregisterAllWatches`

#### Declared In

`PBPebbleCentral.h`

### –&nbsp;lastConnectedWatch

Returns the most recently connected watch from the [registeredWatches](#//api/name/registeredWatches) array.

`- (PBWatch *__nullable)lastConnectedWatch`

#### Declared In

`PBPebbleCentral.h`

### –&nbsp;dataLoggingServiceForAppUUID:

Returns the DataLoggingService for a (previously registered) [appUUID](#//api/name/appUUID)

`- (PBDataLoggingService *__nullable)dataLoggingServiceForAppUUID:(NSUUID *)appUUID`

#### Parameters
_appUUID_The app UUID to recover the data logging service.

#### Declared In

`PBPebbleCentral.h`

## DefaultCentral Methods

### +&nbsp;defaultCentral

The default central singleton instance.

`+ (instancetype)defaultCentral`

#### Return Value

The default central singleton instance.

#### Declared In

`PBPebbleCentral+DefaultCentral.h`

## Legacy Methods

### –&nbsp;hasValidAppUUID

Indicates if the central has been correctly configured with an app UUID. ( **Deprecated:** Use `appUUID != nil` instead.)

`- (BOOL)hasValidAppUUID`

#### Declared In

`PBPebbleCentral+Legacy.h`

### +&nbsp;setDebugLogsEnabled:

Enables or disables debug logging for PebbleKit. ( **Deprecated:** Use `+[PBPebbleKitLogging setLogLevel:]` instead.)

`+ (void)setDebugLogsEnabled:(BOOL)logsEnabled`

#### Parameters
_logsEnabled_Whether logging should be enabled or not.

#### Declared In

`PBPebbleCentral+Legacy.h`

### +&nbsp;setLogLevel:

Configures which events should be logged. ( **Deprecated:** Use `+[PBPebbleKitLogging setLogLevel:]` instead.)

`+ (void)setLogLevel:(PBPebbleKitLogLevel)logLevel`

#### Parameters
_logLevel_One of the values in PBPebbleKitLogLevel, which will be the maximum level that will be logged. You can use PBPebbleKitLogLevelOff to disable all logging.

#### Declared In

`PBPebbleCentral+Legacy.h`

### dataLoggingService

Use [`dataLoggingServiceForAppUUID:`](#//api/name/dataLoggingServiceForAppUUID:) instead. ( **Deprecated:** Use `dataLoggingServiceForAppUUID:` instead.)

`@property (nonatomic, readonly) PBDataLoggingService *dataLoggingService`

#### Declared In

`PBPebbleCentral+Legacy.h`
