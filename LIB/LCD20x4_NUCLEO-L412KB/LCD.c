#include "LCD.h"

/*VARIABLES PRIVADAS*/



/********FUNCIONES PRIVADAS******************/
/**
@brief CONFIGURA LOS FINES DE LCD
@param :none
@returns: none
@verbatim
 * esta funcion inicializa los pines elegidos para la conexion con la lcd
 */
static void LCD_InitPinout(void){
	LCD_RCC_ENABLE();
	//D4
	LCD_D4_PORT->MODER &=~(3U<<2*LCD_D4_PIN);	 
	LCD_D4_PORT->MODER |= (1<<2*LCD_D4_PIN);		//output
	LCD_D4_PORT->OTYPER &=~ (1U<<LCD_D4_PIN);		//push-pull
	LCD_D4_PORT->OSPEEDR |=(3<<2*LCD_D4_PIN);		//high speed
	//D5
	LCD_D5_PORT->MODER &=~(3U<<2*LCD_D5_PIN);
	LCD_D5_PORT->MODER |= (1<<2*LCD_D5_PIN);
	LCD_D5_PORT->OTYPER &=~ (1U<<LCD_D5_PIN);		//push-pull
	LCD_D5_PORT->OSPEEDR |=(3<<2*LCD_D5_PIN);		//high speed
	//D6
	LCD_D6_PORT->MODER &=~(3U<<2*LCD_D6_PIN);
	LCD_D6_PORT->MODER |= (1<<2*LCD_D6_PIN);
	LCD_D6_PORT->OTYPER &=~ (1U<<LCD_D6_PIN);		//push-pull
	LCD_D6_PORT->OSPEEDR |=(3<<2*LCD_D6_PIN);
	//D7
	LCD_D7_PORT->MODER &=~(3U<<2*LCD_D7_PIN);
	LCD_D7_PORT->MODER |= (1<<2*LCD_D7_PIN);
	LCD_D7_PORT->OTYPER &=~ (1U<<LCD_D7_PIN);		//push-pull
	LCD_D7_PORT->OSPEEDR |=(3<<2*LCD_D7_PIN);
	//se inicializa el EN_PORT
	LCD_EN_PORT->MODER &=~(3U<<2*LCD_EN_PIN);
	LCD_EN_PORT->MODER |=(1<<2*LCD_EN_PIN);
	LCD_EN_PORT->OTYPER &=~ (1U<<LCD_EN_PIN);		//push-pull
	LCD_EN_PORT->OSPEEDR |= (3<<2*LCD_EN_PIN);			//medium speed
	//se inicializa el RS_PORT
	LCD_RS_PORT->MODER &=~(3U<<2*LCD_RS_PIN);
	LCD_RS_PORT->MODER |=(1<<2*LCD_RS_PIN);
	LCD_RS_PORT->OTYPER &=~ (1U<<LCD_RS_PIN);		//push-pull
	LCD_RS_PORT->OSPEEDR |=(3<<2*LCD_RS_PIN);
}

/**
 * @brief EST FUNCION NOS SIRVE PARA ENVIAR UN NIBLE A LA PANTALLA
 */
void LCD_nibble_write(char data, unsigned char control){
	/*RESET VALUE*/
	LCD_D4_PORT->BSRR |= 1U<<(16 + LCD_D4_PIN);
	LCD_D5_PORT->BSRR |= 1U<<(16 + LCD_D5_PIN);
	LCD_D6_PORT->BSRR |= 1U<<(16 + LCD_D6_PIN);
	LCD_D7_PORT->BSRR |= 1U<<(16 + LCD_D7_PIN);
	/*se establecen los valores*/
	//BIT 0
	if(data & 0x1)
		LCD_D4_PORT->BSRR |= 1U<<LCD_D4_PIN;
	//BIT 1
	if(data & 0x2)
		LCD_D5_PORT->BSRR |= 1U<<LCD_D5_PIN;
	//BIT 2
	if(data & 0x4)
		LCD_D6_PORT->BSRR |= 1U<<LCD_D6_PIN;
	//BIT 3
	if(data & 0x8)
		LCD_D7_PORT->BSRR |= 1U<<LCD_D7_PIN;
	/*si es dato o comando*/
	if(control & 1)
		LCD_RS_PORT->BSRR |= 1U<<LCD_RS_PIN;
	else
		LCD_RS_PORT->BSRR |= 1U<<(16 + LCD_RS_PIN);
	/*se genera un pulso*/
	LCD_EN_PORT->BSRR |= 1U<<LCD_EN_PIN;
	LCD_Delay_ms(0);
	LCD_EN_PORT->BSRR |= 1U<<(16 + LCD_EN_PIN);
	
	return;
}


/**
 * @brief ESTA FUNCION ENVIA UN BYTE DE DATOS A LA LCD
 */
void LCD_data(char data){
	LCD_nibble_write((data>>4) & 0x0F,1);
	LCD_nibble_write(data & 0x0F,1);
	LCD_Delay_ms(1);
	return;
}
/**
 * @brief ESTA FUNCION ENVIA UN COMANDO A LA LCD
 */
void LCD_command(unsigned char command){
	LCD_nibble_write((command>>4) & 0x0F,0);
	LCD_nibble_write(command & 0x0F,0);
	if(command < 4)
		LCD_Delay_ms(2);
	else
		LCD_Delay_ms(1);
	return;
}


/**
 * @brief INICIALIZA LA PANTALLA LCD
 * @param :none
 * @return : none
 */
void LCD_Init(void){
	LCD_InitPinout();
	
	LCD_Delay_ms(50);
	LCD_nibble_write(0x30, 0);
  LCD_Delay_ms(5);
  LCD_nibble_write(0x30, 0);
  LCD_Delay_ms(1);
  LCD_nibble_write(0x30, 0);
  LCD_Delay_ms(1);

  LCD_nibble_write(0x20, 0);  // set 4-bit data mode
  LCD_Delay_ms(1);
  LCD_command(0x28);          // 4-bit data, 2-line, 5x7 font
  LCD_command(0x06);          // move cursor right 
  LCD_command(0x01);          // clear screen, move cursor to home
	LCD_command(0x0F);          // turn on display, cursor blinking 
	
}


/**
 * @brief ESTABLECE LA POSICION DEL CURSOR
 */
void LCD_Set_Cursor(uint8_t x, uint8_t y){
	uint8_t addr = 0;
	switch(x){
		case 0: addr = 0x80; break; //Starting address of 1st line
    case 1: addr = 0xC0; break; //Starting address of 2nd line
    case 2: addr = 0x94; break; //Starting address of 3rd line
    case 3: addr = 0xD4; break; //Starting address of 4th line
    default: ; 
	}
	addr += y;
	LCD_command(addr);
	return;
}

/**
 * @brief ENVIA UNA CADENA A LA PANTALLA
 */
void LCD_printStr(char *buffer) {
    while (*buffer) // Write data to LCD up to null
    {
    	LCD_data(*buffer); // Write character to LCD
        buffer++; // Increment buffer
    }
    return;
}



