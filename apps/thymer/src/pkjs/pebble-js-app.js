const Clay = require("@rebble/clay");
const buildClayConfig = require("./config");
const clayTextarea = require("./clay-textarea");
const { MAX_TIMERS, parseTimerToml } = require("./timer-config");

const STORAGE_KEY = "thymer.toml.v1";
const STORAGE_KEY_ICONS_ENABLED = "thymer.ui.icons-enabled.v1";
const STORAGE_KEY_BACKGROUND_ENABLED = "thymer.ui.background-enabled.v1";
const STORAGE_KEY_TIMER_ACCENT_ENABLED = "thymer.ui.timer-accent-enabled.v1";

const KEY_REQUEST_CONFIG = 10000;
const KEY_CFG_OP = 10001;
const KEY_CFG_TIMER = 10002;
const KEY_CFG_SEGMENT = 10003;
const KEY_CFG_FLAGS = 10004;
const KEY_CFG_ITER = 10005;
const KEY_CFG_TRIGGER_KIND = 10006;
const KEY_CFG_TRIGGER_FROM = 10007;
const KEY_CFG_TRIGGER_TO = 10008;
const KEY_CFG_DURATION = 10009;
const KEY_CFG_TEXT = 10010;
const KEY_CFG_ALERT = 10011;
const KEY_CFG_INTENSITY = 10012;
const KEY_CFG_DELAY = 10013;
const KEY_CFG_REPEAT_PATTERN_DELAY = 10014;
const KEY_CFG_ERROR = 10015;
const KEY_CFG_UP_ACTION = 10016;
const KEY_CFG_UP_LONG_ACTION = 10017;
const KEY_CFG_UI_FLAGS = 10018;
const KEY_CFG_ACK_DURATION = 10019;
const KEY_CFG_HINT = 10020;
const KEY_CFG_UP_ACTION_TIME = 10021;
const KEY_CFG_UP_LONG_ACTION_TIME = 10022;
const KEY_CFG_SELECT_LONG_ACTION = 10023;
const KEY_CFG_SELECT_LONG_ACTION_TIME = 10024;
const KEY_CFG_WARN = 10025;
const KEY_CFG_WARN_TIME = 10026;

const CFG_OP_BEGIN = 1;
const CFG_OP_TIMER = 2;
const CFG_OP_SEGMENT = 3;
const CFG_OP_VIBRATE = 4;
const CFG_OP_COMMIT = 5;
const CFG_OP_ERROR = 6;
const CFG_OP_UI = 7;
const CFG_OP_WARN = 8;

const FINISH_VIBE_SEGMENT = 255;
const CONFIG_FLAG_ICONS = 0x1;
const CONFIG_FLAG_BACKGROUND = 0x2;
const CONFIG_FLAG_TIMER_ACCENT = 0x4;

function loadToml() {
  return localStorage.getItem(STORAGE_KEY) || "";
}

function saveToml(toml) {
  localStorage.setItem(STORAGE_KEY, toml);
}

function loadBoolean(key, fallback) {
  const value = localStorage.getItem(key);
  if (value === null) {
    return fallback;
  }
  return value !== "false";
}

function saveBoolean(key, value) {
  localStorage.setItem(key, value ? "true" : "false");
}

function loadUiSettings() {
  return {
    iconsEnabled: loadBoolean(STORAGE_KEY_ICONS_ENABLED, true),
    backgroundEnabled: loadBoolean(STORAGE_KEY_BACKGROUND_ENABLED, true),
    timerAccentEnabled: loadBoolean(STORAGE_KEY_TIMER_ACCENT_ENABLED, true),
  };
}

function saveUiSettings(settings) {
  saveBoolean(STORAGE_KEY_ICONS_ENABLED, settings.iconsEnabled);
  saveBoolean(STORAGE_KEY_BACKGROUND_ENABLED, settings.backgroundEnabled);
  saveBoolean(STORAGE_KEY_TIMER_ACCENT_ENABLED, settings.timerAccentEnabled);
}

function uiSettingsEqual(left, right) {
  return !!left && !!right &&
    left.iconsEnabled === right.iconsEnabled &&
    left.backgroundEnabled === right.backgroundEnabled &&
    left.timerAccentEnabled === right.timerAccentEnabled;
}

