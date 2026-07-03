# Events and Services

Source: https://developer.repebble.com/guides/events-and-services/

All Pebble watches contain a collection of sensors than can be used as input devices for apps. Available sensors include four buttons, an accelerometer, and a magnetometer (accessible via the [`CompassService`](/docs/c/Foundation/Event_Service/CompassService/ "CompassService") API). In addition, the Basalt and Chalk platforms also include a microphone (accessible via the[`Dictation`](/docs/c/Foundation/Dictation/ "Dictation") API) and access to Pebble Health data sets. Read [_Hardware Information_](/guides/tools-and-resources/hardware-information.md) for more information on sensor availability per platform.

While providing more interactivity, excessive regular use of these sensors will stop the watch's CPU from sleeping and result in faster battery drain, so use them sparingly. An alternative to constantly reading accelerometer data is to obtain data in batches, allowing sleeping periods in between. Read [_Conserving Battery Life_](/guides/best-practices/conserving-battery-life.md) for more information.

## Contents

- [**Accelerometer**](/guides/events-and-services/accelerometer.md) - How to use data and simple tap gestures from the onboard accelerometer.

- [**Background Worker**](/guides/events-and-services/background-worker.md) - Using the Background Worker to do work in the background, such as activity tracking.

- [**Backlight**](/guides/events-and-services/light.md) - How to trigger the backlight, force it on, and - on hardware with an RGB backlight - tint it.

- [**Buttons**](/guides/events-and-services/buttons.md) - How to react to button presses in your app.

- [**Compass**](/guides/events-and-services/compass.md) - How to use data from the Compass API to determine direction.

- [**Dictation**](/guides/events-and-services/dictation.md) - How to use the Dictation API to get voice-to-text input in watchapps.

- [**Event Services**](/guides/events-and-services/events.md) - How to use the various asynchronous event services to power app features.

- [**Heart Rate Monitor**](/guides/events-and-services/hrm.md) - Information on using the HealthService API to obtain information from the Heart Rate Monitor.

- [**Pebble Health**](/guides/events-and-services/health.md) - Information on using the HealthService API to incorporate multiple types of health data into your apps.

- [**Persistent Storage**](/guides/events-and-services/persistent-storage.md) - Using persistent storage to improve your app's UX.

- [**Speaker**](/guides/events-and-services/speaker.md) - How to play tones, melodies, polyphonic tracks, and PCM streams through the speaker.

- [**Touch**](/guides/events-and-services/touch.md) - How to subscribe to touch events on platforms with a touchscreen.

- [**Wakeups**](/guides/events-and-services/wakeups.md) - Using the Wakeup API to launch an app at some future time.
