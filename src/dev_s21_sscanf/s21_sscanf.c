#include "../s21_string.h"

typedef struct {
  int width;
  char length;
  char specifier;
} flgs;

int s21_sscanf(const char *str, const char *format, ...);
const char *getwidth(const char *format, flgs *f, va_list lst);
const char *getlength(const char *format, flgs *f);
void handle_val(flgs *f, char *buf, va_list lst, const char **str, int *n_args);
void parse_int(flgs *f, const char *buf, va_list lst, const char **str);
void parse_char(flgs *f, char *buf, va_list lst, const char **str);
void parse_float(flgs *f, char *buf, va_list lst, const char **str);
double string_to_ld(const char *string);
double long_s21_atoi(const char *str);
void process_exponent(char *shift_num_buf, char *number, int *pow_int);

int main() {
  char *line = "%F 109 5.2081e+1 8";
  char name = 'P';
  int age;
  double salary;
  int test, ret;

  ret = s21_sscanf(line, "%%%c %d %lf %d", &name, &age, &salary, &test);
  // printf("Age: %d\n", age);
  // printf("Name: %c \tAge: %d \tSalary: %lf \tTest: %d\n", name, age, salary,
  //        test);
  // printf("Returnable value: %d\n", ret);
  // ________________TEST____________________________________________________/
  // printf(
  //     "ORIGINAL:_______________________________________________________________"
  //     "__\n");
  // sscanf(line, "%%%c %d %lf %d", &name, &age, &salary, &test);
  // printf("Name: %c \tAge: %d \tSalary: %f \tTest: %d\n", name, age, salary,
  //        test);
  // printf(
  //     "END_ORIGINAL____________________________________________________________"
  //     "__\n");

  // printf("%f\n", salary);
  // ________________________________________________________________________/

  return 0;
}

int s21_sscanf(const char *str, const char *format, ...) {
  flgs f = {0};
  va_list lst;
  va_start(lst, format);
  // const char *str_start = str;
  int n_args = 0;

  while (*format) {
    if (*format == '%') {
      format++;
      s21_memset(&f, 0, sizeof(flgs));
      // printf("Строка: %s\n", str);
      // str++;
    }

    format = getwidth(format, &f, lst);
    format = getlength(format, &f);

    f.specifier = *format;

    char buf[BUFF_SIZE] = {'\0'};
    handle_val(&f, buf, lst, &str, &n_args);

    // if (f.specifier == 'n') {
    //   int *ret = va_arg(lst, int *);
    //   *ret = str - str_start;
    // }

    if (f.specifier != ' ') {
      // printf("Specifier: %c\nWidth: %d\nLength: %c\n\n", f.specifier,
      // f.width,
      //        f.length);
    }

    format++;
  }

  va_end(lst);

  return n_args;
}

const char *getwidth(const char *format, flgs *f, va_list lst) {
  if (*format == '*') {
    format++;
    f->width = va_arg(lst, int);
  } else if (isdigit(*format)) {
    char tmp[BUFF_SIZE] = {'\0'};
    for (int i = 0; isdigit(*format); i++, format++) {
      tmp[i] = *format;
    }
    f->width = s21_atoi(tmp);
  }
  return format;
}

const char *getlength(const char *format, flgs *f) {
  switch (*format) {
    case 'h':
      f->length = 'h';
      format++;
      break;
    case 'l':
      f->length = 'l';
      format++;
      break;
    case 'L':
      f->length = 'L';
      format++;
      break;
  }
  return format;
}

