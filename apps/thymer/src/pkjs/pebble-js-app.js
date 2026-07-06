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
const MAX_TIMERS = 100;
const MAX_WARN_ATS = 4;
const DEFAULT_WARNING_VIBRATE = "mid-mid-mid";
const DEFAULT_VIBRATION_LEVELS = {
  low: 75,
  mid: 100,
  high: 150,
};

const UP_ACTION_NONE = 0;
const UP_ACTION_SKIP = 1;
const UP_ACTION_HIDE = 2;
const UP_ACTION_INCREMENT = 3;
const UP_ACTION_DECREMENT = 4;
const UP_ACTION_STOPWATCH = 5;

const SEGMENT_KEYS = ["hint", "time", "vibrate", "warn-at"];

function parseUpActionKind(raw, fieldName, index) {
  switch (String(raw == null ? "" : raw).trim().toLowerCase()) {
    case "skip":
      return UP_ACTION_SKIP;
    case "hide":
      return UP_ACTION_HIDE;
    case "increment":
      return UP_ACTION_INCREMENT;
    case "decrement":
      return UP_ACTION_DECREMENT;
    case "stopwatch":
      return UP_ACTION_STOPWATCH;
    default:
      throw new Error(
        `timer ${index + 1} ${fieldName} action must be "skip", "hide", "increment", "decrement", or "stopwatch"`
      );
  }
}
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

