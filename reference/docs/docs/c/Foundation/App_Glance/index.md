# App Glance

Source: https://developer.repebble.com/docs/c/Foundation/App_Glance/index.html

API for the application to modify its "glance" i.e. app menu subtitle.

Apps have the ability to show a temporary icon and subtitle in the app selection menu; this is known as a "glance". For example, the app might use it to display a preview of its current state such as the currently playing song or the number of pending notifications.

The glance is loaded with a stack of [AppGlanceSlice](/docs/c/Foundation/App_Glance/#AppGlanceSlice) structs; only the latest slice is shown, and they are set to expire at a certain time to show the next slice in the stack.

To update the glance with a stack of slices, you must define an [AppGlanceReloadCallback](/docs/c/Foundation/App_Glance/#AppGlanceReloadCallback) and give it to [app\_glance\_reload](/docs/c/Foundation/App_Glance/#app_glance_reload). The implementation of your [AppGlanceReloadCallback](/docs/c/Foundation/App_Glance/#AppGlanceReloadCallback) should call [app\_glance\_add\_slice](/docs/c/Foundation/App_Glance/#app_glance_add_slice) to add slices to the glance.

The main window's unload handler is usually a good place to call [app\_glance\_reload](/docs/c/Foundation/App_Glance/#app_glance_reload).

PBL\_PLATFORM\_APLITE does not support App Glance.Example code:

```
#if !PBL\_PLATFORM\_APLITEstatic void glance\_reload\_callback(AppGlanceReloadSession \*session, size\_t limit, void \*context) {AppGlanceSlice slice = {.expiration\_time = APP\_GLANCE\_SLICE\_NO\_EXPIRATION,.layout.icon = APP\_GLANCE\_SLICE\_DEFAULT\_ICON,.layout.subtitle\_template\_string = "hello!",};AppGlanceResult result = app\_glance\_add\_slice(session, slice);if (result != APP\_GLANCE\_RESULT\_SUCCESS){APP\_LOG(APP\_LOG\_LEVEL\_ERROR, "app\_glance\_add\_slice() returned %d", result);}}#endif // !PBL\_PLATFORM\_APLITEstatic void main\_window\_unload(Window \*window) {#if !PBL\_PLATFORM\_APLITEapp\_glance\_reload(glance\_reload\_callback, NULL);#endif // !PBL\_PLATFORM\_APLITE}
```

## Function Documentation

[AppGlanceResult](/docs/c/Foundation/App_Glance/#AppGlanceResult) app\_glance\_add\_slice(AppGlanceReloadSession \* session, [AppGlanceSlice](/docs/c/Foundation/App_Glance/#AppGlanceSlice) slice)

Add a slice to the app's glance. This function will only succeed if called with a valid AppGlanceReloadSession that is provided in an [AppGlanceReloadCallback](/docs/c/Foundation/App_Glance/#AppGlanceReloadCallback).

#### Parameters
 session

The session variable provided in an [AppGlanceReloadCallback](/docs/c/Foundation/App_Glance/#AppGlanceReloadCallback)

 slice

The slice to add to the app's glance

#### Returns

The result of trying to add the slice to the app's glance

void app\_glance\_reload([AppGlanceReloadCallback](/docs/c/Foundation/App_Glance/#AppGlanceReloadCallback) callback, void \* context)

Clear any existing slices in the app's glance and trigger a reload via the provided callback.

#### Parameters
 callback

A function that will be called to add new slices to the app's glance; even if the provided callback is NULL, any existing slices will still be cleared from the app's glance

 context

User-provided context that will be passed to the callback

## Data Structure Documentation

- [SDK 3](javascript:void(0);)
- [SDK 4](javascript:void(0);)
- [SDK 4.9+](javascript:void(0);)

struct AppGlanceSlice

An app's glance can change over time as defined by zero or more app glance slices that each describe the state of the app glance at a particular point in time. Slices are displayed in the order they are added, and they are removed at the specified expiration time.

#### Data Fields
struct [AppGlanceSlice](/docs/c/Foundation/App_Glance/#AppGlanceSlice) layout

Describes how the slice should be visualized in the app's glance in the launcher.

[time\_t](/docs/c/Standard_C/Time/#time_t) expiration\_time

The UTC time after which this slice should no longer be shown in the app's glance. Use [APP\_GLANCE\_SLICE\_NO\_EXPIRATION](/docs/c/Foundation/App_Glance/#APP_GLANCE_SLICE_NO_EXPIRATION) if the slice should never expire.

struct AppGlanceSlice

An app's glance can change over time as defined by zero or more app glance slices that each describe the state of the app glance at a particular point in time. Slices are displayed in the order they are added, and they are removed at the specified expiration time.

#### Data Fields
struct [AppGlanceSlice](/docs/c/Foundation/App_Glance/#AppGlanceSlice) layout

Describes how the slice should be visualized in the app's glance in the launcher.

[time\_t](/docs/c/Standard_C/Time/#time_t) expiration\_time

The UTC time after which this slice should no longer be shown in the app's glance. Use [APP\_GLANCE\_SLICE\_NO\_EXPIRATION](/docs/c/Foundation/App_Glance/#APP_GLANCE_SLICE_NO_EXPIRATION) if the slice should never expire.

struct AppGlanceSlice

An app's glance can change over time as defined by zero or more app glance slices that each describe the state of the app glance at a particular point in time. Slices are displayed in the order they are added, and they are removed at the specified expiration time.

#### Data Fields
[AppGlanceSliceLayout](/docs/c/Foundation/App_Glance/#AppGlanceSliceLayout) layout

Describes how the slice should be visualized in the app's glance in the launcher.

[time\_t](/docs/c/Standard_C/Time/#time_t) expiration\_time

The UTC time after which this slice should no longer be shown in the app's glance. Use [APP\_GLANCE\_SLICE\_NO\_EXPIRATION](/docs/c/Foundation/App_Glance/#APP_GLANCE_SLICE_NO_EXPIRATION) if the slice should never expire.

struct AppGlanceSliceLayout

Describes how the slice should be visualized in the app's glance in the launcher.

#### Data Fields
[PublishedId](/docs/c/Foundation/App_Glance/#PublishedId) icon

The published resource ID of the bitmap icon to display in the app's glance. Use [APP\_GLANCE\_SLICE\_DEFAULT\_ICON](/docs/c/Foundation/App_Glance/#APP_GLANCE_SLICE_DEFAULT_ICON) to use the app's default bitmap icon.

const char \* subtitle\_template\_string

A template string to visualize in the app's glance. The string will be copied, so it is safe to destroy after adding the slice to the glance. Use NULL if no string should be displayed.

## Enum Documentation

enum AppGlanceResult

Bitfield enum describing the result of trying to add an [AppGlanceSlice](/docs/c/Foundation/App_Glance/#AppGlanceSlice) to an app's glance.

#### Enumerators
APP\_GLANCE\_RESULT\_SUCCESS

The slice was successfully added to the app's glance.

APP\_GLANCE\_RESULT\_INVALID\_TEMPLATE\_STRING

The subtitle\_template\_string provided in the slice was invalid.

APP\_GLANCE\_RESULT\_TEMPLATE\_STRING\_TOO\_LONG

The subtitle\_template\_string provided in the slice was longer than 150 bytes.

APP\_GLANCE\_RESULT\_INVALID\_ICON

The icon provided in the slice was invalid.

APP\_GLANCE\_RESULT\_SLICE\_CAPACITY\_EXCEEDED

The provided slice would exceed the app glance's slice capacity.

APP\_GLANCE\_RESULT\_EXPIRES\_IN\_THE\_PAST

The expiration\_time provided in the slice expires in the past.

APP\_GLANCE\_RESULT\_INVALID\_SESSION

The AppGlanceReloadSession provided was invalid.

## Typedef Documentation

 typedef [uint32\_t](/docs/c/Standard_C/#uint32_t) PublishedId

The ID of a published app resource defined within the publishedMedia section of package.json.

 typedef struct AppGlanceReloadSession AppGlanceReloadSession

 typedef void(\* AppGlanceReloadCallback)(AppGlanceReloadSession \*session, size\_t limit, void \*context) 

User-provided callback for reloading the slices in the app's glance.

#### Parameters
 session

A session variable that must be passed to [app\_glance\_add\_slice](/docs/c/Foundation/App_Glance/#app_glance_add_slice) when adding slices to the app's glance; it becomes invalid when the [AppGlanceReloadCallback](/docs/c/Foundation/App_Glance/#AppGlanceReloadCallback) returns

 limit

The number of entries that can be added to the app's glance

 context

User-provided context provided when calling [app\_glance\_reload()](/docs/c/Foundation/App_Glance/#app_glance_reload)

## Macro Definition Documentation

#define APP\_GLANCE\_SLICE\_NO\_EXPIRATION (([time\_t](/docs/c/Standard_C/Time/#time_t))0)

Can be used for the expiration\_time of an [AppGlanceSlice](/docs/c/Foundation/App_Glance/#AppGlanceSlice) so that the slice never expires.

#define APP\_GLANCE\_SLICE\_DEFAULT\_ICON (([PublishedId](/docs/c/Foundation/App_Glance/#PublishedId))0)

Can be used for the icon of an [AppGlanceSlice](/docs/c/Foundation/App_Glance/#AppGlanceSlice) so that the slice displays the app's default icon.
