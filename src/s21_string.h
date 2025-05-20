#pragma once
#ifndef S21_STRING
#define S21_STRING

#include <math.h>
#include <stdarg.h>
#include <stdlib.h>

#define BUFF_SIZE 512

enum errorCode {
  _ERROR = -1,
  _OK,
};

typedef enum widthType { NONE_WIDTH, WIDTH_NUMBER, WIDTH_STAR } widthType;

typedef enum lengthType {
  NONE_LENGTH,
  LENGTH_SHORT,
  LENGTH_LONG,
  LENGTH_LONG_LONG,
  LENGTH_DOUBLE,
  LENGTH_LONG_DOUBLE
} lengthType;

typedef struct token {
  void *address;
  widthType widthType;
  lengthType lengthType;
  unsigned int width;
  char buffer[512];
  char spec;
} token;

#define NUMS_STR "0123456789"
#define s21_NULL ((void *)0)
#define spec_c 1
#define spec_d 2
#define spec_i 4
#define spec_e 8
#define spec_E 16
#define spec_f 32
#define spec_g 64
#define spec_G 128
#define spec_o 256
#define spec_s 512
#define spec_u 1024
#define spec_x 2048
#define spec_X 4096
#define spec_p 8192
#define spec_n 16384
#define spec_percent 32768

#define flag_minus 1
#define flag_plus 2
#define flag_space 4
#define flag_sharp 8
#define flag_0 16

#define len_h 1
#define len_l 2
#define len_L 4

typedef long unsigned s21_size_t;

typedef struct string_format {
  int specifier;
  int flags;
  int width;
  s21_size_t precision;
  int len;
  int is_precision;
} FORMAT;

// Ищет первое вхождение символа c (беззнакового символа) в первых n байтах
// строки, на которую указывает аргумент str.
void *s21_memchr(const void *str, int c, s21_size_t n);
// Сравнивает первые n байтов строк str1 и str2.
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
// Копирует n символов из источника в пункт назначения.
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
// Еще одна функция для копирования n символов из src в dest.
void *s21_memmove(void *dest, const void *src, s21_size_t n);
// Копирует символ c (беззнаковый символ) в первые n символов строки, на которую
// указывает аргумент str.
void *s21_memset(void *str, int c, s21_size_t n);
// Добавляет строку, на которую указывает src, в конец строки, на которую
// указывает dest.
char *s21_strcat(char *dest, const char *src);
// Добавляет строку, на которую указывает src, к концу строки, на которую
// указывает dest, длиной до n символов.
char *s21_strncat(char *dest, const char *src, s21_size_t n);
// Ищет первое вхождение символа c (беззнакового символа) в строке, на которую
// указывает аргумент str.
int s21_strcmp(const char *str1, const char *str2);
// Сравнивает строку, на которую указывает строка str1, со строкой, на которую
// указывает строка str2.
char *s21_strchr(const char *str, int c);
// Сравнивает не более первых n байтов строк str1 и str2.
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
// Копирует строку, на которую указывает src, в dest.
char *s21_strcpy(char *dest, const char *src);
// Копирует до n символов из строки, на которую указывает src, в dest.
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
// Вычисляет длину начального сегмента строки str1, который полностью состоит из
// символов, отсутствующих в строке str2.
s21_size_t s21_strcspn(const char *str1, const char *str2);
// Ищет во внутреннем массиве номер ошибки errnum и возвращает указатель на
// строку сообщения об ошибке. Вам необходимо объявить макросы, содержащие
// массивы сообщений об ошибках, для операционных систем Mac и Linux. Описания
// ошибок доступны в оригинальной библиотеке. Проверка текущей ОС осуществляется
// с помощью директив.
char *s21_strerror(int errnum);
// Вычисляет длину строки str до завершающего нулевого символа, но не включая
// его.
s21_size_t s21_strlen(const char *str);
s21_size_t s21_strlen_long(const wchar_t *str);
// Находит первый символ в строке str1, соответствующий любому символу,
// указанному в str2.
char *s21_strpbrk(const char *str1, const char *str2);
// Ищет последнее вхождение символа c (беззнакового символа) в строке, на
// которую указывает аргумент str.
char *s21_strrchr(const char *str, int c);
// Вычисляет длину начального сегмента строки str1, который полностью состоит из
// символов строки str2.
s21_size_t s21_strspn(const char *str1, const char *str2);
// Находит первое вхождение всей строки иглы (не включая завершающий нулевой
// символ), которая появляется в строковом стоге.
char *s21_strstr(const char *haystack, const char *needle);
// Разбивает строку str на серию токенов, разделенных разделителем.
char *s21_strtok(char *str, const char *delim);

