#include "stm32f10x.h"
#include "interrupt.h"


// 4 interrupt functions each take struct pin as input and checks the port of the pin
// to enable appropriate register for enabling interrupt for that pin
// on that port, and then enables the specified interrupt of that port and pin
void init_interrupt0(struct pin x)
{
	if(x.port == 'A')
	{
		RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_AFIOEN;
		AFIO->EXTICR[0] |= AFIO_EXTICR1_EXTI0_PA;
	}
	else if(x.port == 'B')
	{
		RCC->APB2ENR |= RCC_APB2ENR_IOPBEN | RCC_APB2ENR_AFIOEN;
		AFIO->EXTICR[0] |= AFIO_EXTICR1_EXTI0_PB;
	}
	else if(x.port == 'C')
	{
		RCC->APB2ENR |= RCC_APB2ENR_IOPCEN | RCC_APB2ENR_AFIOEN;
		AFIO->EXTICR[0] |= AFIO_EXTICR1_EXTI0_PC;
	}
	
	EXTI->IMR |= EXTI_IMR_MR0;
	EXTI->FTSR |= EXTI_FTSR_TR0;
	NVIC->ISER[0] |= NVIC_ISER_SETENA_6;
}

void init_interrupt1(struct pin x)
{
	if(x.port == 'A')
	{
		RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_AFIOEN;
		AFIO->EXTICR[0] |= AFIO_EXTICR1_EXTI1_PA;
	}
	else if(x.port == 'B')
	{
		RCC->APB2ENR |= RCC_APB2ENR_IOPBEN | RCC_APB2ENR_AFIOEN;
		AFIO->EXTICR[0] |= AFIO_EXTICR1_EXTI1_PB;
	}
	else if(x.port == 'C')
	{
		RCC->APB2ENR |= RCC_APB2ENR_IOPCEN | RCC_APB2ENR_AFIOEN;
		AFIO->EXTICR[0] |= AFIO_EXTICR1_EXTI1_PC;
	}
	
	EXTI->IMR |= EXTI_IMR_MR1;
	EXTI->FTSR |= EXTI_FTSR_TR1;
	NVIC->ISER[0] |= NVIC_ISER_SETENA_7;
}

void init_interrupt2(struct pin x)
{
	if(x.port == 'A')
	{
		RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_AFIOEN;
		AFIO->EXTICR[0] |= AFIO_EXTICR1_EXTI2_PA;
	}
	else if(x.port == 'B')
	{
		RCC->APB2ENR |= RCC_APB2ENR_IOPBEN | RCC_APB2ENR_AFIOEN;
		AFIO->EXTICR[0] |= AFIO_EXTICR1_EXTI2_PB;
	}
	else if(x.port == 'C')
	{
		RCC->APB2ENR |= RCC_APB2ENR_IOPCEN | RCC_APB2ENR_AFIOEN;
		AFIO->EXTICR[0] |= AFIO_EXTICR1_EXTI2_PC;
	}
	
	EXTI->IMR |= EXTI_IMR_MR2;
	EXTI->FTSR |= EXTI_FTSR_TR2;
	NVIC->ISER[0] |= NVIC_ISER_SETENA_8;
}

void init_interrupt3(struct pin x)
{
	if(x.port == 'A')
	{
		RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_AFIOEN;
		AFIO->EXTICR[0] |= AFIO_EXTICR1_EXTI3_PA;
	}
	else if(x.port == 'B')
	{
		RCC->APB2ENR |= RCC_APB2ENR_IOPBEN | RCC_APB2ENR_AFIOEN;
		AFIO->EXTICR[0] |= AFIO_EXTICR1_EXTI3_PB;
	}
	else if(x.port == 'C')
	{
		RCC->APB2ENR |= RCC_APB2ENR_IOPCEN | RCC_APB2ENR_AFIOEN;
		AFIO->EXTICR[0] |= AFIO_EXTICR1_EXTI3_PC;
	}
	
	EXTI->IMR |= EXTI_IMR_MR3;
	EXTI->FTSR |= EXTI_FTSR_TR3;
	NVIC->ISER[0] |= NVIC_ISER_SETENA_9;
}


