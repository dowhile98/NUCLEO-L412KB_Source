

#ifndef __LPUART_H
#define __LPUART_H

/*INCLUDES*/
#include "stm32l4xx.h"                  // Device header

/**
  * @fn CONFIGURA EL LPUART1
	* @param frencuencia de funcionamiento del LPUART1
	* @param BUAD : la taza baudios deseada
	*/
void LPUART1_Config(uint32_t fck,uint32_t BUAD);
#endif /*__LPUART_H*/

