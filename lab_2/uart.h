#include "stm32f10x.h"

void uart1_init(void);
void uart1_send(uint16_t ascii);
char uart1_receive(void);
void uart2_init(void);
void uart2_terminate(void);
void uart2_send(uint16_t ascii);
char uart2_receive(void);

