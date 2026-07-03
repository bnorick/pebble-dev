# PBWatch Class Reference

Source: https://developer.repebble.com/docs/pebblekit-ios/Classes/PBWatch/

| Inherits from | NSObject |
| Declared in | PBWatch.h |

## Overview

Represents a Pebble watch.

## Other Methods

### central

The central that is managing this watch.

`@property (nonatomic, weak, readonly) PBPebbleCentral *central`

#### Discussion

This property is KVO-compliant.

#### Declared In

`PBWatch.h`

### –&nbsp;isNew

YES if the receiver it’s the first time that watch has been seen.

`- (BOOL)isNew`

#### Discussion

This property is KVO-compliant.

#### Declared In

`PBWatch.h`

### connected

YES if the receiver is connected and NO if the receiver is disconnected.

`@property (nonatomic, assign, readonly, getter=isConnected) BOOL connected`

#### Discussion

This property is KVO-compliant.

#### Declared In

`PBWatch.h`

### name

The human-friendly name of the receiver. This is the same name as the user will see in the iOS Bluetooth Settings.

`@property (nonatomic, copy, readonly) NSString *name`

#### Declared In

`PBWatch.h`

### serialNumber

The serial number of the receiver.

`@property (nonatomic, copy, readonly) NSString *serialNumber`

#### Declared In

`PBWatch.h`

### versionInfo

The versionInfo of the receiver.

`@property (nonatomic, strong, readonly) PBVersionInfo *versionInfo`

#### See Also

- `PBVersionInfo`

#### Declared In

`PBWatch.h`

### delegate

The delegate of the watch that will be notified of disconnections and errors.

`@property (nonatomic, weak) id<PBWatchDelegate> __nullable delegate`

#### See Also

- `PBWatchDelegate`

#### Declared In

`PBWatch.h`

### userInfo

The userInfo property can be used to associate application specific data with the watch. Note that the application itself is responsible for persisting the information if neccessary.

`@property (nonatomic, strong) id __nullable userInfo`

#### Declared In

`PBWatch.h`

### lastConnectedDate

