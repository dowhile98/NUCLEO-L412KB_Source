/**
  *@autor Quino B. Jeffry
  *@version v.1
  */
#ifndef __ADC_H
#define __ADC_H

/*INCLUDES*/
#include "stm32f10x.h"                  // Device header



/*DEFINICION DE MACROS*/

#define ADC_IN0													0x0U 	//PA0
#define ADC_IN1													0x1U	//PA1
#define ADC_IN2													0x2U	//PA2
#define ADC_IN3													0x3U	//PA3
#define ADC_IN4													0x4U	//PA4
#define ADC_IN5													0x5U	//PA5
#define ADC_IN6													0x6U	//PA6
#define ADC_IN7													0x7U	//PA7
#define ADC_IN8													0x8U	//PB0
#define ADC_IN9													0x9U	//PB1


#define ADCPRE_PCLK2_2									0x0U<<14 
#define ADCPRE_PLCK2_4									0x1U<<14
#define ADCPRE_PLCK2_6									0x2U<<14
#define ADCPRE_PLKC2_8									0x3U<<14



#define ADC_EXT_TIM1_CC1								0x0U<<17
#define ADC_EXT_TIM1_CC2								0x1U<<17
#define ADC_EXT_TIM1_CC3 								0x2U<<17
#define ADC_EXT_TIM2_CC2 								0x3U<<17
#define ADC_EXT_TIM3_TRGO								0x4U<<17
#define ADC_EXT_TIM4_CC4								0x5U<<17
#define ADC_EXT_EXTI11									0x6U<<17
#define ADC_EXT_SWSTART									0x7U<<17

/*PROTOTIPO DE FUNCIONES*/

				


/**
	* @brief INICIALIZAION DEL ADC
	* @param ADCx: ADC1/ADC2 que se quiere configurar
  * @param CONT: ADC_CR2_CONT si se quiere activar el modo de con. continua, de lo contrario 0.
	* @param SCAN: ADC_CR1_SCAN si se quiere activar el modo scan, de lo contrario 0
	* @param EOCIE: ADC_CR1_EOCIE si quiere activar interrupciones en cada conversion
  */
void ADC_Init(ADC_TypeDef * ADCx,uint32_t CONT,uint32_t SCAN,uint32_t EOCIE);
/**
	* @brief INICIALIZAION DEL ADC
	* @param ADCx: ADC1/ADC2 que se quiere habilitar
	*/
void ADC_Enable(ADC_TypeDef * ADCx);


/**
  * @brief APLICA UN PRESCALER AL LA FUENTE DE RELOJ DEL ADC
	* @param PCLK2_PSC: Valor del prescaler del apb2
	*/
void ADCPRE_SetPrescaler(uint32_t PLCK2_PSC);


/**
  * @brief ESTA FUNCION SELECCIONA LA FUENTE DE TRIGGER DEL ADC
	* @param ADCx: ADC1/ADC2 que se quiere configurar
	* @param TRIGGEG: La fuente de trigger
	*/
void ADC_SelectTrigger(ADC_TypeDef * ADCx,uint32_t TRIGGER);
#endif /*__ADC_H*/


