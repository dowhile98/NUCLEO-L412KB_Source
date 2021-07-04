 /*------>MANEJO DE DISPLA DE 7Seg<-----
 *				 CONEXIONES
 *a		->A4(PA5) 
 *b		->A6(PA7) 
 *c		->D9(PA8) 
 *d		->D10(PA11) 
 *e		->D11(PB5) 
 *f		->A3(PA4) 
 *g		-> A2(PA3)
 *EN1	->D2(PA12)  
 *EN2	->D5(PB6) 
 *EN3	->D3(PB0)
 *Push button-> D6 (PB1)
 *
 *@autor: QUINO B. JEFFRY
 */


#include "stm32l4xx.h"                  // Device header
#include "RCC.h"
/************DEFINICION DE MACROS*******/
/*LEDs LCD*/
#define a									5
#define b									7
#define c									8
#define d 								11
#define e									5
#define f									4
#define g									3


#define EN1_SET() 				GPIOA->BSRR |= (1U<<12)
#define EN1_RESET()				GPIOA->BRR |= (1U<<12)
#define EN2_SET() 				GPIOB->BSRR |= (1U<<6)
#define EN2_RESET()				GPIOB->BRR |= (1U<<6)
#define EN3_SET() 				GPIOB->BSRR |= (1U<<0)
#define EN3_RESET()				GPIOB->BRR |= (1U<<0)

/***********VARIABLES GLOBALES**********/
const uint8_t Table7seg[] = {0X3F , 0X06 , 0X5B, 0X4F, 0X66, 0X6D, 0X7D, 0X07, 0X7F, 0X67 } ;
/*********PROTOTIPO DE FUNCIONES********/
void GPIO_Config(void);
void sendDisplay(uint8_t numDisplay,uint8_t data);
void delay_ms(uint32_t delay);

int main(void){
	PLL_Config();													//sysclk = 80MHz
	GPIO_Config();
	
	
	while(1){
		sendDisplay(1,Table7seg[1]);
		delay_ms(5);
		sendDisplay(2,Table7seg[2]);
		delay_ms(5);
		sendDisplay(3,Table7seg[3]);
		delay_ms(5);
	}
}

/*********DEFINICION DE FUNCIONES*******/
void GPIO_Config(void){
	/*enable clk*/
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;			//CLCK ENABLE FOR GPIOA
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;			//CLCK ENABLE FOR GPIOB
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;			//CLCK ENABLE FOR GPIOC
	/*PA2,PA3,PA4, PA5,PA6,PA7, PA8, PA11, PA12: output mode push pull*/
	GPIOA->MODER &=~ (GPIO_MODER_MODE2 | GPIO_MODER_MODE3 | \
										GPIO_MODER_MODE4 | GPIO_MODER_MODE5 | \
										GPIO_MODER_MODE6 | GPIO_MODER_MODE7 | \
										GPIO_MODER_MODE8 | GPIO_MODER_MODE11 | \
										GPIO_MODER_MODE12);
	GPIOA->MODER |= ( GPIO_MODER_MODE2_0 | GPIO_MODER_MODE3_0 | \
										GPIO_MODER_MODE4_0 | GPIO_MODER_MODE5_0 | \
										GPIO_MODER_MODE6_0 | GPIO_MODER_MODE7_0 | \
										GPIO_MODER_MODE8_0 | GPIO_MODER_MODE11_0 | \
										GPIO_MODER_MODE12_0);		//general purpose oput mode
	GPIOA->OTYPER &=~(GPIO_OTYPER_OT2 | GPIO_OTYPER_OT3 | \
										GPIO_OTYPER_OT4 | GPIO_OTYPER_OT5 | \
										GPIO_OTYPER_OT6 | GPIO_OTYPER_OT7 | \
										GPIO_OTYPER_OT8 | GPIO_OTYPER_OT11 | \
										GPIO_OTYPER_OT12);					//Output push-pull
	GPIOA->OSPEEDR &=~ (GPIO_OSPEEDR_OSPEED2 | GPIO_OSPEEDR_OSPEED3 | \
											GPIO_OSPEEDR_OSPEED4 | GPIO_OSPEEDR_OSPEED5 | \
											GPIO_OSPEEDR_OSPEED6 | GPIO_OSPEEDR_OSPEED7 | \
											GPIO_OSPEEDR_OSPEED8 | GPIO_OSPEEDR_OSPEED11 | \
											 GPIO_OSPEEDR_OSPEED12);		//low speed
	GPIOA->PUPDR &=~ (GPIO_PUPDR_PUPD2 | GPIO_PUPDR_PUPD3 | \
										GPIO_PUPDR_PUPD4 | GPIO_PUPDR_PUPD5 | \
										GPIO_PUPDR_PUPD6 | GPIO_PUPDR_PUPD7 | \
										GPIO_PUPDR_PUPD8 | GPIO_PUPDR_PUPD11 | \
										GPIO_PUPDR_PUPD12);			//No pull up/down
	/*PB0, PB5, PB6: output mode push-pull*/
	GPIOB->MODER &=~ (GPIO_MODER_MODE0 | GPIO_MODER_MODE5 | GPIO_MODER_MODE6);
	GPIOB->MODER |= GPIO_MODER_MODE0_0 | GPIO_MODER_MODE5_0 | GPIO_MODER_MODE6_0;														//general purpose output mode
	GPIOB->OTYPER &=~ (GPIO_OTYPER_OT0 | GPIO_OTYPER_OT5 | GPIO_OTYPER_OT6);														//output push pull
	GPIOB->OSPEEDR &=~ (GPIO_OSPEEDR_OSPEED0 | GPIO_OSPEEDR_OSPEED5 | GPIO_OSPEEDR_OSPEED6);											//low speed
	GPIOB->PUPDR &=~ (GPIO_PUPDR_PUPD0 | GPIO_PUPDR_PUPD5 | GPIO_PUPDR_PUPD6);														//no pull up/down
	
	
	/*PB1: Input mode pull down*/
	GPIOB->MODER &=~ GPIO_MODER_MODE1;														//input mode
	GPIOB->PUPDR &=~ GPIO_PUPDR_PUPD1;
	GPIOB->PUPDR |= GPIO_PUPDR_PUPD1_1;														//pull down
}

