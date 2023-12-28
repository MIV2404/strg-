CC=gcc
FLAGS=-Wall -Werror -Wextra -std=c11
GLFLAGS=--coverage
LIBNAME=s21_string.a

TEST_DIR = tests/

rebuild: clean all

all: s21_string.a s21_sscanf

s21_string.a: 
		$(CC) $(FLAGS) -c ../s21*.c 
		ar rcs $(LIBNAME) *.o
		ranlib $(LIBNAME) s21_string.a

s21_sscanf :
	$(CC) $(CFLAGS) -o s21_sscanf s21_sscanf.c -L.. s21_string.a

clean :
	rm -f s21_sscanf *.o *.a

rebuild : clean all