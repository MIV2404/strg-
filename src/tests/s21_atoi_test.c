#include "s21_tests_main.h"

START_TEST(s21_atoi_test1) {
  char src[] = "0";
  ck_assert_int_eq(atoi(src), s21_atoi(src));
}
END_TEST

START_TEST(s21_atoi_test2) {
  char src[] = "123123123";
  ck_assert_int_eq(atoi(src), s21_atoi(src));
}
END_TEST

START_TEST(s21_atoi_test3) {
  char src[] = "    123123123";
  ck_assert_int_eq(atoi(src), s21_atoi(src));
}
END_TEST

START_TEST(s21_atoi_test4) {
  char src[] = "-123123123";
  ck_assert_int_eq(atoi(src), s21_atoi(src));
}
END_TEST

START_TEST(s21_atoi_test5) {
  char src[] = "+123123123";
  ck_assert_int_eq(atoi(src), s21_atoi(src));
}
END_TEST

START_TEST(s21_atoi_test6) {
  char src[] = "++123123123";
  ck_assert_int_eq(atoi(src), s21_atoi(src));
}
END_TEST

START_TEST(s21_atoi_test7) {
  char src[] = " 123123123123123123123123123123123";
  ck_assert_ldouble_eq(atoi(src), s21_atoi(src));
}
END_TEST

Suite* s21_atoi_test(void) {
  Suite* s;
  TCase* tc_s21_atoi;
  s = suite_create("\033[34m \033[46m ATOI TESTS \033[0m");

  tc_s21_atoi = tcase_create("s21_atoi");
  tcase_add_test(tc_s21_atoi, s21_atoi_test1);
  tcase_add_test(tc_s21_atoi, s21_atoi_test2);
  tcase_add_test(tc_s21_atoi, s21_atoi_test3);
  tcase_add_test(tc_s21_atoi, s21_atoi_test4);
  tcase_add_test(tc_s21_atoi, s21_atoi_test5);
  tcase_add_test(tc_s21_atoi, s21_atoi_test6);
  tcase_add_test(tc_s21_atoi, s21_atoi_test7);
  suite_add_tcase(s, tc_s21_atoi);
  return s;
}
