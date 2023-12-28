#include "s21_string.h"

char* s21_strncpy(char* dest, const char* src, s21_size_t n) {
  if (n == 0) return (dest);
  unsigned char *dest_tmp = (unsigned char*)dest,
                *src_tmp = (unsigned char*)src;
  do {
    if (*src_tmp != '\0') {
      *dest_tmp++ = *src_tmp++;
    } else {
      *dest_tmp++ = '\0';
    }
  } while (--n);

  return dest;
}