const test = require("node:test");
const assert = require("node:assert/strict");
const fs = require("node:fs");

const { parseTimerToml } = require("../src/pkjs/timer-config");

test("parses the shipped full example config", function() {
  const toml = fs.readFileSync("examples/full-config.toml", "utf8");
  const config = parseTimerToml(toml);

  assert.equal(config.timers.length > 0, true);
});

test("parses a single-segment timer using timer-level time", function() {
  const config = parseTimerToml([
    "[timers.focus]",
    'trigger = { tap = "top" }',
    'time = "00:15:00"',
    'warn-at = "00:01:00"',
  ].join("\n"));

  assert.equal(config.timers.length, 1);
  assert.equal(config.timers[0].pattern.length, 1);
  assert.equal(config.timers[0].pattern[0].durationMs, 15 * 60 * 1000);
  assert.equal(config.timers[0].pattern[0].warnAt.length, 1);
});

test("parses a true stopwatch without pattern or time", function() {
  const config = parseTimerToml([
    "[timers.stopwatch]",
    'trigger = { tap = "center" }',
    "stopwatch = true",
  ].join("\n"));

  assert.equal(config.timers.length, 1);
  assert.equal(config.timers[0].stopwatch, true);
  assert.equal(config.timers[0].stopwatchOnly, true);
  assert.equal(config.timers[0].pattern.length, 1);
  assert.equal(config.timers[0].pattern[0].durationMs, Number.MAX_SAFE_INTEGER);
});

test("rejects invalid true stopwatch combinations", function() {
  assert.throws(function() {
    parseTimerToml([
      "[timers.stopwatch]",
      'trigger = { tap = "center" }',
      "stopwatch = true",
      'on-finished = { vibrate = "mid" }',
    ].join("\n"));
  }, {
    message: "timer 1 [timers.stopwatch] true stopwatch cannot use on-finished",
  });
});

test("includes timer map key in timer-level time errors", function() {
  assert.throws(function() {
    parseTimerToml([
      "[timers.focus_block]",
      'trigger = { tap = "top" }',
      "time = 9007199254741",
    ].join("\n"));
  }, {
    message: "timer 1 [timers.focus_block] time out of range: 9007199254741",
  });
});

test("includes timer map key in warn-at errors", function() {
  assert.throws(function() {
    parseTimerToml([
      "[timers.focus]",
      'trigger = { tap = "top" }',
      'time = "00:01:00"',
      'warn-at = "00:01:00"',
    ].join("\n"));
  }, {
    message: "timer 1 [timers.focus] warn-at 1 must be less than the segment time",
  });
});
