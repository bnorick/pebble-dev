# Triggers

Each timer must define a trigger. Triggers are matched on touch-capable watches and used to quick-select timers on the watch.

## Tap triggers

Tap triggers use a single zone:

```toml
trigger = { tap = "top" }
```

Accepted zone names:

- `left` or `l`
- `top` or `t`
- `right` or `r`
- `bottom` or `b`
- `center` or `c`

## Swipe triggers

Swipe triggers use a `from-to` pair:

```toml
trigger = { swipe = "l-to-r" }
```

The same zone aliases apply on both sides of the swipe.

Directional aliases are also accepted:

- `left` or `l` means `right-to-left`
- `up` or `u` means `bottom-to-top`
- `right` or `r` means `left-to-right`
- `down` or `d` means `top-to-bottom`

Example:

```toml
trigger = { swipe = "up" }
```

On the watch, Thymer first checks the exact `from-to` pair, then falls back to the directional form. That keeps existing zone-pair triggers like `c-to-b` working while making simple directional swipes easier to use reliably.

## Uniqueness

Triggers do not need to be unique. Multiple timers can share the same trigger definition, which is useful when you want one gesture to rotate through a group of related timers.

When multiple timers share a trigger, Thymer loops through the matching timers each time you use that trigger.

That means all of these are valid:

- multiple taps from the same zone
- multiple swipes with the same `from` and `to`

## Invalid examples

```toml
trigger = { tap = "north" }
```

```toml
trigger = { swipe = "left-right" }
```
