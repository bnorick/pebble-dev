# Raw Data Files

Source: https://developer.repebble.com/guides/app-resources/raw-data-files/

Some kinds of apps will require extra data that is not a font or an image. In these cases, the file can be included in a Pebble project as a raw resource. When a file is included as a raw resource, it is not modified in any way from the original when the app is built.

Applications of this resource type can be found in the Pebble SDK for APIs such as [`GDrawCommand`](/docs/c/Graphics/Draw_Commands/#GDrawCommand "GDrawCommand") and [`GBitmapSequence`](/docs/c/Graphics/Graphics_Types/#GBitmapSequence "GBitmapSequence"), which both use raw resources as input files. Other possible applications include localized string dictionaries, CSV data files, etc.

## Adding Raw Data Files

To add a file as a raw resource, specify its `type` as `raw` in `package.json`. An example is shown below:

```
"resources": {"media": [{"type": "raw","name": "EXAMPLE\_DATA\_FILE","file": "data.bin"}]}
```

## Reading Bytes and Byte Ranges

Once a raw resource has been added to a project, it can be loaded at runtime in a manner similar to other resources types:

```
// Get resource handleResHandle handle = resource\_get\_handle(RESOURCE\_ID\_DATA);
```

With a handle to the resource now available in the app, the size of the resource can be determined:

```
// Get size of the resource in bytessize\_t res\_size = resource\_size(handle);
```

To read bytes from the resource, create an appropriate byte buffer and copy data into it:

```
// Create a buffer the exact size of the raw resourceuint8\_t \*s\_buffer = (uint8\_t\*)malloc(res\_size);
```

The example below copies the entire resource into a `uint8_t` buffer:

```
// Copy all bytes to a bufferresource\_load(handle, s\_buffer, res\_size);
```

It is also possible to read a specific range of bytes from a given offset into the buffer:

```
// Read the second set of 8 bytesresource\_load\_byte\_range(handle, 8, s\_buffer, 8);
```
