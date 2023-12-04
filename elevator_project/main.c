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
#include "interrupt.h"
#include "systick.h"
#include "queues.h"

int main(void)
{
	clockInit();
	enable_port('A');
	enable_port('B');
	init_led();
	initQueues();
	tim2init();
	tim3init();
	uart2_init();
	uart2_interrupt_init();
	
	struct pin external_interrupt = {
		.pin_num = 1,
		.port = 'C',
	};
	
	init_interrupt1(external_interrupt);
	
	uint8_t buffer2[] = "\033[2J\033[7r\033[6d--------------------------------\n\r";
	CLI_Transmit(buffer2,sizeof(buffer2));
	
	print_arrow();
	
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

// TIM3 interrupt which updates the status window
void TIM3_IRQHandler(void) {
	uint8_t floor_selection = Floor_Selection_Queue_Peek(); // get dipswitch positions
	
	uint8_t buffer7[] = "\033[8m\033[?25l\0337\033[0;0H\033[K"; //set status window
	CLI_Transmit(buffer7,sizeof(buffer7));
	
	
	// Prints current elevator parameters, location, direction, dipswitch position, and the queues
	uint8_t current_floor_buffer[22];	
	uint16_t current_location = Current_Floor_Peek();
	sprintf((char*)current_floor_buffer, "Elevator Location: %d ", current_location);
	CLI_Transmit(current_floor_buffer, sizeof(current_floor_buffer));
	
	uint8_t elevator_direction = Elevator_Direction_Peek();
	
	if(elevator_direction == UP)
	{
		uint8_t direction_buffer[] = "\033[2;0H\033[KElevator Direction: UP";
		CLI_Transmit(direction_buffer, sizeof(direction_buffer));
	}
	else
	{
		uint8_t direction_buffer[] = "\033[2;0H\033[KElevator Direction: DOWN";
		CLI_Transmit(direction_buffer, sizeof(direction_buffer));
	}
	
	volatile uint16_t go_queue = Go_Queue_Peek();
	
	uint8_t go_queue_buffer[] = "\033[3;0H\033[KGo Queue: ";
	CLI_Transmit(go_queue_buffer, sizeof(go_queue_buffer));
	
	for (int i = 0; i < 16; i++)
	{
		if (((go_queue >> i) & 0x1) == 0x1)
		{
			uint8_t queue_buffer[4];
			sprintf((char*)queue_buffer, " %d,  ", i);
			CLI_Transmit(queue_buffer, sizeof(queue_buffer));
		}
	
	}
	
	uint8_t floor_buffer[29];
	
	sprintf((char*)floor_buffer, "\033[4;0H\033[KFloor Selection: %d  ", floor_selection);
	CLI_Transmit(floor_buffer, sizeof(floor_buffer));
	
	uint8_t call_queue_buffer[] = "\033[5;0H\033[KCall Queue: ";
	CLI_Transmit(call_queue_buffer, sizeof(call_queue_buffer));
	
	volatile uint16_t call_queue = Call_Queue_Peek();
	for (int i = 0; i < 16; i++)
	{
		if (((call_queue >> i) & 0x1) == 0x1)
		{
			uint8_t queue_buffer[4];
			sprintf((char*)queue_buffer, " %d,  ", i);
			CLI_Transmit(queue_buffer, sizeof(queue_buffer));
		}
		
	}
	
	uint8_t buffer5[] = "\033[0m\033[?25h\0338";
	CLI_Transmit(buffer5,sizeof(buffer5));
	TIM3->SR &= ~(0x01);
}

// External button interrupt (Pin C4) to add the floor currently selected by the dipswitch to the elevator queue
void EXTI1_IRQHandler(void) {
	EXTI->IMR &= ~EXTI_IMR_MR1;
	NVIC_DisableIRQ(TIM2_IRQn);
	
	uint16_t floor_selection = Floor_Selection_Queue_Peek();
	uint16_t last_floor_selection = Last_Floor_Selection_Queue_Peek();
	

	Last_Floor_Selection_Overwrite(floor_selection);
	uint16_t call_queue = Call_Queue_Peek();
	call_queue = call_queue | (0x1 << floor_selection);
	Call_Queue_Overwrite(call_queue);
	
	NVIC_EnableIRQ(TIM2_IRQn);
	EXTI->IMR |= EXTI_IMR_MR1;
	EXTI->PR |= EXTI_PR_PR1;
}

