#include "s21_string.h"

int s21_atoi(const char* str) {
  int res = 0;
  int positive = 1;
  int over = 0;

  while (*str == ' ') str++;

  switch (*str) {
    case '-':
      positive = -1;
      str++;
      break;
    case '+':
      str++;
  }

  while (*str && '0' <= *str && *str <= '9') {
    res = res * 10 + (*str - '0');

    if (res < 0) {
      over = 1;
      break;
    }
    str++;
  }

  if (over)
    res = -1;
  else
    res *= positive;

  return res;
}
