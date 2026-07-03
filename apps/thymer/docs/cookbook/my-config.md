# My Config

This page carries my personal Thymer config.

```toml
[vibration]
pulse-delay = 200
superlow = 20
low = 100
mid = 300
high = 500

[timers.eyesight]
repeat = 3
pattern = [
  { name = "far",  time = "00:00:15", vibrate = "high" },
  { name = "near", time = "00:00:15", vibrate = "mid-mid" },
]
on-finished = { vibrate = "mid-low-mid" }
trigger = { tap = "top" }


[timers.sharing]
repeat = true
must-acknowledge = true
on-press-up = "skip"
pattern = [
  { name = "Kid 1", time = "00:05:00", vibrate = "high" },
  { name = "Kid 2", time = "00:05:00", vibrate = "high" },
]
trigger = { tap = "left" }


[timers.square]
repeat = true
pattern = [
  { name = "in",   time = "00:00:04", vibrate = "superlow" },
  { name = "hold", time = "00:00:04", vibrate = "superlow" },
  { name = "out",  time = "00:00:04", vibrate = "superlow" },
  { name = "hold", time = "00:00:04", vibrate = "superlow" },
]
trigger = { tap = "right" }


[timers.478]
name = "4-7-8"
repeat = true
on-press-up = "hide"
pattern = [
  { name = "in",   time = "00:00:04", vibrate = "superlow" },
  { name = "hold", time = "00:00:07", vibrate = "superlow-superlow" },
  { name = "out",  time = "00:00:08", vibrate = "superlow-superlow-superlow" },
]
trigger = { tap = "right" }


[timers.test]
repeat = true
must-acknowledge = true
on-press-up = "skip"
pattern = [
  { name = "one",   time = "00:00:04", vibrate = "superlow" },
  { name = "two",   time = "00:00:04", vibrate = "superlow-superlow" },
  { name = "three", time = "00:00:08", vibrate = "superlow-superlow-superlow" },
]
trigger = { tap = "bottom" }
```
