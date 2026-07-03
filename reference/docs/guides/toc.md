# Guides Table of Contents

Source: https://developer.repebble.com/guides/toc/

## [1. Alloy](/guides/alloy.md)

Information on creating apps with JavaScript using the Alloy framework, based on Moddable.

#### [Getting Started with Alloy](/guides/alloy/getting-started.md)

Learn how to create your first Alloy app for Pebble.

#### [Piu UI Framework](/guides/alloy/piu-guide.md)

Build declarative user interfaces with the Piu framework.

#### [Poco Graphics](/guides/alloy/poco-guide.md)

Low-level graphics rendering with the Poco framework.

#### [Sensors and Input](/guides/alloy/sensors-and-input.md)

Access Pebble sensors and handle button input in Alloy apps.

#### [Storage](/guides/alloy/storage.md)

Persist data between app launches using localStorage, key-value storage, or files.

#### [Networking](/guides/alloy/networking.md)

Make HTTP requests and use WebSockets via the phone proxy.

#### [App Messages](/guides/alloy/app-messages.md)

Send and receive messages between the watch and the phone.

#### [Watchfaces](/guides/alloy/watchfaces.md)

Build custom watchfaces with Alloy.

#### [Animations](/guides/alloy/animations.md)

Create smooth animations using Timeline and easing functions.

#### [Port (Custom Drawing)](/guides/alloy/port-drawing.md)

Combine Piu's declarative UI with custom drawing using Port.

#### [Advanced Networking](/guides/alloy/advanced-networking.md)

Low-level HTTP and WebSocket clients for advanced networking needs.

## [2. App Resources](/guides/app-resources.md)

Information on the many kinds of files that can be used inside Pebble apps.

#### [Animated Images](/guides/app-resources/animated-images.md)

How to add animated image resources to a project in the APNG format, and display them in your app.

#### [App Assets](/guides/app-resources/app-assets.md)

A collection of assets for use as resources in Pebble apps.

#### [Converting SVG to PDC](/guides/app-resources/converting-svg-to-pdc.md)

How to create compatible SVG files using Inkscape and Illustrator.

#### [Fonts](/guides/app-resources/fonts.md)

How to use built-in system fonts, or add your own font resources to a project.

#### [Images](/guides/app-resources/images.md)

How to add image resources to a project and display them in your app.

#### [Pebble Draw Command File Format](/guides/app-resources/pdc-format.md)

The binary file format description for Pebble Draw Command Frames, Images and Sequences.

#### [Platform-specific Resources](/guides/app-resources/platform-specific.md)

How to include different resources for different platforms, as well as how to include a resource only on a particular platform.

#### [Raw Data Files](/guides/app-resources/raw-data-files.md)

How to add raw data resources to a project and read them in your app.

#### [System Fonts](/guides/app-resources/system-fonts.md)

A complete list of all the system fonts available for use in Pebble projects.

## [3. Best Practices](/guides/best-practices.md)

Information to help optimize apps and ensure a good user experience.

#### [Building for Every Pebble](/guides/best-practices/building-for-every-pebble.md)

How to write one app compatible with all Pebble smartwatches.

#### [Conserving Battery Life](/guides/best-practices/conserving-battery-life.md)

How to write an app to consume power as efficiently as possible.

#### [Modular App Architecture](/guides/best-practices/modular-app-architecture.md)

How to break up a complex app into smaller pieces for managablilty, modularity and reusability.

## [4. Communication](/guides/communication.md)

How to talk to the phone via PebbleKit with JavaScript and on Android or iOS.

#### [Advanced Communication](/guides/communication/advanced-communication.md)

Details of communication tips and best practices for more advanced scenarios.

#### [Datalogging](/guides/communication/datalogging.md)

Information on how to collect data batches using the Datalogging API.

#### [PebbleKit Android](/guides/communication/using-pebblekit-android.md)

How to use PebbleKit to communicate with a watchapp on Android.

#### [PebbleKit JS](/guides/communication/using-pebblekit-js.md)

How to use PebbleKit JS to communicate with the connected phone's JS environment.

#### [PebbleKit iOS](/guides/communication/using-pebblekit-ios.md)

