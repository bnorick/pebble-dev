# Pebble Timeline Api Ruby

Source: https://developer.repebble.com/community/libraries/pebble-timeline-api-ruby/

A Ruby wrapper for the Pebble Timeline API

This is currently a work in progress and contributions are welcome. It currently offers the ability to push/delete/update shared pins or user pins.

## Installation

Add this line to your application's Gemfile:

```
gem 'pebble\_timeline'
```

And then execute:

```
$ bundle
```

Or install it yourself as:

```
$ gem install pebble_timeline
```

## Usage

```
require 'pebble\_timeline'api = PebbleTimeline::API.new(ENV['PEBBLE\_TIMELINE\_API\_KEY'])# Shared pinspins = PebbleTimeline::Pins.new(api)pins.create(id: "test-1", topics: 'test', time: "2015-06-10T08:01:10.229Z", layout: { type: 'genericPin', title: 'test 1' })pins.delete("test-1")# User pinsuser\_pins = PebbleTimeline::Pins.new(api, 'user', USER\_TOKEN)user\_pins.create(id: "test-1", time: "2015-06-12T16:42:00Z", layout: { type: 'genericPin', title: 'test 1' })user\_pins.delete("test-1")
```