// cs funcs
void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);
void *s21_trim(const char *src, const char *trim_chars);

// sprintf funcs
int s21_sprintf(char *str, const char *format, ...);
int handle_spec(char *str, const char *format, va_list arg, int *j);
void get_len(FORMAT *form, char sym, int *i);
void get_flags(FORMAT *form, char *format, int *i);
void get_specifier(FORMAT *form, char sym, int *i);
void get_precision(FORMAT *form, char *format, int *i, va_list arg);
void get_width(FORMAT *form, char *format, int *i, va_list arg);
int s21_atoi(char *str);
s21_size_t s21_itoa(long long num, char *str, int radix);
s21_size_t s21_utoa(unsigned long long num, char *str, int radix);
s21_size_t s21_ftoa(long double num, char *str, s21_size_t precision);
void format_spec(char *str, FORMAT *form, va_list arg, int *j);
int is_decimal(FORMAT *form);
int is_float(FORMAT *form);
int is_nradix(FORMAT *form);
void format_nradix(char *str, FORMAT *form, va_list arg, int *j);
void format_decimal(char *str, FORMAT *form, va_list arg, int *j);
void format_long(char *str, FORMAT *form, va_list arg, int *j);
void format_unsigned(char *str, FORMAT *form, va_list arg, int *j);
void format_pointer(char *str, FORMAT *form, va_list arg, int *j);
void format_char(char *str, FORMAT *form, va_list arg, int *j);
void format_string(char *str, FORMAT *form, va_list arg, int *j);
void format_string_long(char *str, FORMAT *form, va_list arg, int *j);
void format_percent(char *str, int *j);
void format_float(char *str, FORMAT *form, va_list arg, int *j);
void format_double(char *str, FORMAT *form, va_list arg, int *j);
char *upper(char *str);
void set_nulls(char *str, FORMAT *form);
int g_selector(int p, int x);
int calculate_notation(int notation, double *temp, int *positive_notation);
int calculate_notation_long(int notation, long double *temp,
                            int *positive_notation);
void calculate_precision(FORMAT *form, int total_notation, int total_precision);
int is_bonus_point(FORMAT *form);

// sscanf functions
int s21_sscanf(const char *str, const char *format, ...);

// sscanf parsers
token parseToken(char **formatPtr, va_list *va);
void parseWidth(char **formatPtr, token *result);
int parseNumber(char **formatPtr);
void parseLength(char **formatPtr, token *result);
void parseSpecifier(char **formatPtr, token *result);

// sscanf memory writers
int writeTokensToMemory(char **strPtr, token *tokens, int tokenLen);
int writeCharToMem(char **str, token *tok);
int writeStringToMem(char **str, token *tok);
void writeAcceptToBuffer(char **str, const char *accept, char *buffer,
                         int width, int startIndex);
int writeIntToMem(char **str, token *tok);
int writeFloatToMem(char **str, token *tok);
int writeUnsignedToMem(char **str, token *tok);
int writeUnspecToMem(char **str, token *tok);
int writeOctHexToMem(char **str, token *tok, int base);

// sscanf type converters
void intConverter(token *tok, long long int result);
void floatConverter(token *tok, long double result);

void unsignedConverter(token *tok, unsigned long long int result);
unsigned long long int s21_strntollu(const char *str, char **endptr, int basis,
                                     int n_byte);

// sscanf support function
int isSpace(char c);
int isDigit(char c);
int checkEOFString(const char *str);
int skipCharsInBuffer(char **str, token *tok);
void skipSpaces(char **str);

long double s21_strtold(const char *buffer);
long double s21_atoll(char *str);
// support function for s21_strtold
long double s21_atof(const char *buffer);
int includesExponent(const char *buffer);
long double applyExponent(long double result, const char *buffer);
long double returnInfOrNan(const char *buffer);
int includesInfOrNan(const char *buffer);
int caseInsnsSearch(const char *buffer, const char *pat);

