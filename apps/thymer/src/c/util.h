#pragma once

#include "thymer.h"

uint64_t util_now_ms(void);
int32_t util_clamp_i32(int32_t value, int32_t min_value, int32_t max_value);
UpAction util_clamp_up_action(int32_t value);
uint16_t util_clamp_u64_to_u16(uint64_t value, uint16_t max_value);
uint64_t util_div_ceil_u64(uint64_t value, uint64_t divisor);
uint64_t util_add_u64_saturating(uint64_t a, uint64_t b);
uint64_t util_mul_u64_saturating(uint64_t a, uint64_t b);
bool util_read_uint64_tuple(const Tuple *tuple, uint64_t *out);
void util_copy_string(char *dst, size_t dst_len, const char *src);
void util_format_duration(uint64_t total_ms, char *buffer, size_t buffer_len);
