#pragma once

#include "thymer.h"

const TimerDefinition *timer_selected_timer(void);
const TimerDefinition *timer_active_timer(void);
void timer_reset_phase_tracking(void);
uint64_t timer_cycle_duration_ms(const TimerDefinition *timer);
bool timer_allows_skip(const TimerDefinition *timer);
uint8_t timer_clamp_segment_index(const TimerDefinition *timer, uint8_t segment_index);
uint64_t timer_segment_start_elapsed_ms(const TimerDefinition *timer, uint8_t segment_index);
bool timer_has_finite_end(const TimerDefinition *timer);
uint64_t timer_total_duration_ms(const TimerDefinition *timer);
uint64_t timer_adjusted_total_duration_ms(const TimerDefinition *timer);
uint32_t timer_vibration_pattern_duration_ms(const VibeStep *steps, uint8_t step_count);
void timer_play_vibration_pattern(const VibeStep *steps, uint8_t step_count);
void timer_play_segment_vibration(const TimerSegment *segment);
TimerSnapshot timer_snapshot_for(const TimerDefinition *timer, uint64_t elapsed_ms);
TimerSnapshot timer_current_snapshot(void);
bool timer_next_segment_after(const TimerDefinition *timer,
                              const TimerSnapshot *snap,
                              uint8_t *next_segment,
                              uint16_t *next_iteration,
                              uint64_t *next_elapsed_ms);
void timer_update_running_state(void);
void timer_ensure_refresh_timer(void);
void timer_cancel_refresh_timer(void);
void timer_cancel_wakeup(void);
void timer_cancel_ack_timer(void);
void timer_start(uint8_t timer_index);
void timer_pause(void);
void timer_resume(void);
void timer_reset(void);
bool timer_reset_available(void);
void timer_dismiss_acknowledgement(bool reveal_text);
void timer_silence_acknowledgement(bool reveal_text);
bool timer_skip_selected_segment(void);
bool timer_skip_active_segment(void);
UpAction timer_current_up_action(bool long_press);
bool timer_up_action_available(UpAction action);
bool timer_handle_up_action(bool long_press);
void timer_handle_launch_wakeup(void);
void timer_wakeup_handler(WakeupId wakeup_id, int32_t cookie);
void timer_restore_ack_repeat_if_needed(void);
