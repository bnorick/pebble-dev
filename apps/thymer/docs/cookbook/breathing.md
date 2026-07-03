# Breathing

Breathing timers are a strong fit for Thymer because the watch can carry the cadence through short labels and light tactile cues.

These examples work well as a pair on the same trigger. Because Thymer cycles through timers that share a trigger, you can keep both on `tap = "right"` and switch between a steady box breath and a longer calming breath without spending another gesture.

If you want to use the `superlow` vibration name shown here, define it once in your shared vibration config:

```toml
[vibration]
superlow = 60
```

## Square breathing

Square breathing is a balanced cadence that is easy to memorize and useful for quick regulation, transition moments, or settling before a meeting.

```toml
[timers.square]
repeat = true
trigger = { tap = "right" }
pattern = [
  { description = "in", time = "00:00:04", vibrate = "superlow" },
  { description = "hold", time = "00:00:04", vibrate = "superlow" },
  { description = "out", time = "00:00:04", vibrate = "superlow" },
  { description = "hold", time = "00:00:04", vibrate = "superlow" },
]
```

## 4-7-8 breathing

This one stretches the exhale longer than the inhale, which many people find better for winding down. Hiding the text on demand can also make it easier to run by feel once the pattern is familiar.

If you want a discreet breathing timer, pairing `on-press-up = "hide"` with very subtle vibrations like `superlow` leaves just a nice sprig of Thyme on your wrist.

```toml
[timers.478]
name = "4-7-8"
repeat = true
on-press-up = "hide"
trigger = { tap = "right" }
pattern = [
  { description = "in", time = "00:00:04", vibrate = "superlow" },
  { description = "hold", time = "00:00:07", vibrate = "superlow-superlow" },
  { description = "out", time = "00:00:08", vibrate = "superlow-superlow-superlow" },
]
```
