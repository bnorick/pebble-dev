# Exit Reason

Source: https://developer.repebble.com/docs/c/Foundation/Exit_Reason/index.html

API for the application to notify the system of the reason it will exit.

If the application has not specified an exit reason before it exits, then the exit reason will default to APP\_EXIT\_NOT\_SPECIFIED.

Only an application can set its exit reason. The system will not modify it.

## Function Documentation

void exit\_reason\_set([AppExitReason](/docs/c/Foundation/Exit_Reason/#AppExitReason) exit\_reason)

Set the app exit reason to a new reason.

#### Parameters
 reason

The new app exit reason

## Enum Documentation

enum AppExitReason

[AppExitReason](/docs/c/Foundation/Exit_Reason/#AppExitReason) is used to notify the system of the reason of an application exiting, which may affect the part of the system UI that is presented after the application terminates.

#### Enumerators
APP\_EXIT\_NOT\_SPECIFIED

Exit reason not specified.

APP\_EXIT\_ACTION\_PERFORMED\_SUCCESSFULLY

Application performed an action when it exited.

NUM\_EXIT\_REASONS

Number of [AppExitReason](/docs/c/Foundation/Exit_Reason/#AppExitReason) options.
