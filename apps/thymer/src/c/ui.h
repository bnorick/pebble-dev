#pragma once

#include <pebble.h>

Window *ui_create_window(void);
void ui_destroy_window(void);
Window *ui_get_window(void);
void ui_refresh(void);
void ui_refresh_background_layers(void);
bool ui_skip_hint_visible(void);
bool ui_text_hidden(void);
void ui_apply_text_hidden(bool hidden);
bool ui_toggle_text_hidden(void);
bool ui_reveal_text_if_hidden(void);
void ui_show_config_notice(void);
void ui_refresh_config_progress(void);
