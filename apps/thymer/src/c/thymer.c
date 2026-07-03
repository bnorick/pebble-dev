#include <pebble.h>

#include "config.h"
#include "timer.h"
#include "ui.h"

static void prv_init(void) {
  bool had_persisted_config = config_has_persisted_config();
  config_load();
  config_load_state();
  timer_handle_launch_wakeup();

  Window *window = ui_create_window();

  app_message_register_inbox_received(config_inbox_received);
  app_message_register_inbox_dropped(config_inbox_dropped);
  app_message_register_outbox_failed(config_outbox_failed);
  app_message_open(1024, 256);

  wakeup_service_subscribe(timer_wakeup_handler);

  window_stack_push(window, true);

  ui_refresh();
  timer_restore_ack_repeat_if_needed();
  timer_ensure_refresh_timer();
  if (!had_persisted_config) {
    config_send_request();
  }
}

static void prv_deinit(void) {
  timer_cancel_refresh_timer();
  timer_cancel_ack_timer();
  config_persist_state();
  ui_destroy_window();
  config_deinit();
}

int main(void) {
  prv_init();
  app_event_loop();
  prv_deinit();
}
