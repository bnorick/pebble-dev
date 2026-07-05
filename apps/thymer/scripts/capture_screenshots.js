#!/usr/bin/env node

const fs = require("fs");
const path = require("path");
const { spawnSync } = require("child_process");

const APP_UUID = "419f59db-a7ad-4889-900e-b44b92066252";
const PLATFORM = "emery";
const ROOT = path.resolve(__dirname, "..");
const CONFIG_PATH = path.join(ROOT, "examples", "my-config.toml");
const OUTPUT_DIR = path.join(ROOT, "annex", "screenshots");
const APPMESSAGE_HELPER = path.join(ROOT, "scripts", "send_app_messages.py");

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
const KEY_CFG_UP_ACTION = 10016;
const KEY_CFG_UP_LONG_ACTION = 10017;
const KEY_CFG_UI_FLAGS = 10018;
const KEY_CFG_ACK_DURATION = 10019;
const KEY_CFG_HINT = 10020;
const KEY_CFG_UP_ACTION_TIME = 10021;
const KEY_CFG_UP_LONG_ACTION_TIME = 10022;
const KEY_CFG_SELECT_LONG_ACTION = 10023;
const KEY_CFG_SELECT_LONG_ACTION_TIME = 10024;

const CFG_OP_BEGIN = 1;
const CFG_OP_TIMER = 2;
const CFG_OP_SEGMENT = 3;
const CFG_OP_VIBRATE = 4;
const CFG_OP_COMMIT = 5;
const CFG_OP_UI = 7;

const TRIGGER_NONE = 0;
const TRIGGER_TAP = 1;
const TRIGGER_SWIPE = 2;

const ZONE_NONE = 0;
const ZONE_LEFT = 1;
const ZONE_TOP = 2;
const ZONE_RIGHT = 3;
const ZONE_BOTTOM = 4;
const ZONE_CENTER = 5;

const VIBE_MID = 2;
const FINISH_VIBE_SEGMENT = 255;
const DEFAULT_PULSE_DELAY = 100;
const DEFAULT_REPEAT_PATTERN_DELAY = 500;
const DEFAULT_ACK_ALERT_DURATION = 12;
const MAX_TIMERS = 100;
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

const CONFIG_FLAG_ICONS = 0x1;
const CONFIG_FLAG_BACKGROUND = 0x2;
const CONFIG_FLAG_TIMER_ACCENT = 0x4;

const s_startedAt = Date.now();

function elapsedLabel() {
  const totalMs = Date.now() - s_startedAt;
  const minutes = Math.floor(totalMs / 60000);
  const seconds = Math.floor((totalMs % 60000) / 1000);
  const millis = totalMs % 1000;
  return `${String(minutes).padStart(2, "0")}:${String(seconds).padStart(2, "0")}.${String(millis).padStart(3, "0")}`;
}

function log(message) {
  process.stdout.write(`[${elapsedLabel()}] ${message}\n`);
}

function formatCommand(args) {
  return ["pebble", ...args].join(" ");
}

