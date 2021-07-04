#include "stm32l4xx.h"                  // Device header
#include "RCC.h"

void Delay_Init(void);
void delay_us(uint32_t delay);
void delay_ms(uint32_t delay);

int main(void){
	/*cambiar la fuente de reloj*/
//	RCC->CR |= RCC_CR_HSION;
//	while(!(RCC->CR & RCC_CR_HSIRDY));
//	RCC->CFGR |= RCC_CFGR_SW_HSI;
//	while(!(RCC->CFGR & RCC_CFGR_SWS_HSI));
//	SystemCoreClockUpdate();
	PLL_Config();												//sysclk = 80MHz
	Delay_Init();
	/*PB3->SALIDA PUSH-PULL*/
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
	GPIOB->MODER &=~ GPIO_MODER_MODE3;
	GPIOB->MODER |= GPIO_MODER_MODE3_0;
	while(1){
		GPIOB->BSRR |= GPIO_BSRR_BS3;
		delay_ms(50);
		GPIOB->BRR |= GPIO_BRR_BR3;
		delay_ms(50);
	}
}


void Delay_Init(void){
	/*1. deshabilitar el systick*/
	SysTick->CTRL  = 0;
	/*2. cofigurar el valor de reload*/
	SysTick->LOAD = SystemCoreClock / 1000000 - 1;
	/*3. seleccionar la fuente de reloj*/
	SysTick->CTRL |= 1<<2;		//system clock
	/*4. poner el registro val*/
	SysTick->VAL = 0;
}
void delay_us(uint32_t delay){
	uint32_t i;
	//habilita el conteo
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
	SysTick->VAL = 0;
	//retardo
	for(i = 0; i<delay;i++){
		while(!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk));//1us
	}
	SysTick->CTRL &=~ SysTick_CTRL_ENABLE_Msk;
}
void delay_ms(uint32_t delay){
	uint32_t i;
	for(i = 0; i<delay;i++){
		delay_us(1000);																				//1ms
	}
}