#ifdef __APPLE__
#define ERR_MAX 107
#define STRERR_MAX 70
#define ERROR "Unknown error: "
#define ARRAY                                            \
  char errlist[ERR_MAX][STRERR_MAX] = {                  \
      "Undefined error: 0",                              \
      "Operation not permitted",                         \
      "No such file or directory",                       \
      "No such process",                                 \
      "Interrupted system call",                         \
      "Input/output error",                              \
      "Device not configured",                           \
      "Argument list too long",                          \
      "Exec format error",                               \
      "Bad file descriptor",                             \
      "No child processes",                              \
      "Resource deadlock avoided",                       \
      "Cannot allocate memory",                          \
      "Permission denied",                               \
      "Bad address",                                     \
      "Block device required",                           \
      "Resource busy",                                   \
      "File exists",                                     \
      "Cross-device link",                               \
      "Operation not supported by device",               \
      "Not a directory",                                 \
      "Is a directory",                                  \
      "Invalid argument",                                \
      "Too many open files in system",                   \
      "Too many open files",                             \
      "Inappropriate ioctl for device",                  \
      "Text file busy",                                  \
      "File too large",                                  \
      "No space left on device",                         \
      "Illegal seek",                                    \
      "Read-only file system",                           \
      "Too many links",                                  \
      "Broken pipe",                                     \
      "Numerical argument out of domain",                \
      "Result too large",                                \
      "Resource temporarily unavailable",                \
      "Operation now in progress",                       \
      "Operation already in progress",                   \
      "Socket operation on non-socket",                  \
      "Destination address required",                    \
      "Message too long",                                \
      "Protocol wrong type for socket",                  \
      "Protocol not available",                          \
      "Protocol not supported",                          \
      "Socket type not supported",                       \
      "Operation not supported",                         \
      "Protocol family not supported",                   \
      "Address family not supported by protocol family", \
      "Address already in use",                          \
      "Can't assign requested address",                  \
      "Network is down",                                 \
      "Network is unreachable",                          \
      "Network dropped connection on reset",             \
      "Software caused connection abort",                \
      "Connection reset by peer",                        \
      "No buffer space available",                       \
      "Socket is already connected",                     \
      "Socket is not connected",                         \
      "Can't send after socket shutdown",                \
      "Too many references: can't splice",               \
      "Operation timed out",                             \
      "Connection refused",                              \
      "Too many levels of symbolic links",               \
      "File name too long",                              \
      "Host is down",                                    \
      "No route to host",                                \
      "Directory not empty",                             \
      "Too many processes",                              \
      "Too many users",                                  \
      "Disc quota exceeded",                             \
      "Stale NFS file handle",                           \
      "Too many levels of remote in path",               \
      "RPC struct is bad",                               \
      "RPC version wrong",                               \
      "RPC prog. not avail",                             \
      "Program version wrong",                           \
      "Bad procedure for program",                       \
      "No locks available",                              \
      "Function not implemented",                        \
      "Inappropriate file type or format",               \
      "Authentication error",                            \
      "Need authenticator",                              \
      "Device power is off",                             \
      "Device error",                                    \
      "Value too large to be stored in data type",       \
      "Bad executable (or shared library)",              \
      "Bad CPU type in executable",                      \
      "Shared library version mismatch",                 \
      "Malformed Mach-o file",                           \
      "Operation canceled",                              \
      "Identifier removed",                              \
      "No message of desired type",                      \
      "Illegal byte sequence",                           \
      "Attribute not found",                             \
      "Bad message",                                     \
      "EMULTIHOP (Reserved)",                            \
      "No message available on STREAM",                  \
      "ENOLINK (Reserved)",                              \
      "No STREAM resources",                             \
      "Not a STREAM",                                    \
      "Protocol error",                                  \
      "STREAM ioctl timeout",                            \
      "Operation not supported on socket",               \
      "Policy not found",                                \
      "State not recoverable",                           \
      "Previous owner died",                             \
      "Interface output queue is full"}
