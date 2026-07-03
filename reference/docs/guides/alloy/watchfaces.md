# Watchfaces

Source: https://developer.repebble.com/guides/alloy/watchfaces/

Watchfaces are a special type of Pebble app that displays the current time. Alloy makes it easy to create custom watchfaces using either Poco or Piu.

> **Note** : All code in this guide runs on the watch in `src/embeddedjs/main.js`unless otherwise noted.

## Configuration

To create a watchface, set `watchface` to `true` in your `package.json`:

```
{"pebble": {"watchapp": {"watchface": true}}}
```

## Time Events

Subscribe to time change events using the `watch` global. The event callback receives a `Date` instance for the current time:

```
// Called every secondwatch.addEventListener("secondchange", e =\> {updateDisplay(e.date);});// Called every minutewatch.addEventListener("minutechange", e =\> {updateDisplay(e.date);});
```

Use `secondchange` for watchfaces that show seconds, and `minutechange` for those that only show hours and minutes (saves battery). The callback is also invoked immediately when the event listener is installed, so there is no need to call your display function separately at startup.

## Basic Watchface

Here's a simple digital watchface:

```
import Poco from "commodetto/Poco";const render = new Poco(screen);const font = new render.Font("Bitham-Black", 30);const black = render.makeColor(0, 0, 0);const white = render.makeColor(255, 255, 255);function draw(e) {render.begin();render.fillRectangle(white, 0, 0, render.width, render.height);// Get current time as HH:MM:SSconst time = e.date.toTimeString().slice(0, 8);// Center the textconst width = render.getTextWidth(time, font);const x = (render.width - width) / 2;const y = (render.height - font.height) / 2;render.drawText(time, font, black, x, y);render.end();}watch.addEventListener("secondchange", draw);
```

## Getting Time Components

Use the `Date` provided by the event to get individual time components:

```
function getTimeComponents(date) {return {hours: date.getHours(),// 0-23minutes: date.getMinutes(),// 0-59seconds: date.getSeconds(),// 0-59day: date.getDate(),// 1-31month: date.getMonth(),// 0-11year: date.getFullYear(),// e.g., 2025dayOfWeek: date.getDay()// 0-6 (Sunday=0)};}
```

### Formatting Time

```
function formatTime(hours, minutes) {const h = String(hours).padStart(2, "0");const m = String(minutes).padStart(2, "0");return `${h}:${m}`;}function format12Hour(hours, minutes) {const period = hours \>= 12 ? "PM" : "AM";const h = hours % 12 || 12;const m = String(minutes).padStart(2, "0");return `${h}:${m} ${period}`;}
```

## Watchface with Date

```
import Poco from "commodetto/Poco";const render = new Poco(screen);const timeFont = new render.Font("Leco-Regular", 42);const dateFont = new render.Font("Gothic-Regular", 18);const black = render.makeColor(0, 0, 0);const white = render.makeColor(255, 255, 255);const DAYS = ["Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"];const MONTHS = ["Jan", "Feb", "Mar", "Apr", "May", "Jun","Jul", "Aug", "Sep", "Oct", "Nov", "Dec"];function draw(e) {const now = e.date;render.begin();render.fillRectangle(white, 0, 0, render.width, render.height);// Time (HH:MM)const hours = String(now.getHours()).padStart(2, "0");const minutes = String(now.getMinutes()).padStart(2, "0");const timeStr = `${hours}:${minutes}`;let width = render.getTextWidth(timeStr, timeFont);render.drawText(timeStr, timeFont, black,(render.width - width) / 2,(render.height - timeFont.height) / 2 - 15);// Date (e.g., "Mon, Jan 15")const dayName = DAYS[now.getDay()];const monthName = MONTHS[now.getMonth()];const dateStr = `${dayName}, ${monthName} ${now.getDate()}`;width = render.getTextWidth(dateStr, dateFont);render.drawText(dateStr, dateFont, black,(render.width - width) / 2,(render.height - dateFont.height) / 2 + 30);render.end();}watch.addEventListener("minutechange", draw);
```

## Analog Watchface Concepts

For analog watchfaces, calculate hand positions based on time:

```
function getHandAngles(now) {const hours = now.getHours() % 12;const minutes = now.getMinutes();const seconds = now.getSeconds();// Angles in degrees (0 = 12 o'clock)const secondAngle = seconds \* 6;// 360/60 = 6 degrees per secondconst minuteAngle = minutes \* 6 + seconds \* 0.1;const hourAngle = hours \* 30 + minutes \* 0.5; // 360/12 = 30 degrees per hourreturn { hourAngle, minuteAngle, secondAngle };}
```

### Drawing Clock Hands

```
function drawHand(cx, cy, angle, length, color, thickness) {// Convert angle to radians (0 degrees = up)const radians = (angle - 90) \* Math.PI / 180;const endX = cx + Math.cos(radians) \* length;const endY = cy + Math.sin(radians) \* length;render.drawLine(cx, cy, endX, endY, color, thickness);}function drawAnalogClock(e) {const cx = render.width / 2;const cy = render.height / 2;const { hourAngle, minuteAngle, secondAngle } = getHandAngles(e.date);render.begin();render.fillRectangle(white, 0, 0, render.width, render.height);// Hour handdrawHand(cx, cy, hourAngle, 35, black, 4);// Minute handdrawHand(cx, cy, minuteAngle, 55, black, 3);// Second handdrawHand(cx, cy, secondAngle, 60, red, 1);// Center dotrender.drawCircle(black, cx, cy, 4, 0, 360);render.end();}
```

