#include "s21_string.h"

void* s21_memchr(const void* str, int c, s21_size_t n) {
  if (!str) return s21_NULL;

  s21_size_t i = 0;
  for (; i < n; i++) {
    if (*((unsigned char*)str + i) == c) break;
  }
  return (*((unsigned char*)str + i) == c) ? (unsigned char*)str + i : s21_NULL;
}
