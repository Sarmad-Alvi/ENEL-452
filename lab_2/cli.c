#include "stm32f10x.h"
#include "uart.h"
#include <string.h>
#include "pin.h"

void CLI_Transmit(uint8_t *pData, uint16_t size_t)
{
	for(int i = 0; i < size_t; i++)
	{
		uart2_send(pData[i]);
	}
}

void print_arrow(void)
{
	uint8_t buffer[] = "UART:~$ ";
	CLI_Transmit(buffer,sizeof(buffer));
}

void CLI_Receive(uint8_t *pData, uint16_t size_t)
{
	print_arrow();
	for(int i = 0; i < size_t; i++)
	{
		char received_char = uart2_receive();
		
		
		// When receiving carriage return or new line, send both carriage return and new line
		if ((received_char == 13) || (received_char == 10))
		{
			uart2_send(10);
			uart2_send(13);
			pData[i] = 0;
			break;
		}
		else if (received_char == 8 || received_char == 127)
		{
			pData[i-1] = NULL;
			uart2_send(received_char);
			i = i - 2;
		}
		else
		{
			pData[i] = received_char;
			uart2_send(received_char);
		}
		
	}
}

void parse_command(uint8_t *pData)
{
	if (!strncmp((char*)pData, "help\0", 6))
	{
		uint8_t buffer[] = "help - lists all available function\r\n\
led_on - turns on green led on the microcontroller\r\n\
led_off - turns off green led on microcontroller\r\n\
led_status - displays the status of the green led on the microcontroller \r\n\
clear - clears screen\r\n";
		CLI_Transmit(buffer, sizeof(buffer));
	}
	else if (!strncmp((char*)pData, "led_on\0", 8))
	{
		led_on();
		uint8_t buffer[] = "The green led is now on \r\n";
		CLI_Transmit(buffer,sizeof(buffer));
	}
	else if (!strncmp((char*)pData, "led_off\0", 8))
	{
		led_off();
		uint8_t buffer[] = "The green led is now off \r\n";
		CLI_Transmit(buffer,sizeof(buffer));
	}
	else if (!strncmp((char*)pData, "led_status\0", 8))
	{
		if(GPIOA->IDR & NUC_GREEN_ON)
		{
			uint8_t buffer[] = "The green led is on \r\n";
			CLI_Transmit(buffer,sizeof(buffer));
		}
		else
		{
			uint8_t buffer[] = "The green led is off \r\n";
			CLI_Transmit(buffer,sizeof(buffer));
		}
	}
	else if (!strncmp((char*)pData, "clear\0", 7))
	{
		uint8_t buffer[] = "\033[2J\033[H";
		CLI_Transmit(buffer,sizeof(buffer));
	}
	else
	{
		uint8_t buffer[] = "Invalid command \r\n";
		CLI_Transmit(buffer,sizeof(buffer));
	}
}


