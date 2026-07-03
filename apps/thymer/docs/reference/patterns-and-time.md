# Patterns and Time

Each timer `pattern` is an ordered array of inline tables. Thymer moves through the entries in order and repeats the full pattern only when the timer's `repeat` setting requires it.

## Segment fields

### `description`

Optional display label for the segment.

```toml
{ description = "focus", time = "00:25:00" }
```

If omitted, Thymer falls back to `step N`.

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

## Validation rules

- `time` is required
- numeric `time` must be a safe non-negative integer number of seconds
- string `time` must use the supported clock format
- the final duration must be at least 1 millisecond
