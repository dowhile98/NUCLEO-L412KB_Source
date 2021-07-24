#include "stm32f10x.h"                  // Device header
#include "ADC.h"


/*variables globales*/

uint16_t data;

uint16_t IN0;
uint16_t IN1;
uint16_t IN4;
/*prototipo de funciones*/

/**
  * @brief configura los pines analogicos con los que se desea trabajar
	*/
void ADC_CH_Init(void);

/**
  * @brief configura el tiempo de muestreo para los canales configurados
  * @param ADCx: Adc con el que se desea trabajar
	*/
void ADC_CH_sampleTime(ADC_TypeDef * ADCx);
/**
  * @brief configura la secuencia de muestreo
  * @param ADCx: ADC1/2 el cual se quiere configurar
  * @param sequenceLength: numero de conversiones que se desea realizar
	*/
void ADC_CH_regularSequence(ADC_TypeDef * ADCx,uint8_t sequenceLength);

/**
  *@brief obtiene el valor convertido
	* esta función solo es válido en el modo single mode
	*@param ADCx: ADC1/2 del cual se quiere obtener el valor convertido
	*@param INx: numero de canal a convertir
	*/
	
uint16_t ADC_GetValue(ADC_TypeDef * ADCx, uint8_t INx);

/**
  * @brief FUNCION GENERA RETARDO EN MILISEGUNDOS
  * @param delay: retardo en milisegundos deseados
  */
void delay_ms(uint32_t delay);



int main(void){
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	GPIOC->CRH &=~ (GPIO_CRH_CNF13 | GPIO_CRH_MODE13);
	GPIOC->CRH |= GPIO_CRH_CNF13_0 | GPIO_CRH_MODE13;
	/*aplicar un prescaler a la fuente de reloj del adc (MAX = 14MHz*/
	ADCPRE_SetPrescaler(ADCPRE_PLCK2_6);
	/*configurar el adc*/
	ADC_Init(ADC1,0,ADC_CR1_SCAN,0);
	/*Seleccionar trigger*/
	ADC_SelectTrigger(ADC1,ADC_EXT_SWSTART);
	/*configurar los pines analogicos con los que sedesea trabajar*/
	ADC_CH_Init();
	/*configurar el tiempo de muestreo para los canales configurados*/
	ADC_CH_sampleTime(ADC1);
	/*configurar la secuencia de la conversion*/
	ADC_CH_regularSequence(ADC1,3);
	/*habilitar el adc*/
	ADC_Enable(ADC1);

	
	while(1){
		
//		ADC1->CR2 |= ADC_CR2_SWSTART;
//		while(!(ADC1->SR & ADC_SR_EOC));
//		IN0 = ADC1->DR;
//		
//		ADC1->CR2 |= ADC_CR2_SWSTART;
//		while(!(ADC1->SR & ADC_SR_EOC));
//		IN1 = ADC1->DR;
//		
//		ADC1->CR2 |= ADC_CR2_SWSTART;
//		while(!(ADC1->SR & ADC_SR_EOC));
//		IN4 = ADC1->DR;
//		IN4 = ADC_GetValue(ADC1,ADC_IN4);
		IN4 = ADC_GetValue(ADC1,ADC_IN4);
		if(IN4 > 1024*2)
			GPIOC->BSRR |= (1U<<13);
		else
			GPIOC->BRR |= (1U<<13);
		delay_ms(100);
	}
}

/*definicoin de funciones*/
/**
  * @brief configura los pines analogicos con los que se desea trabajar
	*/
void ADC_CH_Init(void){
	/*PA0, PA1, PA4*/
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	
	GPIOA->CRL &=~ (GPIO_CRL_CNF0 | GPIO_CRL_MODE0);
	GPIOA->CRL &=~ (GPIO_CRL_CNF1 | GPIO_CRL_MODE1);
	GPIOA->CRL &=~ (GPIO_CRL_CNF4 | GPIO_CRL_MODE4);
}

/**
  * @brief configura el tiempo de muestreo para los canales configurados
  * @param ADCx: Adc con el que se desea trabajar
	*/
void ADC_CH_sampleTime(ADC_TypeDef * ADCx){
	ADCx->SMPR2 &=~ ADC_SMPR2_SMP0;			//000: 1.5 cycles
	
	ADCx->SMPR2 &=~ ADC_SMPR2_SMP1;
	
	ADCx->SMPR2 &=~ ADC_SMPR2_SMP4;
}

/**
  * @brief configura la secuencia de muestreo
  * @param ADCx: ADC1/2 el cual se quiere configurar
  * @param sequenceLength: numero de conversiones que se desea realizar
	*/
void ADC_CH_regularSequence(ADC_TypeDef * ADCx,uint8_t sequenceLength){
	ADCx->SQR1 &=~ ADC_SQR1_L;
	ADCx->SQR1 |= (sequenceLength - 1)<<20;
	/*secuencia de conversion*/
	//1st
	ADCx->SQR3 &=~ ADC_SQR3_SQ1;
	ADCx->SQR3 |= ADC_IN0<<0;
	//2nd
	ADCx->SQR3 &=~ ADC_SQR3_SQ2;
	ADCx->SQR3 |= ADC_IN1<<5;
	//3th
	ADCx->SQR3 &=~ ADC_SQR3_SQ3;
	ADCx->SQR3 |= ADC_IN4<<10;
}


/**
  *@brief obtiene el valor convertido
	* esta función solo es válido en el modo single mode
	*@param ADCx: ADC1/2 del cual se quiere obtener el valor convertido
	*@param INx: numero de canal a convertir
	*/
uint16_t ADC_GetValue(ADC_TypeDef * ADCx, uint8_t INx){
	
	ADCx->SQR3 = 0;
	ADCx->SQR1 = 0;
	ADCx->SQR3 = INx;
	/*iniciar la conversion*/
	ADCx->CR2 |= ADC_CR2_SWSTART;
	while(!(ADCx->SR & ADC_SR_EOC)); //delay
	
	/*se retorna el valor convertido*/
	return ADCx->DR;
	
}

/**
  * @brief FUNCION GENERA RETARDO EN MILISEGUNDOS
  * @param delay: retardo en milisegundos deseados
  */
void delay_ms(uint32_t delay){
	uint32_t i;
	SysTick->CTRL = 0;
	SysTick->LOAD = SystemCoreClock / 1000 - 1;
	SysTick->VAL = 0;
	SysTick->CTRL  = 1<<2 | 1<<0;
	
	for(i = 0; i<delay ; i++){
		while(!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG));
	}
	SysTick->CTRL =0;
}

