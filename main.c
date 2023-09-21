/**
    Project: Assignment 1 - A Complex Number Calculator
    Course: ENEL 452
    Date: September 21, 2023
    Programmer: Sarmad Alvi

    Description: This command line program reads user input of a character
        followed by 4 numbers. The character determines the arithmetic
        operation, and performs the calculation on the two pairs of
        complex numbers. Operations include addition ('A'), subtraction ('S'),
        multiplication ('M') and division ('D').

    Note: 1 TAB = 4 spaces

*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>

void get_nums(char *operation, double *arguments, char *buffer);
void print_reults(double *results);
void complex_add(double *arguments, double *result);
void complex_subtract(double *arguments, double *result);
void complex_multiply(double *arguments, double *result);
void complex_divide(double *arguments, double *result);

int main(int argc, char **argv)
{
    fprintf(stderr, "Complex Calculator\n\n");
    fprintf(stderr, " Type a letter to specify the arithmetic operator (A, S, M, D)\n");
    fprintf(stderr, " followed by two complex numbers expressed as pairs of doubles.\n");
    fprintf(stderr, " Type Q to quit.\n\n");
    fprintf(stderr, "Enter exp: ");

    int c = 0;
    double args[5];
    double *arguments = args;
    double answer[2];
    double *results = answer;
    char buffer[512];
    char operation;

    while ((c = fgetc(stdin)) != EOF)
    {   
        if (c == '\n')
        {
            get_nums(&operation, arguments, buffer);

            if (operation == 'A' || operation == 'a')
            {
                complex_add(arguments, results);
            }
            else if (operation == 'S' || operation == 's')
            {
                complex_subtract(arguments, results);
            }
            else if (operation == 'M' || operation == 'm')
            {
                complex_multiply(arguments, results);
            }
            else if (operation == 'D' || operation == 'd')
            {
                complex_divide(arguments, results);
            }
            else if (operation == 'Q' || operation == 'q')
            {
                break;
            }
            else
            {
                errno = 1;
            }

            buffer[0] = '\0';

            print_reults(results);
        }
        else
        {
            char a = (char) c;
            strncat(buffer, &a, 1);
        }
        
        
    }
}


/**
    get_nums: Function takes 3 pointers, operation, arguments, and buffer. 
        Operation is a character which stores the arithmetic operation 
        specified by the user. Arguments stores the 4 double values inputted
        by the user. The buffer stores the entire input from the user.
        The function reads the input buffer for a formated string.
        The operation of the calculation (add, subtract, etc.) is put into
        the operation pointer and the arguments in the arguments pointer.

        Function also sets errno if the input is invalid (too many or too
        few arguments)
*/
void get_nums(char *operation, double *arguments, char *buffer)
{

    int num_assigned = 0;

    num_assigned = sscanf(buffer, " %c %lf %lf %lf %lf %lf ", operation, &arguments[0], &arguments[1], &arguments[2], &arguments[3], &arguments[4]);
    if (num_assigned < 5)
    {
        errno = 2;
        return;
    }
    else if (num_assigned > 5)
    {
        errno = 3;
        return;
    }
}

/**
    complex_add: Function takes pointer to double arry which contains
        4 double values representing 2 complex numbers in the form
        (a + j b, c + j d -> [a, b, c, d]). Function adds the 2 
        complex numbers together and stores it into the results pointer
        in the form ((a + c) + j (b + d) -> [(a + b), (b + d)]).


*/
void complex_add(double *arguments, double *result)
{
    result[0] = arguments[0] + arguments[2];
    result[1] = arguments[1] + arguments[3];

    return;
}


/**
    complex_subtract: Function takes pointer to double arry which contains
        4 double values representing 2 complex numbers in the form
        (a + j b, c + j d -> [a, b, c, d]). Function subtracts the 2 
        complex numbers together and stores it into the results pointer
        in the form ((a - c) + j (b - d) -> [(a - b), (b - d)]).
*/
void complex_subtract(double *arguments, double *result)
{
    result[0] = arguments[0] - arguments[2];
    result[1] = arguments[1] - arguments[3];

    return;
}

/**
    complex_multiply: Function takes pointer to double arry which contains
        4 double values representing 2 complex numbers in the form
        (a + j b, c + j d -> [a, b, c, d]). Function multiplies the 2 
        complex numbers together and stores it into the results pointer
        in the form ((a * c - b * d) + j (a * c + b * d) -> 
        [(a * c - b * d), (a * c + b * d)]).
*/
void complex_multiply(double *arguments, double *result)
{
    result[0] = (arguments[0] * arguments[2]) - (arguments[1] * arguments[3]);
    result[1] = (arguments[0] * arguments[3]) + (arguments[1] * arguments[2]);

    return;
}


/**
    complex_divide: Function takes pointer to double arry which contains
        4 double values representing 2 complex numbers in the form
        (a + j b, c + j d -> [a, b, c, d]). Function divides the 2 
        complex numbers together and stores it into the results pointer
        in the form (((a * c + b * d) / (c * c + d * d)) + 
        j ((a * c - b * d) / (c * c + d * d)) -> 

        [((a * c + b * d) / (c * c + d * d)), 
        ((a * c - b * d) / (c * c + d * d))]).

        Function also sets errno in case of divide by 0 error
*/
void complex_divide(double *arguments, double *result)
{
    if (arguments[2] == 0 && arguments[3] == 0)
    {
        errno = 4;
        return;
    }
    result[0] = ((arguments[0] * arguments[2]) + (arguments[1] * arguments[3])) / ((arguments[2] * arguments[2]) + (arguments[3] * arguments[3]));
    result[1] = ((arguments[1] * arguments[2]) - (arguments[0] * arguments[3])) / ((arguments[2] * arguments[2]) + (arguments[3] * arguments[3]));

    return;
}


/**
    print_results: Function takes a pointer to an array of doubles containing
        2 double values representing a complex number in the form 
        (a + j b -> [a, b]). The function prints the results to stdout if
        there was no error. Otherwise prints error message according
        to error code.
*/
void print_reults(double *result)
{
    if (errno == 0)
    {
        if (result[1] < 0)
        {
            fprintf(stdout, "%g - j %g \n", result[0], (result[1]) * -1);
        }
        else
        {
            fprintf(stdout, "%g + j %g \n", result[0], result[1]);
        }
    }
    else
    {
        switch (errno)
        {
        case 1:
            fprintf(stdout, "error code: 1: illegal command");
            break;
        
        case 2:
            fprintf(stdout, "error code: 2: missing arguments");
            break;

        case 3:
            fprintf(stdout, "error code: 3: extra arguments");
            break;

        case 4:
            fprintf(stdout, "error code: 4: divide by zero");
            break;

        default:
            break;
        } 
    }
    errno = 0;
    fprintf(stderr, "Enter exp: ");
}