#include "ui.h"

#include "app_state.h"
#include "input.h"
#include "timer.h"
#include "thymer.h"
#include "util.h"

static Window *s_window;
static BitmapLayer *s_background_layer;
static BitmapLayer *s_focus_panel_top_layer;
static BitmapLayer *s_focus_panel_mid_layer;
static BitmapLayer *s_focus_panel_bottom_layer;
static TextLayer *s_title_layer;
static TextLayer *s_hint_layer;
static TextLayer *s_timer_layer;
static TextLayer *s_status_layer;
static TextLayer *s_detail_layer;
static TextLayer *s_footer_layer;
static BitmapLayer *s_skip_icon_layer;
static BitmapLayer *s_hide_icon_layer;
static BitmapLayer *s_select_icon_layer;
static BitmapLayer *s_reset_icon_layer;
static TextLayer *s_up_long_hint_layer;

static AppTimer *s_config_notice_timer;

static GBitmap *s_play_icon;
static GBitmap *s_pause_icon;
static GBitmap *s_skip_icon;
static GBitmap *s_hide_icon;
static GBitmap *s_mute_icon;
static GBitmap *s_increment_icon;
static GBitmap *s_decrement_icon;
static GBitmap *s_reset_icon;
static GBitmap *s_background_bitmap;
static GBitmap *s_focus_panel_top_bitmap;
static GBitmap *s_focus_panel_mid_bitmap;
static GBitmap *s_focus_panel_bottom_bitmap;

static char s_time_buffer[24];
static char s_iteration_buffer[24];

enum {
  TITLE_TOP = 4,
  TITLE_HEIGHT = 40,
  HINT_MAX_HEIGHT = 40,
  SEGMENT_MAX_HEIGHT = 72,
  SEGMENT_DESCENDER_PADDING = 4,
  TIMER_HEIGHT = 44,
  DETAIL_MAX_HEIGHT = 32,
  FOOTER_HEIGHT = 30,
  FOOTER_BOTTOM_MARGIN = 2,
  STACK_SIDE_MARGIN = 8,
  TITLE_STACK_GAP = 4,
  STACK_VERTICAL_GAP = 2,
  TIMER_STACK_GAP = 4,
};

static bool prv_text_is_empty(const char *text) {
  return !text || text[0] == '\0';
}

static GBitmap *prv_up_action_icon(UpAction action) {
  switch (action) {
    case UP_ACTION_SKIP:
      return s_skip_icon;
    case UP_ACTION_HIDE:
      return s_hide_icon;
    case UP_ACTION_INCREMENT:
      return s_increment_icon;
    case UP_ACTION_DECREMENT:
      return s_decrement_icon;
    case UP_ACTION_MUTE:
      return s_mute_icon;
    case UP_ACTION_NONE:
    default:
      return NULL;
  }
}

static int16_t prv_measure_text_height(const char *text, GFont font, int16_t width,
                                       int16_t max_height) {
  if (prv_text_is_empty(text) || width <= 0 || max_height <= 0) {
    return 0;
  }

  GSize size = graphics_text_layout_get_content_size(
    text, font, GRect(0, 0, width, max_height), GTextOverflowModeWordWrap, GTextAlignmentCenter);
  return size.h > max_height ? max_height : size.h;
}

