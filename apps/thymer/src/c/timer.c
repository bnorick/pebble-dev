#include "timer.h"

#include "app_state.h"
#include "config.h"
#include "ui.h"
#include "util.h"

static AppTimer *s_refresh_timer;
static AppTimer *s_ack_timer;

static uint32_t prv_scaled_vibe_duration_ms(VibeIntensity intensity, uint16_t duration_ms) {
  uint32_t base = duration_ms ? duration_ms : 100;
  switch (intensity) {
    case VIBE_INTENSITY_LOW: return (base * 3) / 4;
    case VIBE_INTENSITY_HIGH: return (base * 3) / 2;
    case VIBE_INTENSITY_MID:
    default:
      return base;
  }
}

const TimerDefinition *timer_selected_timer(void) {
  if (s_config.timer_count == 0) {
    return NULL;
  }
  if (s_state.selected_timer >= s_config.timer_count) {
    s_state.selected_timer = 0;
  }
  return &s_config.timers[s_state.selected_timer];
}

const TimerDefinition *timer_active_timer(void) {
  if (!s_state.active || s_config.timer_count == 0) {
    return NULL;
  }
  if (s_state.active_timer >= s_config.timer_count) {
    return &s_config.timers[0];
  }
  return &s_config.timers[s_state.active_timer];
}

void timer_reset_phase_tracking(void) {
  s_last_phase_index = 0xff;
  s_last_iteration_index = 0xffff;
}

uint64_t timer_cycle_duration_ms(const TimerDefinition *timer) {
  if (!timer || timer->segment_count == 0 || !timer->segments) {
    return 0;
  }
  uint64_t total = 0;
  for (uint8_t i = 0; i < timer->segment_count; ++i) {
    total = util_add_u64_saturating(total, timer->segments[i].duration_ms);
  }
  return total;
}

bool timer_allows_skip(const TimerDefinition *timer) {
  if (!timer || timer->segment_count <= 1) {
    return false;
  }
  return timer->on_press_up.kind == UP_ACTION_SKIP ||
         timer->on_long_press_up.kind == UP_ACTION_SKIP;
}

uint8_t timer_clamp_segment_index(const TimerDefinition *timer, uint8_t segment_index) {
  if (!timer || timer->segment_count == 0) {
    return 0;
  }
  if (segment_index >= timer->segment_count) {
    return timer->segment_count - 1;
  }
  return segment_index;
}

uint64_t timer_segment_start_elapsed_ms(const TimerDefinition *timer, uint8_t segment_index) {
  if (!timer || timer->segment_count == 0 || !timer->segments) {
    return 0;
  }

  uint8_t bounded_index = timer_clamp_segment_index(timer, segment_index);
  uint64_t elapsed_ms = 0;
  for (uint8_t i = 0; i < bounded_index; ++i) {
    elapsed_ms = util_add_u64_saturating(elapsed_ms, timer->segments[i].duration_ms);
  }
  return elapsed_ms;
}

bool timer_has_finite_end(const TimerDefinition *timer) {
  if (!timer->repeat) {
    return true;
  }
  return timer->iterations_enabled && timer->iterations > 0;
}

uint64_t timer_total_duration_ms(const TimerDefinition *timer) {
  uint64_t cycle = timer_cycle_duration_ms(timer);
  if (!cycle) {
    return 0;
  }
  if (!timer->repeat) {
    return cycle;
  }
  if (timer->iterations_enabled && timer->iterations > 0) {
    return util_mul_u64_saturating(cycle, timer->iterations);
  }
  return 0;
}

static uint64_t prv_adjusted_total_duration_ms(uint64_t base_duration_ms) {
  if (s_state.duration_adjustment_ms >= 0) {
    return util_add_u64_saturating(base_duration_ms, (uint64_t)s_state.duration_adjustment_ms);
  }

  uint64_t reduction_ms = (uint64_t)(-s_state.duration_adjustment_ms);
  return reduction_ms >= base_duration_ms ? 0 : (base_duration_ms - reduction_ms);
}

uint64_t timer_adjusted_total_duration_ms(const TimerDefinition *timer) {
  return prv_adjusted_total_duration_ms(timer_total_duration_ms(timer));
}

