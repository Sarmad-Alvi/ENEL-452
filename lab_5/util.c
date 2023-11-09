/**
* util.c
*
* DESCRIPTION:
* This file contains a simple delay function.
*
* AUTHOR: Sarmad Alvi 200429983
*/

#include "stm32f10x.h"
#include "util.h"

void delay(uint32_t delay)
{
  	 while (delay--)
	{
		}
}
