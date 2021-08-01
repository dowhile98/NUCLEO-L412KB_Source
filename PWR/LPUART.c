#include "LPUART.h"

/**
  * @fn CONFIGURA EL LPUART1
	* @param frencuencia de funcionamiento del LPUART1
	* @param BUAD : la taza baudios deseada
	*/
void LPUART1_Config(uint32_t fck,uint32_t BUAD){
	/*PA2->TX*/
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
	GPIOA->MODER &=~ GPIO_MODER_MODE2;
	GPIOA->MODER |= GPIO_MODER_MODE2_1;
	GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED2;
	GPIOA->AFR[0] &=~ GPIO_AFRL_AFRL2;
	GPIOA->AFR[0] |= 0x8U<<GPIO_AFRL_AFSEL2_Pos;
	/*LPUART1*/
	RCC->APB1ENR2 |=   RCC_APB1ENR2_LPUART1EN;
	/*BUAD*/
	/*cambiamos la fuente de reloj*/
	RCC->CR |= RCC_CR_HSION;
	while(!(RCC->CR & RCC_CR_HSIRDY));
	RCC->CCIPR |= RCC_CCIPR_LPUART1SEL_1;
	
	LPUART1->BRR = (256 * fck) / BUAD;
	/*CR1*/
	LPUART1->CR1 = 0;
	LPUART1->CR1 |= USART_CR1_TE;  //se habilita la transmision
	
	LPUART1->CR1 |= USART_CR1_UE;
	return;
}

/*FUNCTION SEND BYTE LPUART1*/
void LPUART_sendByte(uint8_t ch){
	/*wait until tx buffer empty*/
	while(!(LPUART1->ISR & USART_ISR_TXE));
	LPUART1->TDR = ch;												//send byte
	return;
}
/*RECEIVE BYTE LPUART1*/ 
uint8_t LPUART_getByte(void){
	/*wait until rx buffer no empty*/
	while(!(LPUART1->ISR & USART_ISR_RXNE));
	return (uint8_t)LPUART1->RDR;
}
