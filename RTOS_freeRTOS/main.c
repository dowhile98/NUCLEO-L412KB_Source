#include "stm32l4xx.h"                  // Device header
#include "FreeRTOS.h"
#include "task.h"
#include "USART.h"
#include "Delay.h"
#include <stdio.h>
#include "semphr.h"


TaskHandle_t task1Handle;
TaskHandle_t task2Handle;

SemaphoreHandle_t semPtr = NULL;

/*prototipo de las funciones*/
void task1(void *param);
void task2(void *param);

void GPIO_Config(void);

int main(void){
	uint8_t status;
	
	USART2_Config(SystemCoreClock,USART_OVER8_8,9600);
	printf("configuracion exitosa\r\n");
	Delay_Init();
	GPIO_Config();
	/************************************************/
	
	semPtr = xSemaphoreCreateBinary();
	
	
	
	status = xTaskCreate(task1,"Task-1",configMINIMAL_STACK_SIZE,"tarea 1\r\n",2,&task1Handle);
	configASSERT(status == pdPASS);
	
	status = xTaskCreate(task2,"Task-2",configMINIMAL_STACK_SIZE,"tarea 2\r\n",2,&task1Handle);
	configASSERT(status == pdPASS);
	
	/*iniciarlizar el kernel*/
	vTaskStartScheduler();
	
	while(1){
		//
		
	}
}


void task1(void *param){
	while(1){
//		printf("tarea 1\r\n");
//		vTaskDelay(pdMS_TO_TICKS(100));
//		delay_ms(300);
//		taskYIELD();
		if(GPIOB->IDR & 1){
			vTaskDelay(pdMS_TO_TICKS(200));
			xSemaphoreGive(semPtr);
		}
	}
}
void task2(void *param){
	while(1){
//		printf("tarea 2\r\n");
//		vTaskDelay(pdMS_TO_TICKS(500));
//		delay_ms(500);
//		taskYIELD();

		if(xSemaphoreTake(semPtr,pdMS_TO_TICKS(5000))){
			GPIOB->BSRR |= 1u<<3;
			printf("semaforo recibido\r\n");
		}
		else{
			GPIOB->BRR |= 1u<<3;
			printf("semaforo no recibido\r\n");
		}
	}
	
}

void GPIO_Config(void){
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
	GPIOB->MODER &=~ (GPIO_MODER_MODE0 | GPIO_MODER_MODE3);
	GPIOB->MODER |= GPIO_MODER_MODE3_0;
	
	GPIOB->PUPDR &=~ GPIO_PUPDR_PUPD0;
	GPIOB->PUPDR |= GPIO_PUPDR_PUPD0_1;
}

