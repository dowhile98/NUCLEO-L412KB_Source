#include "stm32l4xx.h"                  // Device header
#include "arm_math.h"
#include "RCC.h"
#include "USART.h"
#include "Delay.h"
#include <stdio.h>
#include "signal.h"
#include "lowPassFir2k.h"


/**********MACRO DEFINES***/
#define BLOCKSIZE			K

/*****GLOBAL VARIABLES*****/
float32_t y[K];														//data filtrado
float32_t firStateF32[BLOCKSIZE + N -1];	//para las operaciones intermedias
uint32_t numCycles;												//cantidad de ciclos que tarda realizar el filtrado
float  timeProcess;												//cantidad de tiempo que tarda realizar el filtrado
float his[N];

arm_fir_instance_f32	S;

float32_t inputSample;
float32_t outputSample;

/***FUNCTION PROTOTYPE*****/
/**
  * @brief funcion filtro fir estructura directa
	* @param []
	* @return
	*/
float fir_filter(float input,float *h, int k, float *history);
/**
  * @brief envio de datos a labview
	* @param []
	* @return
	*/
void plot_signal(void);


int main(void){
	uint32_t i;
	/******PLL INIT**********/
	PLL_Config();
	/********Delay Init******/
	Delay_Init();
	/********USART2 INIT*****/
	USART2_Config(SystemCoreClock,USART_OVER8_16,115200);
	/*Filter init*/
	arm_fir_init_f32(&S,N,h,firStateF32,BLOCKSIZE);
	
	/*filtrado usando programado desde cero*/
	

//	/*filtrado usando la funcion de arm cmsis*/
//	arm_fir_f32(&S,Signal,y,BLOCKSIZE);
	
	while(1){
		/*filtrado usando programado desde cero*/
//		for(i = 0; i<K;i++){
//			y[i] = fir_filter(Signal[i],h,N,his);
//		}
		/*filtrado usando la funcion de arm cmsis*/
		arm_fir_f32(&S,Signal,y,BLOCKSIZE);
		plot_signal();
	}
}
float fir_filter(float input,float *h, int k, float *history){
   uint32_t i;
   float *hist_ptr, *hist1_ptr, *coef_ptr;
   float output;

   hist_ptr = history;
   hist1_ptr = hist_ptr;    //puntero actualizado
   coef_ptr = h + k - 1;    //puntero a los coeficientes
   /*inicio del algoritmo recursivo*/
   output = *hist_ptr++*(*coef_ptr--);
   for(i = 2; i<k; i++){
       *hist1_ptr++ = *hist_ptr;
       output += (*hist_ptr++)*(*coef_ptr--);
   }
    output += input * (*coef_ptr--);
    *hist1_ptr = input;     //se actualiza el history
    return (output);        //se devuelve la salida
}

void plot_signal(void){
	uint32_t i;
	for(i = 0;i<K ;i++){
		inputSample = Signal[i];
		outputSample = y[i];
		printf("%.2f\r\n",inputSample);
		printf("%.2f\r\n",outputSample);
		delay_ms(50);
	}
	
}