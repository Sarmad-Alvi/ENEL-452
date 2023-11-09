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

void initQueues(void);
void initTasks(void);
void CLI_Queue_Enqueue(char c);
void Blinky_Queue_Enqueue(int a);




