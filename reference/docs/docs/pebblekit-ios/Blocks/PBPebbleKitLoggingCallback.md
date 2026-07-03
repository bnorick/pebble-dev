# PBPebbleKitLoggingCallback Block Reference

Source: https://developer.repebble.com/docs/pebblekit-ios/Blocks/PBPebbleKitLoggingCallback/

| Declared in | PBLog+Public.h |

#### Block Definition

### PBPebbleKitLoggingCallback

A logging callback invoked whenever PebbleKit wants to add some message to the log.

`typedef void (^PBPebbleKitLoggingCallback) (BOOL asynchronous, PBPebbleKitLogLevel level, PBPebbleKitLogFlag flag, NSInteger context, const char, * file, const char, * function, NSUInteger line, id __nullable, tag ,, NSString *format, va_list args)`

#### Discussion

It’s important to notice that your logging callback should not block if possible, unless the asynchronous flag is NO, in which case blocking is allowed.

**Note:** See CocoaLumberjack documentation for more information about the usage of the paramaters and what they exactly mean:[https://github.com/CocoaLumberjack/CocoaLumberjack/tree/master/Documentation](https://github.com/CocoaLumberjack/CocoaLumberjack/tree/master/Documentation)

#### Declared In
`PBLog+Public.h`
