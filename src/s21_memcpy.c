#include "s21_string.h"
void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  unsigned char *dest_cp = dest;
  const unsigned char *src_cp = src;

  if (dest_cp < src_cp || dest_cp >= src_cp + n) {
    while (n--) {
      *dest_cp++ = *src_cp++;
    }
  }

  return dest;
}