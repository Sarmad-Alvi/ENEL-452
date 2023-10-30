/**
* cli.c
*
* DESCRIPTION:
* This file contains code to transmit and receive messages over uart.
* File also contains code to implement a CLI through uart. File contains
* code for sending and receivng through interrupts and polling.
*
* AUTHOR: Sarmad Alvi 200429983
*/

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
	uint8_t buffer[] = "\r\nUART:~$ ";
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
			pData[i] = '\0';
			break;
		}
		// When receiving backspace or delete key
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
	if (!strncmp((char*)pData, "help\r\n", 6))
	{
		uint8_t buffer[] = "help - lists all available function\r\n\
led_on - turns on green led on the microcontroller\r\n\
led_off - turns off green led on microcontroller\r\n\
led_status - displays the status of the green led on the microcontroller \r\n\
clear - clears screen\r\n";
		CLI_Transmit(buffer, sizeof(buffer));
	}
	else if (!strncmp((char*)pData, "led_on\r\n", 8))
	{
		led_on();
		uint8_t buffer[] = "The green led is now on \r\n";
		CLI_Transmit(buffer,sizeof(buffer));
	}
	else if (!strncmp((char*)pData, "led_off\r\n", 8))
	{
		led_off();
		uint8_t buffer[] = "The green led is now off \r\n";
		CLI_Transmit(buffer,sizeof(buffer));
	}
	else if (!strncmp((char*)pData, "led_status\r\n", 8))
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
	else if (!strncmp((char*)pData, "clear\r\n", 7))
	{
		uint8_t buffer2[] = "\033[0;0r\033[2JLed Status: ";
		CLI_Transmit(buffer2,sizeof(buffer2));
		uint8_t buffer3[] = "On";
		uint8_t buffer4[] = "Off";
		if(GPIOA->IDR & NUC_GREEN_ON)
		{
			CLI_Transmit(buffer3,sizeof(buffer3));
		}
		else
		{
			CLI_Transmit(buffer4,sizeof(buffer4));
		}
		
		uint8_t buffer5[] = "\033[7;0r\033[6d--------------------------------\n\r";
		CLI_Transmit(buffer5,sizeof(buffer5));
	}
	else if (!strncmp((char*)pData, "update\r\n", 7))
	{
		uint8_t buffer2[] = "\0337\033[0d\033[KLed Status: ";
		CLI_Transmit(buffer2,sizeof(buffer2));
		uint8_t buffer3[] = "On";
		uint8_t buffer4[] = "Off";
		if(GPIOA->IDR & NUC_GREEN_ON)
		{
			CLI_Transmit(buffer3,sizeof(buffer3));
		}
		else
		{
			CLI_Transmit(buffer4,sizeof(buffer4));
		}
		
		uint8_t buffer5[] = "\0338";
		CLI_Transmit(buffer5,sizeof(buffer5));
	}
	else
	{
		uint8_t buffer[] = "Invalid command \r\n";
		CLI_Transmit(buffer,sizeof(buffer));
	}
}

void CLI_Interrupt_Receive(uint8_t *pData, uint16_t size_t, int *i)
{
	char received_char = uart2_receive();
	
	// When receiving carriage return or new line, send both carriage return and new line
	if ((received_char == 13) || (received_char == 10))
	{
		uart2_send(10);
		uart2_send(13);
		uart2_send(10);
		uart2_send(13);
		pData[*i] = 13;
		pData[*i + 1] = 10;
		parse_command(pData);
		pData[0] = '\0';
		print_arrow();
		*i = 0;
		return;
	}
	// When receiving backspace or delete key
	else if ((received_char == 8 || received_char == 127) && (*i > 0))
	{
		pData[*i-1] = NULL;
		uart2_send(received_char);
		*i = *i - 2;
	}
	else if (received_char != 8 && received_char != 127)
	{
		pData[*i] = received_char;
		uart2_send(received_char);
	}
	else
	{
		return;
	}
	
	*i = *i + 1;
}


