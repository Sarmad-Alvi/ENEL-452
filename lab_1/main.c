#include "stm32f10x.h"
#include <stdlib.h>
#include "pin.h"
#include "clock.h"

int main(void)
{
	clockInit();
	enable_port('A');
	enable_port('C');
	init_led();
	
	
	while(1)
	{
		led_flash(1200000);
	}
}
