#include "stm32l4xx.h"                  // Device header
#include "Delay.h"


int main(void){
	//PB3 -> SALIDA
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
	GPIOB->MODER &=~ GPIO_MODER_MODE3;
	GPIOB->MODER |= GPIO_MODER_MODE3_0;
	
	Delay_Init();
	
	while(1){
		GPIOB->ODR ^=1U<<3;
		delay_ms(50);
	}
	
}

//void SysTick_Handler(void){
//	
//	if(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk){
//		//code here
//		GPIOB->ODR ^=1U<<3;
//	}
//}

