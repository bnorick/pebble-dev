#include "util.h"

uint64_t util_now_ms(void) {
  time_t now_s = 0;
  uint16_t now_ms = time_ms(&now_s, NULL);
  return ((uint64_t)now_s * 1000ULL) + now_ms;
}

int32_t util_clamp_i32(int32_t value, int32_t min_value, int32_t max_value) {
  if (value < min_value) {
    return min_value;
  }
  if (value > max_value) {
    return max_value;
  }
  return value;
}

UpAction util_clamp_up_action(int32_t value) {
  return (UpAction)util_clamp_i32(value, UP_ACTION_NONE, UP_ACTION_DECREMENT);
}

uint16_t util_clamp_u64_to_u16(uint64_t value, uint16_t max_value) {
  return value > max_value ? max_value : (uint16_t)value;
}

uint64_t util_div_ceil_u64(uint64_t value, uint64_t divisor) {
  if (!divisor) {
    return 0;
  }
  return (value + divisor - 1) / divisor;
}

uint64_t util_add_u64_saturating(uint64_t a, uint64_t b) {
  if (UINT64_MAX - a < b) {
    return UINT64_MAX;
  }
  return a + b;
}

uint64_t util_mul_u64_saturating(uint64_t a, uint64_t b) {
  if (!a || !b) {
    return 0;
  }
  if (a > UINT64_MAX / b) {
    return UINT64_MAX;
  }
  return a * b;
}

bool util_read_uint64_tuple(const Tuple *tuple, uint64_t *out) {
  if (!tuple || !out || tuple->type != TUPLE_BYTE_ARRAY || tuple->length != 8) {
    return false;
  }
  const uint8_t *bytes = (const uint8_t *)tuple->value;
  uint64_t value = 0;
  for (uint8_t i = 0; i < 8; ++i) {
    value |= ((uint64_t)bytes[i]) << (8 * i);
  }
  *out = value;
  return true;
}

void util_copy_string(char *dst, size_t dst_len, const char *src) {
  if (!dst || !dst_len) {
    return;
  }
  if (!src) {
    dst[0] = '\0';
    return;
  }
  strncpy(dst, src, dst_len - 1);
  dst[dst_len - 1] = '\0';
}

void util_format_duration(uint64_t total_ms, char *buffer, size_t buffer_len) {
  uint64_t total_s = util_div_ceil_u64(total_ms, 1000);
  uint64_t hours = total_s / 3600;
  uint64_t minutes = (total_s / 60) % 60;
  uint64_t seconds = total_s % 60;
  if (hours > 0) {
    snprintf(buffer, buffer_len, "%llu:%02llu:%02llu",
             (unsigned long long)hours,
             (unsigned long long)minutes,
             (unsigned long long)seconds);
  } else {
    snprintf(buffer, buffer_len, "%02llu:%02llu",
             (unsigned long long)minutes,
             (unsigned long long)seconds);
  }
}
