/*-------->GPIO, EXTI AND PLL CONFIG<-------
 *PA11, PC13 	-> OUTPUT (led connect in theses pins)
 *PB0 				-> INPUT (EXTI0 Interrupt) connect push button here
 *PLL					-> CONFIG 64MHz
 *						-> By default  it's set to 72MHz
 *@autor: QUINO B. JEFFRY
 */
#include "stm32f10x.h"                  // Device header

/**********VARIABLES GLOABLES***********/
uint32_t freq;
/**********PROTOTIPO DE FUNCIONES*******/
void PLL_Config(void);
void GPIO_Cofig(void);
void EXTI0_Config(void);
void delay_us(uint32_t delay);
void delay_ms(uint32_t delay);


int main(void){
	__disable_irq();										//disable global interrupts
	freq = SystemCoreClock;							//freq = 72MHz
	PLL_Config();												//PLL output = 64MHz
	SystemCoreClockUpdate();
	freq = SystemCoreClock;							// freq = 64MHz
	GPIO_Cofig();												//PA11, PC13 output mode
	EXTI0_Config();											//PB0 -> EXTI0 interrupt
	__enable_irq();											//ENABLE global interrupts
	while(1){
		GPIOA->BSRR |= GPIO_BSRR_BS11;
		delay_ms(100);
		GPIOA->BRR |= GPIO_BRR_BR11;
		delay_ms(100);
	}
}

void PLL_Config(void){
	/*cambiar la fuente de reloj*/
	RCC->CFGR &=~ RCC_CFGR_SW;									//HSI selected as sysclk
	/*1 deshabilitar el pll*/
	RCC->CR &=~ RCC_CR_PLLON;
	while(RCC->CR & RCC_CR_PLLRDY);
	/*2. seleccionar la fuente de reloj del pll*/
	RCC->CR |= RCC_CR_HSEON;
	while(!(RCC->CR & RCC_CR_HSERDY));
	RCC->CFGR |= RCC_CFGR_PLLSRC_HSE;						//HSE Selected as PLL input clock
	/*3. configurar PLLMUL*/
	RCC->CFGR &=~ (RCC_CFGR_PLLMULL);
	RCC->CFGR |= RCC_CFGR_PLLMULL8;							// PLL input clock x 9 = 72MHz
	/*4. Aplicar los prescaler necesarios*/
	RCC->CFGR &=~ RCC_CFGR_PPRE1;
	RCC->CR |= RCC_CFGR_PPRE1_DIV2;							//HCLK / 2
	/*5 configurar la latencia de la flash*/
	FLASH->ACR &=~ FLASH_ACR_LATENCY;
	FLASH->ACR |= FLASH_ACR_LATENCY_2;
	/*6. encender la pll*/
	RCC->CR |= RCC_CR_PLLON;
	while(!(RCC->CR & RCC_CR_PLLRDY));
	/*7. Seleccionar la fuente de reloj*/
	RCC->CFGR &=~ RCC_CFGR_SW;
	RCC->CFGR |= RCC_CFGR_SW_PLL;
	while(!(RCC->CFGR & RCC_CFGR_SWS_PLL));
}
/***************ISR***********************************/
void EXTI0_IRQHandler(void){
	if(EXTI->PR & EXTI_PR_PR0){
		EXTI->PR |= EXTI_PR_PR0;			/*clear pending bit*/
		
		GPIOC->ODR ^= GPIO_ODR_ODR13;
	}
}


/**********definicion de funciones*******************/
void GPIO_Cofig(void){
	/*enable clock*/
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	/*PC13 -> OUTPUT PUSH PULL*/
	GPIOC->CRH &=~ (GPIO_CRH_CNF13 | GPIO_CRH_MODE13);
	GPIOC->CRH |= GPIO_CRH_MODE13;											/*OUTPUT MODE*/
																											/*ESPEED -> 50MHz*/
																											/*PUSH - PULL*/
	/*PA11 -> OUTPUT PUSH PULL*/
	GPIOA->CRH  &=~ (GPIO_CRH_CNF11 | GPIO_CRH_MODE11);
	GPIOA->CRH |= GPIO_CRH_MODE11;
}

void EXTI0_Config(void){
	/*enable clock*/
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	/*PB0-> INPUT*/
	GPIOB->CRL &=~ (GPIO_CRL_CNF0 | GPIO_CRL_MODE0);
	GPIOB->CRL |= GPIO_CRL_CNF0_1;											/*INPUT*/
	GPIOB->BRR |= GPIO_BRR_BR0;													/*PULL DOWN*/
	AFIO->EXTICR[0] &=~ (uint32_t)AFIO_EXTICR1_EXTI0;
	AFIO->EXTICR[0] |= AFIO_EXTICR1_EXTI0_PB;						/*PB0 exti line conecty*/
	
	/*EXTI CONFIG*/
	EXTI->IMR |= EXTI_IMR_MR0;													/* Interrupt request from Line 0 is not masked*/
	EXTI->RTSR |= EXTI_RTSR_TR0;												/*Rising trigger enabled*/
	EXTI->PR |= EXTI_PR_PR0;														/*CLEAR PENDING BIT*/
	NVIC_SetPriority(EXTI0_IRQn,1);											/*prioridad 1*/
	NVIC_EnableIRQ(EXTI0_IRQn);
}

/*DELAY FUNCTION*/
void delay_us(uint32_t delay){
	uint32_t i;
	SysTick->CTRL = 0;
	SysTick->LOAD = SystemCoreClock/1000000 - 1;
	SysTick->VAL = 0;
	SysTick->CTRL |= 1U<<2 | 1<<0;
	for(i = 0;i< delay;i++){
		while(!(SysTick->CTRL & 1<<16));
	}
	SysTick->CTRL = 0;
}

void delay_ms(uint32_t delay){
	uint32_t i;
	for(i = 0;i<delay; i++){
		delay_us(1000);
	}
}

