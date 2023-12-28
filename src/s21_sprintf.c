#include "s21_sprintf.h"

int s21_sprintf(char* str, const char* format, ...) {
  flgs f = {0};
  va_list lst;
  va_start(lst, format);
  char* str_start = str;

  while (*format) {
    if (*format == '%') {
      format++;
      s21_memset(&f, 0, sizeof(flgs));
    } else {
      *str++ = *format++;
      continue;
    }
    format = getflags(format, &f);
    format = getwidth(format, &f, lst);
    format = getprecision(format, &f, lst);
    format = getlength(format, &f);

    f.specifier = *format;
    format++;

    char buf[BUFF_SIZE] = {'\0'};
    handle_val(f, buf, lst);
    for (int i = 0; buf[i]; i++, str++) *str = buf[i];

    if (f.specifier == 'n') {
      int* ret = va_arg(lst, int*);
      *ret = str - str_start;
    }
  }
  *str = '\0';
  va_end(lst);

  return str - str_start;
}

const char* getflags(const char* format, flgs* f) {
  while (*format == '-' || *format == '+' || *format == ' ' || *format == '#' ||
         *format == '0') {
    switch (*format) {
      case '-':
        f->minus = 1;
        break;
      case '+':
        f->plus = 1;
        break;
      case ' ':
        f->space = 1;
        break;
      case '#':
        f->hash = 1;
        break;
      case '0':
        f->zero = 1;
        break;
    }
    format++;
  }
  return format;
}

const char* getwidth(const char* format, flgs* f, va_list lst) {
  if (*format == '*') {
    format++;
    f->width = va_arg(lst, int);
  } else if (s21_isdigit(*format)) {
    char tmp[BUFF_SIZE] = {'\0'};
    for (int i = 0; s21_isdigit(*format); i++, format++) {
      tmp[i] = *format;
    }
    f->width = s21_atoi(tmp);
  }
  return format;
}

const char* getprecision(const char* format, flgs* f, va_list lst) {
  if (*format == '.') {
    f->is_precision_set = 1;
    format++;
  }
  if (*format == '*') {
    format++;
    f->precision = va_arg(lst, int);
  }
  if (s21_isdigit(*format)) {
    char tmp[BUFF_SIZE] = {'\0'};
    for (int i = 0; s21_isdigit(*format); i++, format++) tmp[i] = *format;
    f->precision = s21_atoi(tmp);
  }
  return format;
}