function assertAllowedKeys(raw, allowedKeys, context) {
  const allowed = {};
  allowedKeys.forEach(function(key) {
    allowed[key] = true;
  });
  Object.keys(raw).forEach(function(key) {
    if (!allowed[key]) {
      throw new Error(`${context} uses unsupported key: ${key}`);
    }
  });
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

function directionalSwipe(value) {
  const normalized = String(value).trim().toLowerCase();
  switch (normalized) {
    case "left":
    case "l":
      return { from: ZONE_RIGHT, to: ZONE_LEFT };
    case "up":
    case "u":
      return { from: ZONE_BOTTOM, to: ZONE_TOP };
    case "right":
    case "r":
      return { from: ZONE_LEFT, to: ZONE_RIGHT };
    case "down":
    case "d":
      return { from: ZONE_TOP, to: ZONE_BOTTOM };
    default:
      return null;
  }
}

function normalizeTrigger(trigger) {
  if (!trigger || typeof trigger !== "object") {
    throw new Error("trigger must be an inline table");
  }
  assertAllowedKeys(trigger, ["tap", "swipe"], "trigger");
  if (trigger.tap) {
    return {
      kind: TRIGGER_TAP,
      from: zoneId(trigger.tap),
      to: ZONE_NONE,
    };
  }
  if (trigger.swipe) {
    const swipe = String(trigger.swipe).trim().toLowerCase();
    const directional = directionalSwipe(swipe);
    if (directional) {
      return {
        kind: TRIGGER_SWIPE,
        from: directional.from,
        to: directional.to,
      };
    }
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
  return String(value || "mid").trim().toLowerCase();
}

function parseVibrationConfig(raw) {
  if (raw == null) {
    return {
      pulseDelay: DEFAULT_PULSE_DELAY,
      acknowledgeAlertDuration: DEFAULT_ACK_ALERT_DURATION,
      levels: Object.assign({}, DEFAULT_VIBRATION_LEVELS),
      warning: DEFAULT_WARNING_VIBRATE,
    };
  }
  if (!raw || typeof raw !== "object" || Array.isArray(raw)) {
    throw new Error("vibration must be a table");
  }

  const levels = Object.assign({}, DEFAULT_VIBRATION_LEVELS);
  let pulseDelay = DEFAULT_PULSE_DELAY;
  let acknowledgeAlertDuration = DEFAULT_ACK_ALERT_DURATION;
  let warning = DEFAULT_WARNING_VIBRATE;
  for (const key of Object.keys(raw)) {
    if (key === "pulse-delay") {
      pulseDelay = Math.max(0, Number(raw[key]) | 0);
      continue;
    }
    if (key === "acknowledgment-alert-duration") {
      acknowledgeAlertDuration = normalizeAckAlertDuration(raw[key], "vibration");
      continue;
    }
    if (key === "warning") {
      warning = raw[key];
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

  return { pulseDelay, acknowledgeAlertDuration, levels, warning };
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
const TRUE_STOPWATCH_DURATION_MS = MAX_DURATION_MS;

function normalizeSegmentDurationMs(value, context) {
  const label = context || "segment time";
  if (value == null) {
    throw new Error(`${label} is required`);
  }
  if (typeof value === "number") {
    if (!Number.isFinite(value) || value < 0 || !Number.isSafeInteger(value)) {
      throw new Error(`invalid ${label}: ${value}`);
    }
    const totalMs = value * MS_PER_SECOND;
    if (!Number.isSafeInteger(totalMs) || totalMs < 1 || totalMs > MAX_DURATION_MS) {
      throw new Error(`${label} out of range: ${value}`);
    }
    return totalMs;
  }

  const raw = String(value == null ? "" : value).trim();
  const match = /^(?:(\d+)-)?(\d{2}):(\d{2}):(\d{2})(?:\.(\d{1,4}))?$/.exec(raw);
  if (!match) {
    throw new Error(`invalid ${label}: ${value}`);
  }

  const days = Number(match[1] || 0);
  const hours = Number(match[2]);
  const minutes = Number(match[3]);
  const seconds = Number(match[4]);
  if (hours > 23 || minutes > 59 || seconds > 59) {
    throw new Error(`invalid ${label}: ${value}`);
  }

  let totalTenThousandths = days * 86400 * TEN_THOUSANDTHS_PER_SECOND;
  totalTenThousandths += hours * 3600 * TEN_THOUSANDTHS_PER_SECOND;
  totalTenThousandths += minutes * 60 * TEN_THOUSANDTHS_PER_SECOND;
  totalTenThousandths += seconds * TEN_THOUSANDTHS_PER_SECOND;
  if (match[5]) {
    totalTenThousandths += Number(match[5].padEnd(4, "0"));
  }

  if (!Number.isSafeInteger(totalTenThousandths)) {
    throw new Error(`${label} out of range: ${value}`);
  }

  const totalMs = Math.floor((totalTenThousandths + 9) / 10);
  if (totalMs < 1 || totalMs > MAX_DURATION_MS) {
    throw new Error(`${label} out of range: ${value}`);
  }
  return totalMs;
}

function normalizeRepeatPatternDelay(value, timerContext) {
  if (value == null) {
    return DEFAULT_REPEAT_PATTERN_DELAY;
  }
  if (typeof value !== "number" || !Number.isFinite(value) || value < 0 || !Number.isSafeInteger(value)) {
    throw new Error(`${timerContext} repeat-pattern-delay must be a non-negative integer`);
  }
  if (value > 65535) {
    throw new Error(`${timerContext} repeat-pattern-delay out of range`);
  }
  return value;
}

function normalizeAckAlertDuration(value, timerContext) {
  if (value == null) {
    return DEFAULT_ACK_ALERT_DURATION;
  }
  if (typeof value !== "number" || !Number.isFinite(value) || value < 0 || !Number.isSafeInteger(value)) {
    throw new Error(`${timerContext || "vibration"} acknowledgment-alert-duration must be a non-negative integer`);
  }
  if (value > 65535) {
    throw new Error(`${timerContext || "vibration"} acknowledgment-alert-duration out of range`);
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
  assertAllowedKeys(raw, ["intensity", "duration", "delay"], "vibrate step");
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

function defaultWarningVibrate(vibrationConfig) {
  return normalizeVibrate(vibrationConfig.warning, vibrationConfig);
}

function normalizeWarnAtEntry(raw, vibrationConfig, context) {
  if (typeof raw === "string" || typeof raw === "number") {
    return {
      timeBeforeEndMs: normalizeSegmentDurationMs(raw, `${context} time`),
      vibrate: defaultWarningVibrate(vibrationConfig),
    };
  }
  if (!raw || typeof raw !== "object" || Array.isArray(raw)) {
    throw new Error(`${context} must be a time value or inline table`);
  }
  assertAllowedKeys(raw, ["time", "vibrate"], context);
  if (raw.time == null) {
    throw new Error(`${context} must define time`);
  }
  return {
    timeBeforeEndMs: normalizeSegmentDurationMs(raw.time, `${context} time`),
    vibrate: raw.vibrate != null
      ? normalizeVibrate(raw.vibrate, vibrationConfig)
      : defaultWarningVibrate(vibrationConfig),
  };
}

function normalizeWarnAt(raw, segmentDurationMs, vibrationConfig, context) {
  if (raw == null) {
    return [];
  }

  const items = Array.isArray(raw) ? raw : [raw];
  if (items.length > MAX_WARN_ATS) {
    throw new Error(`${context} supports at most ${MAX_WARN_ATS} entries`);
  }

  return items.map(function(item, index) {
    const entry = normalizeWarnAtEntry(item, vibrationConfig, `${context} ${index + 1}`);
    if (entry.timeBeforeEndMs < 1 || entry.timeBeforeEndMs >= segmentDurationMs) {
      throw new Error(`${context} ${index + 1} must be less than the segment time`);
    }
    return entry;
  }).sort(function(left, right) {
    return right.timeBeforeEndMs - left.timeBeforeEndMs;
  });
}

function normalizeSegment(raw, context, defaultSegment, vibrationConfig) {
  if (!raw || typeof raw !== "object" || Array.isArray(raw)) {
    throw new Error(`${context} must be inline table`);
  }

  assertAllowedKeys(
    raw,
    ["name"].concat(SEGMENT_KEYS),
    context
  );

  const durationSource = raw.time != null ? raw.time : defaultSegment.time;
  const durationMs = defaultSegment.time === TRUE_STOPWATCH_DURATION_MS && raw.time == null
    ? TRUE_STOPWATCH_DURATION_MS
    : normalizeSegmentDurationMs(durationSource, `${context} time`);
  const segmentVibrate = raw.vibrate != null
    ? normalizeVibrate(raw.vibrate, vibrationConfig)
    : defaultSegment.vibrate;

  return {
    name: raw.name == null ? "" : String(raw.name),
    hint: raw.hint != null ? String(raw.hint) : defaultSegment.hint,
    durationMs: durationMs,
    vibrate: segmentVibrate,
    warnAt: normalizeWarnAt(
      raw["warn-at"] != null ? raw["warn-at"] : defaultSegment.warnAt,
      durationMs,
      vibrationConfig,
      `${context} warn-at`
    ),
  };
}

function normalizeFinishVibrate(raw, timerContext, vibrationConfig) {
  if (raw == null) {
    return [];
  }
  if (!raw || typeof raw !== "object" || Array.isArray(raw)) {
    throw new Error(`${timerContext} on-finished must be an inline table`);
  }
  assertAllowedKeys(raw, ["vibrate"], `${timerContext} on-finished`);
  if (raw.vibrate == null) {
    throw new Error(`${timerContext} on-finished must define vibrate`);
  }
  return normalizeVibrate(raw.vibrate, vibrationConfig);
}

function normalizeUpAction(raw, fieldName, timerContext, index, defaultKind) {
  if (raw == null) {
    return { kind: defaultKind == null ? UP_ACTION_NONE : defaultKind, durationMs: 0 };
  }

  if (typeof raw === "string") {
    const kind = parseUpActionKind(raw, fieldName, index);
    if (kind === UP_ACTION_INCREMENT || kind === UP_ACTION_DECREMENT) {
      throw new Error(`${timerContext} ${fieldName} must use an inline table for ${raw}`);
    }
    return {
      kind: kind,
      durationMs: 0,
    };
  }

  if (!raw || typeof raw !== "object" || Array.isArray(raw)) {
    throw new Error(`${timerContext} ${fieldName} must be a string or inline table`);
  }
  assertAllowedKeys(raw, ["action", "time"], `${timerContext} ${fieldName}`);

  const kind = parseUpActionKind(raw.action, fieldName, index);
  const needsTime = kind === UP_ACTION_INCREMENT || kind === UP_ACTION_DECREMENT;
  if (needsTime && raw.time == null) {
    throw new Error(`${timerContext} ${fieldName} must define time for ${raw.action}`);
  }
  if (!needsTime && raw.time != null) {
    throw new Error(`${timerContext} ${fieldName} only supports time with increment/decrement`);
  }

  return {
    kind: kind,
    durationMs: needsTime ? normalizeSegmentDurationMs(raw.time, `${timerContext} ${fieldName} time`) : 0,
  };
}

function normalizeTimer(raw, index, timerKey, fallbackName, vibrationConfig) {
  const timerContext = timerKey ? `timer ${index + 1} [timers.${timerKey}]` : `timer ${index + 1}`;
  assertAllowedKeys(raw, [
    "name",
    "repeat",
    "stopwatch",
    "trigger",
    "pattern",
    "hint",
    "time",
    "vibrate",
    "warn-at",
    "on-finished",
    "on-press-up",
    "on-long-press-up",
    "on-long-press-select",
    "must-acknowledge",
    "repeat-pattern-delay",
    "acknowledgment-alert-duration",
  ], timerContext);
  if (raw.stopwatch != null && typeof raw.stopwatch !== "boolean") {
    throw new Error(`${timerContext} stopwatch must be true or false`);
  }
  const stopwatch = raw.stopwatch === true;
  const stopwatchOnly = stopwatch && raw.time == null && raw.pattern == null;
  if (raw.time != null && raw.pattern != null) {
    throw new Error(`${timerContext} cannot define both time and pattern`);
  }
  if (raw.pattern != null && (!Array.isArray(raw.pattern) || raw.pattern.length === 0)) {
    throw new Error(`${timerContext} pattern must be a non-empty array`);
  }
  if (!stopwatchOnly && raw.time == null && raw.pattern == null) {
    throw new Error(`${timerContext} must define time or pattern`);
  }
  if (stopwatchOnly && raw["on-finished"] != null) {
    throw new Error(`${timerContext} true stopwatch cannot use on-finished`);
  }
  const rawRepeat = raw.repeat;
  const repeatForever = rawRepeat === true;
  const repeatCount = typeof rawRepeat === "number" ? Math.max(1, Number(rawRepeat) | 0) : 0;
  const repeat = !stopwatchOnly && (repeatForever || repeatCount > 0);
  const finishVibrate = normalizeFinishVibrate(raw["on-finished"], timerContext, vibrationConfig);
  const defaultVibrate = normalizeVibrate(raw.vibrate, vibrationConfig);
  const defaultSegment = {
    hint: raw.hint == null ? "" : String(raw.hint),
    time: stopwatchOnly ? TRUE_STOPWATCH_DURATION_MS : raw.time,
    vibrate: defaultVibrate,
    warnAt: stopwatchOnly ? null : raw["warn-at"],
  };
  if (repeatForever && finishVibrate.length > 0) {
    throw new Error(`${timerContext} cannot use on-finished with repeat = true`);
  }
  if (raw["must-acknowledge"] != null && typeof raw["must-acknowledge"] !== "boolean") {
    throw new Error(`${timerContext} must-acknowledge must be true or false`);
  }
  const onPressUp = normalizeUpAction(raw["on-press-up"], "on-press-up", timerContext, index);
  const onLongPressUp = normalizeUpAction(raw["on-long-press-up"], "on-long-press-up", timerContext, index);
  const onLongPressSelect = normalizeUpAction(
    raw["on-long-press-select"],
    "on-long-press-select",
    timerContext,
    index,
    UP_ACTION_HIDE
  );
  return {
    name: raw.name == null ? String(fallbackName || `Timer ${index + 1}`) : String(raw.name),
    repeat: repeat,
    stopwatch: stopwatch,
    stopwatchOnly: stopwatchOnly,
    iterationsEnabled: !stopwatchOnly && repeatCount > 0,
    iterations: stopwatchOnly ? 0 : repeatCount,
    onPressUp: onPressUp,
    onLongPressUp: onLongPressUp,
    onLongPressSelect: onLongPressSelect,
    mustAcknowledge: raw["must-acknowledge"] === true,
    repeatPatternDelay: normalizeRepeatPatternDelay(raw["repeat-pattern-delay"], timerContext),
    acknowledgeAlertDuration: normalizeAckAlertDuration(
      raw["acknowledgment-alert-duration"] == null
        ? vibrationConfig.acknowledgeAlertDuration
        : raw["acknowledgment-alert-duration"],
      timerContext
    ),
    finishVibrate: finishVibrate,
    trigger: normalizeTrigger(raw.trigger),
    pattern: raw.pattern != null
      ? raw.pattern.map(function(segment, segmentIndex) {
        return normalizeSegment(
          segment,
          `${timerContext} pattern ${segmentIndex + 1}`,
          defaultSegment,
          vibrationConfig
        );
      })
      : [normalizeSegment({}, timerContext, defaultSegment, vibrationConfig)],
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
        section.name,
        titleCaseKey(section.name),
        vibrationConfig
      );
    });
  } else {
    throw new Error("config must define at least one timer with [timers.<name>]");
  }

  if (timers.length > MAX_TIMERS) {
    throw new Error(
      `config defines ${timers.length} timers but Thymer supports at most ${MAX_TIMERS}`
    );
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
  if (!event.response) return;
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
