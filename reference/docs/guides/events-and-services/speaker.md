# Speaker

Source: https://developer.repebble.com/guides/events-and-services/speaker/

On hardware platforms with a built-in speaker, the Speaker API gives apps four different ways to make sound:

- A **one-shot tone** , for short beeps and confirmation sounds.
- A **note sequence** , for monophonic melodies that the system synthesizes from a chosen waveform.
- **Polyphonic tracks** , where up to four voices are mixed together, each optionally backed by a pitch-shifted PCM sample.
- **PCM streaming** , for arbitrary audio that the app generates or decodes on the fly.

All four paths share the same volume control, status reporting, and finished-callback mechanism, so an app can mix and match them as it needs to.

## Volume

Every speaker call takes a volume argument in the range `0`–`100`. The global volume can also be changed at any time, including while audio is playing:

```
speaker\_set\_volume(60);
```

For note sequences, individual notes can override the global volume by setting their `velocity` field (`1`–`127`); a velocity of `0` means "use the global volume."

## Playing a One-Shot Tone

The simplest path is `speaker_play_tone()`, which plays a single frequency with a chosen waveform for up to ten seconds. It's well suited to UI beeps, alarms, and confirmation sounds:

```
// Play a 440 Hz sine wave for 250 ms at 80% volumespeaker\_play\_tone(440, 250, 80, SpeakerWaveformSine);
```

The available waveforms are:

