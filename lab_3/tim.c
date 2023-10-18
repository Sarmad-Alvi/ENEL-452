#include "stm32f10x.h"
#include "tim.h"

void tim1init(void)																				// Configure clocks and IO pins for TIM1 CH1
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_AFIOEN;
	TIM1->CR1 |= TIM_CR1_CEN; 															// Enable Timer1
	TIM1->CR2 |= TIM_CR2_OIS1;															// Output Idle State for Channel 1 OC1=1 when MOE=0
	TIM1->EGR |= TIM_EGR_UG; 																// Reinitialize the counter
	TIM1->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1;			// PWM mode 1,
	TIM1->CCMR1 |= TIM_CCMR1_OC1PE | TIM_CCMR1_OC1FE; 			// Preload Enable, Fast Enable
	TIM1->CCER |= TIM_CCER_CC1E; 														// Enable CH1
	TIM1->PSC = 0x095F; 																		// Divide 24 MHz by 2400 (PSC+1), PSC_CLK= 10000 Hz, 1 count = 0.1 ms
	TIM1->ARR = 100; 																				// 100 counts = 10 ms or 100 Hz
	TIM1->CCR1 = 50; 																				// 50 counts = 5 ms = 50% duty cycle
	TIM1->BDTR |= TIM_BDTR_MOE | TIM_BDTR_OSSI; 						// Main Output Enable, Force Idle Level First
	TIM1->CR1 |= TIM_CR1_ARPE | TIM_CR1_CEN; 								// Enable Timer1
}

void tim2init(void)																				// Configure clocks and IO pins for TIM2 CH1
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_AFIOEN;
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	// TIM2->CR1 |= TIM_CR1_CEN; 															// Enable Timer2
	// TIM2->CR2 |= TIM_CR2_OIS1;															// Output Idle State for Channel 1 OC1=1 when MOE=0
	// TIM2->EGR |= TIM_EGR_UG; 																// Reinitialize the counter
	// TIM2->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1;			// PWM mode 1,
	// TIM2->CCMR1 |= TIM_CCMR1_OC1PE | TIM_CCMR1_OC1FE; 			// Preload Enable, Fast Enable
	// TIM2->CCER |= TIM_CCER_CC1E; 														// Enable CH1
	TIM2->PSC = 0xE0F; 																			// Divide 36 MHz by 3600 (PSC+1), PSC_CLK= 10000 Hz, 1 count = 0.1 ms
	TIM2->ARR = 10; 																				// 10 counts = 1 ms or 1000 Hz, period 
	TIM2->CNT = 0;
	// TIM2->CCR1 = 50; 																				// 50 counts = 5 ms = 50% duty cycle
	TIM2->CR1 |= TIM_CR1_ARPE | TIM_CR1_CEN; 								// Enable Timer2
}

void tim3init(void)																				// Configure clocks and IO pins for TIM3 CH1
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPCEN | RCC_APB2ENR_AFIOEN;
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	GPIOA->CRL &= 0x0B000000;
	GPIOA->CRL |= GPIO_CRL_MODE6 | GPIO_CRL_CNF6_1;
	TIM3->CR1 |= TIM_CR1_CEN; 															// Enable Timer3
	TIM3->EGR |= TIM_EGR_UG; 																// Reinitialize the counter
	TIM3->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1;			// PWM mode 1
	TIM3->CCMR1 |= TIM_CCMR1_OC1PE | TIM_CCMR1_OC1FE; 			// Preload Enable, Fast Enable
	TIM3->CCER |= TIM_CCER_CC1E; 														// Enable CH1
	TIM3->PSC = 0x095F; 																		// Divide 24 MHz by 2400 (PSC+1), PSC_CLK= 10000 Hz, 1 count = 0.1 ms
	TIM3->ARR = 100; 																				// 100 counts = 10 ms or 100 Hz
	TIM3->CCR1 = 50; 																				// 50 counts = 5 ms = 50% duty cycle
	TIM3->CR1 |= TIM_CR1_ARPE | TIM_CR1_CEN; 								// Enable Timer3
}

void tim3updateCCR(uint16_t val)
{
	TIM3->CCR1 = val;
}

