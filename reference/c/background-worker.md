# Background Worker // Pebble Developers
In addition to the main foreground task that every Pebble app implements, a second background worker task can also be created. This worker is capable of running even when the foreground task is closed, and is useful for tasks that must continue for long periods of time. For example, apps that log sensor data.

There are several important points to note about the capabilities of this worker when compared to those of the foreground task:

*   The worker is constrained to 10.5 kB of memory.
    
*   Some APIs are not available to the worker. See the [_Available APIs_](#available-apis) section below for more information.
    
*   There can only be one background worker active at a time. In the event that a second one attempts to launch from another watchapp, the user will be asked to choose whether the new worker can replace the existing one.
    
*   The user can determine which app's worker is running by checking the 'Background App' section of the Settings menu. Workers can also be launched from there.
    
*   The worker can launch the foreground app using [`worker_launch_app()`](about:/docs/c/Worker/#worker_launch_app "worker_launch_app"). This means that the foreground app should be prepared to be launched at any time that the worker is running.
    

> Note: This API should not be used to build background timers; use the [`Wakeup`](https://developer.repebble.com/docs/c/Foundation/Wakeup/ "Wakeup") API instead.

Adding a Worker
---------------

The background worker's behavior is determined by code written in a separate C file to the foreground app, created in the `/worker_src` project directory.

This project structure can also be generated using the [`pebble` tool](https://developer.repebble.com/guides/tools-and-resources/pebble-tool/) with the `--worker` flag as shown below:

```
$ pebble new-project --worker project_name

```


The worker C file itself has a basic structure similar to a regular Pebble app, but with a couple of minor changes, as shown below:

```
#include <pebble_worker.h>

static void prv_init() {
  // Initialize the worker here
}

static void prv_deinit() {
  // Deinitialize the worker here
}

int main(void) {
  prv_init();
  worker_event_loop();
  prv_deinit();
}

```


Launching the Worker
--------------------

To launch the worker from the foreground app, use [`app_worker_launch()`](about:/docs/c/Foundation/AppWorker/#app_worker_launch "app_worker_launch"):

```
// Launch the background worker
AppWorkerResult result = app_worker_launch();

```


The [`AppWorkerResult`](about:/docs/c/Foundation/AppWorker/#AppWorkerResult "AppWorkerResult") returned will indicate any errors encountered as a result of attempting to launch the worker. Possible result values include:



* Result: APP_WORKER_RESULT_SUCCESS
  * Value: 0
  * Description: The worker launch was successful, but may not start running immediately. Use app_worker_is_running() to determine when the worker has started running.
* Result: APP_WORKER_RESULT_NO_WORKER
  * Value: 1
  * Description: No worker found for the current app.
* Result: APP_WORKER_RESULT_ALREADY_RUNNING
  * Value: 4
  * Description: The worker is already running.
* Result: APP_WORKER_RESULT_ASKING_CONFIRMATION
  * Value: 5
  * Description: The user will be asked for confirmation. To determine whether the worker was given permission to launch, use app_worker_is_running() for a short period after receiving this result.


Communicating Between Tasks
---------------------------

There are three methods of passing data between the foreground and background worker tasks:

*   Save the data using the [`Storage`](https://developer.repebble.com/docs/c/Foundation/Storage/ "Storage") API, then read it in the other task.
    
*   Send the data to a companion phone app using the [`DataLogging`](https://developer.repebble.com/docs/c/Foundation/DataLogging/ "DataLogging") API. Details on how to do this are available in [_Datalogging_](https://developer.repebble.com/guides/communication/datalogging/).
    
*   Pass the data directly while the other task is running, using an [`AppWorkerMessage`](about:/docs/c/Foundation/AppWorker/#AppWorkerMessage "AppWorkerMessage"). These messages can be sent bi-directionally by creating an `AppWorkerMessageHandler` in each task. The handler will fire in both the foreground and the background tasks, so you must identify the source of the message using the `type` parameter.
    
    ```
// Used to identify the source of a message
#define SOURCE_FOREGROUND 0
#define SOURCE_BACKGROUND 1

```

    
    **Foreground App**
    
    ```
static int s_some_value = 1;
static int s_another_value = 2;

static void worker_message_handler(uint16_t type, 
                                    AppWorkerMessage *message) {
  if(type == SOURCE_BACKGROUND) {
    // Get the data, only if it was sent from the background
    s_some_value = message->data0;
    s_another_value = message->data1;
  }
}

// Subscribe to get AppWorkerMessages
app_worker_message_subscribe(worker_message_handler);

// Construct a message to send
AppWorkerMessage message = {
  .data0 = s_some_value,
  .data1 = s_another_value
};

// Send the data to the background app
app_worker_send_message(SOURCE_FOREGROUND, &message);

```

    
    **Worker**
    
    ```
static int s_some_value = 3;
static int s_another_value = 4;

// Construct a message to send
AppWorkerMessage message = {
  .data0 = s_some_value,
  .data1 = s_another_value
};

static void worker_message_handler(uint16_t type, 
                                    AppWorkerMessage *message) {
  if(type == SOURCE_FOREGROUND) {
    // Get the data, if it was sent from the foreground
    s_some_value = message->data0;
    s_another_value = message->data1;
  }
}

// Subscribe to get AppWorkerMessages
app_worker_message_subscribe(worker_message_handler);

// Send the data to the foreground app
app_worker_send_message(SOURCE_BACKGROUND, &message);

```

    

Managing the Worker
-------------------

The current running state of the background worker can be determined using the [`app_worker_is_running()`](about:/docs/c/Foundation/AppWorker/#app_worker_is_running "app_worker_is_running") function:

```
// Check to see if the worker is currently active
bool running = app_worker_is_running();

```


The user can tell whether the worker is running by checking the system 'Background App' settings. Any installed workers with be listed there.

The worker can be stopped using [`app_worker_kill()`](about:/docs/c/Foundation/AppWorker/#app_worker_kill "app_worker_kill"):

```
// Stop the background worker
AppWorkerResult result = app_worker_kill();

```


Possible `result` values when attempting to kill the worker are as follows:



* Result: APP_WORKER_RESULT_SUCCESS
  * Value: 0
  * Description: The worker launch was killed successfully.
* Result: APP_WORKER_RESULT_DIFFERENT_APP
  * Value: 2
  * Description: A worker from a different app is running, and cannot be killed by this app.
* Result: APP_WORKER_RESULT_NOT_RUNNING
  * Value: 3
  * Description: The worker is not currently running.


Available APIs
--------------

Background workers do not have access to the UI APIs. They also cannot use the [`AppMessage`](https://developer.repebble.com/docs/c/Foundation/AppMessage/ "AppMessage") API or load resources. Most other APIs are available including (but not limited to) [`AccelerometerService`](https://developer.repebble.com/docs/c/Foundation/Event_Service/AccelerometerService/ "AccelerometerService"), [`CompassService`](https://developer.repebble.com/docs/c/Foundation/Event_Service/CompassService/ "CompassService"), [`DataLogging`](https://developer.repebble.com/docs/c/Foundation/DataLogging/ "DataLogging"), [`HealthService`](https://developer.repebble.com/docs/c/Foundation/Event_Service/HealthService/ "HealthService"), [`ConnectionService`](https://developer.repebble.com/docs/c/Foundation/Event_Service/ConnectionService/ "ConnectionService"), [`BatteryStateService`](https://developer.repebble.com/docs/c/Foundation/Event_Service/BatteryStateService/ "BatteryStateService"), [`TickTimerService`](https://developer.repebble.com/docs/c/Foundation/Event_Service/TickTimerService/ "TickTimerService") and [`Storage`](https://developer.repebble.com/docs/c/Foundation/Storage/ "Storage").

The compiler will throw an error if the developer attempts to use an API unsupported by the worker. For a definitive list of available APIs, check `pebble_worker.h` in the SDK bundle for the presence of the desired API.