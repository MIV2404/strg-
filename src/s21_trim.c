#include "s21_string.h"

void* s21_trim(const char* src, const char* trim_chars) {
  if (!src || !trim_chars) return s21_NULL;

  s21_size_t len = s21_strlen(src) + 1;

  char* new_src = (char*)malloc(len);
  char* start = s21_NULL;
  if (new_src) {
    s21_memset(new_src, 0, len);

    char* trim_cp = (char*)trim_chars;
    start = new_src;

    for (; *trim_cp == *src; ++src)
      if (*(trim_cp + 1) != '\0') trim_cp++;

    while (*src != '\0') *new_src++ = *src++;

    new_src--;

    for (; *trim_cp == *new_src; --new_src) {
      if (*trim_cp == *trim_chars) continue;
      --trim_cp;
    }

    *++new_src = '\0';
  }
  return start;
}