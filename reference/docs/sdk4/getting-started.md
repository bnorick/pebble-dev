# Getting Started with SDK 4

Source: https://developer.repebble.com/sdk4/getting-started/

Pebble SDK 4 is now available for developers who are interested in using the new APIs and features. We encourage developers to read the [Release Notes](/sdk/changelogs/), the [SDK 4 Docs](/docs/c.md), and the new guides listed below to help familiarize themselves with the new functionality.

## Getting Started

#### Mac OS X (Homebrew)

```
$ brew update && brew upgrade pebble-sdk && pebble sdk install latest
```

#### Mac OS X (Manual)

1. Download the[SDK package](https://s3.amazonaws.com/assets.getpebble.com/pebble-tool/pebble-sdk-4.5-mac.tar.bz2).

2. Follow the [Mac manual installation instructions](/sdk/install/mac/).

#### Linux

Linux users should install the SDK manually using the instructions below:

1. Download the relevant package:[Linux (32-bit)](https://s3.amazonaws.com/assets.getpebble.com/pebble-tool/pebble-sdk-4.5-linux32.tar.bz2) |[Linux (64-bit)](https://s3.amazonaws.com/assets.getpebble.com/pebble-tool/pebble-sdk-4.5-linux64.tar.bz2).

2. Install the SDK by following the[manual installation instructions](/sdk/install/linux/).

## Blog Posts

We've published several useful blog posts regarding SDK 4:

- [Introducing Rocky.js Watchfaces!](/blog/2016/08/15/introducing-rockyjs-watchfaces.md)
- [Prime Time is Approaching for OS 4.0](/blog/2016/08/19/prime-time-is-approaching-for-os-4.0.md)
- [Announcing Pebble SDK 4.0](/blog/2016/08/30/announcing-pebble-sdk4.md)

## New Resources

To get you started, we have updated the following sections of the Pebble Developer site with new content and information on designing and developing for the new Pebble hardware platform:

- A 2-part [_Rocky.js tutorial_](/tutorials/js-watchface-tutorial/part1/) - Learn how to create watchfaces in JavaScript using Rocky.js.

- An updated[_Hardware Comparison_](/guides/tools-and-resources/hardware-information.md)chart - See the hardware differences between all Pebble platforms.

- [_AppExitReason API Guide_](/guides/user-interfaces/app-exit-reason.md) - A new guide with information on how to use the `AppExitReason` API.

- [_AppGlance C API Guide_](/guides/user-interfaces/appglance-c.md) - A new guide describing how to use the AppGlance API to display information in the system's launcher.

- [_AppGlance PebbleKit JS API Guide_](/guides/user-interfaces/appglance-pebblekit-js.md) - A new guide describing how to use the AppGlance API to display information in the system's launcher.

- [_One Click Action Guide_](/guides/design-and-interaction/one-click-actions.md) - A new guide with information on how to use one-click actions in watchapps.

- [_UnobstuctedArea API Guide_](/guides/user-interfaces/unobstructed-area.md) - A new guide that will demonstrate the basics of the `UnobstructedArea` API, and how to use it to create watchfaces that respond to Timeline Quick View events.
