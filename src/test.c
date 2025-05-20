#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_string.h"

#define BUF_SIZE 4096
#define LARGE_SIZE 500000
#define Pi 3.141592653589793

// cs_funcs
START_TEST(test_insert) {
  char src[15] = "Hello, World!", str1[] = "Brooo!";
  char *new_str = s21_insert(src, str1, 7);
  ck_assert_str_eq(new_str, "Hello, Brooo!");
  free(new_str);
  char num[] = "123", str2[] = "";
  new_str = s21_insert(num, str2, 3);
  ck_assert_str_eq(new_str, "123");
  free(new_str);
  char *nothing = NULL;
  new_str = s21_insert(nothing, str2, 0);
  ck_assert_ptr_null(new_str);
  free(new_str);
}
END_TEST

START_TEST(test_to_lower) {
  char str[] = "Hello, World!";
  char *str_low = s21_to_lower(str);
  ck_assert_str_eq(str_low, "hello, world!");
  free(str_low);
  char num[] = "123";
  str_low = s21_to_lower(num);
  ck_assert_str_eq(str_low, "123");
  free(str_low);
  char *nothing = NULL;
  str_low = s21_to_lower(nothing);
  ck_assert_ptr_null(str_low);
  free(str_low);
}
END_TEST

START_TEST(test_to_upper) {
  char str[] = "Hello, World!";
  char *str_up = s21_to_upper(str);
  ck_assert_str_eq(str_up, "HELLO, WORLD!");
  free(str_up);
  char num[] = "123";
  str_up = s21_to_upper(num);
  ck_assert_str_eq(str_up, "123");
  free(str_up);
  char *nothing = NULL;
  str_up = s21_to_upper(nothing);
  ck_assert_ptr_null(str_up);
  free(str_up);
}
END_TEST

START_TEST(test_trim) {
  char src[] = "123  Hello, World!  321", str1[] = "123 ";
  char *new_str = s21_trim(src, str1);
  ck_assert_str_eq(new_str, "Hello, World!");
  free(new_str);
  char num[] = " 123 ", str2[] = "";
  new_str = s21_trim(num, str2);
  ck_assert_str_eq(new_str, " 123 ");
  free(new_str);
  char *nothing = NULL;
  new_str = s21_trim(nothing, str2);
  ck_assert_ptr_null(new_str);
  free(new_str);
}
END_TEST

