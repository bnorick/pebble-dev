const Clay = require("@rebble/clay");
const buildClayConfig = require("./config");
const clayTextarea = require("./clay-textarea");

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

const CFG_OP_BEGIN = 1;
const CFG_OP_TIMER = 2;
const CFG_OP_SEGMENT = 3;
const CFG_OP_VIBRATE = 4;
const CFG_OP_COMMIT = 5;
const CFG_OP_ERROR = 6;

const TRIGGER_NONE = 0;
const TRIGGER_TAP = 1;
const TRIGGER_SWIPE = 2;

const ZONE_NONE = 0;
const ZONE_LEFT = 1;
const ZONE_TOP = 2;
const ZONE_RIGHT = 3;
const ZONE_BOTTOM = 4;
const ZONE_CENTER = 5;

const VIBE_LOW = 1;
const VIBE_MID = 2;
const VIBE_HIGH = 3;
const FINISH_VIBE_SEGMENT = 255;
const DEFAULT_PULSE_DELAY = 100;
const DEFAULT_REPEAT_PATTERN_DELAY = 500;
const DEFAULT_ACK_ALERT_DURATION = 12;
const DEFAULT_VIBRATION_LEVELS = {
  low: 75,
  mid: 100,
  high: 150,
};

const UP_ACTION_NONE = 0;
const UP_ACTION_SKIP = 1;
const UP_ACTION_HIDE = 2;
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

const clay = new Clay(buildClayConfig({
  toml: loadToml(),
  iconsEnabled: loadBoolean(STORAGE_KEY_ICONS_ENABLED, true),
  backgroundEnabled: loadBoolean(STORAGE_KEY_BACKGROUND_ENABLED, true),
  timerAccentEnabled: loadBoolean(STORAGE_KEY_TIMER_ACCENT_ENABLED, true),
}), null, { autoHandleEvents: false });
clay.registerComponent(clayTextarea);

function stripComments(line) {
  let result = "";
  let quote = null;
  for (let i = 0; i < line.length; i++) {
    const ch = line[i];
    if (quote) {
      if (ch === quote && line[i - 1] !== "\\") quote = null;
      result += ch;
      continue;
    }
    if (ch === '"' || ch === "'") {
      quote = ch;
      result += ch;
      continue;
    }
    if (ch === "#") break;
    result += ch;
  }
  return result.trim();
}

function splitTopLevel(text, delimiter) {
  const parts = [];
  let start = 0;
  let bracketDepth = 0;
  let braceDepth = 0;
  let quote = null;
  for (let i = 0; i < text.length; i++) {
    const ch = text[i];
    if (quote) {
      if (ch === quote && text[i - 1] !== "\\") quote = null;
      continue;
    }
    if (ch === '"' || ch === "'") {
      quote = ch;
      continue;
    }
    if (ch === "[") bracketDepth++;
    else if (ch === "]") bracketDepth--;
    else if (ch === "{") braceDepth++;
    else if (ch === "}") braceDepth--;
    else if (ch === delimiter && bracketDepth === 0 && braceDepth === 0) {
      parts.push(text.slice(start, i).trim());
      start = i + 1;
    }
  }
  parts.push(text.slice(start).trim());
  return parts.filter(Boolean);
}

function parseString(raw) {
  let result = "";
  for (let i = 1; i < raw.length - 1; i++) {
    const ch = raw[i];
    if (ch === "\\" && i + 1 < raw.length - 1) {
      const next = raw[++i];
      if (next === "n") result += "\n";
      else if (next === "t") result += "\t";
      else result += next;
    } else {
      result += ch;
    }
  }
  return result;
}

function parseValue(raw) {
  const value = raw.trim();
  if (!value) throw new Error("empty value");
  if ((value[0] === '"' && value[value.length - 1] === '"') ||
      (value[0] === "'" && value[value.length - 1] === "'")) {
    return parseString(value);
  }
  if (value === "true") return true;
  if (value === "false") return false;
  if (/^-?\d+$/.test(value)) return Number(value);
  if (value[0] === "[" && value[value.length - 1] === "]") {
    const inner = value.slice(1, -1).trim();
    if (!inner) return [];
    return splitTopLevel(inner, ",").map(parseValue);
  }
  if (value[0] === "{" && value[value.length - 1] === "}") {
    const inner = value.slice(1, -1).trim();
    const object = {};
    if (!inner) return object;
    for (const entry of splitTopLevel(inner, ",")) {
      const eq = entry.indexOf("=");
      if (eq < 0) throw new Error(`invalid inline table entry: ${entry}`);
      object[entry.slice(0, eq).trim()] = parseValue(entry.slice(eq + 1));
    }
    return object;
  }
  throw new Error(`unsupported value: ${value}`);
}