uint32_t timer_vibration_pattern_duration_ms(const VibeStep *steps, uint8_t step_count) {
  uint32_t total_ms = 0;
  if (!steps || step_count == 0) {
    return 0;
  }

  for (uint8_t i = 0; i < step_count && i < MAX_VIBE_STEPS; ++i) {
    total_ms += prv_scaled_vibe_duration_ms(steps[i].intensity, steps[i].duration_ms);
    if (i + 1 < step_count) {
      total_ms += steps[i].delay_ms;
    }
  }
  return total_ms;
}

void timer_play_vibration_pattern(const VibeStep *steps, uint8_t step_count) {
  if (!steps || step_count == 0) {
    return;
  }

  static uint32_t durations[MAX_VIBE_PATTERN_PARTS];
  uint32_t count = 0;
  for (uint8_t i = 0; i < step_count && i < MAX_VIBE_STEPS; ++i) {
    const VibeStep *step = &steps[i];
    durations[count++] = prv_scaled_vibe_duration_ms(step->intensity, step->duration_ms);
    if (i + 1 < step_count) {
      durations[count++] = step->delay_ms;
    }
  }

  if (count == 0) {
    return;
  }

  VibePattern pattern = {
    .durations = durations,
    .num_segments = count,
  };
  vibes_enqueue_custom_pattern(pattern);
}

void timer_play_segment_vibration(const TimerSegment *segment) {
  if (!segment) {
    return;
  }
  timer_play_vibration_pattern(segment->vibes, segment->vibe_count);
}

static void prv_ack_timer_callback(void *context);

static void prv_schedule_ack_repeat(const TimerSegment *segment) {
  if (!segment || !s_state.awaiting_ack || s_state.ack_silenced) {
    return;
  }
  const TimerDefinition *timer = timer_active_timer();
  if (!timer || timer->acknowledge_alert_duration_s == 0) {
    return;
  }

  uint64_t now_ms = util_now_ms();
  uint64_t deadline_ms = s_state.ack_started_at_ms +
    ((uint64_t)timer->acknowledge_alert_duration_s * 1000);
  if (now_ms >= deadline_ms) {
    return;
  }

  uint32_t pattern_ms = timer_vibration_pattern_duration_ms(segment->vibes, segment->vibe_count);
  if (pattern_ms == 0) {
    return;
  }
  uint32_t delay_ms = pattern_ms + timer->repeat_pattern_delay_ms;
  uint64_t remaining_ms = deadline_ms - now_ms;
  if ((uint64_t)delay_ms > remaining_ms) {
    delay_ms = (uint32_t)remaining_ms;
  }

  timer_cancel_ack_timer();
  s_ack_timer = app_timer_register(delay_ms, prv_ack_timer_callback, NULL);
}

static void prv_ack_timer_callback(void *context) {
  (void)context;
  s_ack_timer = NULL;

  if (!s_state.awaiting_ack || !s_state.active) {
    return;
  }

  const TimerDefinition *timer = timer_active_timer();
  if (!timer) {
    return;
  }

  TimerSnapshot snap = timer_current_snapshot();
  if (!snap.valid || snap.completed || snap.phase_index >= timer->segment_count) {
    return;
  }

  const TimerSegment *segment = &timer->segments[snap.phase_index];
  timer_play_segment_vibration(segment);
  prv_schedule_ack_repeat(segment);
}

static void prv_schedule_finish_wakeup(void) {
  timer_cancel_wakeup();
  const TimerDefinition *timer = timer_active_timer();
  if (!timer || !s_state.running || !timer_has_finite_end(timer)) {
    return;
  }
  uint64_t total_duration = prv_adjusted_total_duration_ms(timer_total_duration_ms(timer));
  uint64_t elapsed = util_now_ms() - s_state.started_at_ms;
  if (elapsed >= total_duration) {
    return;
  }
  uint64_t remaining_ms = total_duration - elapsed;
  uint64_t remaining_s = util_div_ceil_u64(remaining_ms, 1000);
  if (remaining_s < 30) {
    return;
  }
  time_t now_s = 0;
  time_ms(&now_s, NULL);
  if (remaining_s > INT32_MAX) {
    APP_LOG(APP_LOG_LEVEL_WARNING, "skip wakeup remaining_s too large=%llu",
            (unsigned long long)remaining_s);
    return;
  }
  WakeupId id = wakeup_schedule(now_s + (time_t)remaining_s, WAKEUP_COOKIE_FINISH, true);
  APP_LOG(APP_LOG_LEVEL_DEBUG, "schedule wakeup remaining_s=%llu id=%ld",
          (unsigned long long)remaining_s, (long)id);
}

