#include "stm32l4xx.h"                  // Device header
#include "LPUART.h"
#include <stdio.h>
#include "RCC.h"


/*prototipo de funciones*/
/**
  * @fn CONFIGURA EL PIN PB0 como fuente de interrupcion externa
	*/
void BUTTON_Init(void);

/**
  * @fn entra al modo LP run mode
	*/
void LowPowerRunMode(void);
/**
  * @fn entra al modo LP sleep
	*/
void LowPowerSleepMode(void);


int main(void){
	
	
	LPUART1_Config(16000000,9600);
	
	/*HABILITA EL RELOJ EN LOS MODOS SLEEP Y STOP*/
	RCC->APB1SMENR2 |= RCC_APB1SMENR2_LPUART1SMEN;
	
	BUTTON_Init();
	printf("CONFIGURACION EXITOSA\r\n");
	/*LP RUN*/
	LowPowerRunMode();
	
	
	while(1){
		
		/*LP SLEEP*/
		printf("ENTRANDO AL MODO LOW POWER SLEEP MODE\r\n");
		LowPowerSleepMode();
		printf("SALIENDO DEL MODO LOW POWER SLEEP MODE\r\n");
	}
}

void BUTTON_Init(void){
	//PB0 -> ENTRADA PULL DOWN
	/*enable clock*/
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
	GPIOB->MODER &=~ GPIO_MODER_MODE0;
	GPIOB->PUPDR &=~ GPIO_PUPDR_PUPD0;	
	GPIOB->PUPDR |= GPIO_PUPDR_PUPD0_1;	
	/*exti , syscfg*/
	RCC->APB2ENR |=   RCC_APB2ENR_SYSCFGEN;
	
	EXTI->IMR1 |= EXTI_IMR1_IM0;
	EXTI->RTSR1 |= EXTI_RTSR1_RT0;
	EXTI->PR1 |= EXTI_PR1_PIF0;
	/*SYSCFGR*/
	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI0_PB;
	/*NVIC*/
	NVIC->IP[EXTI0_IRQn] = 0x1U<<4;
	NVIC_EnableIRQ(EXTI0_IRQn);
}

void EXTI0_IRQHandler(void){
	if(EXTI->PR1 & EXTI_PR1_PIF0){
		EXTI->PR1 |= EXTI_PR1_PIF0;
		//CODIGO
		printf("IT EXTERNA\r\n");
		
	}
	
	return;
	
}
/**
  * @fn entra al modo LP run mode
	*/
void LowPowerRunMode(void){
	MSI_ConfigRange(MSI_RANGE5_2MHz);
	/*enable clock*/
	RCC->APB1ENR1 |= RCC_APB1ENR1_PWREN;
	
	PWR->CR1 |= PWR_CR1_LPR;
}


/**
  * @fn entra al modo LP sleep
	*/
void LowPowerSleepMode(void){
	
	PWR->CR1 |= PWR_CR1_LPR;
	SCB->SCR &=~ SCB_SCR_SLEEPDEEP_Msk;
//	SCB->SCR |= SCB_SCR_SLEEPONEXIT_Msk;
	__WFI();
//	__ASM("WFI");
	return;
}
