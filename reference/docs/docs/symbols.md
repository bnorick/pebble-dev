# symbols

Source: https://developer.repebble.com/docs/symbols/

| c | [Foundation](/docs/c/Foundation/) |
| 

The core of the Pebble SDK.

 |
| c | [Alloy](/docs/c/Foundation/Alloy/) |
| |
| c | [kModdableCreationFlagLogInstrumentation](/docs/c/Foundation/Alloy/#kModdableCreationFlagLogInstrumentation) |
| 

Flag to enable XS instrumentation logging over Bluetooth. When set, the Moddable XS engine will log instrumentation data (e.g. memory usage, slot/chunk/stack statistics) via app\_log. Logging is only active when a Bluetooth log listener is connected; otherwise this flag has no effect.

 |
| c | [moddable\_createMachine](/docs/c/Foundation/Alloy/#moddable_createMachine) |
| 

Create and start a Moddable XS virtual machine for an Alloy app.

 |
| c | [ModdableCreationRecord](/docs/c/Foundation/Alloy/#ModdableCreationRecord) |
| 

Configuration record for creating a Moddable XS virtual machine. Used with [moddable\_createMachine()](/docs/c/Foundation/Alloy/#moddable_createMachine) to customize the JS runtime. Set recordSize to sizeof(ModdableCreationRecord) for version compatibility.

 |
| c | [App](/docs/c/Foundation/App/) |
| 

App entry point and event loop.

 |
| c | [app\_event\_loop](/docs/c/Foundation/App/#app_event_loop) |
| 

The event loop for C apps, to be used in app's main(). Will block until the app is ready to exit.

 |
| c | [App Communication](/docs/c/Foundation/App_Communication/) |
| 

API for interacting with the Pebble communication subsystem.

 |
| c | [SniffInterval](/docs/c/Foundation/App_Communication/#SniffInterval) |
| 

Intervals during which the Bluetooth module may enter a low power mode. The sniff interval defines the period during which the Bluetooth module may not exchange (ACL) packets. The longer the sniff interval, the more time the Bluetooth module may spend in a low power mode. It may be necessary to reduce the sniff interval if an app requires reduced latency when sending messages.

 |
| c | [SNIFF\_INTERVAL\_NORMAL](/docs/c/Foundation/App_Communication/#SNIFF_INTERVAL_NORMAL) |
| 

Set the sniff interval to normal (power-saving) mode.

 |
| c | [SNIFF\_INTERVAL\_REDUCED](/docs/c/Foundation/App_Communication/#SNIFF_INTERVAL_REDUCED) |
| 

Reduce the sniff interval to increase the responsiveness of the radio at the expense of increasing Bluetooth energy consumption by a multiple of 2-5 (very significant)

 |
| c | [app\_comm\_set\_sniff\_interval](/docs/c/Foundation/App_Communication/#app_comm_set_sniff_interval) |
| 

Set the Bluetooth module's sniff interval. The sniff interval will be restored to normal by the OS after the app's de-init handler is called. Set the sniff interval to normal whenever possible.

 |
| c | [app\_comm\_get\_sniff\_interval](/docs/c/Foundation/App_Communication/#app_comm_get_sniff_interval) |
| 

Get the Bluetooth module's sniff interval.

 |
| c | [App Glance](/docs/c/Foundation/App_Glance/) |
| 

API for the application to modify its "glance" i.e. app menu subtitle.

 |
| c | [PublishedId](/docs/c/Foundation/App_Glance/#PublishedId) |
| 

The ID of a published app resource defined within the publishedMedia section of package.json.

 |
| c | [APP\_GLANCE\_SLICE\_NO\_EXPIRATION](/docs/c/Foundation/App_Glance/#APP_GLANCE_SLICE_NO_EXPIRATION) |
| 

Can be used for the expiration\_time of an [AppGlanceSlice](/docs/c/Foundation/App_Glance/#AppGlanceSlice) so that the slice never expires.

 |
| c | [APP\_GLANCE\_SLICE\_DEFAULT\_ICON](/docs/c/Foundation/App_Glance/#APP_GLANCE_SLICE_DEFAULT_ICON) |
| 

Can be used for the icon of an [AppGlanceSlice](/docs/c/Foundation/App_Glance/#AppGlanceSlice) so that the slice displays the app's default icon.

 |
| c | [AppGlanceResult](/docs/c/Foundation/App_Glance/#AppGlanceResult) |
| 

Bitfield enum describing the result of trying to add an [AppGlanceSlice](/docs/c/Foundation/App_Glance/#AppGlanceSlice) to an app's glance.

 |
| c | [APP\_GLANCE\_RESULT\_SUCCESS](/docs/c/Foundation/App_Glance/#APP_GLANCE_RESULT_SUCCESS) |
| 

The slice was successfully added to the app's glance.

 |
| c | [APP\_GLANCE\_RESULT\_INVALID\_TEMPLATE\_STRING](/docs/c/Foundation/App_Glance/#APP_GLANCE_RESULT_INVALID_TEMPLATE_STRING) |
| 

The subtitle\_template\_string provided in the slice was invalid.

 |
| c | [APP\_GLANCE\_RESULT\_TEMPLATE\_STRING\_TOO\_LONG](/docs/c/Foundation/App_Glance/#APP_GLANCE_RESULT_TEMPLATE_STRING_TOO_LONG) |
| 

The subtitle\_template\_string provided in the slice was longer than 150 bytes.

 |
| c | [APP\_GLANCE\_RESULT\_INVALID\_ICON](/docs/c/Foundation/App_Glance/#APP_GLANCE_RESULT_INVALID_ICON) |
| 

The icon provided in the slice was invalid.

 |
| c | [APP\_GLANCE\_RESULT\_SLICE\_CAPACITY\_EXCEEDED](/docs/c/Foundation/App_Glance/#APP_GLANCE_RESULT_SLICE_CAPACITY_EXCEEDED) |
| 

The provided slice would exceed the app glance's slice capacity.

 |
| c | [APP\_GLANCE\_RESULT\_EXPIRES\_IN\_THE\_PAST](/docs/c/Foundation/App_Glance/#APP_GLANCE_RESULT_EXPIRES_IN_THE_PAST) |
| 

The expiration\_time provided in the slice expires in the past.

 |
| c | [APP\_GLANCE\_RESULT\_INVALID\_SESSION](/docs/c/Foundation/App_Glance/#APP_GLANCE_RESULT_INVALID_SESSION) |
| 

The AppGlanceReloadSession provided was invalid.

 |
| c | [AppGlanceReloadSession](/docs/c/Foundation/App_Glance/#AppGlanceReloadSession) |
| |
| c | [app\_glance\_add\_slice](/docs/c/Foundation/App_Glance/#app_glance_add_slice) |
| 

Add a slice to the app's glance. This function will only succeed if called with a valid AppGlanceReloadSession that is provided in an [AppGlanceReloadCallback](/docs/c/Foundation/App_Glance/#AppGlanceReloadCallback).

 |
| c | [AppGlanceReloadCallback](/docs/c/Foundation/App_Glance/#AppGlanceReloadCallback) |
| 

User-provided callback for reloading the slices in the app's glance.

 |
| c | [app\_glance\_reload](/docs/c/Foundation/App_Glance/#app_glance_reload) |
| 

Clear any existing slices in the app's glance and trigger a reload via the provided callback.

 |
| c | [AppGlanceSlice](/docs/c/Foundation/App_Glance/#AppGlanceSlice) |
| 

An app's glance can change over time as defined by zero or more app glance slices that each describe the state of the app glance at a particular point in time. Slices are displayed in the order they are added, and they are removed at the specified expiration time.

 |
| c | [AppGlanceSliceLayout](/docs/c/Foundation/App_Glance/#AppGlanceSliceLayout) |
| 

Describes how the slice should be visualized in the app's glance in the launcher.

 |
| c | [AppMessage](/docs/c/Foundation/AppMessage/) |
| |
| c | [AppMessageResult](/docs/c/Foundation/AppMessage/#AppMessageResult) |
| 

AppMessage result codes.

 |
| c | [APP\_MSG\_OK](/docs/c/Foundation/AppMessage/#APP_MSG_OK) |
| 

(0) All good, operation was successful.

 |
| c | [APP\_MSG\_SEND\_TIMEOUT](/docs/c/Foundation/AppMessage/#APP_MSG_SEND_TIMEOUT) |
| 

(2) The other end did not confirm receiving the sent data with an (n)ack in time.

 |
| c | [APP\_MSG\_SEND\_REJECTED](/docs/c/Foundation/AppMessage/#APP_MSG_SEND_REJECTED) |
| 

(4) The other end rejected the sent data, with a "nack" reply.

 |
| c | [APP\_MSG\_NOT\_CONNECTED](/docs/c/Foundation/AppMessage/#APP_MSG_NOT_CONNECTED) |
| 

(8) The other end was not connected.

 |
| c | [APP\_MSG\_APP\_NOT\_RUNNING](/docs/c/Foundation/AppMessage/#APP_MSG_APP_NOT_RUNNING) |
| 

(16) The local application was not running.

 |
| c | [APP\_MSG\_INVALID\_ARGS](/docs/c/Foundation/AppMessage/#APP_MSG_INVALID_ARGS) |
| 

(32) The function was called with invalid arguments.

 |
| c | [APP\_MSG\_BUSY](/docs/c/Foundation/AppMessage/#APP_MSG_BUSY) |
| 

(64) There are pending (in or outbound) messages that need to be processed first before new ones can be received or sent.

 |
| c | [APP\_MSG\_BUFFER\_OVERFLOW](/docs/c/Foundation/AppMessage/#APP_MSG_BUFFER_OVERFLOW) |
| 

(128) The buffer was too small to contain the incoming message.

 |
| c | [APP\_MSG\_ALREADY\_RELEASED](/docs/c/Foundation/AppMessage/#APP_MSG_ALREADY_RELEASED) |
| 

(512) The resource had already been released.

 |
| c | [APP\_MSG\_CALLBACK\_ALREADY\_REGISTERED](/docs/c/Foundation/AppMessage/#APP_MSG_CALLBACK_ALREADY_REGISTERED) |
| 

(1024) The callback was already registered.

 |
| c | [APP\_MSG\_CALLBACK\_NOT\_REGISTERED](/docs/c/Foundation/AppMessage/#APP_MSG_CALLBACK_NOT_REGISTERED) |
| 

(2048) The callback could not be deregistered, because it had not been registered before.

 |
| c | [APP\_MSG\_OUT\_OF\_MEMORY](/docs/c/Foundation/AppMessage/#APP_MSG_OUT_OF_MEMORY) |
| 

(4096) The system did not have sufficient application memory to perform the requested operation.

 |
| c | [APP\_MSG\_CLOSED](/docs/c/Foundation/AppMessage/#APP_MSG_CLOSED) |
| 

(8192) App message was closed.

 |
| c | [APP\_MSG\_INTERNAL\_ERROR](/docs/c/Foundation/AppMessage/#APP_MSG_INTERNAL_ERROR) |
| 

(16384) An internal OS error prevented AppMessage from completing an operation.

 |
| c | [APP\_MSG\_INVALID\_STATE](/docs/c/Foundation/AppMessage/#APP_MSG_INVALID_STATE) |
| 

(32768) The function was called while App Message was not in the appropriate state.

 |
| c | [app\_message\_open](/docs/c/Foundation/AppMessage/#app_message_open) |
| 

Open AppMessage to transfers.

 |
| c | [app\_message\_deregister\_callbacks](/docs/c/Foundation/AppMessage/#app_message_deregister_callbacks) |
| 

Deregisters all callbacks and their context.

 |
| c | [AppMessageInboxReceived](/docs/c/Foundation/AppMessage/#AppMessageInboxReceived) |
| 

Called after an incoming message is received.

 |
| c | [AppMessageInboxDropped](/docs/c/Foundation/AppMessage/#AppMessageInboxDropped) |
| 

Called after an incoming message is dropped.

 |
| c | [AppMessageOutboxSent](/docs/c/Foundation/AppMessage/#AppMessageOutboxSent) |
| 

Called after an outbound message has been sent and the reply has been received.

 |
| c | [AppMessageOutboxFailed](/docs/c/Foundation/AppMessage/#AppMessageOutboxFailed) |
| 

Called after an outbound message has not been sent successfully.

 |
| c | [app\_message\_get\_context](/docs/c/Foundation/AppMessage/#app_message_get_context) |
| 

Gets the context that will be passed to all AppMessage callbacks.

 |
| c | [app\_message\_set\_context](/docs/c/Foundation/AppMessage/#app_message_set_context) |
| 

Sets the context that will be passed to all AppMessage callbacks.

 |
| c | [app\_message\_register\_inbox\_received](/docs/c/Foundation/AppMessage/#app_message_register_inbox_received) |
| 

Registers a function that will be called after any Inbox message is received successfully.

 |
| c | [app\_message\_register\_inbox\_dropped](/docs/c/Foundation/AppMessage/#app_message_register_inbox_dropped) |
| 

Registers a function that will be called after any Inbox message is received but dropped by the system.

 |
| c | [app\_message\_register\_outbox\_sent](/docs/c/Foundation/AppMessage/#app_message_register_outbox_sent) |
| 

Registers a function that will be called after any Outbox message is sent and an ACK reply occurs in a timely fashion.

 |
| c | [app\_message\_register\_outbox\_failed](/docs/c/Foundation/AppMessage/#app_message_register_outbox_failed) |
| 

Registers a function that will be called after any Outbox message is not sent with a timely ACK reply. The call to [app\_message\_outbox\_send()](/docs/c/Foundation/AppMessage/#app_message_outbox_send) must have succeeded.

 |
| c | [app\_message\_inbox\_size\_maximum](/docs/c/Foundation/AppMessage/#app_message_inbox_size_maximum) |
| 

Programatically determine the inbox size maximum in the current configuration.

 |
| c | [app\_message\_outbox\_size\_maximum](/docs/c/Foundation/AppMessage/#app_message_outbox_size_maximum) |
| 

Programatically determine the outbox size maximum in the current configuration.

 |
| c | [app\_message\_outbox\_begin](/docs/c/Foundation/AppMessage/#app_message_outbox_begin) |
| 

Begin writing to the Outbox's Dictionary buffer.

 |
| c | [app\_message\_outbox\_send](/docs/c/Foundation/AppMessage/#app_message_outbox_send) |
| 

Sends the outbound dictionary.

 |
| c | [APP\_MESSAGE\_INBOX\_SIZE\_MINIMUM](/docs/c/Foundation/AppMessage/#APP_MESSAGE_INBOX_SIZE_MINIMUM) |
| 

As long as the firmware maintains its current major version, inboxes of this size or smaller will be allowed.

 |
| c | [APP\_MESSAGE\_OUTBOX\_SIZE\_MINIMUM](/docs/c/Foundation/AppMessage/#APP_MESSAGE_OUTBOX_SIZE_MINIMUM) |
| 

As long as the firmware maintains its current major version, outboxes of this size or smaller will be allowed.

 |
| c | [AppSync](/docs/c/Foundation/AppSync/) |
| 

UI synchronization layer for AppMessage

 |
| c | [AppSyncTupleChangedCallback](/docs/c/Foundation/AppSync/#AppSyncTupleChangedCallback) |
| 

Called whenever a [Tuple](/docs/c/Foundation/Dictionary/#Tuple) changes. This does not necessarily mean the value in the [Tuple](/docs/c/Foundation/Dictionary/#Tuple) has changed. When the internal "current" dictionary gets updated, existing Tuples might get shuffled around in the backing buffer, even though the values stay the same. In this callback, the client code gets the chance to remove the old reference and start using the new one. In this callback, your application MUST clean up any references to the `old_tuple` of a PREVIOUS call to this callback (and replace it with the `new_tuple` that is passed in with the current call).

 |
| c | [AppSyncErrorCallback](/docs/c/Foundation/AppSync/#AppSyncErrorCallback) |
| 

Called whenever there was an error.

 |
| c | [app\_sync\_init](/docs/c/Foundation/AppSync/#app_sync_init) |
| 

Initialized an AppSync system with specific buffer size and initial keys and values. The `callback.value_changed` callback will be called **asynchronously** with the initial keys and values, as to avoid duplicating code to update your app's UI.

 |
| c | [app\_sync\_deinit](/docs/c/Foundation/AppSync/#app_sync_deinit) |
| 

Cleans up an AppSync system. It frees the buffer allocated by an [app\_sync\_init()](/docs/c/Foundation/AppSync/#app_sync_init) call and deregisters itself from the [AppMessage](/docs/c/Foundation/AppMessage/) subsystem.

 |
| c | [app\_sync\_set](/docs/c/Foundation/AppSync/#app_sync_set) |
| 

Updates key/value pairs using an array of Tuplets.

 |
| c | [app\_sync\_get](/docs/c/Foundation/AppSync/#app_sync_get) |
| 

Finds and gets a tuple in the "current" dictionary.

 |
| c | [AppSync](/docs/c/Foundation/AppSync/#AppSync) |
| |
| c | [AppWorker](/docs/c/Foundation/AppWorker/) |
| 

Runs in the background, and can communicate with the foreground app.

 |
| c | [AppWorkerResult](/docs/c/Foundation/AppWorker/#AppWorkerResult) |
| 

Possible error codes from app\_worker\_launch, app\_worker\_kill.

 |
| c | [APP\_WORKER\_RESULT\_SUCCESS](/docs/c/Foundation/AppWorker/#APP_WORKER_RESULT_SUCCESS) |
| 

Success.

 |
| c | [APP\_WORKER\_RESULT\_NO\_WORKER](/docs/c/Foundation/AppWorker/#APP_WORKER_RESULT_NO_WORKER) |
| 

No worker found for the current app.

 |
| c | [APP\_WORKER\_RESULT\_DIFFERENT\_APP](/docs/c/Foundation/AppWorker/#APP_WORKER_RESULT_DIFFERENT_APP) |
| 

A worker for a different app is already running.

 |
| c | [APP\_WORKER\_RESULT\_NOT\_RUNNING](/docs/c/Foundation/AppWorker/#APP_WORKER_RESULT_NOT_RUNNING) |
| 

The worker is not running.

 |
| c | [APP\_WORKER\_RESULT\_ALREADY\_RUNNING](/docs/c/Foundation/AppWorker/#APP_WORKER_RESULT_ALREADY_RUNNING) |
| 

The worker is already running.

 |
| c | [APP\_WORKER\_RESULT\_ASKING\_CONFIRMATION](/docs/c/Foundation/AppWorker/#APP_WORKER_RESULT_ASKING_CONFIRMATION) |
| 

The user will be asked for confirmation.

 |
| c | [app\_worker\_is\_running](/docs/c/Foundation/AppWorker/#app_worker_is_running) |
| 

Determine if the worker for the current app is running.

 |
| c | [app\_worker\_launch](/docs/c/Foundation/AppWorker/#app_worker_launch) |
| 

Launch the worker for the current app. Note that this is an asynchronous operation, a result code of APP\_WORKER\_RESULT\_SUCCESS merely means that the request was successfully queued up.

 |
| c | [app\_worker\_kill](/docs/c/Foundation/AppWorker/#app_worker_kill) |
| 

Kill the worker for the current app. Note that this is an asynchronous operation, a result code of APP\_WORKER\_RESULT\_SUCCESS merely means that the request was successfully queued up.

 |
| c | [AppWorkerMessageHandler](/docs/c/Foundation/AppWorker/#AppWorkerMessageHandler) |
| 

Callback type for worker messages. Messages can be sent from worker to app or vice versa.

 |
| c | [app\_worker\_message\_subscribe](/docs/c/Foundation/AppWorker/#app_worker_message_subscribe) |
| 

Subscribe to worker messages. Once subscribed, the handler gets called on every message emitted by the other task (either worker or app).

 |
| c | [app\_worker\_message\_unsubscribe](/docs/c/Foundation/AppWorker/#app_worker_message_unsubscribe) |
| 

Unsubscribe from worker messages. Once unsubscribed, the previously registered handler will no longer be called.

 |
| c | [app\_worker\_send\_message](/docs/c/Foundation/AppWorker/#app_worker_send_message) |
| 

Send a message to the other task (either worker or app).

 |
| c | [AppWorkerMessage](/docs/c/Foundation/AppWorker/#AppWorkerMessage) |
| 

Generic structure of a worker message that can be sent between an app and its worker.

 |
| c | [DataLogging](/docs/c/Foundation/DataLogging/) |
| 

Enables logging data asynchronously to a mobile app

 |
| c | [DataLoggingSessionRef](/docs/c/Foundation/DataLogging/#DataLoggingSessionRef) |
| |
| c | [DataLoggingItemType](/docs/c/Foundation/DataLogging/#DataLoggingItemType) |
| 

The different types of session data that Pebble supports. This type describes the type of a singular item in the data session. Every item in a given session is the same type and size.

 |
| c | [DATA\_LOGGING\_BYTE\_ARRAY](/docs/c/Foundation/DataLogging/#DATA_LOGGING_BYTE_ARRAY) |
| 

Array of bytes. Remember that this is the type of a single item in the logging session, so using this type means you'll be logging multiple byte arrays (each a fixed length described by item\_length) for the duration of the session.

 |
| c | [DATA\_LOGGING\_UINT](/docs/c/Foundation/DataLogging/#DATA_LOGGING_UINT) |
| 

Unsigned integer. This may be a 1, 2, or 4 byte integer depending on the item\_length parameter.

 |
| c | [DATA\_LOGGING\_INT](/docs/c/Foundation/DataLogging/#DATA_LOGGING_INT) |
| 

Signed integer. This may be a 1, 2, or 4 byte integer depending on the item\_length parameter.

 |
| c | [DataLoggingResult](/docs/c/Foundation/DataLogging/#DataLoggingResult) |
| 

Enumerated values describing the possible outcomes of data logging operations.

 |
| c | [DATA\_LOGGING\_SUCCESS](/docs/c/Foundation/DataLogging/#DATA_LOGGING_SUCCESS) |
| 

Successful operation.

 |
| c | [DATA\_LOGGING\_BUSY](/docs/c/Foundation/DataLogging/#DATA_LOGGING_BUSY) |
| 

Someone else is writing to this logging session.

 |
| c | [DATA\_LOGGING\_FULL](/docs/c/Foundation/DataLogging/#DATA_LOGGING_FULL) |
| 

No more space to save data.

 |
| c | [DATA\_LOGGING\_NOT\_FOUND](/docs/c/Foundation/DataLogging/#DATA_LOGGING_NOT_FOUND) |
| 

The logging session does not exist.

 |
| c | [DATA\_LOGGING\_CLOSED](/docs/c/Foundation/DataLogging/#DATA_LOGGING_CLOSED) |
| 

The logging session was made inactive.

 |
| c | [DATA\_LOGGING\_INVALID\_PARAMS](/docs/c/Foundation/DataLogging/#DATA_LOGGING_INVALID_PARAMS) |
| 

An invalid parameter was passed to one of the functions.

 |
| c | [DATA\_LOGGING\_INTERNAL\_ERR](/docs/c/Foundation/DataLogging/#DATA_LOGGING_INTERNAL_ERR) |
| 

An internal error occurred.

 |
| c | [data\_logging\_create](/docs/c/Foundation/DataLogging/#data_logging_create) |
| 

Create a new data logging session.

 |
| c | [data\_logging\_finish](/docs/c/Foundation/DataLogging/#data_logging_finish) |
| 

Finish up a data logging\_session. Logging data is kept until it has successfully been transferred over to the phone, but no data may be added to the session after this function is called.

 |
| c | [data\_logging\_log](/docs/c/Foundation/DataLogging/#data_logging_log) |
| 

Add data to the data logging session. If a phone is available, the data is sent directly to the phone. Otherwise, it is saved to the watch storage until the watch is connected to a phone.

 |
| c | [DataStructures](/docs/c/Foundation/DataStructures/) |
| |
| c | [UUID](/docs/c/Foundation/DataStructures/UUID/) |
| |
| c | [UUID\_SIZE](/docs/c/Foundation/DataStructures/UUID/#UUID_SIZE) |
| |
| c | [UuidMake](/docs/c/Foundation/DataStructures/UUID/#UuidMake) |
| 

Make a Uuid object from sixteen bytes.

 |
| c | [UuidMakeFromBEBytes](/docs/c/Foundation/DataStructures/UUID/#UuidMakeFromBEBytes) |
| 

Creates a Uuid from an array of bytes with 16 bytes in Big Endian order.

 |
| c | [UuidMakeFromLEBytes](/docs/c/Foundation/DataStructures/UUID/#UuidMakeFromLEBytes) |
| 

Creates a Uuid from an array of bytes with 16 bytes in Little Endian order.

 |
| c | [uuid\_equal](/docs/c/Foundation/DataStructures/UUID/#uuid_equal) |
| 

Compares two UUIDs.

 |
| c | [uuid\_to\_string](/docs/c/Foundation/DataStructures/UUID/#uuid_to_string) |
| 

Writes UUID in a string form into buffer that looks like the following... {12345678-1234-5678-1234-567812345678} or {NULL UUID} if NULL was passed.

 |
| c | [UUID\_STRING\_BUFFER\_LENGTH](/docs/c/Foundation/DataStructures/UUID/#UUID_STRING_BUFFER_LENGTH) |
| 

The minimum required length of a string used to hold a uuid (including null).

 |
| c | [Uuid](/docs/c/Foundation/DataStructures/UUID/#Uuid) |
| |
| c | [Dictation](/docs/c/Foundation/Dictation/) |
| |
| c | [DictationSession](/docs/c/Foundation/Dictation/#DictationSession) |
| |
| c | [DictationSessionStatus](/docs/c/Foundation/Dictation/#DictationSessionStatus) |
| |
| c | [DictationSessionStatusSuccess](/docs/c/Foundation/Dictation/#DictationSessionStatusSuccess) |
| 

Transcription successful, with a valid result.

 |
| c | [DictationSessionStatusFailureTranscriptionRejected](/docs/c/Foundation/Dictation/#DictationSessionStatusFailureTranscriptionRejected) |
| 

User rejected transcription and exited UI.

 |
| c | [DictationSessionStatusFailureTranscriptionRejectedWithError](/docs/c/Foundation/Dictation/#DictationSessionStatusFailureTranscriptionRejectedWithError) |
| 

User exited UI after transcription error.

 |
| c | [DictationSessionStatusFailureSystemAborted](/docs/c/Foundation/Dictation/#DictationSessionStatusFailureSystemAborted) |
| 

Too many errors occurred during transcription and the UI exited.

 |
| c | [DictationSessionStatusFailureNoSpeechDetected](/docs/c/Foundation/Dictation/#DictationSessionStatusFailureNoSpeechDetected) |
| 

No speech was detected and UI exited.

 |
| c | [DictationSessionStatusFailureConnectivityError](/docs/c/Foundation/Dictation/#DictationSessionStatusFailureConnectivityError) |
| 

No BT or internet connection.

 |
| c | [DictationSessionStatusFailureDisabled](/docs/c/Foundation/Dictation/#DictationSessionStatusFailureDisabled) |
| 

Voice transcription disabled for this user.

 |
| c | [DictationSessionStatusFailureInternalError](/docs/c/Foundation/Dictation/#DictationSessionStatusFailureInternalError) |
| 

Voice transcription failed due to internal error.

 |
| c | [DictationSessionStatusFailureRecognizerError](/docs/c/Foundation/Dictation/#DictationSessionStatusFailureRecognizerError) |
| 

Cloud recognizer failed to transcribe speech (only possible if error dialogs disabled)

 |
| c | [DictationSessionStatusCallback](/docs/c/Foundation/Dictation/#DictationSessionStatusCallback) |
| 

Dictation status callback. Indicates success or failure of the dictation session and, if successful, passes the transcribed string to the user of the dictation session. The transcribed string will be freed after this call returns, so the string should be copied if it needs to be retained afterwards.

 |
| c | [dictation\_session\_create](/docs/c/Foundation/Dictation/#dictation_session_create) |
| 

Create a dictation session. The session object can be used more than once to get a transcription. When a transcription is received a buffer will be allocated to store the text in with a maximum size specified by buffer\_size. When a transcription is accepted by the user or a failure of some sort occurs, the callback specified will be called with the status and the transcription if one was accepted.

 |
| c | [dictation\_session\_destroy](/docs/c/Foundation/Dictation/#dictation_session_destroy) |
| 

Destroy the dictation session and free its memory. Will terminate a session in progress.

 |
| c | [dictation\_session\_start](/docs/c/Foundation/Dictation/#dictation_session_start) |
| 

Start the dictation session. The dictation UI will be shown. When the user accepts a transcription or exits the UI, or, when the confirmation dialog is disabled and a status is received, the status callback will be called. Can only be called when no session is in progress. The session can be restarted multiple times after the UI is exited or the session is stopped.

 |
| c | [dictation\_session\_stop](/docs/c/Foundation/Dictation/#dictation_session_stop) |
| 

Stop the current dictation session. The UI will be hidden and no status callbacks will be received after the session is stopped.

 |
| c | [dictation\_session\_enable\_confirmation](/docs/c/Foundation/Dictation/#dictation_session_enable_confirmation) |
| 

Enable or disable user confirmation of transcribed text, which allows the user to accept or reject (and restart) the transcription. Must be called before the session is started.

 |
| c | [dictation\_session\_enable\_error\_dialogs](/docs/c/Foundation/Dictation/#dictation_session_enable_error_dialogs) |
| 

Enable or disable error dialogs when transcription fails. Must be called before the session is started. Disabling error dialogs will also disable automatic retries if transcription fails.

 |
| c | [PBL\_IF\_MICROPHONE\_ELSE](/docs/c/Foundation/Dictation/#PBL_IF_MICROPHONE_ELSE) |
| 

Convenience macro to switch between two expressions depending on mic support. On platforms with a mic the first expression will be chosen, the second otherwise.

 |
| c | [Dictionary](/docs/c/Foundation/Dictionary/) |
| 

Data serialization utilities

 |
| c | [DictionaryResult](/docs/c/Foundation/Dictionary/#DictionaryResult) |
| 

Return values for dictionary write/conversion functions.

 |
| c | [DICT\_OK](/docs/c/Foundation/Dictionary/#DICT_OK) |
| 

The operation returned successfully.

 |
| c | [DICT\_NOT\_ENOUGH\_STORAGE](/docs/c/Foundation/Dictionary/#DICT_NOT_ENOUGH_STORAGE) |
| 

There was not enough backing storage to complete the operation.

 |
| c | [DICT\_INVALID\_ARGS](/docs/c/Foundation/Dictionary/#DICT_INVALID_ARGS) |
| 

One or more arguments were invalid or uninitialized.

 |
| c | [DICT\_INTERNAL\_INCONSISTENCY](/docs/c/Foundation/Dictionary/#DICT_INTERNAL_INCONSISTENCY) |
| 

The lengths and/or count of the dictionary its tuples are inconsistent.

 |
| c | [DICT\_MALLOC\_FAILED](/docs/c/Foundation/Dictionary/#DICT_MALLOC_FAILED) |
| 

A requested operation required additional memory to be allocated, but the allocation failed, likely due to insufficient remaining heap memory.

 |
| c | [TupleType](/docs/c/Foundation/Dictionary/#TupleType) |
| 

Values representing the type of data that the `value` field of a [Tuple](/docs/c/Foundation/Dictionary/#Tuple) contains.

 |
| c | [TUPLE\_BYTE\_ARRAY](/docs/c/Foundation/Dictionary/#TUPLE_BYTE_ARRAY) |
| 

The value is an array of bytes.

 |
| c | [TUPLE\_CSTRING](/docs/c/Foundation/Dictionary/#TUPLE_CSTRING) |
| 

The value is a zero-terminated, UTF-8 C-string.

 |
| c | [TUPLE\_UINT](/docs/c/Foundation/Dictionary/#TUPLE_UINT) |
| 

The value is an unsigned integer. The tuple's `.length` field is used to determine the size of the integer (1, 2, or 4 bytes).

 |
| c | [TUPLE\_INT](/docs/c/Foundation/Dictionary/#TUPLE_INT) |
| 

The value is a signed integer. The tuple's `.length` field is used to determine the size of the integer (1, 2, or 4 bytes).

 |
| c | [Dictionary](/docs/c/Foundation/Dictionary/#Dictionary) |
| |
| c | [dict\_calc\_buffer\_size](/docs/c/Foundation/Dictionary/#dict_calc_buffer_size) |
| 

Calculates the number of bytes that a dictionary will occupy, given one or more value lengths that need to be stored in the dictionary.

 |
| c | [dict\_size](/docs/c/Foundation/Dictionary/#dict_size) |
| 

Calculates the size of data that has been written to the dictionary. AKA, the "dictionary size". Note that this is most likely different than the size of the backing storage/backing buffer.

 |
| c | [dict\_write\_begin](/docs/c/Foundation/Dictionary/#dict_write_begin) |
| 

Initializes the dictionary iterator with a given buffer and size, resets and empties it, in preparation of writing key/value tuples.

 |
| c | [dict\_write\_data](/docs/c/Foundation/Dictionary/#dict_write_data) |
| 

Adds a key with a byte array value pair to the dictionary.

 |
| c | [dict\_write\_cstring](/docs/c/Foundation/Dictionary/#dict_write_cstring) |
| 

Adds a key with a C string value pair to the dictionary.

 |
| c | [dict\_write\_int](/docs/c/Foundation/Dictionary/#dict_write_int) |
| 

Adds a key with an integer value pair to the dictionary.

 |
| c | [dict\_write\_uint8](/docs/c/Foundation/Dictionary/#dict_write_uint8) |
| 

Adds a key with an unsigned, 8-bit integer value pair to the dictionary.

 |
| c | [dict\_write\_uint16](/docs/c/Foundation/Dictionary/#dict_write_uint16) |
| |
| c | [dict\_write\_uint32](/docs/c/Foundation/Dictionary/#dict_write_uint32) |
| |
| c | [dict\_write\_int8](/docs/c/Foundation/Dictionary/#dict_write_int8) |
| |
| c | [dict\_write\_int16](/docs/c/Foundation/Dictionary/#dict_write_int16) |
| |
| c | [dict\_write\_int32](/docs/c/Foundation/Dictionary/#dict_write_int32) |
| |
| c | [dict\_write\_end](/docs/c/Foundation/Dictionary/#dict_write_end) |
| 

End a series of writing operations to a dictionary. This must be called before reading back from the dictionary.

 |
| c | [dict\_read\_begin\_from\_buffer](/docs/c/Foundation/Dictionary/#dict_read_begin_from_buffer) |
| 

Initializes the dictionary iterator with a given buffer and size, in preparation of reading key/value tuples.

 |
| c | [dict\_read\_next](/docs/c/Foundation/Dictionary/#dict_read_next) |
| 

Progresses the iterator to the next key/value pair.

 |
| c | [dict\_read\_first](/docs/c/Foundation/Dictionary/#dict_read_first) |
| 

Resets the iterator back to the same state as a call to [dict\_read\_begin\_from\_buffer()](/docs/c/Foundation/Dictionary/#dict_read_begin_from_buffer) would do.

 |
| c | [TupletBytes](/docs/c/Foundation/Dictionary/#TupletBytes) |
| 

Macro to create a [Tuplet](/docs/c/Foundation/Dictionary/#Tuplet) with a byte array value.

 |
| c | [TupletCString](/docs/c/Foundation/Dictionary/#TupletCString) |
| 

Macro to create a [Tuplet](/docs/c/Foundation/Dictionary/#Tuplet) with a c-string value.

 |
| c | [TupletInteger](/docs/c/Foundation/Dictionary/#TupletInteger) |
| 

Macro to create a [Tuplet](/docs/c/Foundation/Dictionary/#Tuplet) with an integer value.

 |
| c | [DictionarySerializeCallback](/docs/c/Foundation/Dictionary/#DictionarySerializeCallback) |
| 

Callback for [dict\_serialize\_tuplets()](/docs/c/Foundation/Dictionary/#dict_serialize_tuplets) utility.

 |
| c | [dict\_serialize\_tuplets](/docs/c/Foundation/Dictionary/#dict_serialize_tuplets) |
| 

Utility function that takes a list of Tuplets from which a dictionary will be serialized, ready to transmit or store.

 |
| c | [dict\_serialize\_tuplets\_to\_buffer](/docs/c/Foundation/Dictionary/#dict_serialize_tuplets_to_buffer) |
| 

Utility function that takes an array of Tuplets and serializes them into a dictionary with a given buffer and size.

 |
| c | [dict\_serialize\_tuplets\_to\_buffer\_with\_iter](/docs/c/Foundation/Dictionary/#dict_serialize_tuplets_to_buffer_with_iter) |
| 

Serializes an array of Tuplets into a dictionary with a given buffer and size.

 |
| c | [dict\_write\_tuplet](/docs/c/Foundation/Dictionary/#dict_write_tuplet) |
| 

Serializes a [Tuplet](/docs/c/Foundation/Dictionary/#Tuplet) and writes the resulting [Tuple](/docs/c/Foundation/Dictionary/#Tuple) into a dictionary.

 |
| c | [dict\_calc\_buffer\_size\_from\_tuplets](/docs/c/Foundation/Dictionary/#dict_calc_buffer_size_from_tuplets) |
| 

Calculates the number of bytes that a dictionary will occupy, given one or more Tuplets that need to be stored in the dictionary.

 |
| c | [DictionaryKeyUpdatedCallback](/docs/c/Foundation/Dictionary/#DictionaryKeyUpdatedCallback) |
| 

Type of the callback used in [dict\_merge()](/docs/c/Foundation/Dictionary/#dict_merge)

 |
| c | [dict\_merge](/docs/c/Foundation/Dictionary/#dict_merge) |
| 

Merges entries from another "source" dictionary into a "destination" dictionary. All Tuples from the source are written into the destination dictionary, while updating the exsting Tuples with matching keys.

 |
| c | [dict\_find](/docs/c/Foundation/Dictionary/#dict_find) |
| 

Tries to find a [Tuple](/docs/c/Foundation/Dictionary/#Tuple) with specified key in a dictionary.

 |
| c | [DictionaryIterator](/docs/c/Foundation/Dictionary/#DictionaryIterator) |
| 

An iterator can be used to iterate over the key/value tuples in an existing dictionary, using [dict\_read\_begin\_from\_buffer()](/docs/c/Foundation/Dictionary/#dict_read_begin_from_buffer), [dict\_read\_first()](/docs/c/Foundation/Dictionary/#dict_read_first) and [dict\_read\_next()](/docs/c/Foundation/Dictionary/#dict_read_next). An iterator can also be used to append key/value tuples to a dictionary, for example using [dict\_write\_data()](/docs/c/Foundation/Dictionary/#dict_write_data) or [dict\_write\_cstring()](/docs/c/Foundation/Dictionary/#dict_write_cstring).

 |
| c | [Tuple](/docs/c/Foundation/Dictionary/#Tuple) |
| 

Data structure for one serialized key/value tuple.

 |
| c | [Tuplet](/docs/c/Foundation/Dictionary/#Tuplet) |
| 

Non-serialized, template data structure for a key/value pair. For strings and byte arrays, it only has a pointer to the actual data. For integers, it provides storage for integers up to 32-bits wide. The [Tuplet](/docs/c/Foundation/Dictionary/#Tuplet) data structure is useful when creating dictionaries from values that are already stored in arbitrary buffers. See also [Tuple](/docs/c/Foundation/Dictionary/#Tuple), with is the header of a serialized key/value pair.

 |
| c | [Event Service](/docs/c/Foundation/Event_Service/) |
| 

APIs to handle event services.

 |
| c | [AccelerometerService](/docs/c/Foundation/Event_Service/AccelerometerService/) |
| |
| c | [AccelAxisType](/docs/c/Foundation/Event_Service/AccelerometerService/#AccelAxisType) |
| 

Enumerated values defining the three accelerometer axes.

 |
| c | [ACCEL\_AXIS\_X](/docs/c/Foundation/Event_Service/AccelerometerService/#ACCEL_AXIS_X) |
| 

Accelerometer's X axis. The positive direction along the X axis goes toward the right of the watch.

 |
| c | [ACCEL\_AXIS\_Y](/docs/c/Foundation/Event_Service/AccelerometerService/#ACCEL_AXIS_Y) |
| 

Accelerometer's Y axis. The positive direction along the Y axis goes toward the top of the watch.

 |
| c | [ACCEL\_AXIS\_Z](/docs/c/Foundation/Event_Service/AccelerometerService/#ACCEL_AXIS_Z) |
| 

Accelerometer's Z axis. The positive direction along the Z axis goes vertically out of the watchface.

 |
| c | [AccelDataHandler](/docs/c/Foundation/Event_Service/AccelerometerService/#AccelDataHandler) |
| 

Callback type for accelerometer data events.

 |
| c | [AccelRawDataHandler](/docs/c/Foundation/Event_Service/AccelerometerService/#AccelRawDataHandler) |
| 

Callback type for accelerometer raw data events.

 |
| c | [AccelTapHandler](/docs/c/Foundation/Event_Service/AccelerometerService/#AccelTapHandler) |
| 

Callback type for accelerometer tap events.

 |
| c | [AccelSamplingRate](/docs/c/Foundation/Event_Service/AccelerometerService/#AccelSamplingRate) |
| 

Valid accelerometer sampling rates, in Hz.

 |
| c | [ACCEL\_SAMPLING\_10HZ](/docs/c/Foundation/Event_Service/AccelerometerService/#ACCEL_SAMPLING_10HZ) |
| 

10 HZ sampling rate

 |
| c | [ACCEL\_SAMPLING\_25HZ](/docs/c/Foundation/Event_Service/AccelerometerService/#ACCEL_SAMPLING_25HZ) |
| 

25 HZ sampling rate [Default]

 |
| c | [ACCEL\_SAMPLING\_50HZ](/docs/c/Foundation/Event_Service/AccelerometerService/#ACCEL_SAMPLING_50HZ) |
| 

50 HZ sampling rate

 |
| c | [ACCEL\_SAMPLING\_100HZ](/docs/c/Foundation/Event_Service/AccelerometerService/#ACCEL_SAMPLING_100HZ) |
| 

100 HZ sampling rate

 |
| c | [accel\_service\_peek](/docs/c/Foundation/Event_Service/AccelerometerService/#accel_service_peek) |
| 

Peek at the last recorded reading.

 |
| c | [accel\_service\_set\_sampling\_rate](/docs/c/Foundation/Event_Service/AccelerometerService/#accel_service_set_sampling_rate) |
| 

Change the accelerometer sampling rate.

 |
| c | [accel\_service\_set\_samples\_per\_update](/docs/c/Foundation/Event_Service/AccelerometerService/#accel_service_set_samples_per_update) |
| 

Change the number of samples buffered between each accelerometer data event.

 |
| c | [accel\_data\_service\_subscribe](/docs/c/Foundation/Event_Service/AccelerometerService/#accel_data_service_subscribe) |
| 

Subscribe to the accelerometer data event service. Once subscribed, the handler gets called every time there are new accelerometer samples available.

 |
| c | [accel\_data\_service\_unsubscribe](/docs/c/Foundation/Event_Service/AccelerometerService/#accel_data_service_unsubscribe) |
| 

Unsubscribe from the accelerometer data event service. Once unsubscribed, the previously registered handler will no longer be called.

 |
| c | [accel\_tap\_service\_subscribe](/docs/c/Foundation/Event_Service/AccelerometerService/#accel_tap_service_subscribe) |
| 

Subscribe to the accelerometer tap event service. Once subscribed, the handler gets called on every tap event emitted by the accelerometer.

 |
| c | [accel\_tap\_service\_unsubscribe](/docs/c/Foundation/Event_Service/AccelerometerService/#accel_tap_service_unsubscribe) |
| 

Unsubscribe from the accelerometer tap event service. Once unsubscribed, the previously registered handler will no longer be called.

 |
| c | [accel\_raw\_data\_service\_subscribe](/docs/c/Foundation/Event_Service/AccelerometerService/#accel_raw_data_service_subscribe) |
| 

Subscribe to the accelerometer raw data event service. Once subscribed, the handler gets called every time there are new accelerometer samples available.

 |
| c | [AccelData](/docs/c/Foundation/Event_Service/AccelerometerService/#AccelData) |
| 

A single accelerometer sample for all three axes including timestamp and vibration rumble status.

 |
| c | [AccelRawData](/docs/c/Foundation/Event_Service/AccelerometerService/#AccelRawData) |
| 

A single accelerometer sample for all three axes.

 |
| c | [AppFocusService](/docs/c/Foundation/Event_Service/AppFocusService/) |
| |
| c | [AppFocusHandler](/docs/c/Foundation/Event_Service/AppFocusService/#AppFocusHandler) |
| 

Callback type for focus events.

 |
| c | [app\_focus\_service\_subscribe\_handlers](/docs/c/Foundation/Event_Service/AppFocusService/#app_focus_service_subscribe_handlers) |
| 

Subscribe to the focus event service. Once subscribed, the handlers get called every time the app gains or loses focus.

 |
| c | [app\_focus\_service\_subscribe](/docs/c/Foundation/Event_Service/AppFocusService/#app_focus_service_subscribe) |
| 

Subscribe to the focus event service. Once subscribed, the handler gets called every time the app focus changes.

 |
| c | [app\_focus\_service\_unsubscribe](/docs/c/Foundation/Event_Service/AppFocusService/#app_focus_service_unsubscribe) |
| 

Unsubscribe from the focus event service. Once unsubscribed, the previously registered handlers will no longer be called.

 |
| c | [AppFocusHandlers](/docs/c/Foundation/Event_Service/AppFocusService/#AppFocusHandlers) |
| 

There are two different focus events which take place when transitioning to and from an app being in focus. Below is an example of when these events will occur: 1) The app is launched. Once the system animation to the app has completed and the app is completely in focus, the did\_focus handler is called with in\_focus set to true. 2) A notification comes in and the animation to show the notification starts. The will\_focus handler is called with in\_focus set to false. 3) The animation completes and the notification is in focus, with the app being completely covered. The did\_focus hander is called with in\_focus set to false. 4) The notification is dismissed and the animation to return to the app starts. The will\_focus handler is called with in\_focus set to true. 5) The animation completes and the app is in focus. The did\_focus handler is called with in\_focus set to true.

 |
| c | [BatteryStateService](/docs/c/Foundation/Event_Service/BatteryStateService/) |
| |
| c | [BatteryStateHandler](/docs/c/Foundation/Event_Service/BatteryStateService/#BatteryStateHandler) |
| 

Callback type for battery state change events.

 |
| c | [battery\_state\_service\_subscribe](/docs/c/Foundation/Event_Service/BatteryStateService/#battery_state_service_subscribe) |
| 

Subscribe to the battery state event service. Once subscribed, the handler gets called on every battery state change.

 |
| c | [battery\_state\_service\_unsubscribe](/docs/c/Foundation/Event_Service/BatteryStateService/#battery_state_service_unsubscribe) |
| 

Unsubscribe from the battery state event service. Once unsubscribed, the previously registered handler will no longer be called.

 |
| c | [battery\_state\_service\_peek](/docs/c/Foundation/Event_Service/BatteryStateService/#battery_state_service_peek) |
| 

Peek at the last known battery state.

 |
| c | [BatteryChargeState](/docs/c/Foundation/Event_Service/BatteryStateService/#BatteryChargeState) |
| 

Structure for retrieval of the battery charge state.

 |
| c | [CompassService](/docs/c/Foundation/Event_Service/CompassService/) |
| |
| c | [CompassStatus](/docs/c/Foundation/Event_Service/CompassService/#CompassStatus) |
| 

Enum describing the current state of the Compass Service.

 |
| c | [CompassStatusUnavailable](/docs/c/Foundation/Event_Service/CompassService/#CompassStatusUnavailable) |
| 

The Compass Service is unavailable.

 |
| c | [CompassStatusDataInvalid](/docs/c/Foundation/Event_Service/CompassService/#CompassStatusDataInvalid) |
| 

Compass is calibrating: data is invalid and should not be used Data will become valid once calibration is complete.

 |
| c | [CompassStatusCalibrating](/docs/c/Foundation/Event_Service/CompassService/#CompassStatusCalibrating) |
| 

Compass is calibrating: the data is valid but the calibration is still being refined.

 |
| c | [CompassStatusCalibrated](/docs/c/Foundation/Event_Service/CompassService/#CompassStatusCalibrated) |
| 

Compass data is valid and the calibration has completed.

 |
| c | [CompassHeading](/docs/c/Foundation/Event_Service/CompassService/#CompassHeading) |
| 

Represents an angle relative to get to a reference direction, e.g. (magnetic) north. The angle value is scaled linearly, such that a value of TRIG\_MAX\_ANGLE corresponds to 360 degrees or 2 PI radians. Thus, if heading towards north, north is 0, west is TRIG\_MAX\_ANGLE/4, south is TRIG\_MAX\_ANGLE/2, and so on.

 |
| c | [CompassHeadingHandler](/docs/c/Foundation/Event_Service/CompassService/#CompassHeadingHandler) |
| 

Callback type for compass heading events.

 |
| c | [compass\_service\_set\_heading\_filter](/docs/c/Foundation/Event_Service/CompassService/#compass_service_set_heading_filter) |
| 

Set the minimum angular change required to generate new compass heading events. The angular distance is measured relative to the last delivered heading event. Use 0 to be notified of all movements. Negative values and values \> TRIG\_MAX\_ANGLE / 2 are not valid. The default value of this property is TRIG\_MAX\_ANGLE / 360.

 |
| c | [compass\_service\_subscribe](/docs/c/Foundation/Event_Service/CompassService/#compass_service_subscribe) |
| 

Subscribe to the compass heading event service. Once subscribed, the handler gets called every time the angular distance relative to the previous value exceeds the configured filter.

 |
| c | [compass\_service\_unsubscribe](/docs/c/Foundation/Event_Service/CompassService/#compass_service_unsubscribe) |
| 

Unsubscribe from the compass heading event service. Once unsubscribed, the previously registered handler will no longer be called.

 |
| c | [compass\_service\_peek](/docs/c/Foundation/Event_Service/CompassService/#compass_service_peek) |
| 

Peek at the last recorded reading.

 |
| c | [CompassHeadingData](/docs/c/Foundation/Event_Service/CompassService/#CompassHeadingData) |
| 

Structure containing a single heading towards magnetic and true north.

 |
| c | [ConnectionService](/docs/c/Foundation/Event_Service/ConnectionService/) |
| 

Determine what the Pebble watch is connected to

 |
| c | [ConnectionHandler](/docs/c/Foundation/Event_Service/ConnectionService/#ConnectionHandler) |
| |
| c | [connection\_service\_peek\_pebble\_app\_connection](/docs/c/Foundation/Event_Service/ConnectionService/#connection_service_peek_pebble_app_connection) |
| 

Query the bluetooth connection service for the current Pebble app connection status.

 |
| c | [connection\_service\_peek\_pebblekit\_connection](/docs/c/Foundation/Event_Service/ConnectionService/#connection_service_peek_pebblekit_connection) |
| 

Query the bluetooth connection service for the current PebbleKit connection status.

 |
| c | [connection\_service\_subscribe](/docs/c/Foundation/Event_Service/ConnectionService/#connection_service_subscribe) |
| 

Subscribe to the connection event service. Once subscribed, the appropriate handler gets called based on the type of connection event and user provided handlers.

 |
| c | [connection\_service\_unsubscribe](/docs/c/Foundation/Event_Service/ConnectionService/#connection_service_unsubscribe) |
| 

Unsubscribe from the bluetooth event service. Once unsubscribed, the previously registered handler will no longer be called.

 |
| c | [BluetoothConnectionHandler](/docs/c/Foundation/Event_Service/ConnectionService/#BluetoothConnectionHandler) |
| |
| c | [bluetooth\_connection\_service\_peek](/docs/c/Foundation/Event_Service/ConnectionService/#bluetooth_connection_service_peek) |
| |
| c | [bluetooth\_connection\_service\_subscribe](/docs/c/Foundation/Event_Service/ConnectionService/#bluetooth_connection_service_subscribe) |
| |
| c | [bluetooth\_connection\_service\_unsubscribe](/docs/c/Foundation/Event_Service/ConnectionService/#bluetooth_connection_service_unsubscribe) |
| |
| c | [ConnectionHandlers](/docs/c/Foundation/Event_Service/ConnectionService/#ConnectionHandlers) |
| |
| c | [HealthService](/docs/c/Foundation/Event_Service/HealthService/) |
| |
| c | [HealthMetric](/docs/c/Foundation/Event_Service/HealthService/#HealthMetric) |
| 

Health metric values used to retrieve health data. For example, using [health\_service\_sum()](/docs/c/Foundation/Event_Service/HealthService/#health_service_sum).

 |
| c | [HealthMetricStepCount](/docs/c/Foundation/Event_Service/HealthService/#HealthMetricStepCount) |
| 

The number of steps counted.

 |
| c | [HealthMetricActiveSeconds](/docs/c/Foundation/Event_Service/HealthService/#HealthMetricActiveSeconds) |
| 

The number of seconds spent active (i.e. not resting).

 |
| c | [HealthMetricWalkedDistanceMeters](/docs/c/Foundation/Event_Service/HealthService/#HealthMetricWalkedDistanceMeters) |
| 

The distance walked, in meters.

 |
| c | [HealthMetricSleepSeconds](/docs/c/Foundation/Event_Service/HealthService/#HealthMetricSleepSeconds) |
| 

The number of seconds spent sleeping.

 |
| c | [HealthMetricSleepRestfulSeconds](/docs/c/Foundation/Event_Service/HealthService/#HealthMetricSleepRestfulSeconds) |
| 

The number of sleep seconds in the 'restful' or deep sleep state.

 |
| c | [HealthMetricRestingKCalories](/docs/c/Foundation/Event_Service/HealthService/#HealthMetricRestingKCalories) |
| 

The number of kcal (Calories) burned while resting due to resting metabolism.

 |
| c | [HealthMetricActiveKCalories](/docs/c/Foundation/Event_Service/HealthService/#HealthMetricActiveKCalories) |
| 

The number of kcal (Calories) burned while active.

 |
| c | [HealthMetricHeartRateBPM](/docs/c/Foundation/Event_Service/HealthService/#HealthMetricHeartRateBPM) |
| 

The heart rate, in beats per minute. This is a filtered value that is at most 15 minutes old.

 |
| c | [HealthMetricHeartRateRawBPM](/docs/c/Foundation/Event_Service/HealthService/#HealthMetricHeartRateRawBPM) |
| 

The raw heart rate value of the most recent sample, in beats per minute.

 |
| c | [HealthValue](/docs/c/Foundation/Event_Service/HealthService/#HealthValue) |
| 

Type used to represent [HealthMetric](/docs/c/Foundation/Event_Service/HealthService/#HealthMetric) values.

 |
| c | [HealthMetricAlert](/docs/c/Foundation/Event_Service/HealthService/#HealthMetricAlert) |
| 

Type used as a handle to a registered metric alert (returned by [health\_service\_register\_metric\_alert](/docs/c/Foundation/Event_Service/HealthService/#health_service_register_metric_alert))

 |
| c | [health\_service\_sum](/docs/c/Foundation/Event_Service/HealthService/#health_service_sum) |
| 

Return the sum of a [HealthMetric](/docs/c/Foundation/Event_Service/HealthService/#HealthMetric)'s values over a time range. The `time_start` and `time_end` parameters define the range of time you want the sum for.

 |
| c | [health\_service\_sum\_today](/docs/c/Foundation/Event_Service/HealthService/#health_service_sum_today) |
| 

Convenience wrapper for [health\_service\_sum()](/docs/c/Foundation/Event_Service/HealthService/#health_service_sum) that returns the sum for today.

 |
| c | [health\_service\_peek\_current\_value](/docs/c/Foundation/Event_Service/HealthService/#health_service_peek_current_value) |
| 

Convenience function for peeking at the current value of a metric. This is useful for metrics like HealthMetricHeartRateBPM that represent instantaneous values. It is NOT applicable for metrics like HealthMetricStepCount that must be accumulated over time (it will return 0 if passed that type of metric). This call is equivalent to calling `health_service_aggregate_averaged(metric, time(NULL), time(NULL), HealthAggregationAvg, HealthServiceTimeScopeOnce)`

 |
| c | [HealthServiceTimeScope](/docs/c/Foundation/Event_Service/HealthService/#HealthServiceTimeScope) |
| 

Used by [health\_service\_sum\_averaged()](/docs/c/Foundation/Event_Service/HealthService/#health_service_sum_averaged) to specify how the average is computed.

 |
| c | [HealthServiceTimeScopeOnce](/docs/c/Foundation/Event_Service/HealthService/#HealthServiceTimeScopeOnce) |
| 

No average computed. The result is the same as calling [health\_service\_sum()](/docs/c/Foundation/Event_Service/HealthService/#health_service_sum).

 |
| c | [HealthServiceTimeScopeWeekly](/docs/c/Foundation/Event_Service/HealthService/#HealthServiceTimeScopeWeekly) |
| 

Compute average using the same day from each week. For example, every Monday if the passed in time range falls on a Monday.

 |
| c | [HealthServiceTimeScopeDailyWeekdayOrWeekend](/docs/c/Foundation/Event_Service/HealthService/#HealthServiceTimeScopeDailyWeekdayOrWeekend) |
| 

Compute average using either weekdays (Monday to Friday) or weekends (Saturday and Sunday), depending on which day the passed in time range falls.

 |
| c | [HealthServiceTimeScopeDaily](/docs/c/Foundation/Event_Service/HealthService/#HealthServiceTimeScopeDaily) |
| 

Compute average across all days of the week.

 |
| c | [health\_service\_sum\_averaged](/docs/c/Foundation/Event_Service/HealthService/#health_service_sum_averaged) |
| 

Return the value of a metric's sum over a given time range between `time_start` and `time_end`. Using this call you can specify the time range that you are interested in getting the average for, as well as a `scope` specifier on how to compute an average of the sum. For example, if you want to get the average number of steps taken from 12 AM (midnight) to 9 AM across all days you would specify:

 |
| c | [HealthAggregation](/docs/c/Foundation/Event_Service/HealthService/#HealthAggregation) |
| 

Used by [health\_service\_aggregate\_averaged()](/docs/c/Foundation/Event_Service/HealthService/#health_service_aggregate_averaged) to specify what type of aggregation to perform. This aggregation is applied to the metric before the average is computed.

 |
| c | [HealthAggregationSum](/docs/c/Foundation/Event_Service/HealthService/#HealthAggregationSum) |
| 

Sum the metric. The result is the same as calling [health\_service\_sum\_averaged()](/docs/c/Foundation/Event_Service/HealthService/#health_service_sum_averaged). This operation is only applicable for metrics that accumulate, like HealthMetricStepCount, HealthMetricActiveSeconds, etc.

 |
| c | [HealthAggregationAvg](/docs/c/Foundation/Event_Service/HealthService/#HealthAggregationAvg) |
| 

Use the average of the metric. This is only applicable for metrics that measure instantaneous values, like HealthMetricHeartRateBPM.

 |
| c | [HealthAggregationMin](/docs/c/Foundation/Event_Service/HealthService/#HealthAggregationMin) |
| 

Use the minimum value of the metric. This is only applicable for metrics that measure instantaneous values, like HealthMetricHeartRateBPM.

 |
| c | [HealthAggregationMax](/docs/c/Foundation/Event_Service/HealthService/#HealthAggregationMax) |
| 

Use the maximum value of the metric. This is only applicable for metrics that measure instantaneous values, like HealthMetricHeartRateBPM.

 |
| c | [health\_service\_aggregate\_averaged](/docs/c/Foundation/Event_Service/HealthService/#health_service_aggregate_averaged) |
| 

Return the value of an aggregated metric over a given time range. This call is more flexible than health\_service\_sum\_averaged because it lets you specify which aggregation function to perform.

 |
| c | [HealthActivityMask](/docs/c/Foundation/Event_Service/HealthService/#HealthActivityMask) |
| 

Expresses a set of [HealthActivity](/docs/c/Foundation/Event_Service/HealthService/#HealthActivity) values as a bitmask.

 |
| c | [HealthActivityMaskAll](/docs/c/Foundation/Event_Service/HealthService/#HealthActivityMaskAll) |
| 

A mask value representing all available activities.

 |
| c | [HealthActivity](/docs/c/Foundation/Event_Service/HealthService/#HealthActivity) |
| 

Health-related activities that can be accessed using.

 |
| c | [HealthActivityNone](/docs/c/Foundation/Event_Service/HealthService/#HealthActivityNone) |
| 

No special activity.

 |
| c | [HealthActivitySleep](/docs/c/Foundation/Event_Service/HealthService/#HealthActivitySleep) |
| 

The 'sleeping' activity.

 |
| c | [HealthActivityRestfulSleep](/docs/c/Foundation/Event_Service/HealthService/#HealthActivityRestfulSleep) |
| 

The 'restful sleeping' activity.

 |
| c | [HealthActivityWalk](/docs/c/Foundation/Event_Service/HealthService/#HealthActivityWalk) |
| 

The 'walk' activity.

 |
| c | [HealthActivityRun](/docs/c/Foundation/Event_Service/HealthService/#HealthActivityRun) |
| 

The 'run' activity.

 |
| c | [HealthActivityOpenWorkout](/docs/c/Foundation/Event_Service/HealthService/#HealthActivityOpenWorkout) |
| 

The 'generic' activity.

 |
| c | [health\_service\_peek\_current\_activities](/docs/c/Foundation/Event_Service/HealthService/#health_service_peek_current_activities) |
| 

Return a [HealthActivityMask](/docs/c/Foundation/Event_Service/HealthService/#HealthActivityMask) containing a set of bits, one set for each activity that is currently active.

 |
| c | [HealthActivityIteratorCB](/docs/c/Foundation/Event_Service/HealthService/#HealthActivityIteratorCB) |
| 

Callback used by [health\_service\_activities\_iterate()](/docs/c/Foundation/Event_Service/HealthService/#health_service_activities_iterate).

 |
| c | [HealthIterationDirection](/docs/c/Foundation/Event_Service/HealthService/#HealthIterationDirection) |
| 

Iteration direction, passed to [health\_service\_activities\_iterate()](/docs/c/Foundation/Event_Service/HealthService/#health_service_activities_iterate). When iterating backwards (`HealthIterationDirectionPast`), activities that have a greater value for `time_end` come first. When iterating forward (`HealthIterationDirectionFuture`), activities that have a smaller value for `time_start` come first.

 |
| c | [HealthIterationDirectionPast](/docs/c/Foundation/Event_Service/HealthService/#HealthIterationDirectionPast) |
| 

Iterate into the past.

 |
| c | [HealthIterationDirectionFuture](/docs/c/Foundation/Event_Service/HealthService/#HealthIterationDirectionFuture) |
| 

Iterate into the future.

 |
| c | [health\_service\_activities\_iterate](/docs/c/Foundation/Event_Service/HealthService/#health_service_activities_iterate) |
| 

Iterates backwards or forward within a given time span to list all recorded activities. For example, this can be used to find the last recorded sleep phase or all deep sleep phases in a given time range. Any activity that overlaps with `time_start` and `time_end` will be included, even if the start time starts before `time_start` or end time ends after `time_end`.

 |
| c | [HealthServiceAccessibilityMask](/docs/c/Foundation/Event_Service/HealthService/#HealthServiceAccessibilityMask) |
| 

Possible values returned by [health\_service\_metric\_accessible()](/docs/c/Foundation/Event_Service/HealthService/#health_service_metric_accessible). The values are used in combination as a bitmask. For example, to check if any data is available for a given request use: bool any\_data\_available = value & HealthServiceAccessibilityMaskAvailable;.

 |
| c | [HealthServiceAccessibilityMaskAvailable](/docs/c/Foundation/Event_Service/HealthService/#HealthServiceAccessibilityMaskAvailable) |
| 

Return values are available and represent the collected health information.

 |
| c | [HealthServiceAccessibilityMaskNoPermission](/docs/c/Foundation/Event_Service/HealthService/#HealthServiceAccessibilityMaskNoPermission) |
| 

The user hasn't granted permission.

 |
| c | [HealthServiceAccessibilityMaskNotSupported](/docs/c/Foundation/Event_Service/HealthService/#HealthServiceAccessibilityMaskNotSupported) |
| 

The queried combination of time span and [HealthMetric](/docs/c/Foundation/Event_Service/HealthService/#HealthMetric) or [HealthActivityMask](/docs/c/Foundation/Event_Service/HealthService/#HealthActivityMask) is currently unsupported.

 |
| c | [HealthServiceAccessibilityMaskNotAvailable](/docs/c/Foundation/Event_Service/HealthService/#HealthServiceAccessibilityMaskNotAvailable) |
| 

No samples were recorded for the given time span.

 |
| c | [health\_service\_metric\_accessible](/docs/c/Foundation/Event_Service/HealthService/#health_service_metric_accessible) |
| 

Check if a certain combination of metric and time span is accessible using [health\_service\_sum](/docs/c/Foundation/Event_Service/HealthService/#health_service_sum) by returning a value of [HealthServiceAccessibilityMask](/docs/c/Foundation/Event_Service/HealthService/#HealthServiceAccessibilityMask). Developers should check if the return value is HealthServiceAccessibilityMaskAvailable before calling [health\_service\_sum](/docs/c/Foundation/Event_Service/HealthService/#health_service_sum).

 |
| c | [health\_service\_metric\_averaged\_accessible](/docs/c/Foundation/Event_Service/HealthService/#health_service_metric_averaged_accessible) |
| 

Check if a certain combination of metric, time span, and scope is accessible for calculating summed, averaged data by returning a value of [HealthServiceAccessibilityMask](/docs/c/Foundation/Event_Service/HealthService/#HealthServiceAccessibilityMask). Developers should check if the return value is HealthServiceAccessibilityMaskAvailable before calling [health\_service\_sum\_averaged](/docs/c/Foundation/Event_Service/HealthService/#health_service_sum_averaged).

 |
| c | [health\_service\_metric\_aggregate\_averaged\_accessible](/docs/c/Foundation/Event_Service/HealthService/#health_service_metric_aggregate_averaged_accessible) |
| 

Check if a certain combination of metric, time span, aggregation operation, and scope is accessible for calculating aggregated, averaged data by returning a value of [HealthServiceAccessibilityMask](/docs/c/Foundation/Event_Service/HealthService/#HealthServiceAccessibilityMask). Developers should check if the return value is HealthServiceAccessibilityMaskAvailable before calling [health\_service\_aggregate\_averaged](/docs/c/Foundation/Event_Service/HealthService/#health_service_aggregate_averaged).

 |
| c | [health\_service\_any\_activity\_accessible](/docs/c/Foundation/Event_Service/HealthService/#health_service_any_activity_accessible) |
| 

Check if a certain combination of metric, [HealthActivityMask](/docs/c/Foundation/Event_Service/HealthService/#HealthActivityMask) and time span is accessible. Developers should check if the return value is HealthServiceAccessibilityMaskAvailable before calling any other HealthService APIs that involve the given activities.

 |
| c | [HealthEventType](/docs/c/Foundation/Event_Service/HealthService/#HealthEventType) |
| 

Health event enum. Passed into the [HealthEventHandler](/docs/c/Foundation/Event_Service/HealthService/#HealthEventHandler).

 |
| c | [HealthEventSignificantUpdate](/docs/c/Foundation/Event_Service/HealthService/#HealthEventSignificantUpdate) |
| 

All data is considered as outdated and apps should re-read all health data. This happens after an app is subscribed via [health\_service\_events\_subscribe()](/docs/c/Foundation/Event_Service/HealthService/#health_service_events_subscribe), on a change of the day, or in other cases that significantly change the underlying data.

 |
| c | [HealthEventMovementUpdate](/docs/c/Foundation/Event_Service/HealthService/#HealthEventMovementUpdate) |
| 

Recent values around HealthMetricStepCount, HealthMetricActiveSeconds, or HealthMetricWalkedDistanceMeters have changed.

 |
| c | [HealthEventSleepUpdate](/docs/c/Foundation/Event_Service/HealthService/#HealthEventSleepUpdate) |
| 

Recent values around HealthMetricSleepSeconds, HealthMetricSleepRestfulSeconds, HealthActivitySleep, and HealthActivityRestfulSleep changed.

 |
| c | [HealthEventMetricAlert](/docs/c/Foundation/Event_Service/HealthService/#HealthEventMetricAlert) |
| 

A metric has crossed the threshold set by [health\_service\_register\_metric\_alert](/docs/c/Foundation/Event_Service/HealthService/#health_service_register_metric_alert).

 |
| c | [HealthEventHeartRateUpdate](/docs/c/Foundation/Event_Service/HealthService/#HealthEventHeartRateUpdate) |
| 

Value of HealthMetricHeartRateBPM or HealthMetricHeartRateRawBPM has changed.

 |
| c | [HealthEventHandler](/docs/c/Foundation/Event_Service/HealthService/#HealthEventHandler) |
| 

Developer-supplied event handler, called when a health-related event occurs after subscribing via [health\_service\_events\_subscribe()](/docs/c/Foundation/Event_Service/HealthService/#health_service_events_subscribe);.

 |
| c | [health\_service\_events\_subscribe](/docs/c/Foundation/Event_Service/HealthService/#health_service_events_subscribe) |
| 

Subscribe to HealthService events. This allocates a cache on the application's heap of up to 2048 bytes that will be de-allocated if you call [health\_service\_events\_unsubscribe()](/docs/c/Foundation/Event_Service/HealthService/#health_service_events_unsubscribe). If there's not enough heap available, this function will return `false` and will not subscribe to any events.

 |
| c | [health\_service\_events\_unsubscribe](/docs/c/Foundation/Event_Service/HealthService/#health_service_events_unsubscribe) |
| 

Unsubscribe from HealthService events.

 |
| c | [health\_service\_set\_heart\_rate\_sample\_period](/docs/c/Foundation/Event_Service/HealthService/#health_service_set_heart_rate_sample_period) |
| 

Set the desired sampling period for heart rate readings. Normally, the system will sample the heart rate using a sampling period that is automatically chosen to provide useful information without undue battery drain (it automatically samples more often during periods of intense activity, and less often when the user is idle). If desired though, an application can request a specific sampling period using this call. The system will use this as a suggestion, but does not guarantee that the requested period will be used. The actual sampling period may be greater or less due to system needs or heart rate sensor reading quality issues.

 |
| c | [health\_service\_get\_heart\_rate\_sample\_period\_expiration\_sec](/docs/c/Foundation/Event_Service/HealthService/#health_service_get_heart_rate_sample_period_expiration_sec) |
| 

Return how long a heart rate sample period request (sent via `health_service_set_heart_rate_sample_period`) will remain active after the app exits. If there is no current request by this app, this call will return 0.

 |
| c | [health\_service\_register\_metric\_alert](/docs/c/Foundation/Event_Service/HealthService/#health_service_register_metric_alert) |
| 

Register for an alert when a metric crosses the given threshold. When the metric crosses this threshold (either goes above or below it), a HealthEventMetricAlert event will be generated. To cancel this registration, pass the returned [HealthMetricAlert](/docs/c/Foundation/Event_Service/HealthService/#HealthMetricAlert) value to [health\_service\_cancel\_metric\_alert](/docs/c/Foundation/Event_Service/HealthService/#health_service_cancel_metric_alert). The only metric currently supported by this call is HealthMetricHeartRateBPM, but future versions may support additional metrics. To see if a specific metric is supported by this call, use:

 |
| c | [health\_service\_cancel\_metric\_alert](/docs/c/Foundation/Event_Service/HealthService/#health_service_cancel_metric_alert) |
| 

Cancel an metric alert previously created with [health\_service\_register\_metric\_alert](/docs/c/Foundation/Event_Service/HealthService/#health_service_register_metric_alert).

 |
| c | [AmbientLightLevel](/docs/c/Foundation/Event_Service/HealthService/#AmbientLightLevel) |
| 

Light level enum.

 |
| c | [AmbientLightLevelUnknown](/docs/c/Foundation/Event_Service/HealthService/#AmbientLightLevelUnknown) |
| |
| c | [AmbientLightLevelVeryDark](/docs/c/Foundation/Event_Service/HealthService/#AmbientLightLevelVeryDark) |
| |
| c | [AmbientLightLevelDark](/docs/c/Foundation/Event_Service/HealthService/#AmbientLightLevelDark) |
| |
| c | [AmbientLightLevelLight](/docs/c/Foundation/Event_Service/HealthService/#AmbientLightLevelLight) |
| |
| c | [AmbientLightLevelVeryLight](/docs/c/Foundation/Event_Service/HealthService/#AmbientLightLevelVeryLight) |
| |
| c | [health\_service\_get\_minute\_history](/docs/c/Foundation/Event_Service/HealthService/#health_service_get_minute_history) |
| 

Return historical minute data records. This fills in the `minute_data` array parameter with minute by minute statistics of the user's steps, average watch orientation, etc. The data is returned in time order, with the oldest minute data returned at `minute_data[0]`.

 |
| c | [PBL\_IF\_HEALTH\_ELSE](/docs/c/Foundation/Event_Service/HealthService/#PBL_IF_HEALTH_ELSE) |
| 

Convenience macro to switch between two expressions depending on health support. On platforms with health support the first expression will be chosen, the second otherwise.

 |
| c | [MeasurementSystem](/docs/c/Foundation/Event_Service/HealthService/#MeasurementSystem) |
| 

Types of measurement system a [HealthMetric](/docs/c/Foundation/Event_Service/HealthService/#HealthMetric) may be measured in.

 |
| c | [MeasurementSystemUnknown](/docs/c/Foundation/Event_Service/HealthService/#MeasurementSystemUnknown) |
| 

The measurement system is unknown, or does not apply to the chosen metric.

 |
| c | [MeasurementSystemMetric](/docs/c/Foundation/Event_Service/HealthService/#MeasurementSystemMetric) |
| 

The metric measurement system.

 |
| c | [MeasurementSystemImperial](/docs/c/Foundation/Event_Service/HealthService/#MeasurementSystemImperial) |
| 

The imperial measurement system.

 |
| c | [health\_service\_get\_measurement\_system\_for\_display](/docs/c/Foundation/Event_Service/HealthService/#health_service_get_measurement_system_for_display) |
| 

Get the preferred measurement system for a given [HealthMetric](/docs/c/Foundation/Event_Service/HealthService/#HealthMetric), if the user has chosen a preferred system and it is applicable to that metric.

 |
| c | [HealthMinuteData](/docs/c/Foundation/Event_Service/HealthService/#HealthMinuteData) |
| 

Structure representing a single minute data record returned by [health\_service\_get\_minute\_history()](/docs/c/Foundation/Event_Service/HealthService/#health_service_get_minute_history). The `orientation` field encodes the angle of the watch in the x-y plane (the "yaw") in the lower 4 bits (360 degrees linearly mapped to 1 of 16 different values) and the angle to the z axis (the "pitch") in the upper 4 bits. The `vmc` value is a measure of the total amount of movement seen by the watch. More vigorous movement yields higher VMC values.

 |
| c | [TickTimerService](/docs/c/Foundation/Event_Service/TickTimerService/) |
| 

Handling time components

 |
| c | [TimeUnits](/docs/c/Foundation/Event_Service/TickTimerService/#TimeUnits) |
| 

Time unit flags that can be used to create a bitmask for use in [tick\_timer\_service\_subscribe()](/docs/c/Foundation/Event_Service/TickTimerService/#tick_timer_service_subscribe). This will also be passed to [TickHandler](/docs/c/Foundation/Event_Service/TickTimerService/#TickHandler).

 |
| c | [SECOND\_UNIT](/docs/c/Foundation/Event_Service/TickTimerService/#SECOND_UNIT) |
| 

Flag to represent the "seconds" time unit.

 |
| c | [MINUTE\_UNIT](/docs/c/Foundation/Event_Service/TickTimerService/#MINUTE_UNIT) |
| 

Flag to represent the "minutes" time unit.

 |
| c | [HOUR\_UNIT](/docs/c/Foundation/Event_Service/TickTimerService/#HOUR_UNIT) |
| 

Flag to represent the "hours" time unit.

 |
| c | [DAY\_UNIT](/docs/c/Foundation/Event_Service/TickTimerService/#DAY_UNIT) |
| 

Flag to represent the "days" time unit.

 |
| c | [MONTH\_UNIT](/docs/c/Foundation/Event_Service/TickTimerService/#MONTH_UNIT) |
| 

Flag to represent the "months" time unit.

 |
| c | [YEAR\_UNIT](/docs/c/Foundation/Event_Service/TickTimerService/#YEAR_UNIT) |
| 

Flag to represent the "years" time unit.

 |
| c | [TickHandler](/docs/c/Foundation/Event_Service/TickTimerService/#TickHandler) |
| 

Callback type for tick timer events.

 |
| c | [tick\_timer\_service\_subscribe](/docs/c/Foundation/Event_Service/TickTimerService/#tick_timer_service_subscribe) |
| 

Subscribe to the tick timer event service. Once subscribed, the handler gets called on every requested unit change. Calling this function multiple times will override the units and handler (i.e., only&nbsp; the&nbsp;last&nbsp;tick\_units and&nbsp;handler passed&nbsp;will&nbsp;be&nbsp;used).

 |
| c | [tick\_timer\_service\_unsubscribe](/docs/c/Foundation/Event_Service/TickTimerService/#tick_timer_service_unsubscribe) |
| 

Unsubscribe from the tick timer event service. Once unsubscribed, the previously registered handler will no longer be called.

 |
| c | [TouchService](/docs/c/Foundation/Event_Service/TouchService/) |
| |
| c | [TouchEventType](/docs/c/Foundation/Event_Service/TouchService/#TouchEventType) |
| 

Touch event type.

 |
| c | [TouchEvent\_Touchdown](/docs/c/Foundation/Event_Service/TouchService/#TouchEvent_Touchdown) |
| |
| c | [TouchEvent\_Liftoff](/docs/c/Foundation/Event_Service/TouchService/#TouchEvent_Liftoff) |
| |
| c | [TouchEvent\_PositionUpdate](/docs/c/Foundation/Event_Service/TouchService/#TouchEvent_PositionUpdate) |
| |
| c | [TouchServiceHandler](/docs/c/Foundation/Event_Service/TouchService/#TouchServiceHandler) |
| 

Callback for touch events.

 |
| c | [touch\_service\_subscribe](/docs/c/Foundation/Event_Service/TouchService/#touch_service_subscribe) |
| 

Subscribe to touch events. The touch sensor is enabled while subscribed.

 |
| c | [touch\_service\_unsubscribe](/docs/c/Foundation/Event_Service/TouchService/#touch_service_unsubscribe) |
| 

Unsubscribe from touch events. The touch sensor is disabled if no other subscribers remain.

 |
| c | [touch\_service\_is\_enabled](/docs/c/Foundation/Event_Service/TouchService/#touch_service_is_enabled) |
| |
| c | [TouchEvent](/docs/c/Foundation/Event_Service/TouchService/#TouchEvent) |
| 

Touch event data, carried directly in PebbleTouchEvent.

 |
| c | [Exit Reason](/docs/c/Foundation/Exit_Reason/) |
| 

API for the application to notify the system of the reason it will exit.

 |
| c | [AppExitReason](/docs/c/Foundation/Exit_Reason/#AppExitReason) |
| 

[AppExitReason](/docs/c/Foundation/Exit_Reason/#AppExitReason) is used to notify the system of the reason of an application exiting, which may affect the part of the system UI that is presented after the application terminates.

 |
| c | [APP\_EXIT\_NOT\_SPECIFIED](/docs/c/Foundation/Exit_Reason/#APP_EXIT_NOT_SPECIFIED) |
| 

Exit reason not specified.

 |
| c | [APP\_EXIT\_ACTION\_PERFORMED\_SUCCESSFULLY](/docs/c/Foundation/Exit_Reason/#APP_EXIT_ACTION_PERFORMED_SUCCESSFULLY) |
| 

Application performed an action when it exited.

 |
| c | [NUM\_EXIT\_REASONS](/docs/c/Foundation/Exit_Reason/#NUM_EXIT_REASONS) |
| 

Number of [AppExitReason](/docs/c/Foundation/Exit_Reason/#AppExitReason) options.

 |
| c | [exit\_reason\_set](/docs/c/Foundation/Exit_Reason/#exit_reason_set) |
| 

Set the app exit reason to a new reason.

 |
| c | [Internationalization](/docs/c/Foundation/Internationalization/) |
| 

Internationalization & Localization APIs

 |
| c | [i18n\_get\_system\_locale](/docs/c/Foundation/Internationalization/#i18n_get_system_locale) |
| 

Get the ISO locale name for the language currently set on the watch.

 |
| c | [Launch Reason](/docs/c/Foundation/Launch_Reason/) |
| 

API for checking what caused the application to launch.

 |
| c | [AppLaunchReason](/docs/c/Foundation/Launch_Reason/#AppLaunchReason) |
| 

[AppLaunchReason](/docs/c/Foundation/Launch_Reason/#AppLaunchReason) is used to inform the application about how it was launched.

 |
| c | [APP\_LAUNCH\_SYSTEM](/docs/c/Foundation/Launch_Reason/#APP_LAUNCH_SYSTEM) |
| 

App launched by the system.

 |
| c | [APP\_LAUNCH\_USER](/docs/c/Foundation/Launch_Reason/#APP_LAUNCH_USER) |
| 

App launched by user selection in launcher menu.

 |
| c | [APP\_LAUNCH\_PHONE](/docs/c/Foundation/Launch_Reason/#APP_LAUNCH_PHONE) |
| 

App launched by mobile or companion app.

 |
| c | [APP\_LAUNCH\_WAKEUP](/docs/c/Foundation/Launch_Reason/#APP_LAUNCH_WAKEUP) |
| 

App launched by wakeup event.

 |
| c | [APP\_LAUNCH\_WORKER](/docs/c/Foundation/Launch_Reason/#APP_LAUNCH_WORKER) |
| 

App launched by worker calling [worker\_launch\_app()](/docs/c/Worker/#worker_launch_app)

 |
| c | [APP\_LAUNCH\_QUICK\_LAUNCH](/docs/c/Foundation/Launch_Reason/#APP_LAUNCH_QUICK_LAUNCH) |
| 

App launched by user using quick launch.

 |
| c | [APP\_LAUNCH\_TIMELINE\_ACTION](/docs/c/Foundation/Launch_Reason/#APP_LAUNCH_TIMELINE_ACTION) |
| 

App launched by user opening it from a pin.

 |
| c | [APP\_LAUNCH\_SMARTSTRAP](/docs/c/Foundation/Launch_Reason/#APP_LAUNCH_SMARTSTRAP) |
| 

App launched by a smartstrap.

 |
| c | [launch\_reason](/docs/c/Foundation/Launch_Reason/#launch_reason) |
| 

Provides the method used to launch the current application.

 |
| c | [launch\_get\_args](/docs/c/Foundation/Launch_Reason/#launch_get_args) |
| 

Get the argument passed to the app when it was launched.

 |
| c | [Logging](/docs/c/Foundation/Logging/) |
| 

Functions related to logging from apps.

 |
| c | [app\_log](/docs/c/Foundation/Logging/#app_log) |
| |
| c | [APP\_LOG](/docs/c/Foundation/Logging/#APP_LOG) |
| 

A helper macro that simplifies the use of the app\_log function.

 |
| c | [AppLogLevel](/docs/c/Foundation/Logging/#AppLogLevel) |
| 

Suggested log level values.

 |
| c | [APP\_LOG\_LEVEL\_ERROR](/docs/c/Foundation/Logging/#APP_LOG_LEVEL_ERROR) |
| 

Error level log message.

 |
| c | [APP\_LOG\_LEVEL\_WARNING](/docs/c/Foundation/Logging/#APP_LOG_LEVEL_WARNING) |
| 

Warning level log message.

 |
| c | [APP\_LOG\_LEVEL\_INFO](/docs/c/Foundation/Logging/#APP_LOG_LEVEL_INFO) |
| 

Info level log message.

 |
| c | [APP\_LOG\_LEVEL\_DEBUG](/docs/c/Foundation/Logging/#APP_LOG_LEVEL_DEBUG) |
| 

Debug level log message.

 |
| c | [APP\_LOG\_LEVEL\_DEBUG\_VERBOSE](/docs/c/Foundation/Logging/#APP_LOG_LEVEL_DEBUG_VERBOSE) |
| 

Verbose Debug level log message.

 |
| c | [Math](/docs/c/Foundation/Math/) |
| 

Math routines.

 |
| c | [TRIG\_MAX\_RATIO](/docs/c/Foundation/Math/#TRIG_MAX_RATIO) |
| 

The largest value that can result from a call to [sin\_lookup](/docs/c/Foundation/Math/#sin_lookup) or [cos\_lookup](/docs/c/Foundation/Math/#cos_lookup). For a code example, see the detailed description at the top of this chapter: [Math](/docs/c/Foundation/Math/).

 |
| c | [TRIG\_MAX\_ANGLE](/docs/c/Foundation/Math/#TRIG_MAX_ANGLE) |
| 

Angle value that corresponds to 360 degrees or 2 PI radians.

 |
| c | [TRIGANGLE\_TO\_DEG](/docs/c/Foundation/Math/#TRIGANGLE_TO_DEG) |
| 

Converts from a fixed point value representation to the equivalent value in degrees.

 |
| c | [DEG\_TO\_TRIGANGLE](/docs/c/Foundation/Math/#DEG_TO_TRIGANGLE) |
| 

Converts from an angle in degrees to the equivalent fixed point value representation.

 |
| c | [sin\_lookup](/docs/c/Foundation/Math/#sin_lookup) |
| 

Look-up the sine of the given angle from a pre-computed table.

 |
| c | [cos\_lookup](/docs/c/Foundation/Math/#cos_lookup) |
| 

Look-up the cosine of the given angle from a pre-computed table. This is equivalent to calling `sin_lookup(angle + TRIG_MAX_ANGLE / 4)`.

 |
| c | [atan2\_lookup](/docs/c/Foundation/Math/#atan2_lookup) |
| 

Look-up the arctangent of a given x, y pair The angle value is scaled linearly, such that a value of 0x10000 corresponds to 360 degrees or 2 PI radians.

 |
| c | [Memory Management](/docs/c/Foundation/Memory_Management/) |
| 

Utility functions for managing an application's memory.

 |
| c | [heap\_bytes\_free](/docs/c/Foundation/Memory_Management/#heap_bytes_free) |
| 

Calculates the number of bytes of heap memory _not_ currently being used by the application.

 |
| c | [heap\_bytes\_used](/docs/c/Foundation/Memory_Management/#heap_bytes_used) |
| 

Calculates the number of bytes of heap memory currently being used by the application.

 |
| c | [memory\_cache\_flush](/docs/c/Foundation/Memory_Management/#memory_cache_flush) |
| 

Flushes the data cache and invalidates the instruction cache for the given region of memory, if necessary. This is only required when your app is loading or modifying code in memory and intends to execute it. On some platforms, code executed may be cached internally to improve performance. After writing to memory, but before executing, this function must be called in order to avoid undefined behavior. On platforms without caching, this performs no operation.

 |
| c | [Platform](/docs/c/Foundation/Platform/) |
| |
| c | [PlatformType](/docs/c/Foundation/Platform/#PlatformType) |
| |
| c | [PlatformTypeAplite](/docs/c/Foundation/Platform/#PlatformTypeAplite) |
| |
| c | [PlatformTypeBasalt](/docs/c/Foundation/Platform/#PlatformTypeBasalt) |
| |
| c | [PlatformTypeChalk](/docs/c/Foundation/Platform/#PlatformTypeChalk) |
| |
| c | [PlatformTypeDiorite](/docs/c/Foundation/Platform/#PlatformTypeDiorite) |
| |
| c | [PlatformTypeEmery](/docs/c/Foundation/Platform/#PlatformTypeEmery) |
| |
| c | [PlatformTypeFlint](/docs/c/Foundation/Platform/#PlatformTypeFlint) |
| |
| c | [PlatformTypeGabbro](/docs/c/Foundation/Platform/#PlatformTypeGabbro) |
| |
| c | [PBL\_PLATFORM\_TYPE\_CURRENT](/docs/c/Foundation/Platform/#PBL_PLATFORM_TYPE_CURRENT) |
| |
| c | [PBL\_PLATFORM\_SWITCH\_DEFAULT](/docs/c/Foundation/Platform/#PBL_PLATFORM_SWITCH_DEFAULT) |
| |
| c | [PBL\_PLATFORM\_SWITCH](/docs/c/Foundation/Platform/#PBL_PLATFORM_SWITCH) |
| |
| c | [Resources](/docs/c/Foundation/Resources/) |
| 

Managing application resources

 |
| c | [ResHandle](/docs/c/Foundation/Resources/#ResHandle) |
| 

Opaque reference to a resource.

 |
| c | [RESOURCE\_ID\_FONT\_FALLBACK](/docs/c/Foundation/Resources/#RESOURCE_ID_FONT_FALLBACK) |
| |
| c | [resource\_get\_handle](/docs/c/Foundation/Resources/#resource_get_handle) |
| 

Gets the resource handle for a file identifier.

 |
| c | [resource\_size](/docs/c/Foundation/Resources/#resource_size) |
| 

Gets the size of the resource given a resource handle.

 |
| c | [resource\_load](/docs/c/Foundation/Resources/#resource_load) |
| 

Copies the bytes for the resource with a given handle from flash storage into a given buffer.

 |
| c | [resource\_load\_byte\_range](/docs/c/Foundation/Resources/#resource_load_byte_range) |
| 

Copies a range of bytes from a resource with a given handle into a given buffer.

 |
| c | [File Formats](/docs/c/Foundation/Resources/File_Formats/) |
| |
| c | [PBI File Format](/docs/c/Foundation/Resources/File_Formats/PBI_File_Format/) |
| |
| c | [PNG8 File Format](/docs/c/Foundation/Resources/File_Formats/PNG8_File_Format/) |
| |
| c | [Storage](/docs/c/Foundation/Storage/) |
| 

A mechanism to store persistent application data and state

 |
| c | [PERSIST\_DATA\_MAX\_LENGTH](/docs/c/Foundation/Storage/#PERSIST_DATA_MAX_LENGTH) |
| 

The maximum size of a persist value in bytes.

 |
| c | [PERSIST\_STRING\_MAX\_LENGTH](/docs/c/Foundation/Storage/#PERSIST_STRING_MAX_LENGTH) |
| 

The maximum size of a persist string in bytes including the NULL terminator.

 |
| c | [StatusCode](/docs/c/Foundation/Storage/#StatusCode) |
| 

Status codes. See [status\_t](/docs/c/Foundation/Storage/#status_t).

 |
| c | [S\_SUCCESS](/docs/c/Foundation/Storage/#S_SUCCESS) |
| 

Operation completed successfully.

 |
| c | [E\_ERROR](/docs/c/Foundation/Storage/#E_ERROR) |
| 

An error occurred (no description).

 |
| c | [E\_UNKNOWN](/docs/c/Foundation/Storage/#E_UNKNOWN) |
| 

No idea what went wrong.

 |
| c | [E\_INTERNAL](/docs/c/Foundation/Storage/#E_INTERNAL) |
| 

There was a generic internal logic error.

 |
| c | [E\_INVALID\_ARGUMENT](/docs/c/Foundation/Storage/#E_INVALID_ARGUMENT) |
| 

The function was not called correctly.

 |
| c | [E\_OUT\_OF\_MEMORY](/docs/c/Foundation/Storage/#E_OUT_OF_MEMORY) |
| 

Insufficient allocatable memory available.

 |
| c | [E\_OUT\_OF\_STORAGE](/docs/c/Foundation/Storage/#E_OUT_OF_STORAGE) |
| 

Insufficient long-term storage available.

 |
| c | [E\_OUT\_OF\_RESOURCES](/docs/c/Foundation/Storage/#E_OUT_OF_RESOURCES) |
| 

Insufficient resources available.

 |
| c | [E\_RANGE](/docs/c/Foundation/Storage/#E_RANGE) |
| 

Argument out of range (may be dynamic).

 |
| c | [E\_DOES\_NOT\_EXIST](/docs/c/Foundation/Storage/#E_DOES_NOT_EXIST) |
| 

Target of operation does not exist.

 |
| c | [E\_INVALID\_OPERATION](/docs/c/Foundation/Storage/#E_INVALID_OPERATION) |
| 

Operation not allowed (may depend on state).

 |
| c | [E\_BUSY](/docs/c/Foundation/Storage/#E_BUSY) |
| 

Another operation prevented this one.

 |
| c | [E\_AGAIN](/docs/c/Foundation/Storage/#E_AGAIN) |
| 

Operation not completed; try again.

 |
| c | [S\_TRUE](/docs/c/Foundation/Storage/#S_TRUE) |
| 

Equivalent of boolean true.

 |
| c | [S\_FALSE](/docs/c/Foundation/Storage/#S_FALSE) |
| 

Equivalent of boolean false.

 |
| c | [S\_NO\_MORE\_ITEMS](/docs/c/Foundation/Storage/#S_NO_MORE_ITEMS) |
| 

For list-style requests. At end of list.

 |
| c | [S\_NO\_ACTION\_REQUIRED](/docs/c/Foundation/Storage/#S_NO_ACTION_REQUIRED) |
| 

No action was taken as none was required.

 |
| c | [status\_t](/docs/c/Foundation/Storage/#status_t) |
| 

Return value for system operations. See [StatusCode](/docs/c/Foundation/Storage/#StatusCode) for possible values.

 |
| c | [persist\_exists](/docs/c/Foundation/Storage/#persist_exists) |
| 

Checks whether a value has been set for a given key in persistent storage.

 |
| c | [persist\_get\_size](/docs/c/Foundation/Storage/#persist_get_size) |
| 

Gets the size of a value for a given key in persistent storage.

 |
| c | [persist\_read\_bool](/docs/c/Foundation/Storage/#persist_read_bool) |
| 

Reads a bool value for a given key from persistent storage. If the value has not yet been set, this will return false.

 |
| c | [persist\_read\_int](/docs/c/Foundation/Storage/#persist_read_int) |
| 

Reads an int value for a given key from persistent storage.

 |
| c | [persist\_read\_data](/docs/c/Foundation/Storage/#persist_read_data) |
| 

Reads a blob of data for a given key from persistent storage into a given buffer. If the value has not yet been set, the given buffer is left unchanged.

 |
| c | [persist\_read\_string](/docs/c/Foundation/Storage/#persist_read_string) |
| 

Reads a string for a given key from persistent storage into a given buffer. The string will be null terminated. If the value has not yet been set, the given buffer is left unchanged.

 |
| c | [persist\_write\_bool](/docs/c/Foundation/Storage/#persist_write_bool) |
| 

Writes a bool value flag for a given key into persistent storage.

 |
| c | [persist\_write\_int](/docs/c/Foundation/Storage/#persist_write_int) |
| 

Writes an int value for a given key into persistent storage.

 |
| c | [persist\_write\_data](/docs/c/Foundation/Storage/#persist_write_data) |
| 

Writes a blob of data of a specified size in bytes for a given key into persistent storage. The maximum size is [PERSIST\_DATA\_MAX\_LENGTH](/docs/c/Foundation/Storage/#PERSIST_DATA_MAX_LENGTH).

 |
| c | [persist\_write\_string](/docs/c/Foundation/Storage/#persist_write_string) |
| 

Writes a string a given key into persistent storage. The maximum size is [PERSIST\_STRING\_MAX\_LENGTH](/docs/c/Foundation/Storage/#PERSIST_STRING_MAX_LENGTH) including the null terminator.

 |
| c | [persist\_delete](/docs/c/Foundation/Storage/#persist_delete) |
| 

Deletes the value of a key from persistent storage.

 |
| c | [Timer](/docs/c/Foundation/Timer/) |
| 

Can be used to execute some code at some point in the future.

 |
| c | [psleep](/docs/c/Foundation/Timer/#psleep) |
| 

Waits for a certain amount of milliseconds.

 |
| c | [AppTimer](/docs/c/Foundation/Timer/#AppTimer) |
| |
| c | [AppTimerCallback](/docs/c/Foundation/Timer/#AppTimerCallback) |
| 

The type of function which can be called when a timer fires. The argument will be the `callback_data` passed to [app\_timer\_register()](/docs/c/Foundation/Timer/#app_timer_register).

 |
| c | [app\_timer\_register](/docs/c/Foundation/Timer/#app_timer_register) |
| 

Registers a timer that ends up in callback being called some specified time in the future.

 |
| c | [app\_timer\_reschedule](/docs/c/Foundation/Timer/#app_timer_reschedule) |
| 

Reschedules an already running timer for some point in the future. Elapsed timers cannot be rescheduled.

 |
| c | [app\_timer\_cancel](/docs/c/Foundation/Timer/#app_timer_cancel) |
| 

Cancels an already registered timer. Once cancelled the handle may no longer be used for any purpose. Elapsed timers do not need to be cancelled.

 |
| c | [Wakeup](/docs/c/Foundation/Wakeup/) |
| 

Allows applications to schedule to be launched even if they are not running.

 |
| c | [WakeupId](/docs/c/Foundation/Wakeup/#WakeupId) |
| 

[WakeupId](/docs/c/Foundation/Wakeup/#WakeupId) is an identifier for a wakeup event.

 |
| c | [WakeupHandler](/docs/c/Foundation/Wakeup/#WakeupHandler) |
| 

The type of function which can be called when a wakeup event occurs.   
 The arguments will be the id of the wakeup event that occurred, as well as the scheduled cookie provided to [wakeup\_schedule](/docs/c/Foundation/Wakeup/#wakeup_schedule).

 |
| c | [wakeup\_service\_subscribe](/docs/c/Foundation/Wakeup/#wakeup_service_subscribe) |
| 

Registers a [WakeupHandler](/docs/c/Foundation/Wakeup/#WakeupHandler) to be called when wakeup events occur.

 |
| c | [wakeup\_schedule](/docs/c/Foundation/Wakeup/#wakeup_schedule) |
| 

Registers a wakeup event that triggers a callback at the specified time. Applications may only schedule up to 8 wakeup events. Wakeup events are given a 1 minute duration window, in that no application may schedule a wakeup event with 1 minute of a currently scheduled wakeup event.

 |
| c | [wakeup\_cancel](/docs/c/Foundation/Wakeup/#wakeup_cancel) |
| 

Cancels a wakeup event.

 |
| c | [wakeup\_cancel\_all](/docs/c/Foundation/Wakeup/#wakeup_cancel_all) |
| 

Cancels all wakeup event for the app.

 |
| c | [wakeup\_get\_launch\_event](/docs/c/Foundation/Wakeup/#wakeup_get_launch_event) |
| 

Retrieves the wakeup event info for an app that was launched by a wakeup\_event (ie. [launch\_reason()](/docs/c/Foundation/Launch_Reason/#launch_reason) === APP\_LAUNCH\_WAKEUP) so that an app may display information regarding the wakeup event.

 |
| c | [wakeup\_query](/docs/c/Foundation/Wakeup/#wakeup_query) |
| 

Checks if the current [WakeupId](/docs/c/Foundation/Wakeup/#WakeupId) is still scheduled and therefore valid.

 |
| c | [Wall Time](/docs/c/Foundation/Wall_Time/) |
| 

Functions, data structures and other things related to wall clock time.

 |
| c | [WeekDay](/docs/c/Foundation/Wall_Time/#WeekDay) |
| 

Weekday values.

 |
| c | [TODAY](/docs/c/Foundation/Wall_Time/#TODAY) |
| 

Today.

 |
| c | [SUNDAY](/docs/c/Foundation/Wall_Time/#SUNDAY) |
| 

Sunday.

 |
| c | [MONDAY](/docs/c/Foundation/Wall_Time/#MONDAY) |
| 

Monday.

 |
| c | [TUESDAY](/docs/c/Foundation/Wall_Time/#TUESDAY) |
| 

Tuesday.

 |
| c | [WEDNESDAY](/docs/c/Foundation/Wall_Time/#WEDNESDAY) |
| 

Wednesday.

 |
| c | [THURSDAY](/docs/c/Foundation/Wall_Time/#THURSDAY) |
| 

Thursday.

 |
| c | [FRIDAY](/docs/c/Foundation/Wall_Time/#FRIDAY) |
| 

Friday.

 |
| c | [SATURDAY](/docs/c/Foundation/Wall_Time/#SATURDAY) |
| 

Saturday.

 |
| c | [clock\_copy\_time\_string](/docs/c/Foundation/Wall_Time/#clock_copy_time_string) |
| 

Copies a time string into the buffer, formatted according to the user's time display preferences (such as 12h/24h time). Example results: "7:30" or "15:00".

 |
| c | [clock\_is\_24h\_style](/docs/c/Foundation/Wall_Time/#clock_is_24h_style) |
| 

Gets the user's 12/24h clock style preference.

 |
| c | [clock\_to\_timestamp](/docs/c/Foundation/Wall_Time/#clock_to_timestamp) |
| 

Converts a (day, hour, minute) specification to a UTC timestamp occurring in the future Always returns a timestamp for the next occurring instance, example: specifying TODAY@14:30 when it is 14:40 will return a timestamp for 7 days from now at 14:30.

 |
| c | [clock\_is\_timezone\_set](/docs/c/Foundation/Wall_Time/#clock_is_timezone_set) |
| 

Checks if timezone is currently set, otherwise gmtime == localtime.

 |
| c | [TIMEZONE\_NAME\_LENGTH](/docs/c/Foundation/Wall_Time/#TIMEZONE_NAME_LENGTH) |
| 

The maximum length for a timezone full name (e.g. America/Chicago)

 |
| c | [clock\_get\_timezone](/docs/c/Foundation/Wall_Time/#clock_get_timezone) |
| 

If timezone is set, copies the current timezone long name (e.g. America/Chicago) to user-provided buffer.

 |
| c | [WatchInfo](/docs/c/Foundation/WatchInfo/) |
| 

Provides information about the watch itself.

 |
| c | [WatchInfoModel](/docs/c/Foundation/WatchInfo/#WatchInfoModel) |
| 

The different watch models.

 |
| c | [WATCH\_INFO\_MODEL\_UNKNOWN](/docs/c/Foundation/WatchInfo/#WATCH_INFO_MODEL_UNKNOWN) |
| 

Unknown model.

 |
| c | [WATCH\_INFO\_MODEL\_PEBBLE\_ORIGINAL](/docs/c/Foundation/WatchInfo/#WATCH_INFO_MODEL_PEBBLE_ORIGINAL) |
| 

Original Pebble.

 |
| c | [WATCH\_INFO\_MODEL\_PEBBLE\_STEEL](/docs/c/Foundation/WatchInfo/#WATCH_INFO_MODEL_PEBBLE_STEEL) |
| 

Pebble Steel.

 |
| c | [WATCH\_INFO\_MODEL\_PEBBLE\_TIME](/docs/c/Foundation/WatchInfo/#WATCH_INFO_MODEL_PEBBLE_TIME) |
| 

Pebble Time.

 |
| c | [WATCH\_INFO\_MODEL\_PEBBLE\_TIME\_STEEL](/docs/c/Foundation/WatchInfo/#WATCH_INFO_MODEL_PEBBLE_TIME_STEEL) |
| 

Pebble Time Steel.

 |
| c | [WATCH\_INFO\_MODEL\_PEBBLE\_TIME\_ROUND\_14](/docs/c/Foundation/WatchInfo/#WATCH_INFO_MODEL_PEBBLE_TIME_ROUND_14) |
| 

Pebble Time Round, 14mm lug size.

 |
| c | [WATCH\_INFO\_MODEL\_PEBBLE\_TIME\_ROUND\_20](/docs/c/Foundation/WatchInfo/#WATCH_INFO_MODEL_PEBBLE_TIME_ROUND_20) |
| 

Pebble Time Round, 20mm lug size.

 |
| c | [WATCH\_INFO\_MODEL\_PEBBLE\_2\_HR](/docs/c/Foundation/WatchInfo/#WATCH_INFO_MODEL_PEBBLE_2_HR) |
| 

Pebble 2 HR.

 |
| c | [WATCH\_INFO\_MODEL\_PEBBLE\_2\_SE](/docs/c/Foundation/WatchInfo/#WATCH_INFO_MODEL_PEBBLE_2_SE) |
| 

Pebble 2 SE.

 |
| c | [WATCH\_INFO\_MODEL\_PEBBLE\_TIME\_2](/docs/c/Foundation/WatchInfo/#WATCH_INFO_MODEL_PEBBLE_TIME_2) |
| 

Pebble Time 2.

 |
| c | [WATCH\_INFO\_MODEL\_COREDEVICES\_P2D](/docs/c/Foundation/WatchInfo/#WATCH_INFO_MODEL_COREDEVICES_P2D) |
| 

CoreDevices P2D (Pebble 2 Duo)

 |
| c | [WATCH\_INFO\_MODEL\_COREDEVICES\_PT2](/docs/c/Foundation/WatchInfo/#WATCH_INFO_MODEL_COREDEVICES_PT2) |
| 

CoreDevices PT2 (Pebble Time 2)

 |
| c | [WATCH\_INFO\_MODEL\_COREDEVICES\_PR2](/docs/c/Foundation/WatchInfo/#WATCH_INFO_MODEL_COREDEVICES_PR2) |
| 

CoreDevices PR2 (Pebble Round 2)

 |
| c | [WATCH\_INFO\_MODEL\_\_MAX](/docs/c/Foundation/WatchInfo/#WATCH_INFO_MODEL__MAX) |
| |
| c | [WATCH\_INFO\_MODEL\_COREDEVICES\_C2D](/docs/c/Foundation/WatchInfo/#WATCH_INFO_MODEL_COREDEVICES_C2D) |
| 

CoreDevices C2D (Core 2 Duo)

 |
| c | [WATCH\_INFO\_MODEL\_COREDEVICES\_CT2](/docs/c/Foundation/WatchInfo/#WATCH_INFO_MODEL_COREDEVICES_CT2) |
| 

CoreDevices CT2 (Core Time 2)

 |
| c | [WatchInfoColor](/docs/c/Foundation/WatchInfo/#WatchInfoColor) |
| 

The different watch colors.

 |
| c | [WATCH\_INFO\_COLOR\_UNKNOWN](/docs/c/Foundation/WatchInfo/#WATCH_INFO_COLOR_UNKNOWN) |
| 

Unknown color.

 |
| c | [WATCH\_INFO\_COLOR\_BLACK](/docs/c/Foundation/WatchInfo/#WATCH_INFO_COLOR_BLACK) |
| 

Black.

 |
| c | [WATCH\_INFO\_COLOR\_WHITE](/docs/c/Foundation/WatchInfo/#WATCH_INFO_COLOR_WHITE) |
| 

White.

 |
| c | [WATCH\_INFO\_COLOR\_RED](/docs/c/Foundation/WatchInfo/#WATCH_INFO_COLOR_RED) |
| 

Red.

 |
| c | [WATCH\_INFO\_COLOR\_ORANGE](/docs/c/Foundation/WatchInfo/#WATCH_INFO_COLOR_ORANGE) |
| 

Orange.

 |
| c | [WATCH\_INFO\_COLOR\_GRAY](/docs/c/Foundation/WatchInfo/#WATCH_INFO_COLOR_GRAY) |
| 

Gray.

 |
| c | [WATCH\_INFO\_COLOR\_STAINLESS\_STEEL](/docs/c/Foundation/WatchInfo/#WATCH_INFO_COLOR_STAINLESS_STEEL) |
| 

Stainless Steel.

 |
| c | [WATCH\_INFO\_COLOR\_MATTE\_BLACK](/docs/c/Foundation/WatchInfo/#WATCH_INFO_COLOR_MATTE_BLACK) |
| 

Matte Black.

 |
| c | [WATCH\_INFO\_COLOR\_BLUE](/docs/c/Foundation/WatchInfo/#WATCH_INFO_COLOR_BLUE) |
| 

Blue.

 |
| c | [WATCH\_INFO\_COLOR\_GREEN](/docs/c/Foundation/WatchInfo/#WATCH_INFO_COLOR_GREEN) |
| 

Green.

 |
| c | [WATCH\_INFO\_COLOR\_PINK](/docs/c/Foundation/WatchInfo/#WATCH_INFO_COLOR_PINK) |
| 

Pink.

 |
| c | [WATCH\_INFO\_COLOR\_TIME\_WHITE](/docs/c/Foundation/WatchInfo/#WATCH_INFO_COLOR_TIME_WHITE) |
| 

Time White.

 |
| c | [WATCH\_INFO\_COLOR\_TIME\_BLACK](/docs/c/Foundation/WatchInfo/#WATCH_INFO_COLOR_TIME_BLACK) |
| 

Time Black.

 |
| c | [WATCH\_INFO\_COLOR\_TIME\_RED](/docs/c/Foundation/WatchInfo/#WATCH_INFO_COLOR_TIME_RED) |
| 

Time Red.

 |
| c | [WATCH\_INFO\_COLOR\_TIME\_STEEL\_SILVER](/docs/c/Foundation/WatchInfo/#WATCH_INFO_COLOR_TIME_STEEL_SILVER) |
| 

Time Steel Silver.

 |
| c | [WATCH\_INFO\_COLOR\_TIME\_STEEL\_BLACK](/docs/c/Foundation/WatchInfo/#WATCH_INFO_COLOR_TIME_STEEL_BLACK) |
| 

Time Steel Black.

 |
| c | [WATCH\_INFO\_COLOR\_TIME\_STEEL\_GOLD](/docs/c/Foundation/WatchInfo/#WATCH_INFO_COLOR_TIME_STEEL_GOLD) |
| 

Time Steel Gold.

 |
| c | [WATCH\_INFO\_COLOR\_TIME\_ROUND\_SILVER\_14](/docs/c/Foundation/WatchInfo/#WATCH_INFO_COLOR_TIME_ROUND_SILVER_14) |
| 

Time Round 14mm lug size, Silver.

 |
| c | [WATCH\_INFO\_COLOR\_TIME\_ROUND\_BLACK\_14](/docs/c/Foundation/WatchInfo/#WATCH_INFO_COLOR_TIME_ROUND_BLACK_14) |
| 

Time Round 14mm lug size, Black.

 |
| c | [WATCH\_INFO\_COLOR\_TIME\_ROUND\_SILVER\_20](/docs/c/Foundation/WatchInfo/#WATCH_INFO_COLOR_TIME_ROUND_SILVER_20) |
| 

Time Round 20mm lug size, Silver.

 |
| c | [WATCH\_INFO\_COLOR\_TIME\_ROUND\_BLACK\_20](/docs/c/Foundation/WatchInfo/#WATCH_INFO_COLOR_TIME_ROUND_BLACK_20) |
| 

Time Round 20mm lug size, Black.

 |
| c | [WATCH\_INFO\_COLOR\_TIME\_ROUND\_ROSE\_GOLD\_14](/docs/c/Foundation/WatchInfo/#WATCH_INFO_COLOR_TIME_ROUND_ROSE_GOLD_14) |
| 

Time Round 14mm lug size, Rose Gold.

 |
| c | [WATCH\_INFO\_COLOR\_PEBBLE\_2\_HR\_BLACK](/docs/c/Foundation/WatchInfo/#WATCH_INFO_COLOR_PEBBLE_2_HR_BLACK) |
| 

Pebble 2 HR, Black / Charcoal.

 |
| c | [WATCH\_INFO\_COLOR\_PEBBLE\_2\_HR\_LIME](/docs/c/Foundation/WatchInfo/#WATCH_INFO_COLOR_PEBBLE_2_HR_LIME) |
| 

Pebble 2 HR, Charcoal / Sorbet Green.

 |
| c | [WATCH\_INFO\_COLOR\_PEBBLE\_2\_HR\_FLAME](/docs/c/Foundation/WatchInfo/#WATCH_INFO_COLOR_PEBBLE_2_HR_FLAME) |
| 

Pebble 2 HR, Charcoal / Red.

 |
| c | [WATCH\_INFO\_COLOR\_PEBBLE\_2\_HR\_WHITE](/docs/c/Foundation/WatchInfo/#WATCH_INFO_COLOR_PEBBLE_2_HR_WHITE) |
| 

Pebble 2 HR, White / Gray.

 |
| c | [WATCH\_INFO\_COLOR\_PEBBLE\_2\_HR\_AQUA](/docs/c/Foundation/WatchInfo/#WATCH_INFO_COLOR_PEBBLE_2_HR_AQUA) |
| 

Pebble 2 HR, White / Turquoise.

 |
| c | [WATCH\_INFO\_COLOR\_PEBBLE\_2\_SE\_BLACK](/docs/c/Foundation/WatchInfo/#WATCH_INFO_COLOR_PEBBLE_2_SE_BLACK) |
| 

Pebble 2 SE, Black / Charcoal.

 |
| c | [WATCH\_INFO\_COLOR\_PEBBLE\_2\_SE\_WHITE](/docs/c/Foundation/WatchInfo/#WATCH_INFO_COLOR_PEBBLE_2_SE_WHITE) |
| 

Pebble 2 SE, White / Gray.

 |
| c | [WATCH\_INFO\_COLOR\_PEBBLE\_TIME\_2\_BLACK](/docs/c/Foundation/WatchInfo/#WATCH_INFO_COLOR_PEBBLE_TIME_2_BLACK) |
| 

Pebble Time 2, Black.

 |
| c | [WATCH\_INFO\_COLOR\_PEBBLE\_TIME\_2\_SILVER](/docs/c/Foundation/WatchInfo/#WATCH_INFO_COLOR_PEBBLE_TIME_2_SILVER) |
| 

Pebble Time 2, Silver.

 |
| c | [WATCH\_INFO\_COLOR\_PEBBLE\_TIME\_2\_GOLD](/docs/c/Foundation/WatchInfo/#WATCH_INFO_COLOR_PEBBLE_TIME_2_GOLD) |
| 

Pebble Time 2, Gold.

 |
| c | [WATCH\_INFO\_COLOR\_COREDEVICES\_P2D\_BLACK](/docs/c/Foundation/WatchInfo/#WATCH_INFO_COLOR_COREDEVICES_P2D_BLACK) |
| 

CoreDevices P2D, Black.

 |
| c | [WATCH\_INFO\_COLOR\_COREDEVICES\_P2D\_WHITE](/docs/c/Foundation/WatchInfo/#WATCH_INFO_COLOR_COREDEVICES_P2D_WHITE) |
| 

CoreDevices P2D, White.

 |
| c | [WATCH\_INFO\_COLOR\_COREDEVICES\_PT2\_BLACK\_GREY](/docs/c/Foundation/WatchInfo/#WATCH_INFO_COLOR_COREDEVICES_PT2_BLACK_GREY) |
| 

CoreDevices PT2, Black/Grey.

 |
| c | [WATCH\_INFO\_COLOR\_COREDEVICES\_PT2\_BLACK\_RED](/docs/c/Foundation/WatchInfo/#WATCH_INFO_COLOR_COREDEVICES_PT2_BLACK_RED) |
| 

CoreDevices PT2, Black/Red.

 |
| c | [WATCH\_INFO\_COLOR\_COREDEVICES\_PT2\_SILVER\_BLUE](/docs/c/Foundation/WatchInfo/#WATCH_INFO_COLOR_COREDEVICES_PT2_SILVER_BLUE) |
| 

CoreDevices PT2, Silver/Blue.

 |
| c | [WATCH\_INFO\_COLOR\_COREDEVICES\_PT2\_SILVER\_GREY](/docs/c/Foundation/WatchInfo/#WATCH_INFO_COLOR_COREDEVICES_PT2_SILVER_GREY) |
| 

CoreDevices PT2, Silver/Grey.

 |
| c | [WATCH\_INFO\_COLOR\_COREDEVICES\_PR2\_BLACK\_20](/docs/c/Foundation/WatchInfo/#WATCH_INFO_COLOR_COREDEVICES_PR2_BLACK_20) |
| 

CoreDevices PR2, Black (20mm)

 |
| c | [WATCH\_INFO\_COLOR\_COREDEVICES\_PR2\_SILVER\_20](/docs/c/Foundation/WatchInfo/#WATCH_INFO_COLOR_COREDEVICES_PR2_SILVER_20) |
| 

CoreDevices PR2, Silver (20mm)

 |
| c | [WATCH\_INFO\_COLOR\_COREDEVICES\_PR2\_GOLD\_14](/docs/c/Foundation/WatchInfo/#WATCH_INFO_COLOR_COREDEVICES_PR2_GOLD_14) |
| 

CoreDevices PR2, Gold (14mm)

 |
| c | [WATCH\_INFO\_COLOR\_COREDEVICES\_PR2\_SILVER\_14](/docs/c/Foundation/WatchInfo/#WATCH_INFO_COLOR_COREDEVICES_PR2_SILVER_14) |
| 

CoreDevices PR2, Silver (14mm)

 |
| c | [WATCH\_INFO\_COLOR\_\_MAX](/docs/c/Foundation/WatchInfo/#WATCH_INFO_COLOR__MAX) |
| |
| c | [WATCH\_INFO\_COLOR\_COREDEVICES\_CT2\_BLACK](/docs/c/Foundation/WatchInfo/#WATCH_INFO_COLOR_COREDEVICES_CT2_BLACK) |
| 

CoreDevices CT2, Black.

 |
| c | [WATCH\_INFO\_COLOR\_COREDEVICES\_C2D\_WHITE](/docs/c/Foundation/WatchInfo/#WATCH_INFO_COLOR_COREDEVICES_C2D_WHITE) |
| 

CoreDevices C2D, White.

 |
| c | [WATCH\_INFO\_COLOR\_COREDEVICES\_C2D\_BLACK](/docs/c/Foundation/WatchInfo/#WATCH_INFO_COLOR_COREDEVICES_C2D_BLACK) |
| 

CoreDevices C2D, Black.

 |
| c | [watch\_info\_get\_model](/docs/c/Foundation/WatchInfo/#watch_info_get_model) |
| 

Provides the model of the watch.

 |
| c | [watch\_info\_get\_firmware\_version](/docs/c/Foundation/WatchInfo/#watch_info_get_firmware_version) |
| 

Provides the version of the firmware running on the watch.

 |
| c | [watch\_info\_get\_color](/docs/c/Foundation/WatchInfo/#watch_info_get_color) |
| |
| c | [WatchInfoVersion](/docs/c/Foundation/WatchInfo/#WatchInfoVersion) |
| 

Data structure containing the version of the firmware running on the watch. The version of the firmware has the form X.[X.[X]]. If a version number is not present it will be 0. For example: the version numbers of 2.4.1 are 2, 4, and 1. The version numbers of 2.4 are 2, 4, and 0.

 |
| c | [Graphics](/docs/c/Graphics/) |
| 

Low-level drawing routines.

 |
| c | [Draw Commands](/docs/c/Graphics/Draw_Commands/) |
| 

Pebble Draw Commands are a way to encode arbitrary path draw and fill calls in binary format, so that vector-like graphics can be represented on the watch.

 |
| c | [GDrawCommand](/docs/c/Graphics/Draw_Commands/#GDrawCommand) |
| 

Draw commands are the basic building block of the draw command system, encoding the type of command to draw, the stroke width and color, fill color, and points that define the path (or center of a circle.

 |
| c | [GDrawCommandFrame](/docs/c/Graphics/Draw_Commands/#GDrawCommandFrame) |
| 

Draw command frames contain a list of commands to draw for that frame and a duration, indicating the length of time for which the frame should be drawn in an animation sequence. Frames form the building blocks of a [GDrawCommandSequence](/docs/c/Graphics/Draw_Commands/#GDrawCommandSequence), which consists of multiple frames.

 |
| c | [GDrawCommandImage](/docs/c/Graphics/Draw_Commands/#GDrawCommandImage) |
| 

Draw command images contain a list of commands that can be drawn. An image can be loaded from PDC file data.

 |
| c | [GDrawCommandList](/docs/c/Graphics/Draw_Commands/#GDrawCommandList) |
| 

Draw command lists contain a list of commands that can be iterated over and drawn all at once.

 |
| c | [GDrawCommandListIteratorCb](/docs/c/Graphics/Draw_Commands/#GDrawCommandListIteratorCb) |
| 

Callback for iterating over draw command list.

 |
| c | [GDrawCommandSequence](/docs/c/Graphics/Draw_Commands/#GDrawCommandSequence) |
| 

Draw command sequences allow the animation of frames over time. Each sequence has a list of frames that can be accessed by the elapsed duration of the animation (not maintained internally) or by index. Sequences can be loaded from PDC file data.

 |
| c | [GDrawCommandType](/docs/c/Graphics/Draw_Commands/#GDrawCommandType) |
| |
| c | [GDrawCommandTypeInvalid](/docs/c/Graphics/Draw_Commands/#GDrawCommandTypeInvalid) |
| 

Invalid draw command type.

 |
| c | [GDrawCommandTypePath](/docs/c/Graphics/Draw_Commands/#GDrawCommandTypePath) |
| 

Arbitrary path draw command type.

 |
| c | [GDrawCommandTypeCircle](/docs/c/Graphics/Draw_Commands/#GDrawCommandTypeCircle) |
| 

Circle draw command type.

 |
| c | [GDrawCommandTypePrecisePath](/docs/c/Graphics/Draw_Commands/#GDrawCommandTypePrecisePath) |
| 

Arbitrary path drawn with sub-pixel precision (1/8th precision)

 |
| c | [gdraw\_command\_draw](/docs/c/Graphics/Draw_Commands/#gdraw_command_draw) |
| 

Draw a command.

 |
| c | [gdraw\_command\_get\_type](/docs/c/Graphics/Draw_Commands/#gdraw_command_get_type) |
| 

Get the command type.

 |
| c | [gdraw\_command\_set\_fill\_color](/docs/c/Graphics/Draw_Commands/#gdraw_command_set_fill_color) |
| 

Set the fill color of a command.

 |
| c | [gdraw\_command\_get\_fill\_color](/docs/c/Graphics/Draw_Commands/#gdraw_command_get_fill_color) |
| 

Get the fill color of a command.

 |
| c | [gdraw\_command\_set\_stroke\_color](/docs/c/Graphics/Draw_Commands/#gdraw_command_set_stroke_color) |
| 

Set the stroke color of a command.

 |
| c | [gdraw\_command\_get\_stroke\_color](/docs/c/Graphics/Draw_Commands/#gdraw_command_get_stroke_color) |
| 

Get the stroke color of a command.

 |
| c | [gdraw\_command\_set\_stroke\_width](/docs/c/Graphics/Draw_Commands/#gdraw_command_set_stroke_width) |
| 

Set the stroke width of a command.

 |
| c | [gdraw\_command\_get\_stroke\_width](/docs/c/Graphics/Draw_Commands/#gdraw_command_get_stroke_width) |
| 

Get the stroke width of a command.

 |
| c | [gdraw\_command\_get\_num\_points](/docs/c/Graphics/Draw_Commands/#gdraw_command_get_num_points) |
| 

Get the number of points in a command.

 |
| c | [gdraw\_command\_set\_point](/docs/c/Graphics/Draw_Commands/#gdraw_command_set_point) |
| 

Set the value of the point in a command at the specified index.

 |
| c | [gdraw\_command\_get\_point](/docs/c/Graphics/Draw_Commands/#gdraw_command_get_point) |
| 

Get the value of a point in a command from the specified index.

 |
| c | [gdraw\_command\_set\_radius](/docs/c/Graphics/Draw_Commands/#gdraw_command_set_radius) |
| 

Set the radius of a circle command.

 |
| c | [gdraw\_command\_get\_radius](/docs/c/Graphics/Draw_Commands/#gdraw_command_get_radius) |
| 

Get the radius of a circle command.

 |
| c | [gdraw\_command\_set\_path\_open](/docs/c/Graphics/Draw_Commands/#gdraw_command_set_path_open) |
| 

Set the path of a stroke command to be open.

 |
| c | [gdraw\_command\_get\_path\_open](/docs/c/Graphics/Draw_Commands/#gdraw_command_get_path_open) |
| 

Return whether a stroke command path is open.

 |
| c | [gdraw\_command\_set\_hidden](/docs/c/Graphics/Draw_Commands/#gdraw_command_set_hidden) |
| 

Set a command as hidden. This command will not be drawn when [gdraw\_command\_draw](/docs/c/Graphics/Draw_Commands/#gdraw_command_draw) is called with this command.

 |
| c | [gdraw\_command\_get\_hidden](/docs/c/Graphics/Draw_Commands/#gdraw_command_get_hidden) |
| 

Return whether a command is hidden.

 |
| c | [gdraw\_command\_frame\_draw](/docs/c/Graphics/Draw_Commands/#gdraw_command_frame_draw) |
| 

Draw a frame.

 |
| c | [gdraw\_command\_frame\_set\_duration](/docs/c/Graphics/Draw_Commands/#gdraw_command_frame_set_duration) |
| 

Set the duration of the frame.

 |
| c | [gdraw\_command\_frame\_get\_duration](/docs/c/Graphics/Draw_Commands/#gdraw_command_frame_get_duration) |
| 

Get the duration of the frame.

 |
| c | [gdraw\_command\_image\_create\_with\_resource](/docs/c/Graphics/Draw_Commands/#gdraw_command_image_create_with_resource) |
| 

Creates a [GDrawCommandImage](/docs/c/Graphics/Draw_Commands/#GDrawCommandImage) from the specified resource (PDC file)

 |
| c | [gdraw\_command\_image\_clone](/docs/c/Graphics/Draw_Commands/#gdraw_command_image_clone) |
| 

Creates a [GDrawCommandImage](/docs/c/Graphics/Draw_Commands/#GDrawCommandImage) as a copy from a given image.

 |
| c | [gdraw\_command\_image\_destroy](/docs/c/Graphics/Draw_Commands/#gdraw_command_image_destroy) |
| 

Deletes the [GDrawCommandImage](/docs/c/Graphics/Draw_Commands/#GDrawCommandImage) structure and frees associated data.

 |
| c | [gdraw\_command\_image\_draw](/docs/c/Graphics/Draw_Commands/#gdraw_command_image_draw) |
| 

Draw an image.

 |
| c | [gdraw\_command\_image\_get\_bounds\_size](/docs/c/Graphics/Draw_Commands/#gdraw_command_image_get_bounds_size) |
| 

Get size of the bounding box surrounding all draw commands in the image. This bounding box can be used to set the graphics context or layer bounds when drawing the image.

 |
| c | [gdraw\_command\_image\_set\_bounds\_size](/docs/c/Graphics/Draw_Commands/#gdraw_command_image_set_bounds_size) |
| 

Set size of the bounding box surrounding all draw commands in the image. This bounding box can be used to set the graphics context or layer bounds when drawing the image.

 |
| c | [gdraw\_command\_image\_get\_command\_list](/docs/c/Graphics/Draw_Commands/#gdraw_command_image_get_command_list) |
| 

Get the command list of the image.

 |
| c | [gdraw\_command\_list\_iterate](/docs/c/Graphics/Draw_Commands/#gdraw_command_list_iterate) |
| 

Iterate over all commands in a command list.

 |
| c | [gdraw\_command\_list\_draw](/docs/c/Graphics/Draw_Commands/#gdraw_command_list_draw) |
| 

Draw all commands in a command list.

 |
| c | [gdraw\_command\_list\_get\_command](/docs/c/Graphics/Draw_Commands/#gdraw_command_list_get_command) |
| 

Get the command at the specified index.

 |
| c | [gdraw\_command\_list\_get\_num\_commands](/docs/c/Graphics/Draw_Commands/#gdraw_command_list_get_num_commands) |
| 

Get the number of commands in the list.

 |
| c | [gdraw\_command\_sequence\_create\_with\_resource](/docs/c/Graphics/Draw_Commands/#gdraw_command_sequence_create_with_resource) |
| 

Creates a [GDrawCommandSequence](/docs/c/Graphics/Draw_Commands/#GDrawCommandSequence) from the specified resource (PDC file)

 |
| c | [gdraw\_command\_sequence\_clone](/docs/c/Graphics/Draw_Commands/#gdraw_command_sequence_clone) |
| 

Creates a [GDrawCommandSequence](/docs/c/Graphics/Draw_Commands/#GDrawCommandSequence) as a copy from a given sequence.

 |
| c | [gdraw\_command\_sequence\_destroy](/docs/c/Graphics/Draw_Commands/#gdraw_command_sequence_destroy) |
| 

Deletes the [GDrawCommandSequence](/docs/c/Graphics/Draw_Commands/#GDrawCommandSequence) structure and frees associated data.

 |
| c | [gdraw\_command\_sequence\_get\_frame\_by\_elapsed](/docs/c/Graphics/Draw_Commands/#gdraw_command_sequence_get_frame_by_elapsed) |
| 

Get the frame that should be shown after the specified amount of elapsed time The last frame will be returned if the elapsed time exceeds the total time.

 |
| c | [gdraw\_command\_sequence\_get\_frame\_by\_index](/docs/c/Graphics/Draw_Commands/#gdraw_command_sequence_get_frame_by_index) |
| 

Get the frame at the specified index.

 |
| c | [gdraw\_command\_sequence\_get\_bounds\_size](/docs/c/Graphics/Draw_Commands/#gdraw_command_sequence_get_bounds_size) |
| 

Get the size of the bounding box surrounding all draw commands in the sequence. This bounding box can be used to set the graphics context or layer bounds when drawing the frames in the sequence.

 |
| c | [gdraw\_command\_sequence\_set\_bounds\_size](/docs/c/Graphics/Draw_Commands/#gdraw_command_sequence_set_bounds_size) |
| 

Set size of the bounding box surrounding all draw commands in the sequence. This bounding box can be used to set the graphics context or layer bounds when drawing the frames in the sequence.

 |
| c | [gdraw\_command\_sequence\_get\_play\_count](/docs/c/Graphics/Draw_Commands/#gdraw_command_sequence_get_play_count) |
| 

Get the play count of the sequence.

 |
| c | [gdraw\_command\_sequence\_set\_play\_count](/docs/c/Graphics/Draw_Commands/#gdraw_command_sequence_set_play_count) |
| 

Set the play count of the sequence.

 |
| c | [gdraw\_command\_sequence\_get\_total\_duration](/docs/c/Graphics/Draw_Commands/#gdraw_command_sequence_get_total_duration) |
| 

Get the total duration of the sequence.

 |
| c | [gdraw\_command\_sequence\_get\_num\_frames](/docs/c/Graphics/Draw_Commands/#gdraw_command_sequence_get_num_frames) |
| 

Get the number of frames in the sequence.

 |
| c | [gdraw\_command\_frame\_get\_command\_list](/docs/c/Graphics/Draw_Commands/#gdraw_command_frame_get_command_list) |
| 

Get the command list of the frame.

 |
| c | [Drawing Paths](/docs/c/Graphics/Drawing_Paths/) |
| 

Functions to draw polygons into a graphics context

 |
| c | [gpath\_create](/docs/c/Graphics/Drawing_Paths/#gpath_create) |
| 

Creates a new [GPath](/docs/c/Graphics/Drawing_Paths/#GPath) on the heap based on a series of points described by a [GPathInfo](/docs/c/Graphics/Drawing_Paths/#GPathInfo).

 |
| c | [gpath\_destroy](/docs/c/Graphics/Drawing_Paths/#gpath_destroy) |
| 

Free a dynamically allocated gpath created with [gpath\_create()](/docs/c/Graphics/Drawing_Paths/#gpath_create)

 |
| c | [gpath\_draw\_filled](/docs/c/Graphics/Drawing_Paths/#gpath_draw_filled) |
| 

Draws the fill of a path into a graphics context, using the current fill color, relative to the drawing area as set up by the layering system.

 |
| c | [gpath\_draw\_outline](/docs/c/Graphics/Drawing_Paths/#gpath_draw_outline) |
| 

Draws the outline of a path into a graphics context, using the current stroke color and width, relative to the drawing area as set up by the layering system. The first and last points in the path do have a line between them.

 |
| c | [gpath\_rotate\_to](/docs/c/Graphics/Drawing_Paths/#gpath_rotate_to) |
| 

Sets the absolute rotation of the path. The current rotation will be replaced by the specified angle.

 |
| c | [gpath\_move\_to](/docs/c/Graphics/Drawing_Paths/#gpath_move_to) |
| 

Sets the absolute offset of the path. The current translation will be replaced by the specified offset.

 |
| c | [gpath\_draw\_outline\_open](/docs/c/Graphics/Drawing_Paths/#gpath_draw_outline_open) |
| 

Draws an open outline of a path into a graphics context, using the current stroke color and width, relative to the drawing area as set up by the layering system. The first and last points in the path do not have a line between them.

 |
| c | [GPath](/docs/c/Graphics/Drawing_Paths/#GPath) |
| 

Data structure describing a path, plus its rotation and translation.

 |
| c | [GPathInfo](/docs/c/Graphics/Drawing_Paths/#GPathInfo) |
| 

Data structure describing a naked path.

 |
| c | [Drawing Primitives](/docs/c/Graphics/Drawing_Primitives/) |
| 

Functions to draw into a graphics context

 |
| c | [GCornerMask](/docs/c/Graphics/Drawing_Primitives/#GCornerMask) |
| 

Bit mask values to specify the corners of a rectangle. The values can be combines using binary OR (`|`), For example: the mask to indicate top left and bottom right corners can: be created as follows: `(GCornerTopLeft | GCornerBottomRight)`

 |
| c | [GCornerNone](/docs/c/Graphics/Drawing_Primitives/#GCornerNone) |
| 

No corners.

 |
| c | [GCornerTopLeft](/docs/c/Graphics/Drawing_Primitives/#GCornerTopLeft) |
| 

Top-Left corner.

 |
| c | [GCornerTopRight](/docs/c/Graphics/Drawing_Primitives/#GCornerTopRight) |
| 

Top-Right corner.

 |
| c | [GCornerBottomLeft](/docs/c/Graphics/Drawing_Primitives/#GCornerBottomLeft) |
| 

Bottom-Left corner.

 |
| c | [GCornerBottomRight](/docs/c/Graphics/Drawing_Primitives/#GCornerBottomRight) |
| 

Bottom-Right corner.

 |
| c | [GCornersAll](/docs/c/Graphics/Drawing_Primitives/#GCornersAll) |
| 

All corners.

 |
| c | [GCornersTop](/docs/c/Graphics/Drawing_Primitives/#GCornersTop) |
| 

Top corners.

 |
| c | [GCornersBottom](/docs/c/Graphics/Drawing_Primitives/#GCornersBottom) |
| 

Bottom corners.

 |
| c | [GCornersLeft](/docs/c/Graphics/Drawing_Primitives/#GCornersLeft) |
| 

Left corners.

 |
| c | [GCornersRight](/docs/c/Graphics/Drawing_Primitives/#GCornersRight) |
| 

Right corners.

 |
| c | [graphics\_draw\_pixel](/docs/c/Graphics/Drawing_Primitives/#graphics_draw_pixel) |
| 

Draws a pixel at given point in the current stroke color.

 |
| c | [graphics\_draw\_line](/docs/c/Graphics/Drawing_Primitives/#graphics_draw_line) |
| 

Draws line in the current stroke color, current stroke width and AA flag.

 |
| c | [graphics\_draw\_rect](/docs/c/Graphics/Drawing_Primitives/#graphics_draw_rect) |
| 

Draws a 1-pixel wide rectangle outline in the current stroke color.

 |
| c | [graphics\_fill\_rect](/docs/c/Graphics/Drawing_Primitives/#graphics_fill_rect) |
| 

Fills a rectangle with the current fill color, optionally rounding all or a selection of its corners.

 |
| c | [graphics\_draw\_circle](/docs/c/Graphics/Drawing_Primitives/#graphics_draw_circle) |
| 

Draws the outline of a circle in the current stroke color.

 |
| c | [graphics\_fill\_circle](/docs/c/Graphics/Drawing_Primitives/#graphics_fill_circle) |
| 

Fills a circle in the current fill color.

 |
| c | [graphics\_draw\_round\_rect](/docs/c/Graphics/Drawing_Primitives/#graphics_draw_round_rect) |
| 

Draws the outline of a rounded rectangle in the current stroke color.

 |
| c | [graphics\_draw\_bitmap\_in\_rect](/docs/c/Graphics/Drawing_Primitives/#graphics_draw_bitmap_in_rect) |
| 

Draws a bitmap into the graphics context, inside the specified rectangle.

 |
| c | [graphics\_capture\_frame\_buffer](/docs/c/Graphics/Drawing_Primitives/#graphics_capture_frame_buffer) |
| 

A shortcut to capture the framebuffer in the native format of the watch.

 |
| c | [graphics\_capture\_frame\_buffer\_format](/docs/c/Graphics/Drawing_Primitives/#graphics_capture_frame_buffer_format) |
| 

Captures the frame buffer for direct access, using the given format. Graphics functions will not affect the frame buffer while it is captured. The frame buffer is released when `graphics_release_frame_buffer` is called. The frame buffer must be released before the end of a layer's `.update_proc` for the layer to be drawn properly.

 |
| c | [graphics\_release\_frame\_buffer](/docs/c/Graphics/Drawing_Primitives/#graphics_release_frame_buffer) |
| 

Releases the frame buffer. Must be called before the end of a layer's `.update_proc` for the layer to be drawn properly.

 |
| c | [graphics\_frame\_buffer\_is\_captured](/docs/c/Graphics/Drawing_Primitives/#graphics_frame_buffer_is_captured) |
| 

Whether or not the frame buffer has been captured by `graphics_capture_frame_buffer`. Graphics functions will not affect the frame buffer until it has been released by `graphics_release_frame_buffer`.

 |
| c | [graphics\_draw\_rotated\_bitmap](/docs/c/Graphics/Drawing_Primitives/#graphics_draw_rotated_bitmap) |
| 

Draws a rotated bitmap with a memory-sensitive 2x anti-aliasing technique (using ray-finding instead of super-sampling), which is thresholded into a b/w bitmap for 1-bit and color blended for 8-bit.

 |
| c | [GOvalScaleMode](/docs/c/Graphics/Drawing_Primitives/#GOvalScaleMode) |
| 

Values to specify how a given rectangle should be used to derive an oval shape.

 |
| c | [GOvalScaleModeFitCircle](/docs/c/Graphics/Drawing_Primitives/#GOvalScaleModeFitCircle) |
| 

Places a circle at the center of the rectangle, with a diameter that matches the rectangle's shortest side.

 |
| c | [GOvalScaleModeFillCircle](/docs/c/Graphics/Drawing_Primitives/#GOvalScaleModeFillCircle) |
| 

Places a circle at the center of the rectangle, with a diameter that matches the rectangle's longest side. The circle may overflow the bounds of the rectangle.

 |
| c | [graphics\_draw\_arc](/docs/c/Graphics/Drawing_Primitives/#graphics_draw_arc) |
| 

Draws a line arc clockwise between `angle_start` and `angle_end`, where 0° is the top of the circle. If the difference between `angle_start` and `angle_end` is greater than 360°, a full circle will be drawn.

 |
| c | [graphics\_fill\_radial](/docs/c/Graphics/Drawing_Primitives/#graphics_fill_radial) |
| 

Fills a circle clockwise between `angle_start` and `angle_end`, where 0° is the top of the circle. If the difference between `angle_start` and `angle_end` is greater than 360°, a full circle will be drawn and filled. If `angle_start` is greater than `angle_end` nothing will be drawn.

 |
| c | [gpoint\_from\_polar](/docs/c/Graphics/Drawing_Primitives/#gpoint_from_polar) |
| 

Calculates a [GPoint](/docs/c/Graphics/Graphics_Types/#GPoint) located at the angle provided on the perimeter of a circle defined by the provided [GRect](/docs/c/Graphics/Graphics_Types/#GRect).

 |
| c | [grect\_centered\_from\_polar](/docs/c/Graphics/Drawing_Primitives/#grect_centered_from_polar) |
| 

Calculates a rectangle centered on the perimeter of a circle at a given angle. Use this to construct rectangles that follow the perimeter of a circle as an input for graphics\_fill\_radial\_internal or graphics\_draw\_arc\_internal, e.g. to draw circles every 30 degrees on a watchface.

 |
| c | [Drawing Text](/docs/c/Graphics/Drawing_Text/) |
| 

Functions to draw text into a graphics context

 |
| c | [GTextOverflowMode](/docs/c/Graphics/Drawing_Text/#GTextOverflowMode) |
| 

Text overflow mode controls the way text overflows when the string that is drawn does not fit inside the area constraint.

 |
| c | [GTextOverflowModeWordWrap](/docs/c/Graphics/Drawing_Text/#GTextOverflowModeWordWrap) |
| 

On overflow, wrap words to a new line below the current one. Once vertical space is consumed, the last line may be clipped.

 |
| c | [GTextOverflowModeTrailingEllipsis](/docs/c/Graphics/Drawing_Text/#GTextOverflowModeTrailingEllipsis) |
| 

On overflow, wrap words to a new line below the current one. Once vertical space is consumed, truncate as needed to fit a trailing ellipsis (...). Clipping may occur if the vertical space cannot accomodate the first line of text.

 |
| c | [GTextOverflowModeFill](/docs/c/Graphics/Drawing_Text/#GTextOverflowModeFill) |
| 

Acts like GTextOverflowModeTrailingEllipsis, plus trims leading and trailing newlines, while treating all other newlines as spaces.

 |
| c | [GTextAlignment](/docs/c/Graphics/Drawing_Text/#GTextAlignment) |
| 

Text aligment controls the way the text is aligned inside the box the text is drawn into.

 |
| c | [GTextAlignmentLeft](/docs/c/Graphics/Drawing_Text/#GTextAlignmentLeft) |
| 

Aligns the text to the left of the drawing box.

 |
| c | [GTextAlignmentCenter](/docs/c/Graphics/Drawing_Text/#GTextAlignmentCenter) |
| 

Aligns the text centered inside the drawing box.

 |
| c | [GTextAlignmentRight](/docs/c/Graphics/Drawing_Text/#GTextAlignmentRight) |
| 

Aligns the text to the right of the drawing box.

 |
| c | [GTextAttributes](/docs/c/Graphics/Drawing_Text/#GTextAttributes) |
| |
| c | [graphics\_text\_attributes\_create](/docs/c/Graphics/Drawing_Text/#graphics_text_attributes_create) |
| 

Creates an instance of GTextAttributes for advanced control when rendering text.

 |
| c | [graphics\_text\_attributes\_destroy](/docs/c/Graphics/Drawing_Text/#graphics_text_attributes_destroy) |
| 

Destroys a previously created instance of GTextAttributes.

 |
| c | [graphics\_text\_attributes\_restore\_default\_text\_flow](/docs/c/Graphics/Drawing_Text/#graphics_text_attributes_restore_default_text_flow) |
| 

Restores text flow to the rectangular default.

 |
| c | [graphics\_text\_attributes\_enable\_screen\_text\_flow](/docs/c/Graphics/Drawing_Text/#graphics_text_attributes_enable_screen_text_flow) |
| 

Enables text flow that follows the boundaries of the screen.

 |
| c | [graphics\_text\_attributes\_restore\_default\_paging](/docs/c/Graphics/Drawing_Text/#graphics_text_attributes_restore_default_paging) |
| 

Restores paging and locked content origin to the defaults.

 |
| c | [graphics\_text\_attributes\_enable\_paging](/docs/c/Graphics/Drawing_Text/#graphics_text_attributes_enable_paging) |
| 

Enables paging and locks the text flow calculation to a fixed point on the screen.

 |
| c | [graphics\_draw\_text](/docs/c/Graphics/Drawing_Text/#graphics_draw_text) |
| 

Draw text into the current graphics context, using the context's current text color. The text will be drawn inside a box with the specified dimensions and configuration, with clipping occuring automatically.

 |
| c | [graphics\_text\_layout\_get\_content\_size](/docs/c/Graphics/Drawing_Text/#graphics_text_layout_get_content_size) |
| 

Obtain the maximum size that a text with given font, overflow mode and alignment occupies within a given rectangular constraint.

 |
| c | [graphics\_text\_layout\_get\_content\_size\_with\_attributes](/docs/c/Graphics/Drawing_Text/#graphics_text_layout_get_content_size_with_attributes) |
| 

Obtain the maximum size that a text with given font, overflow mode and alignment occupies within a given rectangular constraint.

 |
| c | [Fonts](/docs/c/Graphics/Fonts/) |
| 

Custom and system fonts.

 |
| c | [FontInfo](/docs/c/Graphics/Fonts/#FontInfo) |
| |
| c | [GFont](/docs/c/Graphics/Fonts/#GFont) |
| 

Pointer to opaque font data structure.

 |
| c | [fonts\_get\_system\_font](/docs/c/Graphics/Fonts/#fonts_get_system_font) |
| 

Loads a system font corresponding to the specified font key.

 |
| c | [fonts\_load\_custom\_font](/docs/c/Graphics/Fonts/#fonts_load_custom_font) |
| 

Loads a custom font.

 |
| c | [fonts\_unload\_custom\_font](/docs/c/Graphics/Fonts/#fonts_unload_custom_font) |
| 

Unloads the specified custom font and frees the memory that is occupied by it.

 |
| c | [Graphics Context](/docs/c/Graphics/Graphics_Context/) |
| 

The "canvas" into which an application draws

 |
| c | [graphics\_context\_set\_stroke\_color](/docs/c/Graphics/Graphics_Context/#graphics_context_set_stroke_color) |
| 

Sets the current stroke color of the graphics context.

 |
| c | [graphics\_context\_set\_fill\_color](/docs/c/Graphics/Graphics_Context/#graphics_context_set_fill_color) |
| 

Sets the current fill color of the graphics context.

 |
| c | [graphics\_context\_set\_text\_color](/docs/c/Graphics/Graphics_Context/#graphics_context_set_text_color) |
| 

Sets the current text color of the graphics context.

 |
| c | [graphics\_context\_set\_compositing\_mode](/docs/c/Graphics/Graphics_Context/#graphics_context_set_compositing_mode) |
| 

Sets the current bitmap compositing mode of the graphics context. The default mode is GCompOpAssign i.e. bitmap transparency disabled.

 |
| c | [graphics\_context\_set\_antialiased](/docs/c/Graphics/Graphics_Context/#graphics_context_set_antialiased) |
| 

Sets whether antialiasing is applied to stroke drawing.

 |
| c | [graphics\_context\_set\_stroke\_width](/docs/c/Graphics/Graphics_Context/#graphics_context_set_stroke_width) |
| 

Sets the width of the stroke for drawing routines.

 |
| c | [Graphics Types](/docs/c/Graphics/Graphics_Types/) |
| 

Basic graphics types (point, rect, size, color, bitmaps, etc.) and utility functions.

 |
| c | [GColorFromRGBA](/docs/c/Graphics/Graphics_Types/#GColorFromRGBA) |
| 

Convert RGBA to GColor.

 |
| c | [GColorFromRGB](/docs/c/Graphics/Graphics_Types/#GColorFromRGB) |
| 

Convert RGB to GColor.

 |
| c | [GColorFromHEX](/docs/c/Graphics/Graphics_Types/#GColorFromHEX) |
| 

Convert hex integer to GColor.

 |
| c | [GColor](/docs/c/Graphics/Graphics_Types/#GColor) |
| |
| c | [gcolor\_equal](/docs/c/Graphics/Graphics_Types/#gcolor_equal) |
| 

True if both colors are identical or both are invisible (i.e. both have alpha values of .a=0).

 |
| c | [gcolor\_legible\_over](/docs/c/Graphics/Graphics_Types/#gcolor_legible_over) |
| 

This method assists in improving the legibility of text on various background colors. It takes the background color for the region in question and computes a color for maximum legibility.

 |
| c | [COLOR\_FALLBACK](/docs/c/Graphics/Graphics_Types/#COLOR_FALLBACK) |
| 

Convenience macro allowing use of a fallback color for black and white platforms. On color platforms, the first expression will be chosen, the second otherwise.

 |
| c | [PBL\_IF\_RECT\_ELSE](/docs/c/Graphics/Graphics_Types/#PBL_IF_RECT_ELSE) |
| 

Convenience macro to switch between two expression depending on the screen of the platform. On platforms with rectangular screen, the first expression will be chosen, the second otherwise.

 |
| c | [PBL\_IF\_ROUND\_ELSE](/docs/c/Graphics/Graphics_Types/#PBL_IF_ROUND_ELSE) |
| 

Convenience macro to switch between two expression depending on the screen of the platform. On platforms with round screen, the first expression will be chosen, the second otherwise.

 |
| c | [PBL\_IF\_BW\_ELSE](/docs/c/Graphics/Graphics_Types/#PBL_IF_BW_ELSE) |
| 

Convenience macro to switch between two expression depending on the screen of the platform. On black& white platforms, the first expression will be chosen, the second otherwise.

 |
| c | [PBL\_IF\_COLOR\_ELSE](/docs/c/Graphics/Graphics_Types/#PBL_IF_COLOR_ELSE) |
| 

Convenience macro to switch between two expression depending on the screen of the platform. On color platforms, the first expression will be chosen, the second otherwise.

 |
| c | [GPoint](/docs/c/Graphics/Graphics_Types/#GPoint) |
| 

Convenience macro to make a [GPoint](/docs/c/Graphics/Graphics_Types/#GPoint).

 |
| c | [GPointZero](/docs/c/Graphics/Graphics_Types/#GPointZero) |
| 

Convenience macro to make a [GPoint](/docs/c/Graphics/Graphics_Types/#GPoint) at (0, 0).

 |
| c | [gpoint\_equal](/docs/c/Graphics/Graphics_Types/#gpoint_equal) |
| 

Tests whether 2 points are equal.

 |
| c | [GSize](/docs/c/Graphics/Graphics_Types/#GSize) |
| 

Convenience macro to make a [GSize](/docs/c/Graphics/Graphics_Types/#GSize).

 |
| c | [GSizeZero](/docs/c/Graphics/Graphics_Types/#GSizeZero) |
| 

Convenience macro to make a [GSize](/docs/c/Graphics/Graphics_Types/#GSize) of (0, 0).

 |
| c | [gsize\_equal](/docs/c/Graphics/Graphics_Types/#gsize_equal) |
| 

Tests whether 2 sizes are equal.

 |
| c | [GRect](/docs/c/Graphics/Graphics_Types/#GRect) |
| 

Convenience macro to make a [GRect](/docs/c/Graphics/Graphics_Types/#GRect).

 |
| c | [GRectZero](/docs/c/Graphics/Graphics_Types/#GRectZero) |
| 

Convenience macro to make a [GRect](/docs/c/Graphics/Graphics_Types/#GRect) of ((0, 0), (0, 0)).

 |
| c | [grect\_equal](/docs/c/Graphics/Graphics_Types/#grect_equal) |
| 

Tests whether 2 rectangles are equal.

 |
| c | [grect\_is\_empty](/docs/c/Graphics/Graphics_Types/#grect_is_empty) |
| 

Tests whether the size of the rectangle is (0, 0).

 |
| c | [grect\_standardize](/docs/c/Graphics/Graphics_Types/#grect_standardize) |
| 

Converts a rectangle's values so that the components of its size (width and/or height) are both positive. In the width and/or height are negative, the origin will offset, so that the final rectangle overlaps with the original. For example, a [GRect](/docs/c/Graphics/Graphics_Types/#GRect) with size (-10, -5) and origin (20, 20), will be standardized to size (10, 5) and origin (10, 15).

 |
| c | [grect\_clip](/docs/c/Graphics/Graphics_Types/#grect_clip) |
| 

Trim one rectangle using the edges of a second rectangle.

 |
| c | [grect\_contains\_point](/docs/c/Graphics/Graphics_Types/#grect_contains_point) |
| 

Tests whether a rectangle contains a point.

 |
| c | [grect\_center\_point](/docs/c/Graphics/Graphics_Types/#grect_center_point) |
| 

Convenience function to compute the center-point of a given rectangle. This is equal to `(rect->x + rect->width / 2, rect->y + rect->height / 2)`.

 |
| c | [grect\_crop](/docs/c/Graphics/Graphics_Types/#grect_crop) |
| 

Reduce the width and height of a rectangle by insetting each of the edges with a fixed inset. The returned rectangle will be centered relative to the input rectangle.

 |
| c | [PLAY\_COUNT\_INFINITE](/docs/c/Graphics/Graphics_Types/#PLAY_COUNT_INFINITE) |
| 

Repeat Sequence or animation indefinitely.

 |
| c | [PLAY\_DURATION\_INFINITE](/docs/c/Graphics/Graphics_Types/#PLAY_DURATION_INFINITE) |
| 

Duration of Sequence or animation is infinite.

 |
| c | [GBitmapFormat](/docs/c/Graphics/Graphics_Types/#GBitmapFormat) |
| 

The format of a GBitmap can either be 1-bit or 8-bit.

 |
| c | [GBitmapFormat1Bit](/docs/c/Graphics/Graphics_Types/#GBitmapFormat1Bit) |
| |
| c | [GBitmapFormat8Bit](/docs/c/Graphics/Graphics_Types/#GBitmapFormat8Bit) |
| |
| c | [GBitmapFormat1BitPalette](/docs/c/Graphics/Graphics_Types/#GBitmapFormat1BitPalette) |
| |
| c | [GBitmapFormat2BitPalette](/docs/c/Graphics/Graphics_Types/#GBitmapFormat2BitPalette) |
| |
| c | [GBitmapFormat4BitPalette](/docs/c/Graphics/Graphics_Types/#GBitmapFormat4BitPalette) |
| |
| c | [GBitmapFormat8BitCircular](/docs/c/Graphics/Graphics_Types/#GBitmapFormat8BitCircular) |
| |
| c | [GBitmap](/docs/c/Graphics/Graphics_Types/#GBitmap) |
| |
| c | [GBitmapSequence](/docs/c/Graphics/Graphics_Types/#GBitmapSequence) |
| |
| c | [gbitmap\_get\_bytes\_per\_row](/docs/c/Graphics/Graphics_Types/#gbitmap_get_bytes_per_row) |
| 

Get the number of bytes per row in the bitmap data for the given GBitmap. On rectangular displays, this can be used as a safe way of iterating over the rows in the bitmap, since bytes per row should be set according to format. On circular displays with pixel format of GBitmapFormat8BitCircular this will return 0, and should not be used for iteration over frame buffer pixels. Instead, use [GBitmapDataRowInfo](/docs/c/Graphics/Graphics_Types/#GBitmapDataRowInfo), which provides safe minimum and maximum x values for a given row's y value.

 |
| c | [gbitmap\_get\_format](/docs/c/Graphics/Graphics_Types/#gbitmap_get_format) |
| 

Get the [GBitmapFormat](/docs/c/Graphics/Graphics_Types/#GBitmapFormat) for the GBitmap.

 |
| c | [gbitmap\_get\_data](/docs/c/Graphics/Graphics_Types/#gbitmap_get_data) |
| 

Get a pointer to the raw image data section of the given GBitmap as specified by the format of the bitmap.

 |
| c | [gbitmap\_set\_data](/docs/c/Graphics/Graphics_Types/#gbitmap_set_data) |
| 

Set the bitmap data for the given GBitmap.

 |
| c | [gbitmap\_get\_bounds](/docs/c/Graphics/Graphics_Types/#gbitmap_get_bounds) |
| 

Gets the bounds of the content for the GBitmap. This is set when loading the image or if changed by [gbitmap\_set\_bounds](/docs/c/Graphics/Graphics_Types/#gbitmap_set_bounds).

 |
| c | [gbitmap\_set\_bounds](/docs/c/Graphics/Graphics_Types/#gbitmap_set_bounds) |
| 

Set the bounds of the given GBitmap.

 |
| c | [gbitmap\_get\_palette](/docs/c/Graphics/Graphics_Types/#gbitmap_get_palette) |
| 

Get the palette for the given GBitmap.

 |
| c | [gbitmap\_set\_palette](/docs/c/Graphics/Graphics_Types/#gbitmap_set_palette) |
| 

Set the palette for the given GBitmap.

 |
| c | [gbitmap\_create\_with\_resource](/docs/c/Graphics/Graphics_Types/#gbitmap_create_with_resource) |
| 

Creates a new GBitmap on the heap using a Pebble image file stored as a resource. The resulting GBitmap must be destroyed using [gbitmap\_destroy()](/docs/c/Graphics/Graphics_Types/#gbitmap_destroy).

 |
| c | [gbitmap\_create\_with\_data](/docs/c/Graphics/Graphics_Types/#gbitmap_create_with_data) |
| 

Creates a new GBitmap on the heap initialized with the provided Pebble image data.

 |
| c | [gbitmap\_create\_as\_sub\_bitmap](/docs/c/Graphics/Graphics_Types/#gbitmap_create_as_sub_bitmap) |
| 

Create a new GBitmap on the heap as a sub-bitmap of a 'base' GBitmap, using a [GRect](/docs/c/Graphics/Graphics_Types/#GRect) to indicate what portion of the base to use. The sub-bitmap will just reference the image data and palette of the base bitmap. No deep-copying occurs as a result of calling this function, thus the caller is responsible for making sure the base bitmap and palette will remain available when using the sub-bitmap. Note that you should not destroy the parent bitmap until the sub\_bitmap has been destroyed. The resulting GBitmap must be destroyed using [gbitmap\_destroy()](/docs/c/Graphics/Graphics_Types/#gbitmap_destroy).

 |
| c | [gbitmap\_create\_from\_png\_data](/docs/c/Graphics/Graphics_Types/#gbitmap_create_from_png_data) |
| 

Create a GBitmap based on raw PNG data. The resulting GBitmap must be destroyed using [gbitmap\_destroy()](/docs/c/Graphics/Graphics_Types/#gbitmap_destroy). The developer is responsible for freeing png\_data following this call.

 |
| c | [gbitmap\_create\_blank](/docs/c/Graphics/Graphics_Types/#gbitmap_create_blank) |
| 

Creates a new blank GBitmap on the heap initialized to zeroes. In the case that the format indicates a palettized bitmap, a palette of appropriate size will also be allocated on the heap. The resulting GBitmap must be destroyed using [gbitmap\_destroy()](/docs/c/Graphics/Graphics_Types/#gbitmap_destroy).

 |
| c | [gbitmap\_create\_blank\_with\_palette](/docs/c/Graphics/Graphics_Types/#gbitmap_create_blank_with_palette) |
| 

Creates a new blank GBitmap on the heap, initialized to zeroes, and assigns it the given palette. No deep-copying of the palette occurs, so the caller is responsible for making sure the palette remains available when using the resulting bitmap. Management of that memory can be handed off to the system with the free\_on\_destroy argument.

 |
| c | [gbitmap\_create\_palettized\_from\_1bit](/docs/c/Graphics/Graphics_Types/#gbitmap_create_palettized_from_1bit) |
| 

Given a 1-bit GBitmap, create a new bitmap of format GBitmapFormat1BitPalette. The new data buffer is allocated on the heap, and a 2-color palette is allocated as well.

 |
| c | [gbitmap\_destroy](/docs/c/Graphics/Graphics_Types/#gbitmap_destroy) |
| 

Destroy a GBitmap. This must be called for every bitmap that's been created with gbitmap\_create\_\*.

 |
| c | [gbitmap\_sequence\_create\_with\_resource](/docs/c/Graphics/Graphics_Types/#gbitmap_sequence_create_with_resource) |
| 

Creates a GBitmapSequence from the specified resource (APNG/PNG files)

 |
| c | [gbitmap\_sequence\_update\_bitmap\_next\_frame](/docs/c/Graphics/Graphics_Types/#gbitmap_sequence_update_bitmap_next_frame) |
| 

Updates the contents of the bitmap sequence to the next frame and optionally returns the delay in milliseconds until the next frame.

 |
| c | [gbitmap\_sequence\_update\_bitmap\_by\_elapsed](/docs/c/Graphics/Graphics_Types/#gbitmap_sequence_update_bitmap_by_elapsed) |
| 

Updates the contents of the bitmap sequence to the frame at elapsed in the sequence. For looping animations this accounts for the loop, for example an animation of 1 second that is configured to loop 2 times updated to 1500 ms elapsed time will display the sequence frame at 500 ms. Elapsed time is the time from the start of the animation, and will be ignored if it is for a time earlier than the last rendered frame.

 |
| c | [gbitmap\_sequence\_destroy](/docs/c/Graphics/Graphics_Types/#gbitmap_sequence_destroy) |
| 

Deletes the GBitmapSequence structure and frees any allocated memory/decoder\_data.

 |
| c | [gbitmap\_sequence\_restart](/docs/c/Graphics/Graphics_Types/#gbitmap_sequence_restart) |
| 

Restarts the GBitmapSequence to the first frame [gbitmap\_sequence\_update\_bitmap\_next\_frame](/docs/c/Graphics/Graphics_Types/#gbitmap_sequence_update_bitmap_next_frame).

 |
| c | [gbitmap\_sequence\_get\_current\_frame\_idx](/docs/c/Graphics/Graphics_Types/#gbitmap_sequence_get_current_frame_idx) |
| 

This function gets the current frame number for the bitmap sequence.

 |
| c | [gbitmap\_sequence\_get\_total\_num\_frames](/docs/c/Graphics/Graphics_Types/#gbitmap_sequence_get_total_num_frames) |
| 

This function sets the total number of frames for the bitmap sequence.

 |
| c | [gbitmap\_sequence\_get\_play\_count](/docs/c/Graphics/Graphics_Types/#gbitmap_sequence_get_play_count) |
| 

This function gets the play count (number of times to repeat) the bitmap sequence.

 |
| c | [gbitmap\_sequence\_set\_play\_count](/docs/c/Graphics/Graphics_Types/#gbitmap_sequence_set_play_count) |
| 

This function sets the play count (number of times to repeat) the bitmap sequence.

 |
| c | [gbitmap\_sequence\_get\_bitmap\_size](/docs/c/Graphics/Graphics_Types/#gbitmap_sequence_get_bitmap_size) |
| 

This function gets the minimum required size (dimensions) necessary to render the bitmap sequence to a GBitmap using the /ref gbitmap\_sequence\_update\_bitmap\_next\_frame.

 |
| c | [gbitmap\_get\_data\_row\_info](/docs/c/Graphics/Graphics_Types/#gbitmap_get_data_row_info) |
| 

Provides information about a pixel data row.

 |
| c | [GAlign](/docs/c/Graphics/Graphics_Types/#GAlign) |
| 

Values to specify how two things should be aligned relative to each other.

 |
| c | [GAlignCenter](/docs/c/Graphics/Graphics_Types/#GAlignCenter) |
| 

Align by centering.

 |
| c | [GAlignTopLeft](/docs/c/Graphics/Graphics_Types/#GAlignTopLeft) |
| 

Align by making the top edges overlap and left edges overlap.

 |
| c | [GAlignTopRight](/docs/c/Graphics/Graphics_Types/#GAlignTopRight) |
| 

Align by making the top edges overlap and left edges overlap.

 |
| c | [GAlignTop](/docs/c/Graphics/Graphics_Types/#GAlignTop) |
| 

Align by making the top edges overlap and centered horizontally.

 |
| c | [GAlignLeft](/docs/c/Graphics/Graphics_Types/#GAlignLeft) |
| 

Align by making the left edges overlap and centered vertically.

 |
| c | [GAlignBottom](/docs/c/Graphics/Graphics_Types/#GAlignBottom) |
| 

Align by making the bottom edges overlap and centered horizontally.

 |
| c | [GAlignRight](/docs/c/Graphics/Graphics_Types/#GAlignRight) |
| 

Align by making the right edges overlap and centered vertically.

 |
| c | [GAlignBottomRight](/docs/c/Graphics/Graphics_Types/#GAlignBottomRight) |
| 

Align by making the bottom edges overlap and right edges overlap.

 |
| c | [GAlignBottomLeft](/docs/c/Graphics/Graphics_Types/#GAlignBottomLeft) |
| 

Align by making the bottom edges overlap and left edges overlap.

 |
| c | [grect\_align](/docs/c/Graphics/Graphics_Types/#grect_align) |
| 

Aligns one rectangle within another rectangle, using an alignment parameter. The relative coordinate systems of both rectangles are assumed to be the same. When clip is true, `rect` is also clipped by the constraint.

 |
| c | [GCompOp](/docs/c/Graphics/Graphics_Types/#GCompOp) |
| 

Values to specify how the source image should be composited onto the destination image.

 |
| c | [GCompOpAssign](/docs/c/Graphics/Graphics_Types/#GCompOpAssign) |
| 

Assign the pixel values of the source image to the destination pixels, effectively replacing the previous values for those pixels. For color displays, when drawing a palettized or 8-bit GBitmap image, the opacity value is ignored.

 |
| c | [GCompOpAssignInverted](/docs/c/Graphics/Graphics_Types/#GCompOpAssignInverted) |
| 

Assign the **inverted** pixel values of the source image to the destination pixels, effectively replacing the previous values for those pixels.

 |
| c | [GCompOpOr](/docs/c/Graphics/Graphics_Types/#GCompOpOr) |
| 

Use the boolean operator `OR` to composite the source and destination pixels. The visual result of this compositing mode is the source's white pixels are painted onto the destination and the source's black pixels are treated as clear.

 |
| c | [GCompOpAnd](/docs/c/Graphics/Graphics_Types/#GCompOpAnd) |
| 

Use the boolean operator `AND` to composite the source and destination pixels. The visual result of this compositing mode is the source's black pixels are painted onto the destination and the source's white pixels are treated as clear.

 |
| c | [GCompOpClear](/docs/c/Graphics/Graphics_Types/#GCompOpClear) |
| 

Clears the bits in the destination image, using the source image as mask. The visual result of this compositing mode is that for the parts where the source image is white, the destination image will be painted black. Other parts will be left untouched.

 |
| c | [GCompOpSet](/docs/c/Graphics/Graphics_Types/#GCompOpSet) |
| 

Sets the bits in the destination image, using the source image as mask. This mode is required to apply any transparency of your bitmap.

 |
| c | [GContext](/docs/c/Graphics/Graphics_Types/#GContext) |
| |
| c | [GEdgeInsets4](/docs/c/Graphics/Graphics_Types/#GEdgeInsets4) |
| 

helper for [GEdgeInsets](/docs/c/Graphics/Graphics_Types/#GEdgeInsets) macro

 |
| c | [GEdgeInsets3](/docs/c/Graphics/Graphics_Types/#GEdgeInsets3) |
| 

helper for [GEdgeInsets](/docs/c/Graphics/Graphics_Types/#GEdgeInsets) macro

 |
| c | [GEdgeInsets2](/docs/c/Graphics/Graphics_Types/#GEdgeInsets2) |
| 

helper for [GEdgeInsets](/docs/c/Graphics/Graphics_Types/#GEdgeInsets) macro

 |
| c | [GEdgeInsets1](/docs/c/Graphics/Graphics_Types/#GEdgeInsets1) |
| 

helper for [GEdgeInsets](/docs/c/Graphics/Graphics_Types/#GEdgeInsets) macro

 |
| c | [GEdgeInsetsN](/docs/c/Graphics/Graphics_Types/#GEdgeInsetsN) |
| 

helper for [GEdgeInsets](/docs/c/Graphics/Graphics_Types/#GEdgeInsets) macro

 |
| c | [GEdgeInsets](/docs/c/Graphics/Graphics_Types/#GEdgeInsets) |
| 

Convenience macro to make a [GEdgeInsets](/docs/c/Graphics/Graphics_Types/#GEdgeInsets) This macro follows the CSS shorthand notation where you can call it with.

 |
| c | [grect\_inset](/docs/c/Graphics/Graphics_Types/#grect_inset) |
| 

Returns a rectangle that is shrinked or expanded by the given edge insets.

 |
| c | [GBitmapDataRowInfo](/docs/c/Graphics/Graphics_Types/#GBitmapDataRowInfo) |
| 

Description of a single data row in the pixel data of a bitmap.

 |
| c | [GColor8](/docs/c/Graphics/Graphics_Types/#GColor8) |
| |
| c | [GEdgeInsets](/docs/c/Graphics/Graphics_Types/#GEdgeInsets) |
| 

Represents insets for four sides. Negative values mean a side extends.

 |
| c | [GPoint](/docs/c/Graphics/Graphics_Types/#GPoint) |
| 

Represents a point in a 2-dimensional coordinate system.

 |
| c | [GRect](/docs/c/Graphics/Graphics_Types/#GRect) |
| 

Represents a rectangle and defining it using the origin of the upper-lefthand corner and its size.

 |
| c | [GSize](/docs/c/Graphics/Graphics_Types/#GSize) |
| 

Represents a 2-dimensional size.

 |
| c | [Color Definitions](/docs/c/Graphics/Graphics_Types/Color_Definitions/) |
| 

A list of all of the named colors available with links to the color map on the Pebble Developer website.

 |
| c | [GColorBlackARGB8](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorBlackARGB8) |
| |
| c | [GColorOxfordBlueARGB8](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorOxfordBlueARGB8) |
| |
| c | [GColorDukeBlueARGB8](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorDukeBlueARGB8) |
| |
| c | [GColorBlueARGB8](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorBlueARGB8) |
| |
| c | [GColorDarkGreenARGB8](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorDarkGreenARGB8) |
| |
| c | [GColorMidnightGreenARGB8](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorMidnightGreenARGB8) |
| |
| c | [GColorCobaltBlueARGB8](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorCobaltBlueARGB8) |
| |
| c | [GColorBlueMoonARGB8](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorBlueMoonARGB8) |
| |
| c | [GColorIslamicGreenARGB8](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorIslamicGreenARGB8) |
| |
| c | [GColorJaegerGreenARGB8](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorJaegerGreenARGB8) |
| |
| c | [GColorTiffanyBlueARGB8](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorTiffanyBlueARGB8) |
| |
| c | [GColorVividCeruleanARGB8](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorVividCeruleanARGB8) |
| |
| c | [GColorGreenARGB8](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorGreenARGB8) |
| |
| c | [GColorMalachiteARGB8](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorMalachiteARGB8) |
| |
| c | [GColorMediumSpringGreenARGB8](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorMediumSpringGreenARGB8) |
| |
| c | [GColorCyanARGB8](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorCyanARGB8) |
| |
| c | [GColorBulgarianRoseARGB8](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorBulgarianRoseARGB8) |
| |
| c | [GColorImperialPurpleARGB8](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorImperialPurpleARGB8) |
| |
| c | [GColorIndigoARGB8](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorIndigoARGB8) |
| |
| c | [GColorElectricUltramarineARGB8](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorElectricUltramarineARGB8) |
| |
| c | [GColorArmyGreenARGB8](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorArmyGreenARGB8) |
| |
| c | [GColorDarkGrayARGB8](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorDarkGrayARGB8) |
| |
| c | [GColorLibertyARGB8](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorLibertyARGB8) |
| |
| c | [GColorVeryLightBlueARGB8](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorVeryLightBlueARGB8) |
| |
| c | [GColorKellyGreenARGB8](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorKellyGreenARGB8) |
| |
| c | [GColorMayGreenARGB8](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorMayGreenARGB8) |
| |
| c | [GColorCadetBlueARGB8](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorCadetBlueARGB8) |
| |
| c | [GColorPictonBlueARGB8](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorPictonBlueARGB8) |
| |
| c | [GColorBrightGreenARGB8](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorBrightGreenARGB8) |
| |
| c | [GColorScreaminGreenARGB8](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorScreaminGreenARGB8) |
| |
| c | [GColorMediumAquamarineARGB8](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorMediumAquamarineARGB8) |
| |
| c | [GColorElectricBlueARGB8](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorElectricBlueARGB8) |
| |
| c | [GColorDarkCandyAppleRedARGB8](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorDarkCandyAppleRedARGB8) |
| |
| c | [GColorJazzberryJamARGB8](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorJazzberryJamARGB8) |
| |
| c | [GColorPurpleARGB8](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorPurpleARGB8) |
| |
| c | [GColorVividVioletARGB8](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorVividVioletARGB8) |
| |
| c | [GColorWindsorTanARGB8](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorWindsorTanARGB8) |
| |
| c | [GColorRoseValeARGB8](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorRoseValeARGB8) |
| |
| c | [GColorPurpureusARGB8](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorPurpureusARGB8) |
| |
| c | [GColorLavenderIndigoARGB8](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorLavenderIndigoARGB8) |
| |
| c | [GColorLimerickARGB8](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorLimerickARGB8) |
| |
| c | [GColorBrassARGB8](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorBrassARGB8) |
| |
| c | [GColorLightGrayARGB8](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorLightGrayARGB8) |
| |
| c | [GColorBabyBlueEyesARGB8](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorBabyBlueEyesARGB8) |
| |
| c | [GColorSpringBudARGB8](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorSpringBudARGB8) |
| |
| c | [GColorInchwormARGB8](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorInchwormARGB8) |
| |
| c | [GColorMintGreenARGB8](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorMintGreenARGB8) |
| |
| c | [GColorCelesteARGB8](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorCelesteARGB8) |
| |
| c | [GColorRedARGB8](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorRedARGB8) |
| |
| c | [GColorFollyARGB8](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorFollyARGB8) |
| |
| c | [GColorFashionMagentaARGB8](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorFashionMagentaARGB8) |
| |
| c | [GColorMagentaARGB8](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorMagentaARGB8) |
| |
| c | [GColorOrangeARGB8](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorOrangeARGB8) |
| |
| c | [GColorSunsetOrangeARGB8](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorSunsetOrangeARGB8) |
| |
| c | [GColorBrilliantRoseARGB8](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorBrilliantRoseARGB8) |
| |
| c | [GColorShockingPinkARGB8](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorShockingPinkARGB8) |
| |
| c | [GColorChromeYellowARGB8](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorChromeYellowARGB8) |
| |
| c | [GColorRajahARGB8](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorRajahARGB8) |
| |
| c | [GColorMelonARGB8](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorMelonARGB8) |
| |
| c | [GColorRichBrilliantLavenderARGB8](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorRichBrilliantLavenderARGB8) |
| |
| c | [GColorYellowARGB8](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorYellowARGB8) |
| |
| c | [GColorIcterineARGB8](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorIcterineARGB8) |
| |
| c | [GColorPastelYellowARGB8](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorPastelYellowARGB8) |
| |
| c | [GColorWhiteARGB8](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorWhiteARGB8) |
| |
| c | [GColorBlack](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorBlack) |
| 

[GColorBlack](https://developer.getpebble.com/tools/color-picker/#000000)

 |
| c | [GColorOxfordBlue](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorOxfordBlue) |
| 

[GColorOxfordBlue](https://developer.getpebble.com/tools/color-picker/#000055)

 |
| c | [GColorDukeBlue](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorDukeBlue) |
| 

[GColorDukeBlue](https://developer.getpebble.com/tools/color-picker/#0000AA)

 |
| c | [GColorBlue](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorBlue) |
| 

[GColorBlue](https://developer.getpebble.com/tools/color-picker/#0000FF)

 |
| c | [GColorDarkGreen](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorDarkGreen) |
| 

[GColorDarkGreen](https://developer.getpebble.com/tools/color-picker/#005500)

 |
| c | [GColorMidnightGreen](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorMidnightGreen) |
| 

[GColorMidnightGreen](https://developer.getpebble.com/tools/color-picker/#005555)

 |
| c | [GColorCobaltBlue](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorCobaltBlue) |
| 

[GColorCobaltBlue](https://developer.getpebble.com/tools/color-picker/#0055AA)

 |
| c | [GColorBlueMoon](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorBlueMoon) |
| 

[GColorBlueMoon](https://developer.getpebble.com/tools/color-picker/#0055FF)

 |
| c | [GColorIslamicGreen](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorIslamicGreen) |
| 

[GColorIslamicGreen](https://developer.getpebble.com/tools/color-picker/#00AA00)

 |
| c | [GColorJaegerGreen](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorJaegerGreen) |
| 

[GColorJaegerGreen](https://developer.getpebble.com/tools/color-picker/#00AA55)

 |
| c | [GColorTiffanyBlue](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorTiffanyBlue) |
| 

[GColorTiffanyBlue](https://developer.getpebble.com/tools/color-picker/#00AAAA)

 |
| c | [GColorVividCerulean](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorVividCerulean) |
| 

[GColorVividCerulean](https://developer.getpebble.com/tools/color-picker/#00AAFF)

 |
| c | [GColorGreen](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorGreen) |
| 

[GColorGreen](https://developer.getpebble.com/tools/color-picker/#00FF00)

 |
| c | [GColorMalachite](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorMalachite) |
| 

[GColorMalachite](https://developer.getpebble.com/tools/color-picker/#00FF55)

 |
| c | [GColorMediumSpringGreen](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorMediumSpringGreen) |
| 

[GColorMediumSpringGreen](https://developer.getpebble.com/tools/color-picker/#00FFAA)

 |
| c | [GColorCyan](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorCyan) |
| 

[GColorCyan](https://developer.getpebble.com/tools/color-picker/#00FFFF)

 |
| c | [GColorBulgarianRose](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorBulgarianRose) |
| 

[GColorBulgarianRose](https://developer.getpebble.com/tools/color-picker/#550000)

 |
| c | [GColorImperialPurple](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorImperialPurple) |
| 

[GColorImperialPurple](https://developer.getpebble.com/tools/color-picker/#550055)

 |
| c | [GColorIndigo](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorIndigo) |
| 

[GColorIndigo](https://developer.getpebble.com/tools/color-picker/#5500AA)

 |
| c | [GColorElectricUltramarine](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorElectricUltramarine) |
| 

[GColorElectricUltramarine](https://developer.getpebble.com/tools/color-picker/#5500FF)

 |
| c | [GColorArmyGreen](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorArmyGreen) |
| 

[GColorArmyGreen](https://developer.getpebble.com/tools/color-picker/#555500)

 |
| c | [GColorDarkGray](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorDarkGray) |
| 

[GColorDarkGray](https://developer.getpebble.com/tools/color-picker/#555555)

 |
| c | [GColorLiberty](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorLiberty) |
| 

[GColorLiberty](https://developer.getpebble.com/tools/color-picker/#5555AA)

 |
| c | [GColorVeryLightBlue](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorVeryLightBlue) |
| 

[GColorVeryLightBlue](https://developer.getpebble.com/tools/color-picker/#5555FF)

 |
| c | [GColorKellyGreen](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorKellyGreen) |
| 

[GColorKellyGreen](https://developer.getpebble.com/tools/color-picker/#55AA00)

 |
| c | [GColorMayGreen](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorMayGreen) |
| 

[GColorMayGreen](https://developer.getpebble.com/tools/color-picker/#55AA55)

 |
| c | [GColorCadetBlue](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorCadetBlue) |
| 

[GColorCadetBlue](https://developer.getpebble.com/tools/color-picker/#55AAAA)

 |
| c | [GColorPictonBlue](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorPictonBlue) |
| 

[GColorPictonBlue](https://developer.getpebble.com/tools/color-picker/#55AAFF)

 |
| c | [GColorBrightGreen](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorBrightGreen) |
| 

[GColorBrightGreen](https://developer.getpebble.com/tools/color-picker/#55FF00)

 |
| c | [GColorScreaminGreen](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorScreaminGreen) |
| 

[GColorScreaminGreen](https://developer.getpebble.com/tools/color-picker/#55FF55)

 |
| c | [GColorMediumAquamarine](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorMediumAquamarine) |
| 

[GColorMediumAquamarine](https://developer.getpebble.com/tools/color-picker/#55FFAA)

 |
| c | [GColorElectricBlue](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorElectricBlue) |
| 

[GColorElectricBlue](https://developer.getpebble.com/tools/color-picker/#55FFFF)

 |
| c | [GColorDarkCandyAppleRed](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorDarkCandyAppleRed) |
| 

[GColorDarkCandyAppleRed](https://developer.getpebble.com/tools/color-picker/#AA0000)

 |
| c | [GColorJazzberryJam](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorJazzberryJam) |
| 

[GColorJazzberryJam](https://developer.getpebble.com/tools/color-picker/#AA0055)

 |
| c | [GColorPurple](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorPurple) |
| 

[GColorPurple](https://developer.getpebble.com/tools/color-picker/#AA00AA)

 |
| c | [GColorVividViolet](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorVividViolet) |
| 

[GColorVividViolet](https://developer.getpebble.com/tools/color-picker/#AA00FF)

 |
| c | [GColorWindsorTan](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorWindsorTan) |
| 

[GColorWindsorTan](https://developer.getpebble.com/tools/color-picker/#AA5500)

 |
| c | [GColorRoseVale](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorRoseVale) |
| 

[GColorRoseVale](https://developer.getpebble.com/tools/color-picker/#AA5555)

 |
| c | [GColorPurpureus](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorPurpureus) |
| 

[GColorPurpureus](https://developer.getpebble.com/tools/color-picker/#AA55AA)

 |
| c | [GColorLavenderIndigo](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorLavenderIndigo) |
| 

[GColorLavenderIndigo](https://developer.getpebble.com/tools/color-picker/#AA55FF)

 |
| c | [GColorLimerick](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorLimerick) |
| 

[GColorLimerick](https://developer.getpebble.com/tools/color-picker/#AAAA00)

 |
| c | [GColorBrass](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorBrass) |
| 

[GColorBrass](https://developer.getpebble.com/tools/color-picker/#AAAA55)

 |
| c | [GColorLightGray](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorLightGray) |
| 

[GColorLightGray](https://developer.getpebble.com/tools/color-picker/#AAAAAA)

 |
| c | [GColorBabyBlueEyes](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorBabyBlueEyes) |
| 

[GColorBabyBlueEyes](https://developer.getpebble.com/tools/color-picker/#AAAAFF)

 |
| c | [GColorSpringBud](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorSpringBud) |
| 

[GColorSpringBud](https://developer.getpebble.com/tools/color-picker/#AAFF00)

 |
| c | [GColorInchworm](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorInchworm) |
| 

[GColorInchworm](https://developer.getpebble.com/tools/color-picker/#AAFF55)

 |
| c | [GColorMintGreen](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorMintGreen) |
| 

[GColorMintGreen](https://developer.getpebble.com/tools/color-picker/#AAFFAA)

 |
| c | [GColorCeleste](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorCeleste) |
| 

[GColorCeleste](https://developer.getpebble.com/tools/color-picker/#AAFFFF)

 |
| c | [GColorRed](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorRed) |
| 

[GColorRed](https://developer.getpebble.com/tools/color-picker/#FF0000)

 |
| c | [GColorFolly](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorFolly) |
| 

[GColorFolly](https://developer.getpebble.com/tools/color-picker/#FF0055)

 |
| c | [GColorFashionMagenta](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorFashionMagenta) |
| 

[GColorFashionMagenta](https://developer.getpebble.com/tools/color-picker/#FF00AA)

 |
| c | [GColorMagenta](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorMagenta) |
| 

[GColorMagenta](https://developer.getpebble.com/tools/color-picker/#FF00FF)

 |
| c | [GColorOrange](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorOrange) |
| 

[GColorOrange](https://developer.getpebble.com/tools/color-picker/#FF5500)

 |
| c | [GColorSunsetOrange](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorSunsetOrange) |
| 

[GColorSunsetOrange](https://developer.getpebble.com/tools/color-picker/#FF5555)

 |
| c | [GColorBrilliantRose](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorBrilliantRose) |
| 

[GColorBrilliantRose](https://developer.getpebble.com/tools/color-picker/#FF55AA)

 |
| c | [GColorShockingPink](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorShockingPink) |
| 

[GColorShockingPink](https://developer.getpebble.com/tools/color-picker/#FF55FF)

 |
| c | [GColorChromeYellow](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorChromeYellow) |
| 

[GColorChromeYellow](https://developer.getpebble.com/tools/color-picker/#FFAA00)

 |
| c | [GColorRajah](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorRajah) |
| 

[GColorRajah](https://developer.getpebble.com/tools/color-picker/#FFAA55)

 |
| c | [GColorMelon](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorMelon) |
| 

[GColorMelon](https://developer.getpebble.com/tools/color-picker/#FFAAAA)

 |
| c | [GColorRichBrilliantLavender](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorRichBrilliantLavender) |
| 

[GColorRichBrilliantLavender](https://developer.getpebble.com/tools/color-picker/#FFAAFF)

 |
| c | [GColorYellow](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorYellow) |
| 

[GColorYellow](https://developer.getpebble.com/tools/color-picker/#FFFF00)

 |
| c | [GColorIcterine](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorIcterine) |
| 

[GColorIcterine](https://developer.getpebble.com/tools/color-picker/#FFFF55)

 |
| c | [GColorPastelYellow](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorPastelYellow) |
| 

[GColorPastelYellow](https://developer.getpebble.com/tools/color-picker/#FFFFAA)

 |
| c | [GColorWhite](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorWhite) |
| 

[GColorWhite](https://developer.getpebble.com/tools/color-picker/#FFFFFF)

 |
| c | [GColorClearARGB8](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorClearARGB8) |
| |
| c | [GColorClear](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorClear) |
| |
| c | [User Interface](/docs/c/User_Interface/) |
| 

Everything related to user interface.

 |
| c | [Animation](/docs/c/User_Interface/Animation/) |
| 

Abstract framework to create arbitrary animations

 |
| c | [Animation](/docs/c/User_Interface/Animation/#Animation) |
| |
| c | [AnimationProgress](/docs/c/User_Interface/Animation/#AnimationProgress) |
| 

The type used to represent how far an animation has progressed. This is passed to the animation's update handler.

 |
| c | [AnimationCurve](/docs/c/User_Interface/Animation/#AnimationCurve) |
| 

Values that are used to indicate the different animation curves, which determine the speed at which the animated value(s) change(s).

 |
| c | [AnimationCurveLinear](/docs/c/User_Interface/Animation/#AnimationCurveLinear) |
| 

Linear curve: the velocity is constant.

 |
| c | [AnimationCurveEaseIn](/docs/c/User_Interface/Animation/#AnimationCurveEaseIn) |
| 

Bicubic ease-in: accelerate from zero velocity.

 |
| c | [AnimationCurveEaseOut](/docs/c/User_Interface/Animation/#AnimationCurveEaseOut) |
| 

Bicubic ease-in: decelerate to zero velocity.

 |
| c | [AnimationCurveEaseInOut](/docs/c/User_Interface/Animation/#AnimationCurveEaseInOut) |
| 

Bicubic ease-in-out: accelerate from zero velocity, decelerate to zero velocity.

 |
| c | [AnimationCurveDefault](/docs/c/User_Interface/Animation/#AnimationCurveDefault) |
| |
| c | [AnimationCurveCustomFunction](/docs/c/User_Interface/Animation/#AnimationCurveCustomFunction) |
| 

Custom (user-provided) animation curve.

 |
| c | [AnimationCurveCustomInterpolationFunction](/docs/c/User_Interface/Animation/#AnimationCurveCustomInterpolationFunction) |
| 

User-provided interpolation function.

 |
| c | [AnimationCurve\_Reserved1](/docs/c/User_Interface/Animation/#AnimationCurve_Reserved1) |
| |
| c | [AnimationCurve\_Reserved2](/docs/c/User_Interface/Animation/#AnimationCurve_Reserved2) |
| |
| c | [animation\_create](/docs/c/User_Interface/Animation/#animation_create) |
| 

Creates a new Animation on the heap and initalizes it with the default values.

 |
| c | [animation\_destroy](/docs/c/User_Interface/Animation/#animation_destroy) |
| 

Destroys an Animation previously created by animation\_create.

 |
| c | [ANIMATION\_DURATION\_INFINITE](/docs/c/User_Interface/Animation/#ANIMATION_DURATION_INFINITE) |
| 

Constant to indicate "infinite" duration. This can be used with [animation\_set\_duration()](/docs/c/User_Interface/Animation/#animation_set_duration) to indicate that the animation should run indefinitely. This is useful when implementing for example a frame-by-frame simulation that does not have a clear ending (e.g. a game).

 |
| c | [ANIMATION\_PLAY\_COUNT\_INFINITE](/docs/c/User_Interface/Animation/#ANIMATION_PLAY_COUNT_INFINITE) |
| 

Constant to indicate infinite play count. Can be passed to [animation\_set\_play\_count()](/docs/c/User_Interface/Animation/#animation_set_play_count) to repeat indefinitely.

 |
| c | [ANIMATION\_NORMALIZED\_MIN](/docs/c/User_Interface/Animation/#ANIMATION_NORMALIZED_MIN) |
| 

The normalized distance at the start of the animation.

 |
| c | [ANIMATION\_NORMALIZED\_MAX](/docs/c/User_Interface/Animation/#ANIMATION_NORMALIZED_MAX) |
| 

The normalized distance at the end of the animation.

 |
| c | [animation\_clone](/docs/c/User_Interface/Animation/#animation_clone) |
| |
| c | [animation\_sequence\_create](/docs/c/User_Interface/Animation/#animation_sequence_create) |
| 

Create a new sequence animation from a list of 2 or more other animations. The returned animation owns the animations that were provided as arguments and no further write operations on those handles are allowed. The variable length argument list must be terminated with a NULL ptr.

 |
| c | [animation\_sequence\_create\_from\_array](/docs/c/User_Interface/Animation/#animation_sequence_create_from_array) |
| 

An alternate form of [animation\_sequence\_create()](/docs/c/User_Interface/Animation/#animation_sequence_create) that accepts an array of other animations.

 |
| c | [animation\_spawn\_create](/docs/c/User_Interface/Animation/#animation_spawn_create) |
| 

Create a new spawn animation from a list of 2 or more other animations. The returned animation owns the animations that were provided as arguments and no further write operations on those handles are allowed. The variable length argument list must be terminated with a NULL ptr.

 |
| c | [animation\_spawn\_create\_from\_array](/docs/c/User_Interface/Animation/#animation_spawn_create_from_array) |
| 

An alternate form of [animation\_spawn\_create()](/docs/c/User_Interface/Animation/#animation_spawn_create) that accepts an array of other animations.

 |
| c | [animation\_set\_elapsed](/docs/c/User_Interface/Animation/#animation_set_elapsed) |
| 

Seek to a specific location in the animation. Only forward seeking is allowed. Returns true if successful, false if the passed in seek location is invalid.

 |
| c | [animation\_get\_elapsed](/docs/c/User_Interface/Animation/#animation_get_elapsed) |
| 

Get the current location in the animation.

 |
| c | [animation\_set\_reverse](/docs/c/User_Interface/Animation/#animation_set_reverse) |
| 

Set an animation to run in reverse (or forward)

 |
| c | [animation\_get\_reverse](/docs/c/User_Interface/Animation/#animation_get_reverse) |
| 

Get the reverse setting of an animation.

 |
| c | [animation\_set\_play\_count](/docs/c/User_Interface/Animation/#animation_set_play_count) |
| 

Set an animation to play N times. The default is 1.

 |
| c | [animation\_get\_play\_count](/docs/c/User_Interface/Animation/#animation_get_play_count) |
| 

Get the play count of an animation.

 |
| c | [animation\_set\_duration](/docs/c/User_Interface/Animation/#animation_set_duration) |
| 

Sets the time in milliseconds that an animation takes from start to finish.

 |
| c | [animation\_get\_duration](/docs/c/User_Interface/Animation/#animation_get_duration) |
| 

Get the static duration of an animation from start to end (ignoring how much has already played, if any).

 |
| c | [animation\_set\_delay](/docs/c/User_Interface/Animation/#animation_set_delay) |
| 

Sets an optional delay for the animation.

 |
| c | [animation\_get\_delay](/docs/c/User_Interface/Animation/#animation_get_delay) |
| 

Get the delay of an animation in milliseconds.

 |
| c | [animation\_set\_curve](/docs/c/User_Interface/Animation/#animation_set_curve) |
| 

Sets the animation curve for the animation.

 |
| c | [animation\_get\_curve](/docs/c/User_Interface/Animation/#animation_get_curve) |
| 

Gets the animation curve for the animation.

 |
| c | [AnimationCurveFunction](/docs/c/User_Interface/Animation/#AnimationCurveFunction) |
| 

The function pointer type of a custom animation curve.

 |
| c | [animation\_set\_custom\_curve](/docs/c/User_Interface/Animation/#animation_set_custom_curve) |
| 

Sets a custom animation curve function.

 |
| c | [animation\_get\_custom\_curve](/docs/c/User_Interface/Animation/#animation_get_custom_curve) |
| 

Gets the custom animation curve function for the animation.

 |
| c | [AnimationStartedHandler](/docs/c/User_Interface/Animation/#AnimationStartedHandler) |
| 

The function pointer type of the handler that will be called when an animation is started, just before updating the first frame of the animation.

 |
| c | [AnimationStoppedHandler](/docs/c/User_Interface/Animation/#AnimationStoppedHandler) |
| 

The function pointer type of the handler that will be called when the animation is stopped.

 |
| c | [animation\_set\_handlers](/docs/c/User_Interface/Animation/#animation_set_handlers) |
| 

Sets the callbacks for the animation. Often an application needs to run code at the start or at the end of an animation. Using this function is possible to register callback functions with an animation, that will get called at the start and end of the animation.

 |
| c | [animation\_get\_context](/docs/c/User_Interface/Animation/#animation_get_context) |
| 

Gets the application-specific callback context of the animation. This `void` pointer is passed as an argument when the animation system calls [AnimationHandlers](/docs/c/User_Interface/Animation/#AnimationHandlers) callbacks. The context pointer can be set to point to any application specific data using [animation\_set\_handlers()](/docs/c/User_Interface/Animation/#animation_set_handlers).

 |
| c | [animation\_schedule](/docs/c/User_Interface/Animation/#animation_schedule) |
| 

Schedules the animation. Call this once after configuring an animation to get it to start running.

 |
| c | [animation\_unschedule](/docs/c/User_Interface/Animation/#animation_unschedule) |
| 

Unschedules the animation, which in effect stops the animation.

 |
| c | [animation\_unschedule\_all](/docs/c/User_Interface/Animation/#animation_unschedule_all) |
| 

Unschedules all animations of the application.

 |
| c | [animation\_is\_scheduled](/docs/c/User_Interface/Animation/#animation_is_scheduled) |
| |
| c | [AnimationSetupImplementation](/docs/c/User_Interface/Animation/#AnimationSetupImplementation) |
| 

Pointer to function that (optionally) prepares the animation for running. This callback is called when the animation is added to the scheduler.

 |
| c | [AnimationUpdateImplementation](/docs/c/User_Interface/Animation/#AnimationUpdateImplementation) |
| 

Pointer to function that updates the animation according to the given normalized progress. This callback will be called repeatedly by the animation scheduler whenever the animation needs to be updated.

 |
| c | [AnimationTeardownImplementation](/docs/c/User_Interface/Animation/#AnimationTeardownImplementation) |
| 

Pointer to function that (optionally) cleans up the animation. This callback is called when the animation is removed from the scheduler. In case the `.setup` implementation allocated any memory, this is a good place to release that memory again.

 |
| c | [animation\_set\_implementation](/docs/c/User_Interface/Animation/#animation_set_implementation) |
| 

Sets the implementation of the custom animation. When implementing custom animations, use this function to specify what functions need to be called to for the setup, frame update and teardown of the animation.

 |
| c | [animation\_get\_implementation](/docs/c/User_Interface/Animation/#animation_get_implementation) |
| 

Gets the implementation of the custom animation.

 |
| c | [AnimationHandlers](/docs/c/User_Interface/Animation/#AnimationHandlers) |
| 

The handlers that will get called when an animation starts and stops. See documentation with the function pointer types for more information.

 |
| c | [AnimationImplementation](/docs/c/User_Interface/Animation/#AnimationImplementation) |
| 

The 3 callbacks that implement a custom animation. Only the `.update` callback is mandatory, `.setup` and `.teardown` are optional. See the documentation with the function pointer typedefs for more information.

 |
| c | [PropertyAnimation](/docs/c/User_Interface/Animation/PropertyAnimation/) |
| 

A ProperyAnimation animates the value of a "property" of a "subject" over time.

 |
| c | [PropertyAnimation](/docs/c/User_Interface/Animation/PropertyAnimation/#PropertyAnimation) |
| |
| c | [property\_animation\_create\_layer\_frame](/docs/c/User_Interface/Animation/PropertyAnimation/#property_animation_create_layer_frame) |
| 

Convenience function to create and initialize a property animation that animates the frame of a Layer. It sets up the PropertyAnimation to use [layer\_set\_frame()](/docs/c/User_Interface/Layers/#layer_set_frame) and [layer\_get\_frame()](/docs/c/User_Interface/Layers/#layer_get_frame) as accessors and uses the `layer` parameter as the subject for the animation. The same defaults are used as with [animation\_create()](/docs/c/User_Interface/Animation/#animation_create).

 |
| c | [property\_animation\_create\_bounds\_origin](/docs/c/User_Interface/Animation/PropertyAnimation/#property_animation_create_bounds_origin) |
| 

Convenience function to create and initialize a property animation that animates the bound's origin of a Layer. It sets up the PropertyAnimation to use [layer\_set\_bounds()](/docs/c/User_Interface/Layers/#layer_set_bounds) and [layer\_get\_bounds()](/docs/c/User_Interface/Layers/#layer_get_bounds) as accessors and uses the `layer` parameter as the subject for the animation. The same defaults are used as with [animation\_create()](/docs/c/User_Interface/Animation/#animation_create).

 |
| c | [property\_animation\_create](/docs/c/User_Interface/Animation/PropertyAnimation/#property_animation_create) |
| 

Creates a new PropertyAnimation on the heap and and initializes it with the specified values. The same defaults are used as with [animation\_create()](/docs/c/User_Interface/Animation/#animation_create). If the `from_value` or the `to_value` is `NULL`, the getter accessor will be called to get the current value of the property and be used instead.

 |
| c | [property\_animation\_destroy](/docs/c/User_Interface/Animation/PropertyAnimation/#property_animation_destroy) |
| 

Destroy a property animation allocated by [property\_animation\_create()](/docs/c/User_Interface/Animation/PropertyAnimation/#property_animation_create) or relatives.

 |
| c | [property\_animation\_update\_int16](/docs/c/User_Interface/Animation/PropertyAnimation/#property_animation_update_int16) |
| 

Default update callback for a property animations to update a property of type int16\_t. Assign this function to the `.base.update` callback field of your [PropertyAnimationImplementation](/docs/c/User_Interface/Animation/PropertyAnimation/#PropertyAnimationImplementation), in combination with a `.getter` and `.setter` accessors of types [Int16Getter](/docs/c/User_Interface/Animation/PropertyAnimation/#Int16Getter) and [Int16Setter](/docs/c/User_Interface/Animation/PropertyAnimation/#Int16Setter). The implementation of this function will calculate the next value of the animation and call the setter to set the new value upon the subject.

 |
| c | [property\_animation\_update\_uint32](/docs/c/User_Interface/Animation/PropertyAnimation/#property_animation_update_uint32) |
| 

Default update callback for a property animations to update a property of type [uint32\_t](/docs/c/Standard_C/#uint32_t). Assign this function to the `.base.update` callback field of your [PropertyAnimationImplementation](/docs/c/User_Interface/Animation/PropertyAnimation/#PropertyAnimationImplementation), in combination with a `.getter` and `.setter` accessors of types [UInt32Getter](/docs/c/User_Interface/Animation/PropertyAnimation/#UInt32Getter) and [UInt32Setter](/docs/c/User_Interface/Animation/PropertyAnimation/#UInt32Setter). The implementation of this function will calculate the next value of the animation and call the setter to set the new value upon the subject.

 |
| c | [property\_animation\_update\_gpoint](/docs/c/User_Interface/Animation/PropertyAnimation/#property_animation_update_gpoint) |
| 

Default update callback for a property animations to update a property of type [GPoint](/docs/c/Graphics/Graphics_Types/#GPoint). Assign this function to the `.base.update` callback field of your [PropertyAnimationImplementation](/docs/c/User_Interface/Animation/PropertyAnimation/#PropertyAnimationImplementation), in combination with a `.getter` and `.setter` accessors of types [GPointGetter](/docs/c/User_Interface/Animation/PropertyAnimation/#GPointGetter) and [GPointSetter](/docs/c/User_Interface/Animation/PropertyAnimation/#GPointSetter). The implementation of this function will calculate the next point of the animation and call the setter to set the new point upon the subject.

 |
| c | [property\_animation\_update\_grect](/docs/c/User_Interface/Animation/PropertyAnimation/#property_animation_update_grect) |
| 

Default update callback for a property animations to update a property of type [GRect](/docs/c/Graphics/Graphics_Types/#GRect). Assign this function to the `.base.update` callback field of your [PropertyAnimationImplementation](/docs/c/User_Interface/Animation/PropertyAnimation/#PropertyAnimationImplementation), in combination with a `.getter` and `.setter` accessors of types [GRectGetter](/docs/c/User_Interface/Animation/PropertyAnimation/#GRectGetter) and [GRectSetter](/docs/c/User_Interface/Animation/PropertyAnimation/#GRectSetter). The implementation of this function will calculate the next rectangle of the animation and call the setter to set the new rectangle upon the subject.

 |
| c | [property\_animation\_update\_gcolor8](/docs/c/User_Interface/Animation/PropertyAnimation/#property_animation_update_gcolor8) |
| 

Default update callback for a property animations to update a property of type GColor8. Assign this function to the `.base.update` callback field of your [PropertyAnimationImplementation](/docs/c/User_Interface/Animation/PropertyAnimation/#PropertyAnimationImplementation), in combination with a `.getter` and `.setter` accessors of types [GColor8Getter](/docs/c/User_Interface/Animation/PropertyAnimation/#GColor8Getter) and [GColor8Setter](/docs/c/User_Interface/Animation/PropertyAnimation/#GColor8Setter). The implementation of this function will calculate the next rectangle of the animation and call the setter to set the new value upon the subject.

 |
| c | [GPointReturn](/docs/c/User_Interface/Animation/PropertyAnimation/#GPointReturn) |
| 

Work-around for function pointer return type [GPoint](/docs/c/Graphics/Graphics_Types/#GPoint) to avoid tripping the pre-processor to use the equally named [GPoint](/docs/c/Graphics/Graphics_Types/#GPoint) define.

 |
| c | [GRectReturn](/docs/c/User_Interface/Animation/PropertyAnimation/#GRectReturn) |
| 

Work-around for function pointer return type [GRect](/docs/c/Graphics/Graphics_Types/#GRect) to avoid tripping the pre-processor to use the equally named [GRect](/docs/c/Graphics/Graphics_Types/#GRect) define.

 |
| c | [Int16Setter](/docs/c/User_Interface/Animation/PropertyAnimation/#Int16Setter) |
| 

Function signature of a setter function to set a property of type int16\_t onto the subject.

 |
| c | [Int16Getter](/docs/c/User_Interface/Animation/PropertyAnimation/#Int16Getter) |
| 

Function signature of a getter function to get the current property of type int16\_t of the subject.

 |
| c | [UInt32Setter](/docs/c/User_Interface/Animation/PropertyAnimation/#UInt32Setter) |
| 

Function signature of a setter function to set a property of type [uint32\_t](/docs/c/Standard_C/#uint32_t) onto the subject.

 |
| c | [UInt32Getter](/docs/c/User_Interface/Animation/PropertyAnimation/#UInt32Getter) |
| 

Function signature of a getter function to get the current property of type [uint32\_t](/docs/c/Standard_C/#uint32_t) of the subject.

 |
| c | [GPointSetter](/docs/c/User_Interface/Animation/PropertyAnimation/#GPointSetter) |
| 

Function signature of a setter function to set a property of type [GPoint](/docs/c/Graphics/Graphics_Types/#GPoint) onto the subject.

 |
| c | [GPointGetter](/docs/c/User_Interface/Animation/PropertyAnimation/#GPointGetter) |
| 

Function signature of a getter function to get the current property of type [GPoint](/docs/c/Graphics/Graphics_Types/#GPoint) of the subject.

 |
| c | [GRectSetter](/docs/c/User_Interface/Animation/PropertyAnimation/#GRectSetter) |
| 

Function signature of a setter function to set a property of type [GRect](/docs/c/Graphics/Graphics_Types/#GRect) onto the subject.

 |
| c | [GRectGetter](/docs/c/User_Interface/Animation/PropertyAnimation/#GRectGetter) |
| 

Function signature of a getter function to get the current property of type [GRect](/docs/c/Graphics/Graphics_Types/#GRect) of the subject.

 |
| c | [GColor8Setter](/docs/c/User_Interface/Animation/PropertyAnimation/#GColor8Setter) |
| 

Function signature of a setter function to set a property of type GColor8 onto the subject.

 |
| c | [GColor8Getter](/docs/c/User_Interface/Animation/PropertyAnimation/#GColor8Getter) |
| 

Function signature of a getter function to get the current property of type GColor8 of the subject.

 |
| c | [property\_animation\_get\_animation](/docs/c/User_Interface/Animation/PropertyAnimation/#property_animation_get_animation) |
| 

Convenience function to retrieve an animation instance from a property animation instance.

 |
| c | [property\_animation\_clone](/docs/c/User_Interface/Animation/PropertyAnimation/#property_animation_clone) |
| 

Convenience function to clone a property animation instance.

 |
| c | [property\_animation\_get\_from\_grect](/docs/c/User_Interface/Animation/PropertyAnimation/#property_animation_get_from_grect) |
| 

Convenience function to retrieve the 'from' [GRect](/docs/c/Graphics/Graphics_Types/#GRect) value from property animation handle.

 |
| c | [property\_animation\_set\_from\_grect](/docs/c/User_Interface/Animation/PropertyAnimation/#property_animation_set_from_grect) |
| 

Convenience function to set the 'from' [GRect](/docs/c/Graphics/Graphics_Types/#GRect) value of property animation handle.

 |
| c | [property\_animation\_get\_from\_gpoint](/docs/c/User_Interface/Animation/PropertyAnimation/#property_animation_get_from_gpoint) |
| 

Convenience function to retrieve the 'from' [GPoint](/docs/c/Graphics/Graphics_Types/#GPoint) value from property animation handle.

 |
| c | [property\_animation\_set\_from\_gpoint](/docs/c/User_Interface/Animation/PropertyAnimation/#property_animation_set_from_gpoint) |
| 

Convenience function to set the 'from' [GPoint](/docs/c/Graphics/Graphics_Types/#GPoint) value of property animation handle.

 |
| c | [property\_animation\_get\_from\_int16](/docs/c/User_Interface/Animation/PropertyAnimation/#property_animation_get_from_int16) |
| 

Convenience function to retrieve the 'from' int16\_t value from property animation handle.

 |
| c | [property\_animation\_set\_from\_int16](/docs/c/User_Interface/Animation/PropertyAnimation/#property_animation_set_from_int16) |
| 

Convenience function to set the 'from' int16\_t value of property animation handle.

 |
| c | [property\_animation\_get\_to\_grect](/docs/c/User_Interface/Animation/PropertyAnimation/#property_animation_get_to_grect) |
| 

Convenience function to retrieve the 'to' [GRect](/docs/c/Graphics/Graphics_Types/#GRect) value from property animation handle.

 |
| c | [property\_animation\_set\_to\_grect](/docs/c/User_Interface/Animation/PropertyAnimation/#property_animation_set_to_grect) |
| 

Convenience function to set the 'to' [GRect](/docs/c/Graphics/Graphics_Types/#GRect) value of property animation handle.

 |
| c | [property\_animation\_get\_to\_gpoint](/docs/c/User_Interface/Animation/PropertyAnimation/#property_animation_get_to_gpoint) |
| 

Convenience function to retrieve the 'to' [GPoint](/docs/c/Graphics/Graphics_Types/#GPoint) value from property animation handle.

 |
| c | [property\_animation\_set\_to\_gpoint](/docs/c/User_Interface/Animation/PropertyAnimation/#property_animation_set_to_gpoint) |
| 

Convenience function to set the 'to' [GPoint](/docs/c/Graphics/Graphics_Types/#GPoint) value of property animation handle.

 |
| c | [property\_animation\_get\_to\_int16](/docs/c/User_Interface/Animation/PropertyAnimation/#property_animation_get_to_int16) |
| 

Convenience function to retrieve the 'to' int16\_t value from property animation handle.

 |
| c | [property\_animation\_set\_to\_int16](/docs/c/User_Interface/Animation/PropertyAnimation/#property_animation_set_to_int16) |
| 

Convenience function to set the 'to' int16\_t value of property animation handle.

 |
| c | [property\_animation\_get\_subject](/docs/c/User_Interface/Animation/PropertyAnimation/#property_animation_get_subject) |
| 

Retrieve the subject of a property animation.

 |
| c | [property\_animation\_set\_subject](/docs/c/User_Interface/Animation/PropertyAnimation/#property_animation_set_subject) |
| 

Set the subject of a property animation.

 |
| c | [property\_animation\_subject](/docs/c/User_Interface/Animation/PropertyAnimation/#property_animation_subject) |
| 

Helper function used by the property\_animation\_get|set\_subject macros.

 |
| c | [property\_animation\_from](/docs/c/User_Interface/Animation/PropertyAnimation/#property_animation_from) |
| 

Helper function used by the property\_animation\_get|set\_from\_.\* macros.

 |
| c | [property\_animation\_to](/docs/c/User_Interface/Animation/PropertyAnimation/#property_animation_to) |
| 

Helper function used by the property\_animation\_get|set\_to\_.\* macros.

 |
| c | [PropertyAnimationAccessors](/docs/c/User_Interface/Animation/PropertyAnimation/#PropertyAnimationAccessors) |
| 

Data structure containing the setter and getter function pointers that the property animation should use. The specified setter function will be used by the animation's update callback.   
 Based on the type of the property (int16\_t, [GPoint](/docs/c/Graphics/Graphics_Types/#GPoint) or [GRect](/docs/c/Graphics/Graphics_Types/#GRect)), the accompanying update callback should be used, see [property\_animation\_update\_int16()](/docs/c/User_Interface/Animation/PropertyAnimation/#property_animation_update_int16), [property\_animation\_update\_gpoint()](/docs/c/User_Interface/Animation/PropertyAnimation/#property_animation_update_gpoint) and [property\_animation\_update\_grect()](/docs/c/User_Interface/Animation/PropertyAnimation/#property_animation_update_grect).   
 The getter function is used when the animation is initialized, to assign the current value of the subject's property as "from" or "to" value, see [property\_animation\_create()](/docs/c/User_Interface/Animation/PropertyAnimation/#property_animation_create).

 |
| c | [PropertyAnimationImplementation](/docs/c/User_Interface/Animation/PropertyAnimation/#PropertyAnimationImplementation) |
| 

Data structure containing a collection of function pointers that form the implementation of the property animation. See the code example at the top ([PropertyAnimation](/docs/c/User_Interface/Animation/PropertyAnimation/)).

 |
| c | [Clicks](/docs/c/User_Interface/Clicks/) |
| 

Handling button click interactions

 |
| c | [ButtonId](/docs/c/User_Interface/Clicks/#ButtonId) |
| 

Button ID values.

 |
| c | [BUTTON\_ID\_BACK](/docs/c/User_Interface/Clicks/#BUTTON_ID_BACK) |
| 

Back button.

 |
| c | [BUTTON\_ID\_UP](/docs/c/User_Interface/Clicks/#BUTTON_ID_UP) |
| 

Up button.

 |
| c | [BUTTON\_ID\_SELECT](/docs/c/User_Interface/Clicks/#BUTTON_ID_SELECT) |
| 

Select (middle) button.

 |
| c | [BUTTON\_ID\_DOWN](/docs/c/User_Interface/Clicks/#BUTTON_ID_DOWN) |
| 

Down button.

 |
| c | [NUM\_BUTTONS](/docs/c/User_Interface/Clicks/#NUM_BUTTONS) |
| 

Total number of buttons.

 |
| c | [ClickRecognizerRef](/docs/c/User_Interface/Clicks/#ClickRecognizerRef) |
| 

Reference to opaque click recognizer When a [ClickHandler](/docs/c/User_Interface/Clicks/#ClickHandler) callback is called, the recognizer that fired the handler is passed in.

 |
| c | [ClickHandler](/docs/c/User_Interface/Clicks/#ClickHandler) |
| 

Function signature of the callback that handles a recognized click pattern.

 |
| c | [ClickConfigProvider](/docs/c/User_Interface/Clicks/#ClickConfigProvider) |
| 

This callback is called every time the window becomes visible (and when you call [window\_set\_click\_config\_provider()](/docs/c/User_Interface/Window/#window_set_click_config_provider) if the window is already visible).

 |
| c | [click\_number\_of\_clicks\_counted](/docs/c/User_Interface/Clicks/#click_number_of_clicks_counted) |
| 

Gets the click count. You can use this inside a click handler implementation to get the click count for multi\_click and (repeated) click events.

 |
| c | [click\_recognizer\_get\_button\_id](/docs/c/User_Interface/Clicks/#click_recognizer_get_button_id) |
| 

Gets the button identifier. You can use this inside a click handler implementation to get the button id for the click event.

 |
| c | [click\_recognizer\_is\_repeating](/docs/c/User_Interface/Clicks/#click_recognizer_is_repeating) |
| 

Is this a repeating click. You can use this inside a click handler implementation to find out whether this is a repeating click or not.

 |
| c | [Layers](/docs/c/User_Interface/Layers/) |
| 

User interface layers for displaying graphic components

 |
| c | [Layer](/docs/c/User_Interface/Layers/#Layer) |
| |
| c | [LayerUpdateProc](/docs/c/User_Interface/Layers/#LayerUpdateProc) |
| 

Function signature for a Layer's render callback (the name of the type is derived from the words 'update procedure'). The system will call the `.update_proc` callback whenever the Layer needs to be rendered.

 |
| c | [layer\_create](/docs/c/User_Interface/Layers/#layer_create) |
| 

Creates a layer on the heap and sets its frame and bounds. Default values:

 |
| c | [layer\_create\_with\_data](/docs/c/User_Interface/Layers/#layer_create_with_data) |
| 

Creates a layer on the heap with extra space for callback data, and set its frame andbounds. Default values:

 |
| c | [layer\_destroy](/docs/c/User_Interface/Layers/#layer_destroy) |
| 

Destroys a layer previously created by layer\_create.

 |
| c | [layer\_mark\_dirty](/docs/c/User_Interface/Layers/#layer_mark_dirty) |
| 

Marks the complete layer as "dirty", awaiting to be asked by the system to redraw itself. Typically, this function is called whenever state has changed that affects what the layer is displaying.

 |
| c | [layer\_set\_update\_proc](/docs/c/User_Interface/Layers/#layer_set_update_proc) |
| 

Sets the layer's render function. The system will call the `update_proc` automatically when the layer needs to redraw itself, see also [layer\_mark\_dirty()](/docs/c/User_Interface/Layers/#layer_mark_dirty).

 |
| c | [layer\_set\_frame](/docs/c/User_Interface/Layers/#layer_set_frame) |
| 

Sets the frame of the layer, which is it's bounding box relative to the coordinate system of its parent layer. The size of the layer's bounds will be extended automatically, so that the bounds cover the new frame.

 |
| c | [layer\_get\_frame](/docs/c/User_Interface/Layers/#layer_get_frame) |
| 

Gets the frame of the layer, which is it's bounding box relative to the coordinate system of its parent layer. If the frame has changed, [layer\_mark\_dirty()](/docs/c/User_Interface/Layers/#layer_mark_dirty) will be called automatically.

 |
| c | [layer\_set\_bounds](/docs/c/User_Interface/Layers/#layer_set_bounds) |
| 

Sets the bounds of the layer, which is it's bounding box relative to its frame. If the bounds has changed, [layer\_mark\_dirty()](/docs/c/User_Interface/Layers/#layer_mark_dirty) will be called automatically.

 |
| c | [layer\_get\_bounds](/docs/c/User_Interface/Layers/#layer_get_bounds) |
| 

Gets the bounds of the layer.

 |
| c | [layer\_get\_unobstructed\_bounds](/docs/c/User_Interface/Layers/#layer_get_unobstructed_bounds) |
| 

Get the largest unobstructed bounds rectangle of a layer.

 |
| c | [layer\_convert\_point\_to\_screen](/docs/c/User_Interface/Layers/#layer_convert_point_to_screen) |
| 

Converts a point from the layer's local coordinate system to screen coordinates.

 |
| c | [layer\_convert\_rect\_to\_screen](/docs/c/User_Interface/Layers/#layer_convert_rect_to_screen) |
| 

Converts a rectangle from the layer's local coordinate system to screen coordinates.

 |
| c | [layer\_get\_window](/docs/c/User_Interface/Layers/#layer_get_window) |
| 

Gets the window that the layer is currently attached to.

 |
| c | [layer\_remove\_from\_parent](/docs/c/User_Interface/Layers/#layer_remove_from_parent) |
| 

Removes the layer from its current parent layer If removed successfully, the child's parent layer will be marked dirty automatically.

 |
| c | [layer\_remove\_child\_layers](/docs/c/User_Interface/Layers/#layer_remove_child_layers) |
| 

Removes child layers from given layer If removed successfully, the child's parent layer will be marked dirty automatically.

 |
| c | [layer\_add\_child](/docs/c/User_Interface/Layers/#layer_add_child) |
| 

Adds the child layer to a given parent layer, making it appear in front of its parent and in front of any existing child layers of the parent. If the child layer was already part of a layer hierarchy, it will be removed from its old parent first. If added successfully, the parent (and children) will be marked dirty automatically.

 |
| c | [layer\_insert\_below\_sibling](/docs/c/User_Interface/Layers/#layer_insert_below_sibling) |
| 

Inserts the layer as a sibling behind another layer. If the layer to insert was already part of a layer hierarchy, it will be removed from its old parent first. The below\_layer has to be a child of a parent layer, otherwise this function will be a noop. If inserted successfully, the parent (and children) will be marked dirty automatically.

 |
| c | [layer\_insert\_above\_sibling](/docs/c/User_Interface/Layers/#layer_insert_above_sibling) |
| 

Inserts the layer as a sibling in front of another layer. The above\_layer has to be a child of a parent layer, otherwise this function will be a noop. If inserted successfully, the parent (and children) will be marked dirty automatically.

 |
| c | [layer\_set\_hidden](/docs/c/User_Interface/Layers/#layer_set_hidden) |
| 

Sets the visibility of the layer. If the visibility has changed, [layer\_mark\_dirty()](/docs/c/User_Interface/Layers/#layer_mark_dirty) will be called automatically on the parent layer.

 |
| c | [layer\_get\_hidden](/docs/c/User_Interface/Layers/#layer_get_hidden) |
| 

Gets the visibility of the layer.

 |
| c | [layer\_set\_clips](/docs/c/User_Interface/Layers/#layer_set_clips) |
| 

Sets whether clipping is enabled for the layer. If enabled, whatever the layer _and its children_ will draw using their `.update_proc` callbacks, will be clipped by the this layer's frame. If the clipping has changed, [layer\_mark\_dirty()](/docs/c/User_Interface/Layers/#layer_mark_dirty) will be called automatically.

 |
| c | [layer\_get\_clips](/docs/c/User_Interface/Layers/#layer_get_clips) |
| 

Gets whether clipping is enabled for the layer. If enabled, whatever the layer _and its children_ will draw using their `.update_proc` callbacks, will be clipped by the this layer's frame.

 |
| c | [layer\_get\_data](/docs/c/User_Interface/Layers/#layer_get_data) |
| 

Gets the data from a layer that has been created with an extra data region.

 |
| c | [ActionBarLayer](/docs/c/User_Interface/Layers/ActionBarLayer/) |
| 

Vertical, bar-shaped control widget on the right edge of the window

 |
| c | [ACTION\_BAR\_WIDTH](/docs/c/User_Interface/Layers/ActionBarLayer/#ACTION_BAR_WIDTH) |
| 

The width of the action bar in pixels.

 |
| c | [\_ACTION\_BAR\_WIDTH](/docs/c/User_Interface/Layers/ActionBarLayer/#_ACTION_BAR_WIDTH) |
| 

The width of the action bar in pixels, for all platforms.

 |
| c | [NUM\_ACTION\_BAR\_ITEMS](/docs/c/User_Interface/Layers/ActionBarLayer/#NUM_ACTION_BAR_ITEMS) |
| 

The maximum number of action bar items.

 |
| c | [ActionBarLayerIconPressAnimation](/docs/c/User_Interface/Layers/ActionBarLayer/#ActionBarLayerIconPressAnimation) |
| |
| c | [ActionBarLayerIconPressAnimationNone](/docs/c/User_Interface/Layers/ActionBarLayer/#ActionBarLayerIconPressAnimationNone) |
| |
| c | [ActionBarLayerIconPressAnimationMoveLeft](/docs/c/User_Interface/Layers/ActionBarLayer/#ActionBarLayerIconPressAnimationMoveLeft) |
| |
| c | [ActionBarLayerIconPressAnimationMoveUp](/docs/c/User_Interface/Layers/ActionBarLayer/#ActionBarLayerIconPressAnimationMoveUp) |
| |
| c | [ActionBarLayerIconPressAnimationMoveRight](/docs/c/User_Interface/Layers/ActionBarLayer/#ActionBarLayerIconPressAnimationMoveRight) |
| |
| c | [ActionBarLayerIconPressAnimationMoveDown](/docs/c/User_Interface/Layers/ActionBarLayer/#ActionBarLayerIconPressAnimationMoveDown) |
| |
| c | [ActionBarLayer](/docs/c/User_Interface/Layers/ActionBarLayer/#ActionBarLayer) |
| |
| c | [action\_bar\_layer\_create](/docs/c/User_Interface/Layers/ActionBarLayer/#action_bar_layer_create) |
| 

Creates a new ActionBarLayer on the heap and initalizes it with the default values.

 |
| c | [action\_bar\_layer\_destroy](/docs/c/User_Interface/Layers/ActionBarLayer/#action_bar_layer_destroy) |
| 

Destroys a ActionBarLayer previously created by action\_bar\_layer\_create.

 |
| c | [action\_bar\_layer\_get\_layer](/docs/c/User_Interface/Layers/ActionBarLayer/#action_bar_layer_get_layer) |
| 

Gets the "root" Layer of the action bar layer, which is the parent for the sub- layers used for its implementation.

 |
| c | [action\_bar\_layer\_set\_context](/docs/c/User_Interface/Layers/ActionBarLayer/#action_bar_layer_set_context) |
| 

Sets the context parameter, which will be passed in to [ClickHandler](/docs/c/User_Interface/Clicks/#ClickHandler) callbacks and the [ClickConfigProvider](/docs/c/User_Interface/Clicks/#ClickConfigProvider) callback of the action bar.

 |
| c | [action\_bar\_layer\_set\_click\_config\_provider](/docs/c/User_Interface/Layers/ActionBarLayer/#action_bar_layer_set_click_config_provider) |
| 

Sets the click configuration provider callback of the action bar. In this callback your application can associate handlers to the different types of click events for each of the buttons, see [Clicks](/docs/c/User_Interface/Clicks/).

 |
| c | [action\_bar\_layer\_set\_icon](/docs/c/User_Interface/Layers/ActionBarLayer/#action_bar_layer_set_icon) |
| 

Sets an action bar icon onto one of the 3 slots as identified by `button_id`. Only BUTTON\_ID\_UP, BUTTON\_ID\_SELECT and BUTTON\_ID\_DOWN can be used. The transition will not be animated. Whenever an icon is set, the click configuration provider will be called, to give the application the opportunity to reconfigure the button interaction.

 |
| c | [action\_bar\_layer\_clear\_icon](/docs/c/User_Interface/Layers/ActionBarLayer/#action_bar_layer_clear_icon) |
| 

Convenience function to clear out an existing icon. All it does is call `action_bar_layer_set_icon(action_bar, button_id, NULL)`

 |
| c | [action\_bar\_layer\_add\_to\_window](/docs/c/User_Interface/Layers/ActionBarLayer/#action_bar_layer_add_to_window) |
| 

Adds the action bar's layer on top of the window's root layer. It also adjusts the layout of the action bar to match the geometry of the window it gets added to. Lastly, it calls [window\_set\_click\_config\_provider\_with\_context()](/docs/c/User_Interface/Window/#window_set_click_config_provider_with_context) on the window to set it up to work with the internal callback and raw click handlers of the action bar, to enable the highlighting of the section of the action bar when the user presses a button.

 |
| c | [action\_bar\_layer\_remove\_from\_window](/docs/c/User_Interface/Layers/ActionBarLayer/#action_bar_layer_remove_from_window) |
| 

Removes the action bar from the window and unconfigures the window's click configuration provider. `NULL` is set as the window's new click config provider and also as its callback context. If it has not been added to a window before, this function is a no-op.

 |
| c | [action\_bar\_layer\_set\_background\_color](/docs/c/User_Interface/Layers/ActionBarLayer/#action_bar_layer_set_background_color) |
| 

Sets the background color of the action bar. Defaults to [GColorBlack](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorBlack). The action bar's layer is automatically marked dirty.

 |
| c | [action\_bar\_layer\_set\_icon\_animated](/docs/c/User_Interface/Layers/ActionBarLayer/#action_bar_layer_set_icon_animated) |
| 

Sets an action bar icon onto one of the 3 slots as identified by `button_id`. Only BUTTON\_ID\_UP, BUTTON\_ID\_SELECT and BUTTON\_ID\_DOWN can be used. Optionally, if `animated` is `true`, the transition will be animated. Whenever an icon is set, the click configuration provider will be called, to give the application the opportunity to reconfigure the button interaction.

 |
| c | [action\_bar\_layer\_set\_icon\_press\_animation](/docs/c/User_Interface/Layers/ActionBarLayer/#action_bar_layer_set_icon_press_animation) |
| 

Sets the animation to use while a button is pressed on an ActionBarLayer. By default we use ActionBarLayerIconPressAnimationMoveLeft.

 |
| c | [BitmapLayer](/docs/c/User_Interface/Layers/BitmapLayer/) |
| 

Layer that displays a bitmap image.

 |
| c | [BitmapLayer](/docs/c/User_Interface/Layers/BitmapLayer/#BitmapLayer) |
| |
| c | [bitmap\_layer\_create](/docs/c/User_Interface/Layers/BitmapLayer/#bitmap_layer_create) |
| 

Creates a new bitmap layer on the heap and initalizes it the default values.

 |
| c | [bitmap\_layer\_destroy](/docs/c/User_Interface/Layers/BitmapLayer/#bitmap_layer_destroy) |
| 

Destroys a window previously created by bitmap\_layer\_create.

 |
| c | [bitmap\_layer\_get\_layer](/docs/c/User_Interface/Layers/BitmapLayer/#bitmap_layer_get_layer) |
| 

Gets the "root" Layer of the bitmap layer, which is the parent for the sub- layers used for its implementation.

 |
| c | [bitmap\_layer\_get\_bitmap](/docs/c/User_Interface/Layers/BitmapLayer/#bitmap_layer_get_bitmap) |
| 

Gets the pointer to the bitmap image that the BitmapLayer is using.

 |
| c | [bitmap\_layer\_set\_bitmap](/docs/c/User_Interface/Layers/BitmapLayer/#bitmap_layer_set_bitmap) |
| 

Sets the bitmap onto the BitmapLayer. The bitmap is set by reference (no deep copy), thus the caller of this function has to make sure the bitmap is kept in memory.

 |
| c | [bitmap\_layer\_set\_alignment](/docs/c/User_Interface/Layers/BitmapLayer/#bitmap_layer_set_alignment) |
| 

Sets the alignment of the image to draw with in frame of the BitmapLayer. The aligment parameter specifies which edges of the bitmap should overlap with the frame of the BitmapLayer. If the bitmap is smaller than the frame of the BitmapLayer, the background is filled with the background color.

 |
| c | [bitmap\_layer\_set\_background\_color](/docs/c/User_Interface/Layers/BitmapLayer/#bitmap_layer_set_background_color) |
| 

Sets the background color of bounding box that will be drawn behind the image of the BitmapLayer.

 |
| c | [bitmap\_layer\_set\_compositing\_mode](/docs/c/User_Interface/Layers/BitmapLayer/#bitmap_layer_set_compositing_mode) |
| 

Sets the compositing mode of how the bitmap image is composited onto the BitmapLayer's background plane, or how it is composited onto what has been drawn beneath the BitmapLayer.

 |
| c | [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/) |
| 

Layer that displays a standard list menu. Data is provided using callbacks.

 |
| c | [menu\_cell\_basic\_draw](/docs/c/User_Interface/Layers/MenuLayer/#menu_cell_basic_draw) |
| 

Section drawing function to draw a basic section cell with the title, subtitle, and icon of the section. Call this function inside the `.draw_row` callback implementation, see [MenuLayerCallbacks](/docs/c/User_Interface/Layers/MenuLayer/#MenuLayerCallbacks). Note that if the size of `cell_layer` is too small to fit all of the cell items specified, not all of them may be drawn.

 |
| c | [menu\_cell\_title\_draw](/docs/c/User_Interface/Layers/MenuLayer/#menu_cell_title_draw) |
| 

Cell drawing function to draw a basic menu cell layout with title, subtitle Cell drawing function to draw a menu cell layout with only one big title. Call this function inside the `.draw_row` callback implementation, see [MenuLayerCallbacks](/docs/c/User_Interface/Layers/MenuLayer/#MenuLayerCallbacks).

 |
| c | [menu\_cell\_basic\_header\_draw](/docs/c/User_Interface/Layers/MenuLayer/#menu_cell_basic_header_draw) |
| 

Section header drawing function to draw a basic section header cell layout with the title of the section. Call this function inside the `.draw_header` callback implementation, see [MenuLayerCallbacks](/docs/c/User_Interface/Layers/MenuLayer/#MenuLayerCallbacks).

 |
| c | [MENU\_CELL\_BASIC\_HEADER\_HEIGHT](/docs/c/User_Interface/Layers/MenuLayer/#MENU_CELL_BASIC_HEADER_HEIGHT) |
| 

Default section header height in pixels.

 |
| c | [MENU\_INDEX\_NOT\_FOUND](/docs/c/User_Interface/Layers/MenuLayer/#MENU_INDEX_NOT_FOUND) |
| |
| c | [MenuIndex](/docs/c/User_Interface/Layers/MenuLayer/#MenuIndex) |
| 

Macro to create a [MenuIndex](/docs/c/User_Interface/Layers/MenuLayer/#MenuIndex).

 |
| c | [menu\_index\_compare](/docs/c/User_Interface/Layers/MenuLayer/#menu_index_compare) |
| 

Comparator function to determine the order of two [MenuIndex](/docs/c/User_Interface/Layers/MenuLayer/#MenuIndex) values.

 |
| c | [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/#MenuLayer) |
| |
| c | [MenuLayerGetNumberOfSectionsCallback](/docs/c/User_Interface/Layers/MenuLayer/#MenuLayerGetNumberOfSectionsCallback) |
| 

Function signature for the callback to get the number of sections in a menu.

 |
| c | [MenuLayerGetNumberOfRowsInSectionsCallback](/docs/c/User_Interface/Layers/MenuLayer/#MenuLayerGetNumberOfRowsInSectionsCallback) |
| 

Function signature for the callback to get the number of rows in a given section in a menu.

 |
| c | [MenuLayerGetCellHeightCallback](/docs/c/User_Interface/Layers/MenuLayer/#MenuLayerGetCellHeightCallback) |
| 

Function signature for the callback to get the height of the menu cell at a given index.

 |
| c | [MenuLayerGetHeaderHeightCallback](/docs/c/User_Interface/Layers/MenuLayer/#MenuLayerGetHeaderHeightCallback) |
| 

Function signature for the callback to get the height of the section header at a given section index.

 |
| c | [MenuLayerGetSeparatorHeightCallback](/docs/c/User_Interface/Layers/MenuLayer/#MenuLayerGetSeparatorHeightCallback) |
| 

Function signature for the callback to get the height of the separator at a given index.

 |
| c | [MenuLayerDrawRowCallback](/docs/c/User_Interface/Layers/MenuLayer/#MenuLayerDrawRowCallback) |
| 

Function signature for the callback to render the menu cell at a given [MenuIndex](/docs/c/User_Interface/Layers/MenuLayer/#MenuIndex).

 |
| c | [MenuLayerDrawHeaderCallback](/docs/c/User_Interface/Layers/MenuLayer/#MenuLayerDrawHeaderCallback) |
| 

Function signature for the callback to render the section header at a given section index.

 |
| c | [MenuLayerDrawSeparatorCallback](/docs/c/User_Interface/Layers/MenuLayer/#MenuLayerDrawSeparatorCallback) |
| 

Function signature for the callback to render the separator at a given [MenuIndex](/docs/c/User_Interface/Layers/MenuLayer/#MenuIndex).

 |
| c | [MenuLayerSelectCallback](/docs/c/User_Interface/Layers/MenuLayer/#MenuLayerSelectCallback) |
| 

Function signature for the callback to handle the event that a user hits the SELECT button.

 |
| c | [MenuLayerSelectionChangedCallback](/docs/c/User_Interface/Layers/MenuLayer/#MenuLayerSelectionChangedCallback) |
| 

Function signature for the callback to handle a change in the current selected item in the menu.

 |
| c | [MenuLayerSelectionWillChangeCallback](/docs/c/User_Interface/Layers/MenuLayer/#MenuLayerSelectionWillChangeCallback) |
| 

Function signature for the callback which allows or changes selection behavior of the menu. In order to change the cell that should be selected, modify the passed in new\_index. Preventing the selection from changing, new\_index can be assigned the value of old\_index.

 |
| c | [MenuLayerDrawBackgroundCallback](/docs/c/User_Interface/Layers/MenuLayer/#MenuLayerDrawBackgroundCallback) |
| 

Function signature for the callback which draws the menu's background. The background is underneath the cells of the menu, and is visible in the padding below the bottom cell, or if a cell's background color is set to GColorClear.

 |
| c | [menu\_layer\_create](/docs/c/User_Interface/Layers/MenuLayer/#menu_layer_create) |
| 

Creates a new [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/) on the heap and initalizes it with the default values.

 |
| c | [menu\_layer\_destroy](/docs/c/User_Interface/Layers/MenuLayer/#menu_layer_destroy) |
| 

Destroys a [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/) previously created by menu\_layer\_create.

 |
| c | [menu\_layer\_get\_layer](/docs/c/User_Interface/Layers/MenuLayer/#menu_layer_get_layer) |
| 

Gets the "root" Layer of the [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/), which is the parent for the sub- layers used for its implementation.

 |
| c | [menu\_layer\_get\_scroll\_layer](/docs/c/User_Interface/Layers/MenuLayer/#menu_layer_get_scroll_layer) |
| 

Gets the ScrollLayer of the [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/), which is the layer responsible for the scrolling of the [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/).

 |
| c | [menu\_layer\_set\_callbacks](/docs/c/User_Interface/Layers/MenuLayer/#menu_layer_set_callbacks) |
| 

Sets the callbacks for the MenuLayer.

 |
| c | [menu\_layer\_set\_click\_config\_onto\_window](/docs/c/User_Interface/Layers/MenuLayer/#menu_layer_set_click_config_onto_window) |
| 

Convenience function to set the [ClickConfigProvider](/docs/c/User_Interface/Clicks/#ClickConfigProvider) callback on the given window to the [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/) internal click config provider. This internal click configuration provider, will set up the default UP & DOWN scrolling / menu item selection behavior. This function calls [scroll\_layer\_set\_click\_config\_onto\_window](/docs/c/User_Interface/Layers/ScrollLayer/#scroll_layer_set_click_config_onto_window) to accomplish this.

 |
| c | [MenuRowAlign](/docs/c/User_Interface/Layers/MenuLayer/#MenuRowAlign) |
| 

Values to specify how a (selected) row should be aligned relative to the visible area of the [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/).

 |
| c | [MenuRowAlignNone](/docs/c/User_Interface/Layers/MenuLayer/#MenuRowAlignNone) |
| 

Don't align or update the scroll offset of the [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/).

 |
| c | [MenuRowAlignCenter](/docs/c/User_Interface/Layers/MenuLayer/#MenuRowAlignCenter) |
| 

Scroll the contents of the [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/) in such way that the selected row is centered relative to the visible area.

 |
| c | [MenuRowAlignTop](/docs/c/User_Interface/Layers/MenuLayer/#MenuRowAlignTop) |
| 

Scroll the contents of the [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/) in such way that the selected row is at the top of the visible area.

 |
| c | [MenuRowAlignBottom](/docs/c/User_Interface/Layers/MenuLayer/#MenuRowAlignBottom) |
| 

Scroll the contents of the [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/) in such way that the selected row is at the bottom of the visible area.

 |
| c | [menu\_layer\_set\_selected\_next](/docs/c/User_Interface/Layers/MenuLayer/#menu_layer_set_selected_next) |
| 

Selects the next or previous item, relative to the current selection.

 |
| c | [menu\_layer\_set\_selected\_index](/docs/c/User_Interface/Layers/MenuLayer/#menu_layer_set_selected_index) |
| 

Selects the item with given [MenuIndex](/docs/c/User_Interface/Layers/MenuLayer/#MenuIndex).

 |
| c | [menu\_layer\_get\_selected\_index](/docs/c/User_Interface/Layers/MenuLayer/#menu_layer_get_selected_index) |
| 

Gets the [MenuIndex](/docs/c/User_Interface/Layers/MenuLayer/#MenuIndex) of the currently selected menu item.

 |
| c | [menu\_layer\_reload\_data](/docs/c/User_Interface/Layers/MenuLayer/#menu_layer_reload_data) |
| 

Reloads the data of the menu. This causes the menu to re-request the menu item data, by calling the relevant callbacks. The current selection and scroll position will not be changed. See the note with [menu\_layer\_set\_selected\_index()](/docs/c/User_Interface/Layers/MenuLayer/#menu_layer_set_selected_index) for the behavior if the old selection is no longer valid.

 |
| c | [menu\_cell\_layer\_is\_highlighted](/docs/c/User_Interface/Layers/MenuLayer/#menu_cell_layer_is_highlighted) |
| 

Returns whether or not the given cell layer is highlighted. Using this for determining highlight behaviour is preferable to using [menu\_layer\_get\_selected\_index](/docs/c/User_Interface/Layers/MenuLayer/#menu_layer_get_selected_index). Row drawing callbacks may be invoked multiple times with a different highlight status on the same cell in order to handle partially highlighted cells during animation.

 |
| c | [menu\_layer\_set\_normal\_colors](/docs/c/User_Interface/Layers/MenuLayer/#menu_layer_set_normal_colors) |
| 

Set the default colors to be used for cells when it is in a normal state (not highlighted). The GContext's text and fill colors will be set appropriately prior to calling the `.draw_row` callback. If this function is not explicitly called on a [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/), it will default to white background with black foreground.

 |
| c | [menu\_layer\_set\_highlight\_colors](/docs/c/User_Interface/Layers/MenuLayer/#menu_layer_set_highlight_colors) |
| 

Set the default colors to be used for cells when it is in a highlighted state. The GContext's text and fill colors will be set appropriately prior to calling the `.draw_row` callback. If this function is not explicitly called on a [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/), it will default to black background with white foreground.

 |
| c | [menu\_layer\_pad\_bottom\_enable](/docs/c/User_Interface/Layers/MenuLayer/#menu_layer_pad_bottom_enable) |
| 

This enables or disables padding at the bottom of the [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/). Padding at the bottom of the layer keeps the bottom item from being at the very bottom of the screen. Padding is turned on by default for all MenuLayers. The color of the padded area will be the background color set using [menu\_layer\_set\_normal\_colors()](/docs/c/User_Interface/Layers/MenuLayer/#menu_layer_set_normal_colors). To color the padding a different color, use [MenuLayerDrawBackgroundCallback](/docs/c/User_Interface/Layers/MenuLayer/#MenuLayerDrawBackgroundCallback).

 |
| c | [menu\_layer\_get\_center\_focused](/docs/c/User_Interface/Layers/MenuLayer/#menu_layer_get_center_focused) |
| 

True, if the [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/) generally scrolls such that the selected row is in the center.

 |
| c | [menu\_layer\_set\_center\_focused](/docs/c/User_Interface/Layers/MenuLayer/#menu_layer_set_center_focused) |
| 

Controls if the [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/) generally scrolls such that the selected row is in the center. For platforms with a round display (PBL\_ROUND) the default is true, otherwise false is the default.

 |
| c | [menu\_layer\_is\_index\_selected](/docs/c/User_Interface/Layers/MenuLayer/#menu_layer_is_index_selected) |
| 

Returns whether or not the specified cell index is currently selected.

 |
| c | [MENU\_CELL\_ROUND\_FOCUSED\_SHORT\_CELL\_HEIGHT](/docs/c/User_Interface/Layers/MenuLayer/#MENU_CELL_ROUND_FOCUSED_SHORT_CELL_HEIGHT) |
| 

Constant value representing [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/) short cell height when this item is the selected item on a round display.

 |
| c | [MENU\_CELL\_ROUND\_UNFOCUSED\_SHORT\_CELL\_HEIGHT](/docs/c/User_Interface/Layers/MenuLayer/#MENU_CELL_ROUND_UNFOCUSED_SHORT_CELL_HEIGHT) |
| 

Constant value representing [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/) short cell height when this item is not the selected item on a round display.

 |
| c | [MENU\_CELL\_ROUND\_FOCUSED\_TALL\_CELL\_HEIGHT](/docs/c/User_Interface/Layers/MenuLayer/#MENU_CELL_ROUND_FOCUSED_TALL_CELL_HEIGHT) |
| 

Constant value representing [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/) tall cell height when this item is the selected item on a round display.

 |
| c | [MENU\_CELL\_ROUND\_UNFOCUSED\_TALL\_CELL\_HEIGHT](/docs/c/User_Interface/Layers/MenuLayer/#MENU_CELL_ROUND_UNFOCUSED_TALL_CELL_HEIGHT) |
| 

Constant value representing [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/) tall cell height when this item is not the selected item on a round display.

 |
| c | [MenuCellSpan](/docs/c/User_Interface/Layers/MenuLayer/#MenuCellSpan) |
| |
| c | [MenuIndex](/docs/c/User_Interface/Layers/MenuLayer/#MenuIndex) |
| 

Data structure to represent an menu item's position in a menu, by specifying the section index and the row index within that section.

 |
| c | [MenuLayerCallbacks](/docs/c/User_Interface/Layers/MenuLayer/#MenuLayerCallbacks) |
| 

Data structure containing all the callbacks of a [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/).

 |
| c | [RotBitmapLayer](/docs/c/User_Interface/Layers/RotBitmapLayer/) |
| 

Layer that displays a rotated bitmap image.

 |
| c | [RotBitmapLayer](/docs/c/User_Interface/Layers/RotBitmapLayer/#RotBitmapLayer) |
| |
| c | [rot\_bitmap\_layer\_create](/docs/c/User_Interface/Layers/RotBitmapLayer/#rot_bitmap_layer_create) |
| 

Creates a new RotBitmapLayer on the heap and initializes it with the default values:

 |
| c | [rot\_bitmap\_layer\_destroy](/docs/c/User_Interface/Layers/RotBitmapLayer/#rot_bitmap_layer_destroy) |
| 

Destroys a RotBitmapLayer and frees all associated memory.

 |
| c | [rot\_bitmap\_layer\_set\_corner\_clip\_color](/docs/c/User_Interface/Layers/RotBitmapLayer/#rot_bitmap_layer_set_corner_clip_color) |
| 

Defines what color to use in areas that are not covered by the source bitmap. By default this is GColorClear.

 |
| c | [rot\_bitmap\_layer\_set\_angle](/docs/c/User_Interface/Layers/RotBitmapLayer/#rot_bitmap_layer_set_angle) |
| 

Sets the rotation angle of this RotBitmapLayer.

 |
| c | [rot\_bitmap\_layer\_increment\_angle](/docs/c/User_Interface/Layers/RotBitmapLayer/#rot_bitmap_layer_increment_angle) |
| 

Change the rotation angle of this RotBitmapLayer.

 |
| c | [rot\_bitmap\_set\_src\_ic](/docs/c/User_Interface/Layers/RotBitmapLayer/#rot_bitmap_set_src_ic) |
| 

Defines the only point that will not be affected by the rotation in the source bitmap.

 |
| c | [rot\_bitmap\_set\_compositing\_mode](/docs/c/User_Interface/Layers/RotBitmapLayer/#rot_bitmap_set_compositing_mode) |
| 

Sets the compositing mode of how the bitmap image is composited onto what has been drawn beneath the RotBitmapLayer. By default this is GCompOpAssign, i.e. transparency disabled. The RotBitmapLayer is automatically marked dirty after this operation.

 |
| c | [rot\_bitmap\_layer\_get\_layer](/docs/c/User_Interface/Layers/RotBitmapLayer/#rot_bitmap_layer_get_layer) |
| 

Gets the "root" Layer of the RotBitmapLayer, which is the parent for the sub- layers used for its implementation.

 |
| c | [ScrollLayer](/docs/c/User_Interface/Layers/ScrollLayer/) |
| 

Layer that scrolls its contents, animated.

 |
| c | [ScrollLayer](/docs/c/User_Interface/Layers/ScrollLayer/#ScrollLayer) |
| |
| c | [ScrollLayerCallback](/docs/c/User_Interface/Layers/ScrollLayer/#ScrollLayerCallback) |
| 

Function signature for the `.content_offset_changed_handler` callback.

 |
| c | [scroll\_layer\_create](/docs/c/User_Interface/Layers/ScrollLayer/#scroll_layer_create) |
| 

Creates a new ScrollLayer on the heap and initalizes it with the default values:

 |
| c | [scroll\_layer\_destroy](/docs/c/User_Interface/Layers/ScrollLayer/#scroll_layer_destroy) |
| 

Destroys a ScrollLayer previously created by scroll\_layer\_create.

 |
| c | [scroll\_layer\_get\_layer](/docs/c/User_Interface/Layers/ScrollLayer/#scroll_layer_get_layer) |
| 

Gets the "root" Layer of the scroll layer, which is the parent for the sub- layers used for its implementation.

 |
| c | [scroll\_layer\_add\_child](/docs/c/User_Interface/Layers/ScrollLayer/#scroll_layer_add_child) |
| 

Adds the child layer to the content sub-layer of the ScrollLayer. This will make the child layer part of the scrollable contents. The content sub-layer of the ScrollLayer will become the parent of the child layer.

 |
| c | [scroll\_layer\_set\_click\_config\_onto\_window](/docs/c/User_Interface/Layers/ScrollLayer/#scroll_layer_set_click_config_onto_window) |
| 

Convenience function to set the [ClickConfigProvider](/docs/c/User_Interface/Clicks/#ClickConfigProvider) callback on the given window to scroll layer's internal click config provider. This internal click configuration provider, will set up the default UP & DOWN scrolling behavior. This function calls [window\_set\_click\_config\_provider\_with\_context](/docs/c/User_Interface/Window/#window_set_click_config_provider_with_context) to accomplish this.

 |
| c | [scroll\_layer\_set\_callbacks](/docs/c/User_Interface/Layers/ScrollLayer/#scroll_layer_set_callbacks) |
| 

Sets the callbacks that the scroll layer exposes. The `context` as set by [scroll\_layer\_set\_context()](/docs/c/User_Interface/Layers/ScrollLayer/#scroll_layer_set_context) is passed into each of the callbacks. See [ScrollLayerCallbacks](/docs/c/User_Interface/Layers/ScrollLayer/#ScrollLayerCallbacks) for the different callbacks.

 |
| c | [scroll\_layer\_set\_context](/docs/c/User_Interface/Layers/ScrollLayer/#scroll_layer_set_context) |
| 

Sets a new callback context. This context is passed into the scroll layer's callbacks and also the [ClickHandler](/docs/c/User_Interface/Clicks/#ClickHandler) for the SELECT button. If `NULL` or not set, the context defaults to a pointer to the ScrollLayer itself.

 |
| c | [scroll\_layer\_set\_content\_offset](/docs/c/User_Interface/Layers/ScrollLayer/#scroll_layer_set_content_offset) |
| 

Scrolls to the given offset, optionally animated.

 |
| c | [scroll\_layer\_get\_content\_offset](/docs/c/User_Interface/Layers/ScrollLayer/#scroll_layer_get_content_offset) |
| 

Gets the point by which the contents are offset.

 |
| c | [scroll\_layer\_set\_content\_size](/docs/c/User_Interface/Layers/ScrollLayer/#scroll_layer_set_content_size) |
| 

Sets the size of the contents layer. This determines the area that is scrollable. At the moment, this needs to be set "manually" and is not derived from the geometry of the contents layers.

 |
| c | [scroll\_layer\_get\_content\_size](/docs/c/User_Interface/Layers/ScrollLayer/#scroll_layer_get_content_size) |
| 

Gets the size of the contents layer.

 |
| c | [scroll\_layer\_set\_frame](/docs/c/User_Interface/Layers/ScrollLayer/#scroll_layer_set_frame) |
| 

Set the frame of the scroll layer and adjusts the internal layers' geometry accordingly. The scroll layer is marked dirty automatically.

 |
| c | [scroll\_layer\_scroll\_up\_click\_handler](/docs/c/User_Interface/Layers/ScrollLayer/#scroll_layer_scroll_up_click_handler) |
| 

The click handlers for the UP button that the scroll layer will install as part of [scroll\_layer\_set\_click\_config\_onto\_window()](/docs/c/User_Interface/Layers/ScrollLayer/#scroll_layer_set_click_config_onto_window).

 |
| c | [scroll\_layer\_scroll\_down\_click\_handler](/docs/c/User_Interface/Layers/ScrollLayer/#scroll_layer_scroll_down_click_handler) |
| 

The click handlers for the DOWN button that the scroll layer will install as part of [scroll\_layer\_set\_click\_config\_onto\_window()](/docs/c/User_Interface/Layers/ScrollLayer/#scroll_layer_set_click_config_onto_window).

 |
| c | [scroll\_layer\_set\_shadow\_hidden](/docs/c/User_Interface/Layers/ScrollLayer/#scroll_layer_set_shadow_hidden) |
| 

Sets the visibility of the scroll layer shadow. If the visibility has changed, [layer\_mark\_dirty()](/docs/c/User_Interface/Layers/#layer_mark_dirty) will be called automatically on the scroll layer.

 |
| c | [scroll\_layer\_get\_shadow\_hidden](/docs/c/User_Interface/Layers/ScrollLayer/#scroll_layer_get_shadow_hidden) |
| 

Gets the visibility of the scroll layer shadow.

 |
| c | [scroll\_layer\_set\_paging](/docs/c/User_Interface/Layers/ScrollLayer/#scroll_layer_set_paging) |
| 

Enables or disables paging of the ScrollLayer (default: disabled). When enabled, every button press will change the scroll offset by the frame's height.

 |
| c | [scroll\_layer\_get\_paging](/docs/c/User_Interface/Layers/ScrollLayer/#scroll_layer_get_paging) |
| 

Check whether or not the ScrollLayer uses paging when pressing buttons.

 |
| c | [ContentIndicator](/docs/c/User_Interface/Layers/ScrollLayer/#ContentIndicator) |
| |
| c | [scroll\_layer\_get\_content\_indicator](/docs/c/User_Interface/Layers/ScrollLayer/#scroll_layer_get_content_indicator) |
| 

Gets the ContentIndicator for a ScrollLayer.

 |
| c | [ContentIndicatorDirection](/docs/c/User_Interface/Layers/ScrollLayer/#ContentIndicatorDirection) |
| 

Value to describe directions for ContentIndicator.

 |
| c | [ContentIndicatorDirectionUp](/docs/c/User_Interface/Layers/ScrollLayer/#ContentIndicatorDirectionUp) |
| 

The up direction.

 |
| c | [ContentIndicatorDirectionDown](/docs/c/User_Interface/Layers/ScrollLayer/#ContentIndicatorDirectionDown) |
| 

The down direction.

 |
| c | [NumContentIndicatorDirections](/docs/c/User_Interface/Layers/ScrollLayer/#NumContentIndicatorDirections) |
| 

The number of supported directions.

 |
| c | [content\_indicator\_create](/docs/c/User_Interface/Layers/ScrollLayer/#content_indicator_create) |
| 

Creates a ContentIndicator on the heap.

 |
| c | [content\_indicator\_destroy](/docs/c/User_Interface/Layers/ScrollLayer/#content_indicator_destroy) |
| 

Destroys a ContentIndicator previously created using [content\_indicator\_create()](/docs/c/User_Interface/Layers/ScrollLayer/#content_indicator_create).

 |
| c | [content\_indicator\_configure\_direction](/docs/c/User_Interface/Layers/ScrollLayer/#content_indicator_configure_direction) |
| 

Configures a ContentIndicator for the given direction.

 |
| c | [content\_indicator\_get\_content\_available](/docs/c/User_Interface/Layers/ScrollLayer/#content_indicator_get_content_available) |
| 

Retrieves the availability status of content in the given direction.

 |
| c | [content\_indicator\_set\_content\_available](/docs/c/User_Interface/Layers/ScrollLayer/#content_indicator_set_content_available) |
| 

Sets the availability status of content in the given direction.

 |
| c | [ContentIndicatorConfig](/docs/c/User_Interface/Layers/ScrollLayer/#ContentIndicatorConfig) |
| 

Struct used to configure directions for ContentIndicator.

 |
| c | [ScrollLayerCallbacks](/docs/c/User_Interface/Layers/ScrollLayer/#ScrollLayerCallbacks) |
| 

All the callbacks that the ScrollLayer exposes for use by applications.

 |
| c | [SimpleMenuLayer](/docs/c/User_Interface/Layers/SimpleMenuLayer/) |
| 

Wrapper around [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/), that uses static data to display a list menu.

 |
| c | [SimpleMenuLayer](/docs/c/User_Interface/Layers/SimpleMenuLayer/#SimpleMenuLayer) |
| |
| c | [SimpleMenuLayerSelectCallback](/docs/c/User_Interface/Layers/SimpleMenuLayer/#SimpleMenuLayerSelectCallback) |
| 

Function signature for the callback to handle the event that a user hits the SELECT button.

 |
| c | [simple\_menu\_layer\_create](/docs/c/User_Interface/Layers/SimpleMenuLayer/#simple_menu_layer_create) |
| 

Creates a new SimpleMenuLayer on the heap and initializes it. It also sets the internal click configuration provider onto given window.

 |
| c | [simple\_menu\_layer\_destroy](/docs/c/User_Interface/Layers/SimpleMenuLayer/#simple_menu_layer_destroy) |
| 

Destroys a SimpleMenuLayer previously created by simple\_menu\_layer\_create.

 |
| c | [simple\_menu\_layer\_get\_layer](/docs/c/User_Interface/Layers/SimpleMenuLayer/#simple_menu_layer_get_layer) |
| 

Gets the "root" Layer of the simple menu layer, which is the parent for the sub-layers used for its implementation.

 |
| c | [simple\_menu\_layer\_get\_selected\_index](/docs/c/User_Interface/Layers/SimpleMenuLayer/#simple_menu_layer_get_selected_index) |
| 

Gets the row index of the currently selection menu item.

 |
| c | [simple\_menu\_layer\_set\_selected\_index](/docs/c/User_Interface/Layers/SimpleMenuLayer/#simple_menu_layer_set_selected_index) |
| 

Selects the item in the first section at given row index.

 |
| c | [simple\_menu\_layer\_get\_menu\_layer](/docs/c/User_Interface/Layers/SimpleMenuLayer/#simple_menu_layer_get_menu_layer) |
| |
| c | [SimpleMenuItem](/docs/c/User_Interface/Layers/SimpleMenuLayer/#SimpleMenuItem) |
| 

Data structure containing the information of a menu item.

 |
| c | [SimpleMenuSection](/docs/c/User_Interface/Layers/SimpleMenuLayer/#SimpleMenuSection) |
| 

Data structure containing the information of a menu section.

 |
| c | [StatusBarLayer](/docs/c/User_Interface/Layers/StatusBarLayer/) |
| 

Layer that serves as a configurable status bar.

 |
| c | [StatusBarLayer](/docs/c/User_Interface/Layers/StatusBarLayer/#StatusBarLayer) |
| |
| c | [StatusBarLayerSeparatorMode](/docs/c/User_Interface/Layers/StatusBarLayer/#StatusBarLayerSeparatorMode) |
| 

Values that are used to indicate the different status bar separator modes.

 |
| c | [StatusBarLayerSeparatorModeNone](/docs/c/User_Interface/Layers/StatusBarLayer/#StatusBarLayerSeparatorModeNone) |
| 

The default mode. No separator will be shown.

 |
| c | [StatusBarLayerSeparatorModeDotted](/docs/c/User_Interface/Layers/StatusBarLayer/#StatusBarLayerSeparatorModeDotted) |
| 

A dotted separator at the bottom of the status bar.

 |
| c | [STATUS\_BAR\_LAYER\_HEIGHT](/docs/c/User_Interface/Layers/StatusBarLayer/#STATUS_BAR_LAYER_HEIGHT) |
| 

The fixed height of the status bar, including separator height.

 |
| c | [\_STATUS\_BAR\_LAYER\_HEIGHT](/docs/c/User_Interface/Layers/StatusBarLayer/#_STATUS_BAR_LAYER_HEIGHT) |
| 

The fixed height of the status bar, including separator height, for all platforms.

 |
| c | [status\_bar\_layer\_create](/docs/c/User_Interface/Layers/StatusBarLayer/#status_bar_layer_create) |
| 

Creates a new StatusBarLayer on the heap and initializes it with the default values.

 |
| c | [status\_bar\_layer\_destroy](/docs/c/User_Interface/Layers/StatusBarLayer/#status_bar_layer_destroy) |
| 

Destroys a StatusBarLayer previously created by status\_bar\_layer\_create.

 |
| c | [status\_bar\_layer\_get\_layer](/docs/c/User_Interface/Layers/StatusBarLayer/#status_bar_layer_get_layer) |
| 

Gets the "root" Layer of the status bar, which is the parent for the sub- layers used for its implementation.

 |
| c | [status\_bar\_layer\_get\_background\_color](/docs/c/User_Interface/Layers/StatusBarLayer/#status_bar_layer_get_background_color) |
| 

Gets background color of StatusBarLayer.

 |
| c | [status\_bar\_layer\_get\_foreground\_color](/docs/c/User_Interface/Layers/StatusBarLayer/#status_bar_layer_get_foreground_color) |
| 

Gets foreground color of StatusBarLayer.

 |
| c | [status\_bar\_layer\_set\_colors](/docs/c/User_Interface/Layers/StatusBarLayer/#status_bar_layer_set_colors) |
| 

Sets the background and foreground colors of StatusBarLayer.

 |
| c | [status\_bar\_layer\_set\_separator\_mode](/docs/c/User_Interface/Layers/StatusBarLayer/#status_bar_layer_set_separator_mode) |
| 

Sets the mode of the StatusBarLayer separator, to help divide it from content.

 |
| c | [TextLayer](/docs/c/User_Interface/Layers/TextLayer/) |
| 

Layer that displays and formats a text string.

 |
| c | [TextLayer](/docs/c/User_Interface/Layers/TextLayer/#TextLayer) |
| |
| c | [text\_layer\_create](/docs/c/User_Interface/Layers/TextLayer/#text_layer_create) |
| 

Creates a new TextLayer on the heap and initializes it with the default values.

 |
| c | [text\_layer\_destroy](/docs/c/User_Interface/Layers/TextLayer/#text_layer_destroy) |
| 

Destroys a TextLayer previously created by text\_layer\_create.

 |
| c | [text\_layer\_get\_layer](/docs/c/User_Interface/Layers/TextLayer/#text_layer_get_layer) |
| 

Gets the "root" Layer of the text layer, which is the parent for the sub- layers used for its implementation.

 |
| c | [text\_layer\_set\_text](/docs/c/User_Interface/Layers/TextLayer/#text_layer_set_text) |
| 

Sets the pointer to the string where the TextLayer is supposed to find the text at a later point in time, when it needs to draw itself.

 |
| c | [text\_layer\_get\_text](/docs/c/User_Interface/Layers/TextLayer/#text_layer_get_text) |
| 

Gets the pointer to the string that the TextLayer is using.

 |
| c | [text\_layer\_set\_background\_color](/docs/c/User_Interface/Layers/TextLayer/#text_layer_set_background_color) |
| 

Sets the background color of the bounding box that will be drawn behind the text.

 |
| c | [text\_layer\_set\_text\_color](/docs/c/User_Interface/Layers/TextLayer/#text_layer_set_text_color) |
| 

Sets the color of text that will be drawn.

 |
| c | [text\_layer\_set\_overflow\_mode](/docs/c/User_Interface/Layers/TextLayer/#text_layer_set_overflow_mode) |
| 

Sets the line break mode of the TextLayer.

 |
| c | [text\_layer\_set\_font](/docs/c/User_Interface/Layers/TextLayer/#text_layer_set_font) |
| 

Sets the font of the TextLayer.

 |
| c | [text\_layer\_set\_text\_alignment](/docs/c/User_Interface/Layers/TextLayer/#text_layer_set_text_alignment) |
| 

Sets the alignment of the TextLayer.

 |
| c | [text\_layer\_enable\_screen\_text\_flow\_and\_paging](/docs/c/User_Interface/Layers/TextLayer/#text_layer_enable_screen_text_flow_and_paging) |
| 

Enables text flow following the boundaries of the screen and pagination that introduces extra line spacing at page breaks to avoid partially clipped lines for the TextLayer. If the TextLayer is part of a [ScrollLayer](/docs/c/User_Interface/Layers/ScrollLayer/) the ScrollLayer's frame will be used to configure paging.

 |
| c | [text\_layer\_restore\_default\_text\_flow\_and\_paging](/docs/c/User_Interface/Layers/TextLayer/#text_layer_restore_default_text_flow_and_paging) |
| 

Restores text flow and paging for the TextLayer to the rectangular defaults.

 |
| c | [text\_layer\_get\_content\_size](/docs/c/User_Interface/Layers/TextLayer/#text_layer_get_content_size) |
| 

Calculates the size occupied by the current text of the TextLayer.

 |
| c | [text\_layer\_set\_size](/docs/c/User_Interface/Layers/TextLayer/#text_layer_set_size) |
| 

Update the size of the text layer This is a convenience function to update the frame of the TextLayer.

 |
| c | [Light](/docs/c/User_Interface/Light/) |
| 

Controlling Pebble's backlight

 |
| c | [light\_enable\_interaction](/docs/c/User_Interface/Light/#light_enable_interaction) |
| 

Trigger the backlight and schedule a timer to automatically disable the backlight after a short delay. This is the preferred method of interacting with the backlight.

 |
| c | [light\_enable](/docs/c/User_Interface/Light/#light_enable) |
| 

Turn the watch's backlight on or put it back into automatic control. Developers should take care when calling this function, keeping Pebble's backlight on for long periods of time will rapidly deplete the battery.

 |
| c | [light\_is\_on](/docs/c/User_Interface/Light/#light_is_on) |
| |
| c | [light\_set\_color](/docs/c/User_Interface/Light/#light_set_color) |
| 

Tint the backlight LED to the given color. The color persists while the app is foregrounded and is automatically reset to the user's default (white) when the app exits or is preempted by a system notification. On platforms without a color backlight this is a no-op.

 |
| c | [light\_set\_color\_rgb888](/docs/c/User_Interface/Light/#light_set_color_rgb888) |
| 

Tint the backlight LED to a packed 24-bit RGB value (0x00RRGGBB). Same persistence semantics as [light\_set\_color()](/docs/c/User_Interface/Light/#light_set_color): the override lasts while the app is foregrounded and is reset on app exit or system preempt. No-op on platforms without a color backlight.

 |
| c | [light\_set\_system\_color](/docs/c/User_Interface/Light/#light_set_system_color) |
| 

Restore the backlight to the user's default color. Rarely needed — the system resets automatically on app exit. No-op on platforms without a color backlight.

 |
| c | [Preferences](/docs/c/User_Interface/Preferences/) |
| |
| c | [preferred\_result\_display\_duration](/docs/c/User_Interface/Preferences/#preferred_result_display_duration) |
| 

Get the recommended amount of milliseconds a result window should be visible before it should automatically close.

 |
| c | [PreferredContentSize](/docs/c/User_Interface/Preferences/#PreferredContentSize) |
| 

[PreferredContentSize](/docs/c/User_Interface/Preferences/#PreferredContentSize) represents the display scale of all the app's UI components. The enum contains all sizes that all platforms as a whole are capable of displaying, but each individual platform may not be able to display all sizes.

 |
| c | [PreferredContentSizeSmall](/docs/c/User_Interface/Preferences/#PreferredContentSizeSmall) |
| |
| c | [PreferredContentSizeMedium](/docs/c/User_Interface/Preferences/#PreferredContentSizeMedium) |
| |
| c | [PreferredContentSizeLarge](/docs/c/User_Interface/Preferences/#PreferredContentSizeLarge) |
| |
| c | [PreferredContentSizeExtraLarge](/docs/c/User_Interface/Preferences/#PreferredContentSizeExtraLarge) |
| |
| c | [NumPreferredContentSizes](/docs/c/User_Interface/Preferences/#NumPreferredContentSizes) |
| |
| c | [preferred\_content\_size](/docs/c/User_Interface/Preferences/#preferred_content_size) |
| 

Returns the user's preferred content size representing the scale of all the app's UI components should use for display.

 |
| c | [quiet\_time\_is\_active](/docs/c/User_Interface/Preferences/#quiet_time_is_active) |
| 

Users can toggle Quiet Time manually or on schedule. Watchfaces and apps should respect this choice and avoid disturbing actions such as vibration if quiet time is active.

 |
| c | [Speaker](/docs/c/User_Interface/Speaker/) |
| 

Controlling the speaker

 |
| c | [SpeakerWaveform](/docs/c/User_Interface/Speaker/#SpeakerWaveform) |
| |
| c | [SpeakerWaveformSine](/docs/c/User_Interface/Speaker/#SpeakerWaveformSine) |
| |
| c | [SpeakerWaveformSquare](/docs/c/User_Interface/Speaker/#SpeakerWaveformSquare) |
| |
| c | [SpeakerWaveformTriangle](/docs/c/User_Interface/Speaker/#SpeakerWaveformTriangle) |
| |
| c | [SpeakerWaveformSawtooth](/docs/c/User_Interface/Speaker/#SpeakerWaveformSawtooth) |
| |
| c | [SpeakerWaveformCount](/docs/c/User_Interface/Speaker/#SpeakerWaveformCount) |
| |
| c | [SpeakerPcmFormat](/docs/c/User_Interface/Speaker/#SpeakerPcmFormat) |
| 

PCM audio format for speaker streaming. Bit layout: bit0 = sample rate (0=8kHz, 1=16kHz), bit1 = bit depth (0=8-bit, 1=16-bit). All formats are mono signed PCM (8-bit samples are signed [-128,127], not unsigned).

 |
| c | [SpeakerPcmFormat\_8kHz\_8bit](/docs/c/User_Interface/Speaker/#SpeakerPcmFormat_8kHz_8bit) |
| 

8kHz 8-bit signed (1 byte/sample)

 |
| c | [SpeakerPcmFormat\_16kHz\_8bit](/docs/c/User_Interface/Speaker/#SpeakerPcmFormat_16kHz_8bit) |
| 

16kHz 8-bit signed (1 byte/sample)

 |
| c | [SpeakerPcmFormat\_8kHz\_16bit](/docs/c/User_Interface/Speaker/#SpeakerPcmFormat_8kHz_16bit) |
| 

8kHz 16-bit signed little-endian (2 bytes/sample)

 |
| c | [SpeakerPcmFormat\_16kHz\_16bit](/docs/c/User_Interface/Speaker/#SpeakerPcmFormat_16kHz_16bit) |
| 

16kHz 16-bit signed little-endian (2 bytes/sample)

 |
| c | [SpeakerPcmFormatCount](/docs/c/User_Interface/Speaker/#SpeakerPcmFormatCount) |
| |
| c | [SpeakerStatus](/docs/c/User_Interface/Speaker/#SpeakerStatus) |
| 

Speaker status.

 |
| c | [SpeakerStatusIdle](/docs/c/User_Interface/Speaker/#SpeakerStatusIdle) |
| |
| c | [SpeakerStatusPlaying](/docs/c/User_Interface/Speaker/#SpeakerStatusPlaying) |
| |
| c | [SpeakerStatusDraining](/docs/c/User_Interface/Speaker/#SpeakerStatusDraining) |
| |
| c | [SpeakerFinishReason](/docs/c/User_Interface/Speaker/#SpeakerFinishReason) |
| 

Reason reported when speaker playback ends.

 |
| c | [SpeakerFinishReasonDone](/docs/c/User_Interface/Speaker/#SpeakerFinishReasonDone) |
| 

Playback completed naturally.

 |
| c | [SpeakerFinishReasonStopped](/docs/c/User_Interface/Speaker/#SpeakerFinishReasonStopped) |
| 

Playback was stopped by the app.

 |
| c | [SpeakerFinishReasonPreempted](/docs/c/User_Interface/Speaker/#SpeakerFinishReasonPreempted) |
| 

Preempted by higher priority source.

 |
| c | [SpeakerFinishReasonError](/docs/c/User_Interface/Speaker/#SpeakerFinishReasonError) |
| 

An error occurred.

 |
| c | [SpeakerFinishedCallback](/docs/c/User_Interface/Speaker/#SpeakerFinishedCallback) |
| 

Callback invoked when playback finishes.

 |
| c | [speaker\_play\_notes](/docs/c/User_Interface/Speaker/#speaker_play_notes) |
| 

Play a sequence of notes on the speaker.

 |
| c | [speaker\_play\_tracks](/docs/c/User_Interface/Speaker/#speaker_play_tracks) |
| 

Play N monophonic tracks in parallel, mixed (polyphony).

 |
| c | [speaker\_play\_tone](/docs/c/User_Interface/Speaker/#speaker_play_tone) |
| 

Play a single tone on the speaker (convenience wrapper).

 |
| c | [speaker\_stream\_open](/docs/c/User_Interface/Speaker/#speaker_stream_open) |
| 

Open a raw PCM stream for app-generated audio.

 |
| c | [speaker\_stream\_write](/docs/c/User_Interface/Speaker/#speaker_stream_write) |
| 

Write PCM data to the open stream.

 |
| c | [speaker\_stream\_close](/docs/c/User_Interface/Speaker/#speaker_stream_close) |
| 

Close the PCM stream. Buffered data will be played before stopping.

 |
| c | [speaker\_stop](/docs/c/User_Interface/Speaker/#speaker_stop) |
| 

Stop any active speaker playback immediately.

 |
| c | [speaker\_set\_volume](/docs/c/User_Interface/Speaker/#speaker_set_volume) |
| 

Set the speaker volume.

 |
| c | [speaker\_get\_status](/docs/c/User_Interface/Speaker/#speaker_get_status) |
| 

Get the current speaker status.

 |
| c | [speaker\_set\_finish\_callback](/docs/c/User_Interface/Speaker/#speaker_set_finish_callback) |
| 

Register a callback invoked when speaker playback ends. The callback runs on the app task.

 |
| c | [SpeakerNote](/docs/c/User_Interface/Speaker/#SpeakerNote) |
| 

A single note in a sequence. midi\_note: MIDI note number (0-127, 60=C4). 0 = rest (silence). waveform: SpeakerWaveform value. duration\_ms: Note duration in ms (max 10000). velocity: Volume 0-127 (0 = use global volume).

 |
| c | [SpeakerSample](/docs/c/User_Interface/Speaker/#SpeakerSample) |
| 

A raw PCM sample that can be pitch-shifted when played by a track. data: mono signed PCM in the given format. num\_bytes: size of data in bytes. format: sample rate + bit depth (see [SpeakerPcmFormat](/docs/c/User_Interface/Speaker/#SpeakerPcmFormat)). base\_midi\_note: the MIDI note at which the sample plays unshifted (e.g. 60 = C4). Notes above/below this value are produced by resampling. loop: if true, the sample restarts from the beginning each time it runs out, and keeps playing until the owning note's duration elapses.

 |
| c | [SpeakerTrack](/docs/c/User_Interface/Speaker/#SpeakerTrack) |
| 

A single monophonic voice. Multiple tracks are mixed together by [speaker\_play\_tracks()](/docs/c/User_Interface/Speaker/#speaker_play_tracks) to produce polyphony. notes: array of notes to play sequentially. num\_notes: length of the notes array. sample: if non-NULL, notes are played by pitch-shifting this sample; note.waveform is ignored. If NULL, notes use their waveform field.

 |
| c | [UnobstructedArea](/docs/c/User_Interface/UnobstructedArea/) |
| |
| c | [UnobstructedAreaWillChangeHandler](/docs/c/User_Interface/UnobstructedArea/#UnobstructedAreaWillChangeHandler) |
| 

Handler that will be called just before the unobstructed area will begin changing.

 |
| c | [UnobstructedAreaChangeHandler](/docs/c/User_Interface/UnobstructedArea/#UnobstructedAreaChangeHandler) |
| 

Handler that will be called every time the unobstructed area changes.

 |
| c | [UnobstructedAreaDidChangeHandler](/docs/c/User_Interface/UnobstructedArea/#UnobstructedAreaDidChangeHandler) |
| 

Handler that will be called after the unobstructed area has finished changing.

 |
| c | [unobstructed\_area\_service\_subscribe](/docs/c/User_Interface/UnobstructedArea/#unobstructed_area_service_subscribe) |
| 

Subscribe to be notified when the app's unobstructed area changes. When an unobstructed area begins changing, the `will_change` handler will be called, and every `will_change` call is always paired with a `did_change` call that occurs when it is done changing given that the `will_change` and `did_change` handlers are set. When subscribing while the unobstructed area is changing, the `will_change` handler will be called after subscription in the next event loop.

 |
| c | [unobstructed\_area\_service\_unsubscribe](/docs/c/User_Interface/UnobstructedArea/#unobstructed_area_service_unsubscribe) |
| 

Unsubscribe from notifications about changes to the app's unobstructed area.

 |
| c | [UnobstructedAreaHandlers](/docs/c/User_Interface/UnobstructedArea/#UnobstructedAreaHandlers) |
| |
| c | [Vibes](/docs/c/User_Interface/Vibes/) |
| 

Controlling the vibration motor

 |
| c | [vibes\_cancel](/docs/c/User_Interface/Vibes/#vibes_cancel) |
| 

Cancel any in-flight vibe patterns; this is a no-op if there is no on-going vibe.

 |
| c | [vibes\_short\_pulse](/docs/c/User_Interface/Vibes/#vibes_short_pulse) |
| 

Makes the watch emit one short vibration.

 |
| c | [vibes\_long\_pulse](/docs/c/User_Interface/Vibes/#vibes_long_pulse) |
| 

Makes the watch emit one long vibration.

 |
| c | [vibes\_double\_pulse](/docs/c/User_Interface/Vibes/#vibes_double_pulse) |
| 

Makes the watch emit two brief vibrations.

 |
| c | [vibes\_enqueue\_custom\_pattern](/docs/c/User_Interface/Vibes/#vibes_enqueue_custom_pattern) |
| 

Makes the watch emit a 'custom' vibration pattern.

 |
| c | [VibePattern](/docs/c/User_Interface/Vibes/#VibePattern) |
| 

Data structure describing a vibration pattern.

 |
| c | [Window](/docs/c/User_Interface/Window/) |
| 

The basic building block of the user interface

 |
| c | [Window](/docs/c/User_Interface/Window/#Window) |
| |
| c | [WindowHandler](/docs/c/User_Interface/Window/#WindowHandler) |
| 

Function signature for a handler that deals with transition events of a window.

 |
| c | [window\_create](/docs/c/User_Interface/Window/#window_create) |
| 

Creates a new Window on the heap and initalizes it with the default values.

 |
| c | [window\_destroy](/docs/c/User_Interface/Window/#window_destroy) |
| 

Destroys a Window previously created by window\_create.

 |
| c | [window\_set\_click\_config\_provider](/docs/c/User_Interface/Window/#window_set_click_config_provider) |
| 

Sets the click configuration provider callback function on the window. This will automatically setup the input handlers of the window as well to use the click recognizer subsystem.

 |
| c | [window\_set\_click\_config\_provider\_with\_context](/docs/c/User_Interface/Window/#window_set_click_config_provider_with_context) |
| 

Same as [window\_set\_click\_config\_provider()](/docs/c/User_Interface/Window/#window_set_click_config_provider), but will assign a custom context pointer (instead of the window pointer) that will be passed into the [ClickHandler](/docs/c/User_Interface/Clicks/#ClickHandler) click event handlers.

 |
| c | [window\_get\_click\_config\_provider](/docs/c/User_Interface/Window/#window_get_click_config_provider) |
| 

Gets the current click configuration provider of the window.

 |
| c | [window\_get\_click\_config\_context](/docs/c/User_Interface/Window/#window_get_click_config_context) |
| 

Gets the current click configuration provider context of the window.

 |
| c | [window\_set\_window\_handlers](/docs/c/User_Interface/Window/#window_set_window_handlers) |
| 

Sets the window handlers of the window. These handlers get called e.g. when the user enters or leaves the window.

 |
| c | [window\_get\_root\_layer](/docs/c/User_Interface/Window/#window_get_root_layer) |
| 

Gets the root Layer of the window. The root layer is the layer at the bottom of the layer hierarchy for this window. It is the window's "canvas" if you will. By default, the root layer only draws a solid fill with the window's background color.

 |
| c | [window\_set\_background\_color](/docs/c/User_Interface/Window/#window_set_background_color) |
| 

Sets the background color of the window, which is drawn automatically by the root layer of the window.

 |
| c | [window\_is\_loaded](/docs/c/User_Interface/Window/#window_is_loaded) |
| 

Gets whether the window has been loaded. If a window is loaded, its `.load` handler has been called (and the `.unload` handler has not been called since).

 |
| c | [window\_set\_user\_data](/docs/c/User_Interface/Window/#window_set_user_data) |
| 

Sets a pointer to developer-supplied data that the window uses, to provide a means to access the data at later times in one of the window event handlers.

 |
| c | [window\_get\_user\_data](/docs/c/User_Interface/Window/#window_get_user_data) |
| 

Gets the pointer to developer-supplied data that was previously set using [window\_set\_user\_data()](/docs/c/User_Interface/Window/#window_set_user_data).

 |
| c | [window\_single\_click\_subscribe](/docs/c/User_Interface/Window/#window_single_click_subscribe) |
| 

Subscribe to single click events.

 |
| c | [window\_single\_repeating\_click\_subscribe](/docs/c/User_Interface/Window/#window_single_repeating_click_subscribe) |
| 

Subscribe to single click event, with a repeat interval. A single click is detected every time "repeat\_interval\_ms" has been reached.

 |
| c | [window\_multi\_click\_subscribe](/docs/c/User_Interface/Window/#window_multi_click_subscribe) |
| 

Subscribe to multi click events.

 |
| c | [window\_long\_click\_subscribe](/docs/c/User_Interface/Window/#window_long_click_subscribe) |
| 

Subscribe to long click events.

 |
| c | [window\_raw\_click\_subscribe](/docs/c/User_Interface/Window/#window_raw_click_subscribe) |
| 

Subscribe to raw click events.

 |
| c | [window\_set\_click\_context](/docs/c/User_Interface/Window/#window_set_click_context) |
| 

Set the context that will be passed to handlers for the given button's events. By default the context passed to handlers is equal to the [ClickConfigProvider](/docs/c/User_Interface/Clicks/#ClickConfigProvider) context (defaults to the window).

 |
| c | [WindowHandlers](/docs/c/User_Interface/Window/#WindowHandlers) |
| 

[WindowHandlers](/docs/c/User_Interface/Window/#WindowHandlers) These handlers are called by the [Window Stack](/docs/c/User_Interface/Window_Stack/) as windows get pushed on / popped. All these handlers use [WindowHandler](/docs/c/User_Interface/Window/#WindowHandler) as their function signature.

 |
| c | [ActionMenu](/docs/c/User_Interface/Window/ActionMenu/) |
| |
| c | [ActionMenuItem](/docs/c/User_Interface/Window/ActionMenu/#ActionMenuItem) |
| |
| c | [ActionMenuLevel](/docs/c/User_Interface/Window/ActionMenu/#ActionMenuLevel) |
| |
| c | [ActionMenuAlign](/docs/c/User_Interface/Window/ActionMenu/#ActionMenuAlign) |
| |
| c | [ActionMenuAlignTop](/docs/c/User_Interface/Window/ActionMenu/#ActionMenuAlignTop) |
| |
| c | [ActionMenuAlignCenter](/docs/c/User_Interface/Window/ActionMenu/#ActionMenuAlignCenter) |
| |
| c | [ActionMenu](/docs/c/User_Interface/Window/ActionMenu/#ActionMenu) |
| |
| c | [ActionMenuDidCloseCb](/docs/c/User_Interface/Window/ActionMenu/#ActionMenuDidCloseCb) |
| 

Callback executed after the ActionMenu has closed, so memory may be freed.

 |
| c | [ActionMenuLevelDisplayMode](/docs/c/User_Interface/Window/ActionMenu/#ActionMenuLevelDisplayMode) |
| 

enum value that controls whether menu items are displayed in a grid (similarly to the emoji replies) or in a single column (reminiscent of [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/))

 |
| c | [ActionMenuLevelDisplayModeWide](/docs/c/User_Interface/Window/ActionMenu/#ActionMenuLevelDisplayModeWide) |
| 

Each item gets its own row.

 |
| c | [ActionMenuLevelDisplayModeThin](/docs/c/User_Interface/Window/ActionMenu/#ActionMenuLevelDisplayModeThin) |
| 

Grid view: multiple items per row.

 |
| c | [ActionMenuPerformActionCb](/docs/c/User_Interface/Window/ActionMenu/#ActionMenuPerformActionCb) |
| 

Callback executed when a given action is selected.

 |
| c | [ActionMenuEachItemCb](/docs/c/User_Interface/Window/ActionMenu/#ActionMenuEachItemCb) |
| 

Callback invoked for each item in an action menu hierarchy.

 |
| c | [action\_menu\_item\_get\_label](/docs/c/User_Interface/Window/ActionMenu/#action_menu_item_get_label) |
| 

Getter for the label of a given ActionMenuItem.

 |
| c | [action\_menu\_item\_get\_action\_data](/docs/c/User_Interface/Window/ActionMenu/#action_menu_item_get_action_data) |
| 

Getter for the action\_data pointer of a given ActionMenuitem.

 |
| c | [action\_menu\_level\_create](/docs/c/User_Interface/Window/ActionMenu/#action_menu_level_create) |
| 

Create a new action menu level with storage allocated for a given number of items.

 |
| c | [action\_menu\_level\_set\_display\_mode](/docs/c/User_Interface/Window/ActionMenu/#action_menu_level_set_display_mode) |
| 

Set the action menu display mode.

 |
| c | [action\_menu\_level\_add\_action](/docs/c/User_Interface/Window/ActionMenu/#action_menu_level_add_action) |
| 

Add an action to an ActionLevel.

 |
| c | [action\_menu\_level\_add\_child](/docs/c/User_Interface/Window/ActionMenu/#action_menu_level_add_child) |
| 

Add a child to this ActionMenuLevel.

 |
| c | [action\_menu\_hierarchy\_destroy](/docs/c/User_Interface/Window/ActionMenu/#action_menu_hierarchy_destroy) |
| 

Destroy a hierarchy of ActionMenuLevels.

 |
| c | [action\_menu\_get\_context](/docs/c/User_Interface/Window/ActionMenu/#action_menu_get_context) |
| 

Get the context pointer this ActionMenu was created with.

 |
| c | [action\_menu\_get\_root\_level](/docs/c/User_Interface/Window/ActionMenu/#action_menu_get_root_level) |
| 

Get the root level of an ActionMenu.

 |
| c | [action\_menu\_open](/docs/c/User_Interface/Window/ActionMenu/#action_menu_open) |
| 

Open a new ActionMenu. The ActionMenu acts much like a window. It fills the whole screen and handles clicks.

 |
| c | [action\_menu\_freeze](/docs/c/User_Interface/Window/ActionMenu/#action_menu_freeze) |
| 

Freeze the ActionMenu. The ActionMenu will no longer respond to user input.

 |
| c | [action\_menu\_unfreeze](/docs/c/User_Interface/Window/ActionMenu/#action_menu_unfreeze) |
| 

Unfreeze the ActionMenu previously frozen with [action\_menu\_freeze](/docs/c/User_Interface/Window/ActionMenu/#action_menu_freeze).

 |
| c | [action\_menu\_set\_result\_window](/docs/c/User_Interface/Window/ActionMenu/#action_menu_set_result_window) |
| 

Set the result window for an ActionMenu. The result window will be shown when the ActionMenu closes.

 |
| c | [action\_menu\_close](/docs/c/User_Interface/Window/ActionMenu/#action_menu_close) |
| 

Close the ActionMenu, whether it is frozen or not.

 |
| c | [ActionMenuConfig](/docs/c/User_Interface/Window/ActionMenu/#ActionMenuConfig) |
| 

Configuration struct for the ActionMenu.

 |
| c | [NumberWindow](/docs/c/User_Interface/Window/NumberWindow/) |
| 

A ready-made Window prompting the user to pick a number

 |
| c | [NumberWindow](/docs/c/User_Interface/Window/NumberWindow/#NumberWindow) |
| |
| c | [NumberWindowCallback](/docs/c/User_Interface/Window/NumberWindow/#NumberWindowCallback) |
| 

Function signature for NumberWindow callbacks.

 |
| c | [number\_window\_create](/docs/c/User_Interface/Window/NumberWindow/#number_window_create) |
| 

Creates a new NumberWindow on the heap and initalizes it with the default values.

 |
| c | [number\_window\_destroy](/docs/c/User_Interface/Window/NumberWindow/#number_window_destroy) |
| 

Destroys a NumberWindow previously created by number\_window\_create.

 |
| c | [number\_window\_set\_label](/docs/c/User_Interface/Window/NumberWindow/#number_window_set_label) |
| 

Sets the text of the title or prompt label.

 |
| c | [number\_window\_set\_max](/docs/c/User_Interface/Window/NumberWindow/#number_window_set_max) |
| 

Sets the maximum value this field can hold.

 |
| c | [number\_window\_set\_min](/docs/c/User_Interface/Window/NumberWindow/#number_window_set_min) |
| 

Sets the minimum value this field can hold.

 |
| c | [number\_window\_set\_value](/docs/c/User_Interface/Window/NumberWindow/#number_window_set_value) |
| 

Sets the current value of the field.

 |
| c | [number\_window\_set\_step\_size](/docs/c/User_Interface/Window/NumberWindow/#number_window_set_step_size) |
| 

Sets the amount by which to increment/decrement by on a button click.

 |
| c | [number\_window\_get\_value](/docs/c/User_Interface/Window/NumberWindow/#number_window_get_value) |
| 

Gets the current value.

 |
| c | [number\_window\_get\_window](/docs/c/User_Interface/Window/NumberWindow/#number_window_get_window) |
| 

Gets the "root" Window of the number window.

 |
| c | [NumberWindowCallbacks](/docs/c/User_Interface/Window/NumberWindow/#NumberWindowCallbacks) |
| 

Data structure containing all the callbacks for a NumberWindow.

 |
| c | [Window Stack](/docs/c/User_Interface/Window_Stack/) |
| 

The multiple window manager

 |
| c | [window\_stack\_push](/docs/c/User_Interface/Window_Stack/#window_stack_push) |
| 

Pushes the given window on the window navigation stack, on top of the current topmost window of the app.

 |
| c | [window\_stack\_pop](/docs/c/User_Interface/Window_Stack/#window_stack_pop) |
| 

Pops the topmost window on the navigation stack.

 |
| c | [window\_stack\_pop\_all](/docs/c/User_Interface/Window_Stack/#window_stack_pop_all) |
| 

Pops all windows. See [window\_stack\_remove()](/docs/c/User_Interface/Window_Stack/#window_stack_remove) for a description of the `animated` parameter and notes.

 |
| c | [window\_stack\_remove](/docs/c/User_Interface/Window_Stack/#window_stack_remove) |
| 

Removes a given window from the window stack that belongs to the app task.

 |
| c | [window\_stack\_get\_top\_window](/docs/c/User_Interface/Window_Stack/#window_stack_get_top_window) |
| 

Gets the topmost window on the stack that belongs to the app.

 |
| c | [window\_stack\_contains\_window](/docs/c/User_Interface/Window_Stack/#window_stack_contains_window) |
| 

Checks if the window is on the window stack.

 |
| c | [Worker](/docs/c/Worker/) |
| |
| c | [worker\_event\_loop](/docs/c/Worker/#worker_event_loop) |
| 

The event loop for workers, to be used in worker's main(). Will block until the worker is ready to exit.

 |
| c | [worker\_launch\_app](/docs/c/Worker/#worker_launch_app) |
| 

Launch the foreground app for this worker.

 |
| c | [Standard C](/docs/c/Standard_C/) |
| |
| c | [uint16\_t](/docs/c/Standard_C/#uint16_t) |
| 

16-bit unsigned integer number

 |
| c | [uint32\_t](/docs/c/Standard_C/#uint32_t) |
| 

32-bit unsigned integer number

 |
| c | [Format](/docs/c/Standard_C/Format/) |
| 

Standard formatting.

 |
| c | [snprintf](/docs/c/Standard_C/Format/#snprintf) |
| 

Format a string into a buffer.

 |
| c | [Locale](/docs/c/Standard_C/Locale/) |
| 

Standard locale functions.

 |
| c | [setlocale](/docs/c/Standard_C/Locale/#setlocale) |
| 

Set the app's locale for a category of routines.

 |
| c | [Math](/docs/c/Standard_C/Math/) |
| 

Standard math functions.

 |
| c | [RAND\_MAX](/docs/c/Standard_C/Math/#RAND_MAX) |
| 

The maximum integer value [rand()](/docs/c/Standard_C/Math/#rand) may return.

 |
| c | [rand](/docs/c/Standard_C/Math/#rand) |
| 

Generate a pseudo-random integer between 0 and [RAND\_MAX](/docs/c/Standard_C/Math/#RAND_MAX) inclusive.

 |
| c | [srand](/docs/c/Standard_C/Math/#srand) |
| 

Seed the pseudo-random number generator.

 |
| c | [Memory](/docs/c/Standard_C/Memory/) |
| 

Standard memory functions.

 |
| c | [malloc](/docs/c/Standard_C/Memory/#malloc) |
| 

Allocates a requested amount of memory.

 |
| c | [calloc](/docs/c/Standard_C/Memory/#calloc) |
| 

Allocates space for count objects that are size bytes and fills the memory with bytes of value 0.

 |
| c | [realloc](/docs/c/Standard_C/Memory/#realloc) |
| 

Takes the memory allocated at ptr and changes the length of its allocation to the size specified.

 |
| c | [free](/docs/c/Standard_C/Memory/#free) |
| 

Frees previously allocated memory.

 |
| c | [size\_t](/docs/c/Standard_C/Memory/#size_t) |
| 

size as an unsigned integer

 |
| c | [memcmp](/docs/c/Standard_C/Memory/#memcmp) |
| 

Compares the first n bytes of memory regions ptr1 and ptr2.

 |
| c | [memcpy](/docs/c/Standard_C/Memory/#memcpy) |
| 

Copies n bytes from src to dest.

 |
| c | [memmove](/docs/c/Standard_C/Memory/#memmove) |
| 

Copies n bytes from src to dest by first copying to a temporary area first, allowing dest and src to potentially overlap.

 |
| c | [memset](/docs/c/Standard_C/Memory/#memset) |
| 

Sets n bytes to c starting at dest.

 |
| c | [String](/docs/c/Standard_C/String/) |
| 

Standard C-string manipulation.

 |
| c | [strcmp](/docs/c/Standard_C/String/#strcmp) |
| 

Compares the null terminated strings str1 and str2 to each other.

 |
| c | [strncmp](/docs/c/Standard_C/String/#strncmp) |
| 

Compares the null terminated strings str1 and str2 to each other for up to n bytes.

 |
| c | [strcpy](/docs/c/Standard_C/String/#strcpy) |
| 

Copies the string in src into dest and null terminates dest.

 |
| c | [strncpy](/docs/c/Standard_C/String/#strncpy) |
| 

Copies up to n bytes from the string in src into dest and null terminates dest.

 |
| c | [strcat](/docs/c/Standard_C/String/#strcat) |
| 

Concatenates the string in src to the end of the string pointed by dest and null terminates dest.

 |
| c | [strncat](/docs/c/Standard_C/String/#strncat) |
| 

Concatenates up to n bytes from the string in src to the end of the string pointed by dest and null terminates dest.

 |
| c | [strlen](/docs/c/Standard_C/String/#strlen) |
| 

Calculates the length of a null terminated string.

 |
| c | [Time](/docs/c/Standard_C/Time/) |
| |
| c | [time\_t](/docs/c/Standard_C/Time/#time_t) |
| 

time in seconds since the epoch, January 1st 1970

 |
| c | [TZ\_LEN](/docs/c/Standard_C/Time/#TZ_LEN) |
| |
| c | [SECONDS\_PER\_MINUTE](/docs/c/Standard_C/Time/#SECONDS_PER_MINUTE) |
| |
| c | [MINUTES\_PER\_HOUR](/docs/c/Standard_C/Time/#MINUTES_PER_HOUR) |
| |
| c | [SECONDS\_PER\_HOUR](/docs/c/Standard_C/Time/#SECONDS_PER_HOUR) |
| |
| c | [HOURS\_PER\_DAY](/docs/c/Standard_C/Time/#HOURS_PER_DAY) |
| |
| c | [MINUTES\_PER\_DAY](/docs/c/Standard_C/Time/#MINUTES_PER_DAY) |
| |
| c | [SECONDS\_PER\_DAY](/docs/c/Standard_C/Time/#SECONDS_PER_DAY) |
| |
| c | [strftime](/docs/c/Standard_C/Time/#strftime) |
| 

Format the time value at tm according to fmt and place the result in a buffer s of size max.

 |
| c | [localtime](/docs/c/Standard_C/Time/#localtime) |
| 

convert the time value pointed at by clock to a struct tm which contains the time adjusted for the local timezone

 |
| c | [gmtime](/docs/c/Standard_C/Time/#gmtime) |
| 

convert the time value pointed at by clock to a struct tm which contains the time expressed in Coordinated Universal Time (UTC)

 |
| c | [mktime](/docs/c/Standard_C/Time/#mktime) |
| 

convert the broken-down time structure to a timestamp expressed in Coordinated Universal Time (UTC)

 |
| c | [time](/docs/c/Standard_C/Time/#time) |
| 

Obtain the number of seconds since epoch. Note that the epoch is not adjusted for Timezones and Daylight Savings.

 |
| c | [difftime](/docs/c/Standard_C/Time/#difftime) |
| 

Obtain the number of seconds elapsed between beginning and end represented as a double.

 |
| c | [time\_ms](/docs/c/Standard_C/Time/#time_ms) |
| 

Obtain the number of seconds and milliseconds part since the epoch. This is a non-standard C function provided for convenience.

 |
| c | [time\_start\_of\_today](/docs/c/Standard_C/Time/#time_start_of_today) |
| 

Return the UTC time that corresponds to the start of today (midnight).

 |
| rockyjs | [TextMetrics](/docs/rockyjs/CanvasRenderingContext2D.md#TextMetrics) |
| |
| rockyjs | [fillStyle](/docs/rockyjs/CanvasRenderingContext2D.md#fillStyle) |
| |
| rockyjs | [Canvas](/docs/rockyjs/CanvasRenderingContext2D.md#Canvas) |
| |
| rockyjs | [strokeStyle](/docs/rockyjs/CanvasRenderingContext2D.md#strokeStyle) |
| |
| rockyjs | [canvas](/docs/rockyjs/CanvasRenderingContext2D.md#canvas) |
| |
| rockyjs | [lineWidth](/docs/rockyjs/CanvasRenderingContext2D.md#lineWidth) |
| |
| rockyjs | [font](/docs/rockyjs/CanvasRenderingContext2D.md#font) |
| |
| rockyjs | [textAlign](/docs/rockyjs/CanvasRenderingContext2D.md#textAlign) |
| |
| rockyjs | [clearRect](/docs/rockyjs/CanvasRenderingContext2D.md#clearRect) |
| |
| rockyjs | [fillRect](/docs/rockyjs/CanvasRenderingContext2D.md#fillRect) |
| |
| rockyjs | [strokeRect](/docs/rockyjs/CanvasRenderingContext2D.md#strokeRect) |
| |
| rockyjs | [fillText](/docs/rockyjs/CanvasRenderingContext2D.md#fillText) |
| |
| rockyjs | [measureText](/docs/rockyjs/CanvasRenderingContext2D.md#measureText) |
| |
| rockyjs | [beginPath](/docs/rockyjs/CanvasRenderingContext2D.md#beginPath) |
| |
| rockyjs | [closePath](/docs/rockyjs/CanvasRenderingContext2D.md#closePath) |
| |
| rockyjs | [moveTo](/docs/rockyjs/CanvasRenderingContext2D.md#moveTo) |
| |
| rockyjs | [lineTo](/docs/rockyjs/CanvasRenderingContext2D.md#lineTo) |
| |
| rockyjs | [arc](/docs/rockyjs/CanvasRenderingContext2D.md#arc) |
| |
| rockyjs | [rect](/docs/rockyjs/CanvasRenderingContext2D.md#rect) |
| |
| rockyjs | [fill](/docs/rockyjs/CanvasRenderingContext2D.md#fill) |
| |
| rockyjs | [stroke](/docs/rockyjs/CanvasRenderingContext2D.md#stroke) |
| |
| rockyjs | [save](/docs/rockyjs/CanvasRenderingContext2D.md#save) |
| |
| rockyjs | [restore](/docs/rockyjs/CanvasRenderingContext2D.md#restore) |
| |
| rockyjs | [rockyFillRadial](/docs/rockyjs/CanvasRenderingContext2D.md#rockyFillRadial) |
| |
| rockyjs | [log](/docs/rockyjs/console.md#log) |
| |
| rockyjs | [warn](/docs/rockyjs/console.md#warn) |
| |
| rockyjs | [error](/docs/rockyjs/console.md#error) |
| |
| rockyjs | [toLocaleString](/docs/rockyjs/Date.md#toLocaleString) |
| |
| rockyjs | [toLocaleTimeString](/docs/rockyjs/Date.md#toLocaleTimeString) |
| |
| rockyjs | [toLocaleDateString](/docs/rockyjs/Date.md#toLocaleDateString) |
| |
| rockyjs | [RockyPostMessageErrorCallback](/docs/rockyjs/rocky.md#RockyPostMessageErrorCallback) |
| |
| rockyjs | [RockyPostMessageConnectedCallback](/docs/rockyjs/rocky.md#RockyPostMessageConnectedCallback) |
| |
| rockyjs | [WatchInfo](/docs/rockyjs/rocky.md#WatchInfo) |
| |
| rockyjs | [watchInfo](/docs/rockyjs/rocky.md#watchInfo) |
| |
| rockyjs | [RockyMemoryPressureCallback](/docs/rockyjs/rocky.md#RockyMemoryPressureCallback) |
| |
| rockyjs | [RockyPostMessageDisconnectedCallback](/docs/rockyjs/rocky.md#RockyPostMessageDisconnectedCallback) |
| |
| rockyjs | [UserPreferences](/docs/rockyjs/rocky.md#UserPreferences) |
| |
| rockyjs | [RockyDrawCallback](/docs/rockyjs/rocky.md#RockyDrawCallback) |
| |
| rockyjs | [RockyMessageCallback](/docs/rockyjs/rocky.md#RockyMessageCallback) |
| |
| rockyjs | [RockyTickCallback](/docs/rockyjs/rocky.md#RockyTickCallback) |
| |
| rockyjs | [userPreferences](/docs/rockyjs/rocky.md#userPreferences) |
| |
| rockyjs | [on](/docs/rockyjs/rocky.md#on) |
| |
| rockyjs | [addEventListener](/docs/rockyjs/rocky.md#addEventListener) |
| |
| rockyjs | [removeEventListener](/docs/rockyjs/rocky.md#removeEventListener) |
| |
| rockyjs | [off](/docs/rockyjs/rocky.md#off) |
| |
| rockyjs | [postMessage](/docs/rockyjs/rocky.md#postMessage) |
| |
| rockyjs | [requestDraw](/docs/rockyjs/rocky.md#requestDraw) |
| |
| pebblekit\_js | [addEventListener](/docs/pebblekit-js/Pebble.md#addEventListener) |
| |
| pebblekit\_js | [on](/docs/pebblekit-js/Pebble.md#on) |
| |
| pebblekit\_js | [removeEventListener](/docs/pebblekit-js/Pebble.md#removeEventListener) |
| |
| pebblekit\_js | [off](/docs/pebblekit-js/Pebble.md#off) |
| |
| pebblekit\_js | [showSimpleNotificationOnPebble](/docs/pebblekit-js/Pebble.md#showSimpleNotificationOnPebble) |
| |
| pebblekit\_js | [sendAppMessage](/docs/pebblekit-js/Pebble.md#sendAppMessage) |
| |
| pebblekit\_js | [postMessage](/docs/pebblekit-js/Pebble.md#postMessage) |
| |
| pebblekit\_js | [getTimelineToken](/docs/pebblekit-js/Pebble.md#getTimelineToken) |
| |
| pebblekit\_js | [timelineSubscribe](/docs/pebblekit-js/Pebble.md#timelineSubscribe) |
| |
| pebblekit\_js | [timelineUnsubscribe](/docs/pebblekit-js/Pebble.md#timelineUnsubscribe) |
| |
| pebblekit\_js | [timelineSubscriptions](/docs/pebblekit-js/Pebble.md#timelineSubscriptions) |
| |
| pebblekit\_js | [getActiveWatchInfo](/docs/pebblekit-js/Pebble.md#getActiveWatchInfo) |
| |
| pebblekit\_js | [getAccountToken](/docs/pebblekit-js/Pebble.md#getAccountToken) |
| |
| pebblekit\_js | [getWatchToken](/docs/pebblekit-js/Pebble.md#getWatchToken) |
| |
| pebblekit\_js | [appGlanceReload](/docs/pebblekit-js/Pebble.md#appGlanceReload) |
| |
| pebblekit\_js | [TimelineTopicsCallback](/docs/pebblekit-js/Pebble.md#TimelineTopicsCallback) |
| |
| pebblekit\_js | [openURL](/docs/pebblekit-js/Pebble.md#openURL) |
| |
| pebblekit\_js | [AppGlanceReloadFailureCallback](/docs/pebblekit-js/Pebble.md#AppGlanceReloadFailureCallback) |
| |
| pebblekit\_js | [AppMessageAckCallback](/docs/pebblekit-js/Pebble.md#AppMessageAckCallback) |
| |
| pebblekit\_js | [AppMessageNackCallback](/docs/pebblekit-js/Pebble.md#AppMessageNackCallback) |
| |
| pebblekit\_js | [EventCallback](/docs/pebblekit-js/Pebble.md#EventCallback) |
| |
| pebblekit\_js | [TimelineTokenCallback](/docs/pebblekit-js/Pebble.md#TimelineTokenCallback) |
| |
| pebblekit\_js | [AppGlanceReloadSuccessCallback](/docs/pebblekit-js/Pebble.md#AppGlanceReloadSuccessCallback) |
| |
| pebblekit\_js | [PostMessageCallback](/docs/pebblekit-js/Pebble.md#PostMessageCallback) |
| |
| pebblekit\_js | [PostMessageErrorCallback](/docs/pebblekit-js/Pebble.md#PostMessageErrorCallback) |
| |
| pebblekit\_js | [PostMessageConnectedCallback](/docs/pebblekit-js/Pebble.md#PostMessageConnectedCallback) |
| |
| pebblekit\_js | [PostMessageDisconnectedCallback](/docs/pebblekit-js/Pebble.md#PostMessageDisconnectedCallback) |
| |
| pebblekit\_js | [WatchInfo](/docs/pebblekit-js/Pebble.md#WatchInfo) |
| |
| pebblekit\_js | [AppGlanceSlice](/docs/pebblekit-js/Pebble.md#AppGlanceSlice) |
| |
| pebblekit\_android | [com.getpebble.android.kit](/docs/pebblekit-android/com/getpebble/android/kit.md) |
| |
| pebblekit\_android | [com.getpebble.android.kit.util](/docs/pebblekit-android/com/getpebble/android/kit/util.md) |
| |
| pebblekit\_android | [com.getpebble.android.kit.Constants](/docs/pebblekit-android/com/getpebble/android/kit/Constants.md) |
| |
| pebblekit\_android | [com.getpebble.android.kit.PebbleKit](/docs/pebblekit-android/com/getpebble/android/kit/PebbleKit.md) |
| |
| pebblekit\_android | [com.getpebble.android.kit.PebbleKit.FirmwareVersionInfo](/docs/pebblekit-android/com/getpebble/android/kit/PebbleKit.FirmwareVersionInfo.md) |
| |
| pebblekit\_android | [com.getpebble.android.kit.PebbleKit.PebbleAckReceiver](/docs/pebblekit-android/com/getpebble/android/kit/PebbleKit.PebbleAckReceiver.md) |
| |
| pebblekit\_android | [com.getpebble.android.kit.PebbleKit.PebbleDataLogReceiver](/docs/pebblekit-android/com/getpebble/android/kit/PebbleKit.PebbleDataLogReceiver.md) |
| |
| pebblekit\_android | [com.getpebble.android.kit.PebbleKit.PebbleDataReceiver](/docs/pebblekit-android/com/getpebble/android/kit/PebbleKit.PebbleDataReceiver.md) |
| |
| pebblekit\_android | [com.getpebble.android.kit.PebbleKit.PebbleNackReceiver](/docs/pebblekit-android/com/getpebble/android/kit/PebbleKit.PebbleNackReceiver.md) |
| |
| pebblekit\_android | [com.getpebble.android.kit.Constants.PebbleAppType](/docs/pebblekit-android/com/getpebble/android/kit/Constants.PebbleAppType.md) |
| |
| pebblekit\_android | [com.getpebble.android.kit.Constants.PebbleDataType](/docs/pebblekit-android/com/getpebble/android/kit/Constants.PebbleDataType.md) |
| |
| pebblekit\_android | [com.getpebble.android.kit.PebbleKit.areAppMessagesSupported](/docs/pebblekit-android/com/getpebble/android/kit/PebbleKit.md#areAppMessagesSupported) |
| |
| pebblekit\_android | [com.getpebble.android.kit.PebbleKit.closeAppOnPebble](/docs/pebblekit-android/com/getpebble/android/kit/PebbleKit.md#closeAppOnPebble) |
| |
| pebblekit\_android | [com.getpebble.android.kit.PebbleKit.customizeWatchApp](/docs/pebblekit-android/com/getpebble/android/kit/PebbleKit.md#customizeWatchApp) |
| |
| pebblekit\_android | [com.getpebble.android.kit.PebbleKit.getWatchFWVersion](/docs/pebblekit-android/com/getpebble/android/kit/PebbleKit.md#getWatchFWVersion) |
| |
| pebblekit\_android | [com.getpebble.android.kit.PebbleKit.isDataLoggingSupported](/docs/pebblekit-android/com/getpebble/android/kit/PebbleKit.md#isDataLoggingSupported) |
| |
| pebblekit\_android | [com.getpebble.android.kit.PebbleKit.isWatchConnected](/docs/pebblekit-android/com/getpebble/android/kit/PebbleKit.md#isWatchConnected) |
| |
| pebblekit\_android | [com.getpebble.android.kit.PebbleKit.registerDataLogReceiver](/docs/pebblekit-android/com/getpebble/android/kit/PebbleKit.md#registerDataLogReceiver) |
| |
| pebblekit\_android | [com.getpebble.android.kit.PebbleKit.registerPebbleConnectedReceiver](/docs/pebblekit-android/com/getpebble/android/kit/PebbleKit.md#registerPebbleConnectedReceiver) |
| |
| pebblekit\_android | [com.getpebble.android.kit.PebbleKit.registerPebbleDisconnectedReceiver](/docs/pebblekit-android/com/getpebble/android/kit/PebbleKit.md#registerPebbleDisconnectedReceiver) |
| |
| pebblekit\_android | [com.getpebble.android.kit.PebbleKit.registerReceivedAckHandler](/docs/pebblekit-android/com/getpebble/android/kit/PebbleKit.md#registerReceivedAckHandler) |
| |
| pebblekit\_android | [com.getpebble.android.kit.PebbleKit.registerReceivedDataHandler](/docs/pebblekit-android/com/getpebble/android/kit/PebbleKit.md#registerReceivedDataHandler) |
| |
| pebblekit\_android | [com.getpebble.android.kit.PebbleKit.registerReceivedNackHandler](/docs/pebblekit-android/com/getpebble/android/kit/PebbleKit.md#registerReceivedNackHandler) |
| |
| pebblekit\_android | [com.getpebble.android.kit.PebbleKit.requestDataLogsForApp](/docs/pebblekit-android/com/getpebble/android/kit/PebbleKit.md#requestDataLogsForApp) |
| |
| pebblekit\_android | [com.getpebble.android.kit.PebbleKit.sendAckToPebble](/docs/pebblekit-android/com/getpebble/android/kit/PebbleKit.md#sendAckToPebble) |
| |
| pebblekit\_android | [com.getpebble.android.kit.PebbleKit.sendDataToPebble](/docs/pebblekit-android/com/getpebble/android/kit/PebbleKit.md#sendDataToPebble) |
| |
| pebblekit\_android | [com.getpebble.android.kit.PebbleKit.sendDataToPebbleWithTransactionId](/docs/pebblekit-android/com/getpebble/android/kit/PebbleKit.md#sendDataToPebbleWithTransactionId) |
| |
| pebblekit\_android | [com.getpebble.android.kit.PebbleKit.sendNackToPebble](/docs/pebblekit-android/com/getpebble/android/kit/PebbleKit.md#sendNackToPebble) |
| |
| pebblekit\_android | [com.getpebble.android.kit.PebbleKit.startAppOnPebble](/docs/pebblekit-android/com/getpebble/android/kit/PebbleKit.md#startAppOnPebble) |
| |
| pebblekit\_android | [com.getpebble.android.kit.PebbleKit.FirmwareVersionInfo.getMajor](/docs/pebblekit-android/com/getpebble/android/kit/PebbleKit.FirmwareVersionInfo.md#getMajor) |
| |
| pebblekit\_android | [com.getpebble.android.kit.PebbleKit.FirmwareVersionInfo.getMinor](/docs/pebblekit-android/com/getpebble/android/kit/PebbleKit.FirmwareVersionInfo.md#getMinor) |
| |
| pebblekit\_android | [com.getpebble.android.kit.PebbleKit.FirmwareVersionInfo.getPoint](/docs/pebblekit-android/com/getpebble/android/kit/PebbleKit.FirmwareVersionInfo.md#getPoint) |
| |
| pebblekit\_android | [com.getpebble.android.kit.PebbleKit.FirmwareVersionInfo.getTag](/docs/pebblekit-android/com/getpebble/android/kit/PebbleKit.FirmwareVersionInfo.md#getTag) |
| |
| pebblekit\_android | [com.getpebble.android.kit.PebbleKit.PebbleAckReceiver.onReceive](/docs/pebblekit-android/com/getpebble/android/kit/PebbleKit.PebbleAckReceiver.md#onReceive) |
| |
| pebblekit\_android | [com.getpebble.android.kit.PebbleKit.PebbleAckReceiver.receiveAck](/docs/pebblekit-android/com/getpebble/android/kit/PebbleKit.PebbleAckReceiver.md#receiveAck) |
| |
| pebblekit\_android | [com.getpebble.android.kit.PebbleKit.PebbleDataLogReceiver.onFinishSession](/docs/pebblekit-android/com/getpebble/android/kit/PebbleKit.PebbleDataLogReceiver.md#onFinishSession) |
| |
| pebblekit\_android | [com.getpebble.android.kit.PebbleKit.PebbleDataLogReceiver.onReceive](/docs/pebblekit-android/com/getpebble/android/kit/PebbleKit.PebbleDataLogReceiver.md#onReceive) |
| |
| pebblekit\_android | [com.getpebble.android.kit.PebbleKit.PebbleDataLogReceiver.receiveData](/docs/pebblekit-android/com/getpebble/android/kit/PebbleKit.PebbleDataLogReceiver.md#receiveData) |
| |
| pebblekit\_android | [com.getpebble.android.kit.PebbleKit.PebbleDataLogReceiver.receiveData](/docs/pebblekit-android/com/getpebble/android/kit/PebbleKit.PebbleDataLogReceiver.md#receiveData) |
| |
| pebblekit\_android | [com.getpebble.android.kit.PebbleKit.PebbleDataLogReceiver.receiveData](/docs/pebblekit-android/com/getpebble/android/kit/PebbleKit.PebbleDataLogReceiver.md#receiveData) |
| |
| pebblekit\_android | [com.getpebble.android.kit.PebbleKit.PebbleDataReceiver.onReceive](/docs/pebblekit-android/com/getpebble/android/kit/PebbleKit.PebbleDataReceiver.md#onReceive) |
| |
| pebblekit\_android | [com.getpebble.android.kit.PebbleKit.PebbleDataReceiver.receiveData](/docs/pebblekit-android/com/getpebble/android/kit/PebbleKit.PebbleDataReceiver.md#receiveData) |
| |
| pebblekit\_android | [com.getpebble.android.kit.PebbleKit.PebbleNackReceiver.onReceive](/docs/pebblekit-android/com/getpebble/android/kit/PebbleKit.PebbleNackReceiver.md#onReceive) |
| |
| pebblekit\_android | [com.getpebble.android.kit.PebbleKit.PebbleNackReceiver.receiveNack](/docs/pebblekit-android/com/getpebble/android/kit/PebbleKit.PebbleNackReceiver.md#receiveNack) |
| |
| pebblekit\_android | [com.getpebble.android.kit.Constants.PebbleAppType.valueOf](/docs/pebblekit-android/com/getpebble/android/kit/Constants.PebbleAppType.md#valueOf) |
| |
| pebblekit\_android | [com.getpebble.android.kit.Constants.PebbleAppType.values](/docs/pebblekit-android/com/getpebble/android/kit/Constants.PebbleAppType.md#values) |
| |
| pebblekit\_android | [com.getpebble.android.kit.Constants.PebbleDataType.fromByte](/docs/pebblekit-android/com/getpebble/android/kit/Constants.PebbleDataType.md#fromByte) |
| |
| pebblekit\_android | [com.getpebble.android.kit.Constants.PebbleDataType.valueOf](/docs/pebblekit-android/com/getpebble/android/kit/Constants.PebbleDataType.md#valueOf) |
| |
| pebblekit\_android | [com.getpebble.android.kit.Constants.PebbleDataType.values](/docs/pebblekit-android/com/getpebble/android/kit/Constants.PebbleDataType.md#values) |
| |
| pebblekit\_android | [com.getpebble.android.kit.util.PebbleDictionary](/docs/pebblekit-android/com/getpebble/android/kit/util/PebbleDictionary.md) |
| |
| pebblekit\_android | [com.getpebble.android.kit.util.PebbleTuple](/docs/pebblekit-android/com/getpebble/android/kit/util/PebbleTuple.md) |
| |
| pebblekit\_android | [com.getpebble.android.kit.util.SportsState](/docs/pebblekit-android/com/getpebble/android/kit/util/SportsState.md) |
| |
| pebblekit\_android | [com.getpebble.android.kit.util.PebbleDictionary.PebbleDictTypeException](/docs/pebblekit-android/com/getpebble/android/kit/util/PebbleDictionary.PebbleDictTypeException.md) |
| |
| pebblekit\_android | [com.getpebble.android.kit.util.PebbleDictionary.TupleOverflowException](/docs/pebblekit-android/com/getpebble/android/kit/util/PebbleDictionary.TupleOverflowException.md) |
| |
| pebblekit\_android | [com.getpebble.android.kit.util.PebbleTuple.ValueOverflowException](/docs/pebblekit-android/com/getpebble/android/kit/util/PebbleTuple.ValueOverflowException.md) |
| |
| pebblekit\_android | [com.getpebble.android.kit.util.PebbleDictionary.addBytes](/docs/pebblekit-android/com/getpebble/android/kit/util/PebbleDictionary.md#addBytes) |
| |
| pebblekit\_android | [com.getpebble.android.kit.util.PebbleDictionary.addInt16](/docs/pebblekit-android/com/getpebble/android/kit/util/PebbleDictionary.md#addInt16) |
| |
| pebblekit\_android | [com.getpebble.android.kit.util.PebbleDictionary.addInt32](/docs/pebblekit-android/com/getpebble/android/kit/util/PebbleDictionary.md#addInt32) |
| |
| pebblekit\_android | [com.getpebble.android.kit.util.PebbleDictionary.addInt8](/docs/pebblekit-android/com/getpebble/android/kit/util/PebbleDictionary.md#addInt8) |
| |
| pebblekit\_android | [com.getpebble.android.kit.util.PebbleDictionary.addString](/docs/pebblekit-android/com/getpebble/android/kit/util/PebbleDictionary.md#addString) |
| |
| pebblekit\_android | [com.getpebble.android.kit.util.PebbleDictionary.addTuple](/docs/pebblekit-android/com/getpebble/android/kit/util/PebbleDictionary.md#addTuple) |
| |
| pebblekit\_android | [com.getpebble.android.kit.util.PebbleDictionary.addUint16](/docs/pebblekit-android/com/getpebble/android/kit/util/PebbleDictionary.md#addUint16) |
| |
| pebblekit\_android | [com.getpebble.android.kit.util.PebbleDictionary.addUint32](/docs/pebblekit-android/com/getpebble/android/kit/util/PebbleDictionary.md#addUint32) |
| |
| pebblekit\_android | [com.getpebble.android.kit.util.PebbleDictionary.addUint8](/docs/pebblekit-android/com/getpebble/android/kit/util/PebbleDictionary.md#addUint8) |
| |
| pebblekit\_android | [com.getpebble.android.kit.util.PebbleDictionary.contains](/docs/pebblekit-android/com/getpebble/android/kit/util/PebbleDictionary.md#contains) |
| |
| pebblekit\_android | [com.getpebble.android.kit.util.PebbleDictionary.fromJson](/docs/pebblekit-android/com/getpebble/android/kit/util/PebbleDictionary.md#fromJson) |
| |
| pebblekit\_android | [com.getpebble.android.kit.util.PebbleDictionary.getBytes](/docs/pebblekit-android/com/getpebble/android/kit/util/PebbleDictionary.md#getBytes) |
| |
| pebblekit\_android | [com.getpebble.android.kit.util.PebbleDictionary.getInteger](/docs/pebblekit-android/com/getpebble/android/kit/util/PebbleDictionary.md#getInteger) |
| |
| pebblekit\_android | [com.getpebble.android.kit.util.PebbleDictionary.getString](/docs/pebblekit-android/com/getpebble/android/kit/util/PebbleDictionary.md#getString) |
| |
| pebblekit\_android | [com.getpebble.android.kit.util.PebbleDictionary.getUnsignedIntegerAsLong](/docs/pebblekit-android/com/getpebble/android/kit/util/PebbleDictionary.md#getUnsignedIntegerAsLong) |
| |
| pebblekit\_android | [com.getpebble.android.kit.util.PebbleDictionary.iterator](/docs/pebblekit-android/com/getpebble/android/kit/util/PebbleDictionary.md#iterator) |
| |
| pebblekit\_android | [com.getpebble.android.kit.util.PebbleDictionary.remove](/docs/pebblekit-android/com/getpebble/android/kit/util/PebbleDictionary.md#remove) |
| |
| pebblekit\_android | [com.getpebble.android.kit.util.PebbleDictionary.size](/docs/pebblekit-android/com/getpebble/android/kit/util/PebbleDictionary.md#size) |
| |
| pebblekit\_android | [com.getpebble.android.kit.util.PebbleDictionary.toJsonString](/docs/pebblekit-android/com/getpebble/android/kit/util/PebbleDictionary.md#toJsonString) |
| |
| pebblekit\_android | [com.getpebble.android.kit.util.SportsState.getCustomLabel](/docs/pebblekit-android/com/getpebble/android/kit/util/SportsState.md#getCustomLabel) |
| |
| pebblekit\_android | [com.getpebble.android.kit.util.SportsState.getCustomValue](/docs/pebblekit-android/com/getpebble/android/kit/util/SportsState.md#getCustomValue) |
| |
| pebblekit\_android | [com.getpebble.android.kit.util.SportsState.getDistance](/docs/pebblekit-android/com/getpebble/android/kit/util/SportsState.md#getDistance) |
| |
| pebblekit\_android | [com.getpebble.android.kit.util.SportsState.getHeartBPM](/docs/pebblekit-android/com/getpebble/android/kit/util/SportsState.md#getHeartBPM) |
| |
| pebblekit\_android | [com.getpebble.android.kit.util.SportsState.getPaceInSec](/docs/pebblekit-android/com/getpebble/android/kit/util/SportsState.md#getPaceInSec) |
| |
| pebblekit\_android | [com.getpebble.android.kit.util.SportsState.getSpeed](/docs/pebblekit-android/com/getpebble/android/kit/util/SportsState.md#getSpeed) |
| |
| pebblekit\_android | [com.getpebble.android.kit.util.SportsState.getTimeInSec](/docs/pebblekit-android/com/getpebble/android/kit/util/SportsState.md#getTimeInSec) |
| |
| pebblekit\_android | [com.getpebble.android.kit.util.SportsState.setCustomLabel](/docs/pebblekit-android/com/getpebble/android/kit/util/SportsState.md#setCustomLabel) |
| |
| pebblekit\_android | [com.getpebble.android.kit.util.SportsState.setCustomValue](/docs/pebblekit-android/com/getpebble/android/kit/util/SportsState.md#setCustomValue) |
| |
| pebblekit\_android | [com.getpebble.android.kit.util.SportsState.setDistance](/docs/pebblekit-android/com/getpebble/android/kit/util/SportsState.md#setDistance) |
| |
| pebblekit\_android | [com.getpebble.android.kit.util.SportsState.setHeartBPM](/docs/pebblekit-android/com/getpebble/android/kit/util/SportsState.md#setHeartBPM) |
| |
| pebblekit\_android | [com.getpebble.android.kit.util.SportsState.setPaceInSec](/docs/pebblekit-android/com/getpebble/android/kit/util/SportsState.md#setPaceInSec) |
| |
| pebblekit\_android | [com.getpebble.android.kit.util.SportsState.setSpeed](/docs/pebblekit-android/com/getpebble/android/kit/util/SportsState.md#setSpeed) |
| |
| pebblekit\_android | [com.getpebble.android.kit.util.SportsState.setTimeInSec](/docs/pebblekit-android/com/getpebble/android/kit/util/SportsState.md#setTimeInSec) |
| |
| pebblekit\_android | [com.getpebble.android.kit.util.SportsState.synchronize](/docs/pebblekit-android/com/getpebble/android/kit/util/SportsState.md#synchronize) |
| |
| pebblekit\_ios | [PBPebbleKitLoggingCallback](/docs/pebblekit-ios/Blocks/PBPebbleKitLoggingCallback.md) |
| |
| pebblekit\_ios | [PBVersionInfoCompletionBlock](/docs/pebblekit-ios/Blocks/PBVersionInfoCompletionBlock.md) |
| |
| pebblekit\_ios | [NSData+Pebble](/docs/pebblekit-ios/Categories/NSData%2BPebble/) |
| |
| pebblekit\_ios | [pb\_dictionaryFromPebbleDictionaryDataWithError:](/docs/pebblekit-ios/Categories/NSData%2BPebble/#//api/name/pb_dictionaryFromPebbleDictionaryDataWithError:) |
| Interprets the receiver as Pebble dict data and deserializes it into an NSDictionary. - (nullable NSDictionary \*)pb\_dictionaryFromPebbleDictionaryDataWithError:(NSError \*\_\_autoreleasing \*)error Parameters error Pointer to an NSError \* that will be set after the method has returned in case there was an error. Possible error codes: PBErrorCodeDictionaryInternalConsistency See Also [NSDictionary(Pebble) pb\_pebbleDictionaryData:] Declared In NSDictionary+Pebble.h |
| pebblekit\_ios | [NSNumber+PBStandardIntegerExtensions](/docs/pebblekit-ios/Categories/NSNumber%2BPBStandardIntegerExtensions/) |
| |
| pebblekit\_ios | [pb\_uint32Value](/docs/pebblekit-ios/Categories/NSNumber%2BPBStandardIntegerExtensions/#//api/name/pb_uint32Value) |
| Interprets the receiver as a 32-bits wide, unsigned integer. @property (readonly) uint32\_t pb\_uint32Value Declared In NSNumber+stdint.h |
| pebblekit\_ios | [pb\_uint16Value](/docs/pebblekit-ios/Categories/NSNumber%2BPBStandardIntegerExtensions/#//api/name/pb_uint16Value) |
| Interprets the receiver as a 16-bits wide, unsigned integer. @property (readonly) uint16\_t pb\_uint16Value Declared In NSNumber+stdint.h |
| pebblekit\_ios | [pb\_uint8Value](/docs/pebblekit-ios/Categories/NSNumber%2BPBStandardIntegerExtensions/#//api/name/pb_uint8Value) |
| Interprets the receiver as a 8-bits wide, unsigned integer. @property (readonly) uint8\_t pb\_uint8Value Declared In NSNumber+stdint.h |
| pebblekit\_ios | [pb\_int32Value](/docs/pebblekit-ios/Categories/NSNumber%2BPBStandardIntegerExtensions/#//api/name/pb_int32Value) |
| Interprets the receiver as a 32-bits wide, signed integer. @property (readonly) int32\_t pb\_int32Value Declared In NSNumber+stdint.h |
| pebblekit\_ios | [pb\_int16Value](/docs/pebblekit-ios/Categories/NSNumber%2BPBStandardIntegerExtensions/#//api/name/pb_int16Value) |
| Interprets the receiver as a 16-bits wide, signed integer. @property (readonly) int16\_t pb\_int16Value Declared In NSNumber+stdint.h |
| pebblekit\_ios | [pb\_int8Value](/docs/pebblekit-ios/Categories/NSNumber%2BPBStandardIntegerExtensions/#//api/name/pb_int8Value) |
| Interprets the receiver as a 8-bits wide, signed integer. @property (readonly) int8\_t pb\_int8Value Declared In NSNumber+stdint.h |
| pebblekit\_ios | [pb\_float](/docs/pebblekit-ios/Categories/NSNumber%2BPBStandardIntegerExtensions/#//api/name/pb_float) |
| Gets whether the number that is stored by the receiver should be interpreted as a floating pointer number or not. @property (readonly, getter=pb\_isFloat) BOOL pb\_float Declared In NSNumber+stdint.h |
| pebblekit\_ios | [pb\_signed](/docs/pebblekit-ios/Categories/NSNumber%2BPBStandardIntegerExtensions/#//api/name/pb_signed) |
| Gets whether the number that is stored by the receiver should be interpreted as a signed integer or not. @property (readonly, getter=pb\_isSigned) BOOL pb\_signed Declared In NSNumber+stdint.h |
| pebblekit\_ios | [pb\_byteWidth](/docs/pebblekit-ios/Categories/NSNumber%2BPBStandardIntegerExtensions/#//api/name/pb_byteWidth) |
| Gets the width in bytes of the integer that is stored by the receiver. @property (readonly) uint8\_t pb\_byteWidth Declared In NSNumber+stdint.h |
| pebblekit\_ios | [pb\_numberWithUint32:](/docs/pebblekit-ios/Categories/NSNumber%2BPBStandardIntegerExtensions/#//api/name/pb_numberWithUint32:) |
| Creates an NSNumber with a 32-bits wide, unsigned integer. + (NSNumber \*)pb\_numberWithUint32:(uint32\_t)value Parameters value The value for the created number. Declared In NSNumber+stdint.h |
| pebblekit\_ios | [pb\_numberWithUint16:](/docs/pebblekit-ios/Categories/NSNumber%2BPBStandardIntegerExtensions/#//api/name/pb_numberWithUint16:) |
| Creates an NSNumber with a 16-bits wide, unsigned integer. + (NSNumber \*)pb\_numberWithUint16:(uint16\_t)value Parameters value The value for the created number. Declared In NSNumber+stdint.h |
| pebblekit\_ios | [pb\_numberWithUint8:](/docs/pebblekit-ios/Categories/NSNumber%2BPBStandardIntegerExtensions/#//api/name/pb_numberWithUint8:) |
| Creates an NSNumber with a 8-bits wide, unsigned integer. + (NSNumber \*)pb\_numberWithUint8:(uint8\_t)value Parameters value The value for the created number. Declared In NSNumber+stdint.h |
| pebblekit\_ios | [pb\_numberWithInt32:](/docs/pebblekit-ios/Categories/NSNumber%2BPBStandardIntegerExtensions/#//api/name/pb_numberWithInt32:) |
| Creates an NSNumber with a 32-bits wide, signed integer. + (NSNumber \*)pb\_numberWithInt32:(int32\_t)value Parameters value The value for the created number. Declared In NSNumber+stdint.h |
| pebblekit\_ios | [pb\_numberWithInt16:](/docs/pebblekit-ios/Categories/NSNumber%2BPBStandardIntegerExtensions/#//api/name/pb_numberWithInt16:) |
| Creates an NSNumber with a 16-bits wide, signed integer. + (NSNumber \*)pb\_numberWithInt16:(int16\_t)value Parameters value The value for the created number. Declared In NSNumber+stdint.h |
| pebblekit\_ios | [pb\_numberWithInt8:](/docs/pebblekit-ios/Categories/NSNumber%2BPBStandardIntegerExtensions/#//api/name/pb_numberWithInt8:) |
| Creates an NSNumber with a 8-bits wide, signed integer. + (NSNumber \*)pb\_numberWithInt8:(int8\_t)value Parameters value The value for the created number. Declared In NSNumber+stdint.h |
| pebblekit\_ios | [NSError+Pebble](/docs/pebblekit-ios/Categories/NSError%2BPebble/) |
| |
| pebblekit\_ios | [pebbleErrorWithCode:underLyingError:](/docs/pebblekit-ios/Categories/NSError%2BPebble/#//api/name/pebbleErrorWithCode:underLyingError:) |
| Convenience method to create an NSError object with error domain and a given PBErrorCode and with an underlying NSError object. + (NSError \*)pebbleErrorWithCode:(PBErrorCode)code underLyingError:(NSError \*\_\_nullable)error Parameters code The error code for which to create the error error The underlying error Declared In PBErrors.h |
| pebblekit\_ios | [pebbleErrorWithCode:](/docs/pebblekit-ios/Categories/NSError%2BPebble/#//api/name/pebbleErrorWithCode:) |
| Convenience method to create an NSError object with error domain and a given PBErrorCode. + (NSError \*)pebbleErrorWithCode:(PBErrorCode)code Parameters code The error code for which to create the error Declared In PBErrors.h |
| pebblekit\_ios | [NSDictionary+Pebble](/docs/pebblekit-ios/Categories/NSDictionary%2BPebble/) |
| |
| pebblekit\_ios | [pb\_pebbleDictionaryData:](/docs/pebblekit-ios/Categories/NSDictionary%2BPebble/#//api/name/pb_pebbleDictionaryData:) |
| Serializes the receiver into a Pebble dict. - (nullable NSData \*)pb\_pebbleDictionaryData:(NSError \*\_\_autoreleasing \*)error Parameters error Pointer to an NSError \* that will be set in case there was an error creating the dictionary. Possible error codes: PBErrorCodeDictionaryUnsupportedKeyClass PBErrorCodeDictionaryUnsupportedValueClass PBErrorCodeDictionaryUnsupportedValueClass Discussion The receiver dictionary must comply to the following constraints: The keys must be instances of NSNumber. Their -unsignedLongValue return value will be used as final key. The values must be instances of either NSString, NSData or NSNumber. Use the NSNumber (stdint) category to specify the signedness and width of NSNumber. See Also [NSData(Pebble) pb\_dictionaryFromPebbleDictionaryDataWithError:] Declared In NSDictionary+Pebble.h |
| pebblekit\_ios | [PBSemanticVersion](/docs/pebblekit-ios/Classes/PBSemanticVersion.md) |
| |
| pebblekit\_ios | [majorVersion](/docs/pebblekit-ios/Classes/PBSemanticVersion.md#//api/name/majorVersion) |
| The version major number @property (nonatomic, assign, readonly) NSUInteger majorVersion Declared In PBSemanticVersion.h |
| pebblekit\_ios | [minorVersion](/docs/pebblekit-ios/Classes/PBSemanticVersion.md#//api/name/minorVersion) |
| The version minor number @property (nonatomic, assign, readonly) NSUInteger minorVersion Declared In PBSemanticVersion.h |
| pebblekit\_ios | [revisionVersion](/docs/pebblekit-ios/Classes/PBSemanticVersion.md#//api/name/revisionVersion) |
| The version revision number @property (nonatomic, assign, readonly) NSUInteger revisionVersion Declared In PBSemanticVersion.h |
| pebblekit\_ios | [suffix](/docs/pebblekit-ios/Classes/PBSemanticVersion.md#//api/name/suffix) |
| The version suffix string. @property (nonatomic, copy, readonly) NSString \*suffix Discussion Note: If a version tag string does not contain a suffix, it will be set to an empty string. The release suffix is not used in the compare: or -isEqual: methods. Declared In PBSemanticVersion.h |
| pebblekit\_ios | [initWithVersionString:](/docs/pebblekit-ios/Classes/PBSemanticVersion.md#//api/name/initWithVersionString:) |
| Returns a new instance by parsing the input. - (nullable instancetype)initWithVersionString:(NSString \*)versionString Parameters versionString Expected format: major.minor.revision-sffix. Example: “2.0.1-rc2” If a parsing error occurs, nil will be returned. Return Value A version or nil if some error happen. Declared In PBSemanticVersion.h |
| pebblekit\_ios | [initWithMajor:minor:revision:suffix:](/docs/pebblekit-ios/Classes/PBSemanticVersion.md#//api/name/initWithMajor:minor:revision:suffix:) |
| Returns a new instance by using the given components. - (instancetype)initWithMajor:(NSUInteger)major minor:(NSUInteger)minor revision:(NSUInteger)revision suffix:(nullable NSString \*)suffix Parameters major The version major number. minor The version minor number. revision The version revision number. suffix The version suffix. Can be nil. Declared In PBSemanticVersion.h |
| pebblekit\_ios | [compare:](/docs/pebblekit-ios/Classes/PBSemanticVersion.md#//api/name/compare:) |
| Compares the receiver to another version object. - (NSComparisonResult)compare:(PBSemanticVersion \*)aVersion Parameters aVersion The version to compare with the receiver. Return Value NSOrderedAscending if the value of aVersion is greater than the receiver’s, NSOrderedSame if they’re equal, and NSOrderedDescending if the value of aVersion is less than the receiver’s. Declared In PBSemanticVersion.h |
| pebblekit\_ios | [isEqualOrNewer:](/docs/pebblekit-ios/Classes/PBSemanticVersion.md#//api/name/isEqualOrNewer:) |
| Returns if the the receiver is equal or newer than the given version. - (BOOL)isEqualOrNewer:(PBSemanticVersion \*)other Parameters other Version number to compare against. Return Value YES if the receiver is equal or newer. NO otherwise. Declared In PBSemanticVersion.h |
| pebblekit\_ios | [isNewer:](/docs/pebblekit-ios/Classes/PBSemanticVersion.md#//api/name/isNewer:) |
| Returns if the receiver is strictly newer than the given version. - (BOOL)isNewer:(PBSemanticVersion \*)other Parameters other Version number to compare against. Return Value YES if the receiver is stricly newer. NO otherwise. Declared In PBSemanticVersion.h |
| pebblekit\_ios | [PBFirmwareMetadata](/docs/pebblekit-ios/Classes/PBFirmwareMetadata.md) |
| |
| pebblekit\_ios | [version](/docs/pebblekit-ios/Classes/PBFirmwareMetadata.md#//api/name/version) |
| The version of the firmware. @property (nonatomic, readonly) PBFirmwareVersion \*version See Also PBFirmwareVersion Declared In PBFirmwareMetadata.h |
| pebblekit\_ios | [isRecoveryFirmware](/docs/pebblekit-ios/Classes/PBFirmwareMetadata.md#//api/name/isRecoveryFirmware) |
| YES if the firmware is a recovery firmware, NO if it is a regular firmware. @property (nonatomic, readonly) BOOL isRecoveryFirmware Declared In PBFirmwareMetadata.h |
| pebblekit\_ios | [hardwarePlatform](/docs/pebblekit-ios/Classes/PBFirmwareMetadata.md#//api/name/hardwarePlatform) |
| The hardware platform variant with which the firmware is compatible. @property (nonatomic, readonly) FirmwareMetadataPlatform hardwarePlatform Declared In PBFirmwareMetadata.h |
| pebblekit\_ios | [hardwarePlatformToString:](/docs/pebblekit-ios/Classes/PBFirmwareMetadata.md#//api/name/hardwarePlatformToString:) |
| Converts a FirmwareMetadataPlatform value to a string. + (NSString \*)hardwarePlatformToString:(FirmwareMetadataPlatform)hardwarePlatform Parameters hardwarePlatform The hardware platform value to convert Return Value A string of the hardware platform Declared In PBFirmwareMetadata.h |
| pebblekit\_ios | [stringToHardwarePlatform:](/docs/pebblekit-ios/Classes/PBFirmwareMetadata.md#//api/name/stringToHardwarePlatform:) |
| Converts an NSString hardware platform string to the corresponding FirmwareMetadataPlatform value. + (FirmwareMetadataPlatform)stringToHardwarePlatform:(NSString \*)hardwarePlatformString Parameters hardwarePlatformString The string representing the hardware platform. Return Value The hardware platform enum value Declared In PBFirmwareMetadata.h |
| pebblekit\_ios | [PBFirmwareVersion](/docs/pebblekit-ios/Classes/PBFirmwareVersion.md) |
| |
| pebblekit\_ios | [timestamp](/docs/pebblekit-ios/Classes/PBFirmwareVersion.md#//api/name/timestamp) |
| The version timestamp. @property (nonatomic, readonly) uint32\_t timestamp Discussion The timestamp is in the final comparison equation, in the -compare: method, after evaluating major, minor, and revision components. Declared In PBFirmwareVersion.h |
| pebblekit\_ios | [commitHash](/docs/pebblekit-ios/Classes/PBFirmwareVersion.md#//api/name/commitHash) |
| The version’s git commit hash. @property (nonatomic, readonly, copy, nullable) NSString \*commitHash Discussion The commit hash is not used in the -compare: method. Declared In PBFirmwareVersion.h |
| pebblekit\_ios | [tag](/docs/pebblekit-ios/Classes/PBFirmwareVersion.md#//api/name/tag) |
| The version’s git tag. @property (nonatomic, readonly, copy) NSString \*tag Declared In PBFirmwareVersion.h |
| pebblekit\_ios | [firmwareVersionWithString:](/docs/pebblekit-ios/Classes/PBFirmwareVersion.md#//api/name/firmwareVersionWithString:) |
| Creates a PBFirmwareVersion object given a tag string. + (nullable instancetype)firmwareVersionWithString:(NSString \*)tag Parameters tag The firmware version string to parse. Declared In PBFirmwareVersion.h |
| pebblekit\_ios | [firmwareVersionWithTag:commitHash:timestamp:](/docs/pebblekit-ios/Classes/PBFirmwareVersion.md#//api/name/firmwareVersionWithTag:commitHash:timestamp:) |
| Creates a PBFirmwareVersion object given a tag string and timestamp. + (nullable instancetype)firmwareVersionWithTag:(NSString \*)tag commitHash:(nullable NSString \*)commitHash timestamp:(uint32\_t)timestamp Parameters tag The firmare version string to parse. commitHash A version’s commit hash. Can be nil. timestamp The version timestamp. Declared In PBFirmwareVersion.h |
| pebblekit\_ios | [firmwareVersionWithMajor:minor:revision:suffix:commitHash:timestamp:](/docs/pebblekit-ios/Classes/PBFirmwareVersion.md#//api/name/firmwareVersionWithMajor:minor:revision:suffix:commitHash:timestamp:) |
| Creates a PBFirmwareVersion object given its components. + (instancetype)firmwareVersionWithMajor:(NSInteger)major minor:(NSInteger)minor revision:(NSInteger)revision suffix:(nullable NSString \*)suffix commitHash:(nullable NSString \*)commitHash timestamp:(uint32\_t)timestamp Parameters major The version major number. minor The version minor number. revision The version revision number. suffix The version suffix. Can be nil. commitHash A version’s commit hash. Can be nil. timestamp The version timestamp. Discussion The tag string will be set to the canonical format vMAJOR.MINOR.REVISION(-SUFFIX). Declared In PBFirmwareVersion.h |
| pebblekit\_ios | [os](/docs/pebblekit-ios/Classes/PBFirmwareVersion.md#//api/name/os) |
| The OS version component. (Deprecated: Use [PBSemanticVersion majorVersion]) @property (nonatomic, readonly) NSInteger os Declared In PBFirmwareVersion+Legacy.h |
| pebblekit\_ios | [major](/docs/pebblekit-ios/Classes/PBFirmwareVersion.md#//api/name/major) |
| The major version component. (Deprecated: Use [PBSemanticVersion minorVersion]) @property (nonatomic, readonly) NSInteger major Discussion Note: If a version tag string does not contain a major component, it will be set to 0. Declared In PBFirmwareVersion+Legacy.h |
| pebblekit\_ios | [minor](/docs/pebblekit-ios/Classes/PBFirmwareVersion.md#//api/name/minor) |
| The minor version component. (Deprecated: Use [PBSemanticVersion revisionVersion]) @property (nonatomic, readonly) NSInteger minor Discussion Note: If a version tag string does not contain a major component, it will be set to 0. Declared In PBFirmwareVersion+Legacy.h |
| pebblekit\_ios | [firmwareVersionWithOS:major:minor:suffix:commitHash:timestamp:](/docs/pebblekit-ios/Classes/PBFirmwareVersion.md#//api/name/firmwareVersionWithOS:major:minor:suffix:commitHash:timestamp:) |
| Creates a PBFirmwareVersion object given its components. (Deprecated: Use +[PBFirmwareVersion firmwareVersionWithMajor:minor:revision:suffix:commitHash:timestamp:]) + (nullable instancetype)firmwareVersionWithOS:(NSInteger)os major:(NSInteger)major minor:(NSInteger)minor suffix:(nullable NSString \*)suffix commitHash:(nullable NSString \*)commitHash timestamp:(uint32\_t)timestamp Parameters os The version major number. major The version minor number. minor The version revision number. suffix The version suffix. Can be nil. commitHash A version’s commit hash. Can be nil. timestamp The version timestamp. Discussion The tag string will be set to the canonical format vMAJOR.MINOR.REVISION(-SUFFIX). Declared In PBFirmwareVersion+Legacy.h |
| pebblekit\_ios | [PBDataLoggingService](/docs/pebblekit-ios/Classes/PBDataLoggingService.md) |
| |
| pebblekit\_ios | [delegate](/docs/pebblekit-ios/Classes/PBDataLoggingService.md#//api/name/delegate) |
| The delegate that has the responsility of handling callbacks from the data logging service. @property (atomic, readwrite, weak) id delegate Declared In PBDataLoggingService.h |
| pebblekit\_ios | [setDelegateQueue:](/docs/pebblekit-ios/Classes/PBDataLoggingService.md#//api/name/setDelegateQueue:) |
| Sets the queue on which delegate methods will be executed. Callbacks are intended to be processed in the order as they come in, so it you must use a serial queue. If set to nil (default) the main queue is used. - (void)setDelegateQueue:(dispatch\_queue\_t)delegateQueue Parameters delegateQueue The queue on which the delegate methods will be executed. Declared In PBDataLoggingService.h |
| pebblekit\_ios | [pollForData](/docs/pebblekit-ios/Classes/PBDataLoggingService.md#//api/name/pollForData) |
| Query the latestConnectedWatch for data logging data. (Deprecated: Use pollForDataFromWatch:) - (void)pollForData Declared In PBDataLoggingService.h |
| pebblekit\_ios | [pollForDataFromWatch:](/docs/pebblekit-ios/Classes/PBDataLoggingService.md#//api/name/pollForDataFromWatch:) |
| Query the watch for data logging data. - (void)pollForDataFromWatch:(PBWatch \*)watch Parameters watch The watch to query data from. Declared In PBDataLoggingService.h |
| pebblekit\_ios | [PBPebbleKitLogging](/docs/pebblekit-ios/Classes/PBPebbleKitLogging.md) |
| |
| pebblekit\_ios | [setLogLevel:](/docs/pebblekit-ios/Classes/PBPebbleKitLogging.md#//api/name/setLogLevel:) |
| Configures which events should be logged. + (void)setLogLevel:(PBPebbleKitLogLevel)logLevel Parameters logLevel One of the values in PBPebbleKitLogLevel, which will be the maximum level that will be logged. You can use PBPebbleKitLogLevelOff to disable all logging. Declared In PBLog+Public.h |
| pebblekit\_ios | [setLoggingCallback:](/docs/pebblekit-ios/Classes/PBPebbleKitLogging.md#//api/name/setLoggingCallback:) |
| Sets a new logging callback that will be invoked for each of the log records emitted by PebbleKit. + (void)setLoggingCallback:(nullable PBPebbleKitLoggingCallback)loggingCallback Parameters loggingCallback A block that will be invoked for each of the log records emitted by PebbleKit. Set this value to nil to return to the default NSLog logging. Declared In PBLog+Public.h |
| pebblekit\_ios | [new](/docs/pebblekit-ios/Classes/PBPebbleKitLogging.md#//api/name/new) |
| You should not create instances of this type. + (instancetype)new Discussion Note: You should not create instances of this type. Declared In PBLog+Public.h |
| pebblekit\_ios | [init](/docs/pebblekit-ios/Classes/PBPebbleKitLogging.md#//api/name/init) |
| You should not create instances of this type. - (instancetype)init Discussion Note: You should not create instances of this type. Declared In PBLog+Public.h |
| pebblekit\_ios | [PBWatch](/docs/pebblekit-ios/Classes/PBWatch.md) |
| |
| pebblekit\_ios | [central](/docs/pebblekit-ios/Classes/PBWatch.md#//api/name/central) |
| The central that is managing this watch. @property (nonatomic, weak, readonly) PBPebbleCentral \*central Discussion This property is KVO-compliant. Declared In PBWatch.h |
| pebblekit\_ios | [isNew](/docs/pebblekit-ios/Classes/PBWatch.md#//api/name/isNew) |
| YES if the receiver it’s the first time that watch has been seen. - (BOOL)isNew Discussion This property is KVO-compliant. Declared In PBWatch.h |
| pebblekit\_ios | [connected](/docs/pebblekit-ios/Classes/PBWatch.md#//api/name/connected) |
| YES if the receiver is connected and NO if the receiver is disconnected. @property (nonatomic, assign, readonly, getter=isConnected) BOOL connected Discussion This property is KVO-compliant. Declared In PBWatch.h |
| pebblekit\_ios | [name](/docs/pebblekit-ios/Classes/PBWatch.md#//api/name/name) |
| The human-friendly name of the receiver. This is the same name as the user will see in the iOS Bluetooth Settings. @property (nonatomic, copy, readonly) NSString \*name Declared In PBWatch.h |
| pebblekit\_ios | [serialNumber](/docs/pebblekit-ios/Classes/PBWatch.md#//api/name/serialNumber) |
| The serial number of the receiver. @property (nonatomic, copy, readonly) NSString \*serialNumber Declared In PBWatch.h |
| pebblekit\_ios | [versionInfo](/docs/pebblekit-ios/Classes/PBWatch.md#//api/name/versionInfo) |
| The versionInfo of the receiver. @property (nonatomic, strong, readonly) PBVersionInfo \*versionInfo See Also PBVersionInfo Declared In PBWatch.h |
| pebblekit\_ios | [delegate](/docs/pebblekit-ios/Classes/PBWatch.md#//api/name/delegate) |
| The delegate of the watch that will be notified of disconnections and errors. @property (nonatomic, weak) id \_\_nullable delegate See Also PBWatchDelegate Declared In PBWatch.h |
| pebblekit\_ios | [userInfo](/docs/pebblekit-ios/Classes/PBWatch.md#//api/name/userInfo) |
| The userInfo property can be used to associate application specific data with the watch. Note that the application itself is responsible for persisting the information if neccessary. @property (nonatomic, strong) id \_\_nullable userInfo Declared In PBWatch.h |
| pebblekit\_ios | [lastConnectedDate](/docs/pebblekit-ios/Classes/PBWatch.md#//api/name/lastConnectedDate) |
| The date when the watch was last known to be connected. This date will be updated automatically when the watch connects and disconnects. While the watch is being connected, this date will not be updated. @property (nonatomic, strong, readonly) NSDate \*lastConnectedDate Declared In PBWatch.h |
| pebblekit\_ios | [friendlyDescription](/docs/pebblekit-ios/Classes/PBWatch.md#//api/name/friendlyDescription) |
| Developer-friendly debugging description of the watch. - (NSString \*)friendlyDescription Return Value developer-friendly summary of the receiver, including software and hardware version information, if available. Declared In PBWatch.h |
| pebblekit\_ios | [releaseSharedSession](/docs/pebblekit-ios/Classes/PBWatch.md#//api/name/releaseSharedSession) |
| Releases the shared session to the watch (if one exists). (Deprecated: Remove usages of this method. The implementation is empty.) - (void)releaseSharedSession Discussion Depending on availability a per-app dedicated Bluetooth LE based session (CoreBluetooth.framework) will be used to talk to the watch. In other cases a Bluetooth Classic based session (ExternalAccessory.framework) will be used that is shared between all 3rd party iOS apps. Once the user is done using the app/watch-integration, the shared sessions has to be released using this method so it can be used by other apps. Declared In PBWatch.h |
| pebblekit\_ios | [golfGetIsSupported:](/docs/pebblekit-ios/Classes/PBWatch.md#//api/name/golfGetIsSupported:) |
| Queries the watch whether Golf Messages are supported. - (void)golfGetIsSupported:(void ( ^ ) ( PBWatch \*watch , BOOL isGolfSupported ))fetchedBlock Parameters fetchedBlock The block that will be called when the inquiry has finished. The block will be called asynchronously on the queue that was originally used when calling this method. watch: The watch on which the query was performed. isGolfSupported: YES if Golf Messages are supported, NO if not. Discussion Must be called from the main thread. Declared In PBWatch+Golf.h |
| pebblekit\_ios | [golfAppLaunch:](/docs/pebblekit-ios/Classes/PBWatch.md#//api/name/golfAppLaunch:) |
| Send a command to launch the golf app on the watch that the receiver represents. - (void)golfAppLaunch:(void ( ^ \_\_nullable ) ( PBWatch \*watch , NSError \*\_\_nullable error ))onSent Parameters onSent The handler that will be called when the launch command has been sent or timed out (after 1.5 secs). watch: the recipient of the command. error: nil if the operation was successful, or else an NSError with more information on why it failed. Discussion Must be called from the main thread. Declared In PBWatch+Golf.h |
| pebblekit\_ios | [golfAppKill:](/docs/pebblekit-ios/Classes/PBWatch.md#//api/name/golfAppKill:) |
| Send a command to kill the golf app on the watch that the receiver represents. - (void)golfAppKill:(void ( ^ \_\_nullable ) ( PBWatch \*watch , NSError \*\_\_nullable error ))onSent Parameters onSent The handler that will be called when the kill command has been sent or timed out (after 1.5 secs). watch: the recipient of the command. error: nil if the operation was successful, or else an NSError with more information on why it failed. Discussion Must be called from the main thread. Declared In PBWatch+Golf.h |
| pebblekit\_ios | [golfAppUpdate:onSent:](/docs/pebblekit-ios/Classes/PBWatch.md#//api/name/golfAppUpdate:onSent:) |
| Sends an update to the golf app on the watch that the receiver represents. Must be called from the main thread. - (void)golfAppUpdate:(NSDictionary \*)update onSent:(void ( ^ \_\_nullable ) ( PBWatch \*watch , NSError \*\_\_nullable error ))onSent Parameters update The update to send. Use one or more keys from PBGolfFrontKey, PBGolfMidKey, PBGolfBackKey, PBGolfHoleKey, or PBGolfParKey. Note that the value for each key MUST be of NSString type. onSent The handler that will be called when the update has been sent or timed out (after 1.5 secs). watch: the recipient of the command. error: nil if the operation was successful, or else an NSError with more information on why it failed. Declared In PBWatch+Golf.h |
| pebblekit\_ios | [golfAppAddReceiveUpdateHandler:](/docs/pebblekit-ios/Classes/PBWatch.md#//api/name/golfAppAddReceiveUpdateHandler:) |
| Add a receive handler for incoming Golf updates that are send by the Golf watch application. - (id)golfAppAddReceiveUpdateHandler:(BOOL ( ^ ) ( PBWatch \*watch , GolfAppCommand command ))onReceive Parameters onReceive The block that will be called every time a new update message arrives. watch: The receiver of the update. command: The command as sent by the watch. Return Value An opaque handle object representing the installed receive handler, that can be used in golfAppRemoveUpdateHandler: Discussion Must be called from the main thread. See Also GolfAppCommand - golfAppRemoveUpdateHandler: Declared In PBWatch+Golf.h |
| pebblekit\_ios | [golfAppRemoveUpdateHandler:](/docs/pebblekit-ios/Classes/PBWatch.md#//api/name/golfAppRemoveUpdateHandler:) |
| Removes a receive handler that was previously installed using golfAppAddReceiveUpdateHandler: - (void)golfAppRemoveUpdateHandler:(id)opaqueHandle Parameters opaqueHandle The handle object as returned by golfAppAddReceiveUpdateHandler: Discussion Must be called from the main thread. See Also - golfAppAddReceiveUpdateHandler: Declared In PBWatch+Golf.h |
| pebblekit\_ios | [golfSetTitle:icon:onSent:](/docs/pebblekit-ios/Classes/PBWatch.md#//api/name/golfSetTitle:icon:onSent:) |
| Assigns a custom title and icon to the golf app on the watch. - (void)golfSetTitle:(NSString \*)title icon:(UIImage \*)icon onSent:(void ( ^ \_\_nullable ) ( PBWatch \*watch , NSError \*\_\_nullable error ))onSent Parameters title The custom title (max. 20 bytes of UTF-8 string) icon The custom icon (max. 32x32 pixels, black/white only) onSent The handler that will be called when the title and icon have been set or timed out. watch: the recipient of the title and icon. error: nil if the operation was successful, or else an NSError with more information on why it failed. Discussion Must be called from the main thread. It is recommended to perform this as the first call after golfGetIsSupported: to avoid changing the title and icon while it is being displayed in the menu as to avoid confusion. Declared In PBWatch+Golf.h |
| pebblekit\_ios | [pingWithCookie:onPong:onTimeout:](/docs/pebblekit-ios/Classes/PBWatch.md#//api/name/pingWithCookie:onPong:onTimeout:) |
| Sends a ping to the watch. - (void)pingWithCookie:(uint32\_t)cookie onPong:(void ( ^ \_\_nullable ) ( PBWatch \*watch , uint32\_t cookie ))onPong onTimeout:(void ( ^ \_\_nullable ) ( PBWatch \*watch , uint32\_t cookie ))onTimeout Parameters cookie A number identifying the ping. onPong The block handler that will be called when the “pong” reply from the watch has been received. onTimeout The block handler that will be called when the watch failed to reply in time. Discussion Must be called from the main thread. Declared In PBWatch+Ping.h |
| pebblekit\_ios | [sportsAppSetLabel:onSent:](/docs/pebblekit-ios/Classes/PBWatch.md#//api/name/sportsAppSetLabel:onSent:) |
| Send a command to the sports app on the watch that the receiver represents, to set the preferred data label (either PACE or SPEED) and corresponding units. (Deprecated: Prefer using [PBSportsUpdate pace] or [PBSportsUpdate speed].) - (void)sportsAppSetLabel:(BOOL)isPace onSent:(void ( ^ \_\_nullable ) ( PBWatch \*watch , NSError \*\_\_nullable error ))onSent Parameters isPace YES to request the pace label or NO to request the speed label. onSent The handler that will be called when the unit command has been sent or timed out (after 1.5 secs). watch: the recipient of the command. error: nil if the operation was successful, or else an NSError with more information on why it failed. Discussion Must be called from the main thread. Declared In PBWatch+Sports.h |
| pebblekit\_ios | [sportsAppSetMetric:onSent:](/docs/pebblekit-ios/Classes/PBWatch.md#//api/name/sportsAppSetMetric:onSent:) |
| Send a command to the sports app on the watch that the receiver represents, to set the preferred unit system, either metric or imperial. (Deprecated: Prefer using [PBWatch(Sports) sportsAppSetUnitSystem:onSent:]) - (void)sportsAppSetMetric:(BOOL)isMetric onSent:(void ( ^ \_\_nullable ) ( PBWatch \*watch , NSError \*\_\_nullable error ))onSent Parameters isMetric YES to request metric units or NO to request imperial units. onSent The handler that will be called when the unit command has been sent or timed out (after 1.5 secs). watch: the recipient of the command. error: nil if the operation was successful, or else an NSError with more information on why it failed. Discussion Must be called from the main thread. Declared In PBWatch+Sports.h |
| pebblekit\_ios | [appMessagesGetIsSupported:](/docs/pebblekit-ios/Classes/PBWatch.md#//api/name/appMessagesGetIsSupported:) |
| Queries the watch whether AppMessages are supported. - (void)appMessagesGetIsSupported:(void ( ^ ) ( PBWatch \*watch , BOOL isAppMessagesSupported ))fetchedBlock Parameters fetchedBlock The block that will be called when the inquiry has finished. The block will be called asynchronously on the queue that was originally used when calling this method. watch: The watch on which the query was performed. isAppMessagesSupported: YES if AppMessages are supported, NO if not. Discussion Must be called from the main thread. Declared In PBWatch+AppMessages.h |
| pebblekit\_ios | [appMessagesPushUpdate:onSent:](/docs/pebblekit-ios/Classes/PBWatch.md#//api/name/appMessagesPushUpdate:onSent:) |
| Pushes an update to the watch application with UUID as set using [PBPebbleCentral setAppUUID:]. - (void)appMessagesPushUpdate:(NSDictionary \*)dictionary onSent:(void ( ^ \_\_nullable ) ( PBWatch \*watch , NSDictionary \*update , NSError \*\_\_nullable error ))onSent Parameters dictionary Contains the key/value pairs to update. The dictionary can only contain items with an NSNumber key and only contain NSString, NSNumber or NSData values. Use the methods in the NSNumber (stdint) category to create NSNumbers with specific types standard integer types. onSent The block that will be called when the message was accepted, rejected or timed out. watch: The watch to which the update was sent. update: The dictionary that was sent. error: If there was a problem, this will contain information about the underlying problem. See PBErrorCode for error codes. Discussion Must be called from the main thread. Declared In PBWatch+AppMessages.h |
| pebblekit\_ios | [appMessagesPushUpdate:withUUID:onSent:](/docs/pebblekit-ios/Classes/PBWatch.md#//api/name/appMessagesPushUpdate:withUUID:onSent:) |
| Pushes an update to the watch application with the specified UUID. - (void)appMessagesPushUpdate:(NSDictionary \*)dictionary withUUID:(NSUUID \*)appUUID onSent:(void ( ^ \_\_nullable ) ( PBWatch \*watch , NSDictionary \*update , NSError \*\_\_nullable error ))onSent Parameters dictionary Contains the key/value pairs to update. The dictionary can only contain items with an NSNumber key and only contain NSString, NSNumber or NSData values. Use the methods in the NSNumber (stdint) category to create NSNumbers with specific types standard integer types. appUUID The UUID of the watchapp to which the update should be sent. onSent The block that will be called when the message was accepted, rejected or timed out. watch: The watch to which the update was sent. update: The dictionary that was sent. error: If there was a problem, this will contain information about the underlying problem. See PBErrorCode for error codes. Discussion Must be called from the main thread. Declared In PBWatch+AppMessages.h |
| pebblekit\_ios | [appMessagesAddReceiveUpdateHandler:](/docs/pebblekit-ios/Classes/PBWatch.md#//api/name/appMessagesAddReceiveUpdateHandler:) |
| Add a receive handler for incoming updates that are send by the watch application with UUID as set using [PBPebbleCentral setAppUUID:]. - (id)appMessagesAddReceiveUpdateHandler:(BOOL ( ^ ) ( PBWatch \*watch , NSDictionary \*update ))onReceive Parameters onReceive The block that will be called every time a new update message arrives. watch: The watch that has sent the update. update: The dictionary containing the values sent by the watch. Return Value An opaque handle object representing the installed receive handler, that can be used in appMessagesRemoveUpdateHandler: Discussion Must be called from the main thread. See Also - appMessagesRemoveUpdateHandler: Declared In PBWatch+AppMessages.h |
| pebblekit\_ios | [appMessagesAddReceiveUpdateHandler:withUUID:](/docs/pebblekit-ios/Classes/PBWatch.md#//api/name/appMessagesAddReceiveUpdateHandler:withUUID:) |
| Add a receive handler for incoming updates that are send by the watch application with the specified UUID. - (id)appMessagesAddReceiveUpdateHandler:(BOOL ( ^ ) ( PBWatch \*watch , NSDictionary \*update ))onReceive withUUID:(NSUUID \*)appUUID Parameters onReceive The block that will be called every time a new update message arrives. You should always return YES so than an ACK is sent to the watch. watch: The watch that has sent the update. update: The dictionary containing the values sent by the watch. appUUID The UUID of the watchapp for which sent messages should be handled by the onReceive block. Return Value An opaque handle object representing the installed receive handler, that can be used in appMessagesRemoveUpdateHandler: Discussion Must be called from the main thread. See Also - appMessagesRemoveUpdateHandler: Declared In PBWatch+AppMessages.h |
| pebblekit\_ios | [appMessagesRemoveUpdateHandler:](/docs/pebblekit-ios/Classes/PBWatch.md#//api/name/appMessagesRemoveUpdateHandler:) |
| Removes a receive handler that was previously installed using appMessagesAddReceiveUpdateHandler: - (void)appMessagesRemoveUpdateHandler:(id)opaqueHandle Parameters opaqueHandle The handle object as returned by appMessagesAddReceiveUpdateHandler: Discussion Must be called from the main thread. See Also - appMessagesAddReceiveUpdateHandler: Declared In PBWatch+AppMessages.h |
| pebblekit\_ios | [appMessagesLaunch:](/docs/pebblekit-ios/Classes/PBWatch.md#//api/name/appMessagesLaunch:) |
| Sends a command to launch the watch application with UUID as set using [PBPebbleCentral setAppUUID:] - (void)appMessagesLaunch:(void ( ^ \_\_nullable ) ( PBWatch \*watch , NSError \*\_\_nullable error ))onSent Parameters onSent The block that will be called after the launch command has been sent to the watch. watch: The watch to which the command was sent. error: If there was a problem, this will contain information about the underlying problem. See PBErrorCode for error codes. Discussion Must be called from the main thread. Declared In PBWatch+AppMessages.h |
| pebblekit\_ios | [appMessagesLaunch:withUUID:](/docs/pebblekit-ios/Classes/PBWatch.md#//api/name/appMessagesLaunch:withUUID:) |
| Sends a command to launch the watch application with the specified UUID. - (void)appMessagesLaunch:(void ( ^ \_\_nullable ) ( PBWatch \*watch , NSError \*\_\_nullable error ))onSent withUUID:(NSUUID \*)appUUID Parameters onSent The block that will be called after the launch command has been sent to the watch. watch: The watch to which the command was sent. error: If there was a problem, this will contain information about the underlying problem. See PBErrorCode for error codes. appUUID The UUID of the watch application to launch. Discussion Must be called from the main thread. Declared In PBWatch+AppMessages.h |
| pebblekit\_ios | [appMessagesKill:](/docs/pebblekit-ios/Classes/PBWatch.md#//api/name/appMessagesKill:) |
| Sends a command to kill the watch application with UUID as set using [PBPebbleCentral setAppUUID:]. - (void)appMessagesKill:(void ( ^ \_\_nullable ) ( PBWatch \*watch , NSError \*\_\_nullable error ))onSent Parameters onSent The block that will be called after the kill command has been sent to the watch. watch: The watch to which the command was sent. error: If there was a problem, this will contain information about the underlying problem. See PBErrorCode for error codes. Discussion Must be called from the main thread. Declared In PBWatch+AppMessages.h |
| pebblekit\_ios | [appMessagesKill:withUUID:](/docs/pebblekit-ios/Classes/PBWatch.md#//api/name/appMessagesKill:withUUID:) |
| Sends a command to kill the watch application with the specified UUID. - (void)appMessagesKill:(void ( ^ \_\_nullable ) ( PBWatch \*watch , NSError \*\_\_nullable error ))onSent withUUID:(NSUUID \*)appUUID Parameters onSent The block that will be called after the kill command has been sent to the watch. watch: The watch to which the command was sent. error: If there was a problem, this will contain information about the underlying problem. See PBErrorCode for error codes. appUUID The UUID of the watch application to launch. Discussion Must be called from the main thread. Declared In PBWatch+AppMessages.h |
| pebblekit\_ios | [closeSession:](/docs/pebblekit-ios/Classes/PBWatch.md#//api/name/closeSession:) |
| Closes the communication session with the watch. (Deprecated: Use [PBWatch releaseSharedSession]) - (void)closeSession:(void ( ^ \_\_nullable ) ( void ))onDone Parameters onDone Callback block that will be called after the closing of the session has completed. If there is no open session, the onDone block will (also) be executed asynchronously on the calling queue. Discussion Since there is only one, shared session for all 3rd party iOS apps, an app should close the session after the user is done using the app/watch-integration, so it can be used by other apps. The communication session is implicitely opened automatically when needed. Declared In PBWatch+Legacy.h |
| pebblekit\_ios | [sportsGetIsSupported:](/docs/pebblekit-ios/Classes/PBWatch.md#//api/name/sportsGetIsSupported:) |
| Queries the watch whether Sports Messages are supported. - (void)sportsGetIsSupported:(void ( ^ ) ( PBWatch \*watch , BOOL isSportsSupported ))fetchedBlock Parameters fetchedBlock The block that will be called when the inquiry has finished. The block will be called asynchronously on the queue that was originally used when calling this method. watch: the recipient of the query. isSportsSupported: YES if Sports API is supported, NO otherwise. Discussion Must be called from the main thread. Declared In PBWatch+Sports.h |
| pebblekit\_ios | [sportsAppLaunch:](/docs/pebblekit-ios/Classes/PBWatch.md#//api/name/sportsAppLaunch:) |
| Send a command to launch the sports app on the watch that the receiver represents. - (void)sportsAppLaunch:(void ( ^ \_\_nullable ) ( PBWatch \*watch , NSError \*\_\_nullable error ))onSent Parameters onSent The handler that will be called when the launch command has been sent or timed out (after 1.5 secs). watch: the recipient of the command. error: nil if the operation was successful, or else an NSError with more information on why it failed. Discussion Must be called from the main thread, and before sportsAppSetMetric:onSent: or sportsAppUpdate:onSent:. Declared In PBWatch+Sports.h |
| pebblekit\_ios | [sportsAppKill:](/docs/pebblekit-ios/Classes/PBWatch.md#//api/name/sportsAppKill:) |
| Send a command to kill the sports app on the watch that the receiver represents. - (void)sportsAppKill:(void ( ^ \_\_nullable ) ( PBWatch \*watch , NSError \*\_\_nullable error ))onSent Parameters onSent The handler that will be called when the kill command has been sent or timed out (after 1.5 secs). watch: the recipient of the command. error: nil if the operation was successful, or else an NSError with more information on why it failed. Discussion Must be called from the main thread. Declared In PBWatch+Sports.h |
| pebblekit\_ios | [sportsAppSetUnitSystem:onSent:](/docs/pebblekit-ios/Classes/PBWatch.md#//api/name/sportsAppSetUnitSystem:onSent:) |
| Send a command to the sports app on the watch that the receiver represents, to set the preferred unit system. - (void)sportsAppSetUnitSystem:(PBUnitSystem)unitSystem onSent:(void ( ^ \_\_nullable ) ( PBWatch \*watch , NSError \*\_\_nullable error ))onSent Parameters unitSystem PBUnitSystemMetric to request metric units or PBUnitSystemImperial to request imperial units. onSent The handler that will be called when the unit command has been sent or timed out (after 1.5 secs). watch: the recipient of the command. error: nil if the operation was successful, or else an NSError with more information on why it failed. Discussion Must be called from the main thread. Declared In PBWatch+Sports.h |
| pebblekit\_ios | [sportsAppSetActivityState:onSent:](/docs/pebblekit-ios/Classes/PBWatch.md#//api/name/sportsAppSetActivityState:onSent:) |
| Send a command to the sports app on the watch that the receiver represents, to set the state of the sports activity. Currently only SportsAppActivityStateRunning and SportsAppActivityStatePaused are supported. - (void)sportsAppSetActivityState:(SportsAppActivityState)state onSent:(void ( ^ \_\_nullable ) ( PBWatch \*watch , NSError \*\_\_nullable error ))onSent Parameters state The new sports activity state onSent The handler that will be called when the unit command has been sent or timed out (after 1.5 secs). watch: the recipient of the command. error: nil if the operation was successful, or else an NSError with more information on why it failed. Discussion Must be called from the main thread. Declared In PBWatch+Sports.h |
| pebblekit\_ios | [sportsAppUpdate:onSent:](/docs/pebblekit-ios/Classes/PBWatch.md#//api/name/sportsAppUpdate:onSent:) |
| Sends the update to the sports app on the watch that the receiver represents. - (void)sportsAppUpdate:(NSDictionary \*)update onSent:(void ( ^ \_\_nullable ) ( PBWatch \*watch , NSError \*\_\_nullable error ))onSent Parameters update The update to send. onSent The handler that will be called when the unit command has been sent or timed out (after 1.5 secs). watch: the recipient of the command. error: nil if the operation was successful, or else an NSError with more information on why it failed. Discussion Must be called from the main thread. The valid keys and values for the dictionary are the following: PBSportsTimeKey: the string representing the time. The value must be an NSString. The maximum number of characters is about 8. PBSportsDistanceKey: the string representing the distance. The value must be an NSString. The maximum number of characters is about 5. PBSportsDataKey: the string representing the pace or the speed. The value must be an NSString. The maximum number of characters is about 5. PBSportsActivityStateKey: the state of the activity. The value must be an NSNumber created using +[NSNumber(stdint) pb\_numberWithUint8:]. The value must be one of the values from the enum SportsAppActivityState. PBSportsIsPaceKey: whether the value sent in PBSportsDataKey is the pace (use value 1) or the speed (use value 0). You don’t need to continously send this value. The value must be an NSNumber created using +[NSNumber(stdin) pb\_numberWithUint8:]. PBSportsHeartBPMKey: the current heart rate in beats per minute. The value must be an NSNumber created using [NSNumber(stdin) pb\_numberWithUint8:]. PBSportsCustomLabelKey: the string to show as a custom label. The value must be an NSString. The maximum number of characters is about 10. The string will be transformed into upper case before being sent to the watch. PBSportsCustomValueKey: the string to show as a custom value. The value must be an NSString. The maximum number of characters is about 8. Declared In PBWatch+Sports.h |
| pebblekit\_ios | [sportsAppAddReceiveUpdateHandler:](/docs/pebblekit-ios/Classes/PBWatch.md#//api/name/sportsAppAddReceiveUpdateHandler:) |
| Add a receive handler for incoming Sports updates that are send by the Sports watch application. - (id)sportsAppAddReceiveUpdateHandler:(BOOL ( ^ ) ( PBWatch \*watch , SportsAppActivityState state ))onReceive Parameters onReceive The block that will be called every time a new update message arrives. watch: The watch that has sent the update. state: The new sports activity state as set by the watch. Return Value An opaque handle object representing the installed receive handler, that can be used in sportsAppRemoveUpdateHandler:. Discussion Must be called from the main thread. See Also SportsAppActivityState - sportsAppRemoveUpdateHandler: Declared In PBWatch+Sports.h |
| pebblekit\_ios | [sportsAppRemoveUpdateHandler:](/docs/pebblekit-ios/Classes/PBWatch.md#//api/name/sportsAppRemoveUpdateHandler:) |
| Removes a receive handler that was previously installed using sportsAppAddReceiveUpdateHandler:. - (void)sportsAppRemoveUpdateHandler:(id)opaqueHandle Parameters opaqueHandle The handle object as returned by sportsAppAddReceiveUpdateHandler: Discussion Must be called from the main thread. See Also - sportsAppAddReceiveUpdateHandler: Declared In PBWatch+Sports.h |
| pebblekit\_ios | [sportsSetTitle:icon:onSent:](/docs/pebblekit-ios/Classes/PBWatch.md#//api/name/sportsSetTitle:icon:onSent:) |
| Assigns a custom title and icon to the sports app on the watch. - (void)sportsSetTitle:(NSString \*)title icon:(UIImage \*)icon onSent:(void ( ^ \_\_nullable ) ( PBWatch \*watch , NSError \*\_\_nullable error ))onSent Parameters title The custom title (max. 20 bytes of UTF-8 string) icon The custom icon (max. 32x32 pixels, black/white only). This image cannot be nil. onSent The handler that will be called when the title and icon have been set or timed out. watch: the recipient of the custom title and icon. error: nil if the operation was successful, or else an NSError with more information on why it failed. Discussion Must be called from the main thread.It is recommended to perform this as the first call after sportsGetIsSupported: to avoid changing the title and icon while it is being displayed in the menu as to avoid confusion. Declared In PBWatch+Sports.h |
| pebblekit\_ios | [PBResourceMetadata](/docs/pebblekit-ios/Classes/PBResourceMetadata.md) |
| |
| pebblekit\_ios | [timestamp](/docs/pebblekit-ios/Classes/PBResourceMetadata.md#//api/name/timestamp) |
| The version of the resources as the Epoch timestamp of the Git commit. @property (nonatomic, readonly) uint32\_t timestamp Declared In PBResourceMetadata.h |
| pebblekit\_ios | [crc](/docs/pebblekit-ios/Classes/PBResourceMetadata.md#//api/name/crc) |
| The checksum of the resources. @property (nonatomic, readonly) uint32\_t crc Declared In PBResourceMetadata.h |
| pebblekit\_ios | [PBDataLoggingSessionMetadata](/docs/pebblekit-ios/Classes/PBDataLoggingSessionMetadata.md) |
| |
| pebblekit\_ios | [tag](/docs/pebblekit-ios/Classes/PBDataLoggingSessionMetadata.md#//api/name/tag) |
| A tag associated with the session. @property (nonatomic, readonly) uint32\_t tag Declared In PBDataLoggingService.h |
| pebblekit\_ios | [timestamp](/docs/pebblekit-ios/Classes/PBDataLoggingSessionMetadata.md#//api/name/timestamp) |
| The timestamp of the moment the session was created by the watchapp. @property (nonatomic, readonly) uint32\_t timestamp Declared In PBDataLoggingService.h |
| pebblekit\_ios | [type](/docs/pebblekit-ios/Classes/PBDataLoggingSessionMetadata.md#//api/name/type) |
| The type of data stored in this session. @property (nonatomic, readonly) PBDataLoggingType type Declared In PBDataLoggingService.h |
| pebblekit\_ios | [itemSize](/docs/pebblekit-ios/Classes/PBDataLoggingSessionMetadata.md#//api/name/itemSize) |
| The size of a data item. @property (nonatomic, readonly) uint16\_t itemSize Declared In PBDataLoggingService.h |
| pebblekit\_ios | [serialNumber](/docs/pebblekit-ios/Classes/PBDataLoggingSessionMetadata.md#//api/name/serialNumber) |
| The serial number of the watch that created the sessions. @property (nonatomic, copy, readonly) NSString \*serialNumber Declared In PBDataLoggingService.h |
| pebblekit\_ios | [metadataWithTag:timestamp:type:itemSize:serialNumber:](/docs/pebblekit-ios/Classes/PBDataLoggingSessionMetadata.md#//api/name/metadataWithTag:timestamp:type:itemSize:serialNumber:) |
| Creates a new data logging session metadata object, given all its property values. This method is provided to create a metadata object that can be used to compare it with a metadata object that is passed into one of the PBDataLoggingServiceDelegate methods. + (instancetype)metadataWithTag:(uint32\_t)tag timestamp:(uint32\_t)timestamp type:(PBDataLoggingType)type itemSize:(uint16\_t)itemSize serialNumber:(NSString \*)serialNumber Parameters tag The tag associated with the session timestamp The timestamp of the creation of the session type The type of data stored in the session itemSize The size of a data item serialNumber The serial number of the watch that created the session Return Value A session metadata object with the specified information Declared In PBDataLoggingService.h |
| pebblekit\_ios | [isEqual:](/docs/pebblekit-ios/Classes/PBDataLoggingSessionMetadata.md#//api/name/isEqual:) |
| Tests the equality of the recipient and the given object. - (BOOL)isEqual:(nullable id)object Parameters object The object to check against. Return Value YES if all the property values of the receiver are equal to the property values of the other object. Discussion This method can be used to compare two sessions’ metadata objects to check whether they are referring to the same session or not. Declared In PBDataLoggingService.h |
| pebblekit\_ios | [isEqualToDataLoggingSessionMetadata:](/docs/pebblekit-ios/Classes/PBDataLoggingSessionMetadata.md#//api/name/isEqualToDataLoggingSessionMetadata:) |
| Tests the equality of two data logging sessions’ metadata objects. - (BOOL)isEqualToDataLoggingSessionMetadata:(PBDataLoggingSessionMetadata \*)sessionMetadata Parameters sessionMetadata The session metadata to compare against. Return Value YES if all the property values of the receiver are equal to the property values of the given session. Discussion This method can be used to compare two sessions’ metadata objects to check whether they are referring to the same session or not.Note: Equivalent to [PBDataLoggingSessionMetadata isEqual:] Declared In PBDataLoggingService.h |
| pebblekit\_ios | [PBBitmap](/docs/pebblekit-ios/Classes/PBBitmap.md) |
| |
| pebblekit\_ios | [pixelData](/docs/pebblekit-ios/Classes/PBBitmap.md#//api/name/pixelData) |
| The pixel data of the bitmap. This corresponds to the data as pointed to by GBitmap’s addr field. @property (nonatomic, readonly, strong) NSData \*pixelData Declared In PBBitmap.h |
| pebblekit\_ios | [rowSizeBytes](/docs/pebblekit-ios/Classes/PBBitmap.md#//api/name/rowSizeBytes) |
| The number of bytes per row. Always a multiple of 4 bytes. @property (nonatomic, readonly, assign) uint16\_t rowSizeBytes Declared In PBBitmap.h |
| pebblekit\_ios | [infoFlags](/docs/pebblekit-ios/Classes/PBBitmap.md#//api/name/infoFlags) |
| Bitfield of metadata flags. This corresponds to GBitmap’s info\_flags field. @property (nonatomic, readonly, assign) uint16\_t infoFlags Declared In PBBitmap.h |
| pebblekit\_ios | [bounds](/docs/pebblekit-ios/Classes/PBBitmap.md#//api/name/bounds) |
| The box of bits inside pixelData, that contains the actual image data to use. This corresponds to GBitmap’s bounds field. @property (nonatomic, readonly, assign) GRect bounds Declared In PBBitmap.h |
| pebblekit\_ios | [pebbleBitmapWithUIImage:](/docs/pebblekit-ios/Classes/PBBitmap.md#//api/name/pebbleBitmapWithUIImage:) |
| Factory method to create a PBBitmap from a UIImage instance. + (PBBitmap \*)pebbleBitmapWithUIImage:(UIImage \*)image Parameters image The UIImage from which to create the PBBitmap Declared In PBBitmap.h |
| pebblekit\_ios | [PBSportsUpdate](/docs/pebblekit-ios/Classes/PBSportsUpdate.md) |
| |
| pebblekit\_ios | [time](/docs/pebblekit-ios/Classes/PBSportsUpdate.md#//api/name/time) |
| The current time in seconds. @property (nonatomic) NSTimeInterval time Discussion The possible range is currently limited from -35999 to 35999, inclusive (±9h 59min 59sec). Values larger or smaller than the limits will be transformed into the maximum or minimum, respectively. It will be presented as a duration string in the UI. Hours, minutes and seconds will be separated by colons. The hours value will only appear if the value is more than 1 hour. The decimal part will be discarded for the presentation. Declared In PBWatch+Sports.h |
| pebblekit\_ios | [distance](/docs/pebblekit-ios/Classes/PBSportsUpdate.md#//api/name/distance) |
| The current distance in kilometers or miles. @property (nonatomic) float distance Discussion The possible range is currently limited from -99.9 to 99.9, inclusive. Values larger or smaller than the limits will be transformed into the maximum or minimum, respectively. It will be presented as a decimal number in the UI. The decimal part will be rounded to one digit. The unit of distance is dependent on the current unit setting. See Also [PBWatch sportsAppSetMetric:onSent:] Declared In PBWatch+Sports.h |
| pebblekit\_ios | [pace](/docs/pebblekit-ios/Classes/PBSportsUpdate.md#//api/name/pace) |
| The current pace in seconds per kilometer or seconds per mile. @property (nonatomic) NSTimeInterval pace Discussion The possible range is currently limited from -3599 to 3599, inclusive (±59min 59sec). Values larger or smaller than the limits will be transformed into the maximum or minimum, respectively. It will be presented as a duration string in the UI. Minutes and seconds will be separated by colons. The decimal part will be discarded for the presentation. Currently pace and speed cannot be presented at the same time. Setting speed will discard the value set through pace. Declared In PBWatch+Sports.h |
| pebblekit\_ios | [speed](/docs/pebblekit-ios/Classes/PBSportsUpdate.md#//api/name/speed) |
| The current speed in kilometers per hour or miles per hour. @property (nonatomic) float speed Discussion The possible range is currently limited from -99.9 to 99.9, inclusive. Values larger or smaller than the limits will be transformed into the maximum or minimum, respectively. It will be presented as a decimal number in the UI. The decimal part will be rounded to one digit. Currently pace and speed cannot be presented at the same time. Setting pace will discard the value set through speed. Declared In PBWatch+Sports.h |
| pebblekit\_ios | [heartRate](/docs/pebblekit-ios/Classes/PBSportsUpdate.md#//api/name/heartRate) |
| The current heart rate in beats per minute. @property (nonatomic) uint8\_t heartRate Discussion Currently there’s no way to stop sending heart rate values if one heart rate value was sent. The last value will be shown in the UI. If the heart rate has never been set before, this property will return zero. Declared In PBWatch+Sports.h |
| pebblekit\_ios | [customLabel](/docs/pebblekit-ios/Classes/PBSportsUpdate.md#//api/name/customLabel) |
| A custom label to show in the sports UI. @property (nonatomic, copy, nullable) NSString \*customLabel Discussion The maximum number of characters is ~10, but this maximum is not enforced. The label will be sent in upper case to the watch. To be sent, both customLabel and customValue have to be set to non-nil values. Declared In PBWatch+Sports.h |
| pebblekit\_ios | [customValue](/docs/pebblekit-ios/Classes/PBSportsUpdate.md#//api/name/customValue) |
| A custom value to show in the sports UI. @property (nonatomic, copy, nullable) NSString \*customValue Discussion The maximum number of characters is ~8, but the maximum is not enforced. To be sent, both customValue and customLabel have to be set to non-nil values. Declared In PBWatch+Sports.h |
| pebblekit\_ios | [appMessageDictionary](/docs/pebblekit-ios/Classes/PBSportsUpdate.md#//api/name/appMessageDictionary) |
| Creates an update dictionary from the receiver, that can be used with [PBWatch sportsAppUpdate:onSent:]. @property (nonatomic, readonly) NSDictionary \*appMessageDictionary Discussion You should prefer using [PBSportsUpdate updateWatch:completion:]. See Also [PBWatch sportsAppUpdate:onSent:] Declared In PBWatch+Sports.h |
| pebblekit\_ios | [updateWatch:completion:](/docs/pebblekit-ios/Classes/PBSportsUpdate.md#//api/name/updateWatch:completion:) |
| Sends an update to the watch. - (void)updateWatch:(PBWatch \*)watch completion:(void ( ^ \_\_nullable ) ( NSError \*\_\_nullable error ))completion Parameters watch The watch to send the update to. completion Block that will be called when the update either succeeds or fails. error: nil if the operation was successful, or else an NSError with more information on why it failed. Discussion The method tries to send the minimal set of changes since the last time the method was used, to try to minimize communication with the watch. Declared In PBWatch+Sports.h |
| pebblekit\_ios | [timeStringFromSeconds:](/docs/pebblekit-ios/Classes/PBSportsUpdate.md#//api/name/timeStringFromSeconds:) |
| Creates a formatted time string from a total seconds value, formatted as “h:mm:ss”. + (NSString \*)timeStringFromSeconds:(NSTimeInterval)seconds Parameters seconds The number of seconds from which to create the time string. Return Value Formatted time as “h:mm:ss” Discussion For example, supplying the value 3930.0f seconds will return @“1:05:30”. Declared In PBWatch+Sports.h |
| pebblekit\_ios | [decimalStringFromFloat:](/docs/pebblekit-ios/Classes/PBSportsUpdate.md#//api/name/decimalStringFromFloat:) |
| Creates a formatted decimal string with one decimal number. + (NSString \*)decimalStringFromFloat:(float)decimal Parameters decimal The decimal number to format as a string. Return Value The formatted decimal number. Discussion For example, supplying the value 13.42f will return @“13.4”. Declared In PBWatch+Sports.h |
| pebblekit\_ios | [data](/docs/pebblekit-ios/Classes/PBSportsUpdate.md#//api/name/data) |
| General purpose data variable. (Deprecated: Prefer either pace or speed.) @property (nonatomic) float data Discussion Note: The original property design is very broken and it has been deprecated in favor of both pace and speed. This value will act as pace from now on. The possible range is currently limited from -3599 to 3599, inclusive (±59min 59sec). Values larger or smaller than the limits will be transformed into the maximum or minimum, respectively. It will be presented as a duration string in the UI. Minutes and seconds will be separated by colons. The decimal part will be discarded for the presentation. Setting a value in either pace or speed will discard the value set through data. See Also [PBWatch sportsAppSetLabel:onSent:] Declared In PBWatch+Sports.h |
| pebblekit\_ios | [updateWithTime:distance:data:](/docs/pebblekit-ios/Classes/PBSportsUpdate.md#//api/name/updateWithTime:distance:data:) |
| Creates a new PBSportsUpdate with the given time, distance and data. (Deprecated: Prefer -[PBSportsUpdate init] and filling the properties.) + (instancetype)updateWithTime:(NSTimeInterval)time distance:(float)distance data:(float)data Parameters time The current time in seconds. distance The current distance in kilometers or miles. data General purpose data variable. Return Value A new PBSportsUpdate with the given time, distance and data. Declared In PBWatch+Sports.h |
| pebblekit\_ios | [dictionary](/docs/pebblekit-ios/Classes/PBSportsUpdate.md#//api/name/dictionary) |
| Creates an update dictionary from the receiver that can be used with [PBWatch sportsAppUpdate:onSent:]. (Deprecated: Prefer using -[PBSportsUpdate appMessageDictionary].) - (NSDictionary \*)dictionary See Also [PBWatch sportsAppUpdate:onSent:] Declared In PBWatch+Sports.h |
| pebblekit\_ios | [timeStringFromFloat:](/docs/pebblekit-ios/Classes/PBSportsUpdate.md#//api/name/timeStringFromFloat:) |
| Creates a formatted time string from a total seconds value, formatted as “h:mm:ss”. (Deprecated: Prefer +[PBSportsUpdate timeStringFromSeconds:].) + (NSString \*)timeStringFromFloat:(float)seconds Parameters seconds The number of seconds from which to create the time string. Return Value Formatted time as “h:mm:ss” Discussion For example, supplying the value 3930.0f seconds will return @“1:05:30”. Declared In PBWatch+Sports.h |
| pebblekit\_ios | [PBVersionInfo](/docs/pebblekit-ios/Classes/PBVersionInfo.md) |
| |
| pebblekit\_ios | [runningFirmwareMetadata](/docs/pebblekit-ios/Classes/PBVersionInfo.md#//api/name/runningFirmwareMetadata) |
| The metadata of the firmware that is running. @property (nonatomic, readonly, strong, nullable) PBFirmwareMetadata \*runningFirmwareMetadata Declared In PBVersionInfo.h |
| pebblekit\_ios | [recoveryFirmwareMetadata](/docs/pebblekit-ios/Classes/PBVersionInfo.md#//api/name/recoveryFirmwareMetadata) |
| The metadata of the recovery firmware that is in storage. @property (nonatomic, readonly, strong, nullable) PBFirmwareMetadata \*recoveryFirmwareMetadata Declared In PBVersionInfo.h |
| pebblekit\_ios | [systemResources](/docs/pebblekit-ios/Classes/PBVersionInfo.md#//api/name/systemResources) |
| The metadata of the system resources. @property (nonatomic, readonly, strong) PBResourceMetadata \*systemResources Declared In PBVersionInfo.h |
| pebblekit\_ios | [bootloaderVersion](/docs/pebblekit-ios/Classes/PBVersionInfo.md#//api/name/bootloaderVersion) |
| The version of the bootloader. @property (nonatomic, readonly) UInt32 bootloaderVersion Declared In PBVersionInfo.h |
| pebblekit\_ios | [hardwareVersion](/docs/pebblekit-ios/Classes/PBVersionInfo.md#//api/name/hardwareVersion) |
| The version of the hardware. @property (nonatomic, readonly, strong) NSString \*hardwareVersion Declared In PBVersionInfo.h |
| pebblekit\_ios | [serialNumber](/docs/pebblekit-ios/Classes/PBVersionInfo.md#//api/name/serialNumber) |
| The serial number. @property (nonatomic, readonly, strong) NSString \*serialNumber Declared In PBVersionInfo.h |
| pebblekit\_ios | [deviceAddress](/docs/pebblekit-ios/Classes/PBVersionInfo.md#//api/name/deviceAddress) |
| The current Bluetooth device address. @property (nonatomic, readonly, strong) NSData \*deviceAddress Declared In PBVersionInfo.h |
| pebblekit\_ios | [remoteProtocolCapabilitiesFlags](/docs/pebblekit-ios/Classes/PBVersionInfo.md#//api/name/remoteProtocolCapabilitiesFlags) |
| Flags for the supported protocol features of the watch. @property (nonatomic, readonly, assign) PBRemoteProtocolCapabilitiesFlags remoteProtocolCapabilitiesFlags Declared In PBVersionInfo.h |
| pebblekit\_ios | [hasBeenUnfaithful](/docs/pebblekit-ios/Classes/PBVersionInfo.md#//api/name/hasBeenUnfaithful) |
| Indicates if the previous connection for the watch was to this device. @property (nonatomic, readonly, assign) BOOL hasBeenUnfaithful Discussion If the watch has been connected to this device, but connects to other device before connecting again to this device, the value will be YES. Declared In PBVersionInfo.h |
| pebblekit\_ios | [hasRecoveryFirmware](/docs/pebblekit-ios/Classes/PBVersionInfo.md#//api/name/hasRecoveryFirmware) |
| YES if valid recovery firmware is installed, NO if not. - (BOOL)hasRecoveryFirmware Declared In PBVersionInfo.h |
| pebblekit\_ios | [hasSystemResources](/docs/pebblekit-ios/Classes/PBVersionInfo.md#//api/name/hasSystemResources) |
| YES if valid system resources are installed, NO if not. - (BOOL)hasSystemResources Declared In PBVersionInfo.h |
| pebblekit\_ios | [appMessagesSupported](/docs/pebblekit-ios/Classes/PBVersionInfo.md#//api/name/appMessagesSupported) |
| YES if app messages are supported, NO if not. - (BOOL)appMessagesSupported Declared In PBVersionInfo.h |
| pebblekit\_ios | [PBPebbleCentral](/docs/pebblekit-ios/Classes/PBPebbleCentral.md) |
| |
| pebblekit\_ios | [connectedWatches](/docs/pebblekit-ios/Classes/PBPebbleCentral.md#//api/name/connectedWatches) |
| The watches that are currently connected. Do not cache the array because it can change over time. @property (nonatomic, readonly, copy) NSArray \*connectedWatches Declared In PBPebbleCentral.h |
| pebblekit\_ios | [registeredWatches](/docs/pebblekit-ios/Classes/PBPebbleCentral.md#//api/name/registeredWatches) |
| The watches that are stored in the user preferences of the application. @property (nonatomic, readonly, copy) NSArray \*registeredWatches Declared In PBPebbleCentral.h |
| pebblekit\_ios | [delegate](/docs/pebblekit-ios/Classes/PBPebbleCentral.md#//api/name/delegate) |
| The central’s delegate. @property (nonatomic, readwrite, weak) id \_\_nullable delegate Declared In PBPebbleCentral.h |
| pebblekit\_ios | [appUUID](/docs/pebblekit-ios/Classes/PBPebbleCentral.md#//api/name/appUUID) |
| Identifier of the watch application this companion app communicates with. @property (nonatomic, copy) NSUUID \*appUUID Discussion The identifier is used to make sure that app message and data logging communications arrive to the right companion watch app in the watch (and not to another app). For most app message methods there is are two variants: one that does not take an UUID parameter and one that does (for example, -appMessagesAddReceiveUpdateHandler: vs -appMessagesAddReceiveUpdateHandler:withUUID:). The methods that do not take an UUID, will use the UUID as set prior to this property.Note: The UUID needs to be set before using either app message or data logging. Declared In PBPebbleCentral.h |
| pebblekit\_ios | [appUUIDs](/docs/pebblekit-ios/Classes/PBPebbleCentral.md#//api/name/appUUIDs) |
| The list of App-UUIDs this PebbleCentral wants to talk to. @property (nonatomic, copy) NSSet \*appUUIDs See Also - addAppUUID: Declared In PBPebbleCentral.h |
| pebblekit\_ios | [addAppUUID:](/docs/pebblekit-ios/Classes/PBPebbleCentral.md#//api/name/addAppUUID:) |
| Registers a new App-UUID with appUUIDs. - (void)addAppUUID:(NSUUID \*)appUUID Parameters appUUID The app UUID to register. See Also @property appUUIDs Declared In PBPebbleCentral.h |
| pebblekit\_ios | [run](/docs/pebblekit-ios/Classes/PBPebbleCentral.md#//api/name/run) |
| Registers and announces internal Bluetooth services. Might cause a dialog to allow this app to talk to other devices. - (void)run Declared In PBPebbleCentral.h |
| pebblekit\_ios | [isMobileAppInstalled](/docs/pebblekit-ios/Classes/PBPebbleCentral.md#//api/name/isMobileAppInstalled) |
| Determines if the Pebble iOS app is installed in the device. - (BOOL)isMobileAppInstalled Return Value YES if the Pebble iOS app is installed, NO if it is not installed. Discussion Note: Since iOS 9.0 you have to add “pebble” to LSApplicationQueriesSchemes in your application Info.plist or this method will return NO all the time. Declared In PBPebbleCentral.h |
| pebblekit\_ios | [installMobileApp](/docs/pebblekit-ios/Classes/PBPebbleCentral.md#//api/name/installMobileApp) |
| Redirects to Pebble in the App Store, so the user can install the app. - (void)installMobileApp Declared In PBPebbleCentral.h |
| pebblekit\_ios | [unregisterAllWatches](/docs/pebblekit-ios/Classes/PBPebbleCentral.md#//api/name/unregisterAllWatches) |
| Wipes out the data associated with the registered watches, that is stored on the phone. - (void)unregisterAllWatches Declared In PBPebbleCentral.h |
| pebblekit\_ios | [lastConnectedWatch](/docs/pebblekit-ios/Classes/PBPebbleCentral.md#//api/name/lastConnectedWatch) |
| Returns the most recently connected watch from the registeredWatches array. - (PBWatch \*\_\_nullable)lastConnectedWatch Declared In PBPebbleCentral.h |
| pebblekit\_ios | [dataLoggingServiceForAppUUID:](/docs/pebblekit-ios/Classes/PBPebbleCentral.md#//api/name/dataLoggingServiceForAppUUID:) |
| Returns the DataLoggingService for a (previously registered) appUUID - (PBDataLoggingService \*\_\_nullable)dataLoggingServiceForAppUUID:(NSUUID \*)appUUID Parameters appUUID The app UUID to recover the data logging service. Declared In PBPebbleCentral.h |
| pebblekit\_ios | [defaultCentral](/docs/pebblekit-ios/Classes/PBPebbleCentral.md#//api/name/defaultCentral) |
| The default central singleton instance. + (instancetype)defaultCentral Return Value The default central singleton instance. Declared In PBPebbleCentral+DefaultCentral.h |
| pebblekit\_ios | [hasValidAppUUID](/docs/pebblekit-ios/Classes/PBPebbleCentral.md#//api/name/hasValidAppUUID) |
| Indicates if the central has been correctly configured with an app UUID. (Deprecated: Use appUUID != nil instead.) - (BOOL)hasValidAppUUID Declared In PBPebbleCentral+Legacy.h |
| pebblekit\_ios | [setDebugLogsEnabled:](/docs/pebblekit-ios/Classes/PBPebbleCentral.md#//api/name/setDebugLogsEnabled:) |
| Enables or disables debug logging for PebbleKit. (Deprecated: Use +[PBPebbleKitLogging setLogLevel:] instead.) + (void)setDebugLogsEnabled:(BOOL)logsEnabled Parameters logsEnabled Whether logging should be enabled or not. Declared In PBPebbleCentral+Legacy.h |
| pebblekit\_ios | [setLogLevel:](/docs/pebblekit-ios/Classes/PBPebbleCentral.md#//api/name/setLogLevel:) |
| Configures which events should be logged. (Deprecated: Use +[PBPebbleKitLogging setLogLevel:] instead.) + (void)setLogLevel:(PBPebbleKitLogLevel)logLevel Parameters logLevel One of the values in PBPebbleKitLogLevel, which will be the maximum level that will be logged. You can use PBPebbleKitLogLevelOff to disable all logging. Declared In PBPebbleCentral+Legacy.h |
| pebblekit\_ios | [dataLoggingService](/docs/pebblekit-ios/Classes/PBPebbleCentral.md#//api/name/dataLoggingService) |
| Use dataLoggingServiceForAppUUID: instead. (Deprecated: Use dataLoggingServiceForAppUUID: instead.) @property (nonatomic, readonly) PBDataLoggingService \*dataLoggingService Declared In PBPebbleCentral+Legacy.h |
| pebblekit\_ios | [SportsAppActivityState](/docs/pebblekit-ios/Constants/SportsAppActivityState.md) |
| |
| pebblekit\_ios | [GolfAppCommand](/docs/pebblekit-ios/Constants/GolfAppCommand.md) |
| |
| pebblekit\_ios | [FirmwareMetadataPlatform](/docs/pebblekit-ios/Constants/FirmwareMetadataPlatform.md) |
| |
| pebblekit\_ios | [PBUnitSystem](/docs/pebblekit-ios/Constants/PBUnitSystem.md) |
| |
| pebblekit\_ios | [PBPebbleKitLogFlag](/docs/pebblekit-ios/Constants/PBPebbleKitLogFlag.md) |
| |
| pebblekit\_ios | [PBRemoteProtocolCapabilitiesFlags](/docs/pebblekit-ios/Constants/PBRemoteProtocolCapabilitiesFlags.md) |
| |
| pebblekit\_ios | [PBDataLoggingType](/docs/pebblekit-ios/Constants/PBDataLoggingType.md) |
| |
| pebblekit\_ios | [PBPebbleKitLogLevel](/docs/pebblekit-ios/Constants/PBPebbleKitLogLevel.md) |
| |
| pebblekit\_ios | [PBErrorCode](/docs/pebblekit-ios/Constants/PBErrorCode.md) |
| |
| pebblekit\_ios | [PBPebbleCentralDelegate](/docs/pebblekit-ios/Protocols/PBPebbleCentralDelegate.md) |
| |
| pebblekit\_ios | [pebbleCentral:watchDidConnect:isNew:](/docs/pebblekit-ios/Protocols/PBPebbleCentralDelegate.md#//api/name/pebbleCentral:watchDidConnect:isNew:) |
| The Pebble Central responsible for calling the delegate method. - (void)pebbleCentral:(PBPebbleCentral \*)central watchDidConnect:(PBWatch \*)watch isNew:(BOOL)isNew Parameters central The Pebble Central responsible for calling the delegate method. watch The PBWatch object representing the watch that was connected. isNew YES if the watch has been connected for the first time since the app has been installed or NO if not. Declared In PBPebbleCentral.h |
| pebblekit\_ios | [pebbleCentral:watchDidDisconnect:](/docs/pebblekit-ios/Protocols/PBPebbleCentralDelegate.md#//api/name/pebbleCentral:watchDidDisconnect:) |
| The Pebble Central responsible for calling the delegate method. - (void)pebbleCentral:(PBPebbleCentral \*)central watchDidDisconnect:(PBWatch \*)watch Parameters central The Pebble Central responsible for calling the delegate method. watch The PBWatch object representing the watch that was disconnected. Declared In PBPebbleCentral.h |
| pebblekit\_ios | [PBDataLoggingServiceDelegate](/docs/pebblekit-ios/Protocols/PBDataLoggingServiceDelegate.md) |
| |
| pebblekit\_ios | [dataLoggingService:hasByteArrays:numberOfItems:forDataLoggingSession:](/docs/pebblekit-ios/Protocols/PBDataLoggingServiceDelegate.md#//api/name/dataLoggingService:hasByteArrays:numberOfItems:forDataLoggingSession:) |
| Called by the service every time there is data available that has not been consumed yet. - (BOOL)dataLoggingService:(PBDataLoggingService \*)service hasByteArrays:(const uint8\_t \*const)bytes numberOfItems:(uint16\_t)numberOfItems forDataLoggingSession:(PBDataLoggingSessionMetadata \*)session Parameters service The data logging service. bytes Pointer to the array of bytes. The array contains (numberOfItems \* session.itemSize) bytes. numberOfItems The number of items that the array contains. session The metadata of the session. Return Value YES if the data was consumed and the service can discard the data. Return NO if the data was not be consumed after the method returned. If NO is returned, the next time this callback is invoked for the session, the data argument will (also) contain the data of the items of the previous invocation of the callback. Declared In PBDataLoggingService.h |
| pebblekit\_ios | [dataLoggingService:hasUInt8s:numberOfItems:forDataLoggingSession:](/docs/pebblekit-ios/Protocols/PBDataLoggingServiceDelegate.md#//api/name/dataLoggingService:hasUInt8s:numberOfItems:forDataLoggingSession:) |
| Called by the service every time there is data available that has not been consumed yet. - (BOOL)dataLoggingService:(PBDataLoggingService \*)service hasUInt8s:(const uint8\_t [])data numberOfItems:(uint16\_t)numberOfItems forDataLoggingSession:(PBDataLoggingSessionMetadata \*)session Parameters service The data logging service. data Pointer to the array of UInt8`s. numberOfItems The number of items that the array contains. session The metadata of the session. Return Value YES if the data was consumed and the service can discard the data. Return NO if the data was not be consumed after the method returned. If NO is returned, the next time this callback is invoked for the session, the data argument will (also) contain the data of the items of the previous invocation of the callback. Declared In PBDataLoggingService.h |
| pebblekit\_ios | [dataLoggingService:hasUInt16s:numberOfItems:forDataLoggingSession:](/docs/pebblekit-ios/Protocols/PBDataLoggingServiceDelegate.md#//api/name/dataLoggingService:hasUInt16s:numberOfItems:forDataLoggingSession:) |
| Called by the service every time there is data available that has not been consumed yet. - (BOOL)dataLoggingService:(PBDataLoggingService \*)service hasUInt16s:(const uint16\_t [])data numberOfItems:(uint16\_t)numberOfItems forDataLoggingSession:(PBDataLoggingSessionMetadata \*)session Parameters service The data logging service. data Pointer to the array of UInt16`s. numberOfItems The number of items that the array contains. session The metadata of the session. Return Value YES if the data was consumed and the service can discard the data. Return NO if the data was not be consumed after the method returned. If NO is returned, the next time this callback is invoked for the session, the data argument will (also) contain the data of the items of the previous invocation of the callback. Declared In PBDataLoggingService.h |
| pebblekit\_ios | [dataLoggingService:hasUInt32s:numberOfItems:forDataLoggingSession:](/docs/pebblekit-ios/Protocols/PBDataLoggingServiceDelegate.md#//api/name/dataLoggingService:hasUInt32s:numberOfItems:forDataLoggingSession:) |
| Called by the service every time there is data available that has not been consumed yet. - (BOOL)dataLoggingService:(PBDataLoggingService \*)service hasUInt32s:(const uint32\_t [])data numberOfItems:(uint16\_t)numberOfItems forDataLoggingSession:(PBDataLoggingSessionMetadata \*)session Parameters service The data logging service. data Pointer to the array of UInt32`s. numberOfItems The number of items that the array contains. session The metadata of the session. Return Value YES if the data was consumed and the service can discard the data. Return NO if the data was not be consumed after the method returned. If NO is returned, the next time this callback is invoked for the session, the data argument will (also) contain the data of the items of the previous invocation of the callback. Declared In PBDataLoggingService.h |
| pebblekit\_ios | [dataLoggingService:hasSInt8s:numberOfItems:forDataLoggingSession:](/docs/pebblekit-ios/Protocols/PBDataLoggingServiceDelegate.md#//api/name/dataLoggingService:hasSInt8s:numberOfItems:forDataLoggingSession:) |
| Called by the service every time there is data available that has not been consumed yet. - (BOOL)dataLoggingService:(PBDataLoggingService \*)service hasSInt8s:(const int8\_t [])data numberOfItems:(uint16\_t)numberOfItems forDataLoggingSession:(PBDataLoggingSessionMetadata \*)session Parameters service The data logging service. data Pointer to the array of SInt8`s. numberOfItems The number of items that the array contains. session The metadata of the session. Return Value YES if the data was consumed and the service can discard the data. Return NO if the data was not be consumed after the method returned. If NO is returned, the next time this callback is invoked for the session, the data argument will (also) contain the data of the items of the previous invocation of the callback. Declared In PBDataLoggingService.h |
| pebblekit\_ios | [dataLoggingService:hasSInt16s:numberOfItems:forDataLoggingSession:](/docs/pebblekit-ios/Protocols/PBDataLoggingServiceDelegate.md#//api/name/dataLoggingService:hasSInt16s:numberOfItems:forDataLoggingSession:) |
| Called by the service every time there is data available that has not been consumed yet. - (BOOL)dataLoggingService:(PBDataLoggingService \*)service hasSInt16s:(const int16\_t [])data numberOfItems:(uint16\_t)numberOfItems forDataLoggingSession:(PBDataLoggingSessionMetadata \*)session Parameters service The data logging service. data Pointer to the array of SInt16`s. numberOfItems The number of items that the array contains. session The metadata of the session. Return Value YES if the data was consumed and the service can discard the data. Return NO if the data was not be consumed after the method returned. If NO is returned, the next time this callback is invoked for the session, the data argument will (also) contain the data of the items of the previous invocation of the callback. Declared In PBDataLoggingService.h |
| pebblekit\_ios | [dataLoggingService:hasSInt32s:numberOfItems:forDataLoggingSession:](/docs/pebblekit-ios/Protocols/PBDataLoggingServiceDelegate.md#//api/name/dataLoggingService:hasSInt32s:numberOfItems:forDataLoggingSession:) |
| Called by the service every time there is data available that has not been consumed yet. - (BOOL)dataLoggingService:(PBDataLoggingService \*)service hasSInt32s:(const int32\_t [])data numberOfItems:(uint16\_t)numberOfItems forDataLoggingSession:(PBDataLoggingSessionMetadata \*)session Parameters service The data logging service. data Pointer to the array of SInt32`s. numberOfItems The number of items that the array contains. session The metadata of the session. Return Value YES if the data was consumed and the service can discard the data. Return NO if the data was not be consumed after the method returned. If NO is returned, the next time this callback is invoked for the session, the data argument will (also) contain the data of the items of the previous invocation of the callback. Declared In PBDataLoggingService.h |
| pebblekit\_ios | [dataLoggingService:sessionDidFinish:](/docs/pebblekit-ios/Protocols/PBDataLoggingServiceDelegate.md#//api/name/dataLoggingService:sessionDidFinish:) |
| Called by the service every time a session is finished. This is guaranteed to be called only after all data has been received and consumed by the application. - (void)dataLoggingService:(PBDataLoggingService \*)service sessionDidFinish:(PBDataLoggingSessionMetadata \*)session Parameters service The data logging service. session The metadata of the session. Declared In PBDataLoggingService.h |
| pebblekit\_ios | [PBWatchDelegate](/docs/pebblekit-ios/Protocols/PBWatchDelegate.md) |
| |
| pebblekit\_ios | [watchDidDisconnect:](/docs/pebblekit-ios/Protocols/PBWatchDelegate.md#//api/name/watchDidDisconnect:) |
| Called when the watch got disconnected. - (void)watchDidDisconnect:(PBWatch \*)watch Parameters watch The watch that was disconnected. Declared In PBWatch.h |
| pebblekit\_ios | [watch:handleError:](/docs/pebblekit-ios/Protocols/PBWatchDelegate.md#//api/name/watch:handleError:) |
| Called when the watch caught an error. - (void)watch:(PBWatch \*)watch handleError:(NSError \*)error Parameters watch The watch that caught the error. error The error catch by the watch. Declared In PBWatch.h |
| pebblekit\_ios | [watchWillResetSession:](/docs/pebblekit-ios/Protocols/PBWatchDelegate.md#//api/name/watchWillResetSession:) |
| Called when an internal session is about to be reset. - (void)watchWillResetSession:(PBWatch \*)watch Parameters watch The watch that will reset its session. Declared In PBWatch.h |
| pebblekit\_ios | [watchDidOpenSession:](/docs/pebblekit-ios/Protocols/PBWatchDelegate.md#//api/name/watchDidOpenSession:) |
| Called when an internal session is opened - (void)watchDidOpenSession:(PBWatch \*)watch Parameters watch The watch that opened a session. Declared In PBWatch.h |
| pebblekit\_ios | [watchDidCloseSession:](/docs/pebblekit-ios/Protocols/PBWatchDelegate.md#//api/name/watchDidCloseSession:) |
| Called when an internal EASession is closed - (void)watchDidCloseSession:(PBWatch \*)watch Parameters watch The watch that closed its session. Declared In PBWatch.h |
| pebblekit\_ios | [hierarchy](/docs/pebblekit-ios/hierarchy.md) |
| |
| pebblekit\_ios | [index](/docs/pebblekit-ios/index.md) |
| |
