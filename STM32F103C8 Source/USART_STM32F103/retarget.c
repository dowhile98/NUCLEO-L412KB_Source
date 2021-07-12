#include <stdio.h>


/*FUNCIONES DECLARADAS EXTERNAMENTE*/

extern int USART1_putc(char ch);
extern char USART1_getc(void);

/*ESTA PARTE DEL CODIGO PERMITE EL MANEJO DE LA FUNCION PRINTF Y SCANF*/
struct __FILE{int handle;};
FILE __stdin = {0};
FILE __stdout ={1};
FILE __stderr = {2};
	
int fgetc(FILE *f){
	int c;
	c = USART1_getc();
	if(c == '\r'){
		USART1_putc(c);
		c = '\n';
	}
	USART1_putc(c);
	return c;
}

int fputc(int c,FILE *f)
{
	return USART1_putc(c);
}
