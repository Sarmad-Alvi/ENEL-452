#include "stm32f10x.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

void CLI_Transmit(uint8_t *pData, uint16_t size_t);
void CLI_Receive(uint8_t *pData, uint16_t size_t);
void parse_command(uint8_t *pData);
void print_arrow(void);