static void prv_finish_to_preview_state(void) {
  uint8_t finished_timer = s_state.active_timer;
  if (finished_timer >= s_config.timer_count) {
    finished_timer = 0;
  }

  s_state.active = false;
  s_state.running = false;
  s_state.completed = true;
  s_state.awaiting_ack = false;
  s_state.ack_silenced = false;
  s_state.selected_timer = finished_timer;
  s_state.active_timer = finished_timer;
  s_state.paused_elapsed_ms = 0;
  s_state.started_at_ms = 0;
  s_state.ack_started_at_ms = 0;
  s_selected_segment = 0;
  timer_reset_phase_tracking();
  timer_cancel_wakeup();
  timer_cancel_ack_timer();
}

static TimerSnapshot prv_timer_snapshot_for_duration(const TimerDefinition *timer,
                                                     uint64_t elapsed_ms,
                                                     uint64_t total_duration_ms) {
  TimerSnapshot snap = {0};
  if (!timer || timer->segment_count == 0 || !timer->segments) {
    return snap;
  }

  snap.valid = true;
  snap.elapsed_ms = elapsed_ms;
  snap.cycle_duration_ms = timer_cycle_duration_ms(timer);
  snap.infinite = !timer_has_finite_end(timer);
  snap.total_duration_ms = total_duration_ms;
  uint64_t base_total_duration_ms = timer_total_duration_ms(timer);

  if (!snap.cycle_duration_ms) {
    return snap;
  }

  if (!snap.infinite && elapsed_ms >= snap.total_duration_ms) {
    snap.completed = true;
    snap.elapsed_ms = snap.total_duration_ms;
    snap.total_remaining_ms = 0;
    snap.iteration_count = timer->repeat ? timer->iterations : 1;
    snap.iteration_index = snap.iteration_count ? (snap.iteration_count - 1) : 0;
    snap.phase_index = timer->segment_count - 1;
    snap.phase_remaining_ms = 0;
    return snap;
  }

  if (!snap.infinite && elapsed_ms >= base_total_duration_ms &&
      snap.total_duration_ms > base_total_duration_ms) {
    snap.iteration_count = timer->repeat ? timer->iterations : 1;
    snap.iteration_index = snap.iteration_count ? (snap.iteration_count - 1) : 0;
    snap.phase_index = timer->segment_count - 1;
    snap.phase_remaining_ms = snap.total_duration_ms - elapsed_ms;
    snap.total_remaining_ms = snap.phase_remaining_ms;
    snap.cycle_elapsed_ms = snap.cycle_duration_ms;
    return snap;
  }

  snap.iteration_index = util_clamp_u64_to_u16(elapsed_ms / snap.cycle_duration_ms, UINT16_MAX);
  snap.cycle_elapsed_ms = elapsed_ms % snap.cycle_duration_ms;
  snap.iteration_count = timer->repeat ? timer->iterations : 1;

  uint64_t accumulated = 0;
  for (uint8_t i = 0; i < timer->segment_count; ++i) {
    uint64_t next = accumulated + timer->segments[i].duration_ms;
    if (snap.cycle_elapsed_ms < next) {
      snap.phase_index = i;
      snap.phase_remaining_ms = next - snap.cycle_elapsed_ms;
      break;
    }
    accumulated = next;
  }

  if (snap.phase_remaining_ms == 0) {
    snap.phase_index = timer->segment_count - 1;
    snap.phase_remaining_ms = timer->segments[snap.phase_index].duration_ms;
  }

  snap.total_remaining_ms = snap.infinite ? 0 : (snap.total_duration_ms - elapsed_ms);
  return snap;
}

