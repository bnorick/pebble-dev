#include "config.h"

#include <stdlib.h>

#include "app_state.h"
#include "input.h"
#include "timer.h"
#include "ui.h"
#include "util.h"

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

static uint32_t prv_timer_key(uint8_t timer_index) {
  return PERSIST_KEY_TIMER_BASE + timer_index;
}

static uint32_t prv_segment_key(uint8_t timer_index, uint8_t segment_index) {
  return PERSIST_KEY_SEGMENT_BASE + (timer_index * MAX_SEGMENTS) + segment_index;
}

static void prv_copy_vibe_to_persist(PersistVibeStep *dst, const VibeStep *src) {
  dst->intensity = (uint8_t)src->intensity;
  dst->duration_ms = src->duration_ms;
  dst->delay_ms = src->delay_ms;
}

static void prv_copy_vibe_from_persist(VibeStep *dst, const PersistVibeStep *src) {
  dst->intensity = (VibeIntensity)util_clamp_i32(src->intensity, VIBE_INTENSITY_NONE,
                                                 VIBE_INTENSITY_HIGH);
  dst->duration_ms = src->duration_ms;
  dst->delay_ms = src->delay_ms;
}

static void prv_copy_warning_to_persist(PersistSegmentWarning *dst, const SegmentWarning *src) {
  dst->time_before_end_ms = src->time_before_end_ms;
  dst->vibe_count = src->vibe_count;
  for (uint8_t i = 0; i < src->vibe_count && i < MAX_VIBE_STEPS; ++i) {
    prv_copy_vibe_to_persist(&dst->vibes[i], &src->vibes[i]);
  }
}

static void prv_copy_warning_from_persist(SegmentWarning *dst, const PersistSegmentWarning *src) {
  dst->time_before_end_ms = src->time_before_end_ms;
  dst->vibe_count = (uint8_t)util_clamp_i32(src->vibe_count, 0, MAX_VIBE_STEPS);
  for (uint8_t i = 0; i < dst->vibe_count; ++i) {
    prv_copy_vibe_from_persist(&dst->vibes[i], &src->vibes[i]);
  }
}

static void prv_reset_timer_definition(TimerDefinition *timer) {
  if (!timer) {
    return;
  }
  free(timer->segments);
  memset(timer, 0, sizeof(*timer));
}

static void prv_reset_timer_array(TimerDefinition *timers, uint8_t count) {
  if (!timers || count == 0) {
    return;
  }
  for (uint8_t i = 0; i < count; ++i) {
    prv_reset_timer_definition(&timers[i]);
  }
}

static void prv_reset_config(TimerConfig *config) {
  if (!config) {
    return;
  }
  prv_reset_timer_array(config->timers, config->timer_capacity);
  free(config->timers);
  memset(config, 0, sizeof(*config));
}

static void prv_reset_pending_config(PendingConfig *config) {
  if (!config) {
    return;
  }
  prv_reset_timer_array(config->timers, config->timer_capacity);
  free(config->timers);
  memset(config, 0, sizeof(*config));
}

static void prv_swap_configs(TimerConfig *a, TimerConfig *b) {
  if (!a || !b || a == b) {
    return;
  }

  TimerConfig tmp = *a;
  *a = *b;
  *b = tmp;
}

static bool prv_ensure_timer_capacity(TimerDefinition **timers,
                                      uint8_t *capacity,
                                      uint8_t required_count) {
  if (!timers || !capacity) {
    return false;
  }
  if (required_count == 0) {
    return true;
  }
  if (*capacity >= required_count && *timers) {
    return true;
  }

  TimerDefinition *resized = realloc(*timers, sizeof(TimerDefinition) * required_count);
  if (!resized) {
    APP_LOG(APP_LOG_LEVEL_ERROR, "timer allocation failed count=%u", (unsigned)required_count);
    return false;
  }
  if (required_count > *capacity) {
    memset(&resized[*capacity], 0, sizeof(TimerDefinition) * (required_count - *capacity));
  }
  *timers = resized;
  *capacity = required_count;
  return true;
}

static bool prv_allocate_segments(TimerDefinition *timer, uint8_t segment_count) {
  if (!timer) {
    return false;
  }

  timer->segments = NULL;
  timer->segment_count = 0;
  if (segment_count == 0) {
    return true;
  }

  timer->segments = calloc(segment_count, sizeof(TimerSegment));
  if (!timer->segments) {
    APP_LOG(APP_LOG_LEVEL_ERROR, "segment allocation failed count=%u", (unsigned)segment_count);
    return false;
  }

  timer->segment_count = segment_count;
  return true;
}

static bool prv_copy_timer_definition(TimerDefinition *dst, const TimerDefinition *src) {
  if (!dst || !src) {
    return false;
  }

  prv_reset_timer_definition(dst);
  util_copy_string(dst->name, sizeof(dst->name), src->name);
  dst->repeat = src->repeat;
  dst->iterations_enabled = src->iterations_enabled;
  dst->must_acknowledge = src->must_acknowledge;
  dst->stopwatch = src->stopwatch;
  dst->stopwatch_only = src->stopwatch_only;
  dst->on_press_up = src->on_press_up;
  dst->on_long_press_up = src->on_long_press_up;
  dst->on_long_press_select = src->on_long_press_select;
  dst->iterations = src->iterations;
  dst->repeat_pattern_delay_ms = src->repeat_pattern_delay_ms;
  dst->acknowledge_alert_duration_s = src->acknowledge_alert_duration_s;
  dst->finish_vibe_count = src->finish_vibe_count;
  dst->trigger_kind = src->trigger_kind;
  dst->trigger_from = src->trigger_from;
  dst->trigger_to = src->trigger_to;
  memcpy(dst->finish_vibes, src->finish_vibes, sizeof(dst->finish_vibes));

  if (src->segment_count == 0) {
    return true;
  }
  if (!src->segments) {
    APP_LOG(APP_LOG_LEVEL_ERROR, "copy timer missing segments count=%u",
            (unsigned)src->segment_count);
    return false;
  }
  if (!prv_allocate_segments(dst, src->segment_count)) {
    return false;
  }
  memcpy(dst->segments, src->segments, sizeof(TimerSegment) * src->segment_count);
  return true;
}

