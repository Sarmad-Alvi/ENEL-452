#include "pin.h"
#include "stm32f10x.h"
#include <stdint.h>
#include "util.h"
uint32_t lookup_set(uint8_t a);
uint32_t lookup_reset(uint8_t a);

// function sets a pin high or low
// takes input of pin struct
// function checks which port the pin is and then enables or disables it
// using the BSRR register based on second argument of function
void set_pin(struct pin a, uint32_t b)
{
	switch(a.port)
	{
		case 'A':
			b = !b;
			GPIOA->BSRR |= (0x00000001 << (a.pin_num + (b * 16)));
			break;
		
		case 'B':
			b = !b;
			GPIOB->BSRR |= (0x00000001 << (a.pin_num + (b * 16)));
			break;
		
		case 'C':
			b = !b;
			GPIOC->BSRR |= (0x00000001 << (a.pin_num + (b * 16)));
			break;
	}
}

void led_flash(uint32_t delay_time)
{
	    while(1){
				GPIOA->BSRR = NUC_GREEN_ON;
				delay(delay_time);
				GPIOA->BSRR = NUC_GREEN_OFF;
				delay(delay_time);
			}
}

void init_led(void)
{
	GPIOA->CRL |= GPIO_CRL_MODE5;
	GPIOA->CRL &= ~GPIO_CRL_CNF5;
}
