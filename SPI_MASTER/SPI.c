/**
  * SPI.c
	*/
	
#include "SPI.h"

/**
  * @brief CONFIGURA LOS PINES SPI en su funcion alternativa
	* SPI1_MOSI	: PA7(AF5),PA12(AF5),PB5(AF5)
	* SPI1_MISO	: PA6(AF5),PA11(AF5),PB4(AF5)
	* SPI1_SCK	: PA1(AF5),PA5(AF5),PB3(AF5)
	* SPI1_NSS	: PA4(AF5),PA15(AF5),PB0(AF5)
	*/
static void SPI1_Pins_Config(void){
	/*enable clk*/
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
	//SPI1_MOSI -> PA7
	GPIOA->MODER &=~ GPIO_MODER_MODE7;
	GPIOA->MODER |= GPIO_MODER_MODE7_1;				//FUNCION ALTERNATIVA
	GPIOA->AFR[0] &=~ GPIO_AFRL_AFRL7;				//RESET
	GPIOA->AFR[0] |= 0x5U<<GPIO_AFRL_AFSEL7_Pos;//PA7-> SPI1_MOSI
	GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED7;		//very high speed
	//SPI1_MISO -> PA6
	GPIOA->MODER &=~ GPIO_MODER_MODE6;
	GPIOA->MODER |= GPIO_MODER_MODE6_1;				//FUNCION ALTERNATIVA
	GPIOA->AFR[0] &=~ GPIO_AFRL_AFRL6;
	GPIOA->AFR[0] |= 0x5U<<GPIO_AFRL_AFSEL6_Pos;
	GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED6;		//very high speed
	//SPI1_SCK -> PA1
	GPIOA->MODER &=~ GPIO_MODER_MODE1;
	GPIOA->MODER |= GPIO_MODER_MODE1_1;				//FUNCION ALTERNATIVA
	GPIOA->AFR[0] &=~ GPIO_AFRL_AFRL1;
	GPIOA->AFR[0] |= 0x5U<<GPIO_AFRL_AFSEL1_Pos;
	GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED1;		//very high speed
	//SPI1_NSS -> PA4
	GPIOA->MODER &=~ GPIO_MODER_MODE4;
	GPIOA->MODER |= GPIO_MODER_MODE4_1;				//FUNCION ALTERNATIVA
	GPIOA->AFR[0] &=~ GPIO_AFRL_AFRL4;
	GPIOA->AFR[0] |= 0x5U<<GPIO_AFRL_AFSEL4_Pos;
	GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED4;		//very high speed
}


/**
  * @brief configura los parametros de comunicacion SPI1
	*/
void SPI1_Config(void){
	/*1. configuramos los pines*/
	SPI1_Pins_Config();
	/*enble clk spi1*/
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
	/*2. configurar el registro CR1*/
	SPI1->CR1 = 0;
	//SPI1->CR1 |= SPI_CR1_CPOL;
	SPI1->CR1 |= SPI_CR1_SSI;
	SPI1->CR1 |= SPI_CR1_BR_2;				//FCLK / 32
	SPI1->CR1 |= SPI_CR1_MSTR;				//Master configuration
	/*3. Configurar el registro CR2*/
	SPI1->CR2 = 0;
	SPI1->CR2 |= 0x7U<<SPI_CR2_DS_Pos;	//8-BIT
	SPI1->CR2 |= SPI_CR2_SSOE;				//SS output is enabled in master mode and when the SPI interface is enabled
	SPI1->CR2 |= SPI_CR2_NSSP;
	SPI1->CR2 |= SPI_CR2_FRXTH; 			//RXNE -> 1/4(8-bit)
}


/**
  * @fn habilita el SPI1
  */
void SPI1_Enable(void){
	
	SPI1->CR1 |= SPI_CR1_SPE;
	return;
}


/**
  * @fn deshabilita el SPI1
  */
void SPI1_Disable(void){
	uint16_t temp;
	//1. Wait until FTLVL[1:0] = 00 (no more data to transmit).
	while(SPI1->SR & SPI_SR_FTLVL);
	//2. Wait until BSY=0 (the last data frame is processed).
	while(SPI1->SR & SPI_SR_BSY);
	//3.Disable the SPI (SPE=0).
	SPI1->CR1 &=~ SPI_CR1_SPE;
	//4. Read data until FRLVL[1:0] = 00 (read all the received data).
	while(SPI1->SR & SPI_SR_FRLVL){
		temp = SPI1->DR;
	}
	return;
}


/**
  * @fn Envia una serie de bytes por el SPI
	* @param[pTxBuffer]: buffer a enviar
	* @param[Len]: cantidad de datos a enviar
	*/
void SPI1_sendData(uint8_t *pTxBuffer, uint32_t Len){
	uint8_t temp;
	
	while(Len>0){

		//1. wait until TXE is set
		while(!(SPI1->SR & SPI_SR_TXE));
		//2. check the DS bit in CR2
		temp = (SPI1->CR2 >> 8) & 0xF;
		if(temp > 7){
			SPI1->DR =   *((uint16_t*)pTxBuffer);
			Len--;
			Len--;
			(uint16_t*)pTxBuffer++;
		}else{
			*((__IO uint8_t *)&SPI1->DR) =   *pTxBuffer;
			Len--;
			pTxBuffer +=1;
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
	uint8_t temp;
	while(Len>0){
		//1. wait until RXNE is set
		while(!(SPI1->SR & SPI_SR_RXNE));
		//2. check the DS bit in CR2
		temp = (SPI1->CR2 >>8) & 0xF;
		if(temp > 7){
			*((uint16_t*)pRxBuffer) = SPI1->DR ;
			Len--;
			Len--;
			(uint16_t*)pRxBuffer++;
		}
		else{
			*(pRxBuffer) = SPI1->DR ;
			Len--;
			pRxBuffer++;
		}
	}
	
	return;
}
