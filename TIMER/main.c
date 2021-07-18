#include "stm32l4xx.h"                  // Device header
#include "RCC.h"
#include "TIMER.h"
#include "Delay.h"

#define CH1_PSC			1
#define POLARITY		1

float freq;
float dist;

/*prototipo de funciones*/
float calFreq(void);
float calDist(void);

int main(void){
	uint32_t i;
	//pb3-> salida
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
	GPIOB->MODER &=~ GPIO_MODER_MODE3;
	GPIOB->MODER |= GPIO_MODER_MODE3_0;
	PLL_Config();												//SystemCoreClock = 80MHz
	Delay_Init();
	TIMER6_BaseTime(1,800-1,TIM_IT_DISABLE);
	
	TIMER2_CH1_IC_Start(1,0xFFFFFFFF,TIM_IC_IC1F_NO_FITER, \
											TIM_IC_IC1PSC_NO_PSC,TIM_IC_BOTH,TIM_IT_DISABLE);
	TIMER16_CH1_OC_PWM_Start(80,20000-1,1000);
	while(1){
//		for( i = 0;i<=20000; i+=20){
//			TIM16->CCR1 = i;
//			delay_ms(1);
//		}
	}
	
}


/*definicion de funciones*/
float calFreq(void){
	uint32_t capture[2];		//para almacenar el valor de CCR1
	float diffCapture;			//para la diferencia de los valores leidos
	uint32_t TIM2_CLK = SystemCoreClock;
	float frequency;				//frecuencia medida
	/*se espera hasta que se detecte un flanco de subida*/
	TIM2->SR &=~ TIM_SR_CC1IF;
	while(!(TIM2->SR & TIM_SR_CC1IF));
	TIM2->SR &=~ TIM_SR_CC1IF;
	capture[0] = TIM2->CCR1;
	/*se espera hasta obtener el siguiente flanco de subida*/
	while(!(TIM2->SR & TIM_SR_CC1IF));
	TIM2->SR &=~ TIM_SR_CC1IF;
	capture[1] = TIM2->CCR1;
	/*verificamos los datos leidos*/
	if(capture[1] >= capture[0]){
		diffCapture = capture[1] - capture[0];
	}
	else{
		diffCapture = TIM2->ARR - capture[0] + capture[1];
	}
	/*calculo del la frecuencia*/

	frequency = (float)((TIM2_CLK/((TIM2->PSC +1)  * POLARITY)) / diffCapture) * CH1_PSC;
	
	return frequency;
}

float calDist(void){
	uint32_t capture[2];
	float diffCapture;
	float timeUs;
	float dist;
	uint32_t TIM2_CLK = SystemCoreClock;
	
	TIM6->CNT = 0;				//REINICIO DEL CONTADOR
	TIM6->SR = 0;
	/*generar un pulso de 10us*/
	GPIOB->BSRR |= 1U<<3;
	while(!(TIM6->SR & TIM_SR_UIF)); //delay
	GPIOB->BRR |= 1U<<3;
	TIM6->SR = 0;
	/*ESPERAR EL FLANCO DE DE SUBIDA*/
	TIM2->SR =0 ;
	while(!(TIM2->SR & TIM_SR_CC1IF));
	TIM2->SR &=~ TIM_SR_CC1IF;
	capture[0] = TIM2->CCR1;
	/*se espera el flanco de bajada*/
	while(!(TIM2->SR & TIM_SR_CC1IF));
	TIM2->SR &=~ TIM_SR_CC1IF;
	capture[1] = TIM2->CCR1;
	/*se calcula la diferencia de los valores leidos*/
	if(capture[1] >= capture[0]){
		diffCapture = capture[1] - capture[0];
	}
	else{
		diffCapture = TIM2->ARR - capture[0] + capture[1];
	}
	/*se calcula el tiempo del ancho de pulso en us*/
	timeUs = (diffCapture * ((float)(TIM2->PSC + 1)/TIM2_CLK)) * 1000000;
	/*Se calcula la distancia*/
	dist = timeUs / 58;
	/*ser retorna el valor calculado*/
	return dist;
}


/*ISR*/
void TIM6_IRQHandler(void){
	if(TIM6->SR & TIM_SR_UIF){
		TIM6->SR = 0;
		GPIOB->ODR ^=1<<3;
	}
	
}
