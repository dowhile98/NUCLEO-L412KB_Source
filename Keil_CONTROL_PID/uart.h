#ifndef __USART_H
#define __USART_H

/*includes*/
#include "stm32l4xx.h"                  // Device header

/*definicion de macros*/


/*prototipo de funciones*/
void UART1_Config(uint32_t fck, uint32_t txRxBaud);
void UART2_Config(uint32_t fck, uint32_t txRxBaud);

void USART1_putc(char ch);
char USART1_getc(void);


void USART2_putc(char ch);
char USART2_getc(void);

#endif /*__USART_H*/