function parseAssignments(text) {
  const lines = text.split(/\r?\n/);
  const result = {};
  for (let i = 0; i < lines.length; i++) {
    const cleaned = stripComments(lines[i]);
    if (!cleaned) continue;
    const eq = cleaned.indexOf("=");
    if (eq < 0) throw new Error(`invalid line: ${cleaned}`);
    const key = cleaned.slice(0, eq).trim();
    let value = cleaned.slice(eq + 1).trim();

    let bracketDepth = (value.match(/\[/g) || []).length - (value.match(/\]/g) || []).length;
    let braceDepth = (value.match(/\{/g) || []).length - (value.match(/\}/g) || []).length;
    while (bracketDepth > 0 || braceDepth > 0) {
      i += 1;
      if (i >= lines.length) throw new Error(`unterminated value for ${key}`);
      const nextLine = stripComments(lines[i]);
      value += "\n" + nextLine;
      bracketDepth += (nextLine.match(/\[/g) || []).length - (nextLine.match(/\]/g) || []).length;
      braceDepth += (nextLine.match(/\{/g) || []).length - (nextLine.match(/\}/g) || []).length;
    }

    result[key] = parseValue(value);
  }
  return result;
}

function titleCaseKey(key) {
  return String(key)
    .replace(/[-_]+/g, " ")
    .replace(/\b[a-z]/g, function(match) { return match.toUpperCase(); });
}

function zoneId(value) {
  const normalized = String(value).trim().toLowerCase();
  switch (normalized) {
    case "left":
    case "l":
      return ZONE_LEFT;
    case "top":
    case "t":
      return ZONE_TOP;
    case "right":
    case "r":
      return ZONE_RIGHT;
    case "bottom":
    case "b":
      return ZONE_BOTTOM;
    case "center":
    case "c":
      return ZONE_CENTER;
    default:
      throw new Error(`invalid zone: ${value}`);
  }
}

function normalizeTrigger(trigger) {
  if (!trigger || typeof trigger !== "object") {
    throw new Error("trigger must be an inline table");
  }
  if (trigger.tap) {
    return {
      kind: TRIGGER_TAP,
      from: zoneId(trigger.tap),
      to: ZONE_NONE,
    };
  }
  if (trigger.swipe) {
    const swipe = String(trigger.swipe).trim().toLowerCase();
    const parts = swipe.split("-to-");
    if (parts.length !== 2) throw new Error(`invalid swipe: ${trigger.swipe}`);
    return {
      kind: TRIGGER_SWIPE,
      from: zoneId(parts[0]),
      to: zoneId(parts[1]),
    };
  }
  throw new Error("trigger must be { tap = ... } or { swipe = ... }");
}

function normalizeVibrationName(value) {
  const normalized = String(value || "mid").trim().toLowerCase();
  return normalized === "medium" ? "mid" : normalized;
}

function parseVibrationConfig(raw) {
  if (raw == null) {
    return {
      pulseDelay: DEFAULT_PULSE_DELAY,
      acknowledgeAlertDuration: DEFAULT_ACK_ALERT_DURATION,
      levels: Object.assign({}, DEFAULT_VIBRATION_LEVELS),
    };
  }
  if (!raw || typeof raw !== "object" || Array.isArray(raw)) {
    throw new Error("vibration must be a table");
  }

  const levels = Object.assign({}, DEFAULT_VIBRATION_LEVELS);
  let pulseDelay = DEFAULT_PULSE_DELAY;
  let acknowledgeAlertDuration = DEFAULT_ACK_ALERT_DURATION;
  for (const key of Object.keys(raw)) {
    if (key === "pulse-delay") {
      pulseDelay = Math.max(0, Number(raw[key]) | 0);
      continue;
    }
    if (key === "acknowledgement-alert-duration" ||
        key === "acknowledgment-alert-duration" ||
        key === "ack-alert-duration") {
      acknowledgeAlertDuration = normalizeAckAlertDuration(raw[key], 0);
      continue;
    }

    const normalizedKey = normalizeVibrationName(key);
    if (!/^[a-z][a-z0-9_-]*$/.test(normalizedKey)) {
      throw new Error(`invalid vibration key: ${key}`);
    }

    const duration = Math.max(0, Number(raw[key]) | 0);
    if (duration < 1) {
      throw new Error(`vibration ${key} must be at least 1`);
    }
    levels[normalizedKey] = duration;
  }

  return { pulseDelay, acknowledgeAlertDuration, levels };
}