// sscanf
START_TEST(test_sscanf_c) {
  char str1[] = "Hello, World!";
  char c1, c2;
  s21_sscanf(str1, "%c", &c1);
  sscanf(str1, "%c", &c2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_sscanf_d) {
  char str2[] = "10|10|1000000";
  int d1, d2;
  short h1, h2;
  long l1, l2;
  s21_sscanf(str2, "%d|%hd|%ld", &d1, &h1, &l1);
  sscanf(str2, "%d|%hd|%ld", &d2, &h2, &l2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(h1, h2);
  ck_assert_int_eq(l1, l2);
}
END_TEST

START_TEST(test_sscanf_i) {
  char str_plus_minus[] = "10 -10 +10";
  int i1, i2, i3, i4, i5, i6;
  s21_sscanf(str_plus_minus, "%i %i %i", &i1, &i2, &i3);
  sscanf(str_plus_minus, "%i %i %i", &i4, &i5, &i6);
  ck_assert_int_eq(i1, i4);
  ck_assert_int_eq(i2, i5);
  ck_assert_int_eq(i3, i6);
  char str_dec_oct_hex[] = "123 0177 0x1F";
  s21_sscanf(str_dec_oct_hex, "%i %i %i", &i1, &i2, &i3);
  sscanf(str_dec_oct_hex, "%i %i %i", &i4, &i5, &i6);
  ck_assert_int_eq(i1, i4);
  ck_assert_int_eq(i2, i5);
  ck_assert_int_eq(i3, i6);
}
END_TEST

START_TEST(test_sscanf_e) {
  char str4[] = "123456789.0 -987654321.0 123456789.0 -987654321.0";
  float e1, e2, e3, e4;
  long double el1, el2, el3, el4;
  s21_sscanf(str4, "%e %Le %E %LE", &e1, &el1, &e2, &el2);
  sscanf(str4, "%e %Le %E %LE", &e3, &el3, &e4, &el4);
  ck_assert_float_eq(e1, e3);
  ck_assert_float_eq(e2, e4);
  ck_assert_double_eq(el1, el3);
  ck_assert_double_eq(el2, el4);
}
END_TEST

START_TEST(test_sscanf_f) {
  char str5[] = "3.14 3.141592 3.141592653589793";
  float f1, f2;
  double f3, f4;
  long double f5, f6;
  s21_sscanf(str5, "%f %lf %Lf", &f1, &f3, &f5);
  sscanf(str5, "%f %lf %Lf", &f2, &f4, &f6);
  ck_assert_float_eq(f1, f2);
  ck_assert_double_eq(f3, f4);
  ck_assert_double_eq(f5, f6);
  char str_lf[] = "18E2 18E-2";
  long double lf1, lf2, lf3, lf4;
  s21_sscanf(str_lf, "%Lf %Lf", &lf1, &lf2);
  sscanf(str_lf, "%Lf %Lf", &lf3, &lf4);
  ck_assert_double_eq(lf1, lf3);
  ck_assert_double_eq(lf2, lf4);
  char str_nan_inf[] = "nan infinity";
  double ni1, ni2;
  s21_sscanf(str_nan_inf, "%lf %lf", &ni1, &ni2);
  ck_assert_double_nan(ni1);
  ck_assert_double_infinite(ni2);
}
END_TEST

START_TEST(test_sscanf_g) {
  float g1, g2, g3, g4;
  long double gl1, gl2, gl3, gl4;
  char str6[] = "123.4567890 -987.6543210 123.4567890 -987.6543210";
  s21_sscanf(str6, "%g %Lg %G %LG", &g1, &gl1, &g2, &gl2);
  sscanf(str6, "%g %Lg %G %LG", &g3, &gl3, &g4, &gl4);
  ck_assert_float_eq(g1, g3);
  ck_assert_float_eq(g2, g4);
  ck_assert_double_eq(gl1, gl3);
  ck_assert_double_eq(gl2, gl4);
}
END_TEST

START_TEST(test_sscanf_o) {
  char str_oct[] = "012 -012";
  int o1, o2, o3, o4;
  s21_sscanf(str_oct, "%o %o", &o1, &o2);
  sscanf(str_oct, "%o %o", &o3, &o4);
  ck_assert_int_eq(o1, o3);
  ck_assert_int_eq(o2, o4);
}
END_TEST

START_TEST(test_sscanf_s) {
  char str1[] = "Hello, World!";
  char s1[BUF_SIZE], s2[BUF_SIZE];
  s21_sscanf(str1, "%s", s1);
  sscanf(str1, "%s", s2);
  ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_sscanf_u) {
  char str7[] = "10 10 1000000";
  unsigned short hu1, hu2;
  unsigned int u1, u2;
  unsigned long lu1, lu2;
  s21_sscanf(str7, "%hu %u %lu", &hu1, &u1, &lu1);
  sscanf(str7, "%hu %u %lu", &hu2, &u2, &lu2);
  ck_assert_int_eq(hu1, hu2);
  ck_assert_int_eq(u1, u2);
  ck_assert_int_eq(lu1, lu2);
}
END_TEST

START_TEST(test_sscanf_x) {
  char str8[] = "7fff 7fff ffe0b7f4";
  unsigned short hx1, hx2;
  unsigned int x1, x2;
  unsigned long lx1, lx2;
  s21_sscanf(str8, "%hx %x %lx", &hx1, &x1, &lx1);
  sscanf(str8, "%hx %x %lx", &hx2, &x2, &lx2);
  ck_assert_int_eq(hx1, hx2);
  ck_assert_int_eq(x1, x2);
  ck_assert_int_eq(lx1, lx2);
  char str9[] = "7FFF 7FFF FFE0B7F4";
  s21_sscanf(str9, "%hX %X %lX", &hx1, &x1, &lx1);
  sscanf(str9, "%hX %X %lX", &hx2, &x2, &lx2);
  ck_assert_int_eq(hx1, hx2);
  ck_assert_int_eq(x1, x2);
  ck_assert_int_eq(lx1, lx2);
  char str_long[] = "7FFFFFFFFFFFFFFF -7FFFFFFFFFFFFFFF";
  long long long1, long2, long3, long4;
  s21_sscanf(str_long, "%llx %llx", &long1, &long2);
  sscanf(str_long, "%llx %llx", &long3, &long4);
}
END_TEST

START_TEST(test_sscanf_p) {
  int ten = 10;
  int *ptr = &ten;
  char buffer[BUF_SIZE] = {0};
  s21_sprintf(buffer, "%p", ptr);
  int *sc_ptr1, *sc_ptr2;
  s21_sscanf(buffer, "%p", &sc_ptr1);
  sscanf(buffer, "%p", &sc_ptr2);
  ck_assert_ptr_eq(sc_ptr1, sc_ptr2);
  ck_assert_int_eq(*sc_ptr1, *sc_ptr2);
}
END_TEST

START_TEST(test_sscanf_n) {
  char str5[] = "3.14 3.141592 3.141592653589793";
  int n1, n2;
  s21_sscanf(str5, "%*s%n", &n1);
  sscanf(str5, "%*s%n", &n2);
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(test_sscanf_per) {
  char per[] = "100%%";
  char per1, per2;
  s21_sscanf(per, "%*d%%%c", &per1);
  sscanf(per, "%*d%%%c", &per2);
  ck_assert_int_eq(per1, per2);
}
END_TEST

// sprintf
START_TEST(test_sprintf_c) {
  char buffer1[BUF_SIZE] = {0}, buffer2[BUF_SIZE] = {0};
  int c = 65;
  s21_sprintf(buffer1, "%10c %-10c", c, c);
  sprintf(buffer2, "%10c %-10c", c, c);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_sprintf_d) {
  char buffer1[BUF_SIZE] = {0}, buffer2[BUF_SIZE] = {0};
  int ten = 10;
  s21_sprintf(buffer1, "%+0*d %10d %-10d", ten, ten, ten, ten);
  sprintf(buffer2, "%+0*d %10d %-10d", ten, ten, ten, ten);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_sprintf_hd_ld) {
  char buffer1[BUF_SIZE] = {0}, buffer2[BUF_SIZE] = {0};
  short h = 10;
  long ld = 1000000;
  s21_sprintf(buffer1, "% hd %ld", h, ld);
  sprintf(buffer2, "% hd %ld", h, ld);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_sprintf_i) {
  char buffer1[BUF_SIZE] = {0}, buffer2[BUF_SIZE] = {0};
  int ten = 10;
  s21_sprintf(buffer1, "%i %+i %+i", ten, -ten, +ten);
  sprintf(buffer2, "%i %+i %+i", ten, -ten, +ten);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_sprintf_e1) {
  char buffer1[BUF_SIZE] = {0}, buffer2[BUF_SIZE] = {0};
  double d = 123456789.0;
  s21_sprintf(buffer1, "%+#e", d);
  sprintf(buffer2, "%+#e", d);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_sprintf_e2) {
  char buffer1[BUF_SIZE] = {0}, buffer2[BUF_SIZE] = {0};
  double d = 123.4567890;
  s21_sprintf(buffer1, "% #E", d);
  sprintf(buffer2, "% #E", d);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_sprintf_f) {
  char buffer1[BUF_SIZE] = {0}, buffer2[BUF_SIZE] = {0};
  int ten = 10;
  double p = 10;
  s21_sprintf(buffer1, "%#.0f %10.2f %-12.4f %.*f", p, Pi, Pi, ten, Pi);
  sprintf(buffer2, "%#.0f %10.2f %-12.4f %.*f", p, Pi, Pi, ten, Pi);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_sprintf_g1) {
  char buffer1[BUF_SIZE] = {0}, buffer2[BUF_SIZE] = {0};
  double d = 123.4567890;
  long double lf1 = 123.567L;
  s21_sprintf(buffer1, "%g %.0g %#20.g %+#.Lg", d, d, d, lf1);
  sprintf(buffer2, "%g %.0g %#20.g %+#.Lg", d, d, d, lf1);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_sprintf_g2) {
  char buffer1[BUF_SIZE] = {0}, buffer2[BUF_SIZE] = {0};
  double d = 123.4567890;
  s21_sprintf(buffer1, "%#G % 0.4g %-+2.G", d, d, d);
  sprintf(buffer2, "%#G % 0.4g %-+2.G", d, d, d);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_sprintf_o) {
  char buffer1[BUF_SIZE] = {0}, buffer2[BUF_SIZE] = {0};
  int ten = 10;
  short h = 10;
  s21_sprintf(buffer1, "%#o %ho", ten, h);
  sprintf(buffer2, "%#o %ho", ten, h);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_sprintf_s) {
  char buffer1[BUF_SIZE] = {0}, buffer2[BUF_SIZE] = {0};
  char *str = "Hello, World!";
  s21_sprintf(buffer1, "%20s %-20s %.4s", str, str, str);
  sprintf(buffer2, "%20s %-20s %.4s", str, str, str);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_sprintf_ls) {
  char buffer1[BUF_SIZE] = {0}, buffer2[BUF_SIZE] = {0};
  wchar_t *ls = L"3wtf80";
  s21_sprintf(buffer1, "%20ls %-20ls %.2ls", ls, ls, ls);
  sprintf(buffer2, "%20ls %-20ls %.2ls", ls, ls, ls);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_sprintf_u) {
  char buffer1[BUF_SIZE] = {0}, buffer2[BUF_SIZE] = {0};
  int ten = 10;
  short h = 10;
  long ld = 1000000;
  s21_sprintf(buffer1, "%u %05hu %-10.lu", ten, h, ld);
  sprintf(buffer2, "%u %05hu %-10.lu", ten, h, ld);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_sprintf_x1) {
  char buffer1[BUF_SIZE] = {0}, buffer2[BUF_SIZE] = {0};
  int ten = 10;
  long ld = 1000000;
  s21_sprintf(buffer1, "%#x %#lx %-10x", ten, ld, ten);
  sprintf(buffer2, "%#x %#lx %-10x", ten, ld, ten);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_sprintf_x2) {
  char buffer1[BUF_SIZE] = {0}, buffer2[BUF_SIZE] = {0};
  int ten = 10;
  s21_sprintf(buffer1, "%#X %10X", ten, ten);
  sprintf(buffer2, "%#X %10X", ten, ten);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_sprintf_p) {
  char buffer1[BUF_SIZE] = {0}, buffer2[BUF_SIZE] = {0};
  int ten = 10;
  int *ptr = &ten;
  s21_sprintf(buffer1, "%20p %-20p", ptr, ptr);
  sprintf(buffer2, "%20p %-20p", ptr, ptr);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_sprintf_per) {
  char buffer1[BUF_SIZE] = {0}, buffer2[BUF_SIZE] = {0};
  s21_sprintf(buffer1, "%%");
  sprintf(buffer2, "%%");
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_sprintf_lf) {
  char buffer1[BUF_SIZE] = {0}, buffer2[BUF_SIZE] = {0};
  long double lf1 = 123.567L, lf2 = -123.567L;
  s21_sprintf(buffer1, "%Lf %Lf", lf1, lf2);
  sprintf(buffer2, "%Lf %Lf", lf1, lf2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// string_funcs
START_TEST(test_s21_memchr) {
  const char str1[] = "Hello, World!";
  // существующий символ
  ck_assert_ptr_eq(s21_memchr(str1, 'W', s21_strlen(str1)),
                   memchr(str1, 'W', strlen(str1)));
  // несуществующий символ
  ck_assert_ptr_null(s21_memchr(str1, 'A', s21_strlen(str1)));
  // большой массив данных
  char str2[LARGE_SIZE] = {0};
  for (int i = 0; i < LARGE_SIZE - 2; i++) str2[i] = 'A';
  str2[LARGE_SIZE - 2] = 'B';
  str2[LARGE_SIZE - 1] = '\0';
  ck_assert_ptr_eq(s21_memchr(str2, 'B', s21_strlen(str2)),
                   memchr(str2, 'B', strlen(str2)));
}
END_TEST

START_TEST(test_s21_memcmp) {
  char src1[] = "Hello, World!", src2[] = "hello, World!",
       dst1[] = "Hello, World!", dst2[] = "hello, World!";
  // равенство строк
  ck_assert_int_eq(s21_memcmp(src1, dst1, s21_strlen(src1)),
                   memcmp(src1, dst1, strlen(src1)));
  // в первой строке отличный байт больше
  ck_assert_int_eq(s21_memcmp(src2, dst1, s21_strlen(src2)),
                   memcmp(src2, dst1, strlen(src2)));
  // в первой строке отличный байт меньше
  ck_assert_int_eq(s21_memcmp(src1, dst2, s21_strlen(src1)),
                   memcmp(src1, dst2, strlen(src1)));
  // большой массив данных
  char dst3[LARGE_SIZE] = {0}, dst4[LARGE_SIZE] = {0};
  for (int i = 0; i < LARGE_SIZE; i++) {
    dst3[i] = 'A';
    dst4[i] = 'A';
  }
  dst3[LARGE_SIZE - 1] = '\0';
  dst4[LARGE_SIZE - 1] = '\0';
  ck_assert_int_eq(s21_memcmp(dst3, dst4, s21_strlen(dst3)),
                   memcmp(dst3, dst4, s21_strlen(dst3)));
}
END_TEST

START_TEST(test_s21_memcpy) {
  // простая строка
  char dst1[15] = {0}, dst2[15] = {0};
  const char src1[15] = "This is source";
  s21_memcpy(dst1, src1, s21_strlen(src1) + 1);
  memcpy(dst2, src1, strlen(src1) + 1);
  ck_assert_str_eq(dst1, dst2);
  // большой массив данных
  char dst3[LARGE_SIZE], dst4[LARGE_SIZE] = {0}, src2[LARGE_SIZE] = {0};
  for (int i = 0; i < LARGE_SIZE; i++) src2[i] = 'A';
  src2[LARGE_SIZE - 1] = '\0';
  s21_memcpy(dst3, src2, s21_strlen(src2) + 1);
  memcpy(dst4, src2, strlen(src2) + 1);
  ck_assert_str_eq(dst3, dst4);
  // пустая строка
  char dst5[1] = {0}, dst6[1] = {0};
  const char src3[] = "";
  s21_memcpy(dst5, src3, s21_strlen(src3) + 1);
  memcpy(dst6, src3, strlen(src3) + 1);
  ck_assert_str_eq(dst5, dst6);
  // пересечение массивов данных
  char dst7[] = "This is destination", dst8[] = "This is destination";
  s21_memcpy(dst7, src1, s21_strlen(src1) + 1);
  memcpy(dst8, src1, strlen(src1) + 1);
  ck_assert_str_eq(dst7, dst8);
  // строка меньше
  char dst9[20] = {0}, dst10[20] = {0};
  s21_memcpy(dst9, src1, s21_strlen(src1) + 1);
  memcpy(dst10, src1, strlen(src1) + 1);
  ck_assert_str_eq(dst9, dst10);
}
END_TEST

START_TEST(test_s21_memset) {
  // простая строка
  char dst1[] = "1234567890", dst2[] = "1234567890";
  ck_assert_str_eq(s21_memset(dst1, 'A', s21_strlen(dst1)),
                   memset(dst2, 'A', strlen(dst2)));
  // большой массив данных
  char dst3[LARGE_SIZE] = {0}, dst4[LARGE_SIZE] = {0};
  for (int i = 0; i < LARGE_SIZE; i++) {
    dst3[i] = 'A';
    dst4[i] = 'A';
  }
  dst3[LARGE_SIZE - 1] = '\0';
  dst4[LARGE_SIZE - 1] = '\0';
  ck_assert_str_eq(s21_memset(dst3, 'B', s21_strlen(dst3)),
                   memset(dst4, 'B', strlen(dst4)));
  // пустая строка
  char dst5[2] = {0}, dst6[2] = {0};
  ck_assert_str_eq(s21_memset(dst5, 'A', 1), memset(dst6, 'A', 1));
}
END_TEST

START_TEST(test_s21_strncat) {
  char dst1[15] = "12345", dst2[15] = "12345";
  const char app[] = "Hello";
  // простая строка
  ck_assert_str_eq(s21_strncat(dst1, app, 4), strncat(dst2, app, 4));
  // большой массив данных
  char dst3[LARGE_SIZE] = {0}, dst4[LARGE_SIZE] = {0};
  for (int i = 0; i < LARGE_SIZE - 6; i++) {
    dst3[i] = 'H';
    dst4[i] = 'H';
  }
  for (int i = LARGE_SIZE - 6; i < LARGE_SIZE; i++) {
    dst3[i] = '\0';
    dst4[i] = '\0';
  }
  ck_assert_str_eq(s21_strncat(dst3, app, 6), strncat(dst4, app, 6));
  // пустая строка
  char dst5[6] = {0}, dst6[6] = {0};
  ck_assert_str_eq(s21_strncat(dst5, app, 5), strncat(dst6, app, 5));
}
END_TEST

START_TEST(test_s21_strchr) {
  const char str[] = "Hello, World!";
  // существующий символ
  ck_assert_ptr_eq(s21_strchr(str, 'W'), strchr(str, 'W'));
  // несуществующий символ
  ck_assert_ptr_null(s21_strchr(str, 'A'));
  // большой массив данных
  char str2[LARGE_SIZE] = {0};
  for (int i = 0; i < LARGE_SIZE - 2; i++) str2[i] = 'A';
  str2[LARGE_SIZE - 2] = 'B';
  str2[LARGE_SIZE - 1] = '\0';
  ck_assert_ptr_eq(s21_strchr(str2, 'B'), strchr(str2, 'B'));
}
END_TEST

START_TEST(test_s21_strncmp) {
  char src1[] = "Hello, World!", src2[] = "hello, World!",
       dst1[] = "Hello, World!", dst2[] = "hello, World!";
  // равенство строк
  ck_assert_int_eq(s21_strncmp(src1, dst1, s21_strlen(src1)),
                   strncmp(src1, dst1, strlen(src1)));
  // в первой строке отличный байт больше
  ck_assert_int_ne(s21_strncmp(src2, dst1, s21_strlen(src2)), 0);
  // в первой строке отличный байт меньше
  ck_assert_int_ne(s21_strncmp(src1, dst2, s21_strlen(src1)), 0);
  // большой массив данных
  char dst3[LARGE_SIZE] = {0}, dst4[LARGE_SIZE] = {0};
  for (int i = 0; i < LARGE_SIZE; i++) {
    dst3[i] = 'A';
    dst4[i] = 'A';
  }
  dst3[LARGE_SIZE - 1] = '\0';
  dst4[LARGE_SIZE - 1] = '\0';
  ck_assert_int_eq(s21_strncmp(dst3, dst4, s21_strlen(dst3)),
                   strncmp(dst3, dst4, strlen(dst3)));
}
END_TEST

START_TEST(test_s21_strncpy) {
  // простая строка
  char dst1[15] = {0}, dst2[15] = {0};
  const char src1[] = "This is source";
  s21_strncpy(dst1, src1, s21_strlen(src1) + 1);
  strncpy(dst2, src1, strlen(src1) + 1);
  ck_assert_str_eq(dst1, dst2);
  // большой массив данных
  char dst3[LARGE_SIZE] = {0}, dst4[LARGE_SIZE] = {0}, src2[LARGE_SIZE] = {0};
  for (int i = 0; i < LARGE_SIZE; i++) src2[i] = 'A';
  src2[LARGE_SIZE - 1] = '\0';
  s21_strncpy(dst3, src2, s21_strlen(src2) + 1);
  strncpy(dst4, src2, strlen(src2) + 1);
  ck_assert_str_eq(dst3, dst4);
  // пустая строка
  char dst5[1] = {0}, dst6[1] = {0};
  const char src3[] = {0};
  s21_strncpy(dst5, src3, s21_strlen(src3) + 1);
  strncpy(dst6, src3, strlen(src3) + 1);
  ck_assert_str_eq(dst5, dst6);
  // пересечение массивов данных
  char dst7[] = "This is destination", dst8[] = "This is destination";
  s21_strncpy(dst7, src1, s21_strlen(src1) + 1);
  strncpy(dst8, src1, strlen(src1) + 1);
  ck_assert_str_eq(dst7, dst8);
  // строка меньше
  char dst9[20] = {0}, dst10[20] = {0};
  s21_strncpy(dst9, src1, s21_strlen(src1) + 1);
  strncpy(dst10, src1, strlen(src1) + 1);
  ck_assert_str_eq(dst9, dst10);
}
END_TEST

START_TEST(test_s21_strcspn) {
  const char str1[] = "Hello, World!", sym1[] = "l", sym2[] = "a", sym3[] = "",
             sym4[] = "B";
  // строка содержит символы
  ck_assert_int_eq(s21_strcspn(str1, sym1), strcspn(str1, sym1));
  // строка не содержит символы
  ck_assert_int_eq(s21_strcspn(str1, sym2), strcspn(str1, sym2));
  // пустая строка
  ck_assert_int_eq(s21_strcspn(str1, sym3), strcspn(str1, sym3));
  // большой массив данных
  char str2[LARGE_SIZE] = {0};
  for (int i = 0; i < LARGE_SIZE - 2; i++) str2[i] = 'A';
  str2[LARGE_SIZE - 2] = 'B';
  str2[LARGE_SIZE - 1] = '\0';
  ck_assert_int_eq(s21_strcspn(str2, sym4), strcspn(str2, sym4));
}
END_TEST

START_TEST(test_s21_strerror) {
  // код ошибки больше 0 и меньше ERR_MAX
  for (int i = 0; i < ERR_MAX; i++)
    ck_assert_str_eq(s21_strerror(i), strerror(i));
  // код ошибки больше ERR_MAX
  ck_assert_str_eq(s21_strerror(107), strerror(107));
  // код ошибки меньше 0
  ck_assert_str_eq(s21_strerror(-1), strerror(-1));
}
END_TEST

START_TEST(test_s21_strlen) {
  // простая строка
  const char str1[] = "Hello, World!";
  ck_assert_int_eq(s21_strlen(str1), strlen(str1));
  // большой массив данных
  char str2[LARGE_SIZE] = {0};
  for (int i = 0; i < LARGE_SIZE; i++) str2[i] = 'A';
  str2[LARGE_SIZE - 1] = '\0';
  ck_assert_int_eq(s21_strlen(str2), strlen(str2));
  // пустая строка
  const char str3[] = {0};
  ck_assert_int_eq(s21_strlen(str3), strlen(str3));
}
END_TEST

START_TEST(test_s21_strpbrk) {
  const char str1[] = "Hello, World!", sym1[] = "World", sym2[] = "abc",
             sym3[] = "", sym4[] = "B";
  // строка содержит символы
  ck_assert_ptr_eq(s21_strpbrk(str1, sym1), strpbrk(str1, sym1));
  // строка не содержит символы
  ck_assert_ptr_eq(s21_strpbrk(str1, sym2), strpbrk(str1, sym2));
  // пустая строка
  ck_assert_ptr_eq(s21_strpbrk(str1, sym3), strpbrk(str1, sym3));
  // большой массив данных
  char str2[LARGE_SIZE];
  for (int i = 0; i < LARGE_SIZE - 3; i++) str2[i] = 'A';
  str2[LARGE_SIZE - 3] = 'B';
  str2[LARGE_SIZE - 2] = 'C';
  str2[LARGE_SIZE - 1] = '\0';
  ck_assert_ptr_eq(s21_strpbrk(str2, sym4), strpbrk(str2, sym4));
}
END_TEST

START_TEST(test_s21_strrchr) {
  const char str[] = "Hello, World!";
  // существующий символ
  ck_assert_ptr_eq(s21_strrchr(str, 'l'), strrchr(str, 'l'));
  //   несуществующий символ
  ck_assert_ptr_null(s21_strrchr(str, 'A'));
  // большой массив данных
  char str2[LARGE_SIZE] = {0};
  for (int i = 0; i < LARGE_SIZE - 2; i++) str2[i] = 'A';
  str2[LARGE_SIZE - 2] = 'B';
  str2[LARGE_SIZE - 1] = '\0';
  ck_assert_ptr_eq(s21_strrchr(str2, 'A'), strrchr(str2, 'A'));
}
END_TEST

START_TEST(test_s21_strstr) {
  const char str1[] = "Hello, World!", sub1[] = "World", sub2[] = "abc",
             sub3[] = "", sub4[] = "AB";
  // строка содержит символы
  ck_assert_ptr_eq(s21_strstr(str1, sub1), strstr(str1, sub1));
  //   строка не содержит символы
  ck_assert_ptr_eq(s21_strstr(str1, sub2), strstr(str1, sub2));
  //   пустая строка
  ck_assert_ptr_eq(s21_strstr(str1, sub3), strstr(str1, sub3));
  //  большой массив данных
  char str2[10000] = {0};
  for (int i = 0; i < 1000 - 2; i++) str2[i] = 'A';
  str2[1000 - 2] = 'B';
  str2[1000 - 1] = '\0';
  ck_assert_ptr_eq(s21_strstr(str2, sub4), strstr(str2, sub4));
}
END_TEST

START_TEST(test_s21_strtok) {
  // строка содержит разделители
  char str1[] = "H/e l l/o", str2[] = "H/e l l/o";
  const char sep1[] = "/ ";
  char *s21_sub = s21_strtok(str1, sep1);
  char *std_sub = strtok(str2, sep1);
  int diff = 0;
  while (s21_sub != NULL) {
    diff = s21_memcmp(s21_sub, std_sub, s21_strlen(s21_sub));
    s21_sub = s21_strtok(NULL, sep1);
    std_sub = strtok(NULL, sep1);
  }
  ck_assert_int_eq(diff, 0);
  // строка не содержит разделители
  char str3[] = "Hello", str4[] = "Hello";
  s21_sub = s21_strtok(str3, sep1);
  std_sub = strtok(str4, sep1);
  diff = 0;
  while (s21_sub != NULL) {
    diff = s21_memcmp(s21_sub, std_sub, s21_strlen(s21_sub));
    s21_sub = s21_strtok(NULL, sep1);
    std_sub = strtok(NULL, sep1);
  }
  ck_assert_int_eq(diff, 0);
  //  пустая строка
  char str5[] = {0}, str6[] = {0};
  s21_sub = s21_strtok(str5, sep1);
  std_sub = strtok(str6, sep1);
  if (s21_sub == NULL && std_sub == NULL) diff = 0;
  ck_assert_int_eq(diff, 0);
  //  пустой разделитель
  const char sep2[] = {0};
  s21_sub = s21_strtok(str1, sep2);
  std_sub = strtok(str2, sep2);
  diff = 0;
  while (s21_sub != NULL) {
    diff = s21_memcmp(s21_sub, std_sub, s21_strlen(s21_sub));
    s21_sub = s21_strtok(NULL, sep2);
    std_sub = strtok(NULL, sep2);
  }
  ck_assert_int_eq(diff, 0);
  // большой массив данных
  char str7[10000] = {0}, str8[10000] = {0};
  const char sep3[] = " ";
  for (int i = 0; i < 10000; i++) {
    str7[i] = 'A';
    str8[i] = 'A';
    if ((i % 100 == 0) && (i != 10000)) {
      i += 1;
      str7[i] = ' ';
      str8[i] = ' ';
    }
  }
  str7[10000 - 1] = '\0';
  str8[10000 - 1] = '\0';
  s21_sub = s21_strtok(str7, sep3);
  std_sub = strtok(str8, sep3);
  diff = 0;
  while (s21_sub != NULL) {
    diff = s21_memcmp(s21_sub, std_sub, s21_strlen(s21_sub));
    s21_sub = s21_strtok(NULL, sep3);
    std_sub = strtok(NULL, sep3);
  }
  ck_assert_int_eq(diff, 0);
  // строка содержит несколько разделителей подряд
  char str9[] = "H///e  l  l///o", str10[] = "H///e  l  l///o";
  s21_sub = s21_strtok(str9, sep1);
  std_sub = strtok(str10, sep1);
  diff = 0;
  while (s21_sub != NULL) {
    diff = s21_memcmp(s21_sub, std_sub, s21_strlen(s21_sub));
    s21_sub = s21_strtok(NULL, sep1);
    std_sub = strtok(NULL, sep1);
  }
  ck_assert_int_eq(diff, 0);
}
END_TEST

START_TEST(test_s21_strcpy) {
  // простая строка
  char dst1[15] = {0}, dst2[15] = {0};
  const char src1[] = "This is source";
  ck_assert_str_eq(s21_strcpy(dst1, src1), strcpy(dst2, src1));
  // большой массив данных
  char dst3[LARGE_SIZE] = {0}, dst4[LARGE_SIZE] = {0}, src2[LARGE_SIZE] = {0};
  for (int i = 0; i < LARGE_SIZE; i++) src2[i] = 'A';
  src2[LARGE_SIZE - 1] = '\0';
  ck_assert_str_eq(s21_strcpy(dst3, src2), strcpy(dst4, src2));
  // пустая строка
  char dst5[1] = {0}, dst6[1] = {0};
  const char src3[] = {0};
  ck_assert_str_eq(s21_strcpy(dst5, src3), strcpy(dst6, src3));
  // пересечение массивов данных
  char dst7[] = "This is destination", dst8[] = "This is destination";
  ck_assert_str_eq(s21_strcpy(dst7, src1), strcpy(dst8, src1));
  // строка меньше
  char dst9[20] = {0}, dst10[20] = {0};
  s21_strcpy(dst9, src1);
  strcpy(dst10, src1);
  ck_assert_str_eq(dst9, dst10);
}
END_TEST

Suite *str_suite(void) {
  Suite *suite;
  TCase *tc_core;

  suite = suite_create("s21_string");
  tc_core = tcase_create("Core");

  // cs_funcs
  tcase_add_test(tc_core, test_insert);
  tcase_add_test(tc_core, test_to_lower);
  tcase_add_test(tc_core, test_to_upper);
  tcase_add_test(tc_core, test_trim);
  // scanf
  tcase_add_test(tc_core, test_sscanf_c);
  tcase_add_test(tc_core, test_sscanf_d);
  tcase_add_test(tc_core, test_sscanf_i);
  tcase_add_test(tc_core, test_sscanf_e);
  tcase_add_test(tc_core, test_sscanf_f);
  tcase_add_test(tc_core, test_sscanf_g);
  tcase_add_test(tc_core, test_sscanf_o);
  tcase_add_test(tc_core, test_sscanf_s);
  tcase_add_test(tc_core, test_sscanf_u);
  tcase_add_test(tc_core, test_sscanf_x);
  tcase_add_test(tc_core, test_sscanf_p);
  tcase_add_test(tc_core, test_sscanf_n);
  tcase_add_test(tc_core, test_sscanf_per);
  // sprintf
  tcase_add_test(tc_core, test_sprintf_c);
  tcase_add_test(tc_core, test_sprintf_d);
  tcase_add_test(tc_core, test_sprintf_hd_ld);
  tcase_add_test(tc_core, test_sprintf_i);
  tcase_add_test(tc_core, test_sprintf_e1);
  tcase_add_test(tc_core, test_sprintf_e2);
  tcase_add_test(tc_core, test_sprintf_f);
  tcase_add_test(tc_core, test_sprintf_g1);
  tcase_add_test(tc_core, test_sprintf_g2);
  tcase_add_test(tc_core, test_sprintf_o);
  tcase_add_test(tc_core, test_sprintf_s);
  tcase_add_test(tc_core, test_sprintf_ls);
  tcase_add_test(tc_core, test_sprintf_u);
  tcase_add_test(tc_core, test_sprintf_x1);
  tcase_add_test(tc_core, test_sprintf_x2);
  tcase_add_test(tc_core, test_sprintf_p);
  tcase_add_test(tc_core, test_sprintf_per);
  tcase_add_test(tc_core, test_sprintf_lf);
  // string_funcs
  tcase_add_test(tc_core, test_s21_memchr);
  tcase_add_test(tc_core, test_s21_memcmp);
  tcase_add_test(tc_core, test_s21_memcpy);
  tcase_add_test(tc_core, test_s21_memset);
  tcase_add_test(tc_core, test_s21_strncat);
  tcase_add_test(tc_core, test_s21_strchr);
  tcase_add_test(tc_core, test_s21_strncmp);
  tcase_add_test(tc_core, test_s21_strncpy);
  tcase_add_test(tc_core, test_s21_strcspn);
  tcase_add_test(tc_core, test_s21_strerror);
  tcase_add_test(tc_core, test_s21_strlen);
  tcase_add_test(tc_core, test_s21_strpbrk);
  tcase_add_test(tc_core, test_s21_strrchr);
  tcase_add_test(tc_core, test_s21_strstr);
  tcase_add_test(tc_core, test_s21_strtok);
  tcase_add_test(tc_core, test_s21_strcpy);

  suite_add_tcase(suite, tc_core);

  return suite;
}
int main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = str_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}