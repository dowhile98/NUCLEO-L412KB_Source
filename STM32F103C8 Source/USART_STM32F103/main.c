#include "stm32f10x.h"                  // Device header
#include "USART.h"
#include <stdio.h>


/*variables glogales*/
uint32_t PCLK2;
uint32_t data;

void delay_ms(uint32_t delay);


int main(void){
	
	PCLK2 = SystemCoreClock;
	USART1_Config(PCLK2,115200);
	printf("CONFIGURACION USART1 EXITOSA\n\r");
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	GPIOC->CRH &=~ (GPIO_CRH_CNF13 | GPIO_CRH_MODE13);
	GPIOC->CRH |= GPIO_CRH_MODE13;
	ITM_SendChar('h');
	for(;;){
//		printf("ingrese un numero->");
//		scanf("%d",&data);
//		printf("se ingresó->%d\r\n",data);
		GPIOC->ODR ^= 1<<13;
		delay_ms(100);
	}
	
}



void USART1_IRQHandler(void){
	if(USART1->SR & USART_SR_RXNE){
		data = USART1->DR;
		printf("Se recibio (USART1)-> %c\n\r",data);
	}
}

/*RETARDO*/
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
