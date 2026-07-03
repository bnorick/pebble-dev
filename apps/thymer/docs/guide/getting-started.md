# Getting Started

Timer definitions in Thymer are entered as TOML in the phone-side settings page. While it can be useful for quick changes, I don't recommend editing your timers extensively in that small input box. Personally, I copy paste my configuration from my note taking app, where I make changes on my computer that are synced to my phone.

The app parses the TOML configuration on the phone, validates it, and sends a normalized timer model to the watch. Some additional appearance settings can be configured direction in the phone-side settings page.

Thymer is on the [Pebble Appstore](https://apps.repebble.com/337bcb025b4e48788aa24d00).

## Start with one timer

Every config needs at least one named timer section under `timers.*`.

```toml
[timers.focus]
trigger = { tap = "top" }
pattern = [
  { name = "focus", time = "00:25:00" },
  { name = "break", time = "00:05:00", vibrate = "low" },
]
```

That example uses:

- a named timer key, `focus`
- a required `trigger`
- a required `pattern`
- `time` values written as `HH:MM:SS`

## What lives at the top level

Only these top-level sections are part of the current config model:

- `[vibration]`
- `[timers.<name>]`

## Appearance settings

The settings UI also exposes watch-side appearance toggles for icon display, background display, and timer accent. Those toggles are not part of the TOML config. They are stored separately from the timer definition.

## Next steps

- Read [Config Format](/reference/config-format) for the supported top-level structure.
- Read [Timers](/reference/timers) for per-timer fields.
- Read [Cookbook](/cookbook/concepts) for worked recipes and longer configs.