void handle_val(flgs *f, char *buf, va_list lst, const char **str,
                int *n_args) {
  if (*buf || lst) {
    ;
  }

  if (f->specifier == 'd' || f->specifier == 'i') {
    // printf("Case: d or i ");
    parse_int(f, buf, lst, str);
    // printf("Символ: %c\n", **str);
    ++*str;
    ++*n_args;
  } else if (f->specifier == 'u') {
    // printf("Case: u ");
    // parse_unsign(f, buf, lst);
    ++*n_args;
  } else if (f->specifier == 'o') {
    // printf("Case: o ");
    // parse_octal(f, buf, lst);
    ++*n_args;
  } else if (f->specifier == 'x' || f->specifier == 'X') {
    // printf("Case: x or X ");
    // parse_hex(f, buf, lst);
    ++*n_args;
  } else if (f->specifier == '%') {
    ++*str;

    // buf[0] = '%';
  } else if (f->specifier == 'c') {
    // printf("Case: c ");
    parse_char(f, buf, lst, str);
    ++*str;
    ++*str;
    ++*n_args;
  } else if (f->specifier == 's') {
    // printf("Case: s ");
    // parse_strg(f, buf, lst);
    ++*n_args;
  } else if (f->specifier == 'p') {
    // printf("Case: p ");
    // parse_pointer(f, buf, lst);
    ++*n_args;
  } else if (f->specifier == 'e' || f->specifier == 'E' ||
             f->specifier == 'f' || f->specifier == 'g' ||
             f->specifier == 'G') {
    // printf("Case: f ");
    parse_float(f, buf, lst, str);
    // while (**str != ' ') {
    //   ++*str;
    // }
    ++*str;
    ++*n_args;
  }
  if (f->specifier == 'X' || f->specifier == 'G' || f->specifier == 'E') {
    // printf("Case: X, G or E ");
    // to_upper(buf);
    ++*n_args;
  }
}

void parse_int(flgs *f, const char *buf, va_list lst, const char **str) {
  // int32_t не может содержать больше 10 знаков
  char number[10];
  int i;
  int res_num;

  if (f->length || *buf) {
    ;
  }

  int32_t *val;

  val = va_arg(lst, int32_t *);

  for (i = 0; i < 10 && isdigit(**str); i++) {
    number[i] = **str;
    ++*str;
  }
  while (isdigit(**str)) {
    ++*str;
  }

  number[i] = '\0';

  res_num = s21_atoi(number);

  // printf("\nЧисло: |%lld|\n", res_num);
  *val = res_num;

  // switch (f.length) {
  // case 0:
  //   val = (int32_t)val;
  //   break;-
  // case 'h':
  //   val = (int16_t)val;
  // }
  // whole_num_to_strg(val, buf, 10);
  // format_precision(buf, f);
  // format_flgs(buf, f);
}

void parse_char(flgs *f, char *buf, va_list lst, const char **str) {
  if (*buf) {
    ;
  }

  if (f->length == 'l') {
    wchar_t *w_c;
    w_c = va_arg(lst, wchar_t *);
    *w_c = **str;
    // format_wchar(f, buf, w_c);
  } else {
    int32_t *c;
    c = va_arg(lst, int32_t *);
    // format_char(f, buf, c);
    *c = **str;
  }
}

void parse_float(flgs *f, char *buf, va_list lst, const char **str) {
  char num_buf[46];
  char number[46];
  s21_memset(number, 0, 46);
  int i, number_len, pow_int = 0;
  number_len = 0;
  int exponent = 0;
  char sign = '0';
  char shift_num_buf[46];

  // Нужно добавить обработку мантиссы/экспоненты

  if (*buf) {
    ;
  }

  for (i = 0; i < 46 && (isdigit(**str) || **str == '.' || **str == 'e' ||
                         **str == '+' || **str == '-');
       i++, ++*str, number_len++) {
    // printf("ЧИСЛО: : %c\n", **str);
    if (**str == 'e') {
      exponent = 1;
      // printf("Экспааааааааааааа!\n");
      num_buf[i] = '\0';
      s21_strcpy(number, num_buf);
      number[number_len] = '\0';
      s21_memset(num_buf, 0, 46);
      i = -2;
      sign = '?';
    } else if (**str == '+') {
      sign = '+';
    } else if (**str == '-') {
      sign = '-';
    } else {
      if (sign == '?') {
        sign = '+';
        --*str;
      }
      num_buf[i] = **str;
    }
  }
  num_buf[i] = '\0';
  // printf("Длина числа: %d\n", number_len);

  if (exponent == 1) {
    char pow[46];
    s21_strcpy(pow, num_buf);
    pow_int = s21_atoi(pow);
    if (sign == '-') {
      pow_int *= -1;
    }
    // printf("Exponent: %d\tSign:%c\tNumber part: %s\tPow: %d\n", exponent,
    // sign,
    //        number, pow_int);
  }

  process_exponent(shift_num_buf, number, &pow_int);

  while (isdigit(**str) || **str == '.') {
    ++*str;
  }
  // num_buf[i] = '\0';

  double mantissa_buf = string_to_ld(shift_num_buf);

  if (f->length == 'L') {
    long double *val = 0;
    val = va_arg(lst, long double *);
    *val = mantissa_buf;
  } else {
    double *val = 0;
    val = va_arg(lst, double *);
    *val = mantissa_buf;
  }

  // if (!f.is_precision_set) {
  //   f.precision = 6;
  // }

  // double_strg(val, buf, f);
  // format_flgs(buf, f);
}

