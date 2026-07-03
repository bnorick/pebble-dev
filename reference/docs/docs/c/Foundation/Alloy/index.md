# Alloy

Source: https://developer.repebble.com/docs/c/Foundation/Alloy/index.html

The APIs on this page will only work with SDK 4.9+.

## Function Documentation

void moddable\_createMachine([ModdableCreationRecord](/docs/c/Foundation/Alloy/#ModdableCreationRecord) \* creation)

Create and start a Moddable XS virtual machine for an Alloy app.

#### Parameters
 creation

Configuration record, or NULL for default settings.

#### See Also
[ModdableCreationRecord](/docs/c/Foundation/Alloy/#ModdableCreationRecord)

## Data Structure Documentation

struct ModdableCreationRecord

Configuration record for creating a Moddable XS virtual machine. Used with [moddable\_createMachine()](/docs/c/Foundation/Alloy/#moddable_createMachine) to customize the JS runtime. Set recordSize to sizeof(ModdableCreationRecord) for version compatibility.

#### Data Fields
[uint32\_t](/docs/c/Standard_C/#uint32_t) recordSize

Size of this struct in bytes (for versioning)

[uint32\_t](/docs/c/Standard_C/#uint32_t) stack

Stack size in bytes (0 for default)

[uint32\_t](/docs/c/Standard_C/#uint32_t) slot

Slot heap size in bytes (0 for default)

[uint32\_t](/docs/c/Standard_C/#uint32_t) chunk

Chunk heap size in bytes (0 for default)

[uint32\_t](/docs/c/Standard_C/#uint32_t) flags

Combination of kModdableCreationFlag\* values.

## Macro Definition Documentation

#define kModdableCreationFlagLogInstrumentation (1 \<\< 0)

Flag to enable XS instrumentation logging over Bluetooth. When set, the Moddable XS engine will log instrumentation data (e.g. memory usage, slot/chunk/stack statistics) via app\_log. Logging is only active when a Bluetooth log listener is connected; otherwise this flag has no effect.

#### See Also
[ModdableCreationRecord](/docs/c/Foundation/Alloy/#ModdableCreationRecord)
