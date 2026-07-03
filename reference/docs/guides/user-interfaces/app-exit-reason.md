# App Exit Reason

Source: https://developer.repebble.com/guides/user-interfaces/app-exit-reason/

Introduced in SDK v4.0, the [`AppExitReason`](/docs/c/Foundation/Exit_Reason/#AppExitReason "AppExitReason") API allows developers to provide a reason when terminating their application. The system uses these reasons to determine where the user should be sent when the current application terminates.

At present, there are only two [`AppExitReason`](/docs/c/Foundation/Exit_Reason/#AppExitReason "AppExitReason") states when exiting an application, but this may change in future updates.

### APP\_EXIT\_NOT\_SPECIFIED

This is the default state and when the current watchapp terminates. The user is returned to their previous location. If you do not specify an [`AppExitReason`](/docs/c/Foundation/Exit_Reason/#AppExitReason "AppExitReason"), this state will be used automatically.

```
static void prv\_deinit() {// Optional, default behavior// App will exit to the previous location in the systemexit\_reason\_set(APP\_EXIT\_NOT\_SPECIFIED);}
```

### APP\_EXIT\_ACTION\_PERFORMED\_SUCCESSFULLY

This state is primarily provided for developers who are creating one click action applications. When the current watchapp terminates, the user is returned to the default watchface.

```
static void prv\_deinit() {// App will exit to default watchfaceexit\_reason\_set(APP\_EXIT\_ACTION\_PERFORMED\_SUCCESSFULLY);}
```