static void prv_layout_focus_panel(void) {
  if (!SHOW_TIMER_BACKGROUND) {
    return;
  }
  if (!s_window || !s_focus_panel_top_layer || !s_focus_panel_mid_layer ||
      !s_focus_panel_bottom_layer || !s_timer_layer) {
    return;
  }

  GRect timer_frame = layer_get_frame(text_layer_get_layer(s_timer_layer));
  int16_t content_top = timer_frame.origin.y;
  int16_t content_bottom = timer_frame.origin.y + timer_frame.size.h;

  TextLayer *layers[] = { s_hint_layer, s_status_layer };
  for (size_t i = 0; i < ARRAY_LENGTH(layers); ++i) {
    if (!layers[i]) {
      continue;
    }
    Layer *layer = text_layer_get_layer(layers[i]);
    if (layer_get_hidden(layer)) {
      continue;
    }
    GRect frame = layer_get_frame(layer);
    if (frame.origin.y < content_top) {
      content_top = frame.origin.y;
    }
    int16_t frame_bottom = frame.origin.y + frame.size.h;
    if (frame_bottom > content_bottom) {
      content_bottom = frame_bottom;
    }
  }

  Layer *window_layer = window_get_root_layer(s_window);
  GRect bounds = layer_get_bounds(window_layer);
  int16_t origin_x = (bounds.size.w - FOCUS_PANEL_BITMAP_WIDTH) / 2;
  int16_t origin_y = content_top - 2;
  int16_t panel_height = content_bottom - content_top + 12;
  int16_t min_height = FOCUS_PANEL_TOP_HEIGHT + FOCUS_PANEL_BOTTOM_HEIGHT;
  if (panel_height < min_height) {
    panel_height = min_height;
  }
  if (panel_height > FOCUS_PANEL_BITMAP_HEIGHT) {
    panel_height = FOCUS_PANEL_BITMAP_HEIGHT;
  }
  int16_t mid_height = panel_height - FOCUS_PANEL_TOP_HEIGHT - FOCUS_PANEL_BOTTOM_HEIGHT;

  layer_set_frame(bitmap_layer_get_layer(s_focus_panel_top_layer),
                  GRect(origin_x, origin_y, FOCUS_PANEL_BITMAP_WIDTH, FOCUS_PANEL_TOP_HEIGHT));
  layer_set_frame(bitmap_layer_get_layer(s_focus_panel_mid_layer),
                  GRect(origin_x, origin_y + FOCUS_PANEL_TOP_HEIGHT,
                        FOCUS_PANEL_BITMAP_WIDTH, mid_height));
  layer_set_frame(bitmap_layer_get_layer(s_focus_panel_bottom_layer),
                  GRect(origin_x, origin_y + FOCUS_PANEL_TOP_HEIGHT + mid_height,
                        FOCUS_PANEL_BITMAP_WIDTH, FOCUS_PANEL_BOTTOM_HEIGHT));
  layer_set_hidden(bitmap_layer_get_layer(s_focus_panel_mid_layer), mid_height <= 0);
}

static void prv_set_focus_panel_hidden(bool hidden) {
  if (!SHOW_TIMER_BACKGROUND || !s_focus_panel_top_layer || !s_focus_panel_mid_layer ||
      !s_focus_panel_bottom_layer) {
    return;
  }
  bool has_mid = layer_get_frame(bitmap_layer_get_layer(s_focus_panel_mid_layer)).size.h > 0;
  layer_set_hidden(bitmap_layer_get_layer(s_focus_panel_top_layer), hidden);
  layer_set_hidden(bitmap_layer_get_layer(s_focus_panel_mid_layer), hidden || !has_mid);
  layer_set_hidden(bitmap_layer_get_layer(s_focus_panel_bottom_layer), hidden);
}

void ui_refresh_background_layers(void) {
  if (s_background_layer) {
    layer_set_hidden(bitmap_layer_get_layer(s_background_layer), !s_config.background_enabled);
  }
  if (s_focus_panel_top_layer && s_focus_panel_mid_layer && s_focus_panel_bottom_layer) {
    bool hidden = !s_config.timer_accent_enabled || s_text_hidden;
    prv_set_focus_panel_hidden(hidden);
  }
}

static void prv_cancel_config_notice_timer(void) {
  if (s_config_notice_timer) {
    app_timer_cancel(s_config_notice_timer);
    s_config_notice_timer = NULL;
  }
}

static void prv_config_notice_timer_callback(void *context) {
  (void)context;
  s_config_notice_timer = NULL;
  s_show_config_notice = false;
  ui_refresh();
}

void ui_show_config_notice(void) {
  static const VibeStep update_vibe = {
    .intensity = VIBE_INTENSITY_LOW,
    .duration_ms = 100,
    .delay_ms = 100,
  };

  prv_cancel_config_notice_timer();
  s_show_config_notice = true;
  timer_play_vibration_pattern(&update_vibe, 1);
  s_config_notice_timer = app_timer_register(1500, prv_config_notice_timer_callback, NULL);
}

void ui_apply_text_hidden(bool hidden) {
  s_text_hidden = hidden;
  if (!s_title_layer || !s_hint_layer || !s_timer_layer || !s_status_layer || !s_detail_layer ||
      !s_footer_layer) {
    return;
  }
  prv_set_focus_panel_hidden(hidden);
  layer_set_hidden(text_layer_get_layer(s_title_layer), hidden);
  layer_set_hidden(text_layer_get_layer(s_hint_layer), hidden);
  layer_set_hidden(text_layer_get_layer(s_timer_layer), hidden);
  layer_set_hidden(text_layer_get_layer(s_status_layer), hidden);
  layer_set_hidden(text_layer_get_layer(s_detail_layer), hidden);
  layer_set_hidden(text_layer_get_layer(s_footer_layer), hidden);
}

