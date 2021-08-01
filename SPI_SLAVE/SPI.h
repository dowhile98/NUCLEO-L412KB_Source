/**
  * @autor QUINO B. Jeffry
	* @version V 1.0
	*/
	
	
#ifndef  __SPI_H
#define __SPI_H


/*includes*/
#include "stm32f4xx.h"                  // Device header

/*macros*/


/*prototip de funciones*/

/**
  * @fn CONFIGURA EL SPI1 EN MODO ESCLAVO
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


/**
  * habilita el spi1
	*/
void SPI1_Enable(void);


/**
  * deshabilita el spi1
	*/
void SPI1_Disable(void);


#endif /*__SPI_H*/

