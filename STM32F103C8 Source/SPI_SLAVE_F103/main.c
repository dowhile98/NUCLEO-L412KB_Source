#include "stm32f10x.h"                  // Device header
#include "USART.h"
#include "Delay.h"
#include <stdio.h>
#include <string.h>

/*variables globales*/
uint8_t dataLen;
uint32_t i;
uint8_t dataBuff[500];

/**********PROTOTIPO DE FUNCIONES********/

/**
  * @fn CONFIGURA EL SPI1 en modo esclavo
	*/
void SPI1_Slave_Config(void);

/**
  * @fn Envia una serie de bytes por el SPI
	* @param[pTxBuffer]: buffer a enviar
	* @param[Len]: cantidad de datos a enviar
	*/
void SPI1_sendData(uint8_t *pTxBuffer, uint32_t Len);

/**
  * @fn recibe una serie de bytes por el SPI
	* @param[pTxBuffer]: buffer a recibir
	* @param[Len]: cantidad de datos a enviar
	*/
void SPI1_ReceiveData(uint8_t *pRxBuffer, uint32_t Len);

int main(void){
	/*delay init*/
	Delay_Init();
	/*USART1 init*/
	USART1_Config(SystemCoreClock,115200);
	
	
	/***********SPI Init*******************/
	SPI1_Slave_Config();
	/**************************************/
	printf("Configuracion exitosa\r\n");
	
	while(1){
		printf("Esclavo esperando que SS se estableca a 0\r\n");
		while(GPIOA->IDR & 1U<<4);
		SPI1_ReceiveData(&dataLen,1);
		SPI1_ReceiveData(dataBuff,dataLen);
		printf("Rcvd: %s\r\n",dataBuff);
		printf("Length: %d\r\n",dataLen);
	}
}

/**
  * @fn Configura los pines del SPI1
	* SPIx_SCK 	-> input floating																	(PA5)
  * SPIx_MOSI -> input floating																	(PA7)
  * SPIx_MISO -> Alternate function push-pull										(PA6)
  * SPIx_NSS  -> Input floating/ Input pull-up / Input pull-down(PA4)
  */
void SPI_Pins_Config(void){
	/*enable clock*/
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	//PA5->SCK
	GPIOA->CRL &=~ (GPIO_CRL_CNF5 | GPIO_CRL_MODE5);
	GPIOA->CRL |= GPIO_CRL_CNF5_0;
	//PA7->MOSI
	GPIOA->CRL &=~ (GPIO_CRL_CNF7 | GPIO_CRL_MODE7);
	GPIOA->CRL |= GPIO_CRL_CNF7_0;
	//PA6->MISO
	GPIOA->CRL &=~ (GPIO_CRL_CNF6 | GPIO_CRL_MODE6);
	GPIOA->CRL |= GPIO_CRL_CNF6_1 | GPIO_CRL_MODE6;
	//PA4->NSS
	GPIOA->CRL &=~ (GPIO_CRL_CNF4 | GPIO_CRL_MODE4);
	GPIOA->CRL |= GPIO_CRL_CNF4_0;
}

/**
  * @fn CONFIGURA EL SPI1 en modo esclavo
	*/
void SPI1_Slave_Config(void){
	/*pin config*/
	SPI_Pins_Config();
	/*enable clock*/
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
	/*SPI parameter config*/
	/*1. configurar el formato de datos DFF*/
	SPI1->CR1 &=~ SPI_CR1_DFF;						//8-Bit
	/*2. Seleccionar CPOL y CPHA*/
	SPI1->CR1 &=~ (SPI_CR1_CPHA | SPI_CR1_CPOL);
	//SPI1->CR1 |= SPI_CR1_CPOL;
	/*3. el formato de la trama (MSB first, LSB first)*/
	SPI1->CR1 &=~ (SPI_CR1_LSBFIRST);
	/*4. configurar la gestion del pin NSS*/
	SPI1->CR1 &=~ SPI_CR1_SSM;						//hardware
	/*5. clear the MSTR Bit*/
	SPI1->CR1 &=~ SPI_CR1_MSTR;						//slave
	/*6. habilitar el SPI*/
	SPI1->CR1 |= SPI_CR1_SPE;
}


/**
  * @fn Envia una serie de bytes por el SPI
	* @param[pTxBuffer]: buffer a enviar
	* @param[Len]: cantidad de datos a enviar
	*/
void SPI1_sendData(uint8_t *pTxBuffer, uint32_t Len){
	
	while(Len>0){
		//1. wait until TXE is set
		while(!(SPI1->SR & SPI_SR_TXE));
		//2. check the DFF
		if(SPI1->CR1 & SPI_CR1_DFF){
			SPI1->DR =   *((uint16_t*)pTxBuffer);
			Len--;
			Len--;
			(uint16_t*)pTxBuffer++;
		}else{
			*((__IO uint8_t *)&SPI1->DR) =   *pTxBuffer;
			Len--;
			pTxBuffer++;
		}
	}
	
	return;
}

/**
  * @fn recibe una serie de bytes por el SPI
	* @param[pTxBuffer]: buffer a recibir
	* @param[Len]: cantidad de datos a enviar
	*/
void SPI1_ReceiveData(uint8_t *pRxBuffer, uint32_t Len){
	while(Len>0){
		//1. wait until RXNE is set
		while(!(SPI1->SR & SPI_SR_RXNE));
		//2. check the DFF
		if(SPI1->CR1 & SPI_CR1_DFF){
			*((uint16_t*)pRxBuffer) = SPI1->DR ;
			Len--;
			Len--;
			(uint16_t*)pRxBuffer++;
		}
		else{
			*(pRxBuffer) = *((__IO uint8_t *)&SPI1->DR) ;
			Len--;
			pRxBuffer++;
		}
	}
	
	return;
}