static bool prv_timer_segments_equal(const TimerDefinition *a, const TimerDefinition *b) {
  if (a->segment_count != b->segment_count) {
    return false;
  }
  if (a->segment_count == 0) {
    return true;
  }
  if (!a->segments || !b->segments) {
    return false;
  }

  for (uint8_t i = 0; i < a->segment_count; ++i) {
    const TimerSegment *left = &a->segments[i];
    const TimerSegment *right = &b->segments[i];
    if (strncmp(left->name, right->name, MAX_SEGMENT_NAME_LEN) != 0 ||
        strncmp(left->hint, right->hint, MAX_HINT_LEN) != 0 ||
        left->duration_ms != right->duration_ms ||
        left->vibe_count != right->vibe_count ||
        left->warn_count != right->warn_count) {
      return false;
    }
    for (uint8_t vibe_index = 0; vibe_index < left->vibe_count; ++vibe_index) {
      if (left->vibes[vibe_index].intensity != right->vibes[vibe_index].intensity ||
          left->vibes[vibe_index].duration_ms != right->vibes[vibe_index].duration_ms ||
          left->vibes[vibe_index].delay_ms != right->vibes[vibe_index].delay_ms) {
        return false;
      }
    }
    for (uint8_t warn_index = 0; warn_index < left->warn_count; ++warn_index) {
      const SegmentWarning *left_warn = &left->warns[warn_index];
      const SegmentWarning *right_warn = &right->warns[warn_index];
      if (left_warn->time_before_end_ms != right_warn->time_before_end_ms ||
          left_warn->vibe_count != right_warn->vibe_count) {
        return false;
      }
      for (uint8_t vibe_index = 0; vibe_index < left_warn->vibe_count; ++vibe_index) {
        if (left_warn->vibes[vibe_index].intensity != right_warn->vibes[vibe_index].intensity ||
            left_warn->vibes[vibe_index].duration_ms != right_warn->vibes[vibe_index].duration_ms ||
            left_warn->vibes[vibe_index].delay_ms != right_warn->vibes[vibe_index].delay_ms) {
          return false;
        }
      }
    }
  }

  return true;
}

static bool prv_timers_equal(const TimerDefinition *a, const TimerDefinition *b) {
  if (strncmp(a->name, b->name, MAX_NAME_LEN) != 0 ||
      a->repeat != b->repeat ||
      a->iterations_enabled != b->iterations_enabled ||
      a->must_acknowledge != b->must_acknowledge ||
      a->stopwatch != b->stopwatch ||
      a->stopwatch_only != b->stopwatch_only ||
      a->on_press_up.kind != b->on_press_up.kind ||
      a->on_press_up.duration_ms != b->on_press_up.duration_ms ||
      a->on_long_press_up.kind != b->on_long_press_up.kind ||
      a->on_long_press_up.duration_ms != b->on_long_press_up.duration_ms ||
      a->on_long_press_select.kind != b->on_long_press_select.kind ||
      a->on_long_press_select.duration_ms != b->on_long_press_select.duration_ms ||
      a->iterations != b->iterations ||
      a->repeat_pattern_delay_ms != b->repeat_pattern_delay_ms ||
      a->acknowledge_alert_duration_s != b->acknowledge_alert_duration_s ||
      a->finish_vibe_count != b->finish_vibe_count ||
      a->trigger_kind != b->trigger_kind ||
      a->trigger_from != b->trigger_from ||
      a->trigger_to != b->trigger_to) {
    return false;
  }

  for (uint8_t i = 0; i < a->finish_vibe_count; ++i) {
    if (a->finish_vibes[i].intensity != b->finish_vibes[i].intensity ||
        a->finish_vibes[i].duration_ms != b->finish_vibes[i].duration_ms ||
        a->finish_vibes[i].delay_ms != b->finish_vibes[i].delay_ms) {
      return false;
    }
  }

  return prv_timer_segments_equal(a, b);
}

static bool prv_configs_equal(const TimerConfig *a, const TimerConfig *b) {
  if (!a || !b) {
    return false;
  }
  if (a->version != b->version ||
      a->timer_count != b->timer_count ||
      a->icons_enabled != b->icons_enabled ||
      a->background_enabled != b->background_enabled ||
      a->timer_accent_enabled != b->timer_accent_enabled) {
    return false;
  }

  for (uint8_t i = 0; i < a->timer_count; ++i) {
    if (!prv_timers_equal(&a->timers[i], &b->timers[i])) {
      return false;
    }
  }
  return true;
}

static void prv_init_default_header(TimerConfig *config) {
  config->version = CONFIG_VERSION;
  config->icons_enabled = true;
  config->background_enabled = true;
  config->timer_accent_enabled = true;
}

static bool prv_set_default_timer(TimerDefinition *timer) {
  if (!timer) {
    return false;
  }

  prv_reset_timer_definition(timer);
  util_copy_string(timer->name, sizeof(timer->name), "Timer 1");
  timer->repeat = true;
  timer->iterations_enabled = false;
  timer->stopwatch = false;
  timer->stopwatch_only = false;
  timer->on_long_press_select.kind = UP_ACTION_HIDE;
  timer->iterations = 0;
  timer->repeat_pattern_delay_ms = DEFAULT_REPEAT_PATTERN_DELAY_MS;
  timer->acknowledge_alert_duration_s = DEFAULT_ACK_ALERT_DURATION_S;
  timer->trigger_kind = TRIGGER_TAP;
  timer->trigger_from = ZONE_TOP;
  timer->trigger_to = ZONE_NONE;

  if (!prv_allocate_segments(timer, 2)) {
    return false;
  }

  util_copy_string(timer->segments[0].name, sizeof(timer->segments[0].name), "far");
  timer->segments[0].duration_ms = 20000;
  timer->segments[0].vibe_count = 1;
  timer->segments[0].vibes[0].intensity = VIBE_INTENSITY_LOW;
  timer->segments[0].vibes[0].duration_ms = 100;
  timer->segments[0].vibes[0].delay_ms = 100;

  util_copy_string(timer->segments[1].name, sizeof(timer->segments[1].name), "near");
  timer->segments[1].duration_ms = 20000;
  timer->segments[1].vibe_count = 1;
  timer->segments[1].vibes[0].intensity = VIBE_INTENSITY_MID;
  timer->segments[1].vibes[0].duration_ms = 150;
  timer->segments[1].vibes[0].delay_ms = 100;
  return true;
}

