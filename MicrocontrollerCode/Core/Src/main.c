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
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stm32f1xx.h"
#include "./usr/lcd.h"
#include "./usr/CommMod.h"
#include "./usr/sensors.h"
#include "./usr/UserInput.h"
#include <stdbool.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;

UART_HandleTypeDef huart2;

/* Definitions for calcTask */
osThreadId_t calcTaskHandle;
const osThreadAttr_t calcTask_attributes = {
  .name = "calcTask",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 4
};
/* Definitions for sendTask */
osThreadId_t sendTaskHandle;
const osThreadAttr_t sendTask_attributes = {
  .name = "sendTask",
  .priority = (osPriority_t) osPriorityHigh,
  .stack_size = 128 * 4
};
/* Definitions for lcdTask */
osThreadId_t lcdTaskHandle;
const osThreadAttr_t lcdTask_attributes = {
  .name = "lcdTask",
  .priority = (osPriority_t) osPriorityLow,
  .stack_size = 128 * 4
};
/* Definitions for structQueue */
osMessageQueueId_t structQueueHandle;
const osMessageQueueAttr_t structQueue_attributes = {
  .name = "structQueue"
};
/* Definitions for rawQueue */
osMessageQueueId_t rawQueueHandle;
const osMessageQueueAttr_t rawQueue_attributes = {
  .name = "rawQueue"
};
/* Definitions for roomQueue */
osMessageQueueId_t roomQueueHandle;
const osMessageQueueAttr_t roomQueue_attributes = {
  .name = "roomQueue"
};
/* USER CODE BEGIN PV */
bool sel = true;
bool proceed = false;
uint8_t room_str[40];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_ADC1_Init(void);
void StartCalcTask(void *argument);
void StartSendTask(void *argument);
void StartLcdTask(void *argument);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
struct DataStruct{
	uint16_t temp;
	uint16_t CO2;
	uint16_t dB;
};
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
  MX_USART2_UART_Init();
  MX_ADC1_Init();
  /* USER CODE BEGIN 2 */

  lcd_IO_init();

  lcd_init();

  //uint8_t room_str[40];
  uint16_t roomSz = 0;

//  char2LCD("hello");

//  CMD2LCD(0xC0);

//  char2LCD("there");

  printString("\x1b[2J");

  printString("\x1b[0;0H");


	CMD2LCD(0x01);
	char2LCD("use inputs");
	CMD2LCD(0xC0);
	char2LCD("room size: ");
	POT_Select();
	while(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13))
	{
		CMD2LCD(0xCB);
		//roomSz = ADC_Read();
//			if(roomSz < 0x555)
//			{
//				strcpy((char *)room_str, "ed435");
//			}
//			else if(roomSz < 0xAAA)
//			{
//				strcpy((char *)room_str, "ed486");
//			}
//			else if(roomSz < 0xFFF)
//			{
//				strcpy((char *)room_str, "cl110");
//			}

		strcpy((char *)room_str, roomSelect(ADC_Read()));
		char2LCD((char *)room_str);
//		char2LCD("8");
//		HAL_Delay(300);
//		CMD2LCD(0xCB);
//		char2LCD("2");
//		HAL_Delay(300);
	}
	CMD2LCD(0x01);
