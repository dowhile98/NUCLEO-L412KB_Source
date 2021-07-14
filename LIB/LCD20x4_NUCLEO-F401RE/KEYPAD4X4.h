#ifndef __KEYPAD4X4_H
#define __KEYPAD4X4_H

/*************************INCLUSION DE LIBRERIAS*******************************/
#include "stm32f4xx.h"
#include "delay.h"
/**********************DEFINICION MACROS***************************************/

/**
 * Cambiar estos macros a conveniencia
 * de acuerdo a los pines usados en su proyecto
 */
//pines para las columnas
#define R1_PORT			GPIOB
#define R1_PIN			2
#define R2_PORT			GPIOC
#define R2_PIN			8
#define R3_PORT			GPIOB
#define R3_PIN			9
#define R4_PORT			GPIOB
#define R4_PIN			5

//pines para las comlumnas

#define C1_PORT			GPIOC
#define C1_PIN			9
#define C2_PORT			GPIOB
#define C2_PIN			7
#define C3_PORT			GPIOC
#define C3_PIN			6
#define C4_PORT			GPIOC
#define C4_PIN			7

#define KEYPAD_RCC_EN()			RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN;


/*********************DEFINICION DE MACROS GENERICOS*********************************/
#define R1_SET		 	R1_PORT->ODR |= 1<<R1_PIN
#define R1_RESET		R1_PORT->ODR &=~(1U<<R1_PIN)
#define R2_SET		 	R2_PORT->ODR |= 1<<R2_PIN
#define R2_RESET		R2_PORT->ODR &=~(1U<<R2_PIN)
#define R3_SET		 	R3_PORT->ODR |= 1<<R3_PIN
#define R3_RESET		R3_PORT->ODR &=~(1U<<R3_PIN)
#define R4_SET		 	R4_PORT->ODR |= 1<<R4_PIN
#define R4_RESET		R4_PORT->ODR &=~(1U<<R4_PIN)

#define C1_BIT			((C1_PORT->IDR>>C1_PIN) & 0x01)
#define C2_BIT			((C2_PORT->IDR>>C2_PIN) & 0x01)
#define C3_BIT			((C3_PORT->IDR>>C3_PIN)	& 0x01)
#define C4_BIT			((C4_PORT->IDR>>C4_PIN)	& 0x01)


#define KEYPAD_EMPTY    0			//si no se lee nada

/*************************DEFINICION DE PROTOTIPO DE FUNCIONES*****************/
void keypad_init(void);
uint8_t keypad_read(void);


#endif /* __KEYPAD4X4_H */
