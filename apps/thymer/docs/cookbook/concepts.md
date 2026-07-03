# General Concepts

Use this section for general Thymer config patterns that are not tied to one domain.

## Minimal single timer

```toml
[timers.focus]
trigger = { tap = "top" }
pattern = [
  { name = "focus", time = "00:25:00" },
]
```

## Finite repeating timer

This is a good shape for work blocks, study intervals, or any routine with a predictable number of rounds.

```toml
[timers.focus-block]
repeat = 4
trigger = { swipe = "l-to-r" }
on-finished = { vibrate = "low-low-high" }
vibrate = { intensity = "mid" }
pattern = [
  { name = "focus", hint = "deep work", time = "00:25:00" },
  { name = "short break", time = 5, vibrate = "low" },
]
```

## Per-segment vibration array

Use the array form when one named vibration level is too coarse and you want a more distinctive tactile pattern.

```toml
[timers.long-break]
name = "Long Break"
trigger = { swipe = "c-to-b" }
pattern = [
  { name = "rest", hint = "walk away", time = "00:15:00", vibrate = [
    { intensity = "low" },
    { duration = 200, delay = 120 },
    { intensity = "high", delay = 120 },
  ] },
]
```
