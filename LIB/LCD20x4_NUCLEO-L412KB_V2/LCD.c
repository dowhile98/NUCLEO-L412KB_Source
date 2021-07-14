#include "LCD.h"

/*VARIABLES PRIVADAS*/
/* Private HD44780 structure */
typedef struct {
	uint8_t DisplayControl;
	uint8_t DisplayFunction;
	uint8_t DisplayMode;
	uint8_t Rows;
	uint8_t Cols;
	uint8_t currentX;
	uint8_t currentY;
} LCD_Options_t;

/* Private variable */
static LCD_Options_t LCD_Opts;



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
	/*RESET PINS*/
	LCD_D4_PORT->BSRR |= 1U<<(16 + LCD_D4_PIN);
	LCD_D5_PORT->BSRR |= 1U<<(16 + LCD_D5_PIN);
	LCD_D6_PORT->BSRR |= 1U<<(16 + LCD_D6_PIN);
	LCD_D7_PORT->BSRR |= 1U<<(16 + LCD_D7_PIN);
	LCD_RS_PORT->BSRR |= 1U<<(16 + LCD_RS_PIN);
	LCD_EN_PORT->BSRR |= 1U<<(16 + LCD_EN_PIN);
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
	LCD_Delay_ms(1);
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
		LCD_Delay_ms(3);
	else
		LCD_Delay_ms(2);
	return;
}


/**
 * @brief INICIALIZA LA PANTALLA LCD
 * @param :none
 * @return : none
 */
void LCD_Init(uint8_t cols,uint8_t rows){
	/* Init pinout */

	LCD_InitPinout();
	
	
	/* At least 30ms */
	LCD_Delay_ms(500);
	
	/* Set LCD width and height */
	LCD_Opts.Rows = rows - 1;
	LCD_Opts.Cols = cols;
	/* Set cursor pointer to beginning for LCD */
	LCD_Opts.currentX = 0;
	LCD_Opts.currentY = 0;
	
	LCD_Opts.DisplayFunction = LCD_4BITMODE | LCD_5x8DOTS | LCD_1LINE;
	if(rows>1)
		LCD_Opts.DisplayFunction |= LCD_2LINE;
	
	LCD_nibble_write(0x30, 0);
  LCD_Delay_ms(5);
  LCD_nibble_write(0x30, 0);
  LCD_Delay_ms(1);
  LCD_nibble_write(0x30, 0);
  LCD_Delay_ms(1);

  LCD_nibble_write(0x20, 0);  // set 4-bit data mode
  LCD_Delay_ms(1);
	
	LCD_command(LCD_FUNCTIONSET | LCD_Opts.DisplayFunction);
	LCD_Opts.DisplayControl = LCD_DISPLAYON;
	
	/* Turn the display on with no cursor or blinking default */
//	LCD_command(0x28);          // 4-bit data, 2-line, 5x7 font
//  LCD_command(0x06);          // move cursor right 
//  LCD_command(0x01);          // clear screen, move cursor to home
//	LCD_command(0x0F);          // turn on display, cursor blinking 
	
	/* Clear lcd */
	LCD_Clear();
	LCD_Delay_ms(5);
	/* Default font directions */
	LCD_Opts.DisplayMode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
	LCD_command(LCD_ENTRYMODESET | LCD_Opts.DisplayMode);
	
}


/**
 * @brief ESTABLECE LA POSICION DEL CURSOR
 */
void LCD_Set_Cursor(uint8_t x, uint8_t y){

	uint8_t row_offsets[] = {0x00, 0x40, 0x14, 0x54};
	if(x > LCD_Opts.Rows)
		x = 0;
	
	/* Set current column and row */
	LCD_Opts.currentX = x;
	LCD_Opts.currentY = y;

	LCD_command(LCD_SETDDRAMADDR | (y + row_offsets[x]));
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

void LCD_Clear(void) {
	LCD_command(LCD_CLEARDISPLAY);
	LCD_Delay_ms(3);
}

void LCD_DisplayOn(void) {
	LCD_Opts.DisplayControl |= LCD_DISPLAYON;
	LCD_command(LCD_DISPLAYCONTROL | LCD_Opts.DisplayControl);
}

void LCD_DisplayOff(void) {
	LCD_Opts.DisplayControl &= ~LCD_DISPLAYON;
	LCD_command(LCD_DISPLAYCONTROL | LCD_Opts.DisplayControl);
}

void LCD_BlinkOn(void) {
	LCD_Opts.DisplayControl |= LCD_BLINKON;
	LCD_command(LCD_DISPLAYCONTROL | LCD_Opts.DisplayControl);
}

void LCD_BlinkOff(void) {
	LCD_Opts.DisplayControl &= ~LCD_BLINKON;
	LCD_command(LCD_DISPLAYCONTROL | LCD_Opts.DisplayControl);
}
void LCD_CursorOn(void) {
	LCD_Opts.DisplayControl |= LCD_CURSORON;
	LCD_command(LCD_DISPLAYCONTROL | LCD_Opts.DisplayControl);
}

void LCD_CursorOff(void) {
	LCD_Opts.DisplayControl &= ~LCD_CURSORON;
	LCD_command(LCD_DISPLAYCONTROL | LCD_Opts.DisplayControl);
}

void LCD_ScrollLeft(void) {
	LCD_command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}

void LCD_ScrollRight(void) {
	LCD_command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}

void LCD_CreateChar(uint8_t location, uint8_t *data) {
	uint8_t i;
	/* We have 8 locations available for custom characters */
	location &= 0x07;
	LCD_command(LCD_SETCGRAMADDR | (location << 3));
	
	for (i = 0; i < 8; i++) {
		LCD_data(data[i]);
	}
}

void LCD_PutCustom(uint8_t x, uint8_t y, uint8_t location) {
	LCD_Set_Cursor(x, y);
	LCD_data(location);
}

void LCD_Puts(uint8_t x, uint8_t y, char* str) {
	LCD_Set_Cursor(x, y);
	while (*str) {
		if (LCD_Opts.currentY >= LCD_Opts.Cols) {
			LCD_Opts.currentY = 0;
			LCD_Opts.currentX++;
			LCD_Set_Cursor(LCD_Opts.currentX, LCD_Opts.currentY);
		}
		if (*str == '\n') {
			LCD_Opts.currentX++;
			LCD_Set_Cursor(LCD_Opts.currentX, LCD_Opts.currentY);
		} else if (*str == '\r') {
			
			LCD_Set_Cursor(LCD_Opts.currentX, 0);
		} else {
			LCD_data(*str);
			LCD_Opts.currentY++;
		}
		str++;
	}
}
