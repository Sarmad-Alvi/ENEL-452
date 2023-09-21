CC=g++

CFLAGS = -Wextra -Wall -Wfloat-equal -Wconversion -Wparentheses -pedantic -Wunused-parameter -Wunused-variable -Wreturn-type -Wunused-function -Wredundant-decls -Wreturn-type -Wunused-value -Wswitch-default -Wuninitialized -Winit-self

CERRORFLAG = -Werror

all: compile clean

main.o : main.c
	$(CC) -c main.c

compile: main.o
	$(CC) $(CFLAGS) main.o -o build/complex_calc
	
check: compile

clean: 
	rm -f *.o main

run: compile clean
	./build/main

error: main.o
	$(CC) $(CFLAGS) $(CERRORFLAG) main.o -o build/complex_calc

final: error clean