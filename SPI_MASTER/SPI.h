/**
  * @brief SPI.h
	* @version V1
	* @autor QUINO B. JEFFRY
	*/
	
#ifndef __SPI_H
#define __SPI_H

#include "stm32l4xx.h"                  // Device header

/*prototipo de funciones*/
/**
  * @brief configura los parametros de comunicacion SPI1
	*/
void SPI1_Config(void);


/**
  * @fn habilita el SPI1
  */
void SPI1_Enable(void);

/**
  * @fn deshabilita el SPI1
  */
void SPI1_Disable(void);

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
#endif /*__SPI_H*/