bool ui_toggle_text_hidden(void) {
  ui_apply_text_hidden(!s_text_hidden);
  ui_refresh();
  return true;
}

bool ui_reveal_text_if_hidden(void) {
  if (!s_text_hidden) {
    return false;
  }
  ui_apply_text_hidden(false);
  ui_refresh();
  return true;
}

bool ui_skip_hint_visible(void) {
  if (s_state.active) {
    if (s_state.running || s_state.completed || s_state.awaiting_ack) {
      return false;
    }

    const TimerDefinition *timer = timer_active_timer();
    if (!timer_allows_skip(timer)) {
      return false;
    }

    TimerSnapshot snap = timer_current_snapshot();
    if (!snap.valid || snap.completed) {
      return false;
    }

    uint16_t next_iteration = 0;
    uint8_t next_segment = 0;
    uint64_t next_elapsed_ms = 0;
    return timer_next_segment_after(timer, &snap, &next_segment, &next_iteration, &next_elapsed_ms);
  }

  return timer_allows_skip(timer_selected_timer());
}

static void prv_refresh_button_hints(void) {
  if (!s_select_icon_layer || !s_reset_icon_layer || !s_skip_icon_layer || !s_hide_icon_layer ||
      !s_up_long_hint_layer) {
    return;
  }

  if (!s_config.icons_enabled) {
    layer_set_hidden(bitmap_layer_get_layer(s_select_icon_layer), true);
    layer_set_hidden(bitmap_layer_get_layer(s_reset_icon_layer), true);
    layer_set_hidden(bitmap_layer_get_layer(s_skip_icon_layer), true);
    layer_set_hidden(bitmap_layer_get_layer(s_hide_icon_layer), true);
    layer_set_hidden(text_layer_get_layer(s_up_long_hint_layer), true);
    return;
  }

  bitmap_layer_set_bitmap(s_select_icon_layer,
                          (s_state.active && s_state.running && !s_state.awaiting_ack &&
                           !s_state.completed) ? s_pause_icon : s_play_icon);
  bitmap_layer_set_bitmap(s_reset_icon_layer, s_reset_icon);
  bitmap_layer_set_bitmap(s_skip_icon_layer, s_skip_icon);
  bitmap_layer_set_bitmap(s_hide_icon_layer, s_hide_icon);

  if (s_text_hidden) {
    layer_set_hidden(bitmap_layer_get_layer(s_select_icon_layer), true);
    layer_set_hidden(bitmap_layer_get_layer(s_reset_icon_layer), true);
    layer_set_hidden(bitmap_layer_get_layer(s_skip_icon_layer), true);
    layer_set_hidden(bitmap_layer_get_layer(s_hide_icon_layer), true);
    layer_set_hidden(text_layer_get_layer(s_up_long_hint_layer), true);
    return;
  }

  UpAction short_action = timer_current_up_action(false);
  UpAction long_action = timer_current_up_action(true);
  bool short_visible = timer_up_action_available(short_action);
  bool long_visible = timer_up_action_available(long_action);
  UpAction shown_action = short_visible ? short_action : (long_visible ? long_action : UP_ACTION_NONE);
  bool show_long_marker = (short_visible && long_visible && short_action != long_action) ||
                          (!short_visible && long_visible);

  layer_set_hidden(bitmap_layer_get_layer(s_select_icon_layer), false);
  bitmap_layer_set_bitmap(s_skip_icon_layer, prv_up_action_icon(shown_action));
  layer_set_hidden(bitmap_layer_get_layer(s_skip_icon_layer), shown_action == UP_ACTION_NONE);
  layer_set_hidden(bitmap_layer_get_layer(s_hide_icon_layer), true);
  text_layer_set_text(s_up_long_hint_layer, show_long_marker ? "L" : "");
  layer_set_hidden(text_layer_get_layer(s_up_long_hint_layer), !show_long_marker);
  layer_set_hidden(bitmap_layer_get_layer(s_reset_icon_layer), !timer_reset_available());
}

