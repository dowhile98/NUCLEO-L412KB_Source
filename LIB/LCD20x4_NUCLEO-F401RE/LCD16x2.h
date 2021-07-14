/*
 * LCD16x2.h
 *
 *  Created on: Sep 8, 2020
 *      Author: QUINO B. JEFFRY
 */
#ifndef LCD16X2_INC_LCD16X2_H_
#define LCD16X2_INC_LCD16X2_H_

/**********************************************************************************
*										INCLUSION DE LIBRERIAS NECESARIAS
**********************************************************************************/
#include "stm32f4xx.h"                  // Device header (cambiar de acuerdo al mcu usado
#include <stdio.h>

/**********************************************************************************
*												DEFINICION DE MACROS
**********************************************************************************/
/*incluir estas funciones de acuerdo a lo definido*/
extern void delay_us(uint32_t delay);
extern void delay_ms(uint32_t delay);

#define lcd_delay_us		delay_us
#define lcd_delay_ms		delay_ms
/*   Definimos los pines donde conectaremos la pantalla LCD   */
//--------------------------------------------------------------

#define LCD_RS_PORT		GPIOB  	 				// Puerto Pin RS
#define LCD_EN_PORT		GPIOA   				// Puerto Pin EN
#define LCD_RS_PIN 		8	  						// Pin RS_LCD
#define LCD_EN_PIN 		0								// Pin EN_LCD
#define LCD_D4_PORT		GPIOA
#define LCD_D4_PIN 		10 							// Pin DATA4_LCD
#define LCD_D5_PORT		GPIOB
#define LCD_D5_PIN 		0  							// Pin DATA5_LCD
#define LCD_D6_PORT		GPIOC
#define LCD_D6_PIN		1  							// Pin DATA6_LCD
#define LCD_D7_PORT		GPIOC
#define LCD_D7_PIN 		3  							// Pin DATA7_LCD

/*modificar de acuerdo a los puertos usados*/
#define LCD_RCC_ENABLE()	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN 


// Definimos que nombres para activar los pines a nivel 'High' y 'Low'
#define LCD_EN_HI()			LCD_EN_PORT->ODR |=1<<LCD_EN_PIN
#define LCD_EN_LO()			LCD_EN_PORT->ODR &=~(1U<<LCD_EN_PIN)
#define LCD_RS_HI() 		LCD_RS_PORT->ODR |=1<<LCD_RS_PIN
#define LCD_RS_LO() 		LCD_RS_PORT->ODR &=~(1U<<LCD_RS_PIN)

#define LCD_D4_HI() 		LCD_D4_PORT->ODR |=1<<LCD_D4_PIN
#define LCD_D4_LO() 		LCD_D4_PORT->ODR &=~(1U<<LCD_D4_PIN)
#define LCD_D5_HI() 		LCD_D5_PORT->ODR |=1<<LCD_D5_PIN
#define LCD_D5_LO() 		LCD_D5_PORT->ODR &=~(1U<<LCD_D5_PIN)
#define LCD_D6_HI() 		LCD_D6_PORT->ODR |=1<<LCD_D6_PIN
#define LCD_D6_LO() 		LCD_D6_PORT->ODR &=~(1U<<LCD_D6_PIN)
#define LCD_D7_HI() 		LCD_D7_PORT->ODR |=1<<LCD_D7_PIN
#define LCD_D7_LO()			LCD_D7_PORT->ODR &=~(1U<<LCD_D7_PIN)

/*   Definimos los nombres de los comandos para el LCD                  */
/* LINES*/
#define DDRAM_LINE1   0b10000000  /* 4-bit Interface               */
#define DDRAM_LINE2   0b11000000  /* 4-bit Interface               */
#define CGRAM_ADDRESS 0b01000000  /* 4-bit Interface               */


#define LCD_cursor_home() 		LCD_Write_Cmd(0x02)		// Establecer el cursor a 'Home'
#define LCD_clear()						LCD_Write_Cmd(0x01)		//clear LCD
#define LCD_display_on() 			LCD_Write_Cmd(0x0E)		// Pantalla LCD Activa
#define LCD_display_off() 		LCD_Write_Cmd(0x08)		// Pantalla LCD Inactiva
#define LCD_cursor_blink() 		LCD_Write_Cmd(0x0F)		// Cursor intermitente
#define LCD_cursor_on() 			LCD_Write_Cmd(0x0E)	  	// Cursor visible activo
#define LCD_cursor_off() 			LCD_Write_Cmd(0x0C)		// Cursor inactivo
#define LCD_cursor_left() 		LCD_Write_Cmd(0x10)		// Movimiento hacia la izquierda del cursor
#define LCD_cursor_right() 		LCD_Write_Cmd(0x14)		// Movimiento hacia la derecha del cursor
#define LCD_display_sleft() 	LCD_Write_Cmd(0x18)		// Movimiento a la izquierda de la pantalla
#define LCD_display_sright() 	LCD_Write_Cmd(0x1C)		// Movimiento a la derecha de la pantalla


/***********************************************************************************
 * 				PROTOTIPO DE FUNCIOENS PARA EL MANEJO LA LCD
 **********************************************************************************/
/**
@brief CONFIGURA LOS FINES DE LCD
@param :none
@returns: none
@verbatim
 * esta funcion inicializa los pines elegidos para la conexion con la lcd
 */
void LCD_InitPinout(void);
/**
 * @brief INICIALIZA LA PANTALLA LCD
 * @param :none
 * @return : none
 */
void LCD_Init(void);
/**
 * @brief EST FUNCION NOS SIRVE PARA ENVIAR UN NIBLE A LA PANTALLA
 */
void LCD_Out_Data4(unsigned char val);
/**
 * @brief ESTA FUNCION ENVIA UN BYTE DE DATOS A LA LCD
 */
void LCD_Write_Byte(unsigned char val);
/**
 * @brief ESTA FUNCION ENVIA UN COMANDO A LA LCD
 */
void LCD_Write_Cmd(unsigned char val);
/**
 * @brief ESTA FUNCION ENVIA UN CARACTER A LA LCD
 */
void LCD_printChar(unsigned char c);
/**
 * @brief ESTABLECE LA POSICION DEL CURSOR
 */
void LCD_Set_Cursor(uint8_t x, uint8_t y);
/**
 * @brief ENVIA UNA CADENA A LA PANTALLA
 */
void LCD_printStr(char *buffer);
/**
 * /@briefENVIA UN NUMERO A LA LCD
 */
void LCD_printInt(int number);

void LCD_printFloat(double number);

void LCD_pulse_EN(void);

//ESTA FUNCIONES ESTAN EN DESARROLO
void LCD_BarGraphic (int value, int size);
void LCD_BarGraphicXY (int pos_x, int pos_y, int value);


#endif /* LCD16X2_INC_LCD16X2_H_ */