function uiFlagsFromSettings(uiSettings) {
  let uiFlags = uiSettings.iconsEnabled ? CONFIG_FLAG_ICONS : 0;
  if (uiSettings.backgroundEnabled) {
    uiFlags |= CONFIG_FLAG_BACKGROUND;
  }
  if (uiSettings.timerAccentEnabled) {
    uiFlags |= CONFIG_FLAG_TIMER_ACCENT;
  }
  return uiFlags;
}

const clay = new Clay(buildClayConfig({
  toml: loadToml(),
  iconsEnabled: loadBoolean(STORAGE_KEY_ICONS_ENABLED, true),
  backgroundEnabled: loadBoolean(STORAGE_KEY_BACKGROUND_ENABLED, true),
  timerAccentEnabled: loadBoolean(STORAGE_KEY_TIMER_ACCENT_ENABLED, true),
}), null, { autoHandleEvents: false });
clay.registerComponent(clayTextarea);

function encodeUint64Bytes(value) {
  if (typeof value !== "number" || !Number.isSafeInteger(value) || value < 0) {
    throw new Error(`uint64 value out of range: ${value}`);
  }
  const bytes = new Array(8);
  let remaining = value;
  for (let i = 0; i < 8; i++) {
    bytes[i] = remaining % 256;
    remaining = Math.floor(remaining / 256);
  }
  return bytes;
}

function sendMessage(payload, onSuccess, onFailure) {
  Pebble.sendAppMessage(payload, onSuccess || function() {}, onFailure || function() {});
}

function sendConfig(config) {
  const timers = config.timers;
  if (timers.length > MAX_TIMERS) {
    throw new Error(
      `config defines ${timers.length} timers but Thymer supports at most ${MAX_TIMERS}`
    );
  }
  const uiSettings = loadUiSettings();
  const uiFlags = uiFlagsFromSettings(uiSettings);
  const payload = {};
  payload[KEY_CFG_OP] = CFG_OP_BEGIN;
  payload[KEY_CFG_TIMER] = timers.length;
  payload[KEY_CFG_UI_FLAGS] = uiFlags;
  sendMessage(payload, function() {
    sendTimerAt(timers, 0);
  });
}

function sendUiConfig(uiSettings) {
  const payload = {};
  payload[KEY_CFG_OP] = CFG_OP_UI;
  payload[KEY_CFG_UI_FLAGS] = uiFlagsFromSettings(uiSettings);
  sendMessage(payload);
}

function sendTimerAt(timers, timerIndex) {
  if (timerIndex >= timers.length) {
    const payload = {};
    payload[KEY_CFG_OP] = CFG_OP_COMMIT;
    sendMessage(payload);
    return;
  }

  const timer = timers[timerIndex];
  const flags = (timer.repeat ? 1 : 0) |
    (timer.iterationsEnabled ? 2 : 0) |
    (timer.mustAcknowledge ? 4 : 0) |
    (timer.stopwatch ? 8 : 0) |
    (timer.stopwatchOnly ? 16 : 0);
  const payload = {};
  payload[KEY_CFG_OP] = CFG_OP_TIMER;
  payload[KEY_CFG_TIMER] = timerIndex;
  payload[KEY_CFG_SEGMENT] = timer.pattern.length;
  payload[KEY_CFG_FLAGS] = flags;
  payload[KEY_CFG_ITER] = timer.iterations;
  payload[KEY_CFG_TRIGGER_KIND] = timer.trigger.kind;
  payload[KEY_CFG_TRIGGER_FROM] = timer.trigger.from;
  payload[KEY_CFG_TRIGGER_TO] = timer.trigger.to;
  payload[KEY_CFG_ALERT] = timer.finishVibrate.length;
  payload[KEY_CFG_REPEAT_PATTERN_DELAY] = timer.repeatPatternDelay;
  payload[KEY_CFG_ACK_DURATION] = timer.acknowledgeAlertDuration;
  payload[KEY_CFG_UP_ACTION] = timer.onPressUp.kind;
  payload[KEY_CFG_UP_LONG_ACTION] = timer.onLongPressUp.kind;
  payload[KEY_CFG_SELECT_LONG_ACTION] = timer.onLongPressSelect.kind;
  payload[KEY_CFG_UP_ACTION_TIME] = encodeUint64Bytes(timer.onPressUp.durationMs);
  payload[KEY_CFG_UP_LONG_ACTION_TIME] = encodeUint64Bytes(timer.onLongPressUp.durationMs);
  payload[KEY_CFG_SELECT_LONG_ACTION_TIME] = encodeUint64Bytes(timer.onLongPressSelect.durationMs);
  payload[KEY_CFG_TEXT] = timer.name;
  sendMessage(payload, function() {
    sendSegmentAt(timers, timerIndex, 0);
  });
}

