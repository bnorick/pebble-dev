#pragma once

#include "thymer.h"

bool config_has_persisted_config(void);
void config_deinit(void);
void config_default_config(void);
void config_default_state(void);
void config_load(void);
void config_load_state(void);
void config_persist_config(void);
void config_persist_state(void);
void config_send_request(void);
void config_inbox_received(DictionaryIterator *iter, void *context);
void config_inbox_dropped(AppMessageResult reason, void *context);
void config_outbox_failed(DictionaryIterator *iter, AppMessageResult reason, void *context);
