/** 
  * @autor QUINO B. JEFFRY
	* @verion V.10
	*/
	
#include "I2C.h"

/*FUNCIONES PRIVADAS*/
/**
  * @fn establece la condicion de inicio (start)
	*/
void I2C_Start(I2C_TypeDef * I2Cx, uint32_t devAddress,uint8_t size,uint8_t Direction){
	
	uint32_t tempreg = I2Cx->CR2;
	
	tempreg &= (uint32_t)~((uint32_t)(I2C_CR2_SADD | I2C_CR2_NBYTES | \
																		I2C_CR2_RELOAD | I2C_CR2_AUTOEND | \
																		I2C_CR2_RD_WRN | I2C_CR2_START 	| \
																		I2C_CR2_STOP));
	/*se comprueba la direccion de la transferencia*/
	if( Direction == READ_FROM_SLAVE){
		tempreg |= I2C_CR2_RD_WRN;				//read from slave
	}
	else if ( Direction == WRITE_TO_SLAVE){
		tempreg &=~ I2C_CR2_RD_WRN;
	}
	
	/*se establece los parametros*/
	tempreg |= (uint32_t)(((uint32_t)devAddress & I2C_CR2_SADD ) | \
											 (((uint32_t)size<<16) & I2C_CR2_NBYTES));
	tempreg |= I2C_CR2_START;
	
	/*set CR2*/
	I2Cx->CR2 = tempreg;
	
	return;
}

/**
  * @fn generacion de la condicion de parada
  */
void I2C_Stop(I2C_TypeDef * I2Cx){
	/*master: generate STOP bit after current byte has been transfered*/
	I2Cx->CR2 |= I2C_CR2_STOP;
	
	/*wait until STOPF flag is reset*/
	while(!(I2Cx->ISR & I2C_ISR_STOPF));
	
	/*clear flag*/
	I2Cx->ICR |= I2C_ICR_STOPCF;
	
	return;
}
/**
  * @fn funcion que espera mientras que al linea I2C está ocupada
  */
void I2C_WaitLineIdle(I2C_TypeDef *I2Cx){
	/*wait until I2C bus is ready*/
	while((I2Cx->ISR & I2C_ISR_BUSY) == I2C_ISR_BUSY);
	
	return;
}

/**
  * @fn funcion que envia bytes por el I2C
  * @param SalaveAddress: direccion del esclavo
  * @param pData: puntero a los datos a transferir
  * @param Size: cantidad de bytes a transferir
  */
int8_t I2C_SendData(I2C_TypeDef *I2Cx,uint8_t SlaveAddress, uint8_t *pData, uint8_t Size){
	/*verificar los datos*/
	if( Size <= 0 || pData == NULL)
		return -1;
	/*esperar que la linea esté libre*/
	I2C_WaitLineIdle(I2Cx);
	
	/*iniciar la transmision*/
	I2C_Start(I2Cx,SlaveAddress,Size,WRITE_TO_SLAVE);
	
	while(Size>0){
		/*wait*/
		//while((I2Cx->ISR & I2C_ISR_TXIS) == 0);
		while(!(I2Cx->ISR & I2C_ISR_TXE));
		/*send*/
		I2Cx->TXDR = *pData & I2C_TXDR_TXDATA;
		pData++;
		Size--;
	}
	/*espera hasta que el TC se establesca*/
	while((I2Cx->ISR & I2C_ISR_TC) == 0 && ( I2Cx->ISR & I2C_ISR_NACKF) == 0);
	
	if((I2Cx->ISR & I2C_ISR_NACKF) != 0)
		return -1;
	/*stop*/
	I2C_Stop(I2Cx);
	
	return 0;
}

/**
  * @fn recibe bytes por el I2C
  * @param SalaveAddress: direccion del esclavo
  * @param pData: puntero para recibir datos
  * @param Size: cantidad de bytes a transferir	
	*/
int8_t I2C_ReceiveData(I2C_TypeDef *I2Cx,uint8_t SlaveAddress, uint8_t *pData, uint8_t Size){
	/*verificar los datos*/
	if( Size <= 0 || pData == NULL)
		return -1;
	
	/*esperar que la linea esté libre*/
	I2C_WaitLineIdle(I2Cx);
	
	/*inicia la comunicacion*/
	I2C_Start(I2Cx,SlaveAddress,Size, READ_FROM_SLAVE);
	
	/*transmit*/
	while(Size>0){
		/*wait*/
		while((I2Cx->ISR & I2C_ISR_RXNE) == 0);
		*pData = I2Cx->RXDR & I2C_RXDR_RXDATA;
		pData++;
		Size--;
	}
	/*wait*/
	while((I2Cx->ISR & I2C_ISR_TC) == 0); //wait until TCR flag is set
	
	/*stop*/
	I2C_Stop(I2Cx);
	
	
	return 0;
}
/**
  * @fn configura los pines para el I2C1
	* @note :
	* PA9  	-> I2C1_SCL (AF4)
	* PA10 	-> I2C1_SDA (AF4)
	* PB6 	-> I2C1_SCL (AF4)
	* PB7		-> I2C1_SDA (AF4)
	*/
