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

void led_flash(uint32_t delay_time);

void init_led(void);

#define NUC_GREEN_ON	0X00000020
#define NUC_GREEN_OFF	0x00200000 
#endif
