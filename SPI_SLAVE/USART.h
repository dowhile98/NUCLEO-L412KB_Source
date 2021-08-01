/**
  * @autor QUINO B. Jeffry
	* @version V 1.0
	*/
	
	
#ifndef __USART_H
#define __USART_H

/*******************INCLUSIONES*****************/
#include "stm32f4xx.h"                  // Device header


/**************DEFINCION DE MACROS**************/

#define UART_DIV_SAMPLING16(_PCLK_, _BAUD_)            ((uint32_t)((((uint64_t)(_PCLK_))*25U)/(4U*((uint64_t)(_BAUD_)))))
#define UART_DIVMANT_SAMPLING16(_PCLK_, _BAUD_)        (UART_DIV_SAMPLING16((_PCLK_), (_BAUD_))/100U)
#define UART_DIVFRAQ_SAMPLING16(_PCLK_, _BAUD_)        ((((UART_DIV_SAMPLING16((_PCLK_), (_BAUD_)) - (UART_DIVMANT_SAMPLING16((_PCLK_), (_BAUD_)) * 100U)) * 16U) + 50U) / 100U)
/* UART BRR = mantissa + overflow + fraction
            = (UART DIVMANT << 4) + (UART DIVFRAQ & 0xF0) + (UART DIVFRAQ & 0x0FU) */
#define UART_BRR_SAMPLING16(_PCLK_, _BAUD_)            ((UART_DIVMANT_SAMPLING16((_PCLK_), (_BAUD_)) << 4U) + \
                                                        (UART_DIVFRAQ_SAMPLING16((_PCLK_), (_BAUD_)) & 0xF0U) + \
                                                        (UART_DIVFRAQ_SAMPLING16((_PCLK_), (_BAUD_)) & 0x0FU))


#define UART_DIV_SAMPLING8(_PCLK_, _BAUD_)             ((uint32_t)((((uint64_t)(_PCLK_))*25U)/(2U*((uint64_t)(_BAUD_)))))
#define UART_DIVMANT_SAMPLING8(_PCLK_, _BAUD_)         (UART_DIV_SAMPLING8((_PCLK_), (_BAUD_))/100U)
#define UART_DIVFRAQ_SAMPLING8(_PCLK_, _BAUD_)         ((((UART_DIV_SAMPLING8((_PCLK_), (_BAUD_)) - (UART_DIVMANT_SAMPLING8((_PCLK_), (_BAUD_)) * 100U)) * 8U) + 50U) / 100U)
/* UART BRR = mantissa + overflow + fraction
            = (UART DIVMANT << 4) + ((UART DIVFRAQ & 0xF8) << 1) + (UART DIVFRAQ & 0x07U) */
#define UART_BRR_SAMPLING8(_PCLK_, _BAUD_)             ((UART_DIVMANT_SAMPLING8((_PCLK_), (_BAUD_)) << 4U) + \
                                                        ((UART_DIVFRAQ_SAMPLING8((_PCLK_), (_BAUD_)) & 0xF8U) << 1U) + \
                                                        (UART_DIVFRAQ_SAMPLING8((_PCLK_), (_BAUD_)) & 0x07U))


/****OVER 8************************************/
#define USART_OVER8_0								0
#define USART_OVER8_1 							USART_CR1_OVER8


/*PROTOTIPO DE FUNCIONES*/

/**
  * @fn CONFIGURA EL USART en modo asincrono
	* @param USARTx: USART que se quiere configurar
	* @param PLCK: frecuencia del bus donde va conectado el USART
	* @param BUAD: Velocidad en baudios deseada
	* @param OVER8: Sobremuestreo entre 8 o 16
  */
void USART_Config(USART_TypeDef * USARTx, uint32_t PCLK,uint32_t BAUD, uint32_t OVER8);
	

/**
  * @fn funcion recibe un byte
	*/
uint8_t USART2_getc(void);


/**
  * @fn funcion envia un byte
	*/
void USART2_putc(uint8_t ch);


/**
  * @fn funcion recibe un byte
	*/
uint8_t USART1_getc(void);


/**
  * @fn funcion envia un byte
	*/
void USART1_putc(uint8_t ch);



#endif /*__USART_H*/

