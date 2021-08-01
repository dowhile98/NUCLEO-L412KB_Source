#include "USART.h"

/*FUNCIONES PRIVADAS*/
/**
  * @brief configura los pines PA2 -> USART2_TX, USART2_RX (AF7)
	*/ 
static void USART2_Pins_Config(void){
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	GPIOA->MODER &=~ (GPIO_MODER_MODE3 | GPIO_MODER_MODE2);
	GPIOA->MODER |= GPIO_MODER_MODE3_1 | GPIO_MODER_MODE2_1;
	GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED3 | GPIO_OSPEEDR_OSPEED3;
	GPIOA->AFR[0] &=~ (GPIO_AFRL_AFRL3 | GPIO_AFRL_AFRL2);
	GPIOA->AFR[0] |= 0x7U<<GPIO_AFRL_AFSEL3_Pos;
	GPIOA->AFR[0] |= 0x7U<<GPIO_AFRL_AFSEL2_Pos;
}


/**
  * @brief configura los pines PA9 -> USART1_TX,PA10-> USART1_RX (AF7)
	*/ 
static void USART1_Pins_Config(void){
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	GPIOA->MODER &=~ (GPIO_MODER_MODE10 | GPIO_MODER_MODE9);
	GPIOA->MODER |= GPIO_MODER_MODE10_1 | GPIO_MODER_MODE9_1;
	GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED10 | GPIO_OSPEEDR_OSPEED9;
	GPIOA->AFR[1] &=~ (GPIO_AFRH_AFSEL10 | GPIO_AFRH_AFSEL9);
	GPIOA->AFR[1] |= 0x7U<<GPIO_AFRH_AFSEL10_Pos;
	GPIOA->AFR[1] |= 0x7U<<GPIO_AFRH_AFSEL9_Pos;
	return;
}

/**
  * @fn CONFIGURA EL USART en modo asincrono
	* @param USARTx: USART que se quiere configurar
	* @param PLCK: frecuencia del bus donde va conectado el USART
	* @param BUAD: Velocidad en baudios deseada
	* @param OVER8: Sobremuestreo entre 8 o 16
  */
void USART_Config(USART_TypeDef * USARTx, uint32_t PCLK,uint32_t BAUD, uint32_t OVER8){
	if(USARTx == USART1){
		//code here
		RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
		USART1_Pins_Config();
		
	}else if(USARTx == USART2){
		RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
		/*Pin config*/
		USART2_Pins_Config();
	}
	/*configurar parametros*/
	USARTx->CR1 = 0;
	USARTx->CR2 = 0;
	
	USARTx->CR1 |= USART_CR1_TE;
	USARTx->CR1 |= USART_CR1_RE;
	/*SET BAUDIOS*/
	if(OVER8 == USART_OVER8_0){
		USARTx->BRR = UART_BRR_SAMPLING16(PCLK,BAUD);
	}
	else{
		USARTx->BRR = UART_BRR_SAMPLING8(PCLK,BAUD);
		USARTx->CR1 |= USART_CR1_OVER8;
	}
	USARTx->CR1 |= USART_CR1_UE;		//ENABLE USART
}

/**
  * @fn funcion recibe un byte
	*/
uint8_t USART2_getc(void){
	while(!(USART2->SR & USART_SR_RXNE));
	return USART2->DR;
}


/**
  * @fn funcion envia un byte
	*/
void USART2_putc(uint8_t ch){
	while(!(USART2->SR & USART_SR_TXE));
	USART2->DR = ch;
	
}

/**
  * @fn funcion recibe un byte
	*/
uint8_t USART1_getc(void){
	while(!(USART1->SR & USART_SR_RXNE));
	return USART1->DR;
}


/**
  * @fn funcion envia un byte
	*/
void USART1_putc(uint8_t ch){
	while(!(USART1->SR & USART_SR_TXE));
	USART1->DR = ch;
	
}
