/**
  * En este proyecto se configura el SPI1 en modo esclavo
	* El esclavo recibe y envia
	* PA9 -> LED
	*/

#include "stm32f4xx.h"                  // Device header
#include "USART.h"
#include <stdio.h>
#include "SPI.h"

/*macros*/
#define NACK 											0xA5
#define ACK 											0xF5
#define COMMAND_LED_CTRL          0x50
#define COMMAND_PRINT           	0x53
#define LED_ON     1
#define LED_OFF    0


/*variables globales*/
uint8_t dataLen;
uint32_t i;
uint8_t dataBuff[500];
uint8_t data, command, len, ackornack,dummy_read;



uint8_t checkData(uint8_t commnad)
{
  //todo
  return ACK;
}


int main(void){
	
	/*usart init*/
	USART_Config(USART2,SystemCoreClock,115200,USART_OVER8_1);
	
	/***********SPI*****************/
	SPI1_Slave_Config();
	/*******************************/
	//pa9 -> led
	RCC->AHB1ENR |=  RCC_AHB1ENR_GPIOAEN;
	GPIOA->MODER &=~ GPIO_MODER_MODE9;
	GPIOA->MODER |= GPIO_MODER_MODE9_0;
	
	printf("CONFIGURACION EXITOSA\r\n");
	
	while(1){
		//SPI1_Enable();
		printf("\nEsclavo esperando que SS se estableca a 0\r\n");
		while(GPIOA->IDR & 1U<<4);
//		SPI1_ReceiveData(&dataLen,1);
//		SPI1_ReceiveData(dataBuff,dataLen);
//		printf("Rcvd: %s\r\n",dataBuff);
//		printf("Length: %d\r\n",dataLen);
		
		/*esclavo recibe el comando*/
		SPI1_ReceiveData(&command,1);
		printf("Comando-> %x\r\n",command);
		ackornack = checkData(command);
		/*se envia la confirmacion al maestro*/
		SPI1_sendData(&ackornack,1);
		/*se borra el RXNE*/
		SPI1_ReceiveData(&dummy_read,1);  //dummy byte (borrar RXNE)
		printf("confirmacion-> %x\r\n",ackornack);
		
		
		
		//Se verifica el comando
		if(command == COMMAND_LED_CTRL){
			SPI1_ReceiveData(&data,1);
			printf("Instruccion->%X\r\n",data);
			if(data == LED_ON){
				GPIOA->BSRR |= 1U<<9;
				printf("led encendido\r\n");
			}else if(data == LED_OFF){
				printf("led apagado\r\n");
				GPIOA->BSRR |= 1U<<(16+ 9);
			}
		}
		
		//SPI1_Disable();
		
		
	}
}