How to use PebbleKit to communicate with a watchapp on iOS.

#### [Sending and Receiving Data](/guides/communication/sending-and-receiving-data.md)

How to send and receive data between your watchapp and phone.

#### [Sports API](/guides/communication/using-the-sports-api.md)

How to use the PebbleKit Sports API to integrate your mobile sports app with Pebble.

## [5. Debugging](/guides/debugging.md)

How to find and fix common compilation and runtime problems in apps.

#### [Common Runtime Errors](/guides/debugging/common-runtime-errors.md)

Examples of commonly encountered runtime problems that cannot be detected at compile time and can usually be fixed by logical thought and experimentation.

#### [Common Syntax Errors](/guides/debugging/common-syntax-errors.md)

Details of common problems encountered when writing C apps for Pebble, and how to resolve them.

#### [Debugging with App Logs](/guides/debugging/debugging-with-app-logs.md)

How to use the app logs to debug problems with an app, as well as tips on interpreting common run time errors.

#### [Debugging with GDB](/guides/debugging/debugging-with-gdb.md)

How to use GDB to debug a Pebble app in the emulator.

## [6. Design and Interaction](/guides/design-and-interaction.md)

Information on creating the best app user experiences and layout designs.

#### [Benefits of Design Guidelines](/guides/design-and-interaction/benefits.md)

Learn the main concepts of design guidelines, why they are needed, and how they can help developers.

#### [Core Experience Design](/guides/design-and-interaction/core-experience.md)

How design guidelines shape the core Pebble app experience.

#### [One Click Actions](/guides/design-and-interaction/one-click-actions.md)

Details about how to create One Click Action watchapps

#### [Recommended Guidelines and Patterns](/guides/design-and-interaction/recommended.md)

Pebble's recommended guidelines for creating awesome app experiences.

#### [Round App Design](/guides/design-and-interaction/in-the-round.md)

Tips and advice for designing apps that take advantage of the Pebble Time Round display

#### [Example Implementations](/guides/design-and-interaction/implementation.md)

Resources and code samples to implement common design and UI patterns.

## [7. Events and Services](/guides/events-and-services.md)

How to get data from the onboard sensors and services including the accelerometer, compass, and microphone.

#### [Accelerometer](/guides/events-and-services/accelerometer.md)

How to use data and simple tap gestures from the onboard accelerometer.

#### [Background Worker](/guides/events-and-services/background-worker.md)

Using the Background Worker to do work in the background, such as activity tracking.

#### [Backlight](/guides/events-and-services/light.md)

How to trigger the backlight, force it on, and - on hardware with an RGB backlight - tint it.

#### [Buttons](/guides/events-and-services/buttons.md)

How to react to button presses in your app.

#### [Compass](/guides/events-and-services/compass.md)

How to use data from the Compass API to determine direction.

#### [Dictation](/guides/events-and-services/dictation.md)

How to use the Dictation API to get voice-to-text input in watchapps.

#### [Event Services](/guides/events-and-services/events.md)

How to use the various asynchronous event services to power app features.

#### [Heart Rate Monitor](/guides/events-and-services/hrm.md)

Information on using the HealthService API to obtain information from the Heart Rate Monitor.

#### [Pebble Health](/guides/events-and-services/health.md)

Information on using the HealthService API to incorporate multiple types of health data into your apps.

#### [Persistent Storage](/guides/events-and-services/persistent-storage.md)

Using persistent storage to improve your app's UX.

#### [Speaker](/guides/events-and-services/speaker.md)

How to play tones, melodies, polyphonic tracks, and PCM streams through the speaker.

#### [Touch](/guides/events-and-services/touch.md)

How to subscribe to touch events on platforms with a touchscreen.

#### [Wakeups](/guides/events-and-services/wakeups.md)

Using the Wakeup API to launch an app at some future time.

## [8. Graphics and Animations](/guides/graphics-and-animations.md)

Information on using animations and drawing shapes, text, and images, as well as more advanced techniques.

#### [Animations](/guides/graphics-and-animations/animations.md)

How to use Animations and Timers to add life to your app.

#### [Drawing Primitives, Images and Text](/guides/graphics-and-animations/drawing-primitives-images-and-text.md)

