#include "stm32f10x.h"
#include <stdlib.h>
#include "pin.h"
#include "clock.h"
#include "uart.h"
#include "tim.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include <stdio.h>

#define IDLE_PRITORITY 1
#define BLINKY_PRIORITY 4
#define CLI_PRIORITY 4
#define BLINKY_QUEUE_LENGTH 1
#define BLINKY_QUEUE_ITEM_SIZE sizeof(uint8_t)
	
static QueueHandle_t xElevator_Call_Queue;
static QueueHandle_t xCLI_Queue;
static QueueHandle_t xBlinky_Speed;
static QueueHandle_t xFloor_Selection;
static QueueHandle_t xElevator_Call_Check;

static void vTaskGetFloor(void * parameters);
static void vTaskBlink(void * parameters);
static void vTaskCLI(void * parameters);

	
void initQueues(void);
void initTasks(void);
void CLI_Queue_Enqueue(char c);
//void Blinky_Queue_Enqueue(int a);
uint16_t Floor_Selection_Queue_Peek(void);
uint16_t Last_Floor_Selection_Queue_Peek(void);
void Last_Floor_Selection_Overwrite(uint16_t a);
void Call_Queue_Overwrite(uint16_t a);
uint16_t Call_Queue_Dequeue(void);
uint16_t Call_Queue_Peek(void);



