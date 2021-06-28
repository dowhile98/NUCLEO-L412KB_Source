//#include <stdint.h>

//#define RCC_BASE 	0x40021000UL
//#define RCC_CR    *((volatile uint32_t*)(RCC_BASE + 0x00))
//#define RCC_CFGR	*((volatile uint32_t*)(RCC_BASE + 0x08))	

//int main(void){
//	//volatile unsigned int *RCC_CR =(volatile unsigned int *)RCC_BASE;//esto es una opcion si no se quiere usar defines
		// *RCC_CR |= 1<<8;				//para modificar el contenido del registro
//	RCC_CR |= 1U<<8;
//	while(!(RCC_CR & 1<<10));
//	RCC_CFGR |= 0x1;
//	while(!(RCC_CFGR & 0x1<<2));
//	while(1){
//	}
//}
/*includes*/
#include "stm32l4xx.h"                  // Device header

/********prototipo de funciones***********/
/*Funciones que configuran los RCC*/
void MSI_Config(void);
void HSI16_Config(void);
void PLL_Config(void);

/*variables globales*/
uint32_t freq;													/*para monitorear la frecuencia del sysclk*/
/*funcion principal*/
int main(void){
	
	freq = SystemCoreClock;								/*se lee el valor inicial del rcc*/
	MSI_Config();													/*se configura el msi a 16MHz*/
	SystemCoreClockUpdate();							/*se actualiza el valor de la variable SystemCoreClock*/
	freq = SystemCoreClock;								/*se lee el nuevo valor de la frecuencia del sysclk*/
	
	PLL_Config();													/*PLL-> 80MHz*/
	SystemCoreClockUpdate();
	freq = SystemCoreClock;
	while(1){
		
	}
}

/*DEFINICION DE FUNCIONES*/
void MSI_Config(void){
	/*1. Habilitar*/
	RCC->CR |= RCC_CR_MSION;
	while(!(RCC->CR & RCC_CR_MSIRDY));
	/*configurar el rango*/
	RCC->CR &=~ (RCC_CR_MSIRANGE);
	RCC->CR |= 8<<4;
	RCC->CR |= RCC_CR_MSIRGSEL;
	/*seleccionar la fuente de reloj*/
	RCC->CFGR &=~ RCC_CFGR_SW;
}
void HSI16_Config(void){
	
	
}
/*configurar el pll a 80MHz*/
void PLL_Config(void){
	/*1. Deshabilitar el pll (RCC_CR)*/
	
	/*2. configurar la fuente de reloj del PLL (RCC_PLLCFGR)*/
	
	/*3. configurar los parametros del pll (RCC_PLLCFGR)*/
	//M
	//N
	//R
	/*4. Habilitar y esperar que el pll este listo (RCC_CR)*/
	
	/*5. Habilitar el bit PLLREN (RCC_PLLCFGR)*/
	
	/*6. opcional configurar los prescalers HHB, APBx (RCC_CFGR)*/
	
	/*7. configurar la latencia de la flash (FLASH_ACR)*/
	
	/*8. Seleccionar el reloj habilitado como la fuente del sistema (RCC_CFGR)*/
}
