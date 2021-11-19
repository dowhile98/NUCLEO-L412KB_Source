#include "TIMx.h"

static void GPIO_TIM2_CH1_Config(void){
	RCC->AHB2ENR 	= RCC_AHB2ENR_GPIOAEN;
	
	GPIOA->MODER &=~ GPIO_MODER_MODER0;
	GPIOA->MODER |= GPIO_MODER_MODE0_1;
	GPIOA->AFR[0] |= GPIO_AFRL_AFSEL0_0;				//PA0 -> TIM2_CH1
}


void TIM6_Base_Start_IT(void){
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM6EN;
	TIM6->CR1 = 0;
	TIM6->DIER |= TIM_DIER_UIE;
	TIM6->PSC = 16 - 1;
	TIM6->ARR = 20000 - 1;
	NVIC_SetPriority(TIM6_IRQn,3);
	NVIC_EnableIRQ(TIM6_IRQn);
	
}

void TIM2_PWM_Start(void){
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;
	GPIO_TIM2_CH1_Config();
	/*CONFIGURACION DE PARAMETROS DEL TIMER 2*/
	TIM2->PSC = 2-1;											//16MHz/2 = 4MHZ
	TIM2->ARR = 319-1;										//25khz
	TIM2->CNT = 0;
	TIM2->CCMR1 |= 0x6<<4;								//PWM -> mode 1
	TIM2->CCMR1 |= TIM_CCMR1_OC1PE;
	TIM2->CCER |= TIM_CCER_CC1E;					//se habilita ch1 -> pwm
	
}
