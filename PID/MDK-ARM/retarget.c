#include <stdio.h>
#include "stm32l4xx_hal.h"

extern UART_HandleTypeDef huart2;

struct __FILE
{
  int dummyVar; //Just for the sake of redefining __FILE, we won't we using it anyways ;)
};

FILE __stdout;
FILE __stdin;

int fputc(int c, FILE * stream)
{
	uint8_t ch = c & 0xFF;
	HAL_UART_Transmit(&huart2,&ch,1,1);
	return c; //return the character written to denote a successfull write
}

int fgetc(FILE * stream)
{
	uint8_t c;
	HAL_UART_Receive(&huart2,&c,1,1);
//	uartWrite(c); //To echo Received characters back to serial Terminal
	return c;
}
