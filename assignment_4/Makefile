CC=g++

CFLAGS = -O3 -Wextra -Wall -Wfloat-equal -Wconversion -Wparentheses -pedantic -Wunused-parameter -Wunused-variable -Wreturn-type -Wunused-function -Wredundant-decls -Wreturn-type -Wunused-value -Wswitch-default -Wuninitialized -Winit-self

CERRORFLAG = -Werror

MYDIR = build

all: compile

main.o : main.c
	$(CC) -c main.c

compile: mkdir main.o
	$(CC) $(CFLAGS) main.o -o build/lut_comparison
	
check: compile

clean: 
	rm -f *.o main

run: compile clean
	./build/main

error: mkdir main.o
	$(CC) $(CFLAGS) $(CERRORFLAG) main.o -o build/lut_comparison

final: error clean

mkdir: 
	mkdir -p $(MYDIR)