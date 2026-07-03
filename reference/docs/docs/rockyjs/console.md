# console

Source: https://developer.repebble.com/docs/rockyjs/console/

This provides an interface to the app's debugging console.

If you're using [CloudPebble](https://cloudpebble.net), these logs will appear when you press 'View Logs' after launching your application.

If you're using the local SDK, you can use the `$ pebble logs` command or:

`$ pebble install --emulator basalt --logs`

You can find out more about logging in our [Debugging with App Logs](/guides/debugging/debugging-with-app-logs.md) guide.

### Methods

 console.log(obj) 

Outputs a message to the app's debugging console.

`console.log(rocky.watchInfo.platform);`

#### Parameters
 obj

One or more JavaScript objects to output. The string representations of each of these objects are appended together in the order listed and output.

 console.warn(obj) 

Outputs a warning message to the app's debugging console.

`console.warn('Something seems wrong');`

#### Parameters
 obj

One or more JavaScript objects to output. The string representations of each of these objects are appended together in the order listed and output.

 console.error(obj) 

Outputs an error message to the app's debugging console.

`console.error(JSON.stringify(obj));`

#### Parameters
 obj

One or more JavaScript objects to output. The string representations of each of these objects are appended together in the order listed and output.
