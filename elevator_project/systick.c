#include "systick.h"
#include "stm32f10x.h"

// initialize systick timer with specified reload value and enables systick interrupt
void SysTick_Init(uint32_t reload_val)
{
	SysTick->CTRL = 0x0;
	SysTick->VAL = 0x0;
	SysTick->LOAD = reload_val;
	SysTick->CTRL |= SysTick_CTRL_CLKSOURCE | SysTick_CTRL_ENABLE;
	
}


// returns systick value
uint32_t SysTickGetVal(void)
{
	return SysTick->VAL;
}

// returns whether the systick timer has counted to 0 since the last read
uint8_t SysTickCountFlag(void)
{
	return ((SysTick->CTRL & 0x10000) >> 16);
}

// functions to disable systick interrupt (timer still on but doesn't cause interrupt)
void SysTickDisableInterrupt(void)
{
	SysTick->CTRL &= ~SysTick_CTRL_TICKINT;
}

// functions to enable systick interrupt (timer still on but doesn't cause interrupt)
void SysTickEnableInterrupt(void)
{
	SysTick->CTRL |= SysTick_CTRL_TICKINT;
}
