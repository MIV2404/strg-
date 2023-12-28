#include "s21_string.h"

void* s21_memset(void* str, int c, s21_size_t n) {
  if (str == s21_NULL || n == 0) return str;
  unsigned char* temp = (unsigned char*)str;
  int counter = 0;
  do {
    *(temp + counter) = (unsigned char)c;
    counter++;
  } while (--n != 0);

  return str;
}