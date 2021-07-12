#include "stm32f10x.h"                  // Device header
#include "USART.h"
#include <stdio.h>


/*variables glogales*/
uint32_t PCLK2;
uint32_t data;

int main(void){
	
	PCLK2 = SystemCoreClock;
	USART1_Config(PCLK2,115200);
	printf("CONFIGURACION USART1 EXITOSA\n\r");
	for(;;){
//		printf("ingrese un numero->");
//		scanf("%d",&data);
//		printf("se ingresó->%d\r\n",data);
	}
}



void USART1_IRQHandler(void){
	if(USART1->SR & USART_SR_RXNE){
		data = USART1->DR;
		printf("Se recibio (USART1)-> %c\n\r",data);
	}
}
