#pragma once

#include <limits.h>
#include <pebble.h>
#include <string.h>

#define APP_NAME "Thymer"

#define MAX_TIMERS 8
#define MAX_SEGMENTS 30
#define MAX_NAME_LEN 40
#define MAX_SEGMENT_NAME_LEN 40
#define MAX_HINT_LEN 28
#define MAX_VIBE_STEPS 4
#define MAX_VIBE_PATTERN_PARTS (MAX_VIBE_STEPS * 2)
#define FINISH_VIBE_SEGMENT 255
#define DEFAULT_REPEAT_PATTERN_DELAY_MS 500
#define DEFAULT_ACK_ALERT_DURATION_S 12

#define TIMER_FLAG_REPEAT 0x1
#define TIMER_FLAG_ITERATIONS_ENABLED 0x2
#define TIMER_FLAG_MUST_ACKNOWLEDGE 0x4

#define PERSIST_KEY_CONFIG_META 100
#define PERSIST_KEY_STATE 101
#define PERSIST_KEY_TIMER_BASE 200
#define PERSIST_KEY_SEGMENT_BASE 300

#define WAKEUP_COOKIE_FINISH 1
#define CONFIG_VERSION 11
#define BUTTON_HINT_ICON_SIZE 28
#define BUTTON_HINT_ICON_HALF (BUTTON_HINT_ICON_SIZE / 2)
#define BUTTON_HINT_WIDTH 30
#define BUTTON_HINT_TOP_OFFSET -14
#define BUTTON_HINT_BOTTOM_OFFSET 14
#define SHOW_TIMER_BACKGROUND true
#define CONFIG_FLAG_ICONS 0x1
#define CONFIG_FLAG_BACKGROUND 0x2
#define CONFIG_FLAG_TIMER_ACCENT 0x4
#define FOCUS_PANEL_BITMAP_WIDTH 170
#define FOCUS_PANEL_BITMAP_HEIGHT 90

#ifndef MESSAGE_KEY_CFG_ALERT
#define MESSAGE_KEY_CFG_ALERT 10011
#endif
#ifndef MESSAGE_KEY_CFG_INTENSITY
#define MESSAGE_KEY_CFG_INTENSITY 10012
#endif
#ifndef MESSAGE_KEY_CFG_DELAY
#define MESSAGE_KEY_CFG_DELAY 10013
#endif
#ifndef MESSAGE_KEY_CFG_REPEAT_PATTERN_DELAY
#define MESSAGE_KEY_CFG_REPEAT_PATTERN_DELAY 10014
#endif
#ifndef MESSAGE_KEY_CFG_ERROR
#define MESSAGE_KEY_CFG_ERROR 10015
#endif
#ifndef MESSAGE_KEY_CFG_UP_ACTION
#define MESSAGE_KEY_CFG_UP_ACTION 10016
#endif
#ifndef MESSAGE_KEY_CFG_UP_LONG_ACTION
#define MESSAGE_KEY_CFG_UP_LONG_ACTION 10017
#endif
#ifndef MESSAGE_KEY_CFG_UI_FLAGS
#define MESSAGE_KEY_CFG_UI_FLAGS 10018
#endif
#ifndef MESSAGE_KEY_CFG_ACK_DURATION
#define MESSAGE_KEY_CFG_ACK_DURATION 10019
#endif
#ifndef MESSAGE_KEY_CFG_HINT
#define MESSAGE_KEY_CFG_HINT 10020
#endif

typedef enum {
  CFG_OP_BEGIN = 1,
  CFG_OP_TIMER = 2,
  CFG_OP_SEGMENT = 3,
  CFG_OP_VIBRATE = 4,
  CFG_OP_COMMIT = 5,
  CFG_OP_ERROR = 6,
} ConfigOp;

typedef enum {
  TRIGGER_NONE = 0,
  TRIGGER_TAP = 1,
  TRIGGER_SWIPE = 2,
} TriggerKind;

typedef enum {
  ZONE_NONE = 0,
  ZONE_LEFT = 1,
  ZONE_TOP = 2,
  ZONE_RIGHT = 3,
  ZONE_BOTTOM = 4,
  ZONE_CENTER = 5,
} TriggerZone;

