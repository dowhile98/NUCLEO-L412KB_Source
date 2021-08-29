/** 
  * @autor QUINO B. JEFFRY
	* @verion V.10
	*/
	
#ifndef __I2C_H
#define __I2C_H

/*INCLUDES*/
#include "stm32l4xx.h"                  // Device header
#include <stdio.h>
/*DEFINES*/
/*
 *Handle structure for I2Cx peripheral
 */
typedef struct
{
	I2C_TypeDef 	*pI2Cx;
	uint8_t 			*pTxBuffer; /* !< To store the app. Tx buffer address > */
	uint8_t 			*pRxBuffer;	/* !< To store the app. Rx buffer address > */
	uint32_t 			TxLen;		/* !< To store Tx len > */
	uint32_t 			RxLen;		/* !< To store Tx len > */
	uint8_t 			TxRxState;	/* !< To store Communication state > */
	uint8_t 			DevAddr;	/* !< To store slave/device address > */
  uint32_t      RxSize;		/* !< To store Rx size  > */
  uint8_t       Sr;			/* !< To store repeated start value  > */
}I2C_Handle_t;

/*
 * I2C application states
 */
#define I2C_READY 						0U
#define I2C_BUSY_IN_RX 				1U
#define I2C_BUSY_IN_TX 				2U

#define READ_FROM_SLAVE				1U
#define WRITE_TO_SLAVE				0U

/*PROTOTIPO DE FUNCIONES*/
/**
  * @fn IC2_Config
	* @brief configura el I2Cx
	* @param I2Cx: I2C1/I2C2 que se quiera configurar
	*/
void I2C_Config(I2C_TypeDef * I2Cx);

/**
  * @fn establece la condicion de inicio (start)
	* @param I2Cx: I2C1/I2C3 que se quiera dar inicio 
	* @param devAddress: Slave address (master mode)
	* @param size: cantidad de bytes a transmitir/recibir
	* @param Direction: Transfer direction (master mode)
	*/
void I2C_Start(I2C_TypeDef * I2Cx, uint32_t devAddress,uint8_t size,uint8_t Direction);


/**
  * @fn generacion de la condicion de parada
  */
void I2C_Stop(I2C_TypeDef * I2Cx);

/**
  * @fn funcion que espera mientras que al linea I2C está ocupada
  */
void I2C_WaitLineIdle(I2C_TypeDef * I2Cx);

/**
  * @fn funcion que envia bytes por el I2C
  * @param SalaveAddress: direccion del esclavo
  * @param pData: puntero a los datos a transferir
  * @param Size: cantidad de bytes a transferir
  */
int8_t I2C_SendData(I2C_TypeDef *I2Cx,uint8_t SlaveAddress, uint8_t *pData, uint8_t Size);

/**
  * @fn recibe bytes por el I2C
  * @param SalaveAddress: direccion del esclavo
  * @param pData: puntero para recibir datos
  * @param Size: cantidad de bytes a transferir	
	*/
int8_t I2C_ReceiveData(I2C_TypeDef *I2Cx,uint8_t SlaveAddress, uint8_t *pData, uint8_t Size);
#endif /*__I2C_H*/

