/**
 * @autor QUINO B. JEFFRY
 * @version v.1.0
 */
 
#ifndef __USART_H
#define __USART_H

/*includes*/
#include "stm32f10x.h"                  // Device header



/*********DEFINICION DE MACROS***********/

/*estos macros son para configurar la velocidad en baudios del USART*/
#define UART_DIV_SAMPLING16(_PCLK_, _BAUD_)            (((_PCLK_)*25U)/(4U*(_BAUD_)))
#define UART_DIVMANT_SAMPLING16(_PCLK_, _BAUD_)        (UART_DIV_SAMPLING16((_PCLK_), (_BAUD_))/100U)
#define UART_DIVFRAQ_SAMPLING16(_PCLK_, _BAUD_)        ((((UART_DIV_SAMPLING16((_PCLK_), (_BAUD_)) - (UART_DIVMANT_SAMPLING16((_PCLK_), (_BAUD_)) * 100U)) * 16U) + 50U) / 100U)

/* UART BRR = mantissa + overflow + fraction
            = (UART DIVMANT << 4) + (UART DIVFRAQ & 0xF0) + (UART DIVFRAQ & 0x0FU) */
#define UART_BRR_SAMPLING16(_PCLK_, _BAUD_)            (((UART_DIVMANT_SAMPLING16((_PCLK_), (_BAUD_)) << 4U) + \
                                                        (UART_DIVFRAQ_SAMPLING16((_PCLK_), (_BAUD_)) & 0xF0U)) + \
                                                        (UART_DIVFRAQ_SAMPLING16((_PCLK_), (_BAUD_)) & 0x0FU))

/*********PROTOTIPO DE FUNCIONES*********/
/**
 * @brief CONFIGURA EL USART1
 * @param fck: La freq. para generacion de baudios
 * @param OVER8: valor de oversampling deseado
 * @param txRxBaud: La taza de baudios deseada
 * @return nada
 */
void USART1_Config(uint32_t pclk,uint32_t txRxBaud);


/**
 * @brief Envia un byte por el usart1
 * @param ch: byte a enviar
 */
int USART1_putc(char ch);
/**
 * @brief Lee un byte por el usart1
 * @return retorna el byte recibido
 */
char USART1_getc(void);

#endif /*__USART_H*/