static bool prv_try_load_persisted_config(TimerConfig *out, char *reason, size_t reason_len) {
  PersistConfigMeta meta = {0};

  prv_reset_config(out);
  if (!persist_exists(PERSIST_KEY_CONFIG_META)) {
    util_copy_string(reason, reason_len, "No persisted config key");
    APP_LOG(APP_LOG_LEVEL_INFO, "persist config missing meta key=%d", PERSIST_KEY_CONFIG_META);
    return false;
  }

  int meta_size = persist_read_data(PERSIST_KEY_CONFIG_META, &meta, sizeof(meta));
  if (meta_size != (int)sizeof(meta)) {
    snprintf(reason, reason_len, "Meta size %d != %u", meta_size, (unsigned)sizeof(meta));
    APP_LOG(APP_LOG_LEVEL_ERROR, "persist meta size mismatch read=%d expected=%u",
            meta_size, (unsigned)sizeof(meta));
    goto fail;
  }

  if (meta.version != CONFIG_VERSION) {
    snprintf(reason, reason_len, "Meta version %u != %u",
             (unsigned)meta.version, (unsigned)CONFIG_VERSION);
    APP_LOG(APP_LOG_LEVEL_ERROR, "persist meta version mismatch stored=%u current=%u",
            (unsigned)meta.version, (unsigned)CONFIG_VERSION);
    goto fail;
  }

  if (meta.timer_count == 0 || meta.timer_count > MAX_TIMERS) {
    snprintf(reason, reason_len, "Meta timer_count %u invalid", (unsigned)meta.timer_count);
    APP_LOG(APP_LOG_LEVEL_ERROR, "persist meta invalid timer_count=%u max=%u",
            (unsigned)meta.timer_count, (unsigned)MAX_TIMERS);
    goto fail;
  }

  out->version = CONFIG_VERSION;
  out->timer_count = meta.timer_count;
  out->timer_capacity = 0;
  bool legacy_ui_flags = (meta.ui_flags & ~(uint8_t)CONFIG_FLAG_ICONS) == 0;
  out->icons_enabled = (meta.ui_flags & CONFIG_FLAG_ICONS) != 0;
  out->background_enabled = legacy_ui_flags || (meta.ui_flags & CONFIG_FLAG_BACKGROUND) != 0;
  out->timer_accent_enabled = legacy_ui_flags || (meta.ui_flags & CONFIG_FLAG_TIMER_ACCENT) != 0;
  if (!prv_ensure_timer_capacity(&out->timers, &out->timer_capacity, meta.timer_count)) {
    snprintf(reason, reason_len, "Timer array allocation failed");
    goto fail;
  }

  for (uint8_t timer_index = 0; timer_index < meta.timer_count; ++timer_index) {
    PersistTimerRecord timer_record = {0};
    int timer_size = persist_read_data(prv_timer_key(timer_index), &timer_record,
                                       sizeof(timer_record));
    if (timer_size != (int)sizeof(timer_record)) {
      snprintf(reason, reason_len, "Timer %u size %d != %u",
               (unsigned)timer_index, timer_size, (unsigned)sizeof(timer_record));
      APP_LOG(APP_LOG_LEVEL_ERROR, "persist timer %u size mismatch read=%d expected=%u",
              (unsigned)timer_index, timer_size, (unsigned)sizeof(timer_record));
      goto fail;
    }

    if (timer_record.segment_count > MAX_SEGMENTS ||
        timer_record.finish_vibe_count > MAX_VIBE_STEPS) {
      snprintf(reason, reason_len, "Timer %u invalid counts", (unsigned)timer_index);
      APP_LOG(APP_LOG_LEVEL_ERROR,
              "persist timer %u invalid segment_count=%u finish_vibe_count=%u",
              (unsigned)timer_index, (unsigned)timer_record.segment_count,
              (unsigned)timer_record.finish_vibe_count);
      goto fail;
    }

    TimerDefinition *timer = &out->timers[timer_index];
    util_copy_string(timer->name, sizeof(timer->name), timer_record.name);
    timer->repeat = (timer_record.flags & TIMER_FLAG_REPEAT) != 0;
    timer->iterations_enabled = (timer_record.flags & TIMER_FLAG_ITERATIONS_ENABLED) != 0;
    timer->must_acknowledge = (timer_record.flags & TIMER_FLAG_MUST_ACKNOWLEDGE) != 0;
    timer->stopwatch = (timer_record.flags & TIMER_FLAG_STOPWATCH) != 0;
    timer->stopwatch_only = (timer_record.flags & TIMER_FLAG_STOPWATCH_ONLY) != 0;
    timer->on_press_up.kind = util_clamp_up_action(timer_record.on_press_up);
    timer->on_press_up.duration_ms = timer_record.on_press_up_duration_ms;
    timer->on_long_press_up.kind = util_clamp_up_action(timer_record.on_long_press_up);
    timer->on_long_press_up.duration_ms = timer_record.on_long_press_up_duration_ms;
    timer->on_long_press_select.kind = util_clamp_up_action(timer_record.on_long_press_select);
    timer->on_long_press_select.duration_ms = timer_record.on_long_press_select_duration_ms;
    timer->iterations = timer_record.iterations;
    timer->repeat_pattern_delay_ms = timer_record.repeat_pattern_delay_ms;
    timer->acknowledge_alert_duration_s = timer_record.acknowledge_alert_duration_s;
    timer->finish_vibe_count = timer_record.finish_vibe_count;
    timer->trigger_kind = (TriggerKind)util_clamp_i32(timer_record.trigger_kind, TRIGGER_NONE,
                                                      TRIGGER_SWIPE);
    timer->trigger_from = (TriggerZone)util_clamp_i32(timer_record.trigger_from, ZONE_NONE,
                                                      ZONE_CENTER);
    timer->trigger_to = (TriggerZone)util_clamp_i32(timer_record.trigger_to, ZONE_NONE,
                                                    ZONE_CENTER);
    for (uint8_t i = 0; i < timer->finish_vibe_count; ++i) {
      prv_copy_vibe_from_persist(&timer->finish_vibes[i], &timer_record.finish_vibes[i]);
    }

    if (!prv_allocate_segments(timer, timer_record.segment_count)) {
      snprintf(reason, reason_len, "Timer %u allocation failed", (unsigned)timer_index);
      goto fail;
    }

    for (uint8_t segment_index = 0; segment_index < timer->segment_count; ++segment_index) {
      PersistSegmentRecord segment_record = {0};
      int segment_size = persist_read_data(prv_segment_key(timer_index, segment_index),
                                           &segment_record, sizeof(segment_record));
      if (segment_size != (int)sizeof(segment_record)) {
        snprintf(reason, reason_len, "Seg %u/%u size %d != %u",
                 (unsigned)timer_index, (unsigned)segment_index,
                 segment_size, (unsigned)sizeof(segment_record));
        APP_LOG(APP_LOG_LEVEL_ERROR, "persist segment %u/%u size mismatch read=%d expected=%u",
                (unsigned)timer_index, (unsigned)segment_index,
                segment_size, (unsigned)sizeof(segment_record));
        goto fail;
      }

      if (segment_record.vibe_count > MAX_VIBE_STEPS ||
          segment_record.warn_count > MAX_WARN_ATS) {
        snprintf(reason, reason_len, "Seg %u/%u invalid vibe_count",
                 (unsigned)timer_index, (unsigned)segment_index);
        APP_LOG(APP_LOG_LEVEL_ERROR, "persist segment %u/%u invalid vibe_count=%u warn_count=%u",
                (unsigned)timer_index, (unsigned)segment_index,
                (unsigned)segment_record.vibe_count, (unsigned)segment_record.warn_count);
        goto fail;
      }

      TimerSegment *segment = &timer->segments[segment_index];
      util_copy_string(segment->name, sizeof(segment->name), segment_record.name);
      util_copy_string(segment->hint, sizeof(segment->hint), segment_record.hint);
      segment->duration_ms = segment_record.duration_ms;
      segment->vibe_count = segment_record.vibe_count;
      segment->warn_count = segment_record.warn_count;
      for (uint8_t i = 0; i < segment->vibe_count; ++i) {
        prv_copy_vibe_from_persist(&segment->vibes[i], &segment_record.vibes[i]);
      }
      for (uint8_t i = 0; i < segment->warn_count; ++i) {
        prv_copy_warning_from_persist(&segment->warns[i], &segment_record.warns[i]);
      }
    }
  }

  util_copy_string(reason, reason_len, "Persisted config OK");
  APP_LOG(APP_LOG_LEVEL_INFO,
          "persist config ok version=%u timer_count=%u meta_size=%u timer_size=%u segment_size=%u",
          (unsigned)meta.version, (unsigned)meta.timer_count,
          (unsigned)sizeof(meta), (unsigned)sizeof(PersistTimerRecord),
          (unsigned)sizeof(PersistSegmentRecord));
  return true;

fail:
  prv_reset_config(out);
  return false;
}

