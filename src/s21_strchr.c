#include "s21_string.h"

char* s21_strchr(const char* str, int c) {
  char* temp = s21_NULL;

  do {
    if (*str == c) {
      temp = (char*)str;
      break;
    }
  } while (*str++ != '\0');

  return temp;
}
