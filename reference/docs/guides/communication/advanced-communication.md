# Advanced Communication

Source: https://developer.repebble.com/guides/communication/advanced-communication/

Many types of connected Pebble watchapps and watchfaces perform common tasks such as the ones discussed here. Following these best practices can increase the quality of the implementation of each one, and avoid common bugs.

## Waiting for PebbleKit JS

Any app that wishes to send data from the watch to the phone via[_PebbleKit JS_](/guides/communication/using-pebblekit-js.md) **must** wait until the JavaScript `ready` event has occured, indicating that the phone has loaded the JavaScript component of the launching app. If this JavaScript code implements the `appmessage` event listsner, it is ready to receive data.

> An watchapp that only _receives_ data from PebbleKit JS does not have to wait for the `ready` event. In addition, Android companion apps do not have to wait for such an event thanks to the `Intent` system. iOS companion apps must wait for `-watchDidConnect:`.

A simple method is to define a key in `package.json` that will be interpreted by the watchapp to mean that the JS environment is ready for exchange data:

```
"messageKeys": ["JSReady"]
```

The watchapp should implement a variable that describes if the `ready` event has occured. An example is shown below:

```
static bool s\_js\_ready;
```

This can be exported in a header file for other parts of the app to check. Any parts of the app that are waiting should call this as part of a[retry](#timeouts-and-retries) mechanism.

```
bool comm\_is\_js\_ready() {return s\_js\_ready;}
```

The state of this variable will be `false` until set to `true` when the `ready`event causes the key to be transmitted:

```
Pebble.addEventListener('ready', function() {console.log('PebbleKit JS ready.');// Update s\_js\_ready on watchPebble.sendAppMessage({'JSReady': 1});});
```

This key should be interpreted in the app's [`AppMessageInboxReceived`](/docs/c/Foundation/AppMessage/#AppMessageInboxReceived "AppMessageInboxReceived")implementation:

```
static void inbox\_received\_handler(DictionaryIterator \*iter, void \*context) {Tuple \*ready\_tuple = dict\_find(iter, MESSAGE\_KEY\_JSReady);if(ready\_tuple) {// PebbleKit JS is ready! Safe to send messagess\_js\_ready = true;}}
```

## Timeouts and Retries

Due to the wireless and stateful nature of the Bluetooth connection, some messages sent between the watch and phone may fail. A tried-and-tested method for dealing with these failures is to implement a 'timeout and retry' mechanism. Under such a scheme:

- A message is sent and a timer started.

- If the message is sent successfully (and optionally a reply received), the timer is cancelled.

- If the timer elapses before the message can be sent successfully, the message is reattempted. Depending on the nature of the failure, a suitable retry interval (such as a few seconds) is used to avoid saturating the connection.

The interval chosen before a timeout occurs and the message is resent may vary depending on the circumstances. The first failure should be reattempted fairly quickly (one second), with the interval increasing as successive failures occurs. If the connection is not available the timer interval should be[even longer](https://en.wikipedia.org/wiki/Exponential_backoff), or wait until the connection is restored.

### Using a Timeout Timer

The example below shows the sending of a message and scheduling a timeout timer. The first step is to declare a handle for the timeout timer:

```
static AppTimer \*s\_timeout\_timer;
```

When the message is sent, the timer should be scheduled:

```
static void send\_with\_timeout(int key, int value) {// Construct and send the messageDitionaryIterator \*iter;if(app\_message\_outbox\_begin(&iter) == APP\_MSG\_OK) {dict\_write\_int(iter, key, &value, sizeof(int), true);app\_message\_outbox\_send();}// Schedule the timeout timerconst int interval\_ms = 1000;s\_timout\_timer = app\_timer\_register(interval\_ms, timout\_timer\_handler, NULL);}
```

If the [`AppMessageOutboxSent`](/docs/c/Foundation/AppMessage/#AppMessageOutboxSent "AppMessageOutboxSent") is called, the message was a success, and the timer should be cancelled:

```
static void outbox\_sent\_handler(DictionaryIterator \*iter, void \*context) {// Successful message, the timeout is not needed anymore for this messageapp\_timer\_cancel(s\_timout\_timer);}
```

### Retry a Failed Message

However, if the timeout timer elapses before the message's success can be determined or an expected reply is not received, the callback to`timout_timer_handler()` should be used to inform the user of the failure, and schedule another attempt and retry the message:

```
static void timout\_timer\_handler(void \*context) {// The timer elapsed because no success was reportedtext\_layer\_set\_text(s\_status\_layer, "Failed. Retrying...");// Retry the messagesend\_with\_timeout(some\_key, some\_value);}
```

Alternatively, if the [`AppMessageOutboxFailed`](/docs/c/Foundation/AppMessage/#AppMessageOutboxFailed "AppMessageOutboxFailed") is called the message failed to send, sometimes immediately. The timeout timer should be cancelled and the message reattempted after an additional delay (the 'retry interval') to avoid saturating the channel:

```
static void outbox\_failed\_handler(DictionaryIterator \*iter,AppMessageResult reason, void \*context) {// Message failed before timer elapsed, reschedule for laterif(s\_timout\_timer) {app\_timer\_cancel(s\_timout\_timer);}// Inform the user of the failuretext\_layer\_set\_text(s\_status\_layer, "Failed. Retrying...");// Use the timeout handler to perform the same action - resend the messageconst int retry\_interval\_ms = 500;app\_timer\_register(retry\_interval\_ms, timout\_timer\_handler, NULL);}
```

> Note: All eventualities where a message fails must invoke a resend of the message, or the purpose of an automated 'timeout and retry' mechanism is defeated. However, the number of attempts made and the interval between them is for the developer to decide.

## Sending Lists

Until SDK 3.8, the size of [`AppMessage`](/docs/c/Foundation/AppMessage/ "AppMessage") buffers did not facilitate sending large amounts of data in one message. With the current buffer sizes of up to 8k for each an outbox the need for efficient transmission of multiple sequential items of data is lessened, but the technique is still important. For instance, to transmit sensor data as fast as possible requires careful scheduling of successive messages.

Because there is no guarantee of how long a message will take to transmit, simply using timers to schedule multiple messages after one another is not reliable. A much better method is to make good use of the callbacks provided by the [`AppMessage`](/docs/c/Foundation/AppMessage/ "AppMessage") API.

### Sending a List to the Phone

For instance, the [`AppMessageOutboxSent`](/docs/c/Foundation/AppMessage/#AppMessageOutboxSent "AppMessageOutboxSent") callback can be used to safely schedule the next message to the phone, since the previous one has been acknowledged by the other side at that time. Here is an example array of items:

```
static int s\_data[] = { 2, 4, 8, 16, 32, 64 };#define NUM\_ITEMS sizeof(s\_data);
```

A variable can be used to keep track of the current list item index that should be transmitted next:

```
static int s\_index = 0;
```

When a message has been sent, this index is used to construct the next message:

> Note: A useful key scheme is to use the item's array index as the key. For PebbleKit JS that number of keys will have to be declared in `package.json`, like so: `someArray[6]`

```
static void outbox\_sent\_handler(DictionaryIterator \*iter, void \*context) {// Increment the indexs\_index++;if(s\_index \< NUM\_ITEMS) {// Send the next itemDictionaryIterator \*iter;if(app\_message\_outbox\_begin(&iter) == APP\_MSG\_OK) {dict\_write\_int(iter, MESSAGE\_KEY\_someArray + s\_index, &s\_data[s\_index], sizeof(int), true);app\_message\_outbox\_send();}} else {// We have reached the end of the sequenceAPP\_LOG(APP\_LOG\_LEVEL\_INFO, "All transmission complete!");}}
```

This results in a callback loop that repeats until the last data item has been transmitted, and the index becomes equal to the total number of items. This technique can be combined with a timeout and retry mechanism to reattempt a particular item if transmission fails. This is a good way to avoid gaps in the received data items.

On the phone side, the data items are received in the same order. An analogous`index` variable is used to keep track of which item has been received. This process will look similar to the example shown below:

```
var NUM\_ITEMS = 6;var keys = require('message\_keys');var data = [];var index = 0;Pebble.addEventListener('appmessage', function(e) {// Store this data itemdata[index] = e.payload[keys.someArray + index];// Increment index for next messageindex++;if(index == NUM\_ITEMS) {console.log('Received all data items!');}});
```

### Sending a List to Pebble

Conversely, the `success` callback of `Pebble.sendAppMessage()` in PebbleKit JS is the equivalent safe time to send the next message to the watch.

An example implementation that achieves this is shown below. After the message is sent with `Pebble.sendAppMessage()`, the `success` callback calls the`sendNextItem()` function repeatedly until the index is larger than that of the last list item to be sent, and transmission will be complete. Again, an index variable is maintained to keep track of which item is being transmitted:

```
var keys = require('message\_keys');function sendNextItem(items, index) {// Build messagevar key = keys.someArray + index;var dict = {};dict[key] = items[index];// Send the messagePebble.sendAppMessage(dict, function() {// Use success callback to increment indexindex++;if(index \< items.length) {// Send next itemsendNextItem(items, index);} else {console.log('Last item sent!');}}, function() {console.log('Item transmission failed at index: ' + index);});}function sendList(items) {var index = 0;sendNextItem(items, index);}function onDownloadComplete(responseText) {// Some web response containing a JSON object arrayvar json = JSON.parse(responseText);// Begin transmission loopsendList(json.items);}
```

On the watchapp side, the items are received in the same order in the[`AppMessageInboxReceived`](/docs/c/Foundation/AppMessage/#AppMessageInboxReceived "AppMessageInboxReceived") handler:

```
#define NUM\_ITEMS 6static int s\_index;static int s\_data[NUM\_ITEMS];
```

```
static void inbox\_received\_handler(DictionaryIterator \*iter, void \*context) {Tuple \*data\_t = dict\_find(iter, MESSAGE\_KEY\_someArray + s\_index);if(data\_t) {// Store this items\_data[index] = (int)data\_t-\>value-\>int32;// Increment index for next items\_index++;}if(s\_index == NUM\_ITEMS) {// We have reached the end of the sequenceAPP\_LOG(APP\_LOG\_LEVEL\_INFO, "All transmission complete!");}}
```

This sequence of events is demonstrated for PebbleKit JS, but the same technique can be applied exactly to either and Android or iOS companion app wishing to transmit many data items to Pebble.

Get the complete source code for this example from the[`list-items-example`](https://github.com/pebble-examples/list-items-example)repository on GitHub.

## Sending Image Data

A common task developers want to accomplish is display a dynamically loaded image resource (for example, showing an MMS photo or a news item thumbnail pulled from a webservice). Because some images could be larger than the largest buffer size available to the app, the techniques shown above for sending lists also prove useful here, as the image is essentially a list of color byte values.

### Image Data Format

There are two methods available for displaying image data downloaded from the web:

1. Download a `png` image, transmit the compressed data, and decompress using[`gbitmap_create_from_png_data()`](/docs/c/Graphics/Graphics_Types/#gbitmap_create_from_png_data "gbitmap\_create\_from\_png\_data"). This involves sending less data, but can be prone to failure depending on the exact format of the image. The image must be in a compatible palette (1, 2, 4, or 8-bit) and small enough such that there is enough memory for a compessed copy, an uncompressed copy, and ~2k overhead when it is being processed.

2. Download a `png` image, decompress in the cloud or in PebbleKit JS into an array of image pixel bytes, transmit the pixel data into a blank[`GBitmap`](/docs/c/Graphics/Graphics_Types/#GBitmap "GBitmap")'s `data` member. Each byte must be in the compatible Pebble color format (2 bits per ARGB). This process can be simplified by pre-formatting the image to be dowloaded, as resizing or palette-reduction is difficult to do locally.

### Sending Compressed PNG Data

As the fastest and least complex of the two methods described above, an example of how to display a compressed PNG image will be discussed here. The image that will be displayed is[the HTML 5 logo](https://www.w3.org/html/logo/):

![The HTML5 logo.](/assets/images/guides/pebble-apps/communications/html5-logo-small.png)

> Note: The above image has been resized and palettized for compatibility.

To download this image in PebbleKit JS, use an `XmlHttpRequest` object. It is important to specify the `responseType` as 'arraybuffer' to obtain the image data in the correct format:

```
function downloadImage() {var url = 'https://developer.repebble.com/assets/images/guides/pebble-apps/communications/html5-logo-small.png';var request = new XMLHttpRequest();request.onload = function() {processImage(this.response);};request.responseType = "arraybuffer";request.open("GET", url);request.send();}
```

When the response has been received, `processImage()` will be called. The received data must be converted into an array of unsigned bytes, which is achieved through the use of a `Uint8Array`. This process is shown below (see the[`png-download-example`](https://github.com/pebble-examples/png-download-example)repository for the full example):

```
function processImage(responseData) {// Convert to a arrayvar byteArray = new Uint8Array(responseData);var array = [];for(var i = 0; i \< byteArray.byteLength; i++) {array.push(byteArray[i]);}// Send chunks to PebbletransmitImage(array);}
```

Now that the image data has been converted, the transmission to Pebble can begin. At a high level, the JS side transmits the image data in chunks, using an incremental array index to coordinate saving of data on the C side in a mirror array. In downloading the image data, the following keys are used for the specified purposes:

| Key | Purpose |
| --- | --- |
| `Index` | The array index that the current chunk should be stored at. This gets larger as each chunk is transmitted. |
| `DataLength` | This length of the entire data array to be downloaded. As the image is compressed, this is _not_ the product of the width and height of the image. |
| `DataChunk` | The chunk's image data. |
| `ChunkSize` | The size of this chunk. |
| `Complete` | Used to signify that the image transfer is complete. |

The first message in the sequence should tell the C side how much memory to allocate to store the compressed image data:

```
function transmitImage(array) {var index = 0;var arrayLength = array.length;// Transmit the length for array allocationPebble.sendAppMessage({'DataLength': arrayLength}, function(e) {// Success, begin sending chunkssendChunk(array, index, arrayLength);}, function(e) {console.log('Failed to initiate image transfer!');})}
```

If this message is successful, the transmission of actual image data commences with the first call to `sendChunk()`. This function calculates the size of the next chunk (the smallest of either the size of the `AppMessage` inbox buffer, or the remainder of the data) and assembles the dictionary containing the index in the array it is sliced from, the length of the chunk, and the actual data itself:

```
function sendChunk(array, index, arrayLength) {// Determine the next chunk sizevar chunkSize = BUFFER\_SIZE;if(arrayLength - index \< BUFFER\_SIZE) {// Resize to fit just the remaining data itemschunkSize = arrayLength - index;}// Prepare the dictionaryvar dict = {'DataChunk': array.slice(index, index + chunkSize),'ChunkSize': chunkSize,'Index': index};// Send the chunkPebble.sendAppMessage(dict, function() {// Successindex += chunkSize;if(index \< arrayLength) {// Send the next chunksendChunk(array, index, arrayLength);} else {// Complete!Pebble.sendAppMessage({'Complete': 0});}}, function(e) {console.log('Failed to send chunk with index ' + index);});}
```

After each chunk is sent, the index is incremented with the size of the chunk that was just sent, and compared to the total length of the array. If the index exceeds the size of the array, the loop has sent all the data (this could be just a single chunk if the array is smaller than the maximum message size). The`AppKeyComplete` key is sent to inform the C side that the image is complete and ready for display.

### Receiving Compressed PNG Data

In the previous section, the process for using PebbleKit JS to download and transmit an image to the C side was discussed. The process for storing and displaying this data is discussed here. Only when both parts work in harmony can an image be successfully shown from the web.

The majority of the process takes place within the watchapp's[`AppMessageInboxReceived`](/docs/c/Foundation/AppMessage/#AppMessageInboxReceived "AppMessageInboxReceived") handler, with the presence of each key being detected and the appropriate actions taken to reconstruct the image.

The first item expected is the total size of the data to be transferred. This is recorded (for later use with [`gbitmap_create_from_png_data()`](/docs/c/Graphics/Graphics_Types/#gbitmap_create_from_png_data "gbitmap\_create\_from\_png\_data")) and the buffer used to store the chunks is allocated to this exact size:

```
static uint8\_t \*s\_img\_data;static int s\_img\_size;
```

```
// Get the received image chunkTuple \*img\_size\_t = dict\_find(iter, MESSAGE\_KEY\_DataLength);if(img\_size\_t) {s\_img\_size = img\_size\_t-\>value-\>int32;// Allocate buffer for image dataimg\_data = (uint8\_t\*)malloc(s\_img\_size \* sizeof(uint8\_t));}
```

When the message containing the data size is acknowledged, the JS side begins sending chunks with `sendChunk()`. When one of these subsequent messages is received, the three keys (`DataChunk`, `ChunkSize`, and`Index`) are used to store that chunk of data at the correct offset in the array:

```
// An image chunkTuple \*chunk\_t = dict\_find(iter, MESSAGE\_KEY\_DataChunk);if(chunk\_t) {uint8\_t \*chunk\_data = chunk\_t-\>value-\>data;Tuple \*chunk\_size\_t = dict\_find(iter, MESSAGE\_KEY\_ChunkSize);int chunk\_size = chunk\_size\_t-\>value-\>int32;Tuple \*index\_t = dict\_find(iter, MESSAGE\_KEY\_Index);int index = index\_t-\>value-\>int32;// Save the chunkmemcpy(&s\_img\_data[index], chunk\_data, chunk\_size);}
```

Finally, once the array index exceeds the size of the data array on the JS side, the `AppKeyComplete` key is transmitted, triggering the data to be transformed into a [`GBitmap`](/docs/c/Graphics/Graphics_Types/#GBitmap "GBitmap"):

```
static BitmapLayer \*s\_bitmap\_layer;static GBitmap \*s\_bitmap;
```

```
// Complete?Tuple \*complete\_t = dict\_find(iter, MESSAGE\_KEY\_Complete);if(complete\_t) {// Create new GBitmap from downloaded PNG datas\_bitmap = gbitmap\_create\_from\_png\_data(s\_img\_data, s\_img\_size);// Show the imageif(s\_bitmap) {bitmap\_layer\_set\_bitmap(s\_bitmap\_layer, s\_bitmap);} else {APP\_LOG(APP\_LOG\_LEVEL\_ERROR, "Error creating GBitmap from PNG data!");}}
```

The final result is a compressed PNG image downloaded from the web displayed in a Pebble watchapp.

![watch](/assets/images/guides/pebble-apps/communications/html-5-watch.png)

Get the complete source code for this example from the[`png-download-example`](https://github.com/pebble-examples/png-download-example)repository on GitHub.