function cleanPebbleOutput(text) {
  return String(text || "")
    .replace(/\x1b\[[0-9;]*m/g, "")
    .split(/\r?\n/)
    .map((line) => line.trimEnd())
    .filter((line) => line &&
      !line.includes("A new SDK is available:") &&
      !line.includes("Update with: pebble sdk install latest"))
    .join("\n");
}

function runCommand(command, args, options = {}) {
  const rendered = [command, ...args].join(" ");
  const start = Date.now();
  log(`run ${rendered}`);
  const result = spawnSync(command, args, {
    cwd: ROOT,
    encoding: "utf8",
    stdio: ["ignore", "pipe", "pipe"],
  });
  const durationMs = Date.now() - start;
  const stdout = cleanPebbleOutput(result.stdout);
  const stderr = cleanPebbleOutput(result.stderr);

  if (stdout) {
    stdout.split("\n").forEach((line) => log(`stdout ${line}`));
  }
  if (stderr) {
    stderr.split("\n").forEach((line) => log(`stderr ${line}`));
  }

  if (result.error) {
    log(`fail ${rendered} after ${durationMs}ms`);
    throw result.error;
  }
  if (result.status !== 0) {
    log(`fail ${rendered} exit=${result.status} after ${durationMs}ms`);
    throw new Error(`Command failed: ${rendered}`);
  }

  if (!options.quietSuccess) {
    log(`ok ${rendered} in ${durationMs}ms`);
  }
}

function runPebble(args, options = {}) {
  runCommand("pebble", args, options);
}

function sleep(ms) {
  return new Promise((resolve) => setTimeout(resolve, ms));
}

async function wait(ms, reason) {
  log(`wait ${ms}ms${reason ? ` ${reason}` : ""}`);
  await sleep(ms);
}

function stripComments(line) {
  let result = "";
  let quote = null;
  for (let i = 0; i < line.length; i++) {
    const ch = line[i];
    if (quote) {
      if (ch === quote && line[i - 1] !== "\\") {
        quote = null;
      }
      result += ch;
      continue;
    }
    if (ch === '"' || ch === "'") {
      quote = ch;
      result += ch;
      continue;
    }
    if (ch === "#") {
      break;
    }
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
      if (ch === quote && text[i - 1] !== "\\") {
        quote = null;
      }
      continue;
    }
    if (ch === '"' || ch === "'") {
      quote = ch;
      continue;
    }
    if (ch === "[") {
      bracketDepth++;
    } else if (ch === "]") {
      bracketDepth--;
    } else if (ch === "{") {
      braceDepth++;
    } else if (ch === "}") {
      braceDepth--;
    } else if (ch === delimiter && bracketDepth === 0 && braceDepth === 0) {
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
      if (next === "n") {
        result += "\n";
      } else if (next === "t") {
        result += "\t";
      } else {
        result += next;
      }
    } else {
      result += ch;
    }
  }
  return result;
}

