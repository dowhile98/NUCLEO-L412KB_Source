/**
  * en este proyecto se configura el SPI1 en modo maestro
	* envia y recibe datos
	*/
#include "stm32l4xx.h"                  // Device header
#include "RCC.h"
#include "Delay.h"
#include "USART.h"
#include <stdio.h>
#include <string.h>
#include "SPI.h"

/********************MACROS*****/
#define COMMAND_LED_CTRL      		0x50
#define COMMAND_PRINT      				0x53
#define NACK 											0xA5
#define ACK 											0xF5
#define LED_ON     								1
#define LED_OFF    								0


void BUTTON_Init(void);
uint8_t size;

int main(void){
	uint8_t dummy_write = 0xff;
	uint8_t dummy_read[3];
	uint8_t data;
	uint8_t txt[] = "Mensaje de la NUCLEO-L412KB a NUCLEO-F401";

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
	
  /******************************************************/	
	while(1){
		//wait 1
		while(!(GPIOB->IDR >> 0 & 0x1));
		delay_ms(300);
		SPI1_Enable();
		/*se establece el comando*/
		data = COMMAND_LED_CTRL;
		SPI1_sendData(&data,1);							//envia el comando al esclavo
		SPI1_ReceiveData(dummy_read,1); 		//borra el bir RXNE
		//*se espera que el esclavo procese*/
		delay_ms(1);
		/*se envia el byte ficticio para recibir*/
		SPI1_sendData(&dummy_write,1); 	
		/*se lee byte recibido*/
		SPI1_ReceiveData(&data,1);
		printf("Confirmacion del esclavo->%X\r\n",data);
		delay_ms(1);

		data = LED_ON;
		SPI1_sendData(&data,1);
		
//		if(data == ACK){
//			data = LED_ON;
//			SPI1_sendData(&data,1);
//		}
		
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

