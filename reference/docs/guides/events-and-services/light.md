# Backlight

Source: https://developer.repebble.com/guides/events-and-services/light/

The Light API gives an app limited control over the watch backlight. An app can ask the system to flash the backlight as if the user had performed a wrist gesture, or force it on for as long as it needs. On hardware with an RGB backlight, the same API can also tint that backlight any color the user can render in their UI.

All of these calls operate on top of the user's normal backlight settings (auto on-shake, brightness, etc.), so apps don't need to worry about overriding the user's preferences permanently.

## Triggering the Backlight

The simplest and most common use of the Light API is to trigger the backlight exactly as a wrist flick would. The light comes on, stays on for the system auto-off interval, and then fades out:

```
// Turn the backlight on for the standard auto-off intervallight\_enable\_interaction();
```

This is the recommended entry point for most apps. It respects the user's backlight setting (it does nothing if the user has the backlight disabled) and does not require a follow-up call to turn the light back off.

## Forcing the Backlight On

If an app needs the backlight on for an extended interaction - for example, during a flashlight feature or while the user is doing something with both hands - it can pin it on:

```
// Force the backlight onlight\_enable(true);
```

The backlight stays on until the app explicitly returns control to the automatic system:

```
// Hand control back to the system's auto-off behaviorlight\_enable(false);
```

> Holding the backlight on draws significantly more power than letting it auto-off. The system also dims the backlight automatically when the battery is low to protect the user's remaining runtime, so a forced-on backlight is not a guarantee of full brightness.

To check whether the backlight is currently on, use:

```
if (light\_is\_on()) {// The backlight is currently lit}
```

## Tinting the Backlight (RGB Hardware Only)

On hardware with an RGB backlight, the backlight color can be set to any[`GColor`](/docs/c/Graphics/Graphics_Types/#GColor "GColor") value. The color persists for as long as the app is in the foreground, then resets to the user's default when the app exits or is preempted (for example, by an incoming notification modal).

```
// Tint the backlight redlight\_set\_color(GColorRed);
```

`light_set_color()` takes a [`GColor`](/docs/c/Graphics/Graphics_Types/#GColor "GColor"), which on current hardware quantizes to the 64-color palette the UI uses. For more control over the exact tint - for example, to match a brand color or blend between two palette entries - use `light_set_color_rgb888()`, which takes a 24-bit RGB value packed into a`uint32_t` as `0x00RRGGBB`:

```
// Tint the backlight with an exact RGB color (teal)light\_set\_color\_rgb888(0x0088CC);
```

Once set, the tint persists for the rest of the app's foreground session - every subsequent backlight trigger will use that color until the app changes it again or exits. To return to the user's chosen default mid-session, call:

```
// Restore the user's default backlight colorlight\_set\_system\_color();
```

This is important if the app uses different colors for different states (for example, red for an alert and the user default the rest of the time): without an explicit `light_set_system_color()` call the alert color will stick around for every subsequent backlight flash. The system does reset the color automatically when the app exits or is preempted, so there's no need to call`light_set_system_color()` purely on the way out.

On hardware without an RGB backlight these two calls are no-ops and can be left in unconditionally; there's no need to wrap them in a preprocessor guard just to compile against other platforms. For cases where a whole block of color-specific logic should be excluded on non-RGB platforms, the`PBL_RGB_BACKLIGHT` compile-time define is present on platforms that have an RGB backlight:

```
#if defined(PBL\_RGB\_BACKLIGHT)// Use a different tint per app statelight\_set\_color(is\_alert ? GColorRed : GColorWhite);#endiflight\_enable\_interaction();
```

Tinting only changes the _color_ of the backlight; the backlight still needs to be on for the user to see it. Combine `light_set_color()` with`light_enable_interaction()` or `light_enable(true)` so the user actually sees the new color:

```
// Flash the backlight red for the system auto-off intervallight\_set\_color(GColorRed);light\_enable\_interaction();
```

## Battery Considerations

The backlight is one of the most power-hungry components on the watch. Triggering it through `light_enable_interaction()` for short user interactions is generally fine, but holding it on for long periods with`light_enable(true)` will noticeably reduce battery life. Use the forced-on mode only when the feature genuinely requires it, and make sure to release control with `light_enable(false)` as soon as the user is done.
