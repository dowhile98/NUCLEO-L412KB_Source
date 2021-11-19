#include "uart.h"

/*funciones privadas*/
static void UART1_GPIO_Config(void){
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
	/*PA9->UART1_TX, PA10->UART1_RX*/
	GPIOA->MODER &=~(GPIO_MODER_MODE9);
	GPIOA->MODER |= GPIO_MODER_MODE9_1;
	GPIOA->MODER &=~(GPIO_MODER_MODE10);
	GPIOA->MODER |= GPIO_MODER_MODE10_1;
	GPIOA->OSPEEDR 	= GPIO_OSPEEDR_OSPEED9 | GPIO_OSPEEDR_OSPEED10;				//very high speed
	GPIOA->AFR[1] &=~ GPIO_AFRH_AFRH1;
	GPIOA->AFR[1] &=~ GPIO_AFRH_AFRH2;
	GPIOA->AFR[1] |= GPIO_AFRH_AFSEL9_2 | GPIO_AFRH_AFSEL9_1 | GPIO_AFRH_AFSEL9_0;
	GPIOA->AFR[1] |= GPIO_AFRH_AFSEL10_2 | GPIO_AFRH_AFSEL10_1 | GPIO_AFRH_AFSEL10_0;
}
static void UART2_GPIO_Config(void){
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
	/*PA2->UART2_TX, PA15->UART2_RX*/
	GPIOA->MODER &=~(GPIO_MODER_MODE2);
	GPIOA->MODER |= GPIO_MODER_MODE2_1;
	GPIOA->MODER &=~(GPIO_MODER_MODE15);
	GPIOA->MODER |= GPIO_MODER_MODE15_1;
	GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED2 | GPIO_OSPEEDR_OSPEED15;				//very high speed
	GPIOA->AFR[0] &=~ GPIO_AFRL_AFRL2;
	GPIOA->AFR[1] &=~ GPIO_AFRH_AFRH7;
	GPIOA->AFR[0] |= GPIO_AFRL_AFSEL2_2 | GPIO_AFRL_AFSEL2_1 | GPIO_AFRL_AFSEL2_0;
	GPIOA->AFR[1] |= GPIO_AFRH_AFSEL15_1 | GPIO_AFRH_AFSEL15_0;
}


/*funcion que calcula el USARTDIV*/
static uint16_t computeUSARTDIV(USART_TypeDef *USARTx,uint32_t fck, uint32_t txRxBaud){
	uint16_t temp;
	if(USARTx->CR1 & USART_CR1_OVER8){ //oversampling 8
		temp = (2 * fck ) / txRxBaud;
		temp = (temp & 0xFFFFFFF0) | ((temp & 0xF)>>1);
	}
	else{
		temp = fck / txRxBaud;
	}
	return temp;
}


void UART1_Config(uint32_t fck, uint32_t txRxBaud){
	UART1_GPIO_Config();
	/*se habilita el reloj*/
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
	/*se configuran los parametros del uart1*/
	USART1->CR1 = 0;
	USART1->CR1 &=~ USART_CR1_M1;									//1 Start bit, 8 data bits, n stop bits
	USART1->CR1 &=~ USART_CR1_OVER8;							//Oversampling by 16
	USART1->CR1 |= USART_CR1_RXNEIE;							//rx interrupt
	USART1->CR1 |= USART_CR1_TE;
	USART1->CR1 |= USART_CR1_RE;
	USART1->BRR = computeUSARTDIV(USART1,fck,txRxBaud);
	USART1->CR1 |= USART_CR1_UE;
}

void UART2_Config(uint32_t fck, uint32_t txRxBaud){
	UART2_GPIO_Config();
	/*se habilita el reloj*/
	RCC->APB1ENR1 |= RCC_APB1ENR1_USART2EN;
	/*se configuran los parametros del uart2*/
	USART2->CR1 = 0;
	USART2->CR1 &=~ USART_CR1_M1;									//1 Start bit, 8 data bits, n stop bits
	USART2->CR1 &=~ USART_CR1_OVER8;							//Oversampling by 16
	USART2->CR1 |= USART_CR1_RXNEIE;							//rx interrupt
	USART2->CR1 |= USART_CR1_TE;
	USART2->CR1 |= USART_CR1_RE;
	USART2->BRR = computeUSARTDIV(USART2,fck,txRxBaud);
	USART2->CR1 |= USART_CR1_UE;
}


void USART1_putc(char ch){
	while(!(USART1->ISR & USART_ISR_TXE));
	USART1->TDR = ch;
}
char USART1_getc(void){
	while(!(USART1->ISR & USART_ISR_RXNE));
	return USART1->RDR;
}


void USART2_putc(char ch){
	while(!(USART2->ISR & USART_ISR_TXE));
	USART2->TDR = ch;
}
char USART2_getc(void){
	while(!(USART2->ISR & USART_ISR_RXNE));
	return USART2->RDR;
}

