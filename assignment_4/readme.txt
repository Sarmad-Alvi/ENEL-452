Target: Ryzen 5 3600 @ 4.2 GHz
Date: 2023-12-01
Compiler: g++ 11.4.0
Switches:   -O3 -Wextra -Wall -Wfloat-equal -Wconversion -Wparentheses 
            -pedantic -Wunused-parameter -Wunused-variable -Wreturn-type 
            -Wunused-function -Wredundant-decls -Wreturn-type -Wunused-value 
            -Wswitch-default -Wuninitialized -Winit-self
Measurement: using clock() with 100,000 loops.
Function Speed
---------------------------
table lookup 0.000471 seconds
Built in sin() 0.001851 seconds
Table Speedup 3.929936x

NOTE: I ran the program multiple times and each time it gave a different answer,
    sometimes they varied by a large amount (~2x to ~14x). Most of the time
    the speed up factor was around 3x. I tried removing all compiler flags,
    or just keeping the -O3 flag, but each time the results varied. I think
    this may just be a result of compiler optimizations.