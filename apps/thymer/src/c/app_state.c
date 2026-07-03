#include "app_state.h"

TimerConfig s_config;
TimerConfig s_candidate_config;
PendingConfig s_pending_config;
TimerState s_state;

uint8_t s_last_phase_index = 0xff;
uint16_t s_last_iteration_index = 0xffff;
bool s_show_config_notice = false;
bool s_waiting_for_initial_config = false;
uint8_t s_selected_segment = 0;
bool s_text_hidden = false;
char s_persist_debug_reason[64] = "";
