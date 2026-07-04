#include "input.h"

#include <pebble.h>

#include "app_state.h"
#include "config.h"
#include "timer.h"
#include "thymer.h"
#include "ui.h"

#if defined(PBL_TOUCH)
static bool s_touch_tracking = false;
static int16_t s_touch_start_x = 0;
static int16_t s_touch_start_y = 0;
#endif

#if defined(DEBUG_TOUCH)
static const char *prv_trigger_kind_name(TriggerKind kind) {
  switch (kind) {
    case TRIGGER_TAP:
      return "tap";
    case TRIGGER_SWIPE:
      return "swipe";
    case TRIGGER_NONE:
    default:
      return "none";
  }
}

static const char *prv_zone_name(TriggerZone zone) {
  switch (zone) {
    case ZONE_LEFT:
      return "left";
    case ZONE_TOP:
      return "top";
    case ZONE_RIGHT:
      return "right";
    case ZONE_BOTTOM:
      return "bottom";
    case ZONE_CENTER:
      return "center";
    case ZONE_NONE:
    default:
      return "none";
  }
}

#define PRV_DEBUG_TOUCH_LOG(...) APP_LOG(APP_LOG_LEVEL_INFO, __VA_ARGS__)
#else
#define PRV_DEBUG_TOUCH_LOG(...) ((void)0)
#endif

static TriggerZone prv_zone_for_point(int16_t x, int16_t y, GRect bounds) {
  int16_t left = bounds.size.w / 4;
  int16_t right = bounds.size.w - left;
  int16_t top = bounds.size.h / 4;
  int16_t bottom = bounds.size.h - top;

  if (y <= top) return ZONE_TOP;
  if (y >= bottom) return ZONE_BOTTOM;
  if (x <= left) return ZONE_LEFT;
  if (x >= right) return ZONE_RIGHT;
  return ZONE_CENTER;
}

static bool prv_trigger_matches(const TimerDefinition *timer,
                                TriggerKind kind,
                                TriggerZone from,
                                TriggerZone to) {
  return timer->trigger_kind == kind &&
         timer->trigger_from == from &&
         timer->trigger_to == to;
}

static int prv_next_trigger_match(TriggerKind kind, TriggerZone from, TriggerZone to) {
  if (s_config.timer_count == 0) {
    return -1;
  }

  uint8_t start = s_state.selected_timer;
  if (start >= s_config.timer_count ||
      !prv_trigger_matches(&s_config.timers[start], kind, from, to)) {
    start = s_config.timer_count - 1;
  }

  for (uint8_t offset = 1; offset <= s_config.timer_count; ++offset) {
    uint8_t index = (uint8_t)((start + offset) % s_config.timer_count);
    if (prv_trigger_matches(&s_config.timers[index], kind, from, to)) {
      return index;
    }
  }

  return -1;
}

static bool prv_directional_swipe_for_delta(int16_t dx, int16_t dy,
                                            TriggerZone *from_out, TriggerZone *to_out) {
  if (!from_out || !to_out) {
    return false;
  }

  int16_t adx = dx < 0 ? -dx : dx;
  int16_t ady = dy < 0 ? -dy : dy;
  if (adx == 0 && ady == 0) {
    return false;
  }

  if (adx >= ady) {
    *from_out = dx >= 0 ? ZONE_LEFT : ZONE_RIGHT;
    *to_out = dx >= 0 ? ZONE_RIGHT : ZONE_LEFT;
  } else {
    *from_out = dy >= 0 ? ZONE_TOP : ZONE_BOTTOM;
    *to_out = dy >= 0 ? ZONE_BOTTOM : ZONE_TOP;
  }

  return true;
}

static void prv_handle_touch_gesture(TriggerKind kind, TriggerZone from, TriggerZone to) {
  ui_reveal_text_if_hidden();
  int next = prv_next_trigger_match(kind, from, to);
  PRV_DEBUG_TOUCH_LOG(
    "gesture kind=%s from=%s to=%s selected=%u next=%d active=%d running=%d awaiting_ack=%d",
    prv_trigger_kind_name(kind), prv_zone_name(from), prv_zone_name(to),
    (unsigned)s_state.selected_timer, next, s_state.active, s_state.running,
    s_state.awaiting_ack);
  if (next < 0) {
    return;
  }

  s_state.selected_timer = (uint8_t)next;
  s_selected_segment = 0;
  PRV_DEBUG_TOUCH_LOG("gesture matched timer=%u segment_reset=1",
                      (unsigned)s_state.selected_timer);
  config_persist_state();
  ui_refresh();
}

