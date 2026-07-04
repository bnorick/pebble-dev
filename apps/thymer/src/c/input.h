#pragma once

#include "thymer.h"

void input_click_config_provider(void *context);
#if defined(SCREENSHOT_SUPPORT)
bool input_select_timer_for_trigger(TriggerKind kind, TriggerZone from, TriggerZone to);
#endif
void input_touch_subscribe(void);
void input_touch_unsubscribe(void);
