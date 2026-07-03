# Animated Images

Source: https://developer.repebble.com/guides/app-resources/animated-images/

The Pebble SDK allows animated images to be played inside an app using the[`GBitmapSequence`](/docs/c/Graphics/Graphics_Types/#GBitmapSequence "GBitmapSequence") API, which takes [APNG](https://en.wikipedia.org/wiki/APNG)images as input files. APNG files are similar to well-known `.gif` files, which are not supported directly but can be converted to APNG.

A similar effect can be achieved with multiple image resources, a[`BitmapLayer`](/docs/c/User_Interface/Layers/BitmapLayer/ "BitmapLayer") and an [`AppTimer`](/docs/c/Foundation/Timer/#AppTimer "AppTimer"), but would require a lot more code. The[`GBitmapSequence`](/docs/c/Graphics/Graphics_Types/#GBitmapSequence "GBitmapSequence") API handles the reading, decompression, and frame duration/count automatically.

## Converting GIF to APNG

A `.gif` file can be converted to the APNG `.png` format with[gif2apng](http://gif2apng.sourceforge.net/) and the `-z0` flag:

```
./gif2apng -z0 animation.gif
```

> Note: The file extension must be `.png`, **not** `.apng`.

## Adding an APNG

Include the APNG file in the `resources` array in `package.json` as a `raw`resource:

```
"resources": {"media": [{"type":"raw","name":"ANIMATION","file":"images/animation.png"}]}
```

## Displaying APNG Frames

The [`GBitmapSequence`](/docs/c/Graphics/Graphics_Types/#GBitmapSequence "GBitmapSequence") will use a [`GBitmap`](/docs/c/Graphics/Graphics_Types/#GBitmap "GBitmap") as a container and update its contents each time a new frame is read from the APNG file. This means that the first step is to create a blank [`GBitmap`](/docs/c/Graphics/Graphics_Types/#GBitmap "GBitmap") to be this container.

Declare file-scope variables to hold the data:

```
static GBitmapSequence \*s\_sequence;static GBitmap \*s\_bitmap;
```

Load the APNG from resources into the [`GBitmapSequence`](/docs/c/Graphics/Graphics_Types/#GBitmapSequence "GBitmapSequence") variable, and use the frame size to create the blank [`GBitmap`](/docs/c/Graphics/Graphics_Types/#GBitmap "GBitmap") frame container:

```
// Create sequences\_sequence = gbitmap\_sequence\_create\_with\_resource(RESOURCE\_ID\_ANIMATION);// Create blank GBitmap using APNG frame sizeGSize frame\_size = gbitmap\_sequence\_get\_bitmap\_size(s\_sequence);s\_bitmap = gbitmap\_create\_blank(frame\_size, GBitmapFormat8Bit);
```

Once the app is ready to begin playing the animated image, advance each frame using an [`AppTimer`](/docs/c/Foundation/Timer/#AppTimer "AppTimer") until the end of the sequence is reached. Loading the next APNG frame is handled for you and written to the container [`GBitmap`](/docs/c/Graphics/Graphics_Types/#GBitmap "GBitmap").

Declare a [`BitmapLayer`](/docs/c/User_Interface/Layers/BitmapLayer/ "BitmapLayer") variable to display the current frame, and set it up as described under[_Displaying An Image_](/guides/app-resources/images.md#displaying-an-image).

```
static BitmapLayer \*s\_bitmap\_layer;
```

Create the callback to be used when the [`AppTimer`](/docs/c/Foundation/Timer/#AppTimer "AppTimer") has elapsed, and the next frame should be displayed. This will occur in a loop until there are no more frames, and [`gbitmap_sequence_update_bitmap_next_frame()`](/docs/c/Graphics/Graphics_Types/#gbitmap_sequence_update_bitmap_next_frame "gbitmap\_sequence\_update\_bitmap\_next\_frame") returns `false`:

```
static void timer\_handler(void \*context) {uint32\_t next\_delay;// Advance to the next APNG frame, and get the delay for this frameif(gbitmap\_sequence\_update\_bitmap\_next\_frame(s\_sequence, s\_bitmap, &next\_delay)) {// Set the new frame into the BitmapLayerbitmap\_layer\_set\_bitmap(s\_bitmap\_layer, s\_bitmap);layer\_mark\_dirty(bitmap\_layer\_get\_layer(s\_bitmap\_layer));// Timer for that frame's delayapp\_timer\_register(next\_delay, timer\_handler, NULL);}}
```

When appropriate, schedule the first frame advance with an [`AppTimer`](/docs/c/Foundation/Timer/#AppTimer "AppTimer"):

```
uint32\_t first\_delay\_ms = 10;// Schedule a timer to advance the first frameapp\_timer\_register(first\_delay\_ms, timer\_handler, NULL);
```

When the app exits or the resource is no longer required, destroy the[`GBitmapSequence`](/docs/c/Graphics/Graphics_Types/#GBitmapSequence "GBitmapSequence") and the container [`GBitmap`](/docs/c/Graphics/Graphics_Types/#GBitmap "GBitmap"):

```
gbitmap\_sequence\_destroy(s\_sequence);gbitmap\_destroy(s\_bitmap);
```
