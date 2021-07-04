#include "stm32l4xx.h"                  // Device header

uint8_t PB1_Value;

void GPIO_Config(void);
void delay_ms(uint32_t delay);

int  main(void){
	
	GPIO_Config();
	
//	GPIOB->ODR |= GPIO_ODR_OD3;
//	GPIOB->ODR &=~ GPIO_ODR_OD3;
//	
//	GPIOB->BSRR |= 1U<<3;
//	//GPIOB->BSRR |= 1U<<(16 + 3);
//	GPIOB->BRR |= 1U<<3;
	for(;;){
		PB1_Value = (GPIOB->IDR)>>1 & 0x1;
		if(PB1_Value){
			GPIOB->BSRR |= 1U<<3;
		}else{
			GPIOB->BRR |= 1U<<3;
		}
	}
}

void GPIO_Config(void){
	//PB1-> ENTRADA + PD
	//PB3-> SALIDA PUSH-PULL
	/*0. ENABLE CLK*/
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
	/*PB1*/
	GPIOB->MODER &=~ GPIO_MODER_MODE1;
	GPIOB->PUPDR &=~ GPIO_PUPDR_PUPD1;
	GPIOB->PUPDR |= GPIO_PUPDR_PUPD1_1;			//pull down
	/*PB3*/
	GPIOB->MODER &=~ GPIO_MODER_MODE3;
	GPIOB->MODER |= GPIO_MODER_MODE3_0;			//01: General purpose output mode
	GPIOB->OTYPER &=~GPIO_OTYPER_OT3;				//push pull
	GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED3;	//very high speed
	GPIOB->PUPDR &=~ GPIO_PUPDR_PUPD3;			//no pull up/down
}

void delay_ms(uint32_t delay){
	uint32_t i;
	SysTick->CTRL  = 0;
	SysTick->LOAD = SystemCoreClock/1000;
	SysTick->VAL = 0;
	SysTick->CTRL |= 1<<2 | 1;
	for(i =0; i<delay; i++){
		while(!(SysTick->CTRL & 1<<16));
	}
	SysTick->CTRL = 0;
}


