/**
* tasks.c
*
* DESCRIPTION:
* This file contains the tasks and queues used by the RTOS
*
* AUTHOR: Sarmad Alvi 200429983
*/

#include "stm32f10x.h"
#include <stdlib.h>
#include "pin.h"
#include "clock.h"
#include "uart.h"
#include "cli.h"
#include "tim.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "tasks.h"
#include <stdio.h>
	
void initQueues(void)
{
	xCLI_Queue = xQueueCreate(BLINKY_QUEUE_LENGTH, BLINKY_QUEUE_ITEM_SIZE);
	xBlinky_Speed = xQueueCreate(1, BLINKY_QUEUE_ITEM_SIZE);
	xFloor_Selection = xQueueCreate(1, BLINKY_QUEUE_ITEM_SIZE);
	xElevator_Call_Queue = xQueueCreate(1, sizeof(uint16_t));
	xElevator_Call_Check = xQueueCreate(1, sizeof(uint8_t));
	if( xCLI_Queue == NULL  || xBlinky_Speed == NULL)
	{
		/* The queue could not be created. */
		led_flash(1000);
	}	
}

void CLI_Queue_Enqueue(char c)
{
	xQueueSendToBackFromISR(xCLI_Queue, &c, NULL);
}

void Blinky_Queue_Enqueue(int a)
{
	xQueueSendToBack(xBlinky_Speed, &a, NULL);
}

void Call_Queue_Overwrite(uint16_t a)
{
	xQueueOverwrite(xElevator_Call_Queue, &a);
}

uint16_t Call_Queue_Peek()
{
	uint16_t a = 0;
	if(xQueuePeek(xElevator_Call_Queue, &a, 0) == pdPASS)
	{
		
	}
	return a;
}

void Last_Floor_Selection_Overwrite(uint16_t a)
{
	xQueueOverwrite(xElevator_Call_Check, &a);
}

uint16_t Last_Floor_Selection_Queue_Peek()
{
	uint16_t a = 0;
	if(xQueuePeek(xElevator_Call_Check, &a, 0) == pdPASS)
	{
		return a;
	}
	else
	{
		return 99;
	}
	
}

uint16_t Call_Queue_Dequeue()
{
	uint16_t a = 0;
	if(xQueueReceive(xElevator_Call_Check, &a, 0) == pdPASS)
	{
		return a;
	}
	else
	{
		return 99;
	}
}

uint16_t Floor_Selection_Queue_Peek()
{
	uint16_t a = 0;
	if(xQueuePeek(xFloor_Selection, &a, 0) == pdPASS)
	{
		
	}
	return a;
}

void initTasks(void)
{
	//xTaskCreate(vTaskBlink, "Blinky", configMINIMAL_STACK_SIZE + 30, NULL, BLINKY_PRIORITY, NULL);
	xTaskCreate(vTaskGetFloor, "Floor_Selection", configMINIMAL_STACK_SIZE + 50, NULL, BLINKY_PRIORITY, NULL);
	xTaskCreate(vTaskCLI, "CLI", configMINIMAL_STACK_SIZE + 30, NULL, CLI_PRIORITY, NULL);
}

static void vTaskGetFloor(void * parameters)
{
	uint16_t floor_selection = 0;
	while(1)
	{
		vTaskSuspendAll();
		floor_selection = 0;
		
		floor_selection = (GPIOA->IDR & 0x1) | (GPIOA->IDR & 0x2) | ((GPIOA->IDR & 0x10) >> 2) | ((GPIOB->IDR & 0x1) << 3);
		xQueueOverwrite(xFloor_Selection, &floor_selection);
		xTaskResumeAll();
		taskYIELD();
	}
}

static void vTaskBlink(void * parameters)
{
	uint32_t speed = 100;
	while(1)
	{
		if(xQueueReceive(xBlinky_Speed, &speed, 0) == pdPASS)
		{
			
		}
		led_on();
		vTaskDelay(speed);
		led_off();
		vTaskDelay(speed);
	}
}

static void vTaskCLI(void * parameters)
{
	uint8_t buffer[50];
	buffer[0] = '\0';
	int buffer_index = 0;
	while(1)
	{
		if(xQueueReceive(xCLI_Queue, &buffer[buffer_index], 0) == pdPASS)
		{
			CLI_Interrupt_Receive(buffer, 0, &buffer_index);
		}
	}
}
