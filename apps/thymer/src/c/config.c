#include "config.h"

#include "app_state.h"
#include "timer.h"
#include "ui.h"
#include "util.h"

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

static bool prv_try_load_persisted_config(TimerConfig *out, char *reason, size_t reason_len) {
  PersistConfigMeta meta = {0};
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
    return false;
  }

  if (meta.version != CONFIG_VERSION) {
    snprintf(reason, reason_len, "Meta version %u != %u",
             (unsigned)meta.version, (unsigned)CONFIG_VERSION);
    APP_LOG(APP_LOG_LEVEL_ERROR, "persist meta version mismatch stored=%u current=%u",
            (unsigned)meta.version, (unsigned)CONFIG_VERSION);
    return false;
  }

  if (meta.timer_count == 0 || meta.timer_count > MAX_TIMERS) {
    snprintf(reason, reason_len, "Meta timer_count %u invalid", (unsigned)meta.timer_count);
    APP_LOG(APP_LOG_LEVEL_ERROR, "persist meta invalid timer_count=%u max=%u",
            (unsigned)meta.timer_count, (unsigned)MAX_TIMERS);
    return false;
  }

  memset(out, 0, sizeof(*out));
  out->version = CONFIG_VERSION;
  out->timer_count = meta.timer_count;
  bool legacy_ui_flags = (meta.ui_flags & ~(uint8_t)CONFIG_FLAG_ICONS) == 0;
  out->icons_enabled = (meta.ui_flags & CONFIG_FLAG_ICONS) != 0;
  out->background_enabled = legacy_ui_flags || (meta.ui_flags & CONFIG_FLAG_BACKGROUND) != 0;
  out->timer_accent_enabled = legacy_ui_flags || (meta.ui_flags & CONFIG_FLAG_TIMER_ACCENT) != 0;

  for (uint8_t timer_index = 0; timer_index < meta.timer_count; ++timer_index) {
    PersistTimerRecord timer_record = {0};
    int timer_size = persist_read_data(prv_timer_key(timer_index), &timer_record,
                                       sizeof(timer_record));
    if (timer_size != (int)sizeof(timer_record)) {
      snprintf(reason, reason_len, "Timer %u size %d != %u",
               (unsigned)timer_index, timer_size, (unsigned)sizeof(timer_record));
      APP_LOG(APP_LOG_LEVEL_ERROR, "persist timer %u size mismatch read=%d expected=%u",
              (unsigned)timer_index, timer_size, (unsigned)sizeof(timer_record));
      return false;
    }

    if (timer_record.segment_count > MAX_SEGMENTS ||
        timer_record.finish_vibe_count > MAX_VIBE_STEPS) {
      snprintf(reason, reason_len, "Timer %u invalid counts", (unsigned)timer_index);
      APP_LOG(APP_LOG_LEVEL_ERROR,
              "persist timer %u invalid segment_count=%u finish_vibe_count=%u",
              (unsigned)timer_index, (unsigned)timer_record.segment_count,
              (unsigned)timer_record.finish_vibe_count);
      return false;
    }

    TimerDefinition *timer = &out->timers[timer_index];
    util_copy_string(timer->name, sizeof(timer->name), timer_record.name);
    timer->repeat = (timer_record.flags & TIMER_FLAG_REPEAT) != 0;
    timer->iterations_enabled = (timer_record.flags & TIMER_FLAG_ITERATIONS_ENABLED) != 0;
    timer->must_acknowledge = (timer_record.flags & TIMER_FLAG_MUST_ACKNOWLEDGE) != 0;
    timer->on_press_up = util_clamp_up_action(timer_record.on_press_up);
    timer->on_long_press_up = util_clamp_up_action(timer_record.on_long_press_up);
    timer->iterations = timer_record.iterations;
    timer->repeat_pattern_delay_ms = timer_record.repeat_pattern_delay_ms;
    timer->acknowledge_alert_duration_s = timer_record.acknowledge_alert_duration_s;
    timer->finish_vibe_count = timer_record.finish_vibe_count;
    timer->segment_count = timer_record.segment_count;
    timer->trigger_kind = (TriggerKind)util_clamp_i32(timer_record.trigger_kind, TRIGGER_NONE,
                                                      TRIGGER_SWIPE);
    timer->trigger_from = (TriggerZone)util_clamp_i32(timer_record.trigger_from, ZONE_NONE,
                                                      ZONE_CENTER);
    timer->trigger_to = (TriggerZone)util_clamp_i32(timer_record.trigger_to, ZONE_NONE,
                                                    ZONE_CENTER);
    for (uint8_t i = 0; i < timer->finish_vibe_count; ++i) {
      prv_copy_vibe_from_persist(&timer->finish_vibes[i], &timer_record.finish_vibes[i]);
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
        return false;
      }

      if (segment_record.vibe_count > MAX_VIBE_STEPS) {
        snprintf(reason, reason_len, "Seg %u/%u invalid vibe_count",
                 (unsigned)timer_index, (unsigned)segment_index);
        APP_LOG(APP_LOG_LEVEL_ERROR, "persist segment %u/%u invalid vibe_count=%u",
                (unsigned)timer_index, (unsigned)segment_index,
                (unsigned)segment_record.vibe_count);
        return false;
      }

      TimerSegment *segment = &timer->segments[segment_index];
      util_copy_string(segment->description, sizeof(segment->description),
                       segment_record.description);
      segment->duration_ms = segment_record.duration_ms;
      segment->vibe_count = segment_record.vibe_count;
      for (uint8_t i = 0; i < segment->vibe_count; ++i) {
        prv_copy_vibe_from_persist(&segment->vibes[i], &segment_record.vibes[i]);
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
}

bool config_has_persisted_config(void) {
  return prv_try_load_persisted_config(&s_candidate_config, s_persist_debug_reason,
                                       sizeof(s_persist_debug_reason));
}

void config_default_config(void) {
  memset(&s_config, 0, sizeof(s_config));
  s_config.version = CONFIG_VERSION;
  s_config.icons_enabled = true;
  s_config.background_enabled = true;
  s_config.timer_accent_enabled = true;
  s_config.timer_count = 1;

  TimerDefinition *timer = &s_config.timers[0];
  util_copy_string(timer->name, sizeof(timer->name), "Timer 1");
  timer->repeat = true;
  timer->iterations_enabled = false;
  timer->iterations = 0;
  timer->repeat_pattern_delay_ms = DEFAULT_REPEAT_PATTERN_DELAY_MS;
  timer->acknowledge_alert_duration_s = DEFAULT_ACK_ALERT_DURATION_S;
  timer->segment_count = 2;
  timer->trigger_kind = TRIGGER_TAP;
  timer->trigger_from = ZONE_TOP;
  timer->trigger_to = ZONE_NONE;

  util_copy_string(timer->segments[0].description, sizeof(timer->segments[0].description), "far");
  timer->segments[0].duration_ms = 20000;
  timer->segments[0].vibe_count = 1;
  timer->segments[0].vibes[0].intensity = VIBE_INTENSITY_LOW;
  timer->segments[0].vibes[0].duration_ms = 100;
  timer->segments[0].vibes[0].delay_ms = 100;
  util_copy_string(timer->segments[1].description, sizeof(timer->segments[1].description), "near");
  timer->segments[1].duration_ms = 20000;
  timer->segments[1].vibe_count = 1;
  timer->segments[1].vibes[0].intensity = VIBE_INTENSITY_MID;
  timer->segments[1].vibes[0].duration_ms = 150;
  timer->segments[1].vibes[0].delay_ms = 100;
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
                           (timer->must_acknowledge ? TIMER_FLAG_MUST_ACKNOWLEDGE : 0);
      timer_record.on_press_up = (uint8_t)timer->on_press_up;
      timer_record.on_long_press_up = (uint8_t)timer->on_long_press_up;
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

      for (uint8_t segment_index = 0; segment_index < MAX_SEGMENTS; ++segment_index) {
        uint32_t key = prv_segment_key(timer_index, segment_index);
        if (segment_index < timer->segment_count) {
          const TimerSegment *segment = &timer->segments[segment_index];
          PersistSegmentRecord segment_record;
          memset(&segment_record, 0, sizeof(segment_record));
          util_copy_string(segment_record.description, sizeof(segment_record.description),
                           segment->description);
          segment_record.duration_ms = segment->duration_ms;
          segment_record.vibe_count = segment->vibe_count;
          for (uint8_t i = 0; i < segment->vibe_count; ++i) {
            prv_copy_vibe_to_persist(&segment_record.vibes[i], &segment->vibes[i]);
          }
          persist_write_data(key, &segment_record, sizeof(segment_record));
        } else if (persist_exists(key)) {
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

static void prv_build_config_from_pending(TimerConfig *config) {
  memset(config, 0, sizeof(*config));
  config->version = CONFIG_VERSION;
  config->icons_enabled = s_pending_config.icons_enabled;
  config->background_enabled = s_pending_config.background_enabled;
  config->timer_accent_enabled = s_pending_config.timer_accent_enabled;
  config->timer_count = s_pending_config.timer_count;
  memcpy(config->timers, s_pending_config.timers, sizeof(s_pending_config.timers));
  if (config->timer_count == 0) {
    memset(config, 0, sizeof(*config));
    config->version = CONFIG_VERSION;
    config->icons_enabled = true;
    config->background_enabled = true;
    config->timer_accent_enabled = true;
    config->timer_count = 1;

    TimerDefinition *timer = &config->timers[0];
    util_copy_string(timer->name, sizeof(timer->name), "Timer 1");
    timer->repeat = true;
    timer->repeat_pattern_delay_ms = DEFAULT_REPEAT_PATTERN_DELAY_MS;
    timer->acknowledge_alert_duration_s = DEFAULT_ACK_ALERT_DURATION_S;
    timer->trigger_kind = TRIGGER_TAP;
    timer->trigger_from = ZONE_TOP;
    util_copy_string(timer->segments[0].description, sizeof(timer->segments[0].description), "far");
    timer->segments[0].duration_ms = 20000;
    timer->segments[0].vibe_count = 1;
    timer->segments[0].vibes[0].intensity = VIBE_INTENSITY_LOW;
    timer->segments[0].vibes[0].duration_ms = 100;
    timer->segments[0].vibes[0].delay_ms = 100;
    util_copy_string(timer->segments[1].description, sizeof(timer->segments[1].description), "near");
    timer->segments[1].duration_ms = 20000;
    timer->segments[1].vibe_count = 1;
    timer->segments[1].vibes[0].intensity = VIBE_INTENSITY_MID;
    timer->segments[1].vibes[0].duration_ms = 150;
    timer->segments[1].vibes[0].delay_ms = 100;
    timer->segment_count = 2;
  }
}

static void prv_apply_config_from_pending(bool show_notice) {
  prv_build_config_from_pending(&s_candidate_config);

  bool changed = memcmp(&s_config, &s_candidate_config, sizeof(s_candidate_config)) != 0;
  s_waiting_for_initial_config = false;
  if (!changed) {
    return;
  }

  prv_reset_runtime_for_new_config();
  memcpy(&s_config, &s_candidate_config, sizeof(s_candidate_config));
  config_persist_config();
  config_persist_state();
  ui_refresh_background_layers();
  if (show_notice) {
    ui_show_config_notice();
  }
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
    return;
  }

  int32_t op = op_tuple->value->int32;
  if (op == CFG_OP_BEGIN) {
    memset(&s_pending_config, 0, sizeof(s_pending_config));
    s_pending_config.icons_enabled = true;
    s_pending_config.background_enabled = true;
    s_pending_config.timer_accent_enabled = true;
    Tuple *count_tuple = dict_find(iter, MESSAGE_KEY_CFG_TIMER);
    Tuple *ui_flags_tuple = dict_find(iter, MESSAGE_KEY_CFG_UI_FLAGS);
    if (count_tuple) {
      s_pending_config.timer_count = (uint8_t)util_clamp_i32(count_tuple->value->int32,
                                                             0, MAX_TIMERS);
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
    if (!timer_tuple) {
      return;
    }
    uint8_t index = (uint8_t)timer_tuple->value->int32;
    if (index >= MAX_TIMERS) {
      return;
    }
    TimerDefinition *timer = &s_pending_config.timers[index];
    memset(timer, 0, sizeof(*timer));
    timer->repeat = flags_tuple ? ((flags_tuple->value->int32 & TIMER_FLAG_REPEAT) != 0) : false;
    timer->iterations_enabled = flags_tuple
      ? ((flags_tuple->value->int32 & TIMER_FLAG_ITERATIONS_ENABLED) != 0) : false;
    timer->must_acknowledge = flags_tuple
      ? ((flags_tuple->value->int32 & TIMER_FLAG_MUST_ACKNOWLEDGE) != 0) : false;
    timer->on_press_up = up_action_tuple
      ? util_clamp_up_action(up_action_tuple->value->int32) : UP_ACTION_NONE;
    timer->on_long_press_up = up_long_action_tuple
      ? util_clamp_up_action(up_long_action_tuple->value->int32) : UP_ACTION_NONE;
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
    timer->segment_count = segment_count_tuple
      ? (uint8_t)util_clamp_i32(segment_count_tuple->value->int32, 0, MAX_SEGMENTS) : 0;
    if (text_tuple && text_tuple->type == TUPLE_CSTRING) {
      util_copy_string(timer->name, sizeof(timer->name), text_tuple->value->cstring);
    }
    if (index + 1 > s_pending_config.timer_count) {
      s_pending_config.timer_count = index + 1;
    }
    return;
  }

  if (op == CFG_OP_SEGMENT) {
    Tuple *timer_tuple = dict_find(iter, MESSAGE_KEY_CFG_TIMER);
    Tuple *segment_tuple = dict_find(iter, MESSAGE_KEY_CFG_SEGMENT);
    Tuple *duration_tuple = dict_find(iter, MESSAGE_KEY_CFG_DURATION);
    Tuple *text_tuple = dict_find(iter, MESSAGE_KEY_CFG_TEXT);
    Tuple *alert_tuple = dict_find(iter, MESSAGE_KEY_CFG_ALERT);
    if (!timer_tuple || !segment_tuple || !duration_tuple) {
      return;
    }
    uint8_t timer_index = (uint8_t)timer_tuple->value->int32;
    uint8_t segment_index = (uint8_t)segment_tuple->value->int32;
    if (timer_index >= MAX_TIMERS || segment_index >= MAX_SEGMENTS) {
      return;
    }
    uint64_t duration_ms = 0;
    if (!util_read_uint64_tuple(duration_tuple, &duration_ms) || duration_ms < 1) {
      return;
    }
    TimerSegment *segment = &s_pending_config.timers[timer_index].segments[segment_index];
    segment->duration_ms = duration_ms;
    segment->vibe_count = alert_tuple
      ? (uint8_t)util_clamp_i32(alert_tuple->value->int32, 0, MAX_VIBE_STEPS) : 0;
    if (text_tuple && text_tuple->type == TUPLE_CSTRING) {
      util_copy_string(segment->description, sizeof(segment->description),
                       text_tuple->value->cstring);
    }
    return;
  }

  if (op == CFG_OP_VIBRATE) {
    Tuple *timer_tuple = dict_find(iter, MESSAGE_KEY_CFG_TIMER);
    Tuple *segment_tuple = dict_find(iter, MESSAGE_KEY_CFG_SEGMENT);
    Tuple *alert_tuple = dict_find(iter, MESSAGE_KEY_CFG_ALERT);
    Tuple *intensity_tuple = dict_find(iter, MESSAGE_KEY_CFG_INTENSITY);
    Tuple *duration_tuple = dict_find(iter, MESSAGE_KEY_CFG_DURATION);
    Tuple *delay_tuple = dict_find(iter, MESSAGE_KEY_CFG_DELAY);
    if (!timer_tuple || !segment_tuple || !alert_tuple || !intensity_tuple || !duration_tuple) {
      return;
    }
    uint8_t timer_index = (uint8_t)timer_tuple->value->int32;
    uint8_t segment_index = (uint8_t)segment_tuple->value->int32;
    uint8_t alert_index = (uint8_t)alert_tuple->value->int32;
    if (timer_index >= MAX_TIMERS || alert_index >= MAX_VIBE_STEPS) {
      return;
    }
    VibeStep *step = NULL;
    if (segment_index == FINISH_VIBE_SEGMENT) {
      step = &s_pending_config.timers[timer_index].finish_vibes[alert_index];
    } else {
      if (segment_index >= MAX_SEGMENTS) {
        return;
      }
      step = &s_pending_config.timers[timer_index].segments[segment_index].vibes[alert_index];
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
    for (uint8_t timer_index = 0; timer_index < s_pending_config.timer_count; ++timer_index) {
      TimerDefinition *timer = &s_pending_config.timers[timer_index];
      for (uint8_t segment_index = 0; segment_index < timer->segment_count; ++segment_index) {
        TimerSegment *segment = &timer->segments[segment_index];
        if (!segment->description[0]) {
          snprintf(segment->description, sizeof(segment->description), "step %u",
                   (unsigned)(segment_index + 1));
        }
      }
    }
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