## Using Piu for Watchfaces

You can also build watchfaces with the Piu framework:

```
import {} from "piu/MC";const backgroundSkin = new Skin({ fill: "white" });const timeStyle = new Style({ font: "42px Bitham-Black", color: "black" });class ClockBehavior extends Behavior {onDisplaying(label) {this.updateTime(label);}updateTime(label, date) {const h = String(date.getHours()).padStart(2, "0");const m = String(date.getMinutes()).padStart(2, "0");label.string = `${h}:${m}`;}}const WatchfaceApp = Application.template($ =\> ({skin: backgroundSkin,contents: [Label($, {anchor: "TIME",style: timeStyle,Behavior: ClockBehavior})],Behavior: class extends Behavior {onCreate(app, data) {this.data = data;watch.addEventListener("minutechange", e =\> {this.data.TIME.delegate("updateTime", e.date);});}}}));export default new WatchfaceApp({}, {});
```

## Battery and Connection Status

Good watchfaces show battery and connection status:

```
import Battery from "embedded:sensor/Battery";let batteryPercent = 100;let isConnected = false;// Battery monitoringconst battery = new Battery({onSample() {batteryPercent = this.sample().percent;updateDisplay();}});batteryPercent = battery.sample().percent;// Connection monitoringfunction checkConnection() {isConnected = watch.connected.app;console.log("Connected: " + isConnected);updateDisplay();}watch.addEventListener('connected', checkConnection);checkConnection();function drawStatusBar() {// Battery indicatorconst batteryText = batteryPercent + "%";render.drawText(batteryText, smallFont, gray, 10, 5);// Connection indicator (show X when disconnected)if (!isConnected) {render.drawText("X", smallFont, gray, render.width - 20, 5);}}
```

## Performance Tips

1. **Use minutechange when possible** : Updating every minute instead of every second significantly improves battery life.

2. **Minimize redraw area** : Use `render.begin(x, y, w, h)` to only update changed portions of the screen.

3. **Precompute values** : Calculate font sizes, positions, and colors once at startup.

4. **Avoid complex calculations in draw** : Do math outside the render begin/end block when possible.

5. **Use the provided Date** : Use the `Date` instance from the event instead of creating your own.

## Complete Example: Minimal Watchface

```
import Poco from "commodetto/Poco";import Battery from "embedded:sensor/Battery";const render = new Poco(screen);const timeFont = new render.Font("Leco-Regular", 42);const dateFont = new render.Font("Gothic-Regular", 18);const black = render.makeColor(0, 0, 0);const white = render.makeColor(255, 255, 255);const gray = render.makeColor(128, 128, 128);const DAYS = ["Sunday", "Monday", "Tuesday", "Wednesday","Thursday", "Friday", "Saturday"];let batteryPercent = 100;const battery = new Battery({onSample() {batteryPercent = this.sample().percent;}});batteryPercent = battery.sample().percent;function draw(e) {const now = e.date;render.begin();render.fillRectangle(black, 0, 0, render.width, render.height);// Timeconst h = String(now.getHours()).padStart(2, "0");const m = String(now.getMinutes()).padStart(2, "0");const timeStr = `${h}:${m}`;let width = render.getTextWidth(timeStr, timeFont);render.drawText(timeStr, timeFont, white,(render.width - width) / 2,(render.height / 2) - timeFont.height);// Day of weekconst dayStr = DAYS[now.getDay()];width = render.getTextWidth(dayStr, dateFont);render.drawText(dayStr, dateFont, gray,(render.width - width) / 2,(render.height / 2) + 10);// Batteryconst batteryStr = `${batteryPercent}%`;width = render.getTextWidth(batteryStr, dateFont);render.drawText(batteryStr, dateFont, gray,(render.width - width) / 2,render.height - dateFont.height - 10);render.end();}watch.addEventListener("minutechange", draw);
```

## Examples

The [Pebble Examples](https://github.com/Moddable-OpenSource/pebble-examples)repository includes watchface examples:

- [`hellowatchface`](https://github.com/Moddable-OpenSource/pebble-examples/tree/main/hellowatchface) - simple digital watchface using Poco
- [`piu/watchfaces/cupertino`](https://github.com/Moddable-OpenSource/pebble-examples/tree/main/piu/watchfaces/cupertino) - classic macOS cursor clock
- [`piu/watchfaces/london`](https://github.com/Moddable-OpenSource/pebble-examples/tree/main/piu/watchfaces/london) - Big Ben-inspired analog watchface
- [`piu/watchfaces/helsinki`](https://github.com/Moddable-OpenSource/pebble-examples/tree/main/piu/watchfaces/helsinki) - Nokia style digital watchface
- [`piu/watchfaces/redmond`](https://github.com/Moddable-OpenSource/pebble-examples/tree/main/piu/watchfaces/redmond) - classic Windows clock
- [`piu/watchfaces/zurich`](https://github.com/Moddable-OpenSource/pebble-examples/tree/main/piu/watchfaces/zurich) - Swiss train station clock
