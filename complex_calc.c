
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
        // else if (c == ' ')
        // {
        //     char white_space = ' ';
        //     strncat(buffer, &white_space, 1);
        //     while ((c == ' '))
        //     {
        //         c = fgetc(stdin);
                
        //         if (c == '\n')
        //         {
        //             goto newline;
        //         }
        //     }
        //     char a = (char) c;
        //     strncat(buffer, &a, 1);
        // }
        else
        {
            char a = (char) c;
            strncat(buffer, &a, 1);
        }
        
        
    }
}

void get_nums(char *operation, double *arguments, char *buffer)
{

    int d = 0;
    // d = sscanf(buffer, "%c", operation); 
    // if (d != 1)
    // {
    //     errno = 1;
    //     return;
    // }
    d = sscanf(buffer, " %c %lf %lf %lf %lf %lf ", operation, &arguments[0], &arguments[1], &arguments[2], &arguments[3], &arguments[4]);
    if (d < 5)
    {
        errno = 2;
        return;
    }
    else if (d > 5)
    {
        errno = 3;
        return;
    }
}

void complex_add(double *arguments, double *result)
{
    result[0] = arguments[0] + arguments[2];
    result[1] = arguments[1] + arguments[3];

    return;
}

void complex_subtract(double *arguments, double *result)
{
    result[0] = arguments[0] - arguments[2];
    result[1] = arguments[1] - arguments[3];

    return;
}

void complex_multiply(double *arguments, double *result)
{
    result[0] = (arguments[0] * arguments[2]) - (arguments[1] * arguments[3]);
    result[1] = (arguments[0] * arguments[3]) + (arguments[1] * arguments[2]);

    return;
}

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