# Multi Timer

Source: https://developer.repebble.com/community/apps/multi-timer/

Multi Timer is a Pebble watchapp that allows you to run several timers and stopwatches simultaneously.

It uses [`Persistent Storage`](/docs/c/Foundation/Storage/ "Storage") on the watch to remember your timers, and even fakes the timers running in the background by calculating how much time has elapsed since the app was last run and adding / removing this amount of time from any running timers.

Some parts of the C and JS code are tested, and are run automatically using[Travis CI](https://travis-ci.org/).

The current build status of the app is: [![Build Status](https://travis-ci.org/smallstoneapps/multi-timer.png?branch=master)](https://travis-ci.org/smallstoneapps/multi-timer/)

Here is what the app looks like:

![Multi Timer Screenshot #1](https://raw.githubusercontent.com/smallstoneapps/multi-timer/master/marketing/screenshots/2.7/multi-timer_2-7_01.png)
