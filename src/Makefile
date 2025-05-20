CFLAGS = -c -Wall -Werror -Wextra -std=c11
FLAGS = -std=c11
SOURCE = s21_*.c
OS := $(shell uname -s)
ifeq ($(OS), Linux)
LDFLAGS = -lcheck -lm -lsubunit
endif
ifeq ($(OS), Darwin)
LDFLAGS = -lcheck -lm
endif

all: s21_string.a clean_obj

s21_string.a:
	gcc $(CFLAGS) $(SOURCE)
	ar rc s21_string.a s21_*.o
	ranlib s21_string.a

test: clean test.c s21_string.a clean_obj
	gcc $(FLAGS) -o test test.c s21_string.a $(LDFLAGS)
	./test

gcov_report:clean $(SOURCE) clean_obj
	gcc --coverage $(SOURCE) test.c -o s21_test -lcheck -lm
	./s21_test
	lcov -t "s21_test" -o s21_test.info -c -d .
	genhtml -o report s21_test.info
	open ./report/index.html
	rm -rf *.gcno *.gcda *.info s21_test

clang:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -i *.c *.h
	rm -rf .clang-format

clang_review:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -n *.c *.h
	rm -rf .clang-format

rebuild: clean all 

clean_obj:
	rm -rf *.o

clean:
	rm -rf *.a *.o *.gcno *.gcda test *.info s21_test report
