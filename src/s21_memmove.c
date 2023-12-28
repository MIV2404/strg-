#include "s21_string.h"

void *s21_memmove(void *ptr1, const void *ptr2, s21_size_t n) {
  if (ptr1 == NULL || ptr2 == NULL || n == 0) {
    return ptr1;
  }
  char *to = (char *)ptr1;
  const char *from = (const char *)ptr2;

  if (to > from && to < from + n) {
    char *tmp = (char *)malloc(n);
    if (tmp) {
      s21_memcpy(tmp, from, n);
      s21_memcpy(to, tmp, n);
      free(tmp);
    }
  } else {
    s21_memcpy(to, from, n);
  }

  return ptr1;
}