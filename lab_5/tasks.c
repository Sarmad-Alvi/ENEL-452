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

QueueHandle_t xCLI_Queue;
QueueHandle_t xBlinky_Speed;
	
static void vTaskBlink(void * parameters);
static void vTaskCLI(void * parameters);

void initQueues(void)
{
	xCLI_Queue = xQueueCreate(BLINKY_QUEUE_LENGTH, BLINKY_QUEUE_ITEM_SIZE);
	xBlinky_Speed = xQueueCreate(1, BLINKY_QUEUE_ITEM_SIZE);
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

void initTasks(void)
{
	xTaskCreate(vTaskBlink, "Blinky", configMINIMAL_STACK_SIZE + 10, NULL, BLINKY_PRIORITY, NULL);
	xTaskCreate(vTaskCLI, "CLI", configMINIMAL_STACK_SIZE + 10, NULL, CLI_PRIORITY, NULL);
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