function intensityDuration(value, vibrationConfig) {
  const normalized = normalizeVibrationName(value);
  const duration = vibrationConfig.levels[normalized];
  if (duration == null) {
    throw new Error(`invalid vibrate intensity: ${value}`);
  }
  return duration;
}

const MAX_DURATION_MS = Number.MAX_SAFE_INTEGER;
const MS_PER_SECOND = 1000;
const TEN_THOUSANDTHS_PER_SECOND = 10000;

function normalizeSegmentDurationMs(value) {
  if (value == null) {
    throw new Error("segment time is required");
  }
  if (typeof value === "number") {
    if (!Number.isFinite(value) || value < 0 || !Number.isSafeInteger(value)) {
      throw new Error(`invalid segment duration: ${value}`);
    }
    const totalMs = value * MS_PER_SECOND;
    if (!Number.isSafeInteger(totalMs) || totalMs < 1 || totalMs > MAX_DURATION_MS) {
      throw new Error(`segment duration out of range: ${value}`);
    }
    return totalMs;
  }

  const raw = String(value == null ? "" : value).trim();
  const match = /^(?:(\d+)-)?(\d{2}):(\d{2}):(\d{2})(?:\.(\d{1,4}))?$/.exec(raw);
  if (!match) {
    throw new Error(`invalid segment duration: ${value}`);
  }

  const days = Number(match[1] || 0);
  const hours = Number(match[2]);
  const minutes = Number(match[3]);
  const seconds = Number(match[4]);
  if (hours > 23 || minutes > 59 || seconds > 59) {
    throw new Error(`invalid segment duration: ${value}`);
  }

  let totalTenThousandths = days * 86400 * TEN_THOUSANDTHS_PER_SECOND;
  totalTenThousandths += hours * 3600 * TEN_THOUSANDTHS_PER_SECOND;
  totalTenThousandths += minutes * 60 * TEN_THOUSANDTHS_PER_SECOND;
  totalTenThousandths += seconds * TEN_THOUSANDTHS_PER_SECOND;
  if (match[5]) {
    totalTenThousandths += Number(match[5].padEnd(4, "0"));
  }

  if (!Number.isSafeInteger(totalTenThousandths)) {
    throw new Error(`segment duration out of range: ${value}`);
  }

  const totalMs = Math.floor((totalTenThousandths + 9) / 10);
  if (totalMs < 1 || totalMs > MAX_DURATION_MS) {
    throw new Error(`segment duration out of range: ${value}`);
  }
  return totalMs;
}

function normalizeRepeatPatternDelay(value, index) {
  if (value == null) {
    return DEFAULT_REPEAT_PATTERN_DELAY;
  }
  if (typeof value !== "number" || !Number.isFinite(value) || value < 0 || !Number.isSafeInteger(value)) {
    throw new Error(`timer ${index + 1} repeat-pattern-delay must be a non-negative integer`);
  }
  if (value > 65535) {
    throw new Error(`timer ${index + 1} repeat-pattern-delay out of range`);
  }
  return value;
}

function normalizeAckAlertDuration(value, index) {
  if (value == null) {
    return DEFAULT_ACK_ALERT_DURATION;
  }
  if (typeof value !== "number" || !Number.isFinite(value) || value < 0 || !Number.isSafeInteger(value)) {
    throw new Error(`${index >= 0 ? `timer ${index + 1}` : "vibration"} acknowledgement-alert-duration must be a non-negative integer`);
  }
  if (value > 65535) {
    throw new Error(`${index >= 0 ? `timer ${index + 1}` : "vibration"} acknowledgement-alert-duration out of range`);
  }
  return value;
}

