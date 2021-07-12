#include "stm32l4xx.h"                  // Device header
#include "RCC.h"
#include "USART.h"
#include <stdio.h>

/*VARIABLES GLOBALES*/
uint32_t fck;
char data;
/*PROTOTIPO DE FUNCIONES*/

int main(void){
	MSI_ConfigRange(MSI_RANGE9_24MHz);
	/*seleccionar la fuente de reloj del usart1*/
//	RCC->CCIPR |= RCC_CCIPR_USART1SEL;
	fck = SystemCoreClock;
	USART1_Config(fck,USART_OVER8_16,115200);
	printf("CONFIGURACION DEL USART1 EXITOSA\n\r");
	
	while(1){
		
	}
}

/*DEFINICION DE FUNCIONES*/
void  USART1_IRQHandler(void){
	if(USART1->ISR & USART_ISR_RXNE){
		data = USART1->RDR;
		printf("se recibio->%c\r\n",data);
	}
}
