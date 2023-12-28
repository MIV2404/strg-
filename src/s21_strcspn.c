#include "s21_string.h"

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  if (!str2) return (0);

  unsigned char *tmp_str1 = s21_NULL, *tmp_str2 = (unsigned char *)str2;
  int counter = 0;
  int flag = 1;
  do {
    for (counter = 0, tmp_str1 = (unsigned char *)str1; *tmp_str1 != '\0';
         tmp_str1++) {
      if (*tmp_str1 == *tmp_str2) {
        flag = 0;
        break;
      }
      counter++;
    }
  } while (*tmp_str2++ != '\0' && flag);

  return counter;
}