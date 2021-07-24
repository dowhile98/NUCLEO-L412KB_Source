#include "stm32l4xx.h"                  // Device header
#include <stdio.h>


extern uint16_t dataAdc[5];
uint8_t i;


void ADC1_2_IRQHandler(void){
	
	if(ADC1->ISR & ADC_ISR_EOC){
		dataAdc[i] = ADC1->DR;
		i++;
	}
	else if(ADC1->ISR & ADC_ISR_EOS){
		ADC1->ISR |= ADC_ISR_EOS;
		i = 0;
		printf("IN5->%d , IN6->%d , IN8->%d ,IN9->%d ,IN10->%d \n\r",dataAdc[0], \
						dataAdc[1],dataAdc[2],dataAdc[3],dataAdc[4]);
	}
	
}


