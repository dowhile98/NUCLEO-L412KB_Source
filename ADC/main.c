

#include "stm32l4xx.h"                  // Device header
#include "RCC.h"
#include "USART.h"
#include "Delay.h"
#include "ADC.h"
#include <stdio.h>
/*VARIABLES GLOBALES*/
uint16_t IN5;
uint16_t IN6;
uint16_t IN8;

int main(void){
	
	PLL_Config();													//80MHZ
	Delay_Init();
	USART2_Config(SystemCoreClock,USART_OVER8_16,115200);
	
	/*configurar el adc*/
	ADC1_Init();
	
	ADC_Enable(ADC1);
	while(1){
		IN5 = ADC_GetVal(ADC1,ADC_IN5);
		IN6 = ADC_GetVal(ADC1,ADC_IN6);
		IN8 = ADC_GetVal(ADC1,ADC_IN8);
		printf("ADC1  IN5 -> %d\n\r",IN5);
		printf("ADC1  IN6 -> %d\n\r",IN6);
		printf("ADC1  IN8 -> %d\n\r",IN8);
		delay_ms(100);
		
	}
}

