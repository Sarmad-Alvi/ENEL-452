CC=g++

CFLAGS = -Wextra -Wall -Wfloat-equal -Wconversion -Wparentheses -pedantic -Wunused-parameter -Wunused-variable -Wreturn-type -Wunused-function -Wredundant-decls -Wreturn-type -Wunused-value -Wswitch-default -Wuninitialized -Winit-self

CERRORFLAG = -Werror

all: compile clean

complex_calc.o : complex_calc.c
	$(CC) -c complex_calc.c

compile: complex_calc.o
	$(CC) $(CFLAGS) complex_calc.o -o build/complex_calc
	
check: compile

clean: 
	rm -f *.o complex_calc

run: compile clean
	./build/complex_calc

error: complex_calc.o
	$(CC) $(CFLAGS) $(CERRORFLAG) complex_calc.o -o build/complex_calc

final: error clean