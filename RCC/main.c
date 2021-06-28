//#include <stdint.h>

//#define RCC_BASE 	0x40021000UL
//#define RCC_CR    *((volatile uint32_t*)(RCC_BASE + 0x00))
//#define RCC_CFGR	*((volatile uint32_t*)(RCC_BASE + 0x08))	

//int main(void){
//	//volatile unsigned long *RCC_CR =main (volatile unsigned long *)RCC_BASE;
//	RCC_CR |= 1U<<8;
//	while(!(RCC_CR & 1<<10));
//	RCC_CFGR |= 0x1;
//	while(!(RCC_CFGR & 0x1<<2));
//	while(1){
//	}
//}
#include "stm32l4xx.h"                  // Device header

void MSI_Config(void);
void HSI16_Config(void);
void PLL_Config(void);

uint32_t freq;

int main(void){
	freq = SystemCoreClock;
	MSI_Config();
	SystemCoreClockUpdate();
	freq = SystemCoreClock;
	
	PLL_Config();
	SystemCoreClockUpdate();
	freq = SystemCoreClock;
	while(1){
		
	}
}

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
