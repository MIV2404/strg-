#include "s21_string.h"

char* s21_strrchr(const char* str, int c) {
  char* tmp = (char*)str;
  char* result = s21_NULL;
  do {
    if (*tmp == c) {
      result = tmp;
    }
  } while (*tmp++ != 0);

  return result;
}