function parseValue(raw) {
  const value = raw.trim();
  if (!value) {
    throw new Error("empty value");
  }
  if ((value[0] === '"' && value[value.length - 1] === '"') ||
      (value[0] === "'" && value[value.length - 1] === "'")) {
    return parseString(value);
  }
  if (value === "true") {
    return true;
  }
  if (value === "false") {
    return false;
  }
  if (/^-?\d+$/.test(value)) {
    return Number(value);
  }
  if (value[0] === "[" && value[value.length - 1] === "]") {
    const inner = value.slice(1, -1).trim();
    if (!inner) {
      return [];
    }
    return splitTopLevel(inner, ",").map(parseValue);
  }
  if (value[0] === "{" && value[value.length - 1] === "}") {
    const inner = value.slice(1, -1).trim();
    const object = {};
    if (!inner) {
      return object;
    }
    for (const entry of splitTopLevel(inner, ",")) {
      const eq = entry.indexOf("=");
      if (eq < 0) {
        throw new Error(`invalid inline table entry: ${entry}`);
      }
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
    if (!cleaned) {
      continue;
    }
    const eq = cleaned.indexOf("=");
    if (eq < 0) {
      throw new Error(`invalid line: ${cleaned}`);
    }
    const key = cleaned.slice(0, eq).trim();
    let value = cleaned.slice(eq + 1).trim();

    let bracketDepth = (value.match(/\[/g) || []).length - (value.match(/\]/g) || []).length;
    let braceDepth = (value.match(/\{/g) || []).length - (value.match(/\}/g) || []).length;
    while (bracketDepth > 0 || braceDepth > 0) {
      i += 1;
      if (i >= lines.length) {
        throw new Error(`unterminated value for ${key}`);
      }
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
  allowedKeys.forEach((key) => {
    allowed[key] = true;
  });
  Object.keys(raw).forEach((key) => {
    if (!allowed[key]) {
      throw new Error(`${context} uses unsupported key: ${key}`);
    }
  });
}

function titleCaseKey(key) {
  return String(key)
    .replace(/[-_]+/g, " ")
    .replace(/\b[a-z]/g, (match) => match.toUpperCase());
}

function zoneId(value) {
  const normalized = String(value).trim().toLowerCase();
  switch (normalized) {
    case "left":
    case "l":
      return ZONE_LEFT;
    case "top":
    case "t":
    case "up":
    case "u":
      return ZONE_TOP;
    case "right":
    case "r":
      return ZONE_RIGHT;
    case "bottom":
    case "b":
    case "down":
    case "d":
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
    if (parts.length !== 2) {
      throw new Error(`invalid swipe: ${trigger.swipe}`);
    }
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

function normalizeAckAlertDuration(value, index) {
  if (value == null) {
    return DEFAULT_ACK_ALERT_DURATION;
  }
  if (typeof value !== "number" || !Number.isFinite(value) || value < 0 || !Number.isSafeInteger(value)) {
    throw new Error(`${index >= 0 ? `timer ${index + 1}` : "vibration"} acknowledgment-alert-duration must be a non-negative integer`);
  }
  if (value > 65535) {
    throw new Error(`${index >= 0 ? `timer ${index + 1}` : "vibration"} acknowledgment-alert-duration out of range`);
  }
  return value;
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
    if (key === "acknowledgment-alert-duration") {
      acknowledgeAlertDuration = normalizeAckAlertDuration(raw[key], -1);
      continue;
    }

    const normalizedKey = normalizeVibrationName(key);
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

  const raw = String(value).trim();
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
    default:
      throw new Error(
        `timer ${index + 1} ${fieldName} action must be "skip", "hide", "increment", or "decrement"`
      );
  }
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
  if (raw == null) {
    return [];
  }
  if (typeof raw === "string" && raw.indexOf("-") >= 0) {
    return raw.split("-").map((part) => normalizeVibrateStep(part.trim(), vibrationConfig));
  }
  if (Array.isArray(raw)) {
    return raw.map((step) => normalizeVibrateStep(step, vibrationConfig));
  }
  return [normalizeVibrateStep(raw, vibrationConfig)];
}

function normalizeFinishVibrate(raw, index, vibrationConfig) {
  if (raw == null) {
    return [];
  }
  if (!raw || typeof raw !== "object" || Array.isArray(raw)) {
    throw new Error(`timer ${index + 1} on-finished must be an inline table`);
  }
  assertAllowedKeys(raw, ["vibrate"], `timer ${index + 1} on-finished`);
  if (raw.vibrate == null) {
    throw new Error(`timer ${index + 1} on-finished must define vibrate`);
  }
  return normalizeVibrate(raw.vibrate, vibrationConfig);
}

function normalizeUpAction(raw, fieldName, index, defaultKind) {
  if (raw == null) {
    return { kind: defaultKind == null ? UP_ACTION_NONE : defaultKind, durationMs: 0 };
  }
  if (typeof raw === "string") {
    const kind = parseUpActionKind(raw, fieldName, index);
    if (kind === UP_ACTION_INCREMENT || kind === UP_ACTION_DECREMENT) {
      throw new Error(`timer ${index + 1} ${fieldName} must use an inline table for ${raw}`);
    }
    return { kind, durationMs: 0 };
  }
  if (!raw || typeof raw !== "object" || Array.isArray(raw)) {
    throw new Error(`timer ${index + 1} ${fieldName} must be a string or inline table`);
  }
  assertAllowedKeys(raw, ["action", "time"], `timer ${index + 1} ${fieldName}`);
  const kind = parseUpActionKind(raw.action, fieldName, index);
  const needsTime = kind === UP_ACTION_INCREMENT || kind === UP_ACTION_DECREMENT;
  if (needsTime && raw.time == null) {
    throw new Error(`timer ${index + 1} ${fieldName} must define time for ${raw.action}`);
  }
  if (!needsTime && raw.time != null) {
    throw new Error(`timer ${index + 1} ${fieldName} only supports time with increment/decrement`);
  }
  return {
    kind,
    durationMs: needsTime ? normalizeSegmentDurationMs(raw.time) : 0,
  };
}

function normalizeTimer(raw, index, fallbackName, vibrationConfig) {
  assertAllowedKeys(raw, [
    "name",
    "repeat",
    "trigger",
    "pattern",
    "vibrate",
    "on-finished",
    "on-press-up",
    "on-long-press-up",
    "on-long-press-select",
    "must-acknowledge",
    "repeat-pattern-delay",
    "acknowledgment-alert-duration",
  ], `timer ${index + 1}`);
  if (!Array.isArray(raw.pattern) || raw.pattern.length === 0) {
    throw new Error(`timer ${index + 1} is missing pattern`);
  }
  const rawRepeat = raw.repeat;
  const repeatForever = rawRepeat === true;
  const repeatCount = typeof rawRepeat === "number" ? Math.max(1, Number(rawRepeat) | 0) : 0;
  const repeat = repeatForever || repeatCount > 0;
  const finishVibrate = normalizeFinishVibrate(raw["on-finished"], index, vibrationConfig);
  const defaultVibrate = normalizeVibrate(raw.vibrate, vibrationConfig);
  const onPressUp = normalizeUpAction(raw["on-press-up"], "on-press-up", index);
  const onLongPressUp = normalizeUpAction(raw["on-long-press-up"], "on-long-press-up", index);
  const onLongPressSelect = normalizeUpAction(
    raw["on-long-press-select"],
    "on-long-press-select",
    index,
    UP_ACTION_HIDE
  );
  return {
    name: raw.name == null ? String(fallbackName || `Timer ${index + 1}`) : String(raw.name),
    repeat,
    iterationsEnabled: repeatCount > 0,
    iterations: repeatCount,
    onPressUp,
    onLongPressUp,
    onLongPressSelect,
    mustAcknowledge: raw["must-acknowledge"] === true,
    repeatPatternDelay: normalizeRepeatPatternDelay(raw["repeat-pattern-delay"], index),
    acknowledgeAlertDuration: normalizeAckAlertDuration(
      raw["acknowledgment-alert-duration"] == null
        ? vibrationConfig.acknowledgeAlertDuration
        : raw["acknowledgment-alert-duration"],
      index
    ),
    finishVibrate,
    trigger: normalizeTrigger(raw.trigger),
    pattern: raw.pattern.map((segment, segmentIndex) => {
      if (!segment || typeof segment !== "object") {
        throw new Error(`timer ${index + 1} pattern ${segmentIndex + 1} must be inline table`);
      }
      assertAllowedKeys(segment, ["name", "hint", "time", "vibrate"], `timer ${index + 1} pattern ${segmentIndex + 1}`);
      return {
        name: segment.name == null ? "" : String(segment.name),
        hint: segment.hint == null ? "" : String(segment.hint),
        durationMs: normalizeSegmentDurationMs(segment.time),
        vibrate: segment.vibrate != null
          ? normalizeVibrate(segment.vibrate, vibrationConfig)
          : defaultVibrate,
      };
    }),
  };
}

function hasMeaningfulLines(lines) {
  return lines.some((line) => stripComments(line).length > 0);
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
    if (current) {
      current.lines.push(original);
    } else {
      rootLines.push(original);
    }
  }

  if (hasMeaningfulLines(rootLines)) {
    const rootConfig = parseAssignments(rootLines.join("\n"));
    if (Object.keys(rootConfig).length) {
      throw new Error("root-level fields are not supported; use [timers.<name>] entries");
    }
  }

  const vibrationConfig = parseVibrationConfig(
    vibrationSection ? parseAssignments(vibrationSection.lines.join("\n")) : null
  );
  if (!namedSections.length) {
    throw new Error("config must define at least one timer with [timers.<name>]");
  }

  const timers = namedSections.map((section, index) => normalizeTimer(
    parseAssignments(section.lines.join("\n")),
    index,
    titleCaseKey(section.name),
    vibrationConfig
  ));

  if (timers.length > MAX_TIMERS) {
    throw new Error(`config defines ${timers.length} timers but Thymer supports at most ${MAX_TIMERS}`);
  }

  return { timers };
}

function encodeUint64Hex(value) {
  if (typeof value !== "number" || !Number.isSafeInteger(value) || value < 0 || value > MAX_DURATION_MS) {
    throw new Error(`uint64 value out of range: ${value}`);
  }
  const bytes = new Array(8);
  let remaining = value;
  for (let i = 0; i < 8; i++) {
    bytes[i] = remaining % 256;
    remaining = Math.floor(remaining / 256);
  }
  return bytes.map((byte) => byte.toString(16).padStart(2, "0")).join("").toUpperCase();
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

function buildConfigMessages(config, uiSettings) {
  const messages = [{
    uint: {
      [KEY_CFG_OP]: CFG_OP_BEGIN,
      [KEY_CFG_TIMER]: config.timers.length,
      [KEY_CFG_UI_FLAGS]: uiFlagsFromSettings(uiSettings),
    },
  }];

  config.timers.forEach((timer, timerIndex) => {
    const flags = (timer.repeat ? 1 : 0) |
      (timer.iterationsEnabled ? 2 : 0) |
      (timer.mustAcknowledge ? 4 : 0);

    messages.push({
      uint: {
        [KEY_CFG_OP]: CFG_OP_TIMER,
        [KEY_CFG_TIMER]: timerIndex,
        [KEY_CFG_SEGMENT]: timer.pattern.length,
        [KEY_CFG_FLAGS]: flags,
        [KEY_CFG_ITER]: timer.iterations,
        [KEY_CFG_TRIGGER_KIND]: timer.trigger.kind,
        [KEY_CFG_TRIGGER_FROM]: timer.trigger.from,
        [KEY_CFG_TRIGGER_TO]: timer.trigger.to,
        [KEY_CFG_ALERT]: timer.finishVibrate.length,
        [KEY_CFG_REPEAT_PATTERN_DELAY]: timer.repeatPatternDelay,
        [KEY_CFG_ACK_DURATION]: timer.acknowledgeAlertDuration,
        [KEY_CFG_UP_ACTION]: timer.onPressUp.kind,
        [KEY_CFG_UP_LONG_ACTION]: timer.onLongPressUp.kind,
        [KEY_CFG_SELECT_LONG_ACTION]: timer.onLongPressSelect.kind,
      },
      string: {
        [KEY_CFG_TEXT]: timer.name,
      },
      bytes: {
        [KEY_CFG_UP_ACTION_TIME]: encodeUint64Hex(timer.onPressUp.durationMs),
        [KEY_CFG_UP_LONG_ACTION_TIME]: encodeUint64Hex(timer.onLongPressUp.durationMs),
        [KEY_CFG_SELECT_LONG_ACTION_TIME]: encodeUint64Hex(timer.onLongPressSelect.durationMs),
      },
    });

    timer.pattern.forEach((segment, segmentIndex) => {
      messages.push({
        uint: {
          [KEY_CFG_OP]: CFG_OP_SEGMENT,
          [KEY_CFG_TIMER]: timerIndex,
          [KEY_CFG_SEGMENT]: segmentIndex,
          [KEY_CFG_ALERT]: segment.vibrate.length,
        },
        string: {
          [KEY_CFG_TEXT]: segment.name,
          [KEY_CFG_HINT]: segment.hint,
        },
        bytes: {
          [KEY_CFG_DURATION]: encodeUint64Hex(segment.durationMs),
        },
      });

      segment.vibrate.forEach((vibe, vibeIndex) => {
        messages.push({
          uint: {
            [KEY_CFG_OP]: CFG_OP_VIBRATE,
            [KEY_CFG_TIMER]: timerIndex,
            [KEY_CFG_SEGMENT]: segmentIndex,
            [KEY_CFG_ALERT]: vibeIndex,
            [KEY_CFG_INTENSITY]: vibe.intensity,
            [KEY_CFG_DURATION]: vibe.duration,
            [KEY_CFG_DELAY]: vibe.delay,
          },
        });
      });
    });

    timer.finishVibrate.forEach((vibe, vibeIndex) => {
      messages.push({
        uint: {
          [KEY_CFG_OP]: CFG_OP_VIBRATE,
          [KEY_CFG_TIMER]: timerIndex,
          [KEY_CFG_SEGMENT]: FINISH_VIBE_SEGMENT,
          [KEY_CFG_ALERT]: vibeIndex,
          [KEY_CFG_INTENSITY]: vibe.intensity,
          [KEY_CFG_DURATION]: vibe.duration,
          [KEY_CFG_DELAY]: vibe.delay,
        },
      });
    });
  });

  messages.push({
    uint: {
      [KEY_CFG_OP]: CFG_OP_COMMIT,
    },
  });
  return messages;
}

function sendAppMessages(messages, options = {}) {
  const retries = options.retries == null ? 1 : options.retries;
  const retryDelayMs = options.retryDelayMs == null ? 2000 : options.retryDelayMs;
  const label = options.label || "appmessage batch";
  const tempPath = path.join(OUTPUT_DIR, `.appmessage-batch-${process.pid}-${Date.now()}.json`);
  try {
    fs.writeFileSync(tempPath, JSON.stringify(messages), "utf8");
    for (let attempt = 1; attempt <= retries; attempt++) {
      try {
        if (attempt > 1) {
          log(`retry ${label} attempt=${attempt}/${retries}`);
        }
        runCommand("uv", [
          "run",
          APPMESSAGE_HELPER,
          "--platform", PLATFORM,
          "--app-uuid", APP_UUID,
          "--messages-file", tempPath,
          "--ack-timeout", "10",
          "--message-delay-ms", "0",
          "--verbose",
        ]);
        return;
      } catch (error) {
        if (attempt === retries) {
          throw error;
        }
        log(`${label} failed on attempt ${attempt}/${retries}`);
        awaitSleep(retryDelayMs);
      }
    }
  } finally {
    if (fs.existsSync(tempPath)) {
      fs.unlinkSync(tempPath);
    }
  }
}

function awaitSleep(ms) {
  const shared = new Int32Array(new SharedArrayBuffer(4));
  Atomics.wait(shared, 0, 0, ms);
}

async function sendConfigToml(toml, uiSettings) {
  const config = parseTimerToml(toml);
  const messages = buildConfigMessages(config, uiSettings);
  log(`send config timers=${config.timers.length} messages=${messages.length} uiFlags=${uiFlagsFromSettings(uiSettings)}`);
  sendAppMessages(messages, {
    label: "initial config batch",
    retries: 3,
    retryDelayMs: 2500,
  });
}

function sendUiSettings(uiSettings) {
  sendAppMessages([{
    uint: {
      [KEY_CFG_OP]: CFG_OP_UI,
      [KEY_CFG_UI_FLAGS]: uiFlagsFromSettings(uiSettings),
    },
  }], {
    label: "ui settings batch",
    retries: 2,
    retryDelayMs: 1000,
  });
}

function sendTrigger(trigger) {
  const normalized = normalizeTrigger(trigger);
  sendAppMessages([{
    uint: {
      [KEY_CFG_TRIGGER_KIND]: normalized.kind,
      [KEY_CFG_TRIGGER_FROM]: normalized.from,
      [KEY_CFG_TRIGGER_TO]: normalized.to,
    },
  }], {
    label: `trigger ${describeTrigger(trigger)}`,
    retries: 2,
    retryDelayMs: 1000,
  });
}

function clickButton(button) {
  log(`button ${button}`);
  runPebble(["emu-button", "--emulator", PLATFORM, "click", button]);
}

function captureOnce(filename) {
  const outputPath = path.join(OUTPUT_DIR, filename);
  log(`capture ${filename}`);
  runPebble(["screenshot", "--emulator", PLATFORM, "--no-open", outputPath]);
}

function warmupScreenshot() {
  const outputPath = path.join(OUTPUT_DIR, ".screenshot-warmup.png");
  log("warmup screenshot");
  runPebble(["screenshot", "--emulator", PLATFORM, "--no-open", outputPath]);
  if (fs.existsSync(outputPath)) {
    fs.unlinkSync(outputPath);
  }
}

async function capture(filename, retries = 3) {
  let lastError = null;
  for (let attempt = 1; attempt <= retries; attempt++) {
    try {
      if (attempt > 1) {
        log(`retry capture ${filename} attempt=${attempt}/${retries}`);
      }
      captureOnce(filename);
      return;
    } catch (error) {
      lastError = error;
      if (attempt === retries) {
        break;
      }
      await wait(1500, `before screenshot retry for ${filename}`);
    }
  }
  throw lastError;
}

async function settle(ms = 500, reason = "settle") {
  await wait(ms, reason);
}

function describeTrigger(trigger) {
  if (trigger.tap) {
    return `tap=${trigger.tap}`;
  }
  if (trigger.swipe) {
    return `swipe=${trigger.swipe}`;
  }
  return JSON.stringify(trigger);
}

function triggerAndSettle(trigger, ms = 800) {
  log(`trigger ${describeTrigger(trigger)}`);
  sendTrigger(trigger);
  return settle(ms, `after ${describeTrigger(trigger)}`);
}

function buttonAndSettle(button, ms = 500) {
  clickButton(button);
  return settle(ms, `after button ${button}`);
}

async function main() {
  fs.mkdirSync(OUTPUT_DIR, { recursive: true });
  log(`output dir ${OUTPUT_DIR}`);
  log(`config ${CONFIG_PATH}`);
  await wait(5000, "startup");

  const toml = fs.readFileSync(CONFIG_PATH, "utf8");
  const allOn = {
    iconsEnabled: true,
    backgroundEnabled: true,
    timerAccentEnabled: true,
  };

  await sendConfigToml(toml, allOn);
  await wait(2500, "after initial config");
  warmupScreenshot();
  await settle(500, "after warmup screenshot");

  await triggerAndSettle({ tap: "top" });
  clickButton("select");
  await wait(6000, "eyesight running before screenshot");
  await capture("00-eyesight-running.png");

  await buttonAndSettle("select", 300);
  await buttonAndSettle("select", 300);
  await wait(12000, "eyesight resumed before pause");
  await buttonAndSettle("select", 300);
  await capture("01-eyesight-paused.png");

  await buttonAndSettle("down", 300);
  await triggerAndSettle({ tap: "right" });
  await capture("02-478-ready.png");

  await buttonAndSettle("up", 300);
  await capture("03-478-hidden.png");

  await triggerAndSettle({ tap: "left" }, 1000);
  await capture("04-sharing-ready.png");

  await buttonAndSettle("up", 300);
  await capture("05-sharing-skip.png");

  await triggerAndSettle({ tap: "bottom" }, 1000);
  await capture("06-1min-ready.png");

  await buttonAndSettle("up", 300);
  await capture("07-1min-incremented.png");

  await triggerAndSettle({ tap: "top" }, 1000);
  clickButton("select");
  await wait(6000, "eyesight running before ui-flag shots");
  await buttonAndSettle("select", 300);

  log("ui icons off");
  sendUiSettings({
    iconsEnabled: false,
    backgroundEnabled: true,
    timerAccentEnabled: true,
  });
  await settle(800, "after ui icons off");
  await capture("08-eyesight-icons-off.png");

  log("ui background off");
  sendUiSettings({
    iconsEnabled: true,
    backgroundEnabled: false,
    timerAccentEnabled: true,
  });
  await settle(800, "after ui background off");
  await capture("09-eyesight-background-off.png");

  log("ui timer accent off");
  sendUiSettings({
    iconsEnabled: true,
    backgroundEnabled: true,
    timerAccentEnabled: false,
  });
  await settle(800, "after ui timer accent off");
  await capture("10-eyesight-timer-accent-off.png");

  sendUiSettings(allOn);
  log("done");
}

main().catch((error) => {
  console.error(error.message || error);
  process.exit(1);
});
