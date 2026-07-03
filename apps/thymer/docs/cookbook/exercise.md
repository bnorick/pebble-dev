# Exercise

Exercise timers benefit from short labels, decisive vibrations, and patterns you can run without needing to read much once you know the flow.

## 7-minute workout

Thymer needs a bit of work on long names, I'll get to it. This is the 7-minute workout, obviously.

```toml
[timers.7-min]
trigger = { tap = "bottom" }
vibrate = "high-high"
pattern = [
  { description = "get ready", time = 10 },
  { description = "jumping jack", time = 30 },
  { description = "rest: wall sit", time = 10 },
  { description = "wall sit", time = 30 },
  { description = "rest: push-up", time = 10 },
  { description = "push-up", time = 30 },
  { description = "rest: crunch", time = 10 },
  { description = "crunch", time = 30 },
  { description = "rest: step-up onto chair", time = 10 },
  { description = "step-up onto chair", time = 30 },
  { description = "rest: squat", time = 10 },
  { description = "squat", time = 30 },
  { description = "rest: tricep dip", time = 10 },
  { description = "tricep dip", time = 30 },
  { description = "rest: plank", time = 10 },
  { description = "plank", time = 30 },
  { description = "rest: high knees run", time = 10 },
  { description = "high knees run", time = 30 },
  { description = "rest: lunge", time = 10 },
  { description = "lunge", time = 30 },
  { description = "rest: push+rotate", time = 10 },
  { description = "push-up and rotation", time = 30 },
  { description = "rest: side plank", time = 10 },
  { description = "side plank", time = 30 },
  { description = "done", time = 10 },
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
  { description = "far", time = "00:00:15", vibrate = "high" },
  { description = "near", time = "00:00:15", vibrate = "mid-mid" },
]
```