| Waveform | Description |
| --- | --- |
| [`SpeakerWaveformSine`](/docs/c/User_Interface/Speaker/#SpeakerWaveformSine "SpeakerWaveformSine") | Smooth sine wave; the gentlest option. |
| [`SpeakerWaveformSquare`](/docs/c/User_Interface/Speaker/#SpeakerWaveformSquare "SpeakerWaveformSquare") | Hollow, retro square wave. |
| [`SpeakerWaveformTriangle`](/docs/c/User_Interface/Speaker/#SpeakerWaveformTriangle "SpeakerWaveformTriangle") | Brighter than a sine, softer than a square. |
| [`SpeakerWaveformSawtooth`](/docs/c/User_Interface/Speaker/#SpeakerWaveformSawtooth "SpeakerWaveformSawtooth") | Buzzy, harmonically rich sawtooth. |

`speaker_play_tone()` returns `true` if playback started, or `false` if the duration is out of range or the speaker is busy with a different request.

## Playing a Note Sequence

For monophonic melodies, build an array of [`SpeakerNote`](/docs/c/User_Interface/Speaker/#SpeakerNote "SpeakerNote") values and hand it to `speaker_play_notes()`. Each note carries a MIDI note number, a waveform, a duration in milliseconds (capped at 10000), and an optional per-note velocity:

```
// A short C-major arpeggiostatic const SpeakerNote s\_arpeggio[] = {{ .midi\_note = 60, .waveform = SpeakerWaveformSine,.duration\_ms = 200 }, // C4{ .midi\_note = 64, .waveform = SpeakerWaveformSine,.duration\_ms = 200 }, // E4{ .midi\_note = 67, .waveform = SpeakerWaveformSine,.duration\_ms = 200 }, // G4{ .midi\_note = 72, .waveform = SpeakerWaveformTriangle, .duration\_ms = 400 }, // C5};speaker\_play\_notes(s\_arpeggio, ARRAY\_LENGTH(s\_arpeggio), 80);
```

A `midi_note` of `0` is treated as a rest of the given duration. MIDI note`60` is middle C (C4), and the standard MIDI note numbering applies.

## Playing Polyphonic Tracks

`speaker_play_tracks()` mixes up to four [`SpeakerTrack`](/docs/c/User_Interface/Speaker/#SpeakerTrack "SpeakerTrack") voices together. Each track is its own monophonic note sequence, so four tracks together can play a four-voice harmony. Each track may also point at a [`SpeakerSample`](/docs/c/User_Interface/Speaker/#SpeakerSample "SpeakerSample"), which causes the synthesizer to pitch-shift that PCM sample to the requested note instead of generating a waveform:

```
static const SpeakerNote s\_melody[] = {{ .midi\_note = 72, .waveform = SpeakerWaveformSine, .duration\_ms = 250 },{ .midi\_note = 74, .waveform = SpeakerWaveformSine, .duration\_ms = 250 },{ .midi\_note = 76, .waveform = SpeakerWaveformSine, .duration\_ms = 500 },};static const SpeakerNote s\_bass[] = {{ .midi\_note = 48, .waveform = SpeakerWaveformTriangle, .duration\_ms = 500 },{ .midi\_note = 50, .waveform = SpeakerWaveformTriangle, .duration\_ms = 500 },};static const SpeakerTrack s\_tracks[] = {{ .notes = s\_melody, .num\_notes = ARRAY\_LENGTH(s\_melody) },{ .notes = s\_bass,.num\_notes = ARRAY\_LENGTH(s\_bass)},};speaker\_play\_tracks(s\_tracks, ARRAY\_LENGTH(s\_tracks), 80);
```

To use a sample instead of a synthesized waveform, fill in a[`SpeakerSample`](/docs/c/User_Interface/Speaker/#SpeakerSample "SpeakerSample") and point the track at it. The sample's `base_midi_note`specifies which note plays the sample at its original pitch; other notes in the track are produced by pitch-shifting the same sample. Setting `loop` to`true` lets a short sample sustain through longer notes:

```
static const SpeakerSample s\_kick = {.data= kick\_pcm\_data,.num\_bytes= sizeof(kick\_pcm\_data),.format= SpeakerPcmFormat\_16kHz\_16bit,.base\_midi\_note = 36,// C2.loop= false,};static const SpeakerTrack s\_drum\_track = {.notes= s\_drum\_notes,.num\_notes = ARRAY\_LENGTH(s\_drum\_notes),.sample= &s\_kick,};
```

Pass between 1 and 4 tracks to `speaker_play_tracks()`. Tracks beyond the fourth are not supported.

## Streaming PCM

For arbitrary audio - synthesised on the fly, decoded from a downloaded file, or generated procedurally - open a PCM stream, push bytes into it, and close it when done.

Open a stream by choosing one of the supported PCM formats and a starting volume:

```
if (!speaker\_stream\_open(SpeakerPcmFormat\_16kHz\_16bit, 80)) {// Speaker was busy or unavailablereturn;}
```

The supported formats are all mono, signed PCM:

| Format | Bytes / sample | Sample rate |
| --- | --- | --- |
| [`SpeakerPcmFormat_8kHz_8bit`](/docs/c/User_Interface/Speaker/#SpeakerPcmFormat_8kHz_8bit "SpeakerPcmFormat\_8kHz\_8bit") | 1 | 8 kHz |
| [`SpeakerPcmFormat_16kHz_8bit`](/docs/c/User_Interface/Speaker/#SpeakerPcmFormat_16kHz_8bit "SpeakerPcmFormat\_16kHz\_8bit") | 1 | 16 kHz |
| [`SpeakerPcmFormat_8kHz_16bit`](/docs/c/User_Interface/Speaker/#SpeakerPcmFormat_8kHz_16bit "SpeakerPcmFormat\_8kHz\_16bit") | 2 (little-endian) | 8 kHz |
| [`SpeakerPcmFormat_16kHz_16bit`](/docs/c/User_Interface/Speaker/#SpeakerPcmFormat_16kHz_16bit "SpeakerPcmFormat\_16kHz\_16bit") | 2 (little-endian) | 16 kHz |

Then push samples into the stream. `speaker_stream_write()` returns the number of bytes it actually accepted, which may be less than the amount requested if the internal buffer is full. Loop and retry the remainder:

```
const uint8\_t \*cursor = buffer;uint32\_t remaining = buffer\_size;while (remaining \> 0) {uint32\_t written = speaker\_stream\_write(cursor, remaining);cursor+= written;remaining -= written;if (written == 0) {// Buffer is full - yield briefly and try againpsleep(5);}}
```

When all of the audio has been written, close the stream. `speaker_stream_close()` drains anything still buffered before it stops the speaker, so it's safe to call as soon as the last byte has been written:

```
speaker\_stream\_close();
```

## Stopping Playback Early

Any playback path can be stopped immediately with:

```
speaker\_stop();
```

This applies equally to tones, note sequences, polyphonic tracks, and PCM streams. If a finish callback is registered, it will fire with the[`SpeakerFinishReasonStopped`](/docs/c/User_Interface/Speaker/#SpeakerFinishReasonStopped "SpeakerFinishReasonStopped") reason.

## Knowing When Playback Ends

To find out when playback finishes - naturally or otherwise - register a finish callback before starting playback:

```
static void speaker\_finished(SpeakerFinishReason reason, void \*ctx) {switch (reason) {case SpeakerFinishReasonDone:APP\_LOG(APP\_LOG\_LEVEL\_INFO, "Playback completed");break;case SpeakerFinishReasonStopped:APP\_LOG(APP\_LOG\_LEVEL\_INFO, "Stopped by the app");break;case SpeakerFinishReasonPreempted:APP\_LOG(APP\_LOG\_LEVEL\_INFO, "Preempted by the system");break;case SpeakerFinishReasonError:APP\_LOG(APP\_LOG\_LEVEL\_ERROR, "Playback error");break;}}speaker\_set\_finish\_callback(speaker\_finished, NULL);speaker\_play\_notes(s\_arpeggio, ARRAY\_LENGTH(s\_arpeggio), 80);
```

The callback runs on the app task, so it's safe to update UI or kick off follow-up playback from inside it.

The current state can also be polled at any time with `speaker_get_status()`, which returns one of:

| Status | Meaning |
| --- | --- |
| [`SpeakerStatusIdle`](/docs/c/User_Interface/Speaker/#SpeakerStatusIdle "SpeakerStatusIdle") | Nothing is playing. |
| [`SpeakerStatusPlaying`](/docs/c/User_Interface/Speaker/#SpeakerStatusPlaying "SpeakerStatusPlaying") | A tone, sequence, track set, or stream is actively playing. |
| [`SpeakerStatusDraining`](/docs/c/User_Interface/Speaker/#SpeakerStatusDraining "SpeakerStatusDraining") | Playback has stopped accepting new input and is finishing the buffered audio. |

## Detecting Speaker Support

Not every platform has a built-in speaker. There are two ways to handle this:

At compile time, the `PBL_SPEAKER` preprocessor define is present on platforms that have a speaker, so speaker-specific code can be excluded entirely from builds for platforms that don't:

```
#if defined(PBL\_SPEAKER)speaker\_play\_tone(440, 250, 80, SpeakerWaveformSine);#elsevibes\_short\_pulse();#endif
```

At runtime, `speaker_play_tone()`, `speaker_play_notes()`,`speaker_play_tracks()`, and `speaker_stream_open()` all return `false` on platforms without a speaker (or when the speaker is busy with another request), so apps that always call through the API can just check the return value and fall back to vibration or a visual cue.

## Battery Considerations

Driving the speaker is one of the most power-hungry things an app can do. Long PCM streams in particular keep the audio hardware powered and the CPU busy moving samples into the buffer. Use the speaker for short, intentional sounds - confirmations, alarms, brief melodies - and prefer`speaker_play_tone()` or `speaker_play_notes()` over PCM streaming whenever a synthesized sound would do the job.
