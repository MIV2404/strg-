#include "s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  if (!src || !str) return s21_NULL;

  s21_size_t str_len = s21_strlen(str);
  s21_size_t len = (s21_strlen(src) + str_len) + 1;
  char *start = s21_NULL;
  char *new_str = (char *)malloc(len);
  if (new_str) {
    s21_memset(new_str, 0, len);
    start = new_str;

    if (start_index != 0) {
      for (s21_size_t i = 0; i < start_index; ++i) {
        *new_str++ = *src++;
      }
    }

    for (s21_size_t j = 0; j < str_len; ++j) {
      *new_str++ = *str++;
    }

    for (; *src != '\0';) {
      *new_str++ = *src++;
    }

    *new_str = '\0';
  }

  return start;
}