bool config_has_persisted_config(void) {
  return prv_try_load_persisted_config(&s_candidate_config, s_persist_debug_reason,
                                       sizeof(s_persist_debug_reason));
}

void config_deinit(void) {
  prv_reset_config(&s_config);
  prv_reset_config(&s_candidate_config);
  prv_reset_pending_config(&s_pending_config);
}

void config_default_config(void) {
  prv_reset_config(&s_config);
  prv_init_default_header(&s_config);
  if (!prv_ensure_timer_capacity(&s_config.timers, &s_config.timer_capacity, 1)) {
    return;
  }
  s_config.timer_count = 1;
  if (!prv_set_default_timer(&s_config.timers[0])) {
    s_config.timer_count = 0;
  }
}

void config_default_state(void) {
  memset(&s_state, 0, sizeof(s_state));
  s_state.version = CONFIG_VERSION;
  s_state.selected_timer = 0;
}

void config_persist_config(void) {
  PersistConfigMeta meta = {
    .version = CONFIG_VERSION,
    .timer_count = s_config.timer_count,
    .ui_flags = (s_config.icons_enabled ? CONFIG_FLAG_ICONS : 0) |
                (s_config.background_enabled ? CONFIG_FLAG_BACKGROUND : 0) |
                (s_config.timer_accent_enabled ? CONFIG_FLAG_TIMER_ACCENT : 0),
  };
  persist_write_data(PERSIST_KEY_CONFIG_META, &meta, sizeof(meta));

  for (uint8_t timer_index = 0; timer_index < MAX_TIMERS; ++timer_index) {
    if (timer_index < s_config.timer_count) {
      const TimerDefinition *timer = &s_config.timers[timer_index];
      PersistTimerRecord timer_record;
      memset(&timer_record, 0, sizeof(timer_record));
      util_copy_string(timer_record.name, sizeof(timer_record.name), timer->name);
      timer_record.flags = (timer->repeat ? TIMER_FLAG_REPEAT : 0) |
                           (timer->iterations_enabled ? TIMER_FLAG_ITERATIONS_ENABLED : 0) |
                           (timer->must_acknowledge ? TIMER_FLAG_MUST_ACKNOWLEDGE : 0) |
                           (timer->stopwatch ? TIMER_FLAG_STOPWATCH : 0) |
                           (timer->stopwatch_only ? TIMER_FLAG_STOPWATCH_ONLY : 0);
      timer_record.on_press_up = (uint8_t)timer->on_press_up.kind;
      timer_record.on_press_up_duration_ms = timer->on_press_up.duration_ms;
      timer_record.on_long_press_up = (uint8_t)timer->on_long_press_up.kind;
      timer_record.on_long_press_up_duration_ms = timer->on_long_press_up.duration_ms;
      timer_record.on_long_press_select = (uint8_t)timer->on_long_press_select.kind;
      timer_record.on_long_press_select_duration_ms = timer->on_long_press_select.duration_ms;
      timer_record.iterations = timer->iterations;
      timer_record.repeat_pattern_delay_ms = timer->repeat_pattern_delay_ms;
      timer_record.acknowledge_alert_duration_s = timer->acknowledge_alert_duration_s;
      timer_record.finish_vibe_count = timer->finish_vibe_count;
      timer_record.segment_count = timer->segment_count;
      timer_record.trigger_kind = (uint8_t)timer->trigger_kind;
      timer_record.trigger_from = (uint8_t)timer->trigger_from;
      timer_record.trigger_to = (uint8_t)timer->trigger_to;
      for (uint8_t i = 0; i < timer->finish_vibe_count; ++i) {
        prv_copy_vibe_to_persist(&timer_record.finish_vibes[i], &timer->finish_vibes[i]);
      }
      persist_write_data(prv_timer_key(timer_index), &timer_record, sizeof(timer_record));

      for (uint8_t segment_index = 0; segment_index < timer->segment_count; ++segment_index) {
        uint32_t key = prv_segment_key(timer_index, segment_index);
        const TimerSegment *segment = &timer->segments[segment_index];
        PersistSegmentRecord segment_record;
        memset(&segment_record, 0, sizeof(segment_record));
        util_copy_string(segment_record.name, sizeof(segment_record.name), segment->name);
        util_copy_string(segment_record.hint, sizeof(segment_record.hint), segment->hint);
        segment_record.duration_ms = segment->duration_ms;
        segment_record.vibe_count = segment->vibe_count;
        segment_record.warn_count = segment->warn_count;
        for (uint8_t i = 0; i < segment->vibe_count; ++i) {
          prv_copy_vibe_to_persist(&segment_record.vibes[i], &segment->vibes[i]);
        }
        for (uint8_t i = 0; i < segment->warn_count; ++i) {
          prv_copy_warning_to_persist(&segment_record.warns[i], &segment->warns[i]);
        }
        persist_write_data(key, &segment_record, sizeof(segment_record));
      }

      for (uint8_t segment_index = timer->segment_count; segment_index < MAX_SEGMENTS;
           ++segment_index) {
        uint32_t key = prv_segment_key(timer_index, segment_index);
        if (persist_exists(key)) {
          persist_delete(key);
        }
      }
    } else {
      uint32_t timer_key = prv_timer_key(timer_index);
      if (persist_exists(timer_key)) {
        persist_delete(timer_key);
      }
      for (uint8_t segment_index = 0; segment_index < MAX_SEGMENTS; ++segment_index) {
        uint32_t key = prv_segment_key(timer_index, segment_index);
        if (persist_exists(key)) {
          persist_delete(key);
        }
      }
    }
  }
}

