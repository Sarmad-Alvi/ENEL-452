
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char **argv)
{
    fprintf(stderr, "Complex Calculator\n\n");
    fprintf(stderr, " Type a letter to specify the arithmetic operator (A, S, M, D)\n");
    fprintf(stderr, " followed by two complex numbers expressed as pairs of doubles.\n");
    fprintf(stderr, " Type Q to quit.\n\n");
    fprintf(stderr, "Enter exp: ");

    int c = 0;
    char *line;

    while ((c = fgetc(stdin)) != EOF)
    {
        if (c == 'A' || c == 'a')
        {
            char buffer[24];
            buffer[0] = '\0';
            int arguments[4];
            int d = 0;
            int arg_counter = 0;
            int null_tracker = 0;
            while ((d = fgetc(stdin)) != EOF)
            {
                if (arg_counter > 3)
                {
                    printf("error, too many arguments %d \n", arg_counter + 1);
                    while ((d = fgetc(stdin)) != EOF) {}
                    break;
                }

                if ((d == ' ' && strlen(buffer) != 0) || d == 10)
                {
                    null_tracker = 0;
                    arguments[arg_counter] = atoi(buffer);
                    printf("%d \n", arguments[arg_counter]);
                    memset(buffer, 0, 24);
                    arg_counter++;
                    if (d == 10)
                    {
                        break;
                    }
                }
                else
                {
                    char a = (char) d;
                    strncat(buffer, &a, 1);
                }
            }
            // for (int i = 0; i < 4; i++)
            // {
            //     printf("%d \n", arguments[i]);
            // }
            if (arg_counter < 4)
            {
                printf("too few arguments");
            }
        
        }
        else if (c == 'S' || c == 's')
        {

        }
        else if (c == 'M' || c == 'm')
        {

        }
        else if (c == 'D' || c == 'd')
        {

        }
        else if (c == 'Q' || c == 'q')
        {
            break;
        }
        else if (c != ' ')
        {
            printf("error invalid arguments \n");
        }
        
    }
}

