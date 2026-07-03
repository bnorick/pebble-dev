# Libraries for Pushing Pins

Source: https://developer.repebble.com/guides/pebble-timeline/timeline-libraries/

This page contains libraries that are currently available to interact with the timeline. You can use these to build apps and services that push pins to your users.

## timeline.js

**JavaScript Code Snippet** - [Available on GitHub](https://gist.github.com/pebble-gists/6a4082ef12e625d23455)

**Install**

Copy into the `src/pkjs/` directory of your project, add `enableMultiJS: true` in`package.json`, then `require` and use in `index.js`.

**Example**

```
var timeline = require('./timeline');// Push a pin when the app startsPebble.addEventListener('ready', function() {// An hour aheadvar date = new Date();date.setHours(date.getHours() + 1);// Create the pinvar pin = {"id": "example-pin-0","time": date.toISOString(),"layout": {"type": "genericPin","title": "Example Pin","tinyIcon": "system://images/SCHEDULED\_EVENT"}};console.log('Inserting pin in the future: ' + JSON.stringify(pin));// Push the pintimeline.insertUserPin(pin, function(responseText) {console.log('Result: ' + responseText);});});
```

## pebble-api

**Node Module** - [Available on NPM](https://www.npmjs.com/package/pebble-api)

**Install**

```
npm install pebble-api --save
```

**Example**

```
var Timeline = require('pebble-api');var USER\_TOKEN = 'a70b23d3820e9ee640aeb590fdf03a56';var timeline = new Timeline();var pin = new Timeline.Pin({id: 'test-pin-5245',time: new Date(),duration: 10,layout: new Timeline.Pin.Layout({type: Timeline.Pin.LayoutType.GENERIC\_PIN,tinyIcon: Timeline.Pin.Icon.PIN,title: 'Pin Title'})});timeline.sendUserPin(USER\_TOKEN, pin, function (err) {if (err) {return console.error(err);}console.log('Pin sent successfully!');});
```

## PebbleTimeline API Ruby

**Ruby Gem** - [Available on RubyGems](https://rubygems.org/gems/pebble_timeline/versions/0.0.1)

**Install**

```
gem install pebble_timeline
```

**Example**

```
require 'pebble\_timeline'api = PebbleTimeline::API.new(ENV['PEBBLE\_TIMELINE\_API\_KEY'])# Shared pinspins = PebbleTimeline::Pins.new(api)pins.create(id: "test-1", topics: 'test', time: "2015-06-10T08:01:10.229Z", layout: { type: 'genericPin', title: 'test 1' })pins.delete("test-1")# User pinsuser\_pins = PebbleTimeline::Pins.new(api, 'user', USER\_TOKEN)user\_pins.create(id: "test-1", time: "2015-06-12T16:42:00Z", layout: { type: 'genericPin', title: 'test 1' })user\_pins.delete("test-1")
```

## pypebbleapi

**Python Library** - [Available on pip](https://pypi.python.org/pypi/pypebbleapi/0.0.1)

**Install**

```
pip install pypebbleapi
```

**Example**

```
from pypebbleapi importTimeline,Pinimport datetimetimeline=Timeline(my\_api\_key)my\_pin=Pin(id='123',datetime.date.today().isoformat())timeline.send\_shared\_pin(['a\_topic','another\_topic'],my\_pin)
```

## php-pebble-timeline

**PHPebbleTimeline** - [Available on Github](https://github.com/fletchto99/PHPebbleTimeline)

**Install**

Copy the TimelineAPI folder (from the above repository) to your project's directory and include the required files.

**Example**

```
//Include the timeline APIrequire\_once'TimelineAPI/Timeline.php';//Import the required classesuseTimelineAPI\Pin;useTimelineAPI\PinLayout;useTimelineAPI\PinLayoutType;useTimelineAPI\PinIcon;useTimelineAPI\PinReminder;useTimelineAPI\Timeline;//Create some layouts which our pin will use$reminderlayout=newPinLayout(PinLayoutType::GENERIC\_REMINDER,'Sample reminder!',null,null,null,PinIcon::NOTIFICATION\_FLAG);$pinlayout=newPinLayout(PinLayoutType::GENERIC\_PIN,'Our title',null,null,null,PinIcon::NOTIFICATION\_FLAG);//Create a reminder which our pin will push before the event$reminder=newPinReminder($reminderlayout,(newDateTime('now'))-\>add(newDateInterval('PT10M')));//Create the pin$pin=newPin('\<YOUR USER TOKEN HERE\>',(newDateTime('now'))-\>add(newDateInterval('PT5M')),$pinlayout);//Attach the reminder$pin-\>addReminder($reminder);//Push the pin to the timelineTimeline::pushPin('sample-userToken',$pin);
```

## PinPusher

**PHP Library** - [Available on Composer](https://packagist.org/packages/valorin/pinpusher)

**Install**

```
composer require valorin/pinpusher
```

**Example**

```
useValorin\PinPusher\Pusher;useValorin\PinPusher\Pin;$pin=newPin('example-pin-generic-1',newDateTime('2015-03-19T18:00:00Z'),newPin\Layout\Generic("News at 6 o'clock",Pin\Icon::NOTIFICATION\_FLAG));$pusher=newPusher()$pusher-\>pushToUser($userToken,$pin);
```

## pebble-api-dotnet

**PCL C# Library** - [Available on Github](https://github.com/nothingmn/pebble-api-dotnet)

**Install**

```
git clone git@github.com:nothingmn/pebble-api-dotnet.git
```

**Example**

In your C# project, define your global API Key.

```
public static string APIKey = "APIKEY";
```

Launch your app on the watch, and make the API call...

Now, on the server, you can use your "userToken" from the client app, and send pins as follows:

```
var timeline = new Timeline(APIKey);var result = await timeline.SendUserPin(userToken, new Pin(){Id = System.Guid.NewGuid().ToString(),Layout = new GenericLayout(){Title = "Generic Layout",Type = LayoutTypes.genericPin,SmallIcon = Icons.Notification.Flag},});
```

See more examples on the [GitHub repo](https://github.com/nothingmn/pebble-api-dotnet).
