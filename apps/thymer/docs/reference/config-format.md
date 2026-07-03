# Config Format

The current config format is intentionally narrow. A valid document is made of an optional `[vibration]` table plus one or more named timer sections.

## Top-level

```toml
[vibration]
pulse-delay = 200
low = 90
mid = 120
high = 180

[timers.focus]
trigger = { tap = "top" }
pattern = [
  { name = "focus", time = "00:25:00" },
]
```

## Supported sections

### `[vibration]`

Optional shared vibration settings:

- overrides built-in named levels such as `low`, `mid`, and `high`
- can define extra named levels such as `superlow`
- can set `pulse-delay`
- can set `acknowledgement-alert-duration`

### `[timers.<name>]`

Required named timer sections:

- `<name>` is used as the default display name when `name` is omitted
- at least one timer is required
- each timer must define `trigger` and `pattern`
