#include "stm32l4xx.h"                  // Device header
#include "uart.h"
#include "GPIO.h"
#include "TIMx.h"
#include <stdio.h>
#include <string.h>
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
uint8_t count = 1;
								

float ref	;
uint16_t U;													//valor uk calculado
/*esta estructuca contiene las variables presentes y pasadas del controlador*/
typedef struct{
	/*error*/
	float ePresent;
	float ePast;     //ek_1
	/*termino proporcional*/
	float PPresent;
	/*termino integral*/
	float IPresent;
	float IPast;
	/*termino derivativo*/
	float DPresent;
	float DPast;
	/*salida medida*/
	float yPresent;
	float yPast;
	/*salida del wind up*/
	float wPresent;
	float wPast;
	/*salida del saturador*/
	float uPresent;
	float uPast;
	/*salida del controlador*/
	float vPresent;
	float vPast;
	/*valores maximos y minimos del saturador*/
	uint16_t Vmax;
	uint16_t Vmin;
}PID_Def_t;


PID_Def_t MOTOR_DC;

/*definicion de prototipo de funciones */
void delay_ms(uint32_t delay);
/**
 * @brief esta funcion inicializa algunos parametros de PID_Def_t
 * @param PID_Def_t
 * @param vMax : valor maximo del saturador
 * @param vMin : valor minimo del saturador
*/
void PID_Config(PID_Def_t *pPID, uint16_t vMin,uint16_t vMax);

/**
 * @brief esta funcion calcula el valor u(k)
 * @param PID_Def_t
 * @param y  : valor de la velocidad medida en Ts
 * @retval u : retorna el valor de u(k)
*/
uint16_t Calculate_PID(PID_Def_t *pPID,float r, float y);


int main(void){
	/*se selecciana el HSI*/
	RCC->CR |= RCC_CR_HSION;
	while(!(RCC->CR & RCC_CR_HSIRDY));
	RCC->CFGR |= RCC_CFGR_SW_0;
	SystemCoreClockUpdate();
	/*INICIALIZACION DE PERIFERICOS*/
	__disable_irq();
	UART2_Config(SystemCoreClock,115200);
	//TIM6_Base_Start_IT();
	//TIM2_PWM_Start();
	GPIO_Init();
	__enable_irq();
	
	PID_Config(&MOTOR_DC,159,318);
	
	GPIOB->ODR |= IN3;
	GPIOB->ODR &=~ IN4;
	TIM6->CR1 |= TIM_CR1_CEN;				//se habilita el conteo el timer6
	TIM2->CR1 |= TIM_CR1_CEN;				//se hablita el conteo pwm
	printf("CONFIGURACION EXITOSA\r\n");
	
	while(1){
		GPIOB->ODR ^= LED;
		delay_ms(100);
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
		switch(count){
			case 1: 
				ref = 20; count++;break;
			case 2: 
				ref = 50; count++;break;
			case 3: 
				ref = 100; count++;break;
			case 4: 
				ref = 150; count++;break;
			case 5: 
				ref = 200; count++;break;
			case 6: 
				ref = 240; count++;break;
			case 7: 
				ref = 280; count++;break;
			case 8: 
				ref = 300; count++;break;
			case 9: 
				ref = 320; count++;break;
			case 10: 
				ref = 350; count++;break;
			default: 
				ref = 0;count  = 1;break;
		}
		
	}
	return;
}

void TIM6_IRQHandler(void){
	if(TIM6->SR & TIM_SR_UIF){
		TIM6->SR &=~ TIM_SR_UIF;
		/*interrupcion cada 20ms*/
		rpm = pulse * 60.0 /(Ts * S);			//se calcula el RPM
		radS = rpm  *(2*3.1415)/60;				//velocidad en Rad/s
		U = Calculate_PID(&MOTOR_DC,ref,radS);
		TIM2->CCR1 = U;
		printf("%.2f\r\n",radS);
		
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


/*******************DEFINICION DE FUNCIONES PARA EL PID********************/
void PID_Config(PID_Def_t *pPID, uint16_t vMin,uint16_t vMax){
	/*se pone todos los valores a 0*/
	memset(pPID,0,sizeof(PID_Def_t));
	pPID->Vmax = vMax;
	pPID->Vmin = vMin;
}

uint16_t Calculate_PID(PID_Def_t *pPID,float r, float y){
	//se obtiene la medida
	pPID->yPresent = y;
	//se calcula el error
	pPID->ePresent = r - pPID->yPresent;
	//termino proporcional
	pPID->PPresent = -0.008589* pPID->ePresent;
	//termino integral 
	pPID->IPresent =(float)( pPID->IPast + 0.00555*pPID->ePast);
	//termino derivativo con filtro
	pPID->DPresent = (float)(0.1353352*pPID->DPast + 0.01067*pPID->yPresent - 0.01067*pPID->yPast);
	
	//se halla v(k)
	pPID->vPresent = pPID->PPresent + pPID->IPresent + pPID->DPresent + pPID->wPresent + 158;				//se suma 158 ( por que el motor recien gira cuando el duty es mayor 50%)
	
	//se pasa por el saturador
	if(pPID->vPresent > pPID->Vmax)
		pPID->vPresent = pPID->Vmax;
	else if (pPID->vPresent < pPID->Vmin)
		pPID->vPresent = pPID->Vmin;
	//wind up
	pPID->wPresent = (float)(pPID->wPast + 0.4*(pPID->uPast - pPID->vPast));
	
	//se actuliza el valor de la salida
	pPID->uPresent = pPID->vPresent;
	
	//se actulizan los valores pasados
	pPID->DPast = pPID->DPresent;
	pPID->IPast = pPID->IPresent;
	pPID->wPast = pPID->wPresent;
	pPID->uPast = pPID->uPresent;
	pPID->vPast = pPID->vPresent;
	pPID->ePast = pPID->ePresent;
	pPID->yPast = pPID->yPresent;
	
	//se retorna el valor calculado
	return (uint16_t)(pPID->uPresent);
}