static void prv_layout_text_layers(void) {
  if (!s_window || !s_title_layer || !s_hint_layer || !s_status_layer || !s_timer_layer ||
      !s_detail_layer || !s_footer_layer) {
    return;
  }

  Layer *window_layer = window_get_root_layer(s_window);
  GRect bounds = layer_get_bounds(window_layer);
  const char *title_text = text_layer_get_text(s_title_layer);
  const char *hint_text = text_layer_get_text(s_hint_layer);
  const char *status_text = text_layer_get_text(s_status_layer);
  const char *detail_text = text_layer_get_text(s_detail_layer);
  const char *footer_text = text_layer_get_text(s_footer_layer);

  bool show_title = !prv_text_is_empty(title_text);
  bool show_hint = !prv_text_is_empty(hint_text);
  bool show_status = !prv_text_is_empty(status_text);
  bool show_detail = !prv_text_is_empty(detail_text);
  bool show_footer = !prv_text_is_empty(footer_text);

  int16_t content_width = bounds.size.w - (STACK_SIDE_MARGIN * 2);
  // NOTE: Keep the timer locked to the visual center; only the surrounding text may flex.
  int16_t timer_y = (bounds.size.h - TIMER_HEIGHT) / 2 - 5;
  int16_t footer_y = bounds.size.h - FOOTER_HEIGHT - FOOTER_BOTTOM_MARGIN;

  layer_set_frame(text_layer_get_layer(s_title_layer),
                  GRect(STACK_SIDE_MARGIN, TITLE_TOP, content_width, TITLE_HEIGHT));
  layer_set_frame(text_layer_get_layer(s_timer_layer), GRect(0, timer_y, bounds.size.w, TIMER_HEIGHT));
  layer_set_frame(text_layer_get_layer(s_footer_layer),
                  GRect(STACK_SIDE_MARGIN, footer_y, content_width, FOOTER_HEIGHT));

  int16_t available_above = timer_y - (TITLE_TOP + TITLE_HEIGHT + TITLE_STACK_GAP);
  if (available_above < 0) {
    available_above = 0;
  }

  int16_t hint_height = show_hint
    ? prv_measure_text_height(hint_text, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD),
                              content_width, HINT_MAX_HEIGHT)
    : 0;
  int16_t status_height = show_status
    ? prv_measure_text_height(status_text, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD),
                              content_width, SEGMENT_MAX_HEIGHT)
    : 0;
  if (show_status && status_height > 0) {
    // Keep a little extra bottom room for descenders like "y" without moving the timer.
    status_height += SEGMENT_DESCENDER_PADDING;
  }
  int16_t above_gap = (show_hint && show_status) ? STACK_VERTICAL_GAP : 0;
  int16_t above_height = hint_height + status_height + above_gap;
  if (above_height > available_above) {
    int16_t overflow = above_height - available_above;
    if (show_hint && hint_height > 0) {
      int16_t reducible = hint_height - 18;
      if (reducible > 0) {
        int16_t reduction = overflow < reducible ? overflow : reducible;
        hint_height -= reduction;
        overflow -= reduction;
      }
    }
    if (overflow > 0 && show_status && status_height > 0) {
      int16_t reducible = status_height - 28;
      if (reducible > 0) {
        int16_t reduction = overflow < reducible ? overflow : reducible;
        status_height -= reduction;
      }
    }
    above_height = hint_height + status_height + above_gap;
  }

  int16_t stack_bottom = timer_y - TIMER_STACK_GAP;
  int16_t stack_y = stack_bottom - above_height;
  if (stack_y < TITLE_TOP + TITLE_HEIGHT + TITLE_STACK_GAP) {
    stack_y = TITLE_TOP + TITLE_HEIGHT + TITLE_STACK_GAP;
  }

  int16_t current_y = stack_y;
  layer_set_frame(text_layer_get_layer(s_hint_layer),
                  GRect(STACK_SIDE_MARGIN, current_y, content_width, hint_height));
  if (show_hint) {
    current_y += hint_height + above_gap;
  }
  layer_set_frame(text_layer_get_layer(s_status_layer),
                  GRect(STACK_SIDE_MARGIN, current_y, content_width, status_height));

  int16_t available_below = footer_y - TIMER_STACK_GAP - (timer_y + TIMER_HEIGHT);
  if (available_below < 0) {
    available_below = 0;
  }
  int16_t detail_height = show_detail
    ? prv_measure_text_height(detail_text, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD),
                              content_width, DETAIL_MAX_HEIGHT)
    : 0;
  if (detail_height > available_below) {
    detail_height = available_below;
  }
  int16_t detail_y = timer_y + TIMER_HEIGHT + TIMER_STACK_GAP;
  layer_set_frame(text_layer_get_layer(s_detail_layer),
                  GRect(STACK_SIDE_MARGIN, detail_y, content_width, detail_height));

  layer_set_hidden(text_layer_get_layer(s_title_layer), s_text_hidden || !show_title);
  layer_set_hidden(text_layer_get_layer(s_hint_layer), s_text_hidden || !show_hint);
  layer_set_hidden(text_layer_get_layer(s_status_layer), s_text_hidden || !show_status);
  layer_set_hidden(text_layer_get_layer(s_timer_layer), s_text_hidden);
  layer_set_hidden(text_layer_get_layer(s_detail_layer), s_text_hidden || !show_detail);
  layer_set_hidden(text_layer_get_layer(s_footer_layer), s_text_hidden || !show_footer);
}

