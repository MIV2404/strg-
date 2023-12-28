#include "s21_tests_main.h"

START_TEST(test_memmove_basic) {
  char src[] = "Hello";
  char dest1[10] = "";
  char dest2[10] = "";

  memmove(dest1, src, 5);
  s21_memmove(dest2, src, 5);

  ck_assert_mem_eq(dest1, dest2, 5);
}
END_TEST

START_TEST(test_memmove_empty) {
  char src[] = "";
  char dest1[10] = "12345";
  char dest2[10] = "12345";

  memmove(dest1, src, 0);
  s21_memmove(dest2, src, 0);

  ck_assert_mem_eq(dest1, dest2, 5);
}
END_TEST

START_TEST(test_memmove_large) {
  char src[10000];
  char dest1[10000];
  char dest2[10000];

  for (int i = 0; i < 10000; ++i) {
    src[i] = (char)(i % 256);
    dest1[i] = 0;
    dest2[i] = 0;
  }

  memmove(dest1, src, 10000);
  s21_memmove(dest2, src, 10000);

  ck_assert_mem_eq(dest1, dest2, 10000);
}
END_TEST

START_TEST(test_memmove_overlap) {
  char src[] = "Hello";
  char dest1[10] = "12345";
  char dest2[10] = "12345";

  memmove(dest1 + 2, src, 3);
  s21_memmove(dest2 + 2, src, 3);

  ck_assert_mem_eq(dest1, dest2, 5);
}
END_TEST

START_TEST(test_memmove_return_value) {
  char src[] = "Hello";
  char dest1[10] = "";
  char dest2[10] = "";

  char *result1 = memmove(dest1, src, 5);
  char *result2 = s21_memmove(dest2, src, 5);

  ck_assert_ptr_eq(result1, dest1);
  ck_assert_ptr_eq(result2, dest2);
}
END_TEST

Suite *s21_memmove_test(void) {
  Suite *s;
  TCase *tc_s21_memmove;
  s = suite_create("\033[34m \033[46m MEMMOVE TESTS \033[0m");

  tc_s21_memmove = tcase_create("s21_memmove");
  tcase_add_test(tc_s21_memmove, test_memmove_basic);
  tcase_add_test(tc_s21_memmove, test_memmove_empty);
  tcase_add_test(tc_s21_memmove, test_memmove_large);
  tcase_add_test(tc_s21_memmove, test_memmove_overlap);
  tcase_add_test(tc_s21_memmove, test_memmove_return_value);
  suite_add_tcase(s, tc_s21_memmove);
  return s;
}
