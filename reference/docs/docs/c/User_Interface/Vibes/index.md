# Vibes

Source: https://developer.repebble.com/docs/c/User_Interface/Vibes/index.html

Controlling the vibration motor

The Vibes API provides calls that let you control Pebble’s vibration motor.

The vibration motor can be used as a visceral mechanism for giving immediate feedback to the user. You can use it to highlight important moments in games, or to draw the attention of the user. However, you should use the vibration feature sparingly, because sustained use will rapidly deplete Pebble’s battery, and vibrating Pebble too much and too often can become annoying for users.

## Function Documentation

void vibes\_cancel(void)

Cancel any in-flight vibe patterns; this is a no-op if there is no on-going vibe.

void vibes\_short\_pulse(void)

Makes the watch emit one short vibration.

void vibes\_long\_pulse(void)

Makes the watch emit one long vibration.

void vibes\_double\_pulse(void)

Makes the watch emit two brief vibrations.

- [SDK 3](javascript:void(0);)
- [SDK 4](javascript:void(0);)
- [SDK 4.9+](javascript:void(0);)

void vibes\_enqueue\_custom\_pattern([VibePattern](/docs/c/User_Interface/Vibes/#VibePattern) pattern)

Makes the watch emit a ‘custom’ vibration pattern.

#### Parameters
 pattern

An arbitrary vibration pattern

#### See Also
[VibePattern](/docs/c/User_Interface/Vibes/#VibePattern)

void vibes\_enqueue\_custom\_pattern([VibePattern](/docs/c/User_Interface/Vibes/#VibePattern) pattern)

Makes the watch emit a ‘custom’ vibration pattern.

#### Parameters
 pattern

An arbitrary vibration pattern

#### See Also
[VibePattern](/docs/c/User_Interface/Vibes/#VibePattern)

void vibes\_enqueue\_custom\_pattern([VibePattern](/docs/c/User_Interface/Vibes/#VibePattern) pattern)

Makes the watch emit a 'custom' vibration pattern.

#### Parameters
 pattern

An arbitrary vibration pattern

#### See Also
[VibePattern](/docs/c/User_Interface/Vibes/#VibePattern)

## Data Structure Documentation

- [SDK 3](javascript:void(0);)
- [SDK 4](javascript:void(0);)
- [SDK 4.9+](javascript:void(0);)

struct VibePattern

Data structure describing a vibration pattern.

A pattern consists of at least 1 vibe-on duration, optionally followed by alternating vibe-off + vibe-on durations. Each segment may have a different duration.

Example code:

```
// Vibe pattern: ON for 200ms, OFF for 100ms, ON for 400ms:static const uint32\_t const segments[] = { 200, 100, 400 };VibePattern pat = {.durations = segments,.num\_segments = ARRAY\_LENGTH(segments),};vibes\_enqueue\_custom\_pattern(pat);
```

#### Data Fields
const [uint32\_t](/docs/c/Standard_C/#uint32_t) \* durations

Pointer to an array of segment durations, measured in milli-seconds.

The maximum allowed duration is 10000ms.

[uint32\_t](/docs/c/Standard_C/#uint32_t) num\_segments

The length of the array of durations.

#### See Also
[vibes\_enqueue\_custom\_pattern](/docs/c/User_Interface/Vibes/#vibes_enqueue_custom_pattern)

struct VibePattern

Data structure describing a vibration pattern.

A pattern consists of at least 1 vibe-on duration, optionally followed by alternating vibe-off + vibe-on durations. Each segment may have a different duration.

Example code:

```
// Vibe pattern: ON for 200ms, OFF for 100ms, ON for 400ms:static const uint32\_t const segments[] = { 200, 100, 400 };VibePattern pat = {.durations = segments,.num\_segments = ARRAY\_LENGTH(segments),};vibes\_enqueue\_custom\_pattern(pat);
```

#### Data Fields
const [uint32\_t](/docs/c/Standard_C/#uint32_t) \* durations

Pointer to an array of segment durations, measured in milli-seconds.

The maximum allowed duration is 10000ms.

[uint32\_t](/docs/c/Standard_C/#uint32_t) num\_segments

The length of the array of durations.

#### See Also
[vibes\_enqueue\_custom\_pattern](/docs/c/User_Interface/Vibes/#vibes_enqueue_custom_pattern)

struct VibePattern

Data structure describing a vibration pattern.

A pattern consists of at least 1 vibe-on duration, optionally followed by alternating vibe-off + vibe-on durations. Each segment may have a different duration.

Example code:

```
// Vibe pattern: ON for 200ms, OFF for 100ms, ON for 400ms:static const uint32\_t segments[] = { 200, 100, 400 };VibePattern pat = {.durations = segments,.num\_segments = ARRAY\_LENGTH(segments),};vibes\_enqueue\_custom\_pattern(pat);
```

#### Data Fields
const [uint32\_t](/docs/c/Standard_C/#uint32_t) \* durations

Pointer to an array of segment durations, measured in milli-seconds.

The maximum allowed duration is 10000ms.

[uint32\_t](/docs/c/Standard_C/#uint32_t) num\_segments

The length of the array of durations.

#### See Also
[vibes\_enqueue\_custom\_pattern](/docs/c/User_Interface/Vibes/#vibes_enqueue_custom_pattern)
