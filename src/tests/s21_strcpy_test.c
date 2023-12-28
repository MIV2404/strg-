#include "s21_tests_main.h"

START_TEST(aboba_floppa) {
  char src[] = " floppa!!!";
  char res[5 + 15] = "aboba ";
  char expected[5 + 15] = "aboba ";

  s21_strcpy(res, src);
  strcpy(expected, src);

  ck_assert_str_eq(res, expected);
}
END_TEST

START_TEST(_floppa) {
  char src[] = "Floppa!!!";
  char res[5 + 15] = "";
  char expected[5 + 15] = "";

  s21_strcpy(res, src);
  strcpy(expected, src);

  ck_assert_str_eq(res, expected);
}
END_TEST

START_TEST(aboba_) {
  char src[] = "";
  char res[5 + 15] = "abobas";
  char expected[5 + 15] = "abobas";

  s21_strcpy(res, src);
  strcpy(expected, src);

  ck_assert_str_eq(res, expected);
}
END_TEST

START_TEST(empty) {
  char src[] = "";
  char res[5 + 15] = "";
  char expected[5 + 15] = "";

  s21_strcpy(res, src);
  strcpy(expected, src);

  ck_assert_str_eq(res, expected);
}
END_TEST

START_TEST(empty_num) {
  char src[] = "1";
  char res[5 + 15] = "";
  char expected[5 + 15] = "";

  s21_strcpy(res, src);
  strcpy(expected, src);

  ck_assert_str_eq(res, expected);
}
END_TEST

START_TEST(hello) {
  char src[] = " my dear friend\"";
  char res[5 + 15] = "Hello";
  char expected[5 + 15] = "Hello";

  s21_strcpy(res, src);
  strcpy(expected, src);

  ck_assert_str_eq(res, expected);
}
END_TEST

START_TEST(over_string) {
  char src[] = "ab\0ba";
  char res[10 + 9] = "Gre\0t";
  char expected[10 + 9] = "Gre\0t";

  s21_strcpy(res, src);
  strcpy(expected, src);

  ck_assert_str_eq(res, expected);
}
END_TEST

START_TEST(hard_test) {
  char src[] = "ad[sofijpoiajsdf pj98981h23 p9h floppa!!!";
  char res[49 + 42] = "as[oidjf paijsdf j9oqh2837o4h hUW auhduash W8awd";
  char expected[49 + 42] = "as[oidjf paijsdf j9oqh2837o4h hUW auhduash W8awd";

  s21_strcpy(res, src);
  strcpy(expected, src);

  ck_assert_str_eq(res, expected);
}
END_TEST

Suite* s21_strcpy_test(void) {
  Suite* s;
  TCase* tc_s21_strcpy;
  s = suite_create("\033[34m \033[46m STRCPY TESTS \033[0m");

  tc_s21_strcpy = tcase_create("s21_strcpy");
  tcase_add_test(tc_s21_strcpy, aboba_floppa);
  tcase_add_test(tc_s21_strcpy, _floppa);
  tcase_add_test(tc_s21_strcpy, aboba_);
  tcase_add_test(tc_s21_strcpy, empty);
  tcase_add_test(tc_s21_strcpy, empty_num);
  tcase_add_test(tc_s21_strcpy, hard_test);
  tcase_add_test(tc_s21_strcpy, hello);
  tcase_add_test(tc_s21_strcpy, over_string);

  suite_add_tcase(s, tc_s21_strcpy);
  return s;
}
