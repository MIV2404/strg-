#include "s21_string.h"

char* s21_strstr(const char* haystack, const char* needle) {
  if (*needle == '\0') return (void*)haystack;
  char* temp = s21_NULL;
  while (*haystack != '\0') {
    const char* current_haystack = haystack;
    const char* current_needle = needle;

    while (*current_needle != '\0' && *current_needle == *current_haystack) {
      ++current_needle;
      ++current_haystack;
    }

    if (*current_needle == '\0') {
      temp = (char*)haystack;
      break;
    }
    ++haystack;
  }
  return temp;
}
