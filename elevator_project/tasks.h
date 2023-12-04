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
#include "queues.h"
#include "systick.h"
#include <stdio.h>

#define IDLE_PRITORITY 1
#define BLINKY_PRIORITY 4
#define CLI_PRIORITY 4



static void vTaskGetFloor(void * parameters);
static void vTaskBlink(void * parameters);
static void vTaskCLI(void * parameters);
static void vTaskElevatorRun(void * parameters);

void initTasks(void);

#define IDLE_PRITORITY 1
#define BLINKY_PRIORITY 4
#define CLI_PRIORITY 4
#define BLINKY_QUEUE_LENGTH 1
#define BLINKY_QUEUE_ITEM_SIZE sizeof(uint8_t)
#define UP 1
#define DOWN 0
	
static QueueHandle_t xElevator_Call_Queue;
static QueueHandle_t xCLI_Queue;
static QueueHandle_t xBlinky_Speed;
static QueueHandle_t xFloor_Selection;
static QueueHandle_t xElevator_Call_Check;
static QueueHandle_t xElevator_Go_Queue;
static QueueHandle_t xElevator_Current_Location;
static QueueHandle_t xElevator_Direction;

void initQueues(void);
void CLI_Queue_Enqueue(char c);
uint16_t Floor_Selection_Queue_Peek(void);
uint16_t Last_Floor_Selection_Queue_Peek(void);
void Last_Floor_Selection_Overwrite(uint16_t a);
void Call_Queue_Overwrite(uint16_t a);
uint16_t Call_Queue_Dequeue(void);
uint16_t Call_Queue_Peek(void);
void Go_Queue_Overwrite(uint16_t a);
uint16_t Go_Queue_Peek(void);
void Current_Floor_Overwrite(uint16_t a);
uint16_t Current_Floor_Peek(void);
uint8_t Elevator_Direction_Peek(void);
void Elevator_Direction_Overwrite(uint8_t a);


