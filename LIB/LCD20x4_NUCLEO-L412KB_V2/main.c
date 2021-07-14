
#include "stm32l4xx.h"                  // Device header
#include "LCD.h"
#include <stdio.h>
void delay_ms(uint32_t delay);


int main(void){
	char txt[20];
	uint16_t count;
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
	GPIOB->MODER &=~ GPIO_MODER_MODE3;
	GPIOB->MODER |= GPIO_MODER_MODE3_0;
	LCD_Init(20,4);
	LCD_Puts(0,0,"------>UMAKER<------");
	LCD_Puts(1,0,"NUCLEO-L412BK\n\rQUINO B.J. 2021");
	
	while(1){
		++count;
		sprintf(txt,"tiempo->%d seg",count);
		LCD_Puts(3,0,txt);
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
