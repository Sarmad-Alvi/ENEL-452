/**
* main.c
*
* DESCRIPTION:
* This file contains the main function to run a CLI
* with a status window using a timer interrupt to
* update the status window and a UART2 interrupt to
* read input from the user.
*
* AUTHOR: Sarmad Alvi 200429983
*/

#include "stm32f10x.h"
#include "tasks.h"
#include <stdlib.h>
#include "pin.h"
#include "clock.h"
#include "uart.h"
#include "cli.h"
#include "tim.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include <stdio.h>


uint8_t counter = 0;

int main(void)
{
	clockInit();
	enable_port('A');
	init_led();
	tim2init();
	tim3init();
	uart2_init();
	uart2_interrupt_init();
	
	uint8_t buffer2[] = "\033[2J\033[7r\033[6d--------------------------------\n\r";
	CLI_Transmit(buffer2,sizeof(buffer2));
	
	print_arrow();
	
	initQueues();
	initTasks();
	
	vTaskStartScheduler();
	
}

void USART2_IRQHandler(void) {
	NVIC_DisableIRQ(TIM3_IRQn);
	USART2->SR &= ~(USART_SR_RXNE);
	char c = uart2_receive();
	CLI_Queue_Enqueue(c);
	NVIC_EnableIRQ(TIM3_IRQn);
	
}

void TIM3_IRQHandler(void) {
	if (counter == UINT8_MAX)
	{
		counter = 0;
	}
	else
	{
		counter++;
	}
	
	NVIC_DisableIRQ(TIM2_IRQn);
	uint8_t led_status_buffer[] = "\033[8m\033[?25l\0337\033[0;0H\033[KLed Status: ";
	uint8_t counter_buffer[20];
	counter_buffer[0] = '\0';
	CLI_Transmit(led_status_buffer,sizeof(led_status_buffer));
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
	sprintf((char*)counter_buffer, "\033[2;0H\033[KCount: %d", counter);
	CLI_Transmit(counter_buffer, sizeof(counter_buffer));
	
	uint8_t buffer5[] = "\033[0m\033[?25h\0338";
	CLI_Transmit(buffer5,sizeof(buffer5));
	TIM3->SR &= ~(0x01);
	NVIC_EnableIRQ(TIM2_IRQn);
}

