#include "s21_tests_main.h"

START_TEST(Hello_aboba) {
  char src[] = " aboba!!!";
  char res[5 + 10] = "Hello";
  char expected[5 + 10] = "Hello";

  s21_strcat(res, src);
  strcat(expected, src);

  ck_assert_str_eq(res, expected);
}
END_TEST

START_TEST(zero_first) {
  char src[] = " aboba!!!";
  char res[0 + 10] = "";
  char expected[0 + 10] = "";

  s21_strcat(res, src);
  strcat(expected, src);

  ck_assert_str_eq(res, expected);
}
END_TEST

START_TEST(zero_last) {
  char src[] = "";
  char res[] = "Hello";
  char expected[] = "Hello";

  s21_strcat(res, src);
  strcat(expected, src);

  ck_assert_str_eq(res, expected);
}
END_TEST

START_TEST(any_letters_with_register) {
  char src[] = "asdfj  asdf aisdfjaiushdfASD SAD asDSad ASDAsdwqqeAS";
  char res[5 + 53] = "Hello";
  char expected[5 + 53] = "Hello";

  s21_strcat(res, src);
  strcat(expected, src);

  ck_assert_str_eq(res, expected);
}
END_TEST

START_TEST(any_letters_with_register_and_num) {
  char src[] = "asd0fj  asd1f aisdfjw6234A1241SD SA5 asDSad 89SDAsdw7qqeAS";
  char res[5 + 59] = "Hello";
  char expected[5 + 59] = "Hello";

  s21_strcat(res, src);
  strcat(expected, src);

  ck_assert_str_eq(res, expected);
}
END_TEST

START_TEST(any_letters_with_register_and_num_and_sim) {
  char src[] =
      "asd0fj  asd1f aisdfjw6234A1241SD SA5 asDSad 89SDAsdw7qqeAS)(?!.,";
  char res[5 + 65] = "Hello";
  char expected[5 + 65] = "Hello";

  s21_strcat(res, src);
  strcat(expected, src);

  ck_assert_str_eq(res, expected);
}
END_TEST

Suite* s21_strcat_test(void) {
  Suite* s;
  TCase* tc_s21_strcat;
  s = suite_create("\033[34m \033[46m STRCAT \033[0m");

  tc_s21_strcat = tcase_create("s21_strcat");
  tcase_add_test(tc_s21_strcat, Hello_aboba);
  tcase_add_test(tc_s21_strcat, zero_first);
  tcase_add_test(tc_s21_strcat, zero_last);
  tcase_add_test(tc_s21_strcat, any_letters_with_register);
  tcase_add_test(tc_s21_strcat, any_letters_with_register_and_num);
  tcase_add_test(tc_s21_strcat, any_letters_with_register_and_num_and_sim);
  suite_add_tcase(s, tc_s21_strcat);
  return s;
}
