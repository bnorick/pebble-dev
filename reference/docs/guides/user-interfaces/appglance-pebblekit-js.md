# AppGlance in PebbleKit JS

Source: https://developer.repebble.com/guides/user-interfaces/appglance-pebblekit-js/

## Overview

This guide explains how to manage your app's glances via PebbleKit JS. The[`App Glance`](/docs/c/Foundation/App_Glance/ "App Glance") API was added in SDK 4.0 and enables developers to programmatically set the icon and subtitle that appears alongside their app in the launcher.

If you want to learn more about [`App Glance`](/docs/c/Foundation/App_Glance/ "App Glance"), please read the[_AppGlance C API_](/guides/user-interfaces/appglance-c.md) guide.

#### Creating Slices

To create a slice, call `Pebble.appGlanceReload()`. The first parameter is an array of AppGlance slices, followed by a callback for success and one for failure.

```
// Construct the app glance slice objectvar appGlanceSlices = [{"layout": {"icon": "system://images/HOTEL\_RESERVATION","subtitleTemplateString": "Nice Slice!"}}];function appGlanceSuccess(appGlanceSlices, appGlanceReloadResult) {console.log('SUCCESS!');};function appGlanceFailure(appGlanceSlices, appGlanceReloadResult) {console.log('FAILURE!');};// Trigger a reload of the slices in the app glancePebble.appGlanceReload(appGlanceSlices, appGlanceSuccess, appGlanceFailure);
```

#### Slice Icons

There are two types of resources which can be used for AppGlance icons.

- You can use system images. E.g. `system://images/HOTEL_RESERVATION`
- You can use custom images by utilizing the[_Published Media_](/guides/tools-and-resources/app-metadata.md#published-media)`name`. E.g. `app://images/*name*`

#### Subtitle Template Strings

The `subtitle_template_string` field provides developers with a string formatting language for app glance subtitles. Read more in the[_AppGlance C guide_](/guides/user-interfaces/appglance-c.md#subtitle-template-strings).

#### Expiring Slices

When you want your slice to expire automatically, just provide an`expirationTime` in[ISO date-time](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Date/toISOString)format and the system will automatically remove it upon expiry.

```
var appGlanceSlices = [{"layout": {"icon": "system://images/HOTEL\_RESERVATION","subtitleTemplateString": "Nice Slice!"},"expirationTime": "2016-12-31T23:59:59.000Z"}];
```

#### Creating Multiple Slices

Because `appGlanceSlices` is an array, we can pass multiple slices within a single function call. The system is responsible for displaying the correct entries based on the `expirationTime` provided in each slice.

```
var appGlanceSlices = [{"layout": {"icon": "system://images/DINNER\_RESERVATION","subtitleTemplateString": "Lunchtime!"},"expirationTime": "2017-01-01T12:00:00.000Z"},{"layout": {"icon": "system://images/RESULT\_MUTE","subtitleTemplateString": "Nap Time!"},"expirationTime": "2017-01-01T14:00:00.000Z"}];
```

#### Updating Slices

There isn't a concept of updating an AppGlance slice, just call`Pebble.appGlanceReload()` with the new slices and any existing slices will be replaced.

#### Deleting Slices

All you need to do is pass an empty slices array and any existing slices will be removed.

```
Pebble.appGlanceReload([], appGlanceSuccess, appGlanceFailure);
```
