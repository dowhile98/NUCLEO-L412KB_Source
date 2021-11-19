#include "stm32l4xx.h"                  // Device header
#include "uart.h"
#include "GPIO.h"
#include "TIMx.h"
#include <stdio.h>
/***********DEFINICION DE MACROS********/
#define LED				1U<<3
#define IN3				1U<<D4
#define IN4				1U<<D5
#define ENCODER		1U<<A1
#define BUTTON		1U<<A3

#define S					120					//cantidad de pulsos por vuelta
#define Ts				0.02				//tiempo de muestreo
#define MUESTRAS	500					//cantidad de muestras de la velocidad
#define TRUE			1						
#define FALSE 		0	

/***********VARIABLES GLOBALES**********/
float	rpm;										//RPM
float radS;										//velocidad en rad/s
uint32_t pulse;								//pulsos del encoder				

uint8_t state;
float y[MUESTRAS];						//Buffer para la exportacion de datos
uint32_t i;										

/*definicion de prototipo de funciones */
void delay_ms(uint32_t delay);

int main(void){	
	/*se selecciana el HSI*/
	RCC->CR |= RCC_CR_HSION;
	while(!(RCC->CR & RCC_CR_HSIRDY));
	RCC->CFGR |= RCC_CFGR_SW_0;
	SystemCoreClockUpdate();
	/*INICIALIZACION DE PERIFERICOS*/
	__disable_irq();
	UART2_Config(SystemCoreClock,115200);
	TIM6_Base_Start_IT();
	TIM2_PWM_Start();
	GPIO_Init();
	__enable_irq();
	printf("CONFIGURACION EXITOSA\r\n");
	
	while(1){
		
	}
}

/*********ISR********************************/
void EXTI1_IRQHandler(void){
	if(EXTI->PR1 & ENCODER){
		EXTI->PR1 |= ENCODER;
		pulse++;												//lectura de pulsos del encoder
	}
	return;
}

void EXTI4_IRQHandler(void){
	if(EXTI->PR1 & BUTTON){
		EXTI->PR1 |= BUTTON;
		NVIC_DisableIRQ(EXTI4_IRQn);		//SE DESHABILITA LA INTERRUPCION
		GPIOB->ODR &=~LED;
		GPIOB->ODR |= IN3;
		GPIOB->ODR &=~ IN4;
		TIM6->CR1 |= TIM_CR1_CEN;				//se habilita el conteo el timer6
		TIM2->CR1 |= TIM_CR1_CEN;				//se hablita el conteo pwm
		TIM2->CCR1 = 318;								//duty 100%
	}
	return;
}

void TIM6_IRQHandler(void){
	if(TIM6->SR & TIM_SR_UIF){
		TIM6->SR &=~ TIM_SR_UIF;
		/*interrupcion cada 20ms*/
		rpm = pulse * 60.0 /(Ts * S);			//se calcula el RPM
		radS = rpm  *(2*3.1415)/60;				//velocidad en Rad/s
		if(i < MUESTRAS){	
			y[i] = radS;										//para exportar a matlab
			i++;
		}
		else{
			GPIOB->ODR &=~ IN3;
			GPIOB->ODR &=~ IN4;
			TIM6->CR1 &=~ TIM_CR1_CEN;				//se habilita el conteo el timer6
			TIM2->CR1 &=~ TIM_CR1_CEN;				//se hablita el conteo pwm
			GPIOB->ODR |= LED;
		}
		pulse = 0;
	}
}
/*************DEFINICION DE FUNCIONES*********/
void delay_ms(uint32_t delay){
	uint32_t i;
	SysTick->CTRL = 0;
	SysTick->LOAD = SystemCoreClock/1000 - 1;
	SysTick->VAL = 0;
	SysTick->CTRL |= 1<<2 | 1<<0;
	for(i = 0;i<delay;i++){
		while(!(SysTick->CTRL & 1<<16));
	}
	SysTick->CTRL = 0;
}
