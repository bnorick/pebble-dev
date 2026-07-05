# Patterns and Time

Each timer `pattern` is an ordered array of inline tables. Thymer moves through the entries in order and repeats the full pattern only when the timer's `repeat` setting requires it.

## Segment fields

### `name`

Optional display label for the segment.

```toml
{ name = "focus", time = "00:25:00" }
```

If omitted, Thymer falls back to `step N`.

Use `\n` for explicit line breaks when you want the watch to stack the label.

### `hint`

Optional smaller line shown above the segment name on the watch.

```toml
{ hint = "deep work", name = "focus", time = "00:25:00" }
```

### `time`

Required segment duration. Supported forms:

- integer seconds
- `HH:MM:SS`
- `HH:MM:SS.SSSS`
- `DD-HH:MM:SS`
- `DD-HH:MM:SS.SSSS`

Examples:

```toml
time = 5
```

```toml
time = "00:00:06.2500"
```

```toml
time = "02-01:30:00"
```

The parser normalizes string durations to millisecond precision before transport to the watch.

### `vibrate`

Optional per-segment vibration. See [Vibration](/reference/vibration) for the accepted forms.

If the parent timer defines `vibrate`, that timer-level value becomes the default for any segment that omits `vibrate`.

### `warn-at`

Optional warning point or warning list, expressed as time remaining before the segment ends.

These forms are valid:

```toml
warn-at = "00:00:10"
```

```toml
warn-at = ["00:01:00", "00:00:10"]
```

```toml
warn-at = { time = "00:00:10", vibrate = "low-low" }
```

```toml
warn-at = [
  { time = "00:01:00", vibrate = "mid" },
  { time = "00:00:10", vibrate = { duration = 200, delay = 0 } }
]
```

When a `warn-at` entry is only a time value, Thymer uses the shared warning vibration. That default is `"mid-mid-mid"` unless `[vibration].warning` overrides it. If you need a different warning vibration for a specific warning, use the inline table form with `time` and `vibrate`.

## Validation rules

- `time` is required
- numeric `time` must be a safe non-negative integer number of seconds
- string `time` must use the supported clock format
- the final duration must be at least 1 millisecond
- every `warn-at` entry must be at least 1 millisecond and strictly shorter than the segment time
- each segment supports at most 4 `warn-at` entries