function sendSegmentAt(timers, timerIndex, segmentIndex) {
  const timer = timers[timerIndex];
  if (segmentIndex >= timer.pattern.length) {
    sendFinishVibrateAt(timers, timerIndex, 0);
    return;
  }

  const segment = timer.pattern[segmentIndex];
  const payload = {};
  payload[KEY_CFG_OP] = CFG_OP_SEGMENT;
  payload[KEY_CFG_TIMER] = timerIndex;
  payload[KEY_CFG_SEGMENT] = segmentIndex;
  payload[KEY_CFG_DURATION] = encodeUint64Bytes(segment.durationMs);
  payload[KEY_CFG_TEXT] = segment.name;
  payload[KEY_CFG_HINT] = segment.hint;
  payload[KEY_CFG_ALERT] = segment.vibrate.length;
  payload[KEY_CFG_WARN] = segment.warnAt.length;
  sendMessage(payload, function() {
    sendWarnAt(timers, timerIndex, segmentIndex, 0);
  });
}

function sendWarnAt(timers, timerIndex, segmentIndex, warnIndex) {
  const segment = timers[timerIndex].pattern[segmentIndex];
  if (warnIndex >= segment.warnAt.length) {
    sendVibrateAt(timers, timerIndex, segmentIndex, 0);
    return;
  }

  const warnAt = segment.warnAt[warnIndex];
  const payload = {};
  payload[KEY_CFG_OP] = CFG_OP_WARN;
  payload[KEY_CFG_TIMER] = timerIndex;
  payload[KEY_CFG_SEGMENT] = segmentIndex;
  payload[KEY_CFG_WARN] = warnIndex;
  payload[KEY_CFG_WARN_TIME] = encodeUint64Bytes(warnAt.timeBeforeEndMs);
  payload[KEY_CFG_ALERT] = warnAt.vibrate.length;
  sendMessage(payload, function() {
    sendWarnVibrateAt(timers, timerIndex, segmentIndex, warnIndex, 0);
  });
}

function sendWarnVibrateAt(timers, timerIndex, segmentIndex, warnIndex, vibeIndex) {
  const warnAt = timers[timerIndex].pattern[segmentIndex].warnAt[warnIndex];
  if (vibeIndex >= warnAt.vibrate.length) {
    sendWarnAt(timers, timerIndex, segmentIndex, warnIndex + 1);
    return;
  }

  const vibe = warnAt.vibrate[vibeIndex];
  const payload = {};
  payload[KEY_CFG_OP] = CFG_OP_VIBRATE;
  payload[KEY_CFG_TIMER] = timerIndex;
  payload[KEY_CFG_SEGMENT] = segmentIndex;
  payload[KEY_CFG_WARN] = warnIndex;
  payload[KEY_CFG_ALERT] = vibeIndex;
  payload[KEY_CFG_INTENSITY] = vibe.intensity;
  payload[KEY_CFG_DURATION] = vibe.duration;
  payload[KEY_CFG_DELAY] = vibe.delay;
  sendMessage(payload, function() {
    sendWarnVibrateAt(timers, timerIndex, segmentIndex, warnIndex, vibeIndex + 1);
  });
}

