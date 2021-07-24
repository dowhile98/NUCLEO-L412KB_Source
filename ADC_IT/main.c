

#include "stm32l4xx.h"                  // Device header
#include "RCC.h"
#include "USART.h"
#include "Delay.h"
#include "ADC.h"
#include "TIMER.h"

#include <stdio.h>
/*VARIABLES GLOBALES*/
uint16_t dataAdc[5];


/**
  *@brief Configura los pines seleccinados a su función analogico
	* modificar esta funcion de acuerdo a los pines usados
	*/
void ADC_Pins_Init(void);


/**
  *@brief Establece el tiempo de muestreo para cada canal configurado
  * Modificar esta función de acuerdo a los canales usados
	*@param ADCx: ADC1/ADC2 que se desea configurar
	*/
void ADC_SetSamplingTime(ADC_TypeDef * ADCx);


/**
  *@brief Establece la secuencia de conversion
  * Modificar esta función de acuerdo a los canales usados
	*@param ADCx: ADC1/ADC2 que se desea configurar
	*/
void ADC_SetConversionSqc(ADC_TypeDef * ADCx);

int main(void){
	/*RCC configuration*/
	PLL_Config();													//80MHZ
	/*delay init*/
	Delay_Init();
	/*usart2 config*/
	USART2_Config(SystemCoreClock,USART_OVER8_16,115200);
	
	/*************************ADC*******************************/
	//1. ADC Init
	ADC1_Init();
	//2. ADC pinout configuration
	ADC_Pins_Init();
	//3.Set CHANEL sampling time 
	ADC_SetSamplingTime(ADC1);
	//4.Set the conversion sequence of the ADC
	ADC_SetConversionSqc(ADC1);
	//5.Set ADC trigger
	ADC_ExternalTrigger_Init(ADC1,EXT_TIM6_TRGO,HARDWARE_TRIGGER_RISING);
	//6.configure chosen ADC trigger source
	TIMER6_BaseTime(8000,10000-1,TIM_IT_DISABLE);
	TIM6->CR2 &=~ TIM_CR2_MMS;
	TIM6->CR2 |= TIM_CR2_MMS_1; //The update event is selected as trigger output (TRGO)
	//7. Enable interrupt
	ADC1->IER |= ADC_IER_EOCIE | ADC_IER_EOSIE;
	NVIC_EnableIRQ(ADC1_2_IRQn);
	NVIC_SetPriority(ADC1_2_IRQn,2);
	//8. enabla ADC
	ADC_Enable(ADC1);
	ADC1->CR |= ADC_CR_ADSTART;
	while(1){
		/*start conversion*/
		//ADC1->CR |= ADC_CR_ADSTART;
//		/*Wait*/
//		while(!(ADC1->ISR & ADC_ISR_EOC));				// wait for EOC flag to set
//		dataAdc[0] = ADC1->DR;										//IN5
//		while(!(ADC1->ISR & ADC_ISR_EOC));				// wait for EOC flag to set
//		dataAdc[1] = ADC1->DR;										//IN6
//		while(!(ADC1->ISR & ADC_ISR_EOC));				// wait for EOC flag to set
//		dataAdc[2] = ADC1->DR;										//IN8
//		while(!(ADC1->ISR & ADC_ISR_EOC));				// wait for EOC flag to set
//		dataAdc[3] = ADC1->DR;										//IN9
//		while(!(ADC1->ISR & ADC_ISR_EOC));				// wait for EOC flag to set
//		dataAdc[4] = ADC1->DR;										//IN10
//		
//		printf("IN5->%d , IN6->%d , IN8->%d ,IN9->%d ,IN10->%d \n\r",dataAdc[0], \
//						dataAdc[1],dataAdc[2],dataAdc[3],dataAdc[4]);
		delay_ms(100);
		
	}
}

/**
  *@brief Configura los pines seleccinados a su función analogico
	* modificar esta funcion de acuerdo a los pines usados
	*/
void ADC_Pins_Init(void){
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
	//PA0, PA1, PA3, PA4, PA5 -> analogico
	GPIOA->MODER |= GPIO_MODER_MODE0 | GPIO_MODER_MODE1 | GPIO_MODER_MODE3 | \
									GPIO_MODER_MODE4 | GPIO_MODER_MODE5;
	GPIOA->PUPDR &=~ (GPIO_PUPDR_PUPD0 | GPIO_PUPDR_PUPD1 | GPIO_PUPDR_PUPD3 | \
										GPIO_PUPDR_PUPD4 	| GPIO_PUPDR_PUPD5);
}

/**
  *@brief Establece el tiempo de muestreo para cada canal configurado
  * Modificar esta función de acuerdo a los canales usados
	*@param ADCx: ADC1/ADC2 que se desea configurar
	*/
void ADC_SetSamplingTime(ADC_TypeDef * ADCx){
	ADCx->SMPR1 |= ADC_SMPR1_SMP5_1;    //IN5 -> 12.5 ADC clock cycles
	ADCx->SMPR1 |= ADC_SMPR1_SMP6_1;    //IN6 -> 12.5 ADC clock cycles
	ADCx->SMPR1 |= ADC_SMPR1_SMP8_1;    //IN8 -> 12.5 ADC clock cycles
	ADCx->SMPR1 |= ADC_SMPR1_SMP9_1;    //IN9 -> 12.5 ADC clock cycles
	ADCx->SMPR2 |= ADC_SMPR2_SMP10_1;    //IN10 -> 12.5 ADC clock cycles
	
}

/**
  *@brief Establece la secuencia de conversion
  * Modificar esta función de acuerdo a los canales usados
	*@param ADCx: ADC1/ADC2 que se desea configurar
	*/
void ADC_SetConversionSqc(ADC_TypeDef * ADCx){
	ADCx->SQR1  = 0;
	ADCx->SQR1 |= (0x4)<<ADC_SQR1_L_Pos;
	/*configurar la secuencia de la conversion*/
	ADCx->SQR1 |= ADC_IN5 << ADC_SQR1_SQ1_Pos;
	ADCx->SQR1 |= ADC_IN6 << ADC_SQR1_SQ2_Pos;
	ADCx->SQR1 |= ADC_IN8 << ADC_SQR1_SQ3_Pos;
	ADCx->SQR1 |= ADC_IN9 << ADC_SQR1_SQ4_Pos;
	ADCx->SQR2 |= ADC_IN10 << ADC_SQR2_SQ5_Pos;
}