#if defined(PBL_TOUCH)
static void prv_touch_handler(const TouchEvent *event, void *context) {
  (void)context;
  Layer *window_layer = window_get_root_layer(ui_get_window());
  GRect bounds = layer_get_bounds(window_layer);

  switch (event->type) {
    case TouchEvent_Touchdown:
      s_touch_tracking = true;
      s_touch_start_x = event->x;
      s_touch_start_y = event->y;
      PRV_DEBUG_TOUCH_LOG(
        "touch down x=%d y=%d selected=%u active=%d running=%d awaiting_ack=%d text_hidden=%d",
        event->x, event->y, (unsigned)s_state.selected_timer, s_state.active,
        s_state.running, s_state.awaiting_ack, s_text_hidden);
      break;

    case TouchEvent_PositionUpdate:
      break;

    case TouchEvent_Liftoff: {
      if (!s_touch_tracking) {
        PRV_DEBUG_TOUCH_LOG("touch liftoff ignored tracking=0 x=%d y=%d", event->x, event->y);
        break;
      }
      s_touch_tracking = false;

      int16_t dx = event->x - s_touch_start_x;
      int16_t dy = event->y - s_touch_start_y;
      int16_t adx = dx < 0 ? -dx : dx;
      int16_t ady = dy < 0 ? -dy : dy;
      TriggerZone from = prv_zone_for_point(s_touch_start_x, s_touch_start_y, bounds);
      PRV_DEBUG_TOUCH_LOG(
        "touch up start=(%d,%d) end=(%d,%d) delta=(%d,%d) abs=(%d,%d) from=%s bounds=%dx%d",
        s_touch_start_x, s_touch_start_y, event->x, event->y, dx, dy, adx, ady,
        prv_zone_name(from), bounds.size.w, bounds.size.h);

      if (adx < 18 && ady < 18) {
        if (s_state.active && s_state.awaiting_ack) {
          PRV_DEBUG_TOUCH_LOG("touch classified=tap action=silence-ack from=%s",
                              prv_zone_name(from));
          timer_silence_acknowledgement(true);
          break;
        }
        PRV_DEBUG_TOUCH_LOG("touch classified=tap from=%s threshold=18",
                            prv_zone_name(from));
        prv_handle_touch_gesture(TRIGGER_TAP, from, ZONE_NONE);
        break;
      }

      TriggerZone to = prv_zone_for_point(event->x, event->y, bounds);
      if (to == from) {
        if (adx >= ady) {
          to = dx >= 0 ? ZONE_RIGHT : ZONE_LEFT;
        } else {
          to = dy >= 0 ? ZONE_BOTTOM : ZONE_TOP;
        }
      }
      PRV_DEBUG_TOUCH_LOG("touch classified=swipe from=%s to=%s",
                          prv_zone_name(from), prv_zone_name(to));

      int next = prv_next_trigger_match(TRIGGER_SWIPE, from, to);
      PRV_DEBUG_TOUCH_LOG("swipe direct-match from=%s to=%s next=%d",
                          prv_zone_name(from), prv_zone_name(to), next);
      if (next < 0) {
        TriggerZone directional_from = ZONE_NONE;
        TriggerZone directional_to = ZONE_NONE;
        if (prv_directional_swipe_for_delta(dx, dy, &directional_from, &directional_to) &&
            (directional_from != from || directional_to != to)) {
          PRV_DEBUG_TOUCH_LOG("swipe fallback from=%s to=%s original_from=%s original_to=%s",
                              prv_zone_name(directional_from), prv_zone_name(directional_to),
                              prv_zone_name(from), prv_zone_name(to));
          next = prv_next_trigger_match(TRIGGER_SWIPE, directional_from, directional_to);
          PRV_DEBUG_TOUCH_LOG("swipe fallback-match next=%d", next);
        }
      }
      if (next < 0) {
        PRV_DEBUG_TOUCH_LOG("swipe unmatched");
        break;
      }

      ui_reveal_text_if_hidden();
      s_state.selected_timer = (uint8_t)next;
      s_selected_segment = 0;
      PRV_DEBUG_TOUCH_LOG("swipe matched timer=%u segment_reset=1",
                          (unsigned)s_state.selected_timer);
      config_persist_state();
      ui_refresh();
      break;
    }
  }
}

void input_touch_subscribe(void) {
  touch_service_subscribe(prv_touch_handler, NULL);
}

void input_touch_unsubscribe(void) {
  touch_service_unsubscribe();
}
#endif

static void prv_select_click_handler(ClickRecognizerRef recognizer, void *context) {
  (void)recognizer;
  (void)context;
  if (!s_state.active || s_state.completed) {
    timer_start(s_state.selected_timer);
  } else if (s_state.awaiting_ack) {
    timer_dismiss_acknowledgement(true);
  } else if (s_state.running) {
    ui_reveal_text_if_hidden();
    timer_pause();
  } else {
    ui_reveal_text_if_hidden();
    timer_resume();
  }
}

static void prv_up_click_handler(ClickRecognizerRef recognizer, void *context) {
  (void)recognizer;
  (void)context;
  bool revealed = ui_reveal_text_if_hidden();
  UpAction action = timer_current_up_action(false);
  if (revealed && action == UP_ACTION_HIDE) {
    return;
  }
  (void)timer_handle_up_action(action);
}

static void prv_up_long_click_handler(ClickRecognizerRef recognizer, void *context) {
  (void)recognizer;
  (void)context;
  bool revealed = ui_reveal_text_if_hidden();
  UpAction action = timer_current_up_action(true);
  if (revealed && action == UP_ACTION_HIDE) {
    return;
  }
  (void)timer_handle_up_action(action);
}

static void prv_down_click_handler(ClickRecognizerRef recognizer, void *context) {
  (void)recognizer;
  (void)context;
  ui_reveal_text_if_hidden();
  timer_reset();
}

void input_click_config_provider(void *context) {
  (void)context;
  window_single_click_subscribe(BUTTON_ID_SELECT, prv_select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, prv_up_click_handler);
  window_long_click_subscribe(BUTTON_ID_UP, 700, prv_up_long_click_handler, NULL);
  window_single_click_subscribe(BUTTON_ID_DOWN, prv_down_click_handler);
}
