/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
#define S						120									//cantidad de pulsos por vuelta
#define Ts					20E-3								//tiempo de muestreo
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint32_t 	pulse;												//pulsos del encoder
float			rpm;													//RPM
float 		radS;													//velocidad en rad/s
float ref	 = 20;															//referencia
uint16_t U;															//valor uk calculado
char buffer[100];
uint8_t byte;
uint8_t i;
uint8_t state = 1;
/*esta estructuca contiene las variables presentes y pasadas del controlador*/
typedef struct{
	/*error*/
	float ePresent;
	float ePast;     //ek_1
	/*termino proporcional*/
	float PPresent;
	/*termino integral*/
	float IPresent;
	float IPast;
	/*termino derivativo*/
	float DPresent;
	float DPast;
	/*salida medida*/
	float yPresent;
	float yPast;
	/*salida del wind up*/
	float wPresent;
	float wPast;
	/*salida del saturador*/
	float uPresent;
	float uPast;
	/*salida del controlador*/
	float vPresent;
	float vPast;
	/*valores maximos y minimos del saturador*/
	uint16_t Vmax;
	uint16_t Vmin;
}PID_Def_t;


PID_Def_t MOTOR_DC;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
/**
 * @brief esta funcion inicializa algunos parametros de PID_Def_t
 * @param PID_Def_t
 * @param vMax : valor maximo del saturador
 * @param vMin : valor minimo del saturador
*/
void PID_Config(PID_Def_t *pPID, uint16_t vMin,uint16_t vMax);

/**
 * @brief esta funcion calcula el valor u(k)
 * @param PID_Def_t
 * @param y  : valor de la velocidad medida en Ts
 * @retval u : retorna el valor de u(k)
*/
uint16_t Calculate_PID(PID_Def_t *pPID,float r, float y);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM2_Init();
  MX_TIM6_Init();
  MX_TIM15_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);
  HAL_TIM_PWM_Start(&htim15, TIM_CHANNEL_2);		//salida PWM
	
	PID_Config(&MOTOR_DC,0,100-1);
	HAL_UART_Receive_IT(&huart2,&byte,1);
	HAL_TIM_Base_Start_IT(&htim6);										//inicia el muestreo
	HAL_TIM_Base_Start(&htim2);												//inicia el timer2 para que capture los pulsos del encoder
	__HAL_TIM_SET_COMPARE(&htim15,TIM_CHANNEL_2,0);	//duty 0%
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,GPIO_PIN_SET);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 40;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
//void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
//{
//	if(GPIO_Pin == GPIO_PIN_1){
//		if(state == 1){
//			HAL_TIM_Base_Start_IT(&htim6);										//inicia el muestreo
//			HAL_TIM_Base_Start(&htim2);												//inicia el timer2 para que capture los pulsos del encoder
//			__HAL_TIM_SET_COMPARE(&htim15,TIM_CHANNEL_2,0);	//duty 0%
//			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,GPIO_PIN_SET);
//			
//			state = 0;
//		}else{
//			HAL_TIM_Base_Stop_IT(&htim6);
//			HAL_TIM_Base_Stop(&htim2);
//			__HAL_TIM_SET_COMPARE(&htim15,TIM_CHANNEL_2,0);	//duty 0%
//			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,GPIO_PIN_RESET);
//			state = 1;
//		}
//		
//		
//	}

//	return;
//}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(byte == 'x'){
		HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_3);
		ref = atof(buffer);
		memset(buffer,0,i);
		i = 0;
	}else{
		buffer[i] = byte;
		i++;
	}
	
	HAL_UART_Receive_IT(&huart2,&byte,1);
	
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim == &htim6){
/****************************************************************************/
		pulse = __HAL_TIM_GET_COUNTER(&htim2);
		rpm = pulse * 60.0 /(Ts * S);				//se calcula el RPM
		radS = rpm  *(2*3.141592)/60;				//velocidad en Rad/s
		__HAL_TIM_SET_COUNTER(&htim2,0);
/*****************************************************************************/
		U = Calculate_PID(&MOTOR_DC,ref,radS);
		__HAL_TIM_SET_COMPARE(&htim15,TIM_CHANNEL_2,U);	//duty
		printf("%.2f\r\n",radS);
	}
	return;
}


/*******************DEFINICION DE FUNCIONES PARA EL PID********************/
void PID_Config(PID_Def_t *pPID, uint16_t vMin,uint16_t vMax){
	/*se pone todos los valores a 0*/
	memset(pPID,0,sizeof(PID_Def_t));
	pPID->Vmax = vMax;
	pPID->Vmin = vMin;
}

uint16_t Calculate_PID(PID_Def_t *pPID,float r, float y){
	//se obtiene la medida
	pPID->yPresent = y;
	//se calcula el error
	pPID->ePresent = r - pPID->yPresent;
	//termino proporcional
	pPID->PPresent = -0.008589* pPID->ePresent;
	//termino integral 
	pPID->IPresent =(float)( pPID->IPast + 0.00555*pPID->ePast);
	//termino derivativo con filtro
	pPID->DPresent = (float)(0.1353352*pPID->DPast + 0.01067*pPID->yPresent - 0.01067*pPID->yPast);
	
	//se halla v(k)
	pPID->vPresent = pPID->PPresent + pPID->IPresent + pPID->DPresent + pPID->wPresent;
	
	//se pasa por el saturador
	if(pPID->vPresent > pPID->Vmax)
		pPID->vPresent = pPID->Vmax;
	else if (pPID->vPresent < pPID->Vmin)
		pPID->vPresent = pPID->Vmin;
	//wind up
	pPID->wPresent = (float)(pPID->wPast + 0.4*(pPID->uPast - pPID->vPast));
	
	//se actuliza el valor de la salida
	pPID->uPresent = pPID->vPresent;
	
	//se actulizan los valores pasados
	pPID->DPast = pPID->DPresent;
	pPID->IPast = pPID->IPresent;
	pPID->wPast = pPID->wPresent;
	pPID->uPast = pPID->uPresent;
	pPID->vPast = pPID->vPresent;
	pPID->ePast = pPID->ePresent;
	pPID->yPast = pPID->yPresent;
	
	//se retorna el valor calculado
	return (uint16_t)(pPID->uPresent);
}


/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
