# Conserving Battery Life

Source: https://developer.repebble.com/guides/best-practices/conserving-battery-life/

One of Pebble's strengths is its long battery life. This is due in part to using a low-power display technology, conservative use of the backlight, and allowing the processor to sleep whenever possible. It therefore follows that apps which misuse high-power APIs or prevent power-saving mechanisms from working will detract from the user's battery life. Several common causes of battery drain in apps are discussed in this guide, alongside suggestions to help avoid them.

## Time Awake

Because the watch tries to sleep as much as possible to conserve power, any app that keeps the watch awake will incur significant a battery penalty. Examples of such apps include those that frequently use animations, sensors, Bluetooth communications, and vibrations.

### Animations and Display Updates

A common cause of such a drain are long-running animations that cause frequent display updates. For example, a watchface that plays a half-second [`Animation`](/docs/c/User_Interface/Animation/ "Animation")for every second that ticks by will drain the battery faster than one that does so only once per minute. The latter approach will allow a lot more time for the watch to sleep.

```
static void tick\_handler(struct tm \*tick\_time, TimeUnits changed) {// Update timeset\_time\_digits(tick\_time);// Only update once a minuteif(tick\_time-\>tm\_sec == 0) {play\_animation();}}
```

This also applies to apps that make use of short-interval [`Timer`](/docs/c/Foundation/Timer/ "Timer")s, which is another method of creating animations. Consider giving users the option to reduce or disable animations to further conserve power, as well as removing or shortening animations that are not essential to the app's function or aesthetic.