TimerSnapshot timer_snapshot_for(const TimerDefinition *timer, uint64_t elapsed_ms) {
  return prv_timer_snapshot_for_duration(timer, elapsed_ms, timer_total_duration_ms(timer));
}

TimerSnapshot timer_current_snapshot(void) {
  const TimerDefinition *timer = timer_active_timer();
  if (!timer) {
    TimerSnapshot empty = {0};
    return empty;
  }
  uint64_t elapsed_ms = s_state.running
    ? (util_now_ms() - s_state.started_at_ms)
    : s_state.paused_elapsed_ms;
  return prv_timer_snapshot_for_duration(
    timer,
    elapsed_ms,
    prv_adjusted_total_duration_ms(timer_total_duration_ms(timer)));
}

bool timer_next_segment_after(const TimerDefinition *timer,
                              const TimerSnapshot *snap,
                              uint8_t *next_segment,
                              uint16_t *next_iteration,
                              uint64_t *next_elapsed_ms) {
  if (!timer || !snap || !snap->valid || !next_segment || !next_iteration || !next_elapsed_ms ||
      snap->completed) {
    return false;
  }

  uint16_t iteration = snap->iteration_index;
  uint8_t segment = snap->phase_index + 1;
  if (segment >= timer->segment_count) {
    segment = 0;
    if (!timer->repeat) {
      return false;
    }
    if (timer->iterations_enabled && timer->iterations > 0 &&
        snap->iteration_index + 1 >= timer->iterations) {
      return false;
    }
    iteration += 1;
  }

  *next_segment = segment;
  *next_iteration = iteration;
  *next_elapsed_ms = util_add_u64_saturating(
    util_mul_u64_saturating((uint64_t)iteration, snap->cycle_duration_ms),
    timer_segment_start_elapsed_ms(timer, segment));
  return true;
}

void timer_update_running_state(void) {
  if (!s_state.active) {
    return;
  }
  const TimerDefinition *timer = timer_active_timer();
  if (!timer) {
    s_state.active = false;
    s_state.running = false;
    s_state.completed = false;
    return;
  }

  TimerSnapshot snap = timer_current_snapshot();
  if (!snap.completed && snap.valid && s_state.running) {
    if (s_last_phase_index != 0xff &&
        (snap.phase_index != s_last_phase_index || snap.iteration_index != s_last_iteration_index)) {
      if (timer->must_acknowledge) {
        TimerSnapshot previous = snap;
        previous.phase_index = s_last_phase_index;
        previous.iteration_index = s_last_iteration_index;
        uint8_t next_segment = 0;
        uint16_t next_iteration = 0;
        uint64_t next_elapsed_ms = 0;
        if (timer_next_segment_after(timer, &previous, &next_segment, &next_iteration,
                                     &next_elapsed_ms)) {
          (void)next_iteration;
          s_state.running = false;
          s_state.awaiting_ack = true;
          s_state.ack_silenced = false;
          s_state.started_at_ms = 0;
          s_state.paused_elapsed_ms = next_elapsed_ms;
          s_state.ack_started_at_ms = util_now_ms();
          s_last_phase_index = next_segment;
          s_last_iteration_index = snap.iteration_index;
          const TimerSegment *next = &timer->segments[next_segment];
          timer_play_segment_vibration(next);
          prv_schedule_ack_repeat(next);
          timer_cancel_wakeup();
          config_persist_state();
          return;
        }
      } else {
        timer_play_segment_vibration(&timer->segments[snap.phase_index]);
      }
    }
    s_last_phase_index = snap.phase_index;
    s_last_iteration_index = snap.iteration_index;
  }
  if (snap.completed) {
    if (!s_state.alert_fired && timer_has_finite_end(timer)) {
      if (timer->finish_vibe_count > 0) {
        timer_play_vibration_pattern(timer->finish_vibes, timer->finish_vibe_count);
      } else {
        vibes_double_pulse();
      }
      s_state.alert_fired = true;
    }
    prv_finish_to_preview_state();
    config_persist_state();
  }
}

static void prv_refresh_timer_callback(void *context) {
  (void)context;
  s_refresh_timer = NULL;
  timer_update_running_state();
  ui_refresh();

  if (s_state.running) {
    s_refresh_timer = app_timer_register(100, prv_refresh_timer_callback, NULL);
  }
}

