/**
  * main.c
	*/

/*includes*/
#include "stm32l4xx.h"                  // Device header
#include "I2C.h"
#include "RCC.h"
#include "Delay.h"
#include <string.h>
#include "MPU6050.h"

/*MACROS*/
#define SLAVE_ADDR  0x68<<1


/*VARIABLES GLOBALES*/
uint8_t some_data[] = "We are testing I2C master Tx\n";
uint8_t pRxBuffer[100];


RawData_Def myAccelRaw, myGyroRaw;
ScaledData_Def myAccelScaled, myGyroScaled;

/*PROTOTIPO DE FUNCIONES*/
/**
  * @fn configura los pines necesarios
	*/
void GPIO_Config(void);
/**
  * @brief configura el MPU6050
	*/
void MPU6050_Init_Config(void);



int main(void){
	
	
	/*RCC*/
	PLL_Config();
	/*DELAY*/
	Delay_Init();
	/*I2C*/
	I2C_Config(I2C3);
	
	//I2C_SendData(I2C3,SLAVE_ADDR,some_data,strlen((char*)some_data));
	
	/************************************/
	GPIO_Config();
	

	MPU6050_Init_Config();

	
	GPIOB->ODR |= 1U<<3;
	for(;;){
		
		
		MPU6050_Get_Accel_Scale(&myAccelScaled);
	  MPU6050_Get_Gyro_Scale(&myGyroScaled);

		GPIOB->ODR ^=1u<<3;
		delay_ms(100);
	}
}

/*definicion de funciones*/
/**
  * @fn configura los pines necesarios
	*/
void GPIO_Config(void){
	/*PB3 -> SALIDA*/
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
	GPIOB->MODER &=~ GPIO_MODER_MODE3;
	GPIOB->MODER |= GPIO_MODER_MODE3_0;
	/*PB0 -> ENTRADA*/
	GPIOB->MODER &=~ GPIO_MODER_MODE0;
	GPIOB->PUPDR &=~ GPIO_PUPDR_PUPD0;	
	GPIOB->PUPDR |= GPIO_PUPDR_PUPD0_1;
	return;
}


void MPU6050_Init_Config(void){
	MPU_ConfigTypeDef MPU_init = {0};
	MPU_init.ClockSource = Internal_8MHz;
	MPU_init.Gyro_Full_Scale = AFS_SEL_2g;
	MPU_init.CONFIG_DLPF = DLPF_184A_188G_Hz;
	MPU_init.Gyro_Full_Scale =  FS_SEL_500;
	MPU_init.Sleep_Mode_Bit = 0;

	MPU6050_Init(I2C3);
	//se inicializan los parametros del MPU
	MPU6050_Config(&MPU_init);
}