function sendFinishVibrateAt(timers, timerIndex, vibeIndex) {
  const timer = timers[timerIndex];
  if (vibeIndex >= timer.finishVibrate.length) {
    sendTimerAt(timers, timerIndex + 1);
    return;
  }

  const vibe = timer.finishVibrate[vibeIndex];
  const payload = {};
  payload[KEY_CFG_OP] = CFG_OP_VIBRATE;
  payload[KEY_CFG_TIMER] = timerIndex;
  payload[KEY_CFG_SEGMENT] = FINISH_VIBE_SEGMENT;
  payload[KEY_CFG_ALERT] = vibeIndex;
  payload[KEY_CFG_INTENSITY] = vibe.intensity;
  payload[KEY_CFG_DURATION] = vibe.duration;
  payload[KEY_CFG_DELAY] = vibe.delay;
  sendMessage(payload, function() {
    sendFinishVibrateAt(timers, timerIndex, vibeIndex + 1);
  });
}

function sendVibrateAt(timers, timerIndex, segmentIndex, vibeIndex) {
  const segment = timers[timerIndex].pattern[segmentIndex];
  if (vibeIndex >= segment.vibrate.length) {
    sendSegmentAt(timers, timerIndex, segmentIndex + 1);
    return;
  }

  const vibe = segment.vibrate[vibeIndex];
  const payload = {};
  payload[KEY_CFG_OP] = CFG_OP_VIBRATE;
  payload[KEY_CFG_TIMER] = timerIndex;
  payload[KEY_CFG_SEGMENT] = segmentIndex;
  payload[KEY_CFG_ALERT] = vibeIndex;
  payload[KEY_CFG_INTENSITY] = vibe.intensity;
  payload[KEY_CFG_DURATION] = vibe.duration;
  payload[KEY_CFG_DELAY] = vibe.delay;
  sendMessage(payload, function() {
    sendVibrateAt(timers, timerIndex, segmentIndex, vibeIndex + 1);
  });
}

function sendConfigError(message) {
  const payload = {};
  payload[KEY_CFG_OP] = CFG_OP_ERROR;
  payload[KEY_CFG_ERROR] = String(message);
  sendMessage(payload);
}

function sendStoredConfig() {
  const toml = loadToml().trim();
  if (!toml) {
    return;
  }
  try {
    sendConfig(parseTimerToml(toml));
  } catch (error) {
    sendConfigError(error.message || String(error));
  }
}

function syncClaySettings() {
  const uiSettings = loadUiSettings();
  clay.setSettings({
    IconsEnabled: uiSettings.iconsEnabled,
    BackgroundEnabled: uiSettings.backgroundEnabled,
    TimerAccentEnabled: uiSettings.timerAccentEnabled,
    TomlConfig: loadToml(),
  });
}

Pebble.addEventListener("ready", function() {
  sendStoredConfig();
});

Pebble.addEventListener("showConfiguration", function() {
  syncClaySettings();
  Pebble.openURL(clay.generateUrl());
});

Pebble.addEventListener("webviewclosed", function(event) {
  if (!event.response) {
    return;
  }
  try {
    const response = clay.getSettings(event.response, false);
    const toml = String((response.TomlConfig && response.TomlConfig.value) || "").trim();
    const previousToml = loadToml().trim();
    const previousUiSettings = loadUiSettings();
    const uiSettings = {
      iconsEnabled: !response.IconsEnabled || !!response.IconsEnabled.value,
      backgroundEnabled: !response.BackgroundEnabled || !!response.BackgroundEnabled.value,
      timerAccentEnabled: !response.TimerAccentEnabled || !!response.TimerAccentEnabled.value,
    };
    const tomlChanged = toml !== previousToml;
    const uiChanged = !uiSettingsEqual(previousUiSettings, uiSettings);
    if (!tomlChanged && !uiChanged) {
      return;
    }
    saveUiSettings(uiSettings);
    if (!tomlChanged) {
      sendUiConfig(uiSettings);
      return;
    }
    saveToml(toml);
    sendConfig(parseTimerToml(toml));
  } catch (error) {
    Pebble.showSimpleNotificationOnPebble("Thymer config", error.message || String(error));
    sendConfigError(error.message || String(error));
  }
});

Pebble.addEventListener("appmessage", function(event) {
  if (event && event.payload && event.payload[String(KEY_REQUEST_CONFIG)]) {
    sendStoredConfig();
  }
});
