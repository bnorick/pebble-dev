# Debugging

Source: https://developer.repebble.com/guides/debugging/

When writing apps, everyone makes mistakes. Sometimes a simple typo or omission can lead to all kinds of mysterious behavior or crashes. The guides in this section are aimed at trying to help developers identify and fix a variety of issues that can arise when writing C code (compile-time) or running the compiled app on Pebble (runtime).

There are also a few strategies outlined here, such as app logging and other features of the `pebble` [_Command Line Tool_](/guides/tools-and-resources/pebble-tool.md) that can indicate the source of a problem in the vast majority of cases.

## Contents

- [**Common Runtime Errors**](/guides/debugging/common-runtime-errors.md) - Examples of commonly encountered runtime problems that cannot be detected at compile time and can usually be fixed by logical thought and experimentation.

- [**Common Syntax Errors**](/guides/debugging/common-syntax-errors.md) - Details of common problems encountered when writing C apps for Pebble, and how to resolve them.

- [**Debugging with App Logs**](/guides/debugging/debugging-with-app-logs.md) - How to use the app logs to debug problems with an app, as well as tips on interpreting common run time errors.

- [**Debugging with GDB**](/guides/debugging/debugging-with-gdb.md) - How to use GDB to debug a Pebble app in the emulator.
