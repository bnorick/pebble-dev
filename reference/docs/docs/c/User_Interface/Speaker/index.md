# Speaker

Source: https://developer.repebble.com/docs/c/User_Interface/Speaker/index.html

The APIs on this page will only work with SDK 4.9+.

Controlling the speaker

The Speaker API provides calls that let you play sounds through the watch's speaker. You can play simple note sequences (melodies), single tones, or stream raw PCM audio.

Note sequences are compact representations of melodies using MIDI-like note definitions, supporting 4 basic waveforms: sine, square, triangle, and sawtooth.

Raw PCM streaming allows apps to generate arbitrary audio in configurable formats.

## Function Documentation

bool speaker\_play\_notes(const [SpeakerNote](/docs/c/User_Interface/Speaker/#SpeakerNote) \* notes, [uint32\_t](/docs/c/Standard_C/#uint32_t) num\_notes, uint8\_t volume)

Play a sequence of notes on the speaker.

#### Parameters
 notes

Array of [SpeakerNote](/docs/c/User_Interface/Speaker/#SpeakerNote) structs defining the melody

 num\_notes

Number of notes in the array

 volume

Playback volume (0-100)

#### Returns

true if playback started successfully

bool speaker\_play\_tracks(const [SpeakerTrack](/docs/c/User_Interface/Speaker/#SpeakerTrack) \* tracks, [uint32\_t](/docs/c/Standard_C/#uint32_t) num\_tracks, uint8\_t volume)

Play N monophonic tracks in parallel, mixed (polyphony).

#### Parameters
 tracks

Array of track descriptors (notes + optional sample).

 num\_tracks

Number of tracks. Must be \>= 1 and \<= 4.

 volume

Playback volume (0-100).

#### Returns

true if playback started successfully.

bool speaker\_play\_tone([uint16\_t](/docs/c/Standard_C/#uint16_t) frequency\_hz, [uint32\_t](/docs/c/Standard_C/#uint32_t) duration\_ms, uint8\_t volume, SpeakerWaveform waveform)

Play a single tone on the speaker (convenience wrapper).

#### Parameters
 frequency\_hz

Tone frequency in Hz

 duration\_ms

Tone duration in milliseconds (max 10000)

 volume

Playback volume (0-100)

 waveform

Waveform to use

#### Returns

true if playback started successfully

bool speaker\_stream\_open([SpeakerPcmFormat](/docs/c/User_Interface/Speaker/#SpeakerPcmFormat) format, uint8\_t volume)

Open a raw PCM stream for app-generated audio.

#### Parameters
 format

PCM format specifying sample rate and bit depth

 volume

Playback volume (0-100)

#### Returns

true if stream opened successfully

[uint32\_t](/docs/c/Standard_C/#uint32_t) speaker\_stream\_write(const void \* data, [uint32\_t](/docs/c/Standard_C/#uint32_t) num\_bytes)

Write PCM data to the open stream.

#### Parameters
 data

Buffer of PCM data in the format specified at open

 num\_bytes

Number of bytes to write

#### Returns

Number of bytes actually written (may be less if buffer is full)

void speaker\_stream\_close(void)

Close the PCM stream. Buffered data will be played before stopping.

void speaker\_stop(void)

Stop any active speaker playback immediately.

void speaker\_set\_volume(uint8\_t volume)

Set the speaker volume.

#### Parameters
 volume

Volume level (0-100)

[SpeakerStatus](/docs/c/User_Interface/Speaker/#SpeakerStatus) speaker\_get\_status(void)

Get the current speaker status.

#### Returns

Current [SpeakerStatus](/docs/c/User_Interface/Speaker/#SpeakerStatus)

void speaker\_set\_finish\_callback([SpeakerFinishedCallback](/docs/c/User_Interface/Speaker/#SpeakerFinishedCallback) cb, void \* ctx)

Register a callback invoked when speaker playback ends. The callback runs on the app task.

#### Parameters
 cb

Callback to invoke, or NULL to unregister.

 ctx

User context passed back to cb.

## Data Structure Documentation

struct SpeakerNote

A single note in a sequence. midi\_note: MIDI note number (0-127, 60=C4). 0 = rest (silence). waveform: SpeakerWaveform value. duration\_ms: Note duration in ms (max 10000). velocity: Volume 0-127 (0 = use global volume).

#### Data Fields
uint8\_t midi\_noteuint8\_t waveform[uint16\_t](/docs/c/Standard_C/#uint16_t) duration\_msuint8\_t velocityuint8\_t reserved

struct SpeakerSample

A raw PCM sample that can be pitch-shifted when played by a track. data: mono signed PCM in the given format. num\_bytes: size of data in bytes. format: sample rate + bit depth (see [SpeakerPcmFormat](/docs/c/User_Interface/Speaker/#SpeakerPcmFormat)). base\_midi\_note: the MIDI note at which the sample plays unshifted (e.g. 60 = C4). Notes above/below this value are produced by resampling. loop: if true, the sample restarts from the beginning each time it runs out, and keeps playing until the owning note's duration elapses.

#### Data Fields
const void \* data[uint32\_t](/docs/c/Standard_C/#uint32_t) num\_bytes[SpeakerPcmFormat](/docs/c/User_Interface/Speaker/#SpeakerPcmFormat) formatuint8\_t base\_midi\_notebool loop

struct SpeakerTrack

A single monophonic voice. Multiple tracks are mixed together by [speaker\_play\_tracks()](/docs/c/User_Interface/Speaker/#speaker_play_tracks) to produce polyphony. notes: array of notes to play sequentially. num\_notes: length of the notes array. sample: if non-NULL, notes are played by pitch-shifting this sample; note.waveform is ignored. If NULL, notes use their waveform field.

#### Data Fields
const [SpeakerNote](/docs/c/User_Interface/Speaker/#SpeakerNote) \* notes[uint32\_t](/docs/c/Standard_C/#uint32_t) num\_notesconst [SpeakerSample](/docs/c/User_Interface/Speaker/#SpeakerSample) \* sample

## Enum Documentation

enum SpeakerWaveform

#### Enumerators
SpeakerWaveformSineSpeakerWaveformSquareSpeakerWaveformTriangleSpeakerWaveformSawtoothSpeakerWaveformCount

enum SpeakerPcmFormat

PCM audio format for speaker streaming. Bit layout: bit0 = sample rate (0=8kHz, 1=16kHz), bit1 = bit depth (0=8-bit, 1=16-bit). All formats are mono signed PCM (8-bit samples are signed [-128,127], not unsigned).

#### Enumerators
SpeakerPcmFormat\_8kHz\_8bit

8kHz 8-bit signed (1 byte/sample)

SpeakerPcmFormat\_16kHz\_8bit

16kHz 8-bit signed (1 byte/sample)

SpeakerPcmFormat\_8kHz\_16bit

8kHz 16-bit signed little-endian (2 bytes/sample)

SpeakerPcmFormat\_16kHz\_16bit

16kHz 16-bit signed little-endian (2 bytes/sample)

SpeakerPcmFormatCount

enum SpeakerStatus

Speaker status.

#### Enumerators
SpeakerStatusIdleSpeakerStatusPlayingSpeakerStatusDraining

enum SpeakerFinishReason

Reason reported when speaker playback ends.

#### Enumerators
SpeakerFinishReasonDone

Playback completed naturally.

SpeakerFinishReasonStopped

Playback was stopped by the app.

SpeakerFinishReasonPreempted

Preempted by higher priority source.

SpeakerFinishReasonError

An error occurred.

## Typedef Documentation

 typedef void(\* SpeakerFinishedCallback)(SpeakerFinishReason reason, void \*ctx) 

Callback invoked when playback finishes.

#### Parameters
 reason

Why playback ended

 ctx

User context
