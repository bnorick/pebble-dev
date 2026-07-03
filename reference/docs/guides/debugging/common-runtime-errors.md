# Common Runtime Errors

Source: https://developer.repebble.com/guides/debugging/common-runtime-errors/

Whether just beginning to create apps for the Pebble platform or are creating a more complex app, the output from app logs can be very useful in tracking down problems with an app's code. Some examples of common problems are explored here, including some examples to help gain familiarity with compiler output.

In contrast with syntactical errors in written code (See [_Common Syntax Errors_](/guides/debugging/common-syntax-errors.md)), there can also be problems that only occur when the app is actually run on a Pebble. The reason for this is that perfectly valid C code can sometimes cause improper behavior that is incompatible with the hardware.

These problems can manifest themselves as an app crashing and very little other information available as to what the cause was, which means that they can take an abnormally long time to diagnose and fix.

One option to help track down the offending lines is to begin at the start of app initialization and use a call to [`APP_LOG()`](/docs/c/Foundation/Logging/#app_log "app\_log") to establish where execution stops. If the message in the log call appears, then execution has at least reached that point. Move the call further through logical execution until it ceases to appear, as it will then be after the point where the app crashes.

## Null Pointers

The Pebble SDK uses a dynamic memory allocation model, meaning that all the SDK objects and structures available for use by developers are allocated as and when needed. This model has the advantage that only the immediately needed data and objects can be kept in memory and unloaded when they are not needed, increasing the scale and capability of apps that can be created.

In this paradigm a structure is first declared as a pointer (which may be given an initial value of `NULL`) before being fully allocated a structure later in the app's initialization. Therefore one of the most common problems that can arise is that of the developer attempting to use an unallocated structure or data item.

For example, the following code segment will cause a crash:

```
Window \*main\_window;static void init() {// Attempting to push an uninitialized Window!window\_stack\_push(main\_window, true);}
```

The compiler will not report this, but when run the app will crash before the[`Window`](/docs/c/User_Interface/Window/ "Window") can be displayed, with an error message sent to the console output along the following lines:

```
[INFO] E ault_handling.c:77 App fault! {f23aecb8-bdb5-4d6b-b270-602a1940575e} PC: 0x8016716 LR: 0x8016713
[WARNING] Program Counter (PC): 0x8016716 ???
[WARNING] Link Register (LR): 0x8016713 ???
```

When possible, the pebble tool will tell the developer the PC (Program Counter, or which statement is currently being executed) and LR (Link Register, address to return to when the current function scope ends) addresses and line numbers at the time of the crash, which may help indicate the source of the problem.

This problem can be fixed by ensuring that any data structures declared as pointers are properly allocated using the appropriate `_create()` SDK functions before they are used as arguments:

```
Window \*main\_window;static void init(void) {main\_window = window\_create();window\_stack\_push(main\_window, true);}
```

In situations where available heap space is limited, `_create()` functions may return `NULL`, and the object will not be allocated. Apps can detect this situation as follows:

```
Window \*main\_window;static void init(void) {main\_window = window\_create();if(main\_window != NULL) {// Allocation was successful!window\_stack\_push(main\_window, true);} else {// The Window could not be allocated! // Tell the user that the operation could not be completedtext\_layer\_set\_text(s\_output\_layer, "Unable to use this feature at the moment.");}}
```

This `NULL` pointer error can also occur to any dynamically allocated structure or variable of the developer's own creation outside the SDK. For example, a typical dynamically allocated array will cause a crash if it is used before it is allocated:

```
char \*array;// Array is still NULL!array[0] = 'a';
```

This problem can be fixed in a similar manner as before by making sure the array is properly allocated before it is used:

```
char \*array = (char\*)malloc(8 \* sizeof(char));array[0] = 'a';
```

As mentioned above for [`window_create()`](/docs/c/User_Interface/Window/#window_create "window\_create"), be sure also check the [return value](http://pubs.opengroup.org/onlinepubs/009695399/functions/malloc.html) of `malloc()` to determine whether the memory allocation requested was completed successfully:

```
array = (char\*)malloc(8 \* sizeof(char));// Check the malloc() was successfulif(array != NULL) {array[0] = 'a';} else {// Gracefully handle the failed situation}
```

## Outside Array Bounds

Another problem that can look OK to the compiler, but cause an error at runtime is improper use of arrays, such as attempting to access an array index outside the array's bounds. This can occur when a loop is set up to iterate through an array, but the size of the array is reduced or the loop conditions change.

For example, the array iteration below will not cause a crash, but includes the use of 'magic numbers' that can make a program brittle and prone to errors when these numbers change:

```
int \*array;static void init(void) {array = (int\*)malloc(8 \* sizeof(int));for(int i = 0; i \< 8; i++) {array[i] = i \* i;}}
```

If the size of the allocated array is reduced, the app will crash when the iterative loop goes outside the array bounds:

```
int \*array;static void init(void) {array = (int\*)malloc(4 \* sizeof(int));for(int i = 0; i \< 8; i++) {array[i] = i \* i;// Crash when i == 4!}}
```

Since the number of loop iterations is linked to the size of the array, this problem can be avoided by defining the size of the array in advance in one place, and then using that value everywhere the size of the array is needed:

```
#define ARRAY\_SIZE 4int \*array;static void init(void) {array = (int\*)malloc(ARRAY\_SIZE \* sizeof(int));for(int i = 0; i \< ARRAY\_SIZE; i++) {array[i] = i \* i;}}
```

An alternative solution to the above is to use either the `ARRAY_LENGTH()` macro or the `sizeof()` function to programmatically determine the size of the array to be looped over.
