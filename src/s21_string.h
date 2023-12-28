#ifndef S21_UTILS
#define S21_UTILS

#include <ctype.h>
#include <math.h>    //sprintf
#include <stdarg.h>  //sprintf
#include <stddef.h>
#include <stdint.h>  // atoi
#include <stdlib.h>

#define s21_NULL ((void *)0)
typedef unsigned int s21_size_t;
#define BUFF_SIZE 512

void *s21_memchr(const void *str, int c, s21_size_t n);
int s21_memcmp(const void *ptr1, const void *ptr2, s21_size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
char *s21_strchr(const char *str, int c);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
s21_size_t s21_strcspn(const char *str1, const char *str2);
char *s21_strerror(int errnum);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strrchr(const char *str, int c);
char *s21_strstr(const char *haystack, const char *needle);
char *s21_strtok(char *str, const char *delim);

int s21_sprintf(char *str, const char *format, ...);

s21_size_t s21_strlen(const char *str);
int s21_atoi(const char *str);
void *s21_memmove(void *ptr1, const void *ptr2, s21_size_t n);  // sprintf
char *s21_strcpy(char *dest, const char *src);                  // sprintf
char *s21_strcat(char *dest, const char *src);

// bonus task
void *s21_to_upper(const char *);
void *s21_to_lower(const char *);
void *s21_insert(const char *, const char *, s21_size_t);
void *s21_trim(const char *, const char *);

#endif