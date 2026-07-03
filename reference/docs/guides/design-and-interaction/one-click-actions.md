# One Click Actions

Source: https://developer.repebble.com/guides/design-and-interaction/one-click-actions/

One click actions are set to revolutionize the way users interact with their Pebble by providing instant access to their favorite one click watchapps, directly from the new system launcher. Want to unlock your front door? Call an Uber? Or perhaps take an instant voice note? With one click actions, the user is able to instantly perform a single action by launching an app, and taking no further action.

![Lockitron](/assets/images/guides/design-and-interaction/lockitron.png)

### The One Click Flow

It’s important to develop your one click application with a simple and elegant flow. You need to simplify the process of your application by essentially creating an application which serves a single purpose.

The typical flow for a one click application would be as follows:

1. Application is launched
2. Application performs action
3. Application displays status to user
4. Application automatically exits to watchface if the action was successful, or displays status message and does not exit if the action failed

If we were creating an instant voice note watchapp, the flow could be as follows:

1. Application launched
2. Application performs action (take a voice note)
  1. Start listening for dictation
  2. Accept dictation response
3. Application displays a success message
4. Exit to watchface

In the case of a one click application for something like Uber, we would need to track the state of any existing booking to prevent ordering a second car. We would also want to update the [`App Glance`](/docs/c/Foundation/App_Glance/ "App Glance")as the status of the booking changes.

1. Application launched
2. If a booking exists:
  1. Refresh booking status
  2. Update [`App Glance`](/docs/c/Foundation/App_Glance/ "App Glance") with new status
  3. Exit to watchface
3. Application performs action (create a booking)
  1. Update AppGlance: “Your Uber is on it’s way”
  2. Application displays a success message
  3. Exit to watchface

### Building a One Click Application

