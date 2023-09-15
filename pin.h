#ifndef pins
#define pins

#include "stm32f10x.h"

// struct defines a pin as having a char port
// and a uint8_t pin number
// structure makes coding and defining pins easier
struct pin
{
	char port;
	uint8_t pin_num;
};

void set_pin(struct pin a, uint32_t b);




#endif
