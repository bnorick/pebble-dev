# Common Errors

## `config must define at least one timer with [timers.<name>]`

You did not define any named timer sections.

```toml
[timers.focus]
trigger = { tap = "top" }
pattern = [
  { time = 5 },
]
```

## `root-level fields are not supported; use [timers.<name>] entries`

The current parser rejects assignments placed at the document root. Use top-level tables like `[vibration]` and `[timers.<name>]` instead.

```toml
name = "Focus"
pattern = []
```

## `invalid segment duration: ...`

The `time` string is malformed or out of range. Use one of:

- integer seconds
- `HH:MM:SS`
- `HH:MM:SS.SSSS`
- `DD-HH:MM:SS`
- `DD-HH:MM:SS.SSSS`

## `trigger must be { tap = ... } or { swipe = ... }`

Use an inline table:

```toml
trigger = { tap = "top" }
```

or:

```toml
trigger = { swipe = "l-to-r" }
```

Directional aliases also work:

```toml
trigger = { swipe = "up" }
```

## `timer N cannot use on-finished with repeat = true`

Infinite timers never finish, so `on-finished` only works with one-shot and finite repeating timers.

## `timer N true stopwatch cannot use on-finished`

If you omit both `time` and `pattern`, `stopwatch = true` creates a true stopwatch with no preset finish, so `on-finished` is not valid there.

## `... uses unsupported key: ...`

The parser is strict. Unknown keys in timer tables and inline tables are rejected instead of being ignored.

Common examples:

```toml
[timers.focus]
trigger = { tap = "top", zone = "left" }
pattern = [
  { time = 5, description = "work" },
]
```
