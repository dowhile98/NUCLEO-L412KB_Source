#include "USART.h"

/*************FUNCIONES PRIVADAS********************************/
static void USART1_Pins_Config(void){
	/*enable clock*/
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	/*USART1_TX -> PA9
	* USART1_RX -> PA10*/
	GPIOA->CRH &=~ (GPIO_CRH_CNF10 | GPIO_CRH_CNF9 | GPIO_CRH_MODE10 | GPIO_CRH_MODE9);
	GPIOA->CRH |= GPIO_CRH_CNF9_1 | GPIO_CRH_MODE9;		//PA9->AF, speed 50MHz
	GPIOA->CRH |= GPIO_CRH_CNF10_0 ;	//floating input
}



/**
 * @brief CONFIGURA EL USART1
 * @param fck: La freq. para generacion de baudios
 * @param OVER8: valor de oversampling deseado
 * @param txRxBaud: La taza de baudios deseada
 * @return nada
 */
void USART1_Config(uint32_t pclk,uint32_t txRxBaud){
	/*1. Se configura los pines*/
	USART1_Pins_Config();
	/*enable clock*/
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
	/*2. se configuran los parametros del USART1*/
	USART1->CR1 = 0; 							//8-bit data
	USART1->BRR = UART_BRR_SAMPLING16(pclk,txRxBaud);
	USART1->CR1 |= USART_CR1_TE;
	USART1->CR1 |= USART_CR1_RE;
	USART1->CR2 = 0;							//1-bit de stop
	/*se configura la interrupcion si en caso es necesario*/
	USART1->CR1 |= USART_CR1_RXNEIE;
	NVIC_SetPriority(USART1_IRQn,3);
	NVIC_EnableIRQ(USART1_IRQn);
	/*SE HABILITA EL USART1*/
	USART1->CR1 |= USART_CR1_UE;
}

/*Tx byte UART1*/
int USART1_putc(char ch){
	while(!(USART1->SR & USART_SR_TXE));
	USART1->DR = ch;
	return ch;
}
/*Rx byte UART1*/
char USART1_getc(void){
	while(!(USART1->SR & USART_SR_RXNE));
	return USART1->DR;
}

