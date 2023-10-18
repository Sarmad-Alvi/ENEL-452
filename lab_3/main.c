#include "stm32f10x.h"
#include <stdlib.h>
#include "pin.h"
#include "clock.h"
#include "uart.h"
#include "cli.h"
#include "tim.h"

int DATA_RECEIVED = 0;

int main(void)
{
	clockInit();
	enable_port('A');
	init_led();
	tim2init();
	uart2_init();
	uart2_interrupt_init();
	
	uint8_t buffer[512];
	buffer[0] = '\0';
	int char_count = 0;
	
	print_arrow();
	while(1)
	{
		
		if (DATA_RECEIVED == 1)
		{
			CLI_Interrupt_Receive(buffer, 512, &char_count);
			DATA_RECEIVED = 0;
		}
	}
}

void USART2_IRQHandler(void) {
	DATA_RECEIVED = 1; // Set the flag to indicate character reception
	USART2->SR &= ~(USART_SR_RXNE);
}