The date when the watch was last known to be [connected](#//api/name/connected). This date will be updated automatically when the watch connects and disconnects. While the watch is being [connected](#//api/name/connected), this date will not be updated.

`@property (nonatomic, strong, readonly) NSDate *lastConnectedDate`

#### Declared In

`PBWatch.h`

### –&nbsp;friendlyDescription

Developer-friendly debugging description of the watch.

`- (NSString *)friendlyDescription`

#### Return Value

developer-friendly summary of the receiver, including software and hardware version information, if available.

#### Declared In

`PBWatch.h`

### –&nbsp;releaseSharedSession

Releases the shared session to the watch (if one exists). ( **Deprecated:** Remove usages of this method. The implementation is empty.)

`- (void)releaseSharedSession`

#### Discussion

Depending on availability a per-app dedicated Bluetooth LE based session (CoreBluetooth.framework) will be used to talk to the watch. In other cases a Bluetooth Classic based session (ExternalAccessory.framework) will be used that is shared between all 3rd party iOS apps.

Once the user is done using the app/watch-integration, the shared sessions has to be released using this method so it can be used by other apps.

#### Declared In

`PBWatch.h`

## Golf Methods

### –&nbsp;golfGetIsSupported:

Queries the watch whether Golf Messages are supported.

`- (void)golfGetIsSupported:(void ( ^ ) ( PBWatch *watch , BOOL isGolfSupported ))fetchedBlock`

#### Parameters
_fetchedBlock_The block that will be called when the inquiry has finished. The block will be called asynchronously on the queue that was originally used when calling this method. watch: The watch on which the query was performed. isGolfSupported: YES if Golf Messages are supported, NO if not.

#### Discussion

Must be called from the main thread.

#### Declared In

`PBWatch+Golf.h`

### –&nbsp;golfAppLaunch:

Send a command to launch the golf app on the watch that the receiver represents.

`- (void)golfAppLaunch:(void ( ^ __nullable ) ( PBWatch *watch , NSError *__nullable error ))onSent`

#### Parameters
_onSent_The handler that will be called when the launch command has been sent or timed out (after 1.5 secs). watch: the recipient of the command. error: nil if the operation was successful, or else an NSError with more information on why it failed.

#### Discussion

Must be called from the main thread.

#### Declared In

`PBWatch+Golf.h`

### –&nbsp;golfAppKill:

Send a command to kill the golf app on the watch that the receiver represents.

`- (void)golfAppKill:(void ( ^ __nullable ) ( PBWatch *watch , NSError *__nullable error ))onSent`

#### Parameters
_onSent_The handler that will be called when the kill command has been sent or timed out (after 1.5 secs). watch: the recipient of the command. error: nil if the operation was successful, or else an NSError with more information on why it failed.

#### Discussion

Must be called from the main thread.

#### Declared In

`PBWatch+Golf.h`

### –&nbsp;golfAppUpdate:onSent:

Sends an update to the golf app on the watch that the receiver represents. Must be called from the main thread.

`- (void)golfAppUpdate:(NSDictionary *)update onSent:(void ( ^ __nullable ) ( PBWatch *watch , NSError *__nullable error ))onSent`

#### Parameters
_update_The update to send. Use one or more keys from PBGolfFrontKey, PBGolfMidKey, PBGolfBackKey, PBGolfHoleKey, or PBGolfParKey. Note that the value for each key MUST be of NSString type._onSent_The handler that will be called when the update has been sent or timed out (after 1.5 secs). watch: the recipient of the command. error: nil if the operation was successful, or else an NSError with more information on why it failed.

#### Declared In

`PBWatch+Golf.h`

### –&nbsp;golfAppAddReceiveUpdateHandler:

Add a receive handler for incoming Golf updates that are send by the Golf watch application.

`- (id)golfAppAddReceiveUpdateHandler:(BOOL ( ^ ) ( PBWatch *watch , GolfAppCommand command ))onReceive`

#### Parameters
_onReceive_The block that will be called every time a new update message arrives. watch: The receiver of the update. command: The command as sent by the watch.

#### Return Value

An opaque handle object representing the installed receive handler, that can be used in [golfAppRemoveUpdateHandler:](#//api/name/golfAppRemoveUpdateHandler:)

#### Discussion

Must be called from the main thread.

#### See Also

- `GolfAppCommand`
- `- golfAppRemoveUpdateHandler:`

#### Declared In

`PBWatch+Golf.h`

### –&nbsp;golfAppRemoveUpdateHandler:

Removes a receive handler that was previously installed using[golfAppAddReceiveUpdateHandler:](#//api/name/golfAppAddReceiveUpdateHandler:)

`- (void)golfAppRemoveUpdateHandler:(id)opaqueHandle`

#### Parameters
_opaqueHandle_The handle object as returned by golfAppAddReceiveUpdateHandler:

#### Discussion

Must be called from the main thread.

#### See Also

- `- golfAppAddReceiveUpdateHandler:`

#### Declared In

`PBWatch+Golf.h`

### –&nbsp;golfSetTitle:icon:onSent:

Assigns a custom title and icon to the golf app on the watch.

`- (void)golfSetTitle:(NSString *)title icon:(UIImage *)icon onSent:(void ( ^ __nullable ) ( PBWatch *watch , NSError *__nullable error ))onSent`

#### Parameters
_title_The custom title (max. 20 bytes of UTF-8 string)_icon_The custom icon (max. 32x32 pixels, black/white only)_onSent_The handler that will be called when the title and icon have been set or timed out. watch: the recipient of the title and icon. error: nil if the operation was successful, or else an NSError with more information on why it failed.

#### Discussion

Must be called from the main thread.

It is recommended to perform this as the first call after[golfGetIsSupported:](#//api/name/golfGetIsSupported:) to avoid changing the title and icon while it is being displayed in the menu as to avoid confusion.

#### Declared In

`PBWatch+Golf.h`

## Ping Methods

### –&nbsp;pingWithCookie:onPong:onTimeout:

Sends a ping to the watch.

`- (void)pingWithCookie:(uint32_t)cookie onPong:(void ( ^ __nullable ) ( PBWatch *watch , uint32_t cookie ))onPong onTimeout:(void ( ^__nullable ) ( PBWatch *watch , uint32_t cookie ))onTimeout`

#### Parameters
_cookie_A number identifying the ping._onPong_The block handler that will be called when the “pong” reply from the watch has been received._onTimeout_The block handler that will be called when the watch failed to reply in time.

#### Discussion

Must be called from the main thread.

#### Declared In

`PBWatch+Ping.h`

## SportsDeprecated Methods

### –&nbsp;sportsAppSetLabel:onSent:

Send a command to the sports app on the watch that the receiver represents, to set the preferred data label (either PACE or SPEED) and corresponding units. ( **Deprecated:** Prefer using [PBSportsUpdate pace] or [PBSportsUpdate speed].)

`- (void)sportsAppSetLabel:(BOOL)isPace onSent:(void ( ^ __nullable ) ( PBWatch *watch , NSError *__nullable error ))onSent`

#### Parameters
_isPace_YES to request the pace label or NO to request the speed label._onSent_The handler that will be called when the unit command has been sent or timed out (after 1.5 secs). watch: the recipient of the command. error: nil if the operation was successful, or else an NSError with more information on why it failed.

#### Discussion

Must be called from the main thread.

#### Declared In

`PBWatch+Sports.h`

### –&nbsp;sportsAppSetMetric:onSent:

Send a command to the sports app on the watch that the receiver represents, to set the preferred unit system, either metric or imperial. ( **Deprecated:** Prefer using [PBWatch(Sports) sportsAppSetUnitSystem:onSent:])

`- (void)sportsAppSetMetric:(BOOL)isMetric onSent:(void ( ^ __nullable ) ( PBWatch *watch , NSError *__nullable error ))onSent`

#### Parameters
_isMetric_YES to request metric units or NO to request imperial units._onSent_The handler that will be called when the unit command has been sent or timed out (after 1.5 secs). watch: the recipient of the command. error: nil if the operation was successful, or else an NSError with more information on why it failed.

#### Discussion

Must be called from the main thread.

#### Declared In

`PBWatch+Sports.h`

## AppMessages Methods

### –&nbsp;appMessagesGetIsSupported:

Queries the watch whether AppMessages are supported.

`- (void)appMessagesGetIsSupported:(void ( ^ ) ( PBWatch *watch , BOOL isAppMessagesSupported ))fetchedBlock`

#### Parameters
_fetchedBlock_The block that will be called when the inquiry has finished. The block will be called asynchronously on the queue that was originally used when calling this method. watch: The watch on which the query was performed. isAppMessagesSupported: YES if AppMessages are supported, NO if not.

#### Discussion

Must be called from the main thread.

#### Declared In

`PBWatch+AppMessages.h`

### –&nbsp;appMessagesPushUpdate:onSent:

Pushes an update to the watch application with UUID as set using[[PBPebbleCentral setAppUUID:]](../../Classes/PBPebbleCentral/#//api/name/appUUID).

`- (void)appMessagesPushUpdate:(NSDictionary<NSNumber*,id> *)dictionary onSent:(void ( ^ __nullable ) ( PBWatch *watch , NSDictionary *update , NSError *__nullable error ))onSent`

#### Parameters
_dictionary_Contains the key/value pairs to update. The dictionary can only contain items with an NSNumber key and only contain NSString, NSNumber or NSData values. Use the methods in the NSNumber (stdint) category to create NSNumbers with specific types standard integer types._onSent_The block that will be called when the message was accepted, rejected or timed out. watch: The watch to which the update was sent. update: The dictionary that was sent. error: If there was a problem, this will contain information about the underlying problem. See PBErrorCode for error codes.

#### Discussion

Must be called from the main thread.

#### Declared In

`PBWatch+AppMessages.h`

### –&nbsp;appMessagesPushUpdate:withUUID:onSent:

Pushes an update to the watch application with the specified UUID.

`- (void)appMessagesPushUpdate:(NSDictionary<NSNumber*,id> *)dictionary withUUID:(NSUUID *)appUUID onSent:(void ( ^ __nullable ) ( PBWatch *watch , NSDictionary *update , NSError *__nullable error ))onSent`

#### Parameters
_dictionary_Contains the key/value pairs to update. The dictionary can only contain items with an NSNumber key and only contain NSString, NSNumber or NSData values. Use the methods in the NSNumber (stdint) category to create NSNumbers with specific types standard integer types._appUUID_The UUID of the watchapp to which the update should be sent._onSent_The block that will be called when the message was accepted, rejected or timed out. watch: The watch to which the update was sent. update: The dictionary that was sent. error: If there was a problem, this will contain information about the underlying problem. See PBErrorCode for error codes.

#### Discussion

Must be called from the main thread.

#### Declared In

`PBWatch+AppMessages.h`

### –&nbsp;appMessagesAddReceiveUpdateHandler:

Add a receive handler for incoming updates that are send by the watch application with UUID as set using [[PBPebbleCentral setAppUUID:]](../../Classes/PBPebbleCentral/#//api/name/appUUID).

`- (id)appMessagesAddReceiveUpdateHandler:(BOOL ( ^ ) ( PBWatch *watch , NSDictionary<NSNumber*,id> *update ))onReceive`

#### Parameters
_onReceive_The block that will be called every time a new update message arrives. watch: The watch that has sent the update. update: The dictionary containing the values sent by the watch.

#### Return Value

An opaque handle object representing the installed receive handler, that can be used in [appMessagesRemoveUpdateHandler:](#//api/name/appMessagesRemoveUpdateHandler:)

#### Discussion

Must be called from the main thread.

#### See Also

- `- appMessagesRemoveUpdateHandler:`

#### Declared In

`PBWatch+AppMessages.h`

### –&nbsp;appMessagesAddReceiveUpdateHandler:withUUID:

Add a receive handler for incoming updates that are send by the watch application with the specified UUID.

`- (id)appMessagesAddReceiveUpdateHandler:(BOOL ( ^ ) ( PBWatch *watch , NSDictionary<NSNumber*,id> *update ))onReceive withUUID:(NSUUID *)appUUID`

#### Parameters
_onReceive_The block that will be called every time a new update message arrives. You should always return YES so than an ACK is sent to the watch. watch: The watch that has sent the update. update: The dictionary containing the values sent by the watch._appUUID_The UUID of the watchapp for which sent messages should be handled by the onReceive block.

#### Return Value

An opaque handle object representing the installed receive handler, that can be used in [appMessagesRemoveUpdateHandler:](#//api/name/appMessagesRemoveUpdateHandler:)

#### Discussion

Must be called from the main thread.

#### See Also

- `- appMessagesRemoveUpdateHandler:`

#### Declared In

`PBWatch+AppMessages.h`

### –&nbsp;appMessagesRemoveUpdateHandler:

Removes a receive handler that was previously installed using[appMessagesAddReceiveUpdateHandler:](#//api/name/appMessagesAddReceiveUpdateHandler:)

`- (void)appMessagesRemoveUpdateHandler:(id)opaqueHandle`

#### Parameters
_opaqueHandle_The handle object as returned by appMessagesAddReceiveUpdateHandler:

#### Discussion

Must be called from the main thread.

#### See Also

- `- appMessagesAddReceiveUpdateHandler:`

#### Declared In

`PBWatch+AppMessages.h`

### –&nbsp;appMessagesLaunch:

Sends a command to launch the watch application with UUID as set using[[PBPebbleCentral setAppUUID:]](../../Classes/PBPebbleCentral/#//api/name/appUUID)

`- (void)appMessagesLaunch:(void ( ^ __nullable ) ( PBWatch *watch , NSError *__nullable error ))onSent`

#### Parameters
_onSent_The block that will be called after the launch command has been sent to the watch. watch: The watch to which the command was sent. error: If there was a problem, this will contain information about the underlying problem. See PBErrorCode for error codes.

#### Discussion

Must be called from the main thread.

#### Declared In

`PBWatch+AppMessages.h`

### –&nbsp;appMessagesLaunch:withUUID:

Sends a command to launch the watch application with the specified UUID.

`- (void)appMessagesLaunch:(void ( ^ __nullable ) ( PBWatch *watch , NSError *__nullable error ))onSent withUUID:(NSUUID *)appUUID`

#### Parameters
_onSent_The block that will be called after the launch command has been sent to the watch. watch: The watch to which the command was sent. error: If there was a problem, this will contain information about the underlying problem. See PBErrorCode for error codes._appUUID_The UUID of the watch application to launch.

#### Discussion

Must be called from the main thread.

#### Declared In

`PBWatch+AppMessages.h`

### –&nbsp;appMessagesKill:

Sends a command to kill the watch application with UUID as set using[[PBPebbleCentral setAppUUID:]](../../Classes/PBPebbleCentral/#//api/name/appUUID).

`- (void)appMessagesKill:(void ( ^ __nullable ) ( PBWatch *watch , NSError *__nullable error ))onSent`

#### Parameters
_onSent_The block that will be called after the kill command has been sent to the watch. watch: The watch to which the command was sent. error: If there was a problem, this will contain information about the underlying problem. See PBErrorCode for error codes.

#### Discussion

Must be called from the main thread.

#### Declared In

`PBWatch+AppMessages.h`

### –&nbsp;appMessagesKill:withUUID:

Sends a command to kill the watch application with the specified UUID.

`- (void)appMessagesKill:(void ( ^ __nullable ) ( PBWatch *watch , NSError *__nullable error ))onSent withUUID:(NSUUID *)appUUID`

#### Parameters
_onSent_The block that will be called after the kill command has been sent to the watch. watch: The watch to which the command was sent. error: If there was a problem, this will contain information about the underlying problem. See PBErrorCode for error codes._appUUID_The UUID of the watch application to launch.

#### Discussion

Must be called from the main thread.

#### Declared In

`PBWatch+AppMessages.h`

## Legacy Methods

### –&nbsp;closeSession:

Closes the communication session with the watch. ( **Deprecated:** Use [PBWatch releaseSharedSession])

`- (void)closeSession:(void ( ^ __nullable ) ( void ))onDone`

#### Parameters
_onDone_Callback block that will be called after the closing of the session has completed. If there is no open session, the onDone block will (also) be executed asynchronously on the calling queue.

#### Discussion

Since there is only one, shared session for all 3rd party iOS apps, an app should close the session after the user is done using the app/watch-integration, so it can be used by other apps.

The communication session is implicitely opened automatically when needed.

#### Declared In

`PBWatch+Legacy.h`

## Sports Methods

### –&nbsp;sportsGetIsSupported:

Queries the watch whether Sports Messages are supported.

`- (void)sportsGetIsSupported:(void ( ^ ) ( PBWatch *watch , BOOL isSportsSupported ))fetchedBlock`

#### Parameters
_fetchedBlock_The block that will be called when the inquiry has finished. The block will be called asynchronously on the queue that was originally used when calling this method. watch: the recipient of the query. isSportsSupported: YES if Sports API is supported, NO otherwise.

#### Discussion

Must be called from the main thread.

#### Declared In

`PBWatch+Sports.h`

### –&nbsp;sportsAppLaunch:

Send a command to launch the sports app on the watch that the receiver represents.

`- (void)sportsAppLaunch:(void ( ^ __nullable ) ( PBWatch *watch , NSError *__nullable error ))onSent`

#### Parameters
_onSent_The handler that will be called when the launch command has been sent or timed out (after 1.5 secs). watch: the recipient of the command. error: nil if the operation was successful, or else an NSError with more information on why it failed.

#### Discussion

Must be called from the main thread, and before [sportsAppSetMetric:onSent:](#//api/name/sportsAppSetMetric:onSent:)or [sportsAppUpdate:onSent:](#//api/name/sportsAppUpdate:onSent:).

#### Declared In

`PBWatch+Sports.h`

### –&nbsp;sportsAppKill:

Send a command to kill the sports app on the watch that the receiver represents.

`- (void)sportsAppKill:(void ( ^ __nullable ) ( PBWatch *watch , NSError *__nullable error ))onSent`

#### Parameters
_onSent_The handler that will be called when the kill command has been sent or timed out (after 1.5 secs). watch: the recipient of the command. error: nil if the operation was successful, or else an NSError with more information on why it failed.

#### Discussion

Must be called from the main thread.

#### Declared In

`PBWatch+Sports.h`

### –&nbsp;sportsAppSetUnitSystem:onSent:

Send a command to the sports app on the watch that the receiver represents, to set the preferred unit system.

`- (void)sportsAppSetUnitSystem:(PBUnitSystem)unitSystem onSent:(void ( ^ __nullable ) ( PBWatch *watch , NSError *__nullable error ))onSent`

#### Parameters
_unitSystem_PBUnitSystemMetric to request metric units or PBUnitSystemImperial to request imperial units._onSent_The handler that will be called when the unit command has been sent or timed out (after 1.5 secs). watch: the recipient of the command. error: nil if the operation was successful, or else an NSError with more information on why it failed.

#### Discussion

Must be called from the main thread.

#### Declared In

`PBWatch+Sports.h`

### –&nbsp;sportsAppSetActivityState:onSent:

Send a command to the sports app on the watch that the receiver represents, to set the state of the sports activity. Currently only`SportsAppActivityStateRunning` and `SportsAppActivityStatePaused` are supported.

`- (void)sportsAppSetActivityState:(SportsAppActivityState)state onSent:(void ( ^ __nullable ) ( PBWatch *watch , NSError *__nullable error ))onSent`

#### Parameters
_state_The new sports activity state_onSent_The handler that will be called when the unit command has been sent or timed out (after 1.5 secs). watch: the recipient of the command. error: nil if the operation was successful, or else an NSError with more information on why it failed.

#### Discussion

Must be called from the main thread.

#### Declared In

`PBWatch+Sports.h`

### –&nbsp;sportsAppUpdate:onSent:

Sends the update to the sports app on the watch that the receiver represents.

`- (void)sportsAppUpdate:(NSDictionary *)update onSent:(void ( ^ __nullable ) ( PBWatch *watch , NSError *__nullable error ))onSent`

#### Parameters
_update_The update to send._onSent_The handler that will be called when the unit command has been sent or timed out (after 1.5 secs). watch: the recipient of the command. error: nil if the operation was successful, or else an NSError with more information on why it failed.

#### Discussion

Must be called from the main thread.

The valid keys and values for the dictionary are the following:

- `PBSportsTimeKey`: the string representing the time. The value must be an`NSString`. The maximum number of characters is about 8.
- `PBSportsDistanceKey`: the string representing the distance. The value must be an `NSString`. The maximum number of characters is about 5.
- `PBSportsDataKey`: the string representing the pace or the speed. The value must be an `NSString`. The maximum number of characters is about 5.
- `PBSportsActivityStateKey`: the state of the activity. The value must be an`NSNumber` created using +[NSNumber(stdint) pb\_numberWithUint8:]. The value must be one of the values from the enum [SportsAppActivityState](../../Constants/SportsAppActivityState/).
- `PBSportsIsPaceKey`: whether the value sent in `PBSportsDataKey` is the pace (use value 1) or the speed (use value 0). You don’t need to continously send this value. The value must be an `NSNumber` created using +[NSNumber(stdin) pb\_numberWithUint8:].
- `PBSportsHeartBPMKey`: the current heart rate in beats per minute. The value must be an `NSNumber` created using [NSNumber(stdin) pb\_numberWithUint8:].
- `PBSportsCustomLabelKey`: the string to show as a custom label. The value must be an `NSString`. The maximum number of characters is about 10. The string will be transformed into upper case before being sent to the watch.
- `PBSportsCustomValueKey`: the string to show as a custom value. The value must be an `NSString`. The maximum number of characters is about 8.

#### Declared In

`PBWatch+Sports.h`

### –&nbsp;sportsAppAddReceiveUpdateHandler:

Add a receive handler for incoming Sports updates that are send by the Sports watch application.

`- (id)sportsAppAddReceiveUpdateHandler:(BOOL ( ^ ) ( PBWatch *watch , SportsAppActivityState state ))onReceive`

#### Parameters
_onReceive_The block that will be called every time a new update message arrives. watch: The watch that has sent the update. state: The new sports activity state as set by the watch.

#### Return Value

An opaque handle object representing the installed receive handler, that can be used in [sportsAppRemoveUpdateHandler:](#//api/name/sportsAppRemoveUpdateHandler:).

#### Discussion

Must be called from the main thread.

#### See Also

- `SportsAppActivityState`
- `- sportsAppRemoveUpdateHandler:`

#### Declared In

`PBWatch+Sports.h`

### –&nbsp;sportsAppRemoveUpdateHandler:

Removes a receive handler that was previously installed using[sportsAppAddReceiveUpdateHandler:](#//api/name/sportsAppAddReceiveUpdateHandler:).

`- (void)sportsAppRemoveUpdateHandler:(id)opaqueHandle`

#### Parameters
_opaqueHandle_The handle object as returned by sportsAppAddReceiveUpdateHandler:

#### Discussion

Must be called from the main thread.

#### See Also

- `- sportsAppAddReceiveUpdateHandler:`

#### Declared In

`PBWatch+Sports.h`

### –&nbsp;sportsSetTitle:icon:onSent:

Assigns a custom title and icon to the sports app on the watch.

`- (void)sportsSetTitle:(NSString *)title icon:(UIImage *)icon onSent:(void ( ^ __nullable ) ( PBWatch *watch , NSError *__nullable error ))onSent`

#### Parameters
_title_The custom title (max. 20 bytes of UTF-8 string)_icon_The custom icon (max. 32x32 pixels, black/white only). This image cannot be nil._onSent_The handler that will be called when the title and icon have been set or timed out. watch: the recipient of the custom title and icon. error: nil if the operation was successful, or else an NSError with more information on why it failed.

#### Discussion

Must be called from the main thread.

It is recommended to perform this as the first call after[sportsGetIsSupported:](#//api/name/sportsGetIsSupported:) to avoid changing the title and icon while it is being displayed in the menu as to avoid confusion.

#### Declared In

`PBWatch+Sports.h`