/*********DEFINICION DE FUNCIONES*******/
void sendDisplay(uint8_t numDisplay,uint8_t data){
	EN1_RESET();
	EN2_RESET();
	EN3_RESET();
	
	/*set a*/
	if((data>>0 & 0x1U))
		GPIOA->BSRR |= (1U<<a);
	else
		GPIOA->BRR |= (1U<<a);
	/*set b*/
	if((data>>1 & 0x1U))
		GPIOA->BSRR |= 1U<<b;
	else
		GPIOA->BRR |= 1U<<b;
	/*set c*/
	if(data>>2 & 0x1U)
		GPIOA->BSRR |= 1U<<c;
	else
		GPIOA->BRR |= 1U<<c;
	/*set d*/
	if(data>>3 & 0x1U)
		GPIOA->BSRR |= 1U<<d;
	else
		GPIOA->BRR |= 1U<<d;
	/*set e*/
	if(data>>4 & 0x1U)
		GPIOB->BSRR |= 1U<<e;
	else
		GPIOB->BRR |= 1U<<e;
	/*set f*/
	if(data>>5 & 0x1U)
		GPIOA->BSRR |= 1U<<f;
	else
		GPIOA->BRR |= 1U<<f;
	/*set g*/
	if(data>>6 & 0x1U)
		GPIOA->BSRR |= 1U<<g;
	else
		GPIOA->BRR |= 1U<<g;
	/*encender el display elegido*/
	if(numDisplay == 1){
		EN1_SET();
		EN2_RESET();
		EN3_RESET();
	}else if(numDisplay == 2){
		EN1_RESET();
		EN2_SET();
		EN3_RESET();
	}else if(numDisplay == 3){
		EN1_RESET();
		EN2_RESET();
		EN3_SET();
	}else{
		EN1_RESET();
		EN2_RESET();
		EN3_RESET();
	}
	
	return;
}

void delay_ms(uint32_t delay){
	uint32_t i;
	SysTick->CTRL = 0;
	SysTick->LOAD = SystemCoreClock/1000 - 1;
	SysTick->VAL =  0;
	SysTick->CTRL |= 1<<2 | 1<<0;
	for( i = 0; i<delay; i++){
		while(!(SysTick->CTRL & 1<<16));
	}
	SysTick->CTRL = 0;
}


