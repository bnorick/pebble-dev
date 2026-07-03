# Getting Started

Thymer timer definitions are entered as TOML in the phone-side settings page. The app parses that TOML on the phone, validates it, and sends a normalized timer model to the watch.

## Start with one timer

Every config needs at least one named timer section under `timers.*`.

```toml
[timers.focus]
trigger = { tap = "top" }
pattern = [
  { description = "focus", time = "00:25:00" },
  { description = "break", time = "00:05:00", vibrate = "low" },
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

Legacy root-level timer fields and `[[timers]]` arrays are rejected.

## Appearance settings are separate

The settings UI also exposes watch-side appearance toggles such as icons, background, and timer accent images. Those toggles are not part of the TOML config. They are stored separately from the timer definition.

## Next steps

- Read [Config Format](/reference/config-format) for the supported top-level structure.
- Read [Timers](/reference/timers) for per-timer fields.
- Read [Examples](/cookbook/examples) for longer configs.
