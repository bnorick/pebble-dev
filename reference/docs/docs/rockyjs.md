# Rocky.js API Documentation

Source: https://developer.repebble.com/docs/rockyjs/

The RockyJS API allows developers to write watchfaces in JavaScript, that are executed via the firmware's [JerryScript](//github.com/pebble/jerryscript) engine. For instructions on getting started with the RockyJS API, see the [JS Watchface Tutorial](/tutorials/js-watchface-tutorial).   
Note that RockyJS is deprecated and is not recommended for new development. For new development we recommend [Alloy](/tutorials/alloy-watchface-tutorial).

The JavaScript API is broken down into the following modules:

* * *

#### [CanvasRenderingContext2D](/docs/rockyjs/CanvasRenderingContext2D.md)

#### [console](/docs/rockyjs/console.md)

#### [Date](/docs/rockyjs/Date.md)

#### [rocky](/docs/rockyjs/rocky.md)

* * *

The JavaScript API also includes the following global functions:

setTimeout(fct, delay) 

Calls a function after a specified delay.

`var timeoutId = setTimeout(function(...){}, 10000);`

#### Parameters
Function fct

The function to execute

Number delay

The delay (in ms)

#### Returns

timeoutId - The ID of the timeout

clearTimeout(timeoutId) 

Clears the delay set by `setTimeout`.

`clearTimeout(timeoutId);`

#### Parameters
Number timeoutId

The ID of the timeout you wish to clear.

setInterval(fct, delay) 

Repeatedly calls a function, with a fixed time delay between each call.

`var intervalId = setInterval(function(...){}, 10000);`

#### Parameters
Function fct

The function to execute

Number delay

The delay (in ms)

#### Returns

intervalId - The ID of the interval

clearInterval(intervalId) 

Clears the interval set by `setInterval`.

`clearInterval(intervalId);`

#### Parameters
Number intervalId

The ID of the interval you wish to clear

* * *
