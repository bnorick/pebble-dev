# Config Format

The current config format is intentionally narrow. A valid document is made of an optional `[vibration]` table plus one or more named timer sections.

`#` comments are supported. The parser is strict about keys: if a table or inline table contains a key that is not part of the supported Thymer config shape, parsing fails.

## Top-level

```toml
[vibration]
pulse-delay = 200
warning = "mid-mid-mid"
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
- can set `acknowledgment-alert-duration`
- can set `warning` for the default `warn-at` vibration

### `[timers.<name>]`

Required named timer sections:

- `<name>` is used as the default display name when `name` is omitted
- at least one timer is required
- each timer must define `trigger` and either `time` or `pattern`
