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

Required for multi-segment timers unless `stopwatch = true` and you want a true stopwatch with no preset duration. Mutually exclusive with timer-level `time`.

```toml
pattern = [
  { name = "focus", time = "00:25:00" },
  { name = "break", time = "00:05:00", vibrate = "low" },
]
```

### `time`

Required for single-segment timers that omit `pattern`, unless `stopwatch = true` and you want a true stopwatch with no preset duration.

```toml
time = "00:15:00"
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

### `stopwatch`

Defaults to `false`. When `true`, Thymer shows elapsed time counting up during the run instead of time remaining counting down.

```toml
stopwatch = true
time = "00:10:00"
```

If you omit both `time` and `pattern`, `stopwatch = true` creates a true stopwatch with no preset end:

```toml
stopwatch = true
```

### `vibrate`

Optional default vibration for every segment in the timer, and the segment vibration for single-segment timers that use timer-level `time`.

```toml
vibrate = "mid"
```

Any segment with its own `vibrate` value overrides this default.

### `hint`

Optional default hint for every segment in the timer, and the single segment hint when `pattern` is omitted.

```toml
hint = "deep work"
```

### `warn-at`

Optional default warning point or warning list for every segment in the timer, and the single segment warning when `pattern` is omitted.

```toml
warn-at = "00:01:00"
```

Any segment with its own `warn-at` value overrides this default.

### `on-finished`

Optional finish vibration. Both of these are valid:

```toml
on-finished = { vibrate = "low-low-high" }
```

### `on-press-up`, `on-long-press-up`, and `on-long-press-select`

Optional button actions. `skip`, `hide`, and `stopwatch` can still use bare strings:

- `skip`
- `hide`
- `stopwatch`

```toml
on-press-up = "skip"
on-long-press-up = "hide"
on-long-press-select = "hide"
```

You can also use an inline table for any action:

```toml
on-press-up = { action = "hide" }
```

`on-long-press-select` defaults to `hide` when omitted, so every timer can enter hide mode without extra configuration unless overridden without an alternate.

`increment` and `decrement` require an inline table with a `time` value in the same format as segment `time`:

- `increment`
- `decrement`

```toml
on-press-up = { action = "decrement", time = "00:01:00" }
on-long-press-up = { action = "increment", time = "00:01:00" }
on-long-press-select = { action = "increment", time = "00:05:00" }
```

These actions only affect an active timer run. They work while the timer is running or paused. `increment` extends the timer beyond its original configured length, and `decrement` shortens the remaining time and can finish the timer immediately when pushed past the end.

`stopwatch` is the exception: it starts the selected timer in stopwatch mode when no run is active, even if that timer is not configured with `stopwatch = true`.

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
