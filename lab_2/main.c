#include "stm32f10x.h"
#include <stdlib.h>
#include "pin.h"
#include "clock.h"
#include "uart.h"
#include "cli.h"

int main(void)
{
	clockInit();
	enable_port('A');
	init_led();
	uart2_init();
	uint8_t buffer[512];
	buffer[0] = '\0';
	
	while(1)
	{
		CLI_Receive(buffer, 512);
		parse_command(buffer);
		buffer[0] = '\0';
	}
}