However, not all animations are bad. Efficient use of the battery can be maintained if the animations are played at more intelligent times. For example, when the user is holding their arm to view the screen (see[`pebble_glancing_demo`](https://github.com/pebble-hacks/pebble_glancing_demo)) or only when a tap or wrist shake is detected:

```
static void accel\_tap\_handler(AccelAxisType axis, int32\_t direction) {// Animate when the user flicks their wristplay\_animation();}
```

```
accel\_tap\_service\_subscribe(tap\_handler);
```

### Tick Updates

Many watchfaces unecessarily tick once a second by using the [`SECOND_UNIT`](/docs/c/Foundation/Event_Service/TickTimerService/#SECOND_UNIT "SECOND\_UNIT")constant value with the [`TickTimerService`](/docs/c/Foundation/Event_Service/TickTimerService/ "TickTimerService"), when they only update the display once a minute. By using the [`MINUTE_UNIT`](/docs/c/Foundation/Event_Service/TickTimerService/#MINUTE_UNIT "MINUTE\_UNIT") instead, the amount of times the watch is woken up per minute is reduced.

```
// Only tick once a minute, much more time asleeptick\_timer\_service\_subscribe(MINUTE\_UNIT, tick\_handler);
```

If possible, give users the choice to disable the second hand tick and/or animation to further save power. Extremely minimal watchfaces may also use the[`HOUR_UNIT`](/docs/c/Foundation/Event_Service/TickTimerService/#HOUR_UNIT "HOUR\_UNIT") value to only be updated once per hour.

This factor is especially important for Pebble Time Round users. On this platform the reduced battery capacity means that a watchface with animations that play every second could reduce this to one day or less. Consider offering configuration options to reducing tick updates on this platform to save power where it at a premium.

### Sensor Usage

Apps that make frequent usage of Pebble's onboard accelerometer and compass sensors will also prevent the watch from going to sleep and consume more battery power. The [`AccelerometerService`](/docs/c/Foundation/Event_Service/AccelerometerService/ "AccelerometerService") API features the ability to configure the sampling rate and number of samples received per update, allowing batching of data into less frequent updates. By receiving updates less frequently, the battery will last longer.

```
// Batch samples into sets of 10 per callbackconst uint32\_t num\_samples = 10;// Sample at 10 Hzaccel\_service\_set\_sampling\_rate(ACCEL\_SAMPLING\_10HZ);// With this combination, only wake up the app once per second!accel\_data\_service\_subscribe(num\_samples, accel\_data\_handler);
```

Similarly, the [`CompassService`](/docs/c/Foundation/Event_Service/CompassService/ "CompassService") API allows a filter to be set on the heading updates, allowing an app to only be notified per every 45 degree angle change, for example.

```
// Only update if the heading changes significantlycompass\_service\_set\_heading\_filter(TRIG\_MAX\_ANGLE / 36);
```

In addition, making frequent use of the [`Dictation`](/docs/c/Foundation/Dictation/ "Dictation") API will also keep the watch awake, and also incur a penalty for keeping the Bluetooth connection alive. Consider using the [`Storage`](/docs/c/Foundation/Storage/ "Storage") API to remember previous user input and instead present a list of previous inputs if appropriate to reduce usage of this API.

```
static void dictation\_session\_callback(DictationSession \*session, DictationSessionStatus status,char \*transcription, void \*context) {if(status == DictationSessionStatusSuccess) {// Display the dictated textsnprintf(s\_last\_text, sizeof(s\_last\_text), "Transcription:\n\n%s",transcription);text\_layer\_set\_text(s\_output\_layer, s\_last\_text);// Save for later!const int last\_text\_key = 0;persist\_write\_string(last\_text\_key, s\_last\_text);}}
```

### Bluetooth Usage

Hinted at above, frequent use of the [`AppMessage`](/docs/c/Foundation/AppMessage/ "AppMessage") API to send and recieve data will cause the Bluetooth connection to enter a more responsive state, which consumes much more power. A small time after a message is sent, the connection will return back to a low-power state.

The 'sniff interval' determines how often the API checks for new messages from the phone, and should be let in the default [`SNIFF_INTERVAL_NORMAL`](/docs/c/Foundation/App_Communication/#SNIFF_INTERVAL_NORMAL "SNIFF\_INTERVAL\_NORMAL") state as much as possible. Consider how infrequent communication activities can be to save power and maintain functionality, and how data obtained over the Bluetooth connection can be cached using the [`Storage`](/docs/c/Foundation/Storage/ "Storage") API to reduce the frequency of updates (for example, weather information in watchface).

If the reduced sniff state must be used to transfer large amounts of data quickly, be sure to return to the low-power state as soon as the transfer is complete:

```
// Return to low power Bluetooth stateapp\_comm\_set\_sniff\_interval(SNIFF\_INTERVAL\_NORMAL);
```

## Backlight Usage

The backlight LED is another large consumer of battery power. System-level backlight settings may see the backlight turn on for a few seconds every time a button is pressed. While this setting is out of the hands of developers, apps can work to reduce the backlight on-time by minimizing the number of button presses required to operate them. For example, use an [`ActionBarLayer`](/docs/c/User_Interface/Layers/ActionBarLayer/ "ActionBarLayer") to execute common actions with one button press instead of a long scrolling[`MenuLayer`](/docs/c/User_Interface/Layers/MenuLayer/ "MenuLayer").

While the [`Light`](/docs/c/User_Interface/Light/ "Light") API is available to manually turn the backlight on, it should not be used for more than very short periods, if at all. Apps that keep the backlight on all the time will not last more than a few hours. If the backlight must be kept on for an extended period, make sure to return to the automatic mode as soon as possible:

```
// Return to automatic backlight controllight\_enable(false);
```

## Vibration Motor Usage

As a physical converter of electrical to mechanical energy, the vibration motor also consumes a lot of power. Users can elect to use Quiet Time or turn off vibration for notifications to save power, but apps can also contribute to this effort. Try and keep the use of the [`Vibes`](/docs/c/User_Interface/Vibes/ "Vibes") API to a minimum and giving user the option to disable any vibrations the app emits. Another method to reduce vibrator power consumtion is to shorten the length of any custom sequences used.

## Learn More

To learn more about power consumtion on Pebble and how battery life can be extended through app design choices, watch the presentation below given at the 2014 Developer Retreat.