For this example, we’re going to build a one click watchapp which will lock or unlock the front door of our virtual house. We’re going to use a virtual[Lockitron](https://lockitron.com/), or a real one if you’re lucky enough to have one.

Our flow will be incredibly simple:

1. Launch the application
2. Take an action (toggle the state of the lock)
3. Update the [`App Glance`](/docs/c/Foundation/App_Glance/ "App Glance") to indicate the new lock state
4. Display a success message
5. Exit to watchface

For the sake of simplicity in our example, we will not know if someone else has locked or unlocked the door using a different application. You can investigate the [Lockitron API](http://api.lockitron.com) if you want to develop this idea further.

In order to control our Lockitron, we need the UUID of the lock and an access key. You can generate your own virtual lockitron UUID and access code on the[Lockitron website](https://api.lockitron.com/v1/getting_started/virtual_locks).

```
#define LOCKITRON\_LOCK\_UUID "95c22a11-4c9e-4420-adf0-11f1b36575f2"#define LOCKITRON\_ACCESS\_TOKEN "99e75a775fe737bb716caf88f161460bb623d283c3561c833480f0834335668b"
```

> Never publish your actual Lockitron access token in the appstore, unless you want strangers unlocking your door! Ideally you would make these fields configurable using [Clay for Pebble](https://github.com/pebble-dev/clay).

We’re going to need a simple enum for the state of our lock, where 0 is unlocked, 1 is locked and anything else is unknown.

```
typedef enum {LOCKITRON\_UNLOCKED,LOCKITRON\_LOCKED,LOCKITRON\_UNKNOWN} LockitronLockState;
```

We’re also going to use a static variable to keep track of the state of our lock.

```
static LockitronLockState s\_lockitron\_state;
```

When our application launches, we’re going to initialize [`AppMessage`](/docs/c/Foundation/AppMessage/ "AppMessage") and then wait for PebbleKit JS to tell us it’s ready.

```
static void prv\_init(void) {app\_message\_register\_inbox\_received(prv\_inbox\_received\_handler);app\_message\_open(256, 256);s\_window = window\_create();window\_stack\_push(s\_window, false);}static void prv\_inbox\_received\_handler(DictionaryIterator \*iter, void \*context) {Tuple \*ready\_tuple = dict\_find(iter, MESSAGE\_KEY\_APP\_READY);if (ready\_tuple) {// PebbleKit JS is ready, toggle the Lockitron!prv\_lockitron\_toggle\_state();return;}// ...}
```

In order to toggle the state of the Lockitron, we’re going to send an[`AppMessage`](/docs/c/Foundation/AppMessage/ "AppMessage") to PebbleKit JS, containing our UUID and our access key.

```
static void prv\_lockitron\_toggle\_state() {DictionaryIterator \*out;AppMessageResult result = app\_message\_outbox\_begin(&out);dict\_write\_cstring(out, MESSAGE\_KEY\_LOCK\_UUID, LOCKITRON\_LOCK\_UUID);dict\_write\_cstring(out, MESSAGE\_KEY\_ACCESS\_TOKEN, LOCKITRON\_ACCESS\_TOKEN);result = app\_message\_outbox\_send();}
```

PebbleKit JS will handle this request and make the relevant ajax request to the Lockitron API. It will then return the current state of the lock and tell our application to exit back to the default watchface using[`AppExitReason`](/docs/c/Foundation/Exit_Reason/#AppExitReason "AppExitReason"). See the[full example](https://github.com/pebble-examples/one-click-action-example) for the actual Javascript implementation.

```
static void prv\_inbox\_received\_handler(DictionaryIterator \*iter, void \*context) {// ...Tuple \*lock\_state\_tuple = dict\_find(iter, MESSAGE\_KEY\_LOCK\_STATE);if (lock\_state\_tuple) {// Lockitron state has changeds\_lockitron\_state = (LockitronLockState)lock\_state\_tuple-\>value-\>int32;// App will exit to default watchfaceapp\_exit\_reason\_set(APP\_EXIT\_ACTION\_PERFORMED\_SUCCESSFULLY);// Exit the application by unloading the only windowwindow\_stack\_remove(s\_window, false);}}
```

Before our application terminates, we need to update the[`App Glance`](/docs/c/Foundation/App_Glance/ "App Glance") with the current state of our lock. We do this by passing our current lock state into the[`app_glance_reload`](/docs/c/Foundation/App_Glance/#app_glance_reload "app\_glance\_reload") method.

```
static void prv\_deinit(void) {window\_destroy(s\_window);// Before the application terminates, setup the AppGlanceapp\_glance\_reload(prv\_update\_app\_glance, &s\_lockitron\_state);}
```

We only need a single [`AppGlanceSlice`](/docs/c/Foundation/App_Glance/#AppGlanceSlice "AppGlanceSlice") for our [`App Glance`](/docs/c/Foundation/App_Glance/ "App Glance"), but it’s worth noting you can have multiple slices with varying expiration times.

```
static void prv\_update\_app\_glance(AppGlanceReloadSession \*session, size\_t limit, void \*context) {// Check we haven't exceeded system limit of AppGlancesif (limit \< 1) return;// Retrieve the current Lockitron state from contextLockitronLockState \*lockitron\_state = context;// Generate a friendly message for the current Lockitron statechar \*str = prv\_lockitron\_status\_message(lockitron\_state);APP\_LOG(APP\_LOG\_LEVEL\_INFO, "STATE: %s", str);// Create the AppGlanceSlice (no icon, no expiry)const AppGlanceSlice entry = (AppGlanceSlice) {.layout = {.template\_string = str},.expiration\_time = time(NULL)+3600};// Add the slice, and check the resultconst AppGlanceResult result = app\_glance\_add\_slice(session, entry);if (result != APP\_GLANCE\_RESULT\_SUCCESS) {APP\_LOG(APP\_LOG\_LEVEL\_ERROR, "AppGlance Error: %d", result);}}
```

### Handling Launch Reasons

In the example above, we successfully created an application that will automatically execute our One Click Action when the application is launched. But we also need to be aware of some additional launch reasons where it would not be appropriate to perform the action.

By using the [`launch_reason()`](/docs/c/Foundation/Launch_Reason/#launch_reason "launch\_reason") method, we can detect why our application was started and prevent the One Click Action from firing unnecessarily.

A common example, would be to detect if the application was actually started by the user, from either the launcher, or quick launch.

```
if(launch\_reason() == APP\_LAUNCH\_USER || launch\_reason() == APP\_LAUNCH\_QUICK\_LAUNCH) {// Perform One Click} else {// Display a message}
```

### Conclusion

As you can see, it’s a relatively small amount of code to create one click watchapps and we hope this inspires you to build your own!

We recommend that you check out the complete[Lockitron sample](https://github.com/pebble-examples/one-click-action-example)application and also the [`App Glance`](/docs/c/Foundation/App_Glance/ "App Glance") and [`AppExitReason`](/docs/c/Foundation/Exit_Reason/#AppExitReason "AppExitReason") guides for further information.
