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
  { name = "focus", time = "00:25:00" },
  { name = "break", time = "00:05:00", vibrate = "low" },
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

### `vibrate`

Optional default vibration for every segment in the timer.

```toml
vibrate = "mid"
```

Any segment with its own `vibrate` value overrides this default.

### `on-finished`

Optional finish vibration. Both of these are valid:

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

### `acknowledgment-alert-duration`

Per-timer override in milliseconds for acknowledgement reminder vibration duration. Defaults to the root `[vibration]` value, or `12` when that table is omitted.
