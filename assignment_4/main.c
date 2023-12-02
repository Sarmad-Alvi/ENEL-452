/**
    Project: Assignment 4 - RT Analysis: LUT
    Course: ENEL 452
    Date: December 1, 2023
    Programmer: Sarmad Alvi

    Description: This program creates a lookup table of sine
    values for each angle between -359.5 to 359.5 with a resolution
    of 0.5 degrees. The program then iterates through 100,000 values
    using the lookup table and then the same with the built in
    sine function in C in order to measure the speed up factor.
    The clock() function is used to determine the time it took 
    for the code to run and calculate the speed up factor from 
    the look up table.

    Note: 1 TAB = 4 spaces

*/
#include <stdio.h>
#include <time.h>
#include <math.h>

int sin_table[1440];

void init_table() {
    for (int i = 0; i < 1440; ++i) {
        double angle = i * 0.5;
        double sinValue = sin(angle * M_PI / 180.0);
        sin_table[i] = (int)(sinValue * 100000);
    }
}

int main() {
    
    int iteration = 100000;
    init_table();

    clock_t start_lut = clock();

    for (int i = 0; i < iteration; ++i) {
        int index = (int)((i % 720) / 0.5) % 1440;
        int result = sin_table[index];
    }
    clock_t end_lut = clock();

    clock_t start_sin = clock();
    for (int i = 0; i < iteration; ++i) {
        double result = sin((i % 720 - 359.5) * M_PI / 180.0);
    }
    clock_t end_sin = clock();
    double lut_time = difftime(end_lut, start_lut) / CLOCKS_PER_SEC;
    double sin_time = difftime(end_sin, start_sin) / CLOCKS_PER_SEC;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    printf("Date: %d-%d-%d \n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
    printf("Measurement; using clock() with 1e9 loops. \n");
    printf("table lookup: %f seconds\n", lut_time);
    printf("Built in sin(): %f seconds\n", sin_time);
    printf("Table Speedup: %f\n", sin_time / lut_time);
}
