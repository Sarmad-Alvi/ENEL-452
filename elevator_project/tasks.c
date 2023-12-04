/**
* tasks.c
*
* DESCRIPTION:
* This file contains the tasks and queues used by the RTOS
*
* AUTHOR: Sarmad Alvi 200429983
*/
#include "tasks.h"

void initTasks(void)
{
	xTaskCreate(vTaskGetFloor, "Floor_Selection", configMINIMAL_STACK_SIZE + 50, NULL, BLINKY_PRIORITY, NULL);
	xTaskCreate(vTaskCLI, "CLI", configMINIMAL_STACK_SIZE + 30, NULL, CLI_PRIORITY, NULL);
	xTaskCreate(vTaskElevatorRun, "Elevator_Run", configMINIMAL_STACK_SIZE + 30, NULL, CLI_PRIORITY, NULL);
}

// Task that reads the current position of the dip switch connected to GPIO Pins A0, A1, A4, and B0
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
		taskYIELD()

	}
}

// Task changes elevator location based on whether the elevator is going up or down and updates the queues when it has 
// arrived at the location
static void vTaskElevatorRun(void * parameters)
{
	volatile uint16_t call_queue = 0;
	uint8_t elevator_direction = DOWN;
	uint8_t current_location = 0;
	volatile uint16_t go_queue = 0;
	while(1)
	{
		call_queue = Call_Queue_Peek();
		go_queue = Go_Queue_Peek();
		Current_Floor_Overwrite(current_location);
		if((call_queue > 0 || go_queue > 0))
		{			
			if (elevator_direction == UP)
			{
				call_queue = Call_Queue_Peek();
				go_queue = Go_Queue_Peek();
				current_location = Current_Floor_Peek();
				for(int i = current_location; i < 16; i++)
				{
					vTaskDelay(100);
					uint16_t floor_check_call = (call_queue >> i) & 0x1;
					uint16_t floor_check_go = (go_queue >> i) & 0x1;
					
					current_location = i;
					Current_Floor_Overwrite(current_location);
					
					if((floor_check_call || floor_check_go))
					{
						
						uint16_t new_go_queue = ~(0x1 << i) & go_queue;
						uint16_t new_call_queue = ~(0x1 << i) & call_queue;
						Go_Queue_Overwrite(new_go_queue);
						Call_Queue_Overwrite(new_call_queue);
						
						uint8_t buffer[22];
						sprintf((char*)buffer, "\r\nArrived at floor %d\r\n", current_location);
						CLI_Transmit(buffer, sizeof(buffer));
						
					}
					
					
					// mask to check if there are any floors below the current floor in any of the queues
					uint16_t mask = (~(0x1 << current_location) - ((0x1 << current_location) -1));
					
					if((call_queue & mask) == 0  && (go_queue & mask) == 0)
					{
						elevator_direction = DOWN;
						Elevator_Direction_Overwrite(elevator_direction);
						print_arrow();
						break;
					}
				}
			}
			else
			{
				call_queue = Call_Queue_Peek();
				go_queue = Go_Queue_Peek();
				current_location = Current_Floor_Peek();
				for(int i = current_location; i >= 0; i--)
				{
					vTaskDelay(100);
					uint16_t floor_check_call = (call_queue >> i) & 0x1;
					uint16_t floor_check_go = (go_queue >> i) & 0x1;
					
					current_location = i;
					Current_Floor_Overwrite(current_location);
					
					if((floor_check_call || floor_check_go))
					{						
						uint16_t new_go_queue = ~(0x1 << i) & go_queue;
						uint16_t new_call_queue = ~(0x1 << i) & call_queue;
						Go_Queue_Overwrite(new_go_queue);
						Call_Queue_Overwrite(new_call_queue);
						
						uint8_t buffer[22];
						sprintf((char*)buffer, "\r\nArrived at floor %d\r\n", i);
						CLI_Transmit(buffer, sizeof(buffer));
						
					}
					
					// mask to check if there are any floors below the current floor in any of the queues
					uint16_t mask = ~(~(0x1 << current_location) - ((0x1 << current_location) -1));
					if((call_queue & mask) == 0  && (go_queue & mask) == 0)
					{
						elevator_direction = UP;
						Elevator_Direction_Overwrite(elevator_direction);
						break;
					}
				}
			}
		}
		
	}
}

// CLI task to takes values from the UART2 interrupt queue and processes them
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

// Initializes all queues used in project
void initQueues(void)
{
	xCLI_Queue = xQueueCreate(BLINKY_QUEUE_LENGTH, BLINKY_QUEUE_ITEM_SIZE);
	xBlinky_Speed = xQueueCreate(1, BLINKY_QUEUE_ITEM_SIZE);
	xFloor_Selection = xQueueCreate(1, BLINKY_QUEUE_ITEM_SIZE);
	xElevator_Call_Queue = xQueueCreate(1, sizeof(uint16_t));
	xElevator_Call_Check = xQueueCreate(1, sizeof(uint8_t));
	xElevator_Go_Queue = xQueueCreate(1, sizeof(uint16_t));
	xElevator_Current_Location = xQueueCreate(1, sizeof(uint8_t));
	xElevator_Direction = xQueueCreate(1, sizeof(uint8_t));
	if( xCLI_Queue == NULL  || xBlinky_Speed == NULL)
	{
		/* The queue could not be created. */
		led_flash(1000);
	}	
}

// Various functions to enqueue, dequeue, overwrite, or peek at values in different queues
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

void Go_Queue_Overwrite(uint16_t a)
{
	xQueueOverwrite(xElevator_Go_Queue, &a);
}

void Elevator_Direction_Overwrite(uint8_t a)
{
	xQueueOverwrite(xElevator_Direction, &a);
}

uint8_t Elevator_Direction_Peek()
{
	uint8_t a = 0;
	if(xQueuePeek(xElevator_Direction, &a, 0) == pdPASS)
	{
	}
	return a;
	
}

uint16_t Go_Queue_Peek()
{
	uint16_t a = 0;
	if(xQueuePeek(xElevator_Go_Queue, &a, 0) == pdPASS)
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

void Current_Floor_Overwrite(uint16_t a)
{
	xQueueOverwrite(xElevator_Current_Location, &a);
}

uint16_t Current_Floor_Peek()
{
	uint16_t a = 0;
	if(xQueuePeek(xElevator_Current_Location, &a, 0) == pdPASS)
	{
		return a;
	}
	else
	{
		return 0;
	}
	
}
