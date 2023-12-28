#include "s21_string.h"

char* s21_strpbrk(const char* str1, const char* str2) {
  char* tmp1 = (char*)str1;
  char* result = s21_NULL;
  int flag = 1;
  do {
    for (char* tmp2 = (char*)str2; *tmp2 != 0; ++tmp2) {
      if (*tmp2 == *tmp1) {
        result = tmp1;
        flag = 0;
        break;
      }
    }
  } while (*tmp1++ != 0 && flag);

  return result;
}