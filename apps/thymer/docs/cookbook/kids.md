# Kids

Sometimes kids need help sharing and time-windowing can be a good strategy to keep the fighting to a minimum.

## Turn sharing

This is a simple turn-taking timer for situations where kids need a visible and non-negotiable handoff point. `must-acknowledge = true` keeps the alert active until someone responds, and `on-press-up = "skip"` makes it easy to move to the next turn when needed.

```toml
[timers.sharing]
repeat = true
must-acknowledge = true
on-press-up = "skip"
trigger = { tap = "left" }
pattern = [
  { name = "Kid 1", time = "00:05:00", vibrate = "high" },
  { name = "Kid 2", time = "00:05:00", vibrate = "high" },
]
```
