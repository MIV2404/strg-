#include "s21_string.h"

int s21_strncmp(const char* str1, const char* str2, s21_size_t n) {
  if (n == 0) {
    return 0;
  }

  unsigned char *s1 = (unsigned char*)str1, *s2 = (unsigned char*)str2;
  int result = 0;

  do {
    if (*s1 != *s2) {
      result = *s1 - *s2;
      break;
    }

    ++s1;
    ++s2;
  } while (--n != 0);

  return result;
}