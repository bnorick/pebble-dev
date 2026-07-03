# Foundation

Source: https://developer.repebble.com/docs/c/Foundation/index.html

The core of the Pebble SDK.

The Pebble SDK consists of different frameworks that are organized by functionality. Each framework includes an API and provides access to the software libraries supported natively by Pebble OS. You use these interfaces (APIs) in the C programming language to write software for the Pebble platform.

Frameworks are grouped hierarchically into Foundation, Graphics, Standard C and User Interface.

The Foundation framework is the core of the Pebble OS.

## Modules

#### [Alloy](/docs/c/Foundation/Alloy/)

&nbsp;

#### [App](/docs/c/Foundation/App/)

App entry point and event loop.

#### [App Communication](/docs/c/Foundation/App_Communication/)

API for interacting with the Pebble communication subsystem.

#### [App Glance](/docs/c/Foundation/App_Glance/)

API for the application to modify its "glance" i.e. app menu subtitle.

#### [AppMessage](/docs/c/Foundation/AppMessage/)

&nbsp;

#### [AppSync](/docs/c/Foundation/AppSync/)

UI synchronization layer for AppMessage

#### [AppWorker](/docs/c/Foundation/AppWorker/)

Runs in the background, and can communicate with the foreground app.

#### [DataLogging](/docs/c/Foundation/DataLogging/)

Enables logging data asynchronously to a mobile app

#### [DataStructures](/docs/c/Foundation/DataStructures/)

&nbsp;

#### [Dictation](/docs/c/Foundation/Dictation/)

&nbsp;

#### [Dictionary](/docs/c/Foundation/Dictionary/)

Data serialization utilities

#### [Event Service](/docs/c/Foundation/Event_Service/)

APIs to handle event services.

#### [Exit Reason](/docs/c/Foundation/Exit_Reason/)

API for the application to notify the system of the reason it will exit.

#### [Internationalization](/docs/c/Foundation/Internationalization/)

Internationalization & Localization APIs

#### [Launch Reason](/docs/c/Foundation/Launch_Reason/)

API for checking what caused the application to launch.

#### [Logging](/docs/c/Foundation/Logging/)

Functions related to logging from apps.

#### [Math](/docs/c/Foundation/Math/)

Math routines.

#### [Memory Management](/docs/c/Foundation/Memory_Management/)

Utility functions for managing an application's memory.

#### [Platform](/docs/c/Foundation/Platform/)

&nbsp;

#### [Resources](/docs/c/Foundation/Resources/)

Managing application resources

#### [Storage](/docs/c/Foundation/Storage/)

A mechanism to store persistent application data and state

#### [Timer](/docs/c/Foundation/Timer/)

Can be used to execute some code at some point in the future.

#### [Wakeup](/docs/c/Foundation/Wakeup/)

Allows applications to schedule to be launched even if they are not running.

#### [Wall Time](/docs/c/Foundation/Wall_Time/)

Functions, data structures and other things related to wall clock time.

#### [WatchInfo](/docs/c/Foundation/WatchInfo/)

Provides information about the watch itself.