void ui_refresh(void) {
  if (!s_window) {
    return;
  }

  if (s_waiting_for_initial_config) {
    text_layer_set_text(s_title_layer, APP_NAME);
    text_layer_set_text(s_hint_layer, "");
    text_layer_set_text(s_timer_layer, "");
    text_layer_set_text(s_status_layer, "Loading...");
    text_layer_set_text(s_detail_layer, "");
    text_layer_set_text(s_footer_layer, "");
    prv_layout_text_layers();
    prv_layout_focus_panel();
    prv_set_focus_panel_hidden(true);
    ui_refresh_background_layers();
    prv_refresh_button_hints();
    return;
  }

  const TimerDefinition *selected = timer_selected_timer();
  const TimerDefinition *active = s_state.active ? timer_active_timer() : selected;

  if (s_show_config_notice) {
    text_layer_set_text(s_title_layer, APP_NAME);
    text_layer_set_text(s_hint_layer, "");
    text_layer_set_text(s_timer_layer, "");
    text_layer_set_text(s_status_layer, "Updated");
    text_layer_set_text(s_detail_layer, "");
    text_layer_set_text(s_footer_layer, "");
    prv_layout_text_layers();
    prv_layout_focus_panel();
    prv_set_focus_panel_hidden(true);
    ui_refresh_background_layers();
    prv_refresh_button_hints();
    return;
  }

  if (!selected) {
    text_layer_set_text(s_title_layer, APP_NAME);
    text_layer_set_text(s_hint_layer, "");
    text_layer_set_text(s_timer_layer, "--:--");
    text_layer_set_text(s_status_layer, "No timers configured");
    text_layer_set_text(s_detail_layer, "");
    text_layer_set_text(s_footer_layer, "");
    prv_layout_text_layers();
    prv_layout_focus_panel();
    prv_set_focus_panel_hidden(s_text_hidden);
    ui_refresh_background_layers();
    prv_refresh_button_hints();
    return;
  }

  if ((selected->segment_count == 0 || !selected->segments) ||
      (active && (active->segment_count == 0 || !active->segments))) {
    text_layer_set_text(s_title_layer, active ? active->name : selected->name);
    text_layer_set_text(s_hint_layer, "");
    text_layer_set_text(s_timer_layer, "--:--");
    text_layer_set_text(s_status_layer, "Timer has no steps");
    text_layer_set_text(s_detail_layer, "");
    text_layer_set_text(s_footer_layer, "");
    prv_layout_text_layers();
    prv_layout_focus_panel();
    prv_set_focus_panel_hidden(s_text_hidden);
    ui_refresh_background_layers();
    prv_refresh_button_hints();
    return;
  }

  const char *segment_name = "";
  const char *segment_hint = "";
  const char *state_text = "";

  text_layer_set_text(s_title_layer, active ? active->name : selected->name);

  if (s_state.active && active) {
    TimerSnapshot snap = timer_current_snapshot();
    const TimerSegment *segment = &active->segments[snap.phase_index];
    uint64_t shown_remaining_ms = s_state.duration_adjustment_ms != 0
      ? snap.total_remaining_ms
      : snap.phase_remaining_ms;
    util_format_duration(shown_remaining_ms, s_time_buffer, sizeof(s_time_buffer));

    s_iteration_buffer[0] = '\0';
    if (active->repeat) {
      if (active->iterations_enabled && active->iterations > 0) {
        snprintf(s_iteration_buffer, sizeof(s_iteration_buffer), "iter %u/%u",
                 (unsigned)(snap.iteration_index + 1), (unsigned)active->iterations);
      } else {
        snprintf(s_iteration_buffer, sizeof(s_iteration_buffer), "iter %u",
                 (unsigned)(snap.iteration_index + 1));
      }
    }

    segment_name = segment->name;
    segment_hint = segment->hint;
    if (s_state.awaiting_ack) {
      state_text = "Press select";
    } else if (!s_state.running && !snap.completed && !s_state.completed) {
      state_text = "Paused";
    }
  } else {
    uint8_t preview_segment = timer_allows_skip(selected)
      ? timer_clamp_segment_index(selected, s_selected_segment)
      : 0;
    uint64_t shown_duration_ms = s_state.duration_adjustment_ms != 0
      ? timer_adjusted_total_duration_ms(selected)
      : selected->segments[preview_segment].duration_ms;
    util_format_duration(shown_duration_ms, s_time_buffer, sizeof(s_time_buffer));
    segment_name = selected->segments[preview_segment].name;
    segment_hint = selected->segments[preview_segment].hint;
    s_iteration_buffer[0] = '\0';
  }

  text_layer_set_text(s_timer_layer, s_time_buffer);
  text_layer_set_text(s_hint_layer, segment_hint);
  text_layer_set_text(s_status_layer, segment_name);
  text_layer_set_text(s_detail_layer, state_text);
  text_layer_set_text(s_footer_layer, s_iteration_buffer);
  prv_layout_text_layers();
  prv_layout_focus_panel();
  prv_set_focus_panel_hidden(s_text_hidden);
  ui_refresh_background_layers();
  prv_refresh_button_hints();
}

