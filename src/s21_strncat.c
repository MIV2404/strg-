#include "s21_string.h"

char* s21_strncat(char* dest, const char* src, s21_size_t n) {
  if (n == 0) return dest;
  char* source = (char*)src;
  char* destination = s21_strchr(dest, '\0');
  do {
    *destination++ = *source++;
  } while (--n != 0);

  *destination = '\0';

  return dest;
}
