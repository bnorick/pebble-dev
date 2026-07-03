# Triggers

Each timer must define a unique trigger. Triggers are matched on touch-capable watches and used to quick-select the timer on the watch.

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

## Uniqueness

Two timers cannot share the same trigger definition. The validator compares:

- trigger kind
- source zone
- destination zone

That means all of these must be unique across timers:

- taps from the same zone
- swipes with the same `from` and `to`

## Invalid examples

```toml
trigger = { tap = "north" }
```

```toml
trigger = { swipe = "left-right" }
```