#elif __linux__
#define ERR_MAX 134
#define STRERR_MAX 70
#define ERROR "Unknown error "
#define ARRAY                                              \
  char errlist[ERR_MAX][STRERR_MAX] = {                    \
      "Success",                                           \
      "Operation not permitted",                           \
      "No such file or directory",                         \
      "No such process",                                   \
      "Interrupted system call",                           \
      "Input/output error",                                \
      "No such device or address",                         \
      "Argument list too long",                            \
      "Exec format error",                                 \
      "Bad file descriptor",                               \
      "No child processes",                                \
      "Resource temporarily unavailable",                  \
      "Cannot allocate memory",                            \
      "Permission denied",                                 \
      "Bad address",                                       \
      "Block device required",                             \
      "Device or resource busy",                           \
      "File exists",                                       \
      "Invalid cross-device link",                         \
      "No such device",                                    \
      "Not a directory",                                   \
      "Is a directory",                                    \
      "Invalid argument",                                  \
      "Too many open files in system",                     \
      "Too many open files",                               \
      "Inappropriate ioctl for device",                    \
      "Text file busy",                                    \
      "File too large",                                    \
      "No space left on device",                           \
      "Illegal seek",                                      \
      "Read-only file system",                             \
      "Too many links",                                    \
      "Broken pipe",                                       \
      "Numerical argument out of domain",                  \
      "Numerical result out of range",                     \
      "Resource deadlock avoided",                         \
      "File name too long",                                \
      "No locks available",                                \
      "Function not implemented",                          \
      "Directory not empty",                               \
      "Too many levels of symbolic links",                 \
      "Unknown error 41",                                  \
      "No message of desired type",                        \
      "Identifier removed",                                \
      "Channel number out of range",                       \
      "Level 2 not synchronized",                          \
      "Level 3 halted",                                    \
      "Level 3 reset",                                     \
      "Link number out of range",                          \
      "Protocol driver not attached",                      \
      "No CSI structure available",                        \
      "Level 2 halted",                                    \
      "Invalid exchange",                                  \
      "Invalid request descriptor",                        \
      "Exchange full",                                     \
      "No anode",                                          \
      "Invalid request code",                              \
      "Invalid slot",                                      \
      "Unknown error 58",                                  \
      "Bad font file format",                              \
      "Device not a stream",                               \
      "No data available",                                 \
      "Timer expired",                                     \
      "Out of streams resources",                          \
      "Machine is not on the network",                     \
      "Package not installed",                             \
      "Object is remote",                                  \
      "Link has been severed",                             \
      "Advertise error",                                   \
      "Srmount error",                                     \
      "Communication error on send",                       \
      "Protocol error",                                    \
      "Multihop attempted",                                \
      "RFS specific error",                                \
      "Bad message",                                       \
      "Value too large for defined data type",             \
      "Name not unique on network",                        \
      "File descriptor in bad state",                      \
      "Remote address changed",                            \
      "Can not access a needed shared library",            \
      "Accessing a corrupted shared library",              \
      ".lib section in a.out corrupted",                   \
      "Attempting to link in too many shared libraries",   \
      "Cannot exec a shared library directly",             \
      "Invalid or incomplete multibyte or wide character", \
      "Interrupted system call should be restarted",       \
      "Streams pipe error",                                \
      "Too many users",                                    \
      "Socket operation on non-socket",                    \
      "Destination address required",                      \
      "Message too long",                                  \
      "Protocol wrong type for socket",                    \
      "Protocol not available",                            \
      "Protocol not supported",                            \
      "Socket type not supported",                         \
      "Operation not supported",                           \
      "Protocol family not supported",                     \
      "Address family not supported by protocol",          \
      "Address already in use",                            \
      "Cannot assign requested address",                   \
      "Network is down",                                   \
      "Network is unreachable",                            \
      "Network dropped connection on reset",               \
      "Software caused connection abort",                  \
      "Connection reset by peer",                          \
      "No buffer space available",                         \
      "Transport endpoint is already connected",           \
      "Transport endpoint is not connected",               \
      "Cannot send after transport endpoint shutdown",     \
      "Too many references: cannot splice",                \
      "Connection timed out",                              \
      "Connection refused",                                \
      "Host is down",                                      \
      "No route to host",                                  \
      "Operation already in progress",                     \
      "Operation now in progress",                         \
      "Stale file handle",                                 \
      "Structure needs cleaning",                          \
      "Not a XENIX named type file",                       \
      "No XENIX semaphores available",                     \
      "Is a named type file",                              \
      "Remote I/O error",                                  \
      "Disk quota exceeded",                               \
      "No medium found",                                   \
      "Wrong medium type",                                 \
      "Operation canceled",                                \
      "Required key not available",                        \
      "Key has expired",                                   \
      "Key has been revoked",                              \
      "Key was rejected by service",                       \
      "Owner died",                                        \
      "State not recoverable",                             \
      "Operation not possible due to RF-kill",             \
      "Memory page has hardware error"}
#endif

#endif