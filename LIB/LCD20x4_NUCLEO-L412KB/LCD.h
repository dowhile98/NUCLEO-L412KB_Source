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
#include "stm32l4xx.h"                  // Device header (cambiar de acuerdo al mcu usado
#include <stdio.h>

/**********************************************************************************
*												DEFINICION DE MACROS
**********************************************************************************/
/*incluir estas funciones de acuerdo a lo definido*/
extern void delay_ms(uint32_t delay);

#define LCD_Delay_ms		delay_ms


/*   Definimos los pines donde conectaremos la pantalla LCD   */
//--------------------------------------------------------------
/*							CONEXIONES
 *	RS 	-> A7(PA2)
 *	E		-> A6(PA7)
 *	D4 	-> D2(PA12)
 *	D5	-> D3(PB0)
 * 	D6	-> D4(PB7)
 *	D7	-> D5(PB6)
 */
#define LCD_RS_PORT		GPIOA  	 				// Puerto Pin RS
#define LCD_RS_PIN 		12	  						// Pin RS_LCD
#define LCD_EN_PORT		GPIOB   				// Puerto Pin EN
#define LCD_EN_PIN 		0								// Pin EN_LCD
#define LCD_D4_PORT		GPIOA
#define LCD_D4_PIN 		6 							// Pin DATA4_LCD
#define LCD_D5_PORT		GPIOA
#define LCD_D5_PIN 		5  							// Pin DATA5_LCD
#define LCD_D6_PORT		GPIOA
#define LCD_D6_PIN		4  							// Pin DATA6_LCD
#define LCD_D7_PORT		GPIOA
#define LCD_D7_PIN 		3  							// Pin DATA7_LCD

/*modificar de acuerdo a los puertos usados*/
#define LCD_RCC_ENABLE()	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN | RCC_AHB2ENR_GPIOAEN 

/* Commands*/
#define LCD_CLEARDISPLAY        0x01
#define LCD_RETURNHOME          0x02
#define LCD_ENTRYMODESET        0x04
#define LCD_DISPLAYCONTROL      0x08
#define LCD_CURSORSHIFT         0x10
#define LCD_FUNCTIONSET         0x20
#define LCD_SETCGRAMADDR        0x40
#define LCD_SETDDRAMADDR        0x80



/* Flags for display entry mode */
#define LCD_ENTRYRIGHT          0x00
#define LCD_ENTRYLEFT           0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

/* Flags for display on/off control */
#define LCD_DISPLAYON           0x04
#define LCD_CURSORON            0x02
#define LCD_BLINKON             0x01


/* Flags for display/cursor shift */
#define LCD_DISPLAYMOVE         0x08
#define LCD_CURSORMOVE          0x00
#define LCD_MOVERIGHT           0x04
#define LCD_MOVELEFT            0x00

/* Flags for function set */
#define LCD_8BITMODE            0x10
#define LCD_4BITMODE            0x00
#define LCD_2LINE               0x08
#define LCD_1LINE               0x00
#define LCD_5x10DOTS            0x04
#define LCD_5x8DOTS             0x00

/***********************************************************************************
 * 				PROTOTIPO DE FUNCIOENS PARA EL MANEJO LA LCD
 **********************************************************************************/
/**
 * @brief INICIALIZA LA PANTALLA LCD
 * @param :none
 * @return : none
 */
void LCD_Init(void);

/**
 * @brief ESTA FUNCION ENVIA UN BYTE DE DATOS A LA LCD
 */
void LCD_data(char data);
/**
 * @brief ESTA FUNCION ENVIA UN COMANDO A LA LCD
 */
void LCD_command(unsigned char command);

/**
 * @brief ESTABLECE LA POSICION DEL CURSOR
 */
void LCD_Set_Cursor(uint8_t x, uint8_t y);

/**
 * @brief ENVIA UNA CADENA A LA PANTALLA
 */
void LCD_printStr(char *buffer);



/**
 * @brief  Turn display on
 * @param  None
 * @retval None
 */
void LCD_DisplayOn(void);

/**
 * @brief  Turn display off
 * @param  None
 * @retval None
 */
void LCD_DisplayOff(void);

/**
 * @brief  Clears entire LCD
 * @param  None
 * @retval None
 */
void LCD_Clear(void);

/**
 * @brief  Puts string on lcd
 * @param  x location
 * @param  y location
 * @param  *str: pointer to string to display
 * @retval None
 */
void LCD_Puts(uint8_t x, uint8_t y, char* str);

/**
 * @brief  Enables cursor blink
 * @param  None
 * @retval None
 */
void LCD_BlinkOn(void);

/**
 * @brief  Disables cursor blink
 * @param  None
 * @retval None
 */
void LCD_BlinkOff(void);

/**
 * @brief  Shows cursor
 * @param  None
 * @retval None
 */
void LCD_CursorOn(void);

/**
 * @brief  Hides cursor
 * @param  None
 * @retval None
 */
void LCD_CursorOff(void);

/**
 * @brief  Scrolls display to the left
 * @param  None
 * @retval None
 */
void LCD_ScrollLeft(void);

/**
 * @brief  Scrolls display to the right
 * @param  None
 * @retval None
 */
void LCD_ScrollRight(void);

/**
 * @brief  Creates custom character
 * @param  location: Location where to save character on LCD. LCD supports up to 8 custom characters, so locations are 0 - 7
 * @param *data: Pointer to 8-bytes of data for one character
 * @retval None
 */
void LCD_CreateChar(uint8_t location, uint8_t* data);

/**
 * @brief  Puts custom created character on LCD
 * @param  location: Location on LCD where character is stored, 0 - 7
 * @retval None
 */
void LCD_PutCustom(uint8_t x, uint8_t y, uint8_t location);


#endif /* LCD16X2_INC_LCD16X2_H_ */