function encodeUint64Bytes(value) {
  if (typeof value !== "number" || !Number.isSafeInteger(value) || value < 0 || value > MAX_DURATION_MS) {
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

function normalizeVibrateStep(raw, vibrationConfig) {
  if (typeof raw === "string") {
    return {
      intensity: VIBE_MID,
      duration: intensityDuration(raw, vibrationConfig),
      delay: vibrationConfig.pulseDelay,
    };
  }
  if (!raw || typeof raw !== "object" || Array.isArray(raw)) {
    throw new Error("vibrate step must be a string or inline table");
  }
  const hasIntensity = raw.intensity != null;
  const hasDuration = raw.duration != null;
  if (hasIntensity && hasDuration) {
    throw new Error("vibrate step may specify intensity or duration, not both");
  }
  return {
    intensity: VIBE_MID,
    duration: hasDuration
      ? Math.max(1, Number(raw.duration) | 0)
      : intensityDuration(raw.intensity || "mid", vibrationConfig),
    delay: Math.max(0, Number(raw.delay == null ? vibrationConfig.pulseDelay : raw.delay) | 0),
  };
}

function normalizeVibrate(raw, vibrationConfig) {
  if (raw == null) return [];
  if (typeof raw === "string" && raw.indexOf("-") >= 0) {
    return raw.split("-").map(function(part) {
      return normalizeVibrateStep(part.trim(), vibrationConfig);
    });
  }
  if (Array.isArray(raw)) {
    return raw.map(function(step) {
      return normalizeVibrateStep(step, vibrationConfig);
    });
  }
  return [normalizeVibrateStep(raw, vibrationConfig)];
}

function normalizeFinishVibrate(raw, index, vibrationConfig) {
  if (raw == null) {
    return [];
  }
  if (typeof raw === "object" && !Array.isArray(raw) && raw.vibrate != null) {
    return normalizeVibrate(raw.vibrate, vibrationConfig);
  }
  return normalizeVibrate(raw, vibrationConfig);
}

function normalizeUpAction(raw, fieldName, index) {
  if (raw == null) return UP_ACTION_NONE;
  if (typeof raw !== "string") {
    throw new Error(`timer ${index + 1} ${fieldName} must be \"skip\" or \"hide\"`);
  }
  switch (raw.trim().toLowerCase()) {
    case "skip":
      return UP_ACTION_SKIP;
    case "hide":
      return UP_ACTION_HIDE;
    default:
      throw new Error(`timer ${index + 1} ${fieldName} must be \"skip\" or \"hide\"`);
  }
}

function normalizeTimer(raw, index, fallbackName, vibrationConfig) {
  if (!Array.isArray(raw.pattern) || raw.pattern.length === 0) {
    throw new Error(`timer ${index + 1} is missing pattern`);
  }
  if (raw.iterations != null) {
    throw new Error(`timer ${index + 1} uses unsupported key: iterations`);
  }
  const rawRepeat = raw.repeat;
  const repeatForever = rawRepeat === true;
  const repeatCount = typeof rawRepeat === "number" ? Math.max(1, Number(rawRepeat) | 0) : 0;
  const repeat = repeatForever || repeatCount > 0;
  const finishVibrate = normalizeFinishVibrate(raw["on-finished"], index, vibrationConfig);
  const defaultVibrate = normalizeVibrate(raw.vibrate, vibrationConfig);
  if (repeatForever && finishVibrate.length > 0) {
    throw new Error(`timer ${index + 1} cannot use on-finished with repeat = true`);
  }
  if (raw["must-acknowledge"] != null && typeof raw["must-acknowledge"] !== "boolean") {
    throw new Error(`timer ${index + 1} must-acknowledge must be true or false`);
  }
  const ackAlertDurationFields = [
    "acknowledgement-alert-duration",
    "acknowledgment-alert-duration",
    "ack-alert-duration",
  ].filter(function(field) {
    return raw[field] != null;
  });
  if (ackAlertDurationFields.length > 1) {
    throw new Error(`timer ${index + 1} acknowledgement alert duration must only be set once`);
  }
  const onPressUp = normalizeUpAction(raw["on-press-up"], "on-press-up", index);
  const onLongPressUp = normalizeUpAction(raw["on-long-press-up"], "on-long-press-up", index);
  return {
    name: String(raw.name || fallbackName || `Timer ${index + 1}`),
    repeat: repeat,
    iterationsEnabled: repeatCount > 0,
    iterations: repeatCount,
    onPressUp: onPressUp,
    onLongPressUp: onLongPressUp,
    mustAcknowledge: raw["must-acknowledge"] === true,
    repeatPatternDelay: normalizeRepeatPatternDelay(raw["repeat-pattern-delay"], index),
    acknowledgeAlertDuration: normalizeAckAlertDuration(
      ackAlertDurationFields.length ? raw[ackAlertDurationFields[0]] : vibrationConfig.acknowledgeAlertDuration,
      index
    ),
    finishVibrate: finishVibrate,
    trigger: normalizeTrigger(raw.trigger),
    pattern: raw.pattern.map(function(segment, segmentIndex) {
      if (!segment || typeof segment !== "object") {
        throw new Error(`timer ${index + 1} pattern ${segmentIndex + 1} must be inline table`);
      }
      if (segment.description != null || segment.desc != null) {
        throw new Error(`timer ${index + 1} pattern ${segmentIndex + 1} uses unsupported key: description`);
      }
      return {
        name: String(segment.name || `step ${segmentIndex + 1}`),
        hint: segment.hint == null ? "" : String(segment.hint),
        durationMs: normalizeSegmentDurationMs(segment.time),
        vibrate: segment.vibrate != null
          ? normalizeVibrate(segment.vibrate, vibrationConfig)
          : defaultVibrate,
      };
    }),
  };
}

function formatZoneName(zone) {
  switch (zone) {
    case ZONE_LEFT: return "left";
    case ZONE_TOP: return "top";
    case ZONE_RIGHT: return "right";
    case ZONE_BOTTOM: return "bottom";
    case ZONE_CENTER: return "center";
    default: return "none";
  }
}

function hasMeaningfulLines(lines) {
  return lines.some(function(line) {
    return stripComments(line).length > 0;
  });
}

function parseTimerToml(toml) {
  const lines = toml.split(/\r?\n/);
  const rootLines = [];
  const namedSections = [];
  let vibrationSection = null;
  let current = null;

  for (const original of lines) {
    const trimmed = stripComments(original);
    const namedMatch = /^\[\s*timers\.([A-Za-z0-9_-]+)\s*\]$/.exec(trimmed);
    if (trimmed === "[vibration]") {
      current = { kind: "vibration", lines: [] };
      vibrationSection = current;
      continue;
    }
    if (namedMatch) {
      current = { kind: "named", name: namedMatch[1], lines: [] };
      namedSections.push(current);
      continue;
    }
    if (current) current.lines.push(original);
    else rootLines.push(original);
  }

  let rootConfig = {};
  if (hasMeaningfulLines(rootLines)) {
    rootConfig = parseAssignments(rootLines.join("\n"));
    if (Object.keys(rootConfig).length) {
      throw new Error("root-level fields are not supported; use [timers.<name>] entries");
    }
  }

  const vibrationConfig = parseVibrationConfig(
    vibrationSection ? parseAssignments(vibrationSection.lines.join("\n")) : null
  );

  let timers = null;

  if (namedSections.length) {
    timers = namedSections.map(function(section, index) {
      return normalizeTimer(
        parseAssignments(section.lines.join("\n")),
        index,
        titleCaseKey(section.name),
        vibrationConfig
      );
    });
  } else {
    throw new Error("config must define at least one timer with [timers.<name>]");
  }

  return {
    timers: timers,
  };
}

function sendMessage(payload, onSuccess, onFailure) {
  Pebble.sendAppMessage(payload, onSuccess || function() {}, onFailure || function() {});
}

function sendConfig(config) {
  const timers = config.timers;
  const uiSettings = loadUiSettings();
  let uiFlags = uiSettings.iconsEnabled ? CONFIG_FLAG_ICONS : 0;
  if (uiSettings.backgroundEnabled) {
    uiFlags |= CONFIG_FLAG_BACKGROUND;
  }
  if (uiSettings.timerAccentEnabled) {
    uiFlags |= CONFIG_FLAG_TIMER_ACCENT;
  }
  const payload = {};
  payload[KEY_CFG_OP] = CFG_OP_BEGIN;
  payload[KEY_CFG_TIMER] = timers.length;
  payload[KEY_CFG_UI_FLAGS] = uiFlags;
  sendMessage(payload, function() {
    sendTimerAt(timers, 0);
  });
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
    (timer.mustAcknowledge ? 4 : 0);
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
  payload[KEY_CFG_UP_ACTION] = timer.onPressUp;
  payload[KEY_CFG_UP_LONG_ACTION] = timer.onLongPressUp;
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
  sendMessage(payload, function() {
    sendVibrateAt(timers, timerIndex, segmentIndex, 0);
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
  if (!event.response) return;
  try {
    const response = clay.getSettings(event.response, false);
    const toml = String((response.TomlConfig && response.TomlConfig.value) || "").trim();
    const uiSettings = {
      iconsEnabled: !response.IconsEnabled || !!response.IconsEnabled.value,
      backgroundEnabled: !response.BackgroundEnabled || !!response.BackgroundEnabled.value,
      timerAccentEnabled: !response.TimerAccentEnabled || !!response.TimerAccentEnabled.value,
    };
    saveUiSettings(uiSettings);
    const parsed = parseTimerToml(toml);
    saveToml(toml);
    sendConfig(parsed);
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
