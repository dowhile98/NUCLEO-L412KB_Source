#include "stm32f4xx.h"                  // Device header
#include<stdio.h>

void change_sp_to_psp(void);

int func_add(int a, int b , int c , int d)
{
	int sum = a+b+c+d;
	return sum;
}

void generate_exception(void)
{
	/* execute SVC instruction to cause SVC exception */
	__asm volatile("SVC #0X2");
}


int main(void)
{
	/* from here onwards PSP will be used for stack activities */
	int ret;
	
	
	change_sp_to_psp();



	ret = func_add(1, 4, 5, 6);

	printf("result = %d\n",ret);

	generate_exception();

	for(;;);
}


void SVC_Handler(void)
{
	printf(" in SVC_Handler\n");
}
