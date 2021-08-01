
/**
  * SPI.c
	*/ 

#include "SPI.h"


/************FUNCIONES PRIVADAS********************/

/**
  * @fn configura los pines del SPI1
	* SPI1_NSS -> PA4
	* SPI1_SCK -> PA5
	* SPI1_MISO -> PA6
	* SPI1_MOSI -> PA7 (AF5)
  */
void SPI1_Pins_Config(void){
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	//NSS
	GPIOA->MODER &=~ GPIO_MODER_MODE4;
	GPIOA->MODER |= GPIO_MODER_MODE4_1;
	GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED4;
	GPIOA->AFR[0] &=~ GPIO_AFRL_AFSEL4;
	GPIOA->AFR[0] |= 0x5U<<GPIO_AFRL_AFSEL4_Pos;
	//SCK
	GPIOA->MODER &=~ GPIO_MODER_MODE5;
	GPIOA->MODER |= GPIO_MODER_MODE5_1;
	GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED5;
	GPIOA->AFR[0] &=~ GPIO_AFRL_AFSEL5;
	GPIOA->AFR[0] |= 0x5U<<GPIO_AFRL_AFSEL5_Pos;
	//MISO
	GPIOA->MODER &=~ GPIO_MODER_MODE6;
	GPIOA->MODER |= GPIO_MODER_MODE6_1;
	GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED6;
	GPIOA->AFR[0] &=~ GPIO_AFRL_AFSEL6;
	GPIOA->AFR[0] |= 0x5U<<GPIO_AFRL_AFSEL6_Pos;
	//MOSI
	GPIOA->MODER &=~ GPIO_MODER_MODE7;
	GPIOA->MODER |= GPIO_MODER_MODE7_1;
	GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED7;
	GPIOA->AFR[0] &=~ GPIO_AFRL_AFSEL7;
	GPIOA->AFR[0] |= 0x5U<<GPIO_AFRL_AFSEL7_Pos;
	return;
}


/**
  * @fn CONFIGURA EL SPI1 EN MODO ESCLAVO
  */
void SPI1_Slave_Config(void){
	/*PIN INIT*/
	SPI1_Pins_Config();
	
	/*ENABLE CLOCK*/
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
	/*CONFIG SLAVE MODE*/
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
	return;
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

/**
  * habilita el spi1
	*/
void SPI1_Enable(void){
	
	SPI1->CR1 |= SPI_CR1_SPE;
	return;
}


/**
  * deshabilita el spi1
	*/
void SPI1_Disable(void){
	uint8_t temp;
	while(!(SPI1->SR & SPI_SR_RXNE));
	temp = SPI1->DR;
	
	while(!(SPI1->SR & SPI_SR_TXE));
	
	while(SPI1->SR & SPI_SR_BSY);
	
	SPI1->CR1 &=~ SPI_CR1_SPE;
}

