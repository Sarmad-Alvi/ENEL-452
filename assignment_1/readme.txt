This command line program reads user input of a character
followed by 4 numbers. The character determines the arithmetic
operation, and performs the calculation on the two pairs of
complex numbers. Operations include addition ('A'), subtraction ('S'),
multiplication ('M') and division ('D').

The program can be exited by inputting 'Q' as the first character.

The program is able to read and parse an input in the format shown below.
"A 1 2 3 4"

The calculator can also hand an arbitrary number of whitespace infront of,
behind or between the arguments. The calculator is also able to handle
lowercase or upper case for the operation character and is able to handle
no input or just whitespace as input.

The calculator is able to handle 4 types of errors.
    1: Illegal command, not using A, S, M, D, or Q.
    2: Missing arguments, if there are fewer than 4 number arguments.
    3: Extra arguments, if there are more than 4 number arguments.
    4: Divide by 0, when dividing, if the last 2 numbers are 0.

The program is built using the Makefile, which puts the build folder.