void timer_ensure_refresh_timer(void) {
  if (!s_state.running) {
    timer_cancel_refresh_timer();
    return;
  }
  if (!s_refresh_timer) {
    s_refresh_timer = app_timer_register(100, prv_refresh_timer_callback, NULL);
  }
}

void timer_cancel_refresh_timer(void) {
  if (s_refresh_timer) {
    app_timer_cancel(s_refresh_timer);
    s_refresh_timer = NULL;
  }
}

void timer_cancel_wakeup(void) {
  wakeup_cancel_all();
}

void timer_cancel_ack_timer(void) {
  if (s_ack_timer) {
    app_timer_cancel(s_ack_timer);
    s_ack_timer = NULL;
  }
}

void timer_start(uint8_t timer_index) {
  if (timer_index >= s_config.timer_count) {
    return;
  }
  const TimerDefinition *timer = &s_config.timers[timer_index];
  if (timer->segment_count == 0 || !timer->segments) {
    return;
  }
  uint8_t start_segment = timer_allows_skip(timer)
    ? timer_clamp_segment_index(timer, s_selected_segment)
    : 0;
  uint64_t elapsed_ms = timer_segment_start_elapsed_ms(timer, start_segment);
  s_state.active = true;
  s_state.running = true;
  s_state.completed = false;
  s_state.alert_fired = false;
  s_state.awaiting_ack = false;
  s_state.ack_silenced = false;
  s_state.selected_timer = timer_index;
  s_state.active_timer = timer_index;
  s_state.started_at_ms = util_now_ms() - elapsed_ms;
  s_state.paused_elapsed_ms = elapsed_ms;
  s_state.ack_started_at_ms = 0;
  timer_reset_phase_tracking();
  timer_cancel_ack_timer();
  if (timer->segment_count > 0) {
    const TimerSegment *segment = &timer->segments[start_segment];
    timer_play_segment_vibration(segment);
    s_last_phase_index = start_segment;
    s_last_iteration_index = 0;
  }
  prv_schedule_finish_wakeup();
  config_persist_state();
  timer_ensure_refresh_timer();
  ui_refresh();
}

void timer_pause(void) {
  if (!s_state.active || !s_state.running) {
    return;
  }
  s_state.paused_elapsed_ms = util_now_ms() - s_state.started_at_ms;
  s_state.running = false;
  s_state.awaiting_ack = false;
  s_state.ack_silenced = false;
  s_state.ack_started_at_ms = 0;
  timer_cancel_wakeup();
  timer_cancel_ack_timer();
  config_persist_state();
  timer_ensure_refresh_timer();
  ui_refresh();
}

void timer_resume(void) {
  if (!s_state.active || s_state.running || s_state.completed || s_state.awaiting_ack) {
    return;
  }
  s_state.running = true;
  s_state.started_at_ms = util_now_ms() - s_state.paused_elapsed_ms;
  TimerSnapshot snap = timer_current_snapshot();
  s_last_phase_index = snap.valid ? snap.phase_index : 0xff;
  s_last_iteration_index = snap.valid ? snap.iteration_index : 0xffff;
  prv_schedule_finish_wakeup();
  config_persist_state();
  timer_ensure_refresh_timer();
  ui_refresh();
}

void timer_reset(void) {
  uint8_t reset_timer = s_state.active ? s_state.active_timer : s_state.selected_timer;
  if (reset_timer >= s_config.timer_count) {
    reset_timer = 0;
  }
  bool preserve_adjustment = s_state.active && !s_state.completed;

  s_state.active = false;
  s_state.running = false;
  s_state.completed = false;
  s_state.alert_fired = false;
  s_state.awaiting_ack = false;
  s_state.ack_silenced = false;
  s_state.selected_timer = reset_timer;
  s_state.active_timer = reset_timer;
  s_state.paused_elapsed_ms = 0;
  s_state.started_at_ms = 0;
  s_state.ack_started_at_ms = 0;
  if (!preserve_adjustment) {
    s_state.duration_adjustment_ms = 0;
  }
  s_selected_segment = 0;
  timer_reset_phase_tracking();
  timer_cancel_wakeup();
  timer_cancel_ack_timer();
  vibes_cancel();
  config_persist_state();
  timer_ensure_refresh_timer();
  ui_refresh();
}

bool timer_reset_available(void) {
  return s_state.active || s_state.duration_adjustment_ms != 0 || s_selected_segment != 0;
}

void timer_dismiss_acknowledgement(bool reveal_text) {
  if (!s_state.active || !s_state.awaiting_ack) {
    return;
  }

  if (reveal_text) {
    ui_reveal_text_if_hidden();
  }
  s_state.awaiting_ack = false;
  s_state.ack_silenced = false;
  s_state.running = true;
  s_state.started_at_ms = util_now_ms() - s_state.paused_elapsed_ms;
  s_state.ack_started_at_ms = 0;
  timer_cancel_ack_timer();
  vibes_cancel();
  TimerSnapshot snap = timer_current_snapshot();
  s_last_phase_index = snap.valid ? snap.phase_index : 0xff;
  s_last_iteration_index = snap.valid ? snap.iteration_index : 0xffff;
  prv_schedule_finish_wakeup();
  config_persist_state();
  timer_ensure_refresh_timer();
  ui_refresh();
}

void timer_silence_acknowledgement(bool reveal_text) {
  if (!s_state.active || !s_state.awaiting_ack || s_state.ack_silenced) {
    return;
  }

  if (reveal_text) {
    ui_reveal_text_if_hidden();
  }
  s_state.ack_silenced = true;
  timer_cancel_ack_timer();
  vibes_cancel();
  config_persist_state();
  ui_refresh();
}

bool timer_skip_selected_segment(void) {
  const TimerDefinition *timer = timer_selected_timer();
  if (!timer || timer->segment_count == 0 || !timer->segments || !timer_allows_skip(timer)) {
    return false;
  }

  s_selected_segment = (uint8_t)((s_selected_segment + 1) % timer->segment_count);
  ui_refresh();
  return true;
}

bool timer_skip_active_segment(void) {
  if (!s_state.active || s_state.running || s_state.completed || s_state.awaiting_ack) {
    return false;
  }

  const TimerDefinition *timer = timer_active_timer();
  if (!timer || timer->segment_count == 0 || !timer->segments || !timer_allows_skip(timer)) {
    return false;
  }

  TimerSnapshot snap = timer_current_snapshot();
  if (!snap.valid || snap.completed) {
    return false;
  }

  uint16_t next_iteration = 0;
  uint8_t next_segment = 0;
  uint64_t next_elapsed_ms = 0;
  if (!timer_next_segment_after(timer, &snap, &next_segment, &next_iteration, &next_elapsed_ms)) {
    return false;
  }

  bool was_running = s_state.running;
  s_state.started_at_ms = was_running ? (util_now_ms() - next_elapsed_ms) : 0;
  s_state.paused_elapsed_ms = next_elapsed_ms;
  s_state.awaiting_ack = false;
  s_state.ack_silenced = false;
  s_state.ack_started_at_ms = 0;
  s_last_phase_index = next_segment;
  s_last_iteration_index = next_iteration;
  timer_cancel_ack_timer();
  if (was_running) {
    timer_play_segment_vibration(&timer->segments[next_segment]);
    prv_schedule_finish_wakeup();
  } else {
    timer_cancel_wakeup();
  }
  config_persist_state();
  timer_ensure_refresh_timer();
  ui_refresh();
  return true;
}

static const UpActionDefinition *prv_current_up_action_definition(bool long_press) {
  const TimerDefinition *timer = s_state.active ? timer_active_timer() : timer_selected_timer();
  if (!timer) {
    return NULL;
  }
  return long_press ? &timer->on_long_press_up : &timer->on_press_up;
}