const char* getlength(const char* format, flgs* f) {
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

void handle_val(flgs f, char* buf, va_list lst) {
  if (f.specifier == 'd' || f.specifier == 'i')
    parse_int(f, buf, lst);
  else if (f.specifier == 'u')
    parse_unsign(f, buf, lst);
  else if (f.specifier == 'o')
    parse_octal(f, buf, lst);
  else if (f.specifier == 'x' || f.specifier == 'X')
    parse_hex(f, buf, lst);
  else if (f.specifier == '%')
    buf[0] = '%';
  else if (f.specifier == 'c')
    parse_char(f, buf, lst);
  else if (f.specifier == 's')
    parse_strg(f, buf, lst);
  else if (f.specifier == 'p')
    parse_pointer(f, buf, lst);
  else if (f.specifier == 'f')
    parse_float(f, buf, lst);
  else if (f.specifier == 'e' || f.specifier == 'E')
    parse_mantiss(f, buf, lst);
  else if (f.specifier == 'g' || f.specifier == 'G')
    parse_float_Gg(f, buf, lst);
  if (f.specifier == 'X' || f.specifier == 'G' || f.specifier == 'E')
    to_upper(buf);
}

void parse_int(flgs f, char* buf, va_list lst) {
  int64_t val = va_arg(lst, int64_t);

  switch (f.length) {
    case 0:
      val = (int32_t)val;
      break;
    case 'h':
      val = (int16_t)val;
  }
  whole_num_to_strg(val, buf, 10);
  format_precision(buf, f);
  format_flgs(buf, f);
}

void whole_num_to_strg(int64_t val, char* ret, int base) {
  char tmp[BUFF_SIZE] = {'\0'};
  int ind = BUFF_SIZE - 2;

  int neg = val < 0 ? 1 : 0;
  val = neg ? -val : val;

  if (val == 0) tmp[ind] = '0';

  while (val > 0) {
    ind--;  // TOTRY: (val % base) + '0'
    tmp[ind] = "0123456789abcdef"[val % base];
    val /= base;
  }
  for (int j = 0; tmp[ind]; ind++, j++) {
    if (neg && j == 0) ret[j++] = '-';

    ret[j] = tmp[ind];
  }
}

void format_precision(char* buf, flgs f) {
  char tmp[BUFF_SIZE] = {'\0'};

  int sign = 0;
  int len = s21_strlen(buf);

  if (buf[0] == '-') {
    tmp[0] = '-';
    len--;
    sign = 1;
  }

  if (f.precision > len) {
    int ind;
    for (ind = sign; ind < f.precision - len + sign; ind++) tmp[ind] = '0';

    for (int i = sign; buf[i]; i++, ind++) tmp[ind] = buf[i];

    s21_strcpy(buf, tmp);
  }

  if (f.is_precision_set && f.precision == 0 &&
      check_int_specifier(f.specifier) && buf[0] == '0')
    buf[0] = '\0';
}

int check_int_specifier(char c) {
  char specs[] = {'d', 'i', 'o', 'u', 'x', 'X'};
  int res = 0;
  for (s21_size_t i = 0; i < sizeof(specs); i++) {
    if (specs[i] == c) {
      res = 1;
      break;
    }
  }
  return res;
}

void format_flgs(char* buf, flgs f) {
  char tmp[BUFF_SIZE + 1] = {'\0'};
  if (f.plus && f.specifier != 'u') {
    tmp[0] = buf[0] == '-' ? buf[0] : '+';
    s21_strcpy(tmp + 1, buf[0] == '-' ? buf + 1 : buf);
    s21_strcpy(buf, tmp);
  }

  else if (f.space && buf[0] != '-' && f.specifier != 'u') {
    tmp[0] = ' ';
    s21_strcpy(tmp + 1, buf);
    s21_strcpy(buf, tmp);
  }

  if (f.width > (int)s21_strlen(buf)) {
    int ind = f.width - s21_strlen(buf);
    if (!f.minus) {
      s21_memset(tmp, f.zero ? '0' : ' ', ind);
      s21_strcpy(tmp + ind, buf);
    } else {
      s21_strcpy(tmp, buf);
      s21_memset(tmp + s21_strlen(tmp), ' ', ind);
    }
    s21_strcpy(buf, tmp);
  }
}

void unsigned_num_to_string(uint64_t val, char* ret, int base) {
  char buf[BUFF_SIZE + 1] = {'\0'};
  int ind = BUFF_SIZE - 1;
  if (val == 0) {
    buf[ind] = '0';
    ind--;
  }

  for (; val && ind; --ind, val /= base)
    buf[ind] = "0123456789abcdef"[val % base];

  for (int j = 0; buf[ind + 1]; ind++, j++) ret[j] = buf[ind + 1];
}

void parse_unsign(flgs f, char* buf, va_list lst) {
  uint64_t val = va_arg(lst, uint64_t);
  switch (f.length) {
    case 'h':
      val = (uint16_t)val;
      break;
    case 'l':
      val = (uint64_t)val;
      break;
    case 0:
      val = (uint32_t)val;
      break;
  }
  unsigned_num_to_string(val, buf, 10);
  format_precision(buf, f);
  format_flgs(buf, f);
}

void parse_octal(flgs f, char* buf, va_list lst) {
  buf[0] = '0';
  whole_num_to_strg(va_arg(lst, int64_t), buf + f.hash, 8);
  format_precision(buf, f);
  format_flgs(buf, f);
}

void to_upper(char* str) {
  while (*str) {
    if (*str >= 'a' && *str <= 'z') *str = *str - 'a' + 'A';
    str++;
  }
}

int is_all_zeroes(char* buf) {
  int k = 1;
  for (int i = 0; buf[i]; i++)
    if (buf[i] != '0') {
      k = 0;
      break;
    }
  return k;
}

void parse_hex(flgs f, char* buf, va_list lst) {
  uint64_t val = va_arg(lst, uint64_t);
  switch (f.length) {
    case 0:
      val = (uint32_t)val;
      break;
    case 'h':
      val = (uint16_t)val;
      break;
    case 'l':
      val = (uint64_t)val;
      break;
  }
  unsigned_num_to_string(val, buf, 16);
  format_precision(buf, f);
  if (f.hash) {
    prepend_ox(buf, f);
  }
  format_flgs(buf, f);
}

void prepend_ox(char* buf, flgs f) {
  if (!is_all_zeroes(buf) || f.specifier == 'p') {
    s21_memmove(buf + 2, buf, s21_strlen(buf));
    buf[0] = '0';
    buf[1] = 'x';
  }
}

void parse_char(flgs f, char* buf, va_list lst) {
  if (f.length == 'l') {
    wchar_t w_c;
    w_c = va_arg(lst, wchar_t);
    format_wchar(f, buf, w_c);
  } else {
    char c;
    c = va_arg(lst, int);
    format_char(f, buf, c);
  }
}

void format_wchar(flgs f, char* buf, wchar_t w_c) {
  if (!f.minus && f.width) {
    char tmp[BUFF_SIZE] = {'\0'};

    wcstombs(tmp, &w_c, BUFF_SIZE);
    for (s21_size_t i = 0; i < f.width - s21_strlen(tmp); i++) buf[i] = ' ';
    s21_strcat(buf, tmp);
  } else if (f.width) {
    wcstombs(buf, &w_c, BUFF_SIZE);
    for (int i = s21_strlen(buf); i < f.width; i++) buf[i] = ' ';
  } else {
    wcstombs(buf, &w_c, BUFF_SIZE);
  }
}

void format_char(flgs f, char* buf, char c) {
  if (!f.minus && f.width) {
    for (int i = 0; i < f.width; i++) {
      buf[i] = ' ';
      if (i == f.width - 1) buf[i] = c;
    }
  } else if (f.width) {
    buf[0] = c;
    for (int i = 1; i < f.width; i++) buf[i] = ' ';
  } else {
    buf[0] = c;
  }
}

void parse_strg(flgs f, char* buf, va_list lst) {
  if (f.length == 'l') {
    wchar_t* wstr = va_arg(lst, wchar_t*);
    format_wide_strg(f, buf, wstr);
  } else {
    char* str = va_arg(lst, char*);
    format_strg(f, buf, str);
  }
}

void format_strg(flgs f, char* buf, char* str) {
  char tmp[BUFF_SIZE] = {'\0'};
  s21_strcpy(tmp, str);
  if (f.is_precision_set) tmp[f.precision] = '\0';

  int shift = f.width - s21_strlen(tmp);
  int len = s21_strlen(tmp);

  if (f.minus && shift > 0) {
    s21_strcpy(buf, tmp);
    s21_memset(buf + len, ' ', shift);
  } else if (shift > 0) {
    s21_memset(buf, ' ', shift);
    s21_strcpy(buf + shift, tmp);
  } else {
    s21_strcpy(buf, tmp);
  }
}

void format_wide_strg(flgs f, char* buf, wchar_t* wstr) {
  char tmp[BUFF_SIZE] = {'\0'};
  char str[BUFF_SIZE] = {'\0'};

  wcstombs(str, wstr, BUFF_SIZE);
  s21_strcpy(tmp, str);
  if (f.is_precision_set) tmp[f.precision] = '\0';

  int shift = f.width - s21_strlen(tmp);
  int len = s21_strlen(tmp);

  if (f.minus && shift > 0) {
    s21_strcpy(buf, tmp);
    s21_memset(buf + len, ' ', shift);
  } else if (shift > 0) {
    s21_memset(buf, ' ', shift);
    s21_strcpy(buf + shift, tmp);
  } else {
    s21_strcpy(buf, tmp);
  }
}

void parse_pointer(flgs f, char* buf, va_list lst) {
  unsigned_num_to_string(va_arg(lst, uint64_t), buf, 16);
  format_precision(buf, f);
  prepend_ox(buf, f);
  format_flgs(buf, f);
}

void parse_float(flgs f, char* buf, va_list lst) {
  long double val = 0;
  if (f.length == 'L') {
    val = va_arg(lst, long double);
  } else {
    val = va_arg(lst, double);
  }

  if (!f.is_precision_set) {
    f.precision = 6;
  }

  double_strg(val, buf, f);
  format_flgs(buf, f);
}

void double_strg(long double val, char* ret, flgs f) {
  char buf[BUFF_SIZE] = {'\0'};
  int ind = BUFF_SIZE - 2;
  int neg = val < 0 ? 1 : 0;   // TOFIX: we don't nead this line
  val = neg ? val * -1 : val;  // val = val < 0 ? val * -1 : val;
  long double l = 0, r = modfl(val, &l);
  if (f.precision == 0) {
    l = roundl(val);
    r = 0;
  }
  char fractions[BUFF_SIZE] = {
      '\0'};  // don not understand for what this's here
  for (int i = 0; i < f.precision; i++) {
    r = r * 10;
    fractions[i] = (int)r + '0';
  }
  long long right = roundl(r), left = l;
  if (!right) {
    for (int i = 0; i < f.precision; ind--, i++) buf[ind] = '0';
  } else {
    for (int i = s21_strlen(fractions); right || i > 0; right /= 10, ind--, i--)
      buf[ind] = (int)(right % 10 + 0.05) + '0';
  }

  if ((f.is_precision_set && f.precision != 0) ||  //
      (int)r ||                                    //
      (!f.is_precision_set && val == 0) ||         //
      s21_strlen(fractions))                       //
  {
    buf[ind--] = '.';
  }

  if (!left) {
    buf[ind] = '0';  // TOFIX: to buf[ind--] = '0'; like above
    ind--;
  } else {
    for (; left; left /= 10, ind--) buf[ind] = (int)(left % 10) + '0';
  }
  for (int i = 0; buf[ind + 1]; ind++, i++) {
    if (neg && i == 0) {
      ret[i] = '-';
      i++;
    }
    ret[i] = buf[ind + 1];
  }
}

void parse_mantiss(flgs f, char* buf, va_list lst) {
  long double val = 0;
  if (f.length == 'L') {
    val = va_arg(lst, long double);
  } else {
    val = va_arg(lst, double);
  }
  int pow = 0;
  char sign = (int)val == 0 ? '-' : '+';

  if ((int)val - val) {
    while ((int)val == 0) {
      pow++;
      val *= 10;
    }
  } else {
    sign = '+';
  }
  while ((int)val / 10 != 0) {
    pow++;
    val /= 10;
  }

  if (!f.is_precision_set) f.precision = 6;
  double_strg(val, buf, f);
  prepend_mantiss(buf, pow, sign);
  format_flgs(buf, f);
}

void prepend_mantiss(char* str, int pow, char sign) {
  int len = s21_strlen(str);
  str[len] = 'e';
  str[len + 1] = sign;
  str[len + 3] = pow % 10 + '0';
  pow /= 10;
  str[len + 2] = pow % 10 + '0';
  str[len + 4] = '\0';
}

void parse_float_Gg(flgs f, char* buf, va_list lst) {
  long double val = 0;
  if (f.length == 'L') {
    val = va_arg(lst, long double);
  } else {
    val = va_arg(lst, double);
  }

  if (!f.is_precision_set) {
    f.precision = 6;
  }
  if (f.precision == 0) f.precision = 1;
  int precision = f.precision;
  long double m_val = val;
  int pow = 0;
  if ((int)val - val) {
    while ((int)m_val == 0) {
      pow++;
      m_val *= 10;
    }
  }
  if (pow > 4) {
    f.precision = 0;
    double_strg(m_val, buf, f);
  } else {
    f.precision = 10;
    double_strg(val, buf, f);
  }
  format_gG_precision(buf, precision);
  if (pow > 4) prepend_mantiss(buf, pow, '-');
  remove_trailing_zeroes(buf);
  format_flgs(buf, f);
}

void remove_trailing_zeroes(char* buf) {
  int len = s21_strlen(buf);
  char* dot = s21_strchr(buf, '.');
  if (dot) {
    for (int i = len - 1; buf[i] != '.'; i--) {
      if (buf[i] == '0')
        buf[i] = '\0';
      else
        break;
    }
    if (dot[1] == '\0') dot[0] = '\0';
  }
}

void format_gG_precision(char* buf, int precision) {
  int sig_digs = 0;
  s21_size_t len = s21_strlen(buf);
  int not_zero_found = 0;

  for (s21_size_t i = 0; i < s21_strlen(buf); i++) {
    if ((buf[i] == '0' && !not_zero_found) || buf[i] == '.')
      continue;
    else
      not_zero_found = 1;

    if (s21_isdigit(buf[i]) && not_zero_found) {
      sig_digs++;
    }
    if (sig_digs == precision && i + 1 < len) {
      int next = buf[i + 1] == '.' ? 2 : 1;
      buf[i] = buf[i + next] - '0' > 5 ? (char)(buf[i] + 1) : buf[i];
      buf[i + 1] = '\0';
      break;
    }
  }
}

int s21_isdigit(char c) { return (c >= '0' && c <= '9'); }

// int main() {
//   char str1[BUFF_SIZE];
//   char str2[BUFF_SIZE];
// // 1
// //   char format[] = "%0.*i %d %4.*i %013d %d";
// //   int val = 69;

// //   s21_sprintf(str1, format, 5, val, -10431, 13, 5311, 0, -581813581);
// //   sprintf(str2, format, 5, val, -10431, 13, 5311, 0, -581813581);

// //   printf("%s\n", str1);
// //   printf("%s", str2);
// // 2
// //   char format[] = "%+5.31li";
// //   long int val = 698518581899;

// //   s21_sprintf(str1, format, 5, val);
// //   sprintf(str2, format, 5, val);

// //   printf("%s\n", str1);
// //   printf("%s", str2);
// // 3
// //   const char *format = "%lo, %o, %ho, %.5o, %5.o";
// //   long int val = 949149114140;

// //   s21_sprintf(str1, format, 5, val);
// //   sprintf(str2, format, 5, val);

// //   printf("%s\n", str1);
// //   printf("%s", str2);
// // 4
//     char *format = "%u";
//     unsigned int val = 14140;
//     s21_sprintf(str1, format, val);
//     sprintf(str2, format, val);

//     printf("%s\n", str1);
//     printf("%s", str2);

//   return 0;
// }
