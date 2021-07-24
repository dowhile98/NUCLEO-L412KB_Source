/**
  *@autor Quino B. Jeffry
  *@version v.1
  */
 
#include "ADC.h"

/**
	* @brief INICIALIZAION DEL ADC
	* @param ADCx: ADC1/ADC2 que se quiere configurar
  * @param CONT: ADC_CR2_CONT si se quiere activar el modo de con. continua, de lo contrario 0.
	* @param SCAN: ADC_CR1_SCAN si se quiere activar el modo scan, de lo contrario 0
	* @param EOCIE: ADC_CR1_EOCIE si quiere activar interrupciones en cada conversion
  */
void ADC_Init(ADC_TypeDef * ADCx,uint32_t CONT,uint32_t SCAN,uint32_t EOCIE){
	/*enable clock*/
	if(ADCx == ADC1)
		RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	else
		RCC->APB2ENR |= RCC_APB2ENR_ADC2EN;
	/*Calibrar el adc*/
//	ADCx->CR2 |= ADC_CR2_RSTCAL;
//	while((ADCx->CR2 & ADC_CR2_RSTCAL));
//	
//	ADCx->CR2 |= ADC_CR2_CAL;
//	while((ADC1->CR2 & ADC_CR2_CAL));
	/*Configuracion de algunos parametros del del ADC*/
	ADCx->CR2 &=~ ADC_CR2_ALIGN;														//Right Alignment
	ADCx->CR2 &=~ ADC_CR2_CONT;
	ADCx->CR2 |= CONT;
	ADCx->CR1 &=~ ADC_CR1_SCAN;
	ADCx->CR1 |= SCAN;
	/*INTERRUPCION*/
	if(EOCIE == ADC_CR1_EOCIE){
		ADCx->CR1 |= EOCIE;
		NVIC_SetPriority(ADC1_2_IRQn,2);
		NVIC_EnableIRQ(ADC1_2_IRQn);
	}
	else
		ADCx->CR1 &=~ ADC_CR1_EOCIE;
	
	return;
}


/**
	* @brief INICIALIZAION DEL ADC
	* @param ADCx: ADC1/ADC2 que se quiere habilitar
	*/
void ADC_Enable(ADC_TypeDef * ADCx){
	uint32_t delay = 10000;
	ADCx->CR2 |= ADC_CR2_ADON;
	while(delay--);								//delay by Power-up Time
}



/**
  * @brief APLICA UN PRESCALER AL PCLK2
	* @param PCLK2_PSC: Valor del prescaler del apb2
	*/
void ADCPRE_SetPrescaler(uint32_t PLCK2_PSC){
	RCC->CFGR &=~ RCC_CFGR_ADCPRE;
	RCC->CFGR |= PLCK2_PSC;
	return;
}


/**
  * @brief ESTA FUNCION SELECCIONA LA FUENTE DE TRIGGER DEL ADC
	* @param ADCx: ADC1/ADC2 que se quiere configurar
	* @param TRIGGEG: La fuente de trigger
	*/
void ADC_SelectTrigger(ADC_TypeDef * ADCx,uint32_t TRIGGER){
	ADCx->CR2 &=~ ADC_CR2_EXTSEL;
	ADCx->CR2 |= TRIGGER;
	ADCx->CR2 |= ADC_CR2_EXTTRIG;
	return;
}