//	if(osMessageQueuePut(roomQueueHandle, &roomSz, 1U, 0U) != osOK)
//	{
//		Error_Handler();
//	}

  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* creation of structQueue */
  structQueueHandle = osMessageQueueNew (1, sizeof(struct DataStruct), &structQueue_attributes);

  /* creation of rawQueue */
  rawQueueHandle = osMessageQueueNew (1, sizeof(struct DataStruct), &rawQueue_attributes);

  /* creation of roomQueue */
  roomQueueHandle = osMessageQueueNew (1, sizeof(uint16_t), &roomQueue_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of calcTask */
  calcTaskHandle = osThreadNew(StartCalcTask, NULL, &calcTask_attributes);

  /* creation of sendTask */
  sendTaskHandle = osThreadNew(StartSendTask, NULL, &sendTask_attributes);

  /* creation of lcdTask */
  lcdTaskHandle = osThreadNew(StartLcdTask, NULL, &lcdTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */
  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ScanConvMode = ADC_SCAN_ENABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }
//  /** Configure Regular Channel
//  */
//  sConfig.Channel = ADC_CHANNEL_7;
//  sConfig.Rank = ADC_REGULAR_RANK_1;
//  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
//  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
//  {
//    Error_Handler();
//  }
//  /** Configure Regular Channel
//  */
//  sConfig.Channel = ADC_CHANNEL_4;
//  sConfig.Rank = ADC_REGULAR_RANK_2;
//  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
//  {
//    Error_Handler();
//  }
//  /** Configure Regular Channel
//  */
//  sConfig.Channel = ADC_CHANNEL_1;
//  sConfig.Rank = ADC_REGULAR_RANK_3;
//  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
//  {
//    Error_Handler();
//  }
//  /** Configure Regular Channel
//  */
//  sConfig.Rank = ADC_REGULAR_RANK_4;
//  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
//  {
//    Error_Handler();
//  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_5, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PC0 PC1 PC2 PC3
                           PC4 PC5 PC6 PC7 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PA5 */
  GPIO_InitStruct.Pin = GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 PB5 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
//void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
//{
//	if(GPIO_Pin == GPIO_PIN_13)
//	{
//		if(sel == false)
//		{
//			sel = true;
//		}
//		else
//		{
//			sel = false;
//		}
//		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
//
//	}
//
//}

uint16_t reg_out( uint32_t reg_data){

int i;

uint32_t shifted_val;

//DAT2LCD (0x30);
//
//DAT2LCD (0x78);

for ( i=28; i >= 0 ; i = (i-4))

{

shifted_val = (reg_data >> i) & 0xf;
if (i <= 8)
{
dipSW2LCD(shifted_val);
}
}
return (uint16_t)reg_data;

}

/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartCalcTask */
/**
  * @brief  Function implementing the calcTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartCalcTask */
void StartCalcTask(void *argument)
{
  /* USER CODE BEGIN 5 */
	uint16_t data = 0;
	struct DataStruct dc;
	dc.temp = 0;
	dc.CO2 = 0;
	dc.dB = 0;
	/* Infinite loop */
	for(;;)
	{
		TEMP_Select();
		dc.temp = TempConversion(ADC_Read());

		CO2_Select();
		dc.CO2 = CO2Conversion(ADC_Read());

		NOISE_Select();
		dc.dB = NoiseConversion(ADC_Read());

//		dc.CO2 += 5;
//		dc.dB += 10;

		if(osMessageQueuePut(rawQueueHandle, &dc, 1U, 0U) != osOK)
		{
			Error_Handler();
		}

		//DataFormat()
		//OccupancyCalculation()

		if(osMessageQueuePut(structQueueHandle, &dc, 1U, 0U) != osOK)
		{
			Error_Handler();
		}

		osDelay(500);
	}
	osThreadTerminate(NULL);
  /* USER CODE END 5 */
}

/* USER CODE BEGIN Header_StartSendTask */
/**
* @brief Function implementing the sendTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartSendTask */
void StartSendTask(void *argument)
{
  /* USER CODE BEGIN StartSendTask */
	uint8_t data_str[40];
	struct DataStruct dc;
	/* Infinite loop */
	for(;;)
	{
		if(osMessageQueueGet(structQueueHandle, &dc, NULL, 0U) == osOK)
		{
			sprintf((char *)data_str, "%d", dc.temp);
			printString((char *)data_str);
			printString(" ");
			sprintf((char *)data_str, "%d", dc.CO2);
			printString((char *)data_str);
			printString(" ");
			sprintf((char *)data_str, "%d", dc.dB);
			printString((char *)data_str);
			printString("\r\n");
		}
		osDelay(1000);
	}
	osThreadTerminate(NULL);
  /* USER CODE END StartSendTask */
}

/* USER CODE BEGIN Header_StartLcdTask */
/**
* @brief Function implementing the lcdTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartLcdTask */
void StartLcdTask(void *argument)
{
  /* USER CODE BEGIN StartLcdTask */
	uint8_t raw_str[40];
	uint16_t roomSz = 0;
	struct DataStruct rc;
	/* Infinite loop */
	for(;;)
	{
		if(osMessageQueueGet(rawQueueHandle, &rc, NULL, 0U) == osOK)
		{
//			if(osMessageQueueGet(roomQueueHandle, &roomSz, NULL, 0U) == osOK)
//			{
//				roomSz = roomSz / 2.67;
//				roomSz += 500;
//				sprintf((char *)raw_str, "%d", roomSz);
//				CMD2LCD(0x80);
//				char2LCD("rs:");
//				char2LCD((char *)raw_str);
//			}

			CMD2LCD(0x80);
			char2LCD("rs:");
			char2LCD((char *)room_str);

			sprintf((char *)raw_str, "%d", rc.temp);
			CMD2LCD(0x89);
			char2LCD("tmp:");
			char2LCD((char *)raw_str);

			sprintf((char *)raw_str, "%d", rc.CO2);
			CMD2LCD(0xC0);
			char2LCD("co2:");
			char2LCD((char *)raw_str);

			sprintf((char *)raw_str, "%d", rc.dB);
			CMD2LCD(0xC9);
			char2LCD("nl:");
			char2LCD((char *)raw_str);

		}
		osDelay(1);
	}
	osThreadTerminate(NULL);
  /* USER CODE END StartLcdTask */
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM4 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM4) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
