#include "stm32f10x.h"

void SysTick_Init(uint32_t reload_val);
uint32_t SysTickGetVal(void);
uint8_t SysTickCountFlag(void);
void SysTickDisableInterrupt(void);
void SysTickEnableInterrupt(void);

