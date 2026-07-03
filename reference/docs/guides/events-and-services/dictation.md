# Dictation

Source: https://developer.repebble.com/guides/events-and-services/dictation/

**PLATFORM NOTICE**  
 This guide does not apply to apps built to run on the Aplite platform (Pebble Classic, Pebble Steel).

On hardware [platforms](/faqs.md#pebble-sdk) supporting a microphone, the [`Dictation`](/docs/c/Foundation/Dictation/ "Dictation") API can be used to gather arbitrary text input from a user. This approach is much faster than any previous button-based text input system (such as [tertiary text](https://github.com/vgmoose/tertiary_text)), and includes the ability to allow users to re-attempt dictation if there are any errors in the returned transcription.

> Note: Apps running on multiple hardware platforms that may or may not include a microphone should use the `PBL_MICROPHONE` compile-time define (as well as checking API return values) to gracefully handle when it is not available.

## How the Dictation API Works

The [`Dictation`](/docs/c/Foundation/Dictation/ "Dictation") API invokes the same UI that is shown to the user when responding to notifications via the system menu, with events occuring in the following order:

- The user initiates transcription and the dictation UI is displayed.

- The user dictates the phrase they would like converted into text.

- The audio is transmitted via the Pebble phone application to a 3rd party service and translated into text.

- When the text is returned, the user is given the opportunity to review the result of the transcription. At this time they may elect to re-attempt the dictation by pressing the Back button and speaking clearer.

- When the user is happy with the transcription, the text is provided to the app by pressing the Select button.

- If an error occurs in the transcription attempt, the user is automatically allowed to re-attempt the dictation.

- The user can retry their dictation by rejecting a successful transcription, but only if confirmation dialogs are enabled.

## Beginning a Dictation Session

To get voice input from a user, an app must first create a [`DictationSession`](/docs/c/Foundation/Dictation/#DictationSession "DictationSession")that contains data relating to the status of the dictation service, as well as an allocated buffer to store the result of any transcriptions. This should be declared in the file-global scope (as `static`), so it can be used at any time (in button click handlers, for example).

```
static DictationSession \*s\_dictation\_session;
```

A callback of type [`DictationSessionStatusCallback`](/docs/c/Foundation/Dictation/#DictationSessionStatusCallback "DictationSessionStatusCallback") is also required to notify the developer to the status of any dictation requests and transcription results. This is called at any time the dictation UI exits, which can be for any of the following reasons:

- The user accepts a transcription result.

- A transcription is successful but the confirmation dialog is disabled.

- The user exits the dictation UI with the Back button.

- When any error occurs and the error dialogs are disabled.

- Too many transcription errors occur.

```
static void dictation\_session\_callback(DictationSession \*session, DictationSessionStatus status,char \*transcription, void \*context) {// Print the results of a transcription attemptAPP\_LOG(APP\_LOG\_LEVEL\_INFO, "Dictation status: %d", (int)status);}
```

At the end of this callback the `transcription` pointer becomes invalid - if the text is required later it should be copied into a separate buffer provided by the app. The size of this dictation buffer is chosen by the developer, and should be large enough to accept all expected input. Any transcribed text longer than the length of the buffer will be truncated.

```
// Declare a buffer for the DictationSessionstatic char s\_last\_text[512];
```

Finally, create the [`DictationSession`](/docs/c/Foundation/Dictation/#DictationSession "DictationSession") and supply the size of the buffer and the [`DictationSessionStatusCallback`](/docs/c/Foundation/Dictation/#DictationSessionStatusCallback "DictationSessionStatusCallback"). This session may be used as many times as requires for multiple transcriptions. A context pointer may also optionally be provided.

```
// Create new dictation sessions\_dictation\_session = dictation\_session\_create(sizeof(s\_last\_text),dictation\_session\_callback, NULL);
```

## Obtaining Dictated Text

After creating a [`DictationSession`](/docs/c/Foundation/Dictation/#DictationSession "DictationSession"), the developer can begin a dictation attempt at any time, providing that one is not already in progress.

```
// Start dictation UIdictation\_session\_start(s\_dictation\_session);
```

The dictation UI will be displayed and the user will speak their desired input.

![listening](/assets/images/guides/pebble-apps/sensors/listening.png)

It is recommended to provide visual guidance on the format of the expected input before the [`dictation_session_start()`](/docs/c/Foundation/Dictation/#dictation_session_start "dictation\_session\_start") is called. For example, if the user is expected to speak a location that should be a city name, they should be briefed as such before being asked to provide input.

When the user exits the dictation UI, the developer's[`DictationSessionStatusCallback`](/docs/c/Foundation/Dictation/#DictationSessionStatusCallback "DictationSessionStatusCallback") will be called. The `status` parameter provided will inform the developer as to whether or not the transcription was successful using a [`DictationSessionStatus`](/docs/c/Foundation/Dictation/#DictationSessionStatus "DictationSessionStatus") value. It is useful to check this value, as there are multiple reasons why a dictation request may not yield a successful result. These values are described below under[_DictationSessionStatus Values_](#dictationsessionstatus-values).

If the value of `status` is equal to [`DictationSessionStatusSuccess`](/docs/c/Foundation/Dictation/#DictationSessionStatusSuccess "DictationSessionStatusSuccess"), the transcription was successful. The user's input can be read from the`transcription` parameter for evaluation and storage for later use if required. Note that once the callback returns, `transcription` will no longer be valid.

For example, a [`TextLayer`](/docs/c/User_Interface/Layers/TextLayer/ "TextLayer") in the app's UI with variable name `s_output_layer`may be used to show the status of an attempted transcription:

```
if(status == DictationSessionStatusSuccess) {// Display the dictated textsnprintf(s\_last\_text, sizeof(s\_last\_text), "Transcription:\n\n%s", transcription);text\_layer\_set\_text(s\_output\_layer, s\_last\_text);} else {// Display the reason for any errorstatic char s\_failed\_buff[128];snprintf(s\_failed\_buff, sizeof(s\_failed\_buff), "Transcription failed.\n\nReason:\n%d",(int)status);text\_layer\_set\_text(s\_output\_layer, s\_failed\_buff);}
```

The confirmation mechanism allowing review of the transcription result can be disabled if it is not needed. An example of such a scenario may be to speed up a 'yes' or 'no' decision where the two expected inputs are distinct and different.

```
// Disable the confirmation screendictation\_session\_enable\_confirmation(s\_dictation\_session, false);
```

It is also possible to disable the error dialogs, if so desired. This will disable the dialogs that appear when a transcription attempt fails, as well as disabling the ability to retry the dictation if a failure occurs.

```
// Disable error dialogsdictation\_session\_enable\_error\_dialogs(s\_dictation\_session, false);
```

### DictationSessionStatus Values

These are the possible values provided by a [`DictationSessionStatusCallback`](/docs/c/Foundation/Dictation/#DictationSessionStatusCallback "DictationSessionStatusCallback"), and should be used to handle transcription success or failure for any of the following reasons.

| Status | Value | Description |
| --- | --- | --- |
| [`DictationSessionStatusSuccess`](/docs/c/Foundation/Dictation/#DictationSessionStatusSuccess "DictationSessionStatusSuccess") | `0` | Transcription successful, with a valid result. |
| [`DictationSessionStatusFailureTranscriptionRejected`](/docs/c/Foundation/Dictation/#DictationSessionStatusFailureTranscriptionRejected "DictationSessionStatusFailureTranscriptionRejected") | `1` | User rejected transcription and dismissed the dictation UI. |
| [`DictationSessionStatusFailureTranscriptionRejectedWithError`](/docs/c/Foundation/Dictation/#DictationSessionStatusFailureTranscriptionRejectedWithError "DictationSessionStatusFailureTranscriptionRejectedWithError") | `2` | User exited the dictation UI after a transcription error. |
| [`DictationSessionStatusFailureSystemAborted`](/docs/c/Foundation/Dictation/#DictationSessionStatusFailureSystemAborted "DictationSessionStatusFailureSystemAborted") | `3` | Too many errors occurred during transcription and the dictation UI exited. |
| [`DictationSessionStatusFailureNoSpeechDetected`](/docs/c/Foundation/Dictation/#DictationSessionStatusFailureNoSpeechDetected "DictationSessionStatusFailureNoSpeechDetected") | `4` | No speech was detected and the dictation UI exited. |
| [`DictationSessionStatusFailureConnectivityError`](/docs/c/Foundation/Dictation/#DictationSessionStatusFailureConnectivityError "DictationSessionStatusFailureConnectivityError") | `5` | No Bluetooth or Internet connection available. |
| [`DictationSessionStatusFailureDisabled`](/docs/c/Foundation/Dictation/#DictationSessionStatusFailureDisabled "DictationSessionStatusFailureDisabled") | `6` | Voice transcription disabled for this user. This can occur if the user has disabled sending 'Usage logs' in the Pebble mobile app. |
| [`DictationSessionStatusFailureInternalError`](/docs/c/Foundation/Dictation/#DictationSessionStatusFailureInternalError "DictationSessionStatusFailureInternalError") | `7` | Voice transcription failed due to an internal error. |
| [`DictationSessionStatusFailureRecognizerError`](/docs/c/Foundation/Dictation/#DictationSessionStatusFailureRecognizerError "DictationSessionStatusFailureRecognizerError") | `8` | Cloud recognizer failed to transcribe speech (only possible if error dialogs are disabled). |
