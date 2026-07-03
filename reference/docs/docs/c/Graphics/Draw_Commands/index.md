# Draw Commands

Source: https://developer.repebble.com/docs/c/Graphics/Draw_Commands/index.html

Pebble Draw Commands are a way to encode arbitrary path draw and fill calls in binary format, so that vector-like graphics can be represented on the watch.

These draw commands can be loaded from resources, manipulated in place and drawn to the current graphics context. Each [GDrawCommand](/docs/c/Graphics/Draw_Commands/#GDrawCommand) can be an arbitrary path or a circle with optional fill or stroke. The stroke width and color of the stroke and fill are also encoded within the [GDrawCommand](/docs/c/Graphics/Draw_Commands/#GDrawCommand). Paths can can be drawn open or closed.

All aspects of a draw command can be modified, except for the number of points in a path (a circle only has one point, the center).

Draw commands are grouped into a [GDrawCommandList](/docs/c/Graphics/Draw_Commands/#GDrawCommandList), which can be drawn all at once. Each individual [GDrawCommand](/docs/c/Graphics/Draw_Commands/#GDrawCommand) can be accessed from a [GDrawCommandList](/docs/c/Graphics/Draw_Commands/#GDrawCommandList) for modification.

A [GDrawCommandList](/docs/c/Graphics/Draw_Commands/#GDrawCommandList) forms the basis for [GDrawCommandImage](/docs/c/Graphics/Draw_Commands/#GDrawCommandImage) and [GDrawCommandFrame](/docs/c/Graphics/Draw_Commands/#GDrawCommandFrame) objects. A [GDrawCommandImage](/docs/c/Graphics/Draw_Commands/#GDrawCommandImage) represents a static image and can be represented by the PDC file format and can be loaded as a resource.

Once you have a [GDrawCommandImage](/docs/c/Graphics/Draw_Commands/#GDrawCommandImage) loaded in memory you can draw it on the screen in a [LayerUpdateProc](/docs/c/User_Interface/Layers/#LayerUpdateProc) with the [gdraw\_command\_image\_draw()](/docs/c/Graphics/Draw_Commands/#gdraw_command_image_draw).

A [GDrawCommandFrame](/docs/c/Graphics/Draw_Commands/#GDrawCommandFrame) represents a single frame of an animated sequence, with multiple frames making up a single [GDrawCommandSequence](/docs/c/Graphics/Draw_Commands/#GDrawCommandSequence), which can also be stored as a PDC and loaded as a resource.

To draw a [GDrawCommandSequence](/docs/c/Graphics/Draw_Commands/#GDrawCommandSequence), use the [gdraw\_command\_sequence\_get\_frame\_by\_elapsed()](/docs/c/Graphics/Draw_Commands/#gdraw_command_sequence_get_frame_by_elapsed) to obtain the current [GDrawCommandFrame](/docs/c/Graphics/Draw_Commands/#GDrawCommandFrame) and [gdraw\_command\_frame\_draw()](/docs/c/Graphics/Draw_Commands/#gdraw_command_frame_draw) to draw it.

Draw commands also allow access to drawing with sub-pixel precision. The points are treated as Fixed point types in the format 13.3, so that 1/8th of a pixel precision is possible. Only the points in draw commands of the type GDrawCommandTypePrecisePath will be treated as higher precision.

## Function Documentation

void gdraw\_command\_draw(GContext \* ctx, [GDrawCommand](/docs/c/Graphics/Draw_Commands/#GDrawCommand) \* command)

Draw a command.

#### Parameters
 ctx

The destination graphics context in which to draw

 command

[GDrawCommand](/docs/c/Graphics/Draw_Commands/#GDrawCommand) to draw

[GDrawCommandType](/docs/c/Graphics/Draw_Commands/#GDrawCommandType) gdraw\_command\_get\_type([GDrawCommand](/docs/c/Graphics/Draw_Commands/#GDrawCommand) \* command)

Get the command type.

#### Parameters
 command

[GDrawCommand](/docs/c/Graphics/Draw_Commands/#GDrawCommand) from which to get the type

#### Returns

The type of the given [GDrawCommand](/docs/c/Graphics/Draw_Commands/#GDrawCommand)

void gdraw\_command\_set\_fill\_color([GDrawCommand](/docs/c/Graphics/Draw_Commands/#GDrawCommand) \* command, GColor fill\_color)

Set the fill color of a command.

#### Parameters
 command

ref DrawCommand for which to set the fill color

 fill\_color

GColor to set for the fill

GColor gdraw\_command\_get\_fill\_color([GDrawCommand](/docs/c/Graphics/Draw_Commands/#GDrawCommand) \* command)

Get the fill color of a command.

#### Parameters
 command

[GDrawCommand](/docs/c/Graphics/Draw_Commands/#GDrawCommand) from which to get the fill color

#### Returns

fill color of the given [GDrawCommand](/docs/c/Graphics/Draw_Commands/#GDrawCommand)

void gdraw\_command\_set\_stroke\_color([GDrawCommand](/docs/c/Graphics/Draw_Commands/#GDrawCommand) \* command, GColor stroke\_color)

Set the stroke color of a command.

#### Parameters
 command

[GDrawCommand](/docs/c/Graphics/Draw_Commands/#GDrawCommand) for which to set the stroke color

 stroke\_color

GColor to set for the stroke

GColor gdraw\_command\_get\_stroke\_color([GDrawCommand](/docs/c/Graphics/Draw_Commands/#GDrawCommand) \* command)

Get the stroke color of a command.

#### Parameters
 command

[GDrawCommand](/docs/c/Graphics/Draw_Commands/#GDrawCommand) from which to get the stroke color

#### Returns

The stroke color of the given [GDrawCommand](/docs/c/Graphics/Draw_Commands/#GDrawCommand)

void gdraw\_command\_set\_stroke\_width([GDrawCommand](/docs/c/Graphics/Draw_Commands/#GDrawCommand) \* command, uint8\_t stroke\_width)

Set the stroke width of a command.

#### Parameters
 command

[GDrawCommand](/docs/c/Graphics/Draw_Commands/#GDrawCommand) for which to set the stroke width

 stroke\_width

stroke width to set for the command

uint8\_t gdraw\_command\_get\_stroke\_width([GDrawCommand](/docs/c/Graphics/Draw_Commands/#GDrawCommand) \* command)

Get the stroke width of a command.

#### Parameters
 command

[GDrawCommand](/docs/c/Graphics/Draw_Commands/#GDrawCommand) from which to get the stroke width

#### Returns

The stroke width of the given [GDrawCommand](/docs/c/Graphics/Draw_Commands/#GDrawCommand)

[uint16\_t](/docs/c/Standard_C/#uint16_t) gdraw\_command\_get\_num\_points([GDrawCommand](/docs/c/Graphics/Draw_Commands/#GDrawCommand) \* command)

Get the number of points in a command.

void gdraw\_command\_set\_point([GDrawCommand](/docs/c/Graphics/Draw_Commands/#GDrawCommand) \* command, [uint16\_t](/docs/c/Standard_C/#uint16_t) point\_idx, [GPoint](/docs/c/Graphics/Graphics_Types/#GPoint) point)

Set the value of the point in a command at the specified index.

#### Parameters
 command

[GDrawCommand](/docs/c/Graphics/Draw_Commands/#GDrawCommand) for which to set the value of a point

 point\_idx

Index of the point to set the value for

 point

new point value to set

[GPoint](/docs/c/Graphics/Graphics_Types/#GPoint) gdraw\_command\_get\_point([GDrawCommand](/docs/c/Graphics/Draw_Commands/#GDrawCommand) \* command, [uint16\_t](/docs/c/Standard_C/#uint16_t) point\_idx)

Get the value of a point in a command from the specified index.

##### Note

The index **must** be less than the number of points

#### Parameters
 command

[GDrawCommand](/docs/c/Graphics/Draw_Commands/#GDrawCommand) from which to get a point

 point\_idx

The index to get the point for

#### Returns

The point in the [GDrawCommand](/docs/c/Graphics/Draw_Commands/#GDrawCommand) specified by point\_idx

void gdraw\_command\_set\_radius([GDrawCommand](/docs/c/Graphics/Draw_Commands/#GDrawCommand) \* command, [uint16\_t](/docs/c/Standard_C/#uint16_t) radius)

Set the radius of a circle command.

##### Note

This only works for commands of type GDrawCommandCircle

#### Parameters
 command

[GDrawCommand](/docs/c/Graphics/Draw_Commands/#GDrawCommand) from which to set the circle radius

 radius

The radius to set for the circle.

[uint16\_t](/docs/c/Standard_C/#uint16_t) gdraw\_command\_get\_radius([GDrawCommand](/docs/c/Graphics/Draw_Commands/#GDrawCommand) \* command)

Get the radius of a circle command.

##### Note

this only works for commands of typeGDrawCommandCircle.

#### Parameters
 command

[GDrawCommand](/docs/c/Graphics/Draw_Commands/#GDrawCommand) from which to get the circle radius

#### Returns

The radius in pixels if command is of type GDrawCommandCircle

void gdraw\_command\_set\_path\_open([GDrawCommand](/docs/c/Graphics/Draw_Commands/#GDrawCommand) \* command, bool path\_open)

Set the path of a stroke command to be open.

##### Note

This only works for commands of type GDrawCommandPath and GDrawCommandPrecisePath

#### Parameters
 command

[GDrawCommand](/docs/c/Graphics/Draw_Commands/#GDrawCommand) for which to set the path open status

 path\_open

true if path should be hidden

bool gdraw\_command\_get\_path\_open([GDrawCommand](/docs/c/Graphics/Draw_Commands/#GDrawCommand) \* command)

Return whether a stroke command path is open.

##### Note

This only works for commands of type GDrawCommandPath and GDrawCommandPrecisePath

#### Parameters
 command

[GDrawCommand](/docs/c/Graphics/Draw_Commands/#GDrawCommand) from which to get the path open status

#### Returns

true if the path is open

void gdraw\_command\_set\_hidden([GDrawCommand](/docs/c/Graphics/Draw_Commands/#GDrawCommand) \* command, bool hidden)

Set a command as hidden. This command will not be drawn when [gdraw\_command\_draw](/docs/c/Graphics/Draw_Commands/#gdraw_command_draw) is called with this command.

#### Parameters
 command

[GDrawCommand](/docs/c/Graphics/Draw_Commands/#GDrawCommand) for which to set the hidden status

 hidden

true if command should be hidden

bool gdraw\_command\_get\_hidden([GDrawCommand](/docs/c/Graphics/Draw_Commands/#GDrawCommand) \* command)

Return whether a command is hidden.

#### Parameters
 command

[GDrawCommand](/docs/c/Graphics/Draw_Commands/#GDrawCommand) from which to get the hidden status

#### Returns

true if command is hidden

void gdraw\_command\_frame\_draw(GContext \* ctx, [GDrawCommandSequence](/docs/c/Graphics/Draw_Commands/#GDrawCommandSequence) \* sequence, [GDrawCommandFrame](/docs/c/Graphics/Draw_Commands/#GDrawCommandFrame) \* frame, [GPoint](/docs/c/Graphics/Graphics_Types/#GPoint) offset)

Draw a frame.

#### Parameters
 ctx

The destination graphics context in which to draw

 sequence

The sequence from which the frame comes from (this is required)

 frame

Frame to draw

 offset

Offset from draw context origin to draw the frame

void gdraw\_command\_frame\_set\_duration([GDrawCommandFrame](/docs/c/Graphics/Draw_Commands/#GDrawCommandFrame) \* frame, [uint32\_t](/docs/c/Standard_C/#uint32_t) duration)

Set the duration of the frame.

#### Parameters
 frame

[GDrawCommandFrame](/docs/c/Graphics/Draw_Commands/#GDrawCommandFrame) for which to set the duration

 duration

duration of the frame in milliseconds

[uint32\_t](/docs/c/Standard_C/#uint32_t) gdraw\_command\_frame\_get\_duration([GDrawCommandFrame](/docs/c/Graphics/Draw_Commands/#GDrawCommandFrame) \* frame)

Get the duration of the frame.

#### Parameters
 frame

[GDrawCommandFrame](/docs/c/Graphics/Draw_Commands/#GDrawCommandFrame) from which to get the duration

#### Returns

duration of the frame in milliseconds

[GDrawCommandImage](/docs/c/Graphics/Draw_Commands/#GDrawCommandImage) \* gdraw\_command\_image\_create\_with\_resource([uint32\_t](/docs/c/Standard_C/#uint32_t) resource\_id)

Creates a [GDrawCommandImage](/docs/c/Graphics/Draw_Commands/#GDrawCommandImage) from the specified resource (PDC file)

#### Parameters
 resource\_id

Resource containing data to load and create [GDrawCommandImage](/docs/c/Graphics/Draw_Commands/#GDrawCommandImage) from.

#### Returns

[GDrawCommandImage](/docs/c/Graphics/Draw_Commands/#GDrawCommandImage) pointer if the resource was loaded, NULL otherwise

[GDrawCommandImage](/docs/c/Graphics/Draw_Commands/#GDrawCommandImage) \* gdraw\_command\_image\_clone([GDrawCommandImage](/docs/c/Graphics/Draw_Commands/#GDrawCommandImage) \* image)

Creates a [GDrawCommandImage](/docs/c/Graphics/Draw_Commands/#GDrawCommandImage) as a copy from a given image.

#### Parameters
 image

Image to copy.

#### Returns

cloned image or NULL if the operation failed

void gdraw\_command\_image\_destroy([GDrawCommandImage](/docs/c/Graphics/Draw_Commands/#GDrawCommandImage) \* image)

Deletes the [GDrawCommandImage](/docs/c/Graphics/Draw_Commands/#GDrawCommandImage) structure and frees associated data.

#### Parameters
 image

Pointer to the image to free (delete)

void gdraw\_command\_image\_draw(GContext \* ctx, [GDrawCommandImage](/docs/c/Graphics/Draw_Commands/#GDrawCommandImage) \* image, [GPoint](/docs/c/Graphics/Graphics_Types/#GPoint) offset)

Draw an image.

#### Parameters
 ctx

The destination graphics context in which to draw

 image

Image to draw

 offset

Offset from draw context origin to draw the image

[GSize](/docs/c/Graphics/Graphics_Types/#GSize) gdraw\_command\_image\_get\_bounds\_size([GDrawCommandImage](/docs/c/Graphics/Draw_Commands/#GDrawCommandImage) \* image)

Get size of the bounding box surrounding all draw commands in the image. This bounding box can be used to set the graphics context or layer bounds when drawing the image.

#### Parameters
 image

[GDrawCommandImage](/docs/c/Graphics/Draw_Commands/#GDrawCommandImage) from which to get the bounding box size

#### Returns

bounding box size

void gdraw\_command\_image\_set\_bounds\_size([GDrawCommandImage](/docs/c/Graphics/Draw_Commands/#GDrawCommandImage) \* image, [GSize](/docs/c/Graphics/Graphics_Types/#GSize) size)

Set size of the bounding box surrounding all draw commands in the image. This bounding box can be used to set the graphics context or layer bounds when drawing the image.

#### Parameters
 image

[GDrawCommandImage](/docs/c/Graphics/Draw_Commands/#GDrawCommandImage) for which to set the bounding box size

 size

bounding box size

[GDrawCommandList](/docs/c/Graphics/Draw_Commands/#GDrawCommandList) \* gdraw\_command\_image\_get\_command\_list([GDrawCommandImage](/docs/c/Graphics/Draw_Commands/#GDrawCommandImage) \* image)

Get the command list of the image.

#### Parameters
 image

[GDrawCommandImage](/docs/c/Graphics/Draw_Commands/#GDrawCommandImage) from which to get the command list

#### Returns

command list

void gdraw\_command\_list\_iterate([GDrawCommandList](/docs/c/Graphics/Draw_Commands/#GDrawCommandList) \* command\_list, [GDrawCommandListIteratorCb](/docs/c/Graphics/Draw_Commands/#GDrawCommandListIteratorCb) handle\_command, void \* callback\_context)

Iterate over all commands in a command list.

#### Parameters
 command\_list

[GDrawCommandList](/docs/c/Graphics/Draw_Commands/#GDrawCommandList) over which to iterate

 handle\_command

iterator callback

 callback\_context

context pointer to be passed into the iterator callback

void gdraw\_command\_list\_draw(GContext \* ctx, [GDrawCommandList](/docs/c/Graphics/Draw_Commands/#GDrawCommandList) \* command\_list)

Draw all commands in a command list.

#### Parameters
 ctx

The destination graphics context in which to draw

 command\_list

list of commands to draw

[GDrawCommand](/docs/c/Graphics/Draw_Commands/#GDrawCommand) \* gdraw\_command\_list\_get\_command([GDrawCommandList](/docs/c/Graphics/Draw_Commands/#GDrawCommandList) \* command\_list, [uint16\_t](/docs/c/Standard_C/#uint16_t) command\_idx)

Get the command at the specified index.

##### Note

the specified index must be less than the number of commands in the list

#### Parameters
 command\_list

[GDrawCommandList](/docs/c/Graphics/Draw_Commands/#GDrawCommandList) from which to get a command

 command\_idx

index of the command to get

#### Returns

pointer to [GDrawCommand](/docs/c/Graphics/Draw_Commands/#GDrawCommand) at the specified index

[uint32\_t](/docs/c/Standard_C/#uint32_t) gdraw\_command\_list\_get\_num\_commands([GDrawCommandList](/docs/c/Graphics/Draw_Commands/#GDrawCommandList) \* command\_list)

Get the number of commands in the list.

#### Parameters
 command\_list

[GDrawCommandList](/docs/c/Graphics/Draw_Commands/#GDrawCommandList) from which to get the number of commands

#### Returns

number of commands in command list

[GDrawCommandSequence](/docs/c/Graphics/Draw_Commands/#GDrawCommandSequence) \* gdraw\_command\_sequence\_create\_with\_resource([uint32\_t](/docs/c/Standard_C/#uint32_t) resource\_id)

Creates a [GDrawCommandSequence](/docs/c/Graphics/Draw_Commands/#GDrawCommandSequence) from the specified resource (PDC file)

#### Parameters
 resource\_id

Resource containing data to load and create [GDrawCommandSequence](/docs/c/Graphics/Draw_Commands/#GDrawCommandSequence) from.

#### Returns

[GDrawCommandSequence](/docs/c/Graphics/Draw_Commands/#GDrawCommandSequence) pointer if the resource was loaded, NULL otherwise

[GDrawCommandSequence](/docs/c/Graphics/Draw_Commands/#GDrawCommandSequence) \* gdraw\_command\_sequence\_clone([GDrawCommandSequence](/docs/c/Graphics/Draw_Commands/#GDrawCommandSequence) \* sequence)

Creates a [GDrawCommandSequence](/docs/c/Graphics/Draw_Commands/#GDrawCommandSequence) as a copy from a given sequence.

#### Parameters
 sequence

Sequence to copy

#### Returns

cloned sequence or NULL if the operation failed

void gdraw\_command\_sequence\_destroy([GDrawCommandSequence](/docs/c/Graphics/Draw_Commands/#GDrawCommandSequence) \* sequence)

Deletes the [GDrawCommandSequence](/docs/c/Graphics/Draw_Commands/#GDrawCommandSequence) structure and frees associated data.

#### Parameters
 image

Pointer to the sequence to destroy

[GDrawCommandFrame](/docs/c/Graphics/Draw_Commands/#GDrawCommandFrame) \* gdraw\_command\_sequence\_get\_frame\_by\_elapsed([GDrawCommandSequence](/docs/c/Graphics/Draw_Commands/#GDrawCommandSequence) \* sequence, [uint32\_t](/docs/c/Standard_C/#uint32_t) elapsed\_ms)

Get the frame that should be shown after the specified amount of elapsed time The last frame will be returned if the elapsed time exceeds the total time.

#### Parameters
 sequence

[GDrawCommandSequence](/docs/c/Graphics/Draw_Commands/#GDrawCommandSequence) from which to get the frame

 elapsed\_ms

elapsed time in milliseconds

#### Returns

pointer to [GDrawCommandFrame](/docs/c/Graphics/Draw_Commands/#GDrawCommandFrame) that should be displayed at the elapsed time

[GDrawCommandFrame](/docs/c/Graphics/Draw_Commands/#GDrawCommandFrame) \* gdraw\_command\_sequence\_get\_frame\_by\_index([GDrawCommandSequence](/docs/c/Graphics/Draw_Commands/#GDrawCommandSequence) \* sequence, [uint32\_t](/docs/c/Standard_C/#uint32_t) index)

Get the frame at the specified index.

#### Parameters
 sequence

[GDrawCommandSequence](/docs/c/Graphics/Draw_Commands/#GDrawCommandSequence) from which to get the frame

 index

Index of frame to get

#### Returns

pointer to [GDrawCommandFrame](/docs/c/Graphics/Draw_Commands/#GDrawCommandFrame) at the specified index

[GSize](/docs/c/Graphics/Graphics_Types/#GSize) gdraw\_command\_sequence\_get\_bounds\_size([GDrawCommandSequence](/docs/c/Graphics/Draw_Commands/#GDrawCommandSequence) \* sequence)

Get the size of the bounding box surrounding all draw commands in the sequence. This bounding box can be used to set the graphics context or layer bounds when drawing the frames in the sequence.

#### Parameters
 sequence

[GDrawCommandSequence](/docs/c/Graphics/Draw_Commands/#GDrawCommandSequence) from which to get the bounds

#### Returns

bounding box size

void gdraw\_command\_sequence\_set\_bounds\_size([GDrawCommandSequence](/docs/c/Graphics/Draw_Commands/#GDrawCommandSequence) \* sequence, [GSize](/docs/c/Graphics/Graphics_Types/#GSize) size)

Set size of the bounding box surrounding all draw commands in the sequence. This bounding box can be used to set the graphics context or layer bounds when drawing the frames in the sequence.

#### Parameters
 sequence

[GDrawCommandSequence](/docs/c/Graphics/Draw_Commands/#GDrawCommandSequence) for which to set the bounds

 size

bounding box size

[uint32\_t](/docs/c/Standard_C/#uint32_t) gdraw\_command\_sequence\_get\_play\_count([GDrawCommandSequence](/docs/c/Graphics/Draw_Commands/#GDrawCommandSequence) \* sequence)

Get the play count of the sequence.

#### Parameters
 sequence

[GDrawCommandSequence](/docs/c/Graphics/Draw_Commands/#GDrawCommandSequence) from which to get the play count

#### Returns

play count of sequence

void gdraw\_command\_sequence\_set\_play\_count([GDrawCommandSequence](/docs/c/Graphics/Draw_Commands/#GDrawCommandSequence) \* sequence, [uint32\_t](/docs/c/Standard_C/#uint32_t) play\_count)

Set the play count of the sequence.

#### Parameters
 sequence

[GDrawCommandSequence](/docs/c/Graphics/Draw_Commands/#GDrawCommandSequence) for which to set the play count

 play\_count

play count

[uint32\_t](/docs/c/Standard_C/#uint32_t) gdraw\_command\_sequence\_get\_total\_duration([GDrawCommandSequence](/docs/c/Graphics/Draw_Commands/#GDrawCommandSequence) \* sequence)

Get the total duration of the sequence.

#### Parameters
 sequence

[GDrawCommandSequence](/docs/c/Graphics/Draw_Commands/#GDrawCommandSequence) from which to get the total duration

#### Returns

total duration of the sequence in milliseconds

[uint32\_t](/docs/c/Standard_C/#uint32_t) gdraw\_command\_sequence\_get\_num\_frames([GDrawCommandSequence](/docs/c/Graphics/Draw_Commands/#GDrawCommandSequence) \* sequence)

Get the number of frames in the sequence.

#### Parameters
 sequence

[GDrawCommandSequence](/docs/c/Graphics/Draw_Commands/#GDrawCommandSequence) from which to get the number of frames

#### Returns

number of frames in the sequence

[GDrawCommandList](/docs/c/Graphics/Draw_Commands/#GDrawCommandList) \* gdraw\_command\_frame\_get\_command\_list([GDrawCommandFrame](/docs/c/Graphics/Draw_Commands/#GDrawCommandFrame) \* frame)

Get the command list of the frame.

#### Parameters
 frame

[GDrawCommandFrame](/docs/c/Graphics/Draw_Commands/#GDrawCommandFrame) from which to get the command list

#### Returns

command list

## Enum Documentation

enum GDrawCommandType

#### Enumerators
GDrawCommandTypeInvalid

Invalid draw command type.

GDrawCommandTypePath

Arbitrary path draw command type.

GDrawCommandTypeCircle

Circle draw command type.

GDrawCommandTypePrecisePath

Arbitrary path drawn with sub-pixel precision (1/8th precision)

## Typedef Documentation

 typedef struct [GDrawCommand](/docs/c/Graphics/Draw_Commands/#GDrawCommand) GDrawCommand

Draw commands are the basic building block of the draw command system, encoding the type of command to draw, the stroke width and color, fill color, and points that define the path (or center of a circle.

 typedef struct [GDrawCommandFrame](/docs/c/Graphics/Draw_Commands/#GDrawCommandFrame) GDrawCommandFrame

Draw command frames contain a list of commands to draw for that frame and a duration, indicating the length of time for which the frame should be drawn in an animation sequence. Frames form the building blocks of a [GDrawCommandSequence](/docs/c/Graphics/Draw_Commands/#GDrawCommandSequence), which consists of multiple frames.

 typedef struct [GDrawCommandImage](/docs/c/Graphics/Draw_Commands/#GDrawCommandImage) GDrawCommandImage

Draw command images contain a list of commands that can be drawn. An image can be loaded from PDC file data.

 typedef struct [GDrawCommandList](/docs/c/Graphics/Draw_Commands/#GDrawCommandList) GDrawCommandList

Draw command lists contain a list of commands that can be iterated over and drawn all at once.

 typedef bool(\* GDrawCommandListIteratorCb)(GDrawCommand \*command, uint32\_t index, void \*context) 

Callback for iterating over draw command list.

#### Parameters
 command

current [GDrawCommand](/docs/c/Graphics/Draw_Commands/#GDrawCommand) in iteration

 index

index of the current command in the list

 context

context pointer for the iteration operation

#### Returns

true if the iteration should continue after this command is processed

 typedef struct [GDrawCommandSequence](/docs/c/Graphics/Draw_Commands/#GDrawCommandSequence) GDrawCommandSequence

Draw command sequences allow the animation of frames over time. Each sequence has a list of frames that can be accessed by the elapsed duration of the animation (not maintained internally) or by index. Sequences can be loaded from PDC file data.
