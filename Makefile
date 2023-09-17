CC=gcc

CFLAGS = -Wextra -Wall -Wfloat-equal -Wconversion -Wparentheses -pedantic -Wunused-parameter -Wunused-variable -Wreturn-type -Wunused-function -Wredundant-decls -Wreturn-type -Wunused-value -Wswitch-default -Wuninitialized -Winit-self

CERRORFLAG = -Werror

complex_calc.o : complex_calc.c
	$(CC) -c complex_calc.c

all: demo 

demo: complex_calc.o
	$(CC) $(CFLAGS) complex_calc.o -o build/complex_calc
	rm -f *.o complex_calc
check: all
	./build/complex_calc
clean: 
	rm -f *.o complex_calc