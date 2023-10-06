#include "stm32f10x.h"

void uart1_init(void)
{
	RCC->APB2ENR |=  RCC_APB2ENR_IOPAEN | RCC_APB2ENR_AFIOEN | RCC_APB2ENR_USART1EN ;;
	GPIOA->CRH &= 0xFFFFFFBF;
	GPIOA->CRH |= GPIO_CRH_MODE9 | GPIO_CRH_CNF9_1;
	
	USART1->CR1 |= USART_CR1_UE;
	USART1->BRR = 0x9c4;
	USART1->CR1 |= USART_CR1_RE | USART_CR1_TE;
	USART1->CR1 |= USART_CR1_UE;
}

void uart1_send(uint16_t ascii)
{
	while (!(USART1->SR & USART_SR_TXE))
	{
		
	}
    
  USART1->DR = ascii;
}

char uart1_receive(void)
{
	while (!(USART1->SR & USART_SR_RXNE));
    
	return USART1->DR;
}

void uart2_init(void)
{
	RCC->APB1ENR |=  RCC_APB1ENR_USART2EN ;
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_AFIOEN;
	GPIOA->CRH &= 0xFFFFFFFB;
	GPIOA->CRL |= GPIO_CRL_MODE2 | GPIO_CRL_CNF2_1;
	
	USART2->CR1 |= USART_CR1_UE;
	USART2->BRR = 0x0139;
	USART2->CR1 |= USART_CR1_RE | USART_CR1_TE;
	USART2->CR1 |= USART_CR1_UE;
}

void uart2_terminate(void)
{
	RCC->APB1ENR &=  ~RCC_APB1ENR_USART2EN ;
	RCC->APB2ENR &= ~(RCC_APB2ENR_IOPAEN | RCC_APB2ENR_AFIOEN);
	//GPIOA->CRH &= 0xFFFFFFFB;
	GPIOA->CRL &= ~(GPIO_CRL_MODE2 | GPIO_CRL_CNF2_1);
	
	USART2->CR1 &= ~USART_CR1_UE;
	USART2->BRR = 0x0;
	USART2->CR1 &= ~(USART_CR1_RE | USART_CR1_TE);
	USART2->CR1 &= ~(USART_CR1_UE);
}

void uart2_send(uint16_t ascii)
{
	while (!(USART2->SR & USART_SR_TXE))
	{
		
	}
    
  USART2->DR = ascii;
}

char uart2_receive(void)
{
	while (!(USART2->SR & USART_SR_RXNE));
    
	return USART2->DR;
}