static void prv_window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  if (bounds.size.w == 200 && bounds.size.h == 228) {
    s_background_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BACKGROUND);
    s_background_layer = bitmap_layer_create(bounds);
    bitmap_layer_set_bitmap(s_background_layer, s_background_bitmap);
    bitmap_layer_set_background_color(s_background_layer, GColorClear);
    bitmap_layer_set_compositing_mode(s_background_layer, GCompOpSet);
    layer_add_child(window_layer, bitmap_layer_get_layer(s_background_layer));
  }

  if (SHOW_TIMER_BACKGROUND) {
    s_focus_panel_top_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TIMER_BG_TOP);
    s_focus_panel_mid_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TIMER_BG_MID);
    s_focus_panel_bottom_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TIMER_BG_BOT);

    s_focus_panel_top_layer = bitmap_layer_create(
      GRect(0, 0, FOCUS_PANEL_BITMAP_WIDTH, FOCUS_PANEL_TOP_HEIGHT));
    s_focus_panel_mid_layer = bitmap_layer_create(
      GRect(0, 0, FOCUS_PANEL_BITMAP_WIDTH, FOCUS_PANEL_MID_HEIGHT));
    s_focus_panel_bottom_layer = bitmap_layer_create(
      GRect(0, 0, FOCUS_PANEL_BITMAP_WIDTH, FOCUS_PANEL_BOTTOM_HEIGHT));

    bitmap_layer_set_bitmap(s_focus_panel_top_layer, s_focus_panel_top_bitmap);
    bitmap_layer_set_bitmap(s_focus_panel_mid_layer, s_focus_panel_mid_bitmap);
    bitmap_layer_set_bitmap(s_focus_panel_bottom_layer, s_focus_panel_bottom_bitmap);
    bitmap_layer_set_background_color(s_focus_panel_top_layer, GColorClear);
    bitmap_layer_set_background_color(s_focus_panel_mid_layer, GColorClear);
    bitmap_layer_set_background_color(s_focus_panel_bottom_layer, GColorClear);
    bitmap_layer_set_compositing_mode(s_focus_panel_top_layer, GCompOpSet);
    bitmap_layer_set_compositing_mode(s_focus_panel_mid_layer, GCompOpSet);
    bitmap_layer_set_compositing_mode(s_focus_panel_bottom_layer, GCompOpSet);
    layer_add_child(window_layer, bitmap_layer_get_layer(s_focus_panel_top_layer));
    layer_add_child(window_layer, bitmap_layer_get_layer(s_focus_panel_mid_layer));
    layer_add_child(window_layer, bitmap_layer_get_layer(s_focus_panel_bottom_layer));
  }

  s_title_layer = text_layer_create(GRect(8, 4, bounds.size.w - 16, 40));
  text_layer_set_background_color(s_title_layer, GColorClear);
  text_layer_set_text_color(s_title_layer, GColorBlack);
  text_layer_set_font(s_title_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
  text_layer_set_text_alignment(s_title_layer, GTextAlignmentCenter);
  text_layer_set_overflow_mode(s_title_layer, GTextOverflowModeWordWrap);
  layer_add_child(window_layer, text_layer_get_layer(s_title_layer));

  s_hint_layer = text_layer_create(GRect(8, 42, bounds.size.w - 16, 22));
  text_layer_set_background_color(s_hint_layer, GColorClear);
  text_layer_set_text_color(s_hint_layer, GColorDarkGray);
  text_layer_set_font(s_hint_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
  text_layer_set_text_alignment(s_hint_layer, GTextAlignmentCenter);
  text_layer_set_overflow_mode(s_hint_layer, GTextOverflowModeWordWrap);
  layer_add_child(window_layer, text_layer_get_layer(s_hint_layer));

  s_status_layer = text_layer_create(GRect(8, 60, bounds.size.w - 16, 44));
  text_layer_set_background_color(s_status_layer, GColorClear);
  text_layer_set_text_color(s_status_layer, GColorBlack);
  text_layer_set_font(s_status_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
  text_layer_set_text_alignment(s_status_layer, GTextAlignmentCenter);
  text_layer_set_overflow_mode(s_status_layer, GTextOverflowModeWordWrap);
  layer_add_child(window_layer, text_layer_get_layer(s_status_layer));

  s_timer_layer = text_layer_create(GRect(0, 104, bounds.size.w, 44));
  text_layer_set_background_color(s_timer_layer, GColorClear);
  text_layer_set_text_color(s_timer_layer, GColorBlack);
  text_layer_set_font(s_timer_layer, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
  text_layer_set_text_alignment(s_timer_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(s_timer_layer));

  s_detail_layer = text_layer_create(GRect(8, bounds.size.h - 34, bounds.size.w - 16, 28));
  text_layer_set_background_color(s_detail_layer, GColorClear);
  text_layer_set_text_color(s_detail_layer, GColorDarkGray);
  text_layer_set_font(s_detail_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
  text_layer_set_text_alignment(s_detail_layer, GTextAlignmentCenter);
  text_layer_set_overflow_mode(s_detail_layer, GTextOverflowModeWordWrap);
  layer_add_child(window_layer, text_layer_get_layer(s_detail_layer));

  s_footer_layer = text_layer_create(GRect(8, bounds.size.h - 32, bounds.size.w - 16, 30));
  text_layer_set_background_color(s_footer_layer, GColorClear);
  text_layer_set_text_color(s_footer_layer, GColorDarkGray);
  text_layer_set_font(s_footer_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
  text_layer_set_text_alignment(s_footer_layer, GTextAlignmentCenter);
  text_layer_set_overflow_mode(s_footer_layer, GTextOverflowModeWordWrap);
  layer_add_child(window_layer, text_layer_get_layer(s_footer_layer));

  s_up_long_hint_layer = text_layer_create(
    GRect(bounds.size.w - 12, (bounds.size.h / 4) - 18, 12, 12));
  text_layer_set_background_color(s_up_long_hint_layer, GColorClear);
  text_layer_set_text_color(s_up_long_hint_layer, GColorDarkGray);
  text_layer_set_font(s_up_long_hint_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14));
  text_layer_set_text_alignment(s_up_long_hint_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(s_up_long_hint_layer));

  s_play_icon = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_PLAY);
  s_pause_icon = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_PAUSE);
  s_skip_icon = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_SKIP);
  s_hide_icon = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_HIDE);
  s_mute_icon = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_MUTE);
  s_increment_icon = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_INCREMENT);
  s_decrement_icon = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_DECREMENT);
  s_reset_icon = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_RESET);

  int16_t icon_x = bounds.size.w - BUTTON_HINT_WIDTH;
  s_skip_icon_layer = bitmap_layer_create(
    GRect(icon_x, (bounds.size.h / 4) - BUTTON_HINT_ICON_HALF + BUTTON_HINT_TOP_OFFSET,
          BUTTON_HINT_ICON_SIZE, BUTTON_HINT_ICON_SIZE));
  bitmap_layer_set_background_color(s_skip_icon_layer, GColorClear);
  bitmap_layer_set_compositing_mode(s_skip_icon_layer, GCompOpSet);
  layer_add_child(window_layer, bitmap_layer_get_layer(s_skip_icon_layer));

  s_hide_icon_layer = bitmap_layer_create(
    GRect(icon_x, (bounds.size.h / 4) - BUTTON_HINT_ICON_HALF + BUTTON_HINT_TOP_OFFSET,
          BUTTON_HINT_ICON_SIZE, BUTTON_HINT_ICON_SIZE));
  bitmap_layer_set_background_color(s_hide_icon_layer, GColorClear);
  bitmap_layer_set_compositing_mode(s_hide_icon_layer, GCompOpSet);
  layer_add_child(window_layer, bitmap_layer_get_layer(s_hide_icon_layer));

  s_select_icon_layer = bitmap_layer_create(
    GRect(icon_x, (bounds.size.h / 2) - BUTTON_HINT_ICON_HALF,
          BUTTON_HINT_ICON_SIZE, BUTTON_HINT_ICON_SIZE));
  bitmap_layer_set_background_color(s_select_icon_layer, GColorClear);
  bitmap_layer_set_compositing_mode(s_select_icon_layer, GCompOpSet);
  layer_add_child(window_layer, bitmap_layer_get_layer(s_select_icon_layer));

  s_reset_icon_layer = bitmap_layer_create(
    GRect(icon_x, ((bounds.size.h * 3) / 4) - BUTTON_HINT_ICON_HALF + BUTTON_HINT_BOTTOM_OFFSET,
          BUTTON_HINT_ICON_SIZE, BUTTON_HINT_ICON_SIZE));
  bitmap_layer_set_background_color(s_reset_icon_layer, GColorClear);
  bitmap_layer_set_compositing_mode(s_reset_icon_layer, GCompOpSet);
  layer_add_child(window_layer, bitmap_layer_get_layer(s_reset_icon_layer));

  ui_refresh();
}

