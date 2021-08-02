#include "Delay.h"

/*VARIABLES PRIVADAS*/
uint32_t uwTick;			//variable que incrementa cada 1ms

/*********FUNCIONES PRIVADAS**************/


/**
 * @brief Retorna el valor de la variabla ticks
 * @param none
 * @return ticks
 */
uint32_t GetTick(void){
	
	return uwTick;
}

/*DEFINICION DE FUNCIONES*/
/**
 * @brief Configura el SysTick
 * Esta funcion configura el SysTick para generar
 * interrupciones cada 1ms.
 * @param none
 * @return none
 */
void Delay_Init(void){
	__disable_irq();
	#if(USE_SYTICK == 1)
	/*1. deshabilitar el systick*/
	SysTick->CTRL  = 0;
	/*2. cofigurar el valor de reload*/
	SysTick->LOAD = SystemCoreClock / 1000 - 1;
	/*3. seleccionar la fuente de reloj*/
	SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk; 
	/*4. poner el registro val*/
	SysTick->VAL = 0;
	/*5. habilitar la interrupcion y el conteo*/
	SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk | \
									 SysTick_CTRL_ENABLE_Msk;	
	/*6. (opcional) cambiar la prioridad*/
	NVIC_SetPriority(SysTick_IRQn,3);
	#else
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM6EN;
	/*Configurar los parametros del TIMER*/
	TIM6->ARR = SystemCoreClock / 2000 - 1 ;
	TIM6->PSC = 2 - 1;
	/*ENABLE INTERRUPT*/
	TIM6->DIER |= TIM_DIER_UIE;
	NVIC_SetPriority(TIM6_IRQn,3);
	NVIC_EnableIRQ(TIM6_IRQn);
	/*timer enable*/
	TIM6->CR1 |= TIM_CR1_CEN;
	#endif /*USE_SYSTICK*/
  __enable_irq();	
	return;
}


/**
 * @brief Genera retardos en ms
 * Esta funcion genera retardos en ms 
 * @param delay: el tiempo en ms del retardo deseado
 * @return none
 */
void delay_ms(uint32_t delay){
	
	uint32_t tickstart = GetTick();
  uint32_t wait = delay;
	
	/*delay*/
  while ((GetTick() - tickstart) < wait);
	
	return;
}

/*ISR*/
#if(USE_SYTICK == 1)	
void SysTick_Handler(void){
	if(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk)
		uwTick+= 1;   //se incrementa el valor de la variable en 1
	
	return;
}

#else

void TIM6_IRQHandler(void){
	if(TIM6->SR & TIM_SR_UIF){
		TIM6->SR = 0;
		uwTick +=1;
	}
	
}
#endif /*USE_SYSTICK*/
