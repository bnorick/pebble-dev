# Frequently Asked Questions

Source: https://developer.repebble.com/faqs/

## Pebble SDK

What are the Aplite, Basalt, Chalk, Diorite, Emery and Flint platforms?

These are the platform names used to describe different generations of watches. For example, Aplite refers to the original Pebble and Pebble Steel. You can find a full list, as well as information about the capabilities of each platform, on the [Hardware Information page](/guides/tools-and-resources/hardware-information.md)

I cannot find the "Developer Mode" or "Developer Connection" toggle in the iOS or Android application

Please make sure you have updated your mobile applications to at least 2.0. On iOS, you first need to enable Developer Mode in the global _Settings_ application on the phone. On Android, this can be enabled from the navigation drawer.

`pebble` tool error: 'RuntimeError: Freetype library not found'

Please install the freetype library on your computer:

- Mac OS users can use the [homebrew](http://brew.sh/) packaging system and run `brew install freetype`.

- Linux users should not have to do anything.

How do I save the state between app invocations, for example, if I want to store user selections etc and persist it across app invocations?

Use the [Persistent Storage API](/guides/events-and-services/persistent-storage.md), or [PebbleKit JS](/guides/communication/using-pebblekit-js.md) `localStorage`.

How do I calculate the total size of a dictionary?

If you have a pointer to a `DictionaryIterator`, you can easily calculate the total size of this dictionary:

```
int size = (int)received-\>end - (int)received-\>dictionary;
```

Can I get realtime accelerometer data?

Yes. See [this community blog post (external link)](http://ninedof.wordpress.com/2014/03/28/streaming-pebble-accelerometer-data/) for more information.

## App Communication

App message error: 'The app rejected the update'

This is likely caused by a mismatch between your watch application UUID and the UUID you registered for on the mobile application. Please make sure you use the same UUID on both ends.

## Memory Management

How apps are loaded for execution? For example, are apps always in RAM, or loaded in RAM one at a time when the user starts that specific app?

Apps (code and static variables) are loaded entirely in RAM when they are started. Your resources are only loaded in RAM when you call `resource_load()` or one of the function that calls it (like `fonts_load_custom_font()` or `gbitmap_create_with_resource_id()`). Your app, and all memory it has allocated, will be removed from RAM when it is terminated.

What is the maximum code segment size? The data segment size?

All segments share the same memory space. There is no limit on the segment sizes but the global limit of memory available to apps is currently around 24k bytes.

Is there a separate Read-Only data segment vs a Read-Write data?

No. For apps, the data segment is all Read-Write.

Can one app invoke another app to get around app size limits?

You can use the PebbleKit iOS or Android to launch any application on Pebble.

## Pebble SDK 1.x Migration

In my old app `PBL_APP_INFO` I was setting the flags `APP_INFO_STANDARD_APP | APP_INFO_VISIBILITY_SHOWN_ON_COMMUNICATION`. How do I do that with the new `appinfo.json` file?

You can add another flag to `package.json` under the `"watchapp"` block:

```
"watchapp": {"watchface": false"onlyShownOnCommunication": true}
```

## Platforms and Devices

Which platform name maps to which Pebble watch?

Each platform name corresponds to a generation of hardware:

- **Aplite** - original Pebble and Pebble Steel (black & white, rectangular)
- **Basalt** - Pebble Time and Pebble Time Steel (64 colors, rectangular)
- **Chalk** - Pebble Time Round (64 colors, round)
- **Diorite** - Pebble 2 (black & white, rectangular, with heart rate)
- **Flint** - Pebble 2 Duo (black & white, rectangular, re-released by Core Devices)
- **Emery** - Pebble Time 2 (64 colors, rectangular, larger display)
- **Gabbro** - Pebble Time 2 round variant (64 colors, round)

The full capability matrix lives on the [Hardware Information page](/guides/tools-and-resources/hardware-information.md). Use the corresponding `PBL_PLATFORM_*` and `PBL_BW`/`PBL_COLOR`/`PBL_ROUND`/`PBL_RECT` defines to write platform-aware code - see {% guide\_link best-practices/building-for-every-pebble "Building for Every Pebble" %}.

Which platforms support which features?

Color, shape, microphone, heart rate, and compass availability all vary by platform. The full feature matrix is in the table on the [Hardware Information page](/guides/tools-and-resources/hardware-information.md). At compile time, use macros like `PBL_IF_COLOR_ELSE()`, `PBL_IF_ROUND_ELSE()`, and `PBL_IF_MICROPHONE_ELSE()` to branch on capabilities instead of hard-coding platform checks. The complete list is in {% guide\_link best-practices/building-for-every-pebble#available-defines-and-macros "Available Defines and Macros" %}.

## Developing for Pebble

How do I install an app I'm developing onto a real watch?

The default flow uses a cloud relay, so your computer and phone don't need to be on the same network. One-time setup:

1. Install the new Pebble mobile app from [repebble.com/app](https://repebble.com/app).
2. In the app: **Devices → ⋯ → Enable Dev Connect** , then sign in with GitHub.
3. On your computer, run `pebble login` and sign in with the same GitHub account.

Then build and install:

```
$ pebble build
$ pebble install --cloudpebble
```

If you'd rather install over local Wi-Fi (the legacy route), enable the [Developer Connection](/guides/tools-and-resources/developer-connection.md) in the mobile app and use `pebble install --phone IP_ADDRESS` with the Server IP it shows.

How do I install an app on the emulator instead of a physical watch?

Pass `--emulator` with the platform you want to run:

```
$ pebble install --emulator basalt
```

Valid platforms are `aplite`, `basalt`, `chalk`, `diorite`, and `emery`. The same flag works for `pebble logs`, `pebble screenshot`, and other commands that target a watch. Full reference: {% guide\_link tools-and-resources/pebble-tool "Pebble Tool" %}.

How do I see logs from my app?

Use `pebble logs --cloudpebble` (or `--emulator PLATFORM`, or `--phone IP_ADDRESS` for the legacy Wi-Fi route) to stream `APP_LOG` output. If you run `pebble install` with `-v` (or `-vvvv` for more detail) it will install and then immediately attach to the log stream.

## C Apps vs JavaScript Apps

Should I write my app in C or JavaScript (Alloy)?

Both run on the watch itself. Write in **C** when you need to support the full lineup of Pebble watches (Aplite through Gabbro), use the classic Pebble SDK UI primitives (`MenuLayer`, `ActionBarLayer`, etc.), or want the smallest possible memory footprint.

Write in **JavaScript with [Alloy](/guides/alloy.md)** when you want modern JS (ES2025, modules, classes, async/await), the Piu (declarative) or Poco (procedural) UI frameworks from the Moddable SDK, and built-in `fetch`, WebSockets, and ECMA-419 device APIs. Alloy supports both watchfaces and watchapps.

The trade-off today is platform reach: Alloy currently only targets **Emery (Pebble Time 2)** and **Gabbro (Pebble Time 2 round)**. If your app needs to run on Aplite, Basalt, Chalk, Diorite, or Flint, write it in C.

Both C and Alloy apps can have a phone-side **PKJS** component for networking, location, and configuration - that's a separate JavaScript environment from your on-watch code.

What should I know about Alloy's JavaScript runtime?

Alloy uses Moddable's XS engine, which differs from browser/Node.js JavaScript in a few important ways:

- **Platform support** : Emery and Gabbro only - no Aplite/Basalt/Chalk/Diorite/Flint support.
- **Strict mode** is on by default for all code.
- **Hardened JavaScript** : built-in objects (primordials) are frozen - you can't monkey-patch `Array.prototype` and friends.
- **No `eval()`** or `Function()` constructor - keeps the engine footprint small.
- **Two environments per app** : `src/embeddedjs/main.js` runs on the watch; `src/pkjs/index.js` runs on the phone for network and location.

Scaffold a new project with `pebble new-project --alloy my-app`. Full details in {% guide\_link alloy/getting-started "Getting Started with Alloy" %}, and example apps live in the [Moddable Pebble Examples](https://github.com/Moddable-OpenSource/pebble-examples) repo.

## Memory and Resources

How much memory does my app have?

The app heap budget depends on the platform - Aplite is the tightest at around 24 KB, while Basalt, Chalk, Diorite, and Emery have substantially more. Use [`heap_bytes_free()`](/docs/c/Foundation/Memory_Management/#heap_bytes_free "heap\_bytes\_free") and [`heap_bytes_used()`](/docs/c/Foundation/Memory_Management/#heap_bytes_used "heap\_bytes\_used") at runtime, and watch the `Free RAM` line in the build output to track your app's footprint. Tips for fitting into the smaller platforms are in {% guide\_link best-practices/building-for-every-pebble "Building for Every Pebble" %} and {% guide\_link migration/3x-aplite-migration "3.x Aplite Migration" %}.

How should I manage images and other resources?

Declare resources in the `resources` block of `package.json`, then load them at runtime with `gbitmap_create_with_resource_id()`, `fonts_load_custom_font()`, and similar calls. Resources are only loaded into RAM when you ask for them, so destroy them as soon as you're done.

For images, prefer the `bitmap` resource type - the SDK will pick an efficient on-disk format per platform. You can also vary an asset per platform using `targetPlatforms` in the resource definition. See:

- {% guide\_link app-resources/app-assets "App Assets" %}
- {% guide\_link app-resources/images "Images" %}
- {% guide\_link app-resources/platform-specific "Platform-Specific Resources" %}

How do I create vector graphics (PDC) for animations and icons?

Pebble Draw Command (PDC) files are a compact vector format the watch can render directly. The SDK ships an `svg2pdc.py` script for converting Inkscape or Illustrator SVGs - see {% guide\_link app-resources/converting-svg-to-pdc "Converting SVG to PDC" %}.

For interactive editing, the community-maintained [PDC tool by Heiko Behrens](https://pdc-tool.heikobehrens.com/) lets you inspect, tweak, and preview PDC files in the browser, which is handy when you need to fine-tune a converted SVG.

## Emulator and Troubleshooting

The emulator is stuck, crashing, or behaving oddly. How do I reset it?

Run:

```
$ pebble wipe
```

This clears stored emulator state (installed apps, settings, persistent storage) without signing you out of your Pebble account. Add `--everything` to also wipe account data. After wiping, the next `pebble install --emulator PLATFORM` will start a fresh QEMU instance.

`pebble build` or `pebble new-project` says no SDK is installed

After installing the `pebble` tool you also need to fetch an SDK release. Run:

```
$ pebble sdk install latest
```

This downloads the most recent SDK and makes it the active one. You can list installed versions with `pebble sdk list` and switch between them with `pebble sdk activate VERSION`.

The emulator won't start on Linux (missing SDL/glib/pixman errors)

The Pebble QEMU build needs SDL2, glib, pixman, and zlib at runtime - they aren't pulled in by `pebble-tool` itself. Install them with your distro's package manager:

- **Ubuntu/Debian** : `sudo apt install libsdl2-2.0-0 libglib2.0-0 libpixman-1-0 zlib1g`
- **Fedora** : `sudo dnf install SDL2 glib2 pixman zlib`

Then retry `pebble install --emulator PLATFORM`. The full setup steps are on the [SDK installation page](/sdk.md).

## Community Tools

Is there an AI-assisted way to build watchfaces?

Yes: Core Devices maintains a [Pebble Watchface Agent skill](https://github.com/coredevices/pebble-watchface-agent-skill) for Claude Code. It bundles the SDK knowledge an agent needs to scaffold, build, and iterate on a watchface project. Follow the README for installation and prompting tips.

Where can I edit and preview PDC vector files visually?

Heiko Behrens hosts a browser-based [PDC tool](https://pdc-tool.heikobehrens.com/) that loads, displays, and lets you tweak PDC files. It's particularly useful for inspecting the output of `svg2pdc.py` and adjusting paths without re-exporting from your vector editor.
