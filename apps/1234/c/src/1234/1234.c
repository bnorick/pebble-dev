#include <pebble.h>

/* Persistent storage keys */
static const int KEY_MODE       = 0;  // false = PM only, true = AM+PM

/* Alert times */
static const int MIN_ALERT  = 34;

/* Cookie values for wakeup reasons */
static const int COOKIE_AM = 0;
static const int COOKIE_PM = 1;

/* State */
static bool s_am_pm_mode;  // true = alert at both 12:34 AM and PM
static Window *s_window;
static TextLayer *s_title_layer;
static TextLayer *s_mode_layer;

/* Forward declarations */
static void prv_select_long_click(ClickRecognizerRef recognizer, void *context);
static void prv_schedule_all(void);
static void prv_cancel_all(void);
static void prv_do_alert(void);
static void prv_render(void);

/* ------------------------------------------------------------------ */
/*  Persistence                                                       */
/* ------------------------------------------------------------------ */

static void prv_persist_mode(void) {
  persist_write_bool(KEY_MODE, s_am_pm_mode);
}

static void prv_load_mode(void) {
  s_am_pm_mode = persist_read_bool(KEY_MODE);
}

/* ------------------------------------------------------------------ */
/*  Wakeup scheduling                                                 */
/* ------------------------------------------------------------------ */

/* Calculate the next timestamp for the given hour (0–23). */
static time_t prv_next_timestamp(int hour) {
  time_t now = time(NULL);
  struct tm *tick = localtime(&now);

  int target_hour = hour;
  int target_min = MIN_ALERT;

  /* If we already passed this time today, schedule for tomorrow. */
  if (tick->tm_hour > target_hour ||
      (tick->tm_hour == target_hour && tick->tm_min >= target_min)) {
    /* Build tomorrow's date */
    struct tm tomorrow = *tick;
    tomorrow.tm_hour = target_hour;
    tomorrow.tm_min = target_min;
    tomorrow.tm_sec = 0;
    time_t tomorrow_midnight = mktime(&tomorrow);
    /* Add one day */
    return tomorrow_midnight + 86400;
  }

  /* Schedule for today */
  struct tm target = *tick;
  target.tm_hour = target_hour;
  target.tm_min = target_min;
  target.tm_sec = 0;
  return mktime(&target);
}

static void prv_schedule_wakeup(int hour, int cookie) {
  time_t ts = prv_next_timestamp(hour);
  WakeupId id = wakeup_schedule(ts, cookie, true);
  if (id < 0) {
    APP_LOG(APP_LOG_LEVEL_ERROR, "Failed to schedule wakeup %d: %d", hour, id);
  }
}

static void prv_schedule_all(void) {
  prv_cancel_all();

  if (s_am_pm_mode) {
    /* 12:34 AM = hour 0 */
    prv_schedule_wakeup(0, COOKIE_AM);
    /* 12:34 PM = hour 12 */
    prv_schedule_wakeup(12, COOKIE_PM);
  } else {
    /* 12:34 PM only */
    prv_schedule_wakeup(12, COOKIE_PM);
  }
}

static void prv_cancel_all(void) {
  wakeup_cancel_all();
}

/* ------------------------------------------------------------------ */
/*  Vibration                                                         */
/* ------------------------------------------------------------------ */

// Vibration sequence
static const uint32_t vibe_sequence[] = {150, 200, 300, 200, 450, 200, 600};
static const VibePattern vibe_pattern = {
    .durations = vibe_sequence,
    .num_segments = ARRAY_LENGTH(vibe_sequence),
};

static void prv_do_alert(void) {
  vibes_enqueue_custom_pattern(vibe_pattern);
}

/* ------------------------------------------------------------------ */
/*  Wakeup handling                                                   */
/* ------------------------------------------------------------------ */

static void prv_wakeup_handler(WakeupId id, int32_t reason) {
  (void)id;
  (void)reason;
  prv_do_alert();
  prv_schedule_all();
}

/* ------------------------------------------------------------------ */
/*  UI                                                                */
/* ------------------------------------------------------------------ */

static void prv_render(void) {
  const char *mode_text = s_am_pm_mode ? "12:34 AM + PM" : "12:34 PM";
  text_layer_set_text(s_mode_layer, mode_text);
}

static void prv_click_config_provider(Window *window) {
  /* Long-press SELECT toggles mode */
  window_long_click_subscribe(BUTTON_ID_SELECT, 700, prv_select_long_click, NULL);
}

static void prv_select_long_click(ClickRecognizerRef recognizer, void *context)  {
  s_am_pm_mode = !s_am_pm_mode;
  prv_persist_mode();
  prv_schedule_all();
  prv_render();
}

static void prv_window_load(Window *window) {
  Layer *root = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(root);

  s_title_layer = text_layer_create(GRect(0, 20, bounds.size.w, 40));
  text_layer_set_text(s_title_layer, "12:34 Alert");
  text_layer_set_font(s_title_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28));
  text_layer_set_text_alignment(s_title_layer, GTextAlignmentCenter);
  text_layer_set_background_color(s_title_layer, GColorClear);
  layer_add_child(root, text_layer_get_layer(s_title_layer));

  s_mode_layer = text_layer_create(GRect(0, 60, bounds.size.w, 30));
  text_layer_set_font(s_mode_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18));
  text_layer_set_text_alignment(s_mode_layer, GTextAlignmentCenter);
  text_layer_set_background_color(s_mode_layer, GColorClear);
  layer_add_child(root, text_layer_get_layer(s_mode_layer));

  prv_render();
}

static void prv_window_unload(Window *window) {
  (void)window;
  text_layer_destroy(s_title_layer);
  text_layer_destroy(s_mode_layer);
}

/* ------------------------------------------------------------------ */
/*  App lifecycle                                                     */
/* ------------------------------------------------------------------ */

static void init(void) {
  prv_load_mode();

  /* Handle wakeup launch */
  if (launch_reason() == APP_LAUNCH_WAKEUP) {
    WakeupId id;
    int32_t reason;
    wakeup_get_launch_event(&id, &reason);
    prv_wakeup_handler(id, reason);
  } else {
    /* Normal launch — schedule wakeups */
    prv_schedule_all();
  }

  /* Subscribe for wakeups that occur while the app is open */
  wakeup_service_subscribe(prv_wakeup_handler);

  s_window = window_create();
  window_set_click_config_provider(s_window, (ClickConfigProvider) prv_click_config_provider);
  window_set_window_handlers(s_window, (WindowHandlers) {
    .load = prv_window_load,
    .unload = prv_window_unload,
  });
  window_stack_push(s_window, true);
}

static void deinit(void) {
  window_destroy(s_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