void config_persist_state(void) {
  persist_write_data(PERSIST_KEY_STATE, &s_state, sizeof(s_state));
}

void config_load(void) {
  prv_reset_config(&s_candidate_config);
  if (prv_try_load_persisted_config(&s_config, s_persist_debug_reason,
                                    sizeof(s_persist_debug_reason))) {
    return;
  }
  config_default_config();
}

void config_load_state(void) {
  if (persist_exists(PERSIST_KEY_STATE) &&
      persist_read_data(PERSIST_KEY_STATE, &s_state, sizeof(s_state)) == sizeof(s_state) &&
      s_state.version == CONFIG_VERSION) {
    if (s_state.selected_timer >= s_config.timer_count) {
      s_state.selected_timer = 0;
    }
    if (s_state.active_timer >= s_config.timer_count) {
      s_state.active = false;
      s_state.running = false;
      s_state.completed = false;
      s_state.active_stopwatch = false;
    }
    return;
  }
  config_default_state();
}

static void prv_reset_runtime_for_new_config(void) {
  timer_cancel_refresh_timer();
  timer_cancel_ack_timer();
  timer_cancel_wakeup();
  vibes_cancel();

  memset(&s_state, 0, sizeof(s_state));
  s_state.version = CONFIG_VERSION;

  timer_reset_phase_tracking();
  s_show_config_notice = false;
  s_selected_segment = 0;
  s_text_hidden = false;
}

static void prv_build_default_candidate(TimerConfig *config) {
  prv_reset_config(config);
  prv_init_default_header(config);
  if (!prv_ensure_timer_capacity(&config->timers, &config->timer_capacity, 1)) {
    return;
  }
  config->timer_count = 1;
  if (!prv_set_default_timer(&config->timers[0])) {
    config->timer_count = 0;
  }
}

static bool prv_build_config_from_pending(TimerConfig *config) {
  prv_reset_config(config);
  config->version = CONFIG_VERSION;
  config->icons_enabled = s_pending_config.icons_enabled;
  config->background_enabled = s_pending_config.background_enabled;
  config->timer_accent_enabled = s_pending_config.timer_accent_enabled;
  config->timer_count = s_pending_config.timer_count;
  if (!prv_ensure_timer_capacity(&config->timers, &config->timer_capacity, config->timer_count)) {
    prv_build_default_candidate(config);
    return false;
  }

  for (uint8_t timer_index = 0; timer_index < s_pending_config.timer_count; ++timer_index) {
    if (!prv_copy_timer_definition(&config->timers[timer_index],
                                   &s_pending_config.timers[timer_index])) {
      prv_build_default_candidate(config);
      return false;
    }
  }

  if (config->timer_count == 0) {
    prv_build_default_candidate(config);
  }
  return true;
}

static void prv_apply_config_from_pending(bool show_notice) {
  (void)prv_build_config_from_pending(&s_candidate_config);

  bool changed = !prv_configs_equal(&s_config, &s_candidate_config);
  s_waiting_for_initial_config = false;
  prv_reset_pending_config(&s_pending_config);
  if (!changed) {
    prv_reset_config(&s_candidate_config);
    return;
  }

  prv_reset_runtime_for_new_config();
  prv_swap_configs(&s_config, &s_candidate_config);
  prv_reset_config(&s_candidate_config);
  config_persist_config();
  config_persist_state();
  ui_refresh_background_layers();
  if (show_notice) {
    ui_show_config_notice();
  }
}

