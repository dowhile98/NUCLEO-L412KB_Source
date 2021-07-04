#include "KEYPAD4X4.h"

/**************DFININICION DE VARIABLES GLOBLALES*******************************/
static const uint8_t key_table [4][4]= {
                                        {'7','8','9','/'},
                                        {'4','5','6','X'},
                                        {'1','2','3','-'},
                                        {'c','0','=','+'}
                                       };

/***************+DEFINICIOJN DE FUNCIONES         *****************************/

void keypad_init(void){
	/*Se habilita el reloj para los puertos usados*/
	KEYPAD_RCC_EN()
  /*****FILAS**************************/
	//R1
	R1_PORT->MODER &=~(0x3U<<2*R1_PIN);				//RESET
	R1_PORT->MODER |= 1<<2*R1_PIN;						//OUTPUT	
	R1_PORT->OTYPER &=~(0x3U<<R1_PIN);				//PUSH-PULL
	R1_PORT->OSPEEDR |=(0x3U<<2*R1_PIN);			//HIGH SPEED
	//R2
	R2_PORT->MODER &=~(0x3U<<2*R2_PIN);				//RESET
	R2_PORT->MODER |= 1<<2*R2_PIN;						//OUTPUT	
	R2_PORT->OTYPER &=~(0x3U<<R2_PIN);				//PUSH-PULL
	R2_PORT->OSPEEDR |=(0x3U<<2*R2_PIN);			//HIGH SPEED
	//R3
	R3_PORT->MODER &=~(0x3U<<2*R3_PIN);				//RESET
	R3_PORT->MODER |= 1<<2*R3_PIN;						//OUTPUT	
	R3_PORT->OTYPER &=~(0x3U<<R3_PIN);				//PUSH-PULL
	R3_PORT->OSPEEDR |=(0x3U<<2*R3_PIN);			//HIGH SPEED
	//R4
	R4_PORT->MODER &=~(0x3U<<2*R4_PIN);				//RESET
	R4_PORT->MODER |= 1<<2*R4_PIN;						//OUTPUT	
	R4_PORT->OTYPER &=~(0x3U<<R4_PIN);				//PUSH-PULL
	R4_PORT->OSPEEDR |=(0x3U<<2*R4_PIN);			//HIGH SPEED

  /*******************COLUMNAS**************/
	//C1
	C1_PORT->MODER &=~(0x3U<<C1_PIN);					//INPUT
	C1_PORT->PUPDR |= 1<<2*C1_PIN;						//pull up
	//C2
	C2_PORT->MODER &=~(0x3U<<C2_PIN);					//INPUT
	C2_PORT->PUPDR |= 1<<2*C2_PIN;						//pull up
	//C3
	C3_PORT->MODER &=~(0x3U<<C3_PIN);					//INPUT
	C3_PORT->PUPDR |= 1<<2*C3_PIN;						//pull up
	//C4
	C4_PORT->MODER &=~(0x3U<<C4_PIN);					//INPUT
	C4_PORT->PUPDR |= 1<<2*C4_PIN;						//pull up
   
}

uint8_t keypad_read(void){
    uint8_t row;
    int8_t col = 0;
    uint8_t data;
    for(row = 0; row<4; row++){
			R1_SET;
			R2_SET;
			R3_SET;
			R4_SET;
      switch(row){
				case 0: R1_RESET; break;
        case 1: R2_RESET; break;
        case 2: R3_RESET; break;
        case 3: R4_RESET; break;
      }
      delay_us(500);
      data = (uint8_t)(C4_BIT<<3 | C3_BIT<<2 | C2_BIT<<1 | C1_BIT<<0);
      col = KEYPAD_EMPTY;
      switch(data){
				case 0xE: col = 0; break;
        case 0xD: col = 1; break;
        case 0xB: col = 2; break;
        case 0x7: col = 3; break;
      }
      if(col != KEYPAD_EMPTY)
				break;      //salida del for
    }
    if(col == KEYPAD_EMPTY)
			return KEYPAD_EMPTY;
    else
			return(key_table[row][col]);
}
