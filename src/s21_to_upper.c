#include "s21_string.h"

void *s21_to_upper(const char *str) {
  if (!str) return s21_NULL;

  s21_size_t len = s21_strlen(str) + 1;
  char *start = s21_NULL;
  char *new_str = (char *)malloc(len);

  if (new_str) {
    start = new_str;

    do {
      if (*str >= 'A' && *str <= 'Z') {
        *new_str++ = *str;
        continue;
      }

      *new_str = *str - 32;

      if (*new_str < 'A' || *new_str > 'Z') *new_str = *str;

      new_str++;
    } while (*++str != '\0');

    *new_str = '\0';
  }

  return start;
}