How to draw primitive shapes, image, and text onto the Graphics Context.

#### [Framebuffer Graphics](/guides/graphics-and-animations/framebuffer-graphics.md)

How to perform advanced drawing using direct framebuffer access.

#### [Vector Graphics](/guides/graphics-and-animations/vector-graphics.md)

How to draw simple images using vector images, instead of bitmaps.

## [9. Pebble Packages](/guides/pebble-packages.md)

How to create and use Pebble Packages

#### [Creating Pebble Packages](/guides/pebble-packages/creating-packages.md)

How to create Pebble Packages

#### [Using Pebble Packages](/guides/pebble-packages/using-packages.md)

How to use Pebble Packages

## [10. Pebble Timeline](/guides/pebble-timeline.md)

How to use Pebble timeline to bring timely information to app users outside the app itself via web services.

#### [Creating Pins](/guides/pebble-timeline/pin-structure.md)

How to create timeline pins with reminders, actions, and layouts.

#### [Libraries for Pushing Pins](/guides/pebble-timeline/timeline-libraries.md)

A list of libraries available for interacting with the Pebble timeline.

#### [Managing Subscriptions](/guides/pebble-timeline/timeline-js.md)

How to integrate the timeline into apps with the PebbleKit JS subscriptions API according to user preferences.

#### [Public Web API](/guides/pebble-timeline/timeline-public.md)

How to push Pebble timeline data to an app's users using the public web API.

#### [Service Architecture](/guides/pebble-timeline/timeline-architecture.md)

Find out what the timeline is, how it works and how developers can take advantage of it in their apps.

## [11. Tools and Resources](/guides/tools-and-resources.md)

Information on all the software tools available when writing Pebble apps, as well as other resources.

#### [App Metadata](/guides/tools-and-resources/app-metadata.md)

Details of the metadata that describes the app, such as its name, resources and capabilities.

#### [Color Picker Tool](/guides/tools-and-resources/color-picker.md)

Preview all the colors available on Pebble with the associated SDK contants and HTML codes.

#### [Command Line Tool](/guides/tools-and-resources/pebble-tool.md)

How to use the Pebble command line tool to build, debug, and emulate apps.

#### [Developer Connection](/guides/tools-and-resources/developer-connection.md)

How to enable and use the Pebble Developer Connection to install and debug apps directly from a computer.

#### [Getting Started with Pebble Time Round](/guides/getting-started-pebble-time-round.md)

Details on all the new features and APIs available for the Chalk platfom, or Pebble Time Round.

#### [Hardware Information](/guides/tools-and-resources/hardware-information.md)

Details of the the capabilities of the various Pebble hardware platforms.

#### [Internationalization](/guides/tools-and-resources/internationalization.md)

How to localize an app to multiple languages.

## [12. User Interfaces](/guides/user-interfaces.md)

How to build effective user interfaces. Includes information on events, persistent storage, background worker, wakeups and app configuration.

#### [App Configuration](/guides/user-interfaces/app-configuration.md)

How to allow users to customize an app with a configuration page.

#### [App Exit Reason](/guides/user-interfaces/app-exit-reason.md)

Details on how to use the AppExitReason API

#### [AppGlance C API](/guides/user-interfaces/appglance-c.md)

How to programatically update an app's app glance.

#### [AppGlance REST API](/guides/user-interfaces/appglance-rest.md)

How to update an app's app glance using the REST API.

#### [AppGlance in PebbleKit JS](/guides/user-interfaces/appglance-pebblekit-js.md)

How to update an app's glance using PebbleKit JS.

#### [Content Size](/guides/user-interfaces/content-size.md)

Details on how to use the ContentSize API to adapt your watchface layout based on user text size preferences.

#### [Layers](/guides/user-interfaces/layers.md)

How to use standard Layer components to build an app's UI.

#### [Round App UI](/guides/user-interfaces/round-app-ui.md)

Details on how to use the Pebble SDK to create layouts specifically for round displays.

#### [Unobstructed Area](/guides/user-interfaces/unobstructed-area.md)

Details on how to use the UnobstructedArea API to adapt your watchface layout when the screen is partially obstructed by a system overlay.
