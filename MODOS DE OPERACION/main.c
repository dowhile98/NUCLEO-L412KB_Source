#include "stm32f4xx.h"                  // Device header
#include <stdio.h>

/******************MACROS***********************************/

#define STIR		(*(volatile uint32_t*)(0xE000EF00))
#define ISER0		(*(volatile uint32_t*)(0xE000E100))

/*********************FUNCIONES****************************/
/* This function executes in THREAD MODE of the processor */
void generate_interrupt(void){
	//ENABLE IRQ3 interrupt
	ISER0 |= 1<<3;
	//generate an interrupt from software for IRQ3
	STIR |= (3 & 0x1FF);
}

void change_access_level_unpriv(void){
	//read
	__asm volatile("MRS R0,CONTROL");
	//modify
	__asm volatile ("ORR R0,R0,#0x01");
	//write
	__asm volatile ("MSR CONTROL,R0");
}


/* This function executes in THREAD MODE+ PRIV ACCESS LEVEL of the processor */
int main(void){
	printf("In thread mode : before interrupt\n");
	change_access_level_unpriv();
	generate_interrupt();
	printf("In thread mode : after interrupt\n");
	while(1){
		
	}
}

/***********************ISR*************************************/

/* This function(ISR) executes in HANDLER MODE of the processor */
void RTC_WKUP_IRQHandler(void)
{
	printf("In handler mode : ISR\n");
}

void HardFault_Handler(void)
{
	printf("Hard fault detected\n");
	while(1); 
}
