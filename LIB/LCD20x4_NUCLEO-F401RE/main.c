#include "stm32f4xx.h"                  // Device header
#include "LCD16x2.h"
#include "delay.h"
#include "KEYPAD4X4.h"

uint8_t data;


int main(void){
	
	keypad_init();
	LCD_Init();
  LCD_clear();
  LCD_printStr("*******UMAKER*******");
  LCD_Set_Cursor(1, 0);
  LCD_printStr("------>STM32<------");
	LCD_Set_Cursor(2, 0);
  LCD_printInt(2021);
	LCD_Set_Cursor(3, 0);
	LCD_printStr("PRESIONE-> ");
	while(1){
		data = keypad_read();
		if(data != KEYPAD_EMPTY){
			LCD_Set_Cursor(3, 0);
			LCD_printStr("PRESIONE-> ");
			LCD_printChar(data);
		}
	}
}