static void prv_apply_ui_flags(uint8_t ui_flags) {
  bool icons_enabled = (ui_flags & CONFIG_FLAG_ICONS) != 0;
  bool background_enabled = (ui_flags & CONFIG_FLAG_BACKGROUND) != 0;
  bool timer_accent_enabled = (ui_flags & CONFIG_FLAG_TIMER_ACCENT) != 0;

  if (s_config.icons_enabled == icons_enabled &&
      s_config.background_enabled == background_enabled &&
      s_config.timer_accent_enabled == timer_accent_enabled) {
    return;
  }

  s_config.icons_enabled = icons_enabled;
  s_config.background_enabled = background_enabled;
  s_config.timer_accent_enabled = timer_accent_enabled;
  config_persist_config();
  ui_refresh_background_layers();
  ui_refresh();
}

void config_send_request(void) {
  DictionaryIterator *iter = NULL;
  if (app_message_outbox_begin(&iter) != APP_MSG_OK || !iter) {
    return;
  }
  dict_write_uint8(iter, MESSAGE_KEY_REQUEST_CONFIG, 1);
  app_message_outbox_send();
}

void config_inbox_received(DictionaryIterator *iter, void *context) {
  (void)context;
  Tuple *op_tuple = dict_find(iter, MESSAGE_KEY_CFG_OP);
  if (!op_tuple) {
#if defined(SCREENSHOT_SUPPORT)
    Tuple *kind_tuple = dict_find(iter, MESSAGE_KEY_CFG_TRIGGER_KIND);
    Tuple *from_tuple = dict_find(iter, MESSAGE_KEY_CFG_TRIGGER_FROM);
    Tuple *to_tuple = dict_find(iter, MESSAGE_KEY_CFG_TRIGGER_TO);
    if (kind_tuple && from_tuple) {
      TriggerKind kind = (TriggerKind)util_clamp_i32(kind_tuple->value->int32, TRIGGER_NONE,
                                                     TRIGGER_SWIPE);
      TriggerZone from = (TriggerZone)util_clamp_i32(from_tuple->value->int32, ZONE_NONE,
                                                     ZONE_CENTER);
      TriggerZone to = to_tuple
        ? (TriggerZone)util_clamp_i32(to_tuple->value->int32, ZONE_NONE, ZONE_CENTER)
        : ZONE_NONE;
      (void)input_select_timer_for_trigger(kind, from, to);
    }
#endif
    return;
  }

  int32_t op = op_tuple->value->int32;
  if (op == CFG_OP_BEGIN) {
    prv_reset_pending_config(&s_pending_config);
    s_pending_config.icons_enabled = true;
    s_pending_config.background_enabled = true;
    s_pending_config.timer_accent_enabled = true;
    Tuple *count_tuple = dict_find(iter, MESSAGE_KEY_CFG_TIMER);
    Tuple *ui_flags_tuple = dict_find(iter, MESSAGE_KEY_CFG_UI_FLAGS);
    if (count_tuple) {
      s_pending_config.timer_count = (uint8_t)util_clamp_i32(count_tuple->value->int32,
                                                             0, MAX_TIMERS);
      if (!prv_ensure_timer_capacity(&s_pending_config.timers,
                                     &s_pending_config.timer_capacity,
                                     s_pending_config.timer_count)) {
        s_pending_config.timer_count = 0;
      }
    }
    if (ui_flags_tuple) {
      s_pending_config.icons_enabled = (ui_flags_tuple->value->int32 & CONFIG_FLAG_ICONS) != 0;
      s_pending_config.background_enabled =
        (ui_flags_tuple->value->int32 & CONFIG_FLAG_BACKGROUND) != 0;
      s_pending_config.timer_accent_enabled =
        (ui_flags_tuple->value->int32 & CONFIG_FLAG_TIMER_ACCENT) != 0;
    }
    return;
  }

  if (op == CFG_OP_UI) {
    Tuple *ui_flags_tuple = dict_find(iter, MESSAGE_KEY_CFG_UI_FLAGS);
    if (!ui_flags_tuple) {
      return;
    }
    prv_apply_ui_flags((uint8_t)ui_flags_tuple->value->int32);
    return;
  }

  if (op == CFG_OP_TIMER) {
    Tuple *timer_tuple = dict_find(iter, MESSAGE_KEY_CFG_TIMER);
    Tuple *flags_tuple = dict_find(iter, MESSAGE_KEY_CFG_FLAGS);
    Tuple *iter_tuple = dict_find(iter, MESSAGE_KEY_CFG_ITER);
    Tuple *kind_tuple = dict_find(iter, MESSAGE_KEY_CFG_TRIGGER_KIND);
    Tuple *from_tuple = dict_find(iter, MESSAGE_KEY_CFG_TRIGGER_FROM);
    Tuple *to_tuple = dict_find(iter, MESSAGE_KEY_CFG_TRIGGER_TO);
    Tuple *segment_count_tuple = dict_find(iter, MESSAGE_KEY_CFG_SEGMENT);
    Tuple *text_tuple = dict_find(iter, MESSAGE_KEY_CFG_TEXT);
    Tuple *alert_tuple = dict_find(iter, MESSAGE_KEY_CFG_ALERT);
    Tuple *repeat_pattern_delay_tuple = dict_find(iter, MESSAGE_KEY_CFG_REPEAT_PATTERN_DELAY);
    Tuple *ack_duration_tuple = dict_find(iter, MESSAGE_KEY_CFG_ACK_DURATION);
    Tuple *up_action_tuple = dict_find(iter, MESSAGE_KEY_CFG_UP_ACTION);
    Tuple *up_long_action_tuple = dict_find(iter, MESSAGE_KEY_CFG_UP_LONG_ACTION);
    Tuple *select_long_action_tuple = dict_find(iter, MESSAGE_KEY_CFG_SELECT_LONG_ACTION);
    Tuple *up_action_time_tuple = dict_find(iter, MESSAGE_KEY_CFG_UP_ACTION_TIME);
    Tuple *up_long_action_time_tuple = dict_find(iter, MESSAGE_KEY_CFG_UP_LONG_ACTION_TIME);
    Tuple *select_long_action_time_tuple = dict_find(iter, MESSAGE_KEY_CFG_SELECT_LONG_ACTION_TIME);
    if (!timer_tuple) {
      return;
    }
    uint8_t index = (uint8_t)timer_tuple->value->int32;
    if (index >= MAX_TIMERS) {
      return;
    }
    if (!prv_ensure_timer_capacity(&s_pending_config.timers,
                                   &s_pending_config.timer_capacity,
                                   index + 1)) {
      return;
    }
    uint8_t segment_count = segment_count_tuple
      ? (uint8_t)util_clamp_i32(segment_count_tuple->value->int32, 0, MAX_SEGMENTS) : 0;
    TimerDefinition *timer = &s_pending_config.timers[index];
    prv_reset_timer_definition(timer);
    if (!prv_allocate_segments(timer, segment_count)) {
      return;
    }
    timer->repeat = flags_tuple ? ((flags_tuple->value->int32 & TIMER_FLAG_REPEAT) != 0) : false;
    timer->iterations_enabled = flags_tuple
      ? ((flags_tuple->value->int32 & TIMER_FLAG_ITERATIONS_ENABLED) != 0) : false;
    timer->must_acknowledge = flags_tuple
      ? ((flags_tuple->value->int32 & TIMER_FLAG_MUST_ACKNOWLEDGE) != 0) : false;
    timer->stopwatch = flags_tuple
      ? ((flags_tuple->value->int32 & TIMER_FLAG_STOPWATCH) != 0) : false;
    timer->stopwatch_only = flags_tuple
      ? ((flags_tuple->value->int32 & TIMER_FLAG_STOPWATCH_ONLY) != 0) : false;
    timer->on_press_up.kind = up_action_tuple
      ? util_clamp_up_action(up_action_tuple->value->int32) : UP_ACTION_NONE;
    timer->on_press_up.duration_ms = 0;
    (void)util_read_uint64_tuple(up_action_time_tuple, &timer->on_press_up.duration_ms);
    timer->on_long_press_up.kind = up_long_action_tuple
      ? util_clamp_up_action(up_long_action_tuple->value->int32) : UP_ACTION_NONE;
    timer->on_long_press_up.duration_ms = 0;
    (void)util_read_uint64_tuple(up_long_action_time_tuple, &timer->on_long_press_up.duration_ms);
    timer->on_long_press_select.kind = select_long_action_tuple
      ? util_clamp_up_action(select_long_action_tuple->value->int32) : UP_ACTION_HIDE;
    timer->on_long_press_select.duration_ms = 0;
    (void)util_read_uint64_tuple(select_long_action_time_tuple,
                                 &timer->on_long_press_select.duration_ms);
    timer->iterations = iter_tuple
      ? (uint16_t)util_clamp_i32(iter_tuple->value->int32, 0, 65535) : 0;
    timer->repeat_pattern_delay_ms = repeat_pattern_delay_tuple
      ? (uint16_t)util_clamp_i32(repeat_pattern_delay_tuple->value->int32, 0, 65535)
      : DEFAULT_REPEAT_PATTERN_DELAY_MS;
    timer->acknowledge_alert_duration_s = ack_duration_tuple
      ? (uint16_t)util_clamp_i32(ack_duration_tuple->value->int32, 0, 65535)
      : DEFAULT_ACK_ALERT_DURATION_S;
    timer->trigger_kind = kind_tuple ? (TriggerKind)kind_tuple->value->int32 : TRIGGER_NONE;
    timer->trigger_from = from_tuple ? (TriggerZone)from_tuple->value->int32 : ZONE_NONE;
    timer->trigger_to = to_tuple ? (TriggerZone)to_tuple->value->int32 : ZONE_NONE;
    timer->finish_vibe_count = alert_tuple
      ? (uint8_t)util_clamp_i32(alert_tuple->value->int32, 0, MAX_VIBE_STEPS) : 0;
    if (text_tuple && text_tuple->type == TUPLE_CSTRING) {
      util_copy_string(timer->name, sizeof(timer->name), text_tuple->value->cstring);
    }
    if (index + 1 > s_pending_config.timer_count) {
      s_pending_config.timer_count = index + 1;
    }
    PRV_DEBUG_TOUCH_LOG(
      "cfg timer index=%u name=%s trigger=%s from=%s to=%s segments=%u repeat=%d iterations=%u",
      (unsigned)index, timer->name[0] ? timer->name : "(unnamed)",
      prv_trigger_kind_name(timer->trigger_kind), prv_zone_name(timer->trigger_from),
      prv_zone_name(timer->trigger_to), (unsigned)timer->segment_count, timer->repeat,
      (unsigned)timer->iterations);
    return;
  }

  if (op == CFG_OP_SEGMENT) {
    Tuple *timer_tuple = dict_find(iter, MESSAGE_KEY_CFG_TIMER);
    Tuple *segment_tuple = dict_find(iter, MESSAGE_KEY_CFG_SEGMENT);
    Tuple *duration_tuple = dict_find(iter, MESSAGE_KEY_CFG_DURATION);
    Tuple *text_tuple = dict_find(iter, MESSAGE_KEY_CFG_TEXT);
    Tuple *hint_tuple = dict_find(iter, MESSAGE_KEY_CFG_HINT);
    Tuple *alert_tuple = dict_find(iter, MESSAGE_KEY_CFG_ALERT);
    Tuple *warn_tuple = dict_find(iter, MESSAGE_KEY_CFG_WARN);
    if (!timer_tuple || !segment_tuple || !duration_tuple) {
      return;
    }
    uint8_t timer_index = (uint8_t)timer_tuple->value->int32;
    uint8_t segment_index = (uint8_t)segment_tuple->value->int32;
    if (timer_index >= MAX_TIMERS || timer_index >= s_pending_config.timer_capacity ||
        !s_pending_config.timers) {
      return;
    }
    TimerDefinition *timer = &s_pending_config.timers[timer_index];
    if (segment_index >= timer->segment_count || !timer->segments) {
      return;
    }
    uint64_t duration_ms = 0;
    if (!util_read_uint64_tuple(duration_tuple, &duration_ms) || duration_ms < 1) {
      return;
    }
    TimerSegment *segment = &timer->segments[segment_index];
    segment->duration_ms = duration_ms;
    segment->vibe_count = alert_tuple
      ? (uint8_t)util_clamp_i32(alert_tuple->value->int32, 0, MAX_VIBE_STEPS) : 0;
    segment->warn_count = warn_tuple
      ? (uint8_t)util_clamp_i32(warn_tuple->value->int32, 0, MAX_WARN_ATS) : 0;
    if (text_tuple && text_tuple->type == TUPLE_CSTRING) {
      util_copy_string(segment->name, sizeof(segment->name), text_tuple->value->cstring);
    }
    if (hint_tuple && hint_tuple->type == TUPLE_CSTRING) {
      util_copy_string(segment->hint, sizeof(segment->hint), hint_tuple->value->cstring);
    }
    return;
  }

  if (op == CFG_OP_WARN) {
    Tuple *timer_tuple = dict_find(iter, MESSAGE_KEY_CFG_TIMER);
    Tuple *segment_tuple = dict_find(iter, MESSAGE_KEY_CFG_SEGMENT);
    Tuple *warn_tuple = dict_find(iter, MESSAGE_KEY_CFG_WARN);
    Tuple *warn_time_tuple = dict_find(iter, MESSAGE_KEY_CFG_WARN_TIME);
    Tuple *alert_tuple = dict_find(iter, MESSAGE_KEY_CFG_ALERT);
    if (!timer_tuple || !segment_tuple || !warn_tuple || !warn_time_tuple) {
      return;
    }
    uint8_t timer_index = (uint8_t)timer_tuple->value->int32;
    uint8_t segment_index = (uint8_t)segment_tuple->value->int32;
    uint8_t warn_index = (uint8_t)warn_tuple->value->int32;
    if (timer_index >= MAX_TIMERS || warn_index >= MAX_WARN_ATS ||
        timer_index >= s_pending_config.timer_capacity || !s_pending_config.timers) {
      return;
    }
    TimerDefinition *timer = &s_pending_config.timers[timer_index];
    if (segment_index >= timer->segment_count || !timer->segments) {
      return;
    }
    TimerSegment *segment = &timer->segments[segment_index];
    if (warn_index >= segment->warn_count) {
      return;
    }
    SegmentWarning *warn = &segment->warns[warn_index];
    uint64_t time_before_end_ms = 0;
    if (!util_read_uint64_tuple(warn_time_tuple, &time_before_end_ms) ||
        time_before_end_ms < 1 || time_before_end_ms >= segment->duration_ms) {
      return;
    }
    warn->time_before_end_ms = time_before_end_ms;
    warn->vibe_count = alert_tuple
      ? (uint8_t)util_clamp_i32(alert_tuple->value->int32, 0, MAX_VIBE_STEPS) : 0;
    return;
  }

  if (op == CFG_OP_VIBRATE) {
    Tuple *timer_tuple = dict_find(iter, MESSAGE_KEY_CFG_TIMER);
    Tuple *segment_tuple = dict_find(iter, MESSAGE_KEY_CFG_SEGMENT);
    Tuple *alert_tuple = dict_find(iter, MESSAGE_KEY_CFG_ALERT);
    Tuple *intensity_tuple = dict_find(iter, MESSAGE_KEY_CFG_INTENSITY);
    Tuple *duration_tuple = dict_find(iter, MESSAGE_KEY_CFG_DURATION);
    Tuple *delay_tuple = dict_find(iter, MESSAGE_KEY_CFG_DELAY);
    Tuple *warn_tuple = dict_find(iter, MESSAGE_KEY_CFG_WARN);
    if (!timer_tuple || !segment_tuple || !alert_tuple || !intensity_tuple || !duration_tuple) {
      return;
    }
    uint8_t timer_index = (uint8_t)timer_tuple->value->int32;
    uint8_t segment_index = (uint8_t)segment_tuple->value->int32;
    uint8_t alert_index = (uint8_t)alert_tuple->value->int32;
    if (timer_index >= MAX_TIMERS || alert_index >= MAX_VIBE_STEPS ||
        timer_index >= s_pending_config.timer_capacity || !s_pending_config.timers) {
      return;
    }
    VibeStep *step = NULL;
    if (warn_tuple) {
      uint8_t warn_index = (uint8_t)warn_tuple->value->int32;
      TimerDefinition *timer = &s_pending_config.timers[timer_index];
      if (warn_index >= MAX_WARN_ATS ||
          segment_index >= timer->segment_count || !timer->segments) {
        return;
      }
      TimerSegment *segment = &timer->segments[segment_index];
      if (warn_index >= segment->warn_count) {
        return;
      }
      SegmentWarning *warn = &segment->warns[warn_index];
      if (alert_index >= warn->vibe_count) {
        return;
      }
      step = &warn->vibes[alert_index];
    } else if (segment_index == FINISH_VIBE_SEGMENT) {
      step = &s_pending_config.timers[timer_index].finish_vibes[alert_index];
    } else {
      TimerDefinition *timer = &s_pending_config.timers[timer_index];
      if (segment_index >= timer->segment_count || !timer->segments) {
        return;
      }
      step = &timer->segments[segment_index].vibes[alert_index];
    }
    step->intensity = (VibeIntensity)util_clamp_i32(intensity_tuple->value->int32,
                                                    VIBE_INTENSITY_LOW,
                                                    VIBE_INTENSITY_HIGH);
    step->duration_ms = (uint16_t)util_clamp_i32(duration_tuple->value->int32, 1, 10000);
    step->delay_ms = delay_tuple
      ? (uint16_t)util_clamp_i32(delay_tuple->value->int32, 0, 10000) : 100;
    return;
  }

  if (op == CFG_OP_COMMIT) {
    bool show_notice = !s_waiting_for_initial_config;
    prv_apply_config_from_pending(show_notice);
    ui_refresh();
    return;
  }

  if (op == CFG_OP_ERROR) {
    s_waiting_for_initial_config = false;
    Tuple *error_tuple = dict_find(iter, MESSAGE_KEY_CFG_ERROR);
    if (error_tuple && error_tuple->type == TUPLE_CSTRING) {
      APP_LOG(APP_LOG_LEVEL_ERROR, "Config error: %s", error_tuple->value->cstring);
    }
  }
}

void config_inbox_dropped(AppMessageResult reason, void *context) {
  (void)context;
  APP_LOG(APP_LOG_LEVEL_ERROR, "Inbox dropped: %d", reason);
}

void config_outbox_failed(DictionaryIterator *iter, AppMessageResult reason, void *context) {
  (void)iter;
  (void)context;
  APP_LOG(APP_LOG_LEVEL_ERROR, "Outbox failed: %d", reason);
}
