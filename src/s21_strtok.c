#include "s21_string.h"

char *s21_strtok(char *str, const char *delim) {
  static char *nextToken;
  char *tokenStart = s21_NULL;
  int result = 1;

  if (str) {
    nextToken = str;
  }

  while (*nextToken != '\0' && s21_strchr(delim, *nextToken) != s21_NULL) {
    ++nextToken;
  }

  if (*nextToken == '\0') {
    nextToken = s21_NULL;
    result = 0;
  }

  tokenStart = nextToken;
  while (result && *nextToken != '\0' &&
         s21_strchr(delim, *nextToken) == s21_NULL) {
    ++nextToken;
  }

  if (result && *nextToken != '\0') {
    *nextToken = '\0';
    ++nextToken;
  }

  return tokenStart;
}