#include "stm32l4xx.h"                  // Device header
#include "RCC.h"
#include "Delay.h"
#include "USART.h"
#include <stdio.h>
#include <string.h>
#include "SPI.h"

void BUTTON_Init(void);


int main(void){
	uint8_t dummy_write = 0xff;
	uint8_t dummy_read[4];
	char txt[] = "Hola mundo SPI1";
	uint8_t size;
	/*rcc config*/
	PLL_Config();
	/*delay init*/
	Delay_Init();
	/*usart2 init*/
	USART_Config(USART2,SystemCoreClock,USART_OVER8_8,115200);
	printf("configuracion exitosa\r\n");
	/*BUTTON*/
	BUTTON_Init();
	/****************SPI************************************/
	SPI1_Config();
	
	

	
	//deshabilita EL SPI1
	//lear
	SPI1_ReceiveData(dummy_read,3);
	
	
	
	
	while(1){
		//wait 1
		while(!(GPIOB->IDR >> 0 & 0x1));
		delay_ms(200);
		SPI1_Enable();
		//ENVIAR LA CANTIDAD 
		size = strlen(txt);
		SPI1_sendData(&size,1);
		//enviamdo el dato
		SPI1_sendData((uint8_t*)txt,strlen(txt));
		//deshabilitar el spi
		SPI1_Disable();
	}
}

void BUTTON_Init(void){
	//PB0 -> ENTRADA PULL DOWN
	/*enable clock*/
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
	GPIOB->MODER &=~ GPIO_MODER_MODE0;
	GPIOB->PUPDR &=~ GPIO_PUPDR_PUPD0;	
	GPIOB->PUPDR |= GPIO_PUPDR_PUPD0_1;	
}

