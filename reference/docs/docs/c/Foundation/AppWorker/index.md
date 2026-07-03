# AppWorker

Source: https://developer.repebble.com/docs/c/Foundation/AppWorker/index.html

Runs in the background, and can communicate with the foreground app.

## Function Documentation

bool app\_worker\_is\_running(void)

Determine if the worker for the current app is running.

#### Returns

true if running

[AppWorkerResult](/docs/c/Foundation/AppWorker/#AppWorkerResult) app\_worker\_launch(void)

Launch the worker for the current app. Note that this is an asynchronous operation, a result code of APP\_WORKER\_RESULT\_SUCCESS merely means that the request was successfully queued up.

#### Returns

result code

[AppWorkerResult](/docs/c/Foundation/AppWorker/#AppWorkerResult) app\_worker\_kill(void)

Kill the worker for the current app. Note that this is an asynchronous operation, a result code of APP\_WORKER\_RESULT\_SUCCESS merely means that the request was successfully queued up.

#### Returns

result code

bool app\_worker\_message\_subscribe([AppWorkerMessageHandler](/docs/c/Foundation/AppWorker/#AppWorkerMessageHandler) handler)

Subscribe to worker messages. Once subscribed, the handler gets called on every message emitted by the other task (either worker or app).

#### Parameters
 handler

A callback to be executed when the event is received

#### Returns

true on success

bool app\_worker\_message\_unsubscribe(void)

Unsubscribe from worker messages. Once unsubscribed, the previously registered handler will no longer be called.

#### Returns

true on success

void app\_worker\_send\_message(uint8\_t type, [AppWorkerMessage](/docs/c/Foundation/AppWorker/#AppWorkerMessage) \* data)

Send a message to the other task (either worker or app).

#### Parameters
 type

An application defined message type

 data

the message data structure

## Data Structure Documentation

struct AppWorkerMessage

Generic structure of a worker message that can be sent between an app and its worker.

#### Data Fields
[uint16\_t](/docs/c/Standard_C/#uint16_t) data0[uint16\_t](/docs/c/Standard_C/#uint16_t) data1[uint16\_t](/docs/c/Standard_C/#uint16_t) data2

## Enum Documentation

enum AppWorkerResult

Possible error codes from app\_worker\_launch, app\_worker\_kill.

#### Enumerators
APP\_WORKER\_RESULT\_SUCCESS

Success.

APP\_WORKER\_RESULT\_NO\_WORKER

No worker found for the current app.

APP\_WORKER\_RESULT\_DIFFERENT\_APP

A worker for a different app is already running.

APP\_WORKER\_RESULT\_NOT\_RUNNING

The worker is not running.

APP\_WORKER\_RESULT\_ALREADY\_RUNNING

The worker is already running.

APP\_WORKER\_RESULT\_ASKING\_CONFIRMATION

The user will be asked for confirmation.

## Typedef Documentation

 typedef void(\* AppWorkerMessageHandler)(uint16\_t type, AppWorkerMessage \*data) 

Callback type for worker messages. Messages can be sent from worker to app or vice versa.

#### Parameters
 type

An application defined message type

 data

pointer to message data. The receiver must know the structure of the data provided by the sender.
