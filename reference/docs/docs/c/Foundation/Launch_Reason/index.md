# Launch Reason

Source: https://developer.repebble.com/docs/c/Foundation/Launch_Reason/index.html

API for checking what caused the application to launch.

This includes the system, launch by user interaction (User selects the application from the launcher menu), launch by the mobile or a mobile companion application, or launch by a scheduled wakeup event for the specified application.

## Function Documentation

[AppLaunchReason](/docs/c/Foundation/Launch_Reason/#AppLaunchReason) launch\_reason(void)

Provides the method used to launch the current application.

#### Returns

The method or reason the current application was launched

[uint32\_t](/docs/c/Standard_C/#uint32_t) launch\_get\_args(void)

Get the argument passed to the app when it was launched.

##### Note

Currently the only way to pass arguments to apps is by using an openWatchApp action on a pin.

#### Returns

The argument passed to the app, or 0 if the app wasn't launched from a Launch App action

## Enum Documentation

enum AppLaunchReason

[AppLaunchReason](/docs/c/Foundation/Launch_Reason/#AppLaunchReason) is used to inform the application about how it was launched.

New launch reasons may be added in the future. As a best practice, it is recommended to only handle the cases that the app needs to know about, rather than trying to handle all possible launch reasons.

#### Enumerators
APP\_LAUNCH\_SYSTEM

App launched by the system.

APP\_LAUNCH\_USER

App launched by user selection in launcher menu.

APP\_LAUNCH\_PHONE

App launched by mobile or companion app.

APP\_LAUNCH\_WAKEUP

App launched by wakeup event.

APP\_LAUNCH\_WORKER

App launched by worker calling [worker\_launch\_app()](/docs/c/Worker/#worker_launch_app)

APP\_LAUNCH\_QUICK\_LAUNCH

App launched by user using quick launch.

APP\_LAUNCH\_TIMELINE\_ACTION

App launched by user opening it from a pin.

APP\_LAUNCH\_SMARTSTRAP

App launched by a smartstrap.