void process_exponent(char *shift_num_buf, char *number, int *pow_int) {
  int k = 0;
  int dot = 0;

  for (int l = 0; number[l] != '\0'; l++, k++) {
    if (isdigit(number[l])) {
      shift_num_buf[k] = number[l];
      if (dot == 1) {
        --*pow_int;
      }
    } else if (number[l] == '.') {
      k--;
      dot = 1;
    }
  }
  // printf("kkkkkk: %d\n", k);

  // printf("|Итоговое число: %s|\n", shift_num_buf);
  // printf("Изменённый pow: |%d|\n", *pow_int);

  while (*pow_int > 0) {
    shift_num_buf[k] = '0';
    k++;
    --*pow_int;
    // printf("Нуль: %d\n", shift_num_buf[k]);
  }

  // Работа с передвижением запятой назад
  if (*pow_int < 0) {
    *pow_int *= -1;
    int fract_part_len = *pow_int + 1;
    char num_fract_part[fract_part_len];
    num_fract_part[*pow_int] = '\0';
    while (*pow_int >= 0) {
      --*pow_int;
      k--;
      num_fract_part[*pow_int] = shift_num_buf[k];
    }
    // printf("Дробная часть: %s\n", num_fract_part);
    k++;
    shift_num_buf[k] = '.';
    k++;
    // fract_part_len--;
    for (int l = 0; l < fract_part_len; l++, k++) {
      shift_num_buf[k] = num_fract_part[l];
    }
  } else {
    shift_num_buf[k] = '.';
    shift_num_buf[k + 1] = '0';
    shift_num_buf[k + 2] = '\0';
  }

  // printf("|Обычное число: %s|\n", shift_num_buf);
}

double string_to_ld(const char *string) {
  char str_int_num[46];
  int i;
  double int_num;

  for (i = 0; string[i] != '.'; i++) {
    str_int_num[i] = string[i];
  }
  str_int_num[i] = '\0';
  // printf("{%s}", str_int_num);
  int_num = long_s21_atoi(str_int_num);
  // printf("{%f}", int_num);

  i++;
  double k = 10;
  char char_buf_string[2];
  while (string[i] != '\0') {
    // printf("K: %f\n", k);
    // printf("int_num: %f\n", int_num);
    char_buf_string[0] = string[i];
    char_buf_string[1] = '\0';
    // printf("string: %f\n", long_s21_atoi(char_buf_string));
    double num_buf;
    num_buf = s21_atoi(char_buf_string) / k;

    // printf("Plus: %f\n", (long_s21_atoi(char_buf_string) / k));
    int_num += num_buf;
    k = k * 10;
    i++;
  }

  return int_num;
}

double long_s21_atoi(const char *str) {
  double res = 0;
  double positive = 1;
  double over = 0;

  while (*str == ' ') {
    str++;
  }

  switch (*str) {
    case '-':
      positive = -1;
      str++;
      break;
    case '+':
      str++;
  }

  while (*str && '0' <= *str && *str <= '9') {
    res = res * 10 + (*str - '0');
    if (res < 0) {
      over = 1;
      break;
    }
    str++;
  }

  if (over) {
    res = -1;
  } else {
    res *= positive;
  }

  return res;
}
