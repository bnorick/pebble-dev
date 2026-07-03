# Php Pebble Timeline

Source: https://developer.repebble.com/community/libraries/php-pebble-timeline/

PHPebbleTimeline is a library for making use the Timeline API through PHP.

## Setup

Copy the TimelineAPI Folder to your project's directory and include the required files.

## Documentation

See [https://github.com/fletchto99/PHPebbleTimeline/blob/master/Readme.md](https://github.com/fletchto99/PHPebbleTimeline/blob/master/Readme.md) for indepth documentation regarding the API.

## Sample

```
//Include the timeline APIrequire\_once 'TimelineAPI/Timeline.php';//Import the required classesuse TimelineAPI\Pin;use TimelineAPI\PinLayout;use TimelineAPI\PinLayoutType;use TimelineAPI\PinIcon;use TimelineAPI\PinReminder;use TimelineAPI\Timeline;//Create some layouts which our pin will use$reminderlayout = new PinLayout(PinLayoutType::GENERIC\_REMINDER, 'Sample reminder!', null, null, null, PinIcon::NOTIFICATION\_FLAG);$pinlayout = new PinLayout(PinLayoutType::GENERIC\_PIN, 'Our title', null, null, null, PinIcon::NOTIFICATION\_FLAG);//Create a reminder which our pin will push before the event$reminder = new PinReminder($reminderlayout, (new DateTime('now')) -\> add(new DateInterval('PT10M')));//Create the pin$pin = new Pin('\<YOUR USER TOKEN HERE\>', (new DateTime('now')) -\> add(new DateInterval('PT5M')), $pinlayout);//Attach the reminder$pin -\> addReminder($reminder);//Push the pin to the timelineTimeline::pushPin('sample-userToken', $pin);
```
