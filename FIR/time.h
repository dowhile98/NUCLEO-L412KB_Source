#include "stm32l4xx.h"                  // Device header

#include "core_cm4.h"


void startTiming(void){
	CoreDebug->DEMCR |= 1U<<24;			// Enable the DWT unit
	DWT->CTRL  |= 1;								// Enable the cycle counter	
	DWT->CYCCNT = 0;
}

uint32_t StopTiming(void){
	return DWT->CYCCNT;
}

float calculateTime(uint32_t cycle, uint32_t freq){
	return((float)cycle/freq);
}