static void I2C1_Pins_Config(void){
	/*enable clock*/
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
	//PB6
	GPIOB->MODER &=~ GPIO_MODER_MODE6;
	GPIOB->MODER 	|= GPIO_MODER_MODE6_1;			//Alternate function mode
	GPIOB->OTYPER |= GPIO_OTYPER_OT6;					//Output open-drain
	GPIOB->PUPDR &=~ GPIO_PUPDR_PUPD6;
	GPIOB->PUPDR |= GPIO_PUPDR_PUPD6_0;				//Pull-up
	GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR6;
	GPIOB->AFR[0] &=~ GPIO_AFRL_AFRL6;
	GPIOB->AFR[0] |= 0x4U<<GPIO_AFRL_AFSEL6_Pos;
	//PB7
	GPIOB->MODER &=~ GPIO_MODER_MODE7;
	GPIOB->MODER 	|= GPIO_MODER_MODE7_1;			//Alternate function mode
	GPIOB->OTYPER |= GPIO_OTYPER_OT7;					//Output open-drain
	GPIOB->PUPDR &=~ GPIO_PUPDR_PUPD7;
	GPIOB->PUPDR |= GPIO_PUPDR_PUPD7_0;				//Pull-up
	GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR7;
	GPIOB->AFR[0] &=~ GPIO_AFRL_AFRL7;
	GPIOB->AFR[0] |= 0x4U<<GPIO_AFRL_AFSEL7_Pos;
	return;
}

/**
  * @fn configura los pines para el I2C1
	* @note :
	* PA7  	-> I2C3_SCL (AF4)
	* PB4 	-> I2C3_SDA (AF4)
	*/
static void I2C3_Pins_Config(void){
	/*enable clock*/
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
	//PA7
	GPIOA->MODER &=~ GPIO_MODER_MODE7;
	GPIOA->MODER 	|= GPIO_MODER_MODE7_1;			//Alternate function mode
	GPIOA->OTYPER |= GPIO_OTYPER_OT7;					//Output open-drain
	GPIOA->PUPDR &=~ GPIO_PUPDR_PUPD7;
	GPIOA->PUPDR |= GPIO_PUPDR_PUPD7_0;				//Pull-up
	GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR7;
	GPIOA->AFR[0] &=~ GPIO_AFRL_AFRL7;
	GPIOA->AFR[0] |= 0x4U<<GPIO_AFRL_AFSEL7_Pos;
	//PB4
	GPIOB->MODER &=~ GPIO_MODER_MODE4;
	GPIOB->MODER 	|= GPIO_MODER_MODE4_1;			//Alternate function mode
	GPIOB->OTYPER |= GPIO_OTYPER_OT4;					//Output open-drain
	GPIOB->PUPDR &=~ GPIO_PUPDR_PUPD4;
	GPIOB->PUPDR |= GPIO_PUPDR_PUPD4_0;				//Pull-up
	GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR4;
	GPIOB->AFR[0] &=~ GPIO_AFRL_AFRL4;
	GPIOB->AFR[0] |= 0x4U<<GPIO_AFRL_AFSEL4_Pos;
	return;
}

/************************************************************/
/**
  * @fn IC2_Config
	* @brief configura el I2Cx
	* @param I2Cx: I2C1/I2C3 que se quiera configurar
	*/
void I2C_Config(I2C_TypeDef * I2Cx){
	uint32_t OwnAddr = 0x52U;
	/*CLOCK AND PINOUT CONFIG*/
	if(I2Cx == I2C1){
		RCC->APB1ENR1 |= RCC_APB1ENR1_I2C1EN;
		I2C1_Pins_Config();
	}
	else if(I2Cx == I2C3){
		RCC->APB1ENR1 |= RCC_APB1ENR1_I2C3EN;
		I2C3_Pins_Config();
	}else{
		while(1);	//error
	}
	/*Clear PE bit in I2C_CR1*/
	I2Cx->CR1 &=~ I2C_CR1_PE;
	/*Configure ANFOFF and DNF[3:0] in I2C_CR1*/
	I2Cx->CR1 &=~ I2C_CR1_ANFOFF;					//analog filter enable
	I2Cx->CR1 &=~ I2C_CR1_DNF;						//digital filter disabled
	I2Cx->CR1 &=~ I2C_CR1_SMBDEN;					//I2C Mode
	I2Cx->CR1 &=~ I2C_CR1_NOSTRETCH;			//enable clock stretching
	/*Configure PRESC[3:0],SDADEL[3:0], SCLDEL[3:0], SCLH[7:0],
	SCLL[7:0]  in I2C_TIMINGR*/
	I2Cx->TIMINGR = 0;
	I2Cx->TIMINGR |= 7U<<I2C_TIMINGR_PRESC_Pos; //PRESC = 7;
	I2Cx->TIMINGR |= 49U<<I2C_TIMINGR_SCLL_Pos;	//SCLL: SCL low period(master mode) > 4.7us
	I2Cx->TIMINGR |= 49U<<I2C_TIMINGR_SCLH_Pos; //SCLH: SCL high period(master mode) > 4.0us
	I2Cx->TIMINGR |= 14U<<I2C_TIMINGR_SCLDEL_Pos;//SCLDEL: Data setup time > 1.0us
	I2Cx->TIMINGR |= 15U<<I2C_TIMINGR_SDADEL_Pos;//SDADEL: Data hold time > 1.25us
	
	/*I2C Own address 1 register (I2C_OAR1)*/
	I2Cx->OAR1 &=~ I2C_OAR1_OA1EN;
	I2Cx->OAR1 = I2C_OAR1_OA1EN | OwnAddr;				//7bit own address
	I2Cx->OAR2 &=~ I2C_OAR2_OA2EN;								//disable own addres 2
	
	/*I2C CR2 Configuration*/
	I2Cx->CR2 &=~ I2C_CR2_ADD10;									//ADDR -> 7-bit
	I2Cx->CR2 |= I2C_CR2_AUTOEND;									//ENABLE the auto end
	I2Cx->CR2 |= I2C_CR2_NACK;										//For slave mode: set NACK
	/*Set PE bit in I2C_CR1*/
	I2Cx->CR1 |= I2C_CR1_PE;											//enable I2Cx 
	return;
}
