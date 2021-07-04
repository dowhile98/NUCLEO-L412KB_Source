#include "delay.h"

#ifndef USE_SYSTICK
/**
 * @brief RETARDO EN microsegundos
 */
void delay_us(uint32_t delay){
	uint32_t i;
	TIM_RCC_EN();														//enable clock
	TIM_DELAY->CR1 = 0;
	TIM_DELAY->PSC = 0;
	TIM_DELAY->ARR = 16-1;									//definir de acuerdo a la frecuencia trabajada
	TIM_DELAY->CNT = 0;
	TIM_DELAY->CR1 |= TIM_CR1_CEN;
	for(i = 0;i<delay;i++){
		while(!(TIM_DELAY->SR & TIM_SR_UIF));
	}
	TIM_DELAY->CR1 &=~ TIM_CR1_CEN;
}
/**
 * @brief RETARDO EN milisegundos
 */
void delay_ms(uint32_t delay){
	uint32_t i;
	for(i = 0;i<delay;i++){
		delay_us(1000);
	}
}

#else
/**
 * @brief RETARDO EN microsegundos
 */
void delay_us(uint32_t delay){
	uint32_t i;
	SysTick->CTRL = 0;
	SysTick->LOAD = 16 - 1;
	SysTick->VAL = 0;
	SysTick->CTRL |= 1<<2 | 1<<0;
	for( i = 0;i<delay;i++){
		while(!(SysTick->CTRL & 1<<16));
	}
	SysTick->CTRL = 0;
}
/**
 * @brief RETARDO EN milisegundos
 */
void delay_ms(uint32_t delay){
	uint32_t i;
	for(i = 0;i<delay;i++){
		delay_us(1000-1);
	}
}

#endif /*USE_SYSTICK*/
