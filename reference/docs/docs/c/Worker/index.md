# Worker

Source: https://developer.repebble.com/docs/c/Worker/index.html

## Function Documentation

void worker\_event\_loop(void)

The event loop for workers, to be used in worker's main(). Will block until the worker is ready to exit.

#### See Also
[App](/docs/c/Foundation/App/)

void worker\_launch\_app(void)

Launch the foreground app for this worker.
