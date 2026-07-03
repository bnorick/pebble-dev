# Exercise

Exercise timers benefit from short labels, decisive vibrations, and patterns you can run without needing to read much once you know the flow.

## 7-minute workout

This is the 7-minute workout, with a timer-level default vibration and explicit line breaks for the longer labels.

```toml
[timers.7-min]
trigger = { tap = "bottom" }
vibrate = "high-high"
pattern = [
  { name = "get ready", time = 10 },
  { name = "jumping jack", time = 30 },
  { name = "rest", hint = "wall sit", time = 10 },
  { name = "wall sit", time = 30 },
  { name = "rest", hint = "push-up", time = 10 },
  { name = "push-up", time = 30 },
  { name = "rest", hint = "crunch", time = 10 },
  { name = "crunch", time = 30 },
  { name = "rest", hint = "step-up\nonto chair", time = 10 },
  { name = "step-up\nonto chair", time = 30 },
  { name = "rest", hint = "squat", time = 10 },
  { name = "squat", time = 30 },
  { name = "rest", hint = "tricep dip", time = 10 },
  { name = "tricep dip", time = 30 },
  { name = "rest", hint = "plank", time = 10 },
  { name = "plank", time = 30 },
  { name = "rest", hint = "high knees", time = 10 },
  { name = "high knees\nrun", time = 30 },
  { name = "rest", hint = "lunge", time = 10 },
  { name = "lunge", time = 30 },
  { name = "rest", hint = "push+rotate", time = 10 },
  { name = "push-up\nand rotation", time = 30 },
  { name = "rest", hint = "side plank", time = 10 },
  { name = "side plank", time = 30 },
  { name = "done", time = 10 },
]
on-finished = { vibrate = "high-high-high" }
```

## Eyesight break

This is a compact version of the familiar near/far eye-focus drill. It is useful if you spend long stretches staring at a monitor and want a quick guided reset that is short enough to repeat a few times without feeling disruptive.

```toml
[timers.eyesight]
repeat = 3
trigger = { tap = "top" }
on-finished = { vibrate = "mid-low-mid" }
pattern = [
  { name = "far", time = "00:00:15", vibrate = "high" },
  { name = "near", time = "00:00:15", vibrate = "mid-mid" },
]
```