static bool prv_adjust_active_timer(uint64_t delta_ms, bool increment) {
  if (s_state.active && (s_state.completed || s_state.awaiting_ack)) {
    return false;
  }

  const TimerDefinition *timer = s_state.active ? timer_active_timer() : timer_selected_timer();
  if (!timer) {
    return false;
  }

  if (increment) {
    if (delta_ms > (uint64_t)INT64_MAX - (uint64_t)(s_state.duration_adjustment_ms > 0
        ? s_state.duration_adjustment_ms : 0)) {
      s_state.duration_adjustment_ms = INT64_MAX;
    } else {
      s_state.duration_adjustment_ms += (int64_t)delta_ms;
    }
  } else {
    if (delta_ms > (uint64_t)INT64_MAX - (uint64_t)(s_state.duration_adjustment_ms < 0
        ? -s_state.duration_adjustment_ms : 0)) {
      s_state.duration_adjustment_ms = -INT64_MAX;
    } else {
      s_state.duration_adjustment_ms -= (int64_t)delta_ms;
    }
  }

  if (s_state.active) {
    s_state.completed = false;
    s_state.alert_fired = false;
    s_state.ack_silenced = false;
    s_state.ack_started_at_ms = 0;
    timer_cancel_ack_timer();

    timer_update_running_state();
    if (s_state.running) {
      prv_schedule_finish_wakeup();
    } else if (!s_state.awaiting_ack) {
      timer_cancel_wakeup();
    }
  }
  config_persist_state();
  timer_ensure_refresh_timer();
  ui_refresh();
  return true;
}

UpAction timer_current_up_action(bool long_press) {
  if (s_state.awaiting_ack) {
    return (!long_press && !s_state.ack_silenced) ? UP_ACTION_MUTE : UP_ACTION_NONE;
  }
  const UpActionDefinition *action = prv_current_up_action_definition(long_press);
  if (!action) {
    return UP_ACTION_NONE;
  }
  return action->kind;
}

bool timer_up_action_available(UpAction action) {
  switch (action) {
    case UP_ACTION_SKIP:
      return ui_skip_hint_visible();
    case UP_ACTION_HIDE:
    case UP_ACTION_MUTE:
      return true;
    case UP_ACTION_INCREMENT:
    case UP_ACTION_DECREMENT:
      if (s_state.active) {
        return !s_state.completed && !s_state.awaiting_ack && timer_active_timer() != NULL;
      }
      return timer_selected_timer() != NULL;
    case UP_ACTION_NONE:
    default:
      return false;
  }
}

bool timer_handle_up_action(bool long_press) {
  UpAction action = timer_current_up_action(long_press);
  const UpActionDefinition *definition = prv_current_up_action_definition(long_press);
  switch (action) {
    case UP_ACTION_SKIP:
      if (s_state.active) {
        return timer_skip_active_segment();
      }
      return timer_skip_selected_segment();
    case UP_ACTION_HIDE:
      return ui_toggle_text_hidden();
    case UP_ACTION_INCREMENT:
      return definition ? prv_adjust_active_timer(definition->duration_ms, true) : false;
    case UP_ACTION_DECREMENT:
      return definition ? prv_adjust_active_timer(definition->duration_ms, false) : false;
    case UP_ACTION_MUTE:
      timer_silence_acknowledgement(true);
      return true;
    case UP_ACTION_NONE:
    default:
      return false;
  }
}

void timer_handle_launch_wakeup(void) {
  if (launch_reason() != APP_LAUNCH_WAKEUP) {
    return;
  }
  WakeupId id = 0;
  int32_t cookie = 0;
  if (wakeup_get_launch_event(&id, &cookie)) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "wakeup launch id=%ld cookie=%ld", (long)id, (long)cookie);
  }
  timer_update_running_state();
}

void timer_wakeup_handler(WakeupId wakeup_id, int32_t cookie) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "wakeup id=%ld cookie=%ld", (long)wakeup_id, (long)cookie);
  if (cookie == WAKEUP_COOKIE_FINISH) {
    timer_update_running_state();
    ui_refresh();
  }
}

void timer_restore_ack_repeat_if_needed(void) {
  if (!s_state.awaiting_ack || !s_state.active) {
    return;
  }
  const TimerDefinition *timer = timer_active_timer();
  TimerSnapshot snap = timer_current_snapshot();
  if (timer && snap.valid && !snap.completed && snap.phase_index < timer->segment_count) {
    prv_schedule_ack_repeat(&timer->segments[snap.phase_index]);
  }
}