typedef enum {
  VIBE_INTENSITY_NONE = 0,
  VIBE_INTENSITY_LOW = 1,
  VIBE_INTENSITY_MID = 2,
  VIBE_INTENSITY_HIGH = 3,
} VibeIntensity;

typedef enum {
  UP_ACTION_NONE = 0,
  UP_ACTION_SKIP = 1,
  UP_ACTION_HIDE = 2,
  UP_ACTION_MUTE = 3,
} UpAction;

typedef struct {
  VibeIntensity intensity;
  uint16_t duration_ms;
  uint16_t delay_ms;
} VibeStep;

typedef struct {
  char name[MAX_SEGMENT_NAME_LEN];
  char hint[MAX_HINT_LEN];
  uint64_t duration_ms;
  uint8_t vibe_count;
  VibeStep vibes[MAX_VIBE_STEPS];
} TimerSegment;

typedef struct {
  char name[MAX_NAME_LEN];
  bool repeat;
  bool iterations_enabled;
  bool must_acknowledge;
  UpAction on_press_up;
  UpAction on_long_press_up;
  uint16_t iterations;
  uint16_t repeat_pattern_delay_ms;
  uint16_t acknowledge_alert_duration_s;
  uint8_t finish_vibe_count;
  uint8_t segment_count;
  TriggerKind trigger_kind;
  TriggerZone trigger_from;
  TriggerZone trigger_to;
  VibeStep finish_vibes[MAX_VIBE_STEPS];
  TimerSegment *segments;
} TimerDefinition;

typedef struct __attribute__((__packed__)) {
  uint16_t version;
  uint8_t timer_count;
  uint8_t ui_flags;
} PersistConfigMeta;

typedef struct __attribute__((__packed__)) {
  uint8_t intensity;
  uint16_t duration_ms;
  uint16_t delay_ms;
} PersistVibeStep;

typedef struct __attribute__((__packed__)) {
  char name[MAX_NAME_LEN];
  uint8_t flags;
  uint8_t on_press_up;
  uint8_t on_long_press_up;
  uint16_t iterations;
  uint16_t repeat_pattern_delay_ms;
  uint16_t acknowledge_alert_duration_s;
  uint8_t finish_vibe_count;
  uint8_t segment_count;
  uint8_t trigger_kind;
  uint8_t trigger_from;
  uint8_t trigger_to;
  PersistVibeStep finish_vibes[MAX_VIBE_STEPS];
} PersistTimerRecord;

typedef struct __attribute__((__packed__)) {
  char name[MAX_SEGMENT_NAME_LEN];
  char hint[MAX_HINT_LEN];
  uint64_t duration_ms;
  uint8_t vibe_count;
  PersistVibeStep vibes[MAX_VIBE_STEPS];
} PersistSegmentRecord;

typedef struct {
  uint16_t version;
  uint8_t timer_count;
  bool icons_enabled;
  bool background_enabled;
  bool timer_accent_enabled;
  TimerDefinition timers[MAX_TIMERS];
} TimerConfig;

typedef struct {
  uint16_t version;
  bool active;
  bool running;
  bool completed;
  bool alert_fired;
  bool awaiting_ack;
  bool ack_silenced;
  uint8_t selected_timer;
  uint8_t active_timer;
  uint64_t started_at_ms;
  uint64_t paused_elapsed_ms;
  uint64_t ack_started_at_ms;
} TimerState;

typedef struct {
  uint8_t timer_count;
  bool icons_enabled;
  bool background_enabled;
  bool timer_accent_enabled;
  TimerDefinition timers[MAX_TIMERS];
} PendingConfig;

typedef struct {
  bool valid;
  bool completed;
  bool infinite;
  uint64_t elapsed_ms;
  uint64_t cycle_elapsed_ms;
  uint64_t cycle_duration_ms;
  uint64_t total_duration_ms;
  uint64_t total_remaining_ms;
  uint64_t phase_remaining_ms;
  uint16_t iteration_index;
  uint16_t iteration_count;
  uint8_t phase_index;
} TimerSnapshot;
