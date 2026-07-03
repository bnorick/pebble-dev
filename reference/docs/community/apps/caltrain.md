# Caltrain

Source: https://developer.repebble.com/community/apps/caltrain/

Caltrain is a Pebble app that displays upcoming trains at a station, and where those trains will stop along the remainder of each of their routes.

It stores the schedule locally in [`resources`](/docs/c/Foundation/Resources/ "Resources"), and makes heavy use of[`resource_load_byte_range`](/docs/c/Foundation/Resources/#resource_load_byte_range "resource\_load\_byte\_range") to read in the required data without running out of RAM. This is wrapped in a block reading API for performance reasons; without that it takes several seconds to load each window.

It also uses [`Persistent Storage`](/docs/c/Foundation/Storage/ "Storage") to store the state of the UI, so it can be restored to the state in which you left it when you return to the app.

Finally, it uses PebbleKit JS to retrieve your location on launch. If it gets a response before you manually choose a station, it will automatically show the station closest to you.

The windows were built using [CloudPebble's UI Editor](/blog/2014/08/08/CloudPebble-Graphical-UI-Editor.md).

A python script is included to convert from the Caltrain GTFS data to the compressed format it uses.

Screenshots:

![](http://i.imgur.com/iGGxV9q.png) ![](http://i.imgur.com/RNeaSQ1.png) ![](http://i.imgur.com/23kD7ie.png) ![](http://i.imgur.com/mHFaUMy.png)
