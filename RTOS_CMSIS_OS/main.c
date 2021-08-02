#include "stm32l4xx.h"                  // Device header
#include "cmsis_os.h"                  // ::CMSIS:RTOS2


osThreadId task1Handle;
osThreadId task2Handle;

/*prototipo de tareas*/
void task1(void const *params);
void task2(void const *params);


/*task create*/
osThreadDef(task1,osPriorityNormal,1,0);
osThreadDef(task2,osPriorityNormal,1,0);

int main(void){
	
	osKernelInitialize();
	
	task1Handle = osThreadCreate(osThread(task1),NULL);
	task2Handle = osThreadCreate(osThread(task2),NULL);
	
	
	osKernelStart();
	
	
	while(1){
		
		
	}
}


void task1(void const *params){
	
	while(1){
		
	}
}
void task2(void const *params){
	while(1){
		
	}
	
}