static void prv_window_appear(Window *window) {
  (void)window;
#if defined(PBL_TOUCH)
  if (touch_service_is_enabled()) {
    input_touch_subscribe();
  } else {
    text_layer_set_text(s_detail_layer, "Touch disabled in Settings -> Display");
  }
#endif
}

static void prv_window_disappear(Window *window) {
  (void)window;
#if defined(PBL_TOUCH)
  input_touch_unsubscribe();
#endif
}

static void prv_window_unload(Window *window) {
  (void)window;
  prv_cancel_config_notice_timer();

  if (s_background_layer) {
    bitmap_layer_destroy(s_background_layer);
    s_background_layer = NULL;
  }
  if (s_focus_panel_top_layer) {
    bitmap_layer_destroy(s_focus_panel_top_layer);
    s_focus_panel_top_layer = NULL;
  }
  if (s_focus_panel_mid_layer) {
    bitmap_layer_destroy(s_focus_panel_mid_layer);
    s_focus_panel_mid_layer = NULL;
  }
  if (s_focus_panel_bottom_layer) {
    bitmap_layer_destroy(s_focus_panel_bottom_layer);
    s_focus_panel_bottom_layer = NULL;
  }
  if (s_focus_panel_top_bitmap) {
    gbitmap_destroy(s_focus_panel_top_bitmap);
    s_focus_panel_top_bitmap = NULL;
  }
  if (s_focus_panel_mid_bitmap) {
    gbitmap_destroy(s_focus_panel_mid_bitmap);
    s_focus_panel_mid_bitmap = NULL;
  }
  if (s_focus_panel_bottom_bitmap) {
    gbitmap_destroy(s_focus_panel_bottom_bitmap);
    s_focus_panel_bottom_bitmap = NULL;
  }
  text_layer_destroy(s_title_layer);
  text_layer_destroy(s_hint_layer);
  text_layer_destroy(s_timer_layer);
  text_layer_destroy(s_status_layer);
  text_layer_destroy(s_detail_layer);
  text_layer_destroy(s_footer_layer);
  text_layer_destroy(s_up_long_hint_layer);
  bitmap_layer_destroy(s_skip_icon_layer);
  bitmap_layer_destroy(s_hide_icon_layer);
  bitmap_layer_destroy(s_select_icon_layer);
  bitmap_layer_destroy(s_reset_icon_layer);
  gbitmap_destroy(s_play_icon);
  gbitmap_destroy(s_pause_icon);
  gbitmap_destroy(s_skip_icon);
  gbitmap_destroy(s_hide_icon);
  gbitmap_destroy(s_mute_icon);
  gbitmap_destroy(s_increment_icon);
  gbitmap_destroy(s_decrement_icon);
  gbitmap_destroy(s_reset_icon);
  if (s_background_bitmap) {
    gbitmap_destroy(s_background_bitmap);
    s_background_bitmap = NULL;
  }
}

Window *ui_create_window(void) {
  if (s_window) {
    return s_window;
  }

  s_window = window_create();
  window_set_background_color(s_window, GColorWhite);
  window_set_click_config_provider(s_window, input_click_config_provider);
  window_set_window_handlers(s_window, (WindowHandlers){
    .load = prv_window_load,
    .appear = prv_window_appear,
    .disappear = prv_window_disappear,
    .unload = prv_window_unload,
  });
  return s_window;
}

void ui_destroy_window(void) {
  if (!s_window) {
    return;
  }
  window_destroy(s_window);
  s_window = NULL;
}

Window *ui_get_window(void) {
  return s_window;
}
