# Timers

Each timer lives in a named section such as `[timers.focus-block]`.

## Required fields

### `trigger`

Required inline table:

```toml
trigger = { tap = "top" }
```

or:

```toml
trigger = { swipe = "l-to-r" }
```

### `pattern`

Required non-empty array of inline tables:

```toml
pattern = [
  { description = "focus", time = "00:25:00" },
  { description = "break", time = "00:05:00", vibrate = "low" },
]
```

## Optional fields

### `name`

Overrides the display name derived from the timer key.

```toml
name = "Long Break"
```

### `repeat`

Controls repetition:

- omitted or `false`: run once
- `true`: repeat forever
- positive integer: repeat that many times

```toml
repeat = 4
```

`repeat = true` cannot be combined with `on-finished`.

### `on-finished`

Optional finish vibration:

```toml
on-finished = { vibrate = "low-low-high" }
```

### `on-press-up` and `on-long-press-up`

Optional up-button actions:

- `skip`
- `hide`

```toml
on-press-up = "skip"
on-long-press-up = "hide"
```

### `must-acknowledge`

Boolean flag that forces acknowledgement before the timer fully clears.

```toml
must-acknowledge = true
```

### `repeat-pattern-delay`

Delay in milliseconds inserted before the next repetition starts. Defaults to `500`.

```toml
repeat-pattern-delay = 500
```

### `acknowledgement-alert-duration`

Per-timer override in milliseconds for acknowledgement reminder vibration duration. Defaults to the root `[vibration]` value, or `12` when that table is omitted.

Accepted aliases:

- `acknowledgement-alert-duration`
- `acknowledgment-alert-duration`
- `ack-alert-duration`

Only set one alias per timer.
