# Pypebbleapi

Source: https://developer.repebble.com/community/libraries/pypebbleapi/

Python library to interact with the Pebble Timeline APIs. It supports Python 2.7, 3.3 and 3.4.

This is basically a port of the [pebble-api](https://www.npmjs.com/package/pebble-api) library for NodeJS.

## Installation

Just use `pip`:

```
pip install pypebbleapi
```

## Usage

This snippet shows the basic usage:

```
from pypebbleapi importTimeline,Pinimport datetimetimeline=Timeline(my\_api\_key)my\_pin=Pin(id='123',datetime.date.today().isoformat())timeline.send\_shared\_pin(['a\_topic','another\_topic'],my\_pin)
```
