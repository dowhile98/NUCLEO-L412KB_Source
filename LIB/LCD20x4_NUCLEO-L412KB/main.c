
#include "stm32l4xx.h"                  // Device header
#include "LCD.h"

void delay_ms(uint32_t delay);
int main(void){
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
	GPIOB->MODER &=~ GPIO_MODER_MODE3;
	GPIOB->MODER |= GPIO_MODER_MODE3_0;
	LCD_Init();
	LCD_Set_Cursor(0,0);
	LCD_printStr("---->UMAKER SAC<----");
	LCD_Set_Cursor(1,0);
	LCD_printStr("QUINO B. JEFFRY");
	while(1){
		GPIOB->ODR ^=1<<3;
		delay_ms(100);
	}
}


void delay_ms(uint32_t delay){
	uint32_t i;
	SysTick->CTRL = 0;
	SysTick->LOAD = SystemCoreClock /1000 - 1;
	SysTick->VAL = 0;
	SysTick->CTRL |= 1<<2 | 1<<0;
	for(i = 0;i<delay;i++){
		while(!(SysTick->CTRL & 1<<16));
	}
	SysTick->CTRL = 0;
}

