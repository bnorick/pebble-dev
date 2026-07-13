#pragma once

#include "thymer.h"

extern TimerConfig s_config;
extern TimerConfig s_candidate_config;
extern PendingConfig s_pending_config;
extern TimerState s_state;

extern uint8_t s_last_phase_index;
extern uint16_t s_last_iteration_index;
extern bool s_loading_config;
extern bool s_show_config_notice;
extern bool s_waiting_for_initial_config;
extern uint16_t s_config_progress_received;
extern uint16_t s_config_progress_total;
extern uint8_t s_selected_segment;
extern bool s_text_hidden;
extern char s_persist_debug_reason[64];
