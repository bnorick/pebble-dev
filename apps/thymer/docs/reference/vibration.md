# Vibration

Thymer uses the same vibration grammar for segment transitions, timer-level default `vibrate`, and `on-finished`.

## Root vibration table

Use `[vibration]` to set shared named levels and defaults.

```toml
[vibration]
pulse-delay = 200
acknowledgement-alert-duration = 12
superlow = 60
low = 100
mid = 300
high = 500
```

Supported keys:

- `pulse-delay`
- `acknowledgement-alert-duration`
- named levels such as `low`, `mid`, `high`, or custom names like `superlow`

`medium` is normalized to `mid`.

## Simple string form

```toml
vibrate = "low"
```

Uses a named vibration level and the shared default pulse delay.

This same syntax also works directly on `on-finished`:

```toml
on-finished = "low-low-high"
```

## Shorthand sequence form

```toml
vibrate = "low-low-high"
```

Hyphen-separated strings expand into multiple vibration steps.

## Inline table form

```toml
vibrate = { duration = 140, delay = 80 }
```

or:

```toml
vibrate = { intensity = "high", delay = 120 }
```

## Array form

```toml
vibrate = [
  { intensity = "superlow" },
  { duration = 200, delay = 120 },
  { intensity = "low", delay = 120 },
]
```

## Important rules

- each step may specify `intensity` or `duration`, not both
- `delay` is optional and defaults to the root `pulse-delay`
- unknown named levels are rejected
- named levels must be positive durations in milliseconds
