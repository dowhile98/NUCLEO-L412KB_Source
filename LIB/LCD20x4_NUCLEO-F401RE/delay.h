#ifndef __DELAY_H
#define __DELAY_H
/*******INCLUSION DE LIBRERIAS NECESARIAS ***********/
#include "stm32f4xx.h"                  // Device header (cambiar de acuerdo al mcu)


#define USE_SYSTICK

#ifndef USE_SYSTICK
/*CAMBIAR DE ACUERDO AL TIMER USADO*/
#define TIM_DELAY 		TIM10 							//CAMBIAR DE ACUERDO AL TIMER USADO
#define TIM_RCC_EN()	RCC->APB2ENR |= RCC_APB2ENR_TIM10EN
#endif /*USE_SYSTICK*/


/**
 * @brief RETARDO EN MICROSEGUDOS
 * @param :delay
 * @returns: none
 */
void delay_us(uint32_t delay);
/**
 * @brief RETARDO EN MILISEGUNDOS
 * @param :delay
 * @returns: none
 */
void delay_ms(uint32_t delay);

#endif /*__DELAY_H*/


