/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "string.h"
#include "stdio.h"
#include <stdbool.h>
#include <stdlib.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define MAX_LEN 18
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;

TIM_HandleTypeDef htim2;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_TIM2_Init(void);
static void MX_ADC1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
bool bDataAvailable = false;

uint8_t nRxData[MAX_LEN];
uint8_t nTxData[MAX_LEN];

uint8_t STX[] = {0x02U};
uint8_t ETX[] = {0x03U};
uint8_t ACK[] = {0x06U};
uint8_t SYN[] = {0x16U};

uint8_t strCommand[4];
uint8_t strOpt[3];
uint8_t strData[8];

uint32_t adcValue = 0;
bool adcFlag = false;

bool StrCompare(uint8_t *pBuff, uint8_t *Sample, uint8_t nSize);
bool WriteComm(uint8_t *pBuff, uint8_t nSize);
bool ReadComm(uint8_t *pBuff, uint8_t nSize);
bool serialProcess(void);
void HAL_UART_RxCpltCallback (UART_HandleTypeDef *huart);

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
  MX_DMA_Init();
  MX_USART1_UART_Init();
  MX_TIM2_Init();
  MX_ADC1_Init();
  /* USER CODE BEGIN 2 */
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
	HAL_UART_Receive_IT(&huart1, (uint8_t *)nRxData, MAX_LEN);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		if (adcFlag)
		{
				HAL_ADC_Start_DMA(&hadc1, &adcValue, 1);
		__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2, (int)adcValue);
		}

		serialProcess();

  }
  /* USER CODE END 3 */
}
uint8_t *subString(uint8_t *s, int pos, int index)
{
	uint8_t *t = &s[pos];
  uint8_t *result = (uint8_t*)malloc(index + 1);
  memcpy(result, t, index);
  result[index] = '\0';
  return result;
}

// compares two strings character by character. If the strings are equal, the function return true
bool StrCompare(uint8_t *pBuff, uint8_t *Sample, uint8_t nSize) 
{
	for (int i = 0; i < nSize; i++)
	{
		if (pBuff[i] != Sample[i])
		{
			return false;
		}
	}
	return true;
}

// Sends one or more bytes to serial port
bool WriteComm(uint8_t *pBuff, uint8_t nSize)
{
	return HAL_UART_Transmit(&huart1, pBuff, nSize, 1000);
}

// Receives one or more bytes from serial port
bool ReadComm(uint8_t *pBuff, uint8_t nSize)
{
	if ((pBuff[0] == STX[0]) && (pBuff[17] == ETX[0]))
	{
		uint8_t *subCommand = subString(pBuff, 1, 4);
		uint8_t *subOpt = subString(pBuff, 5, 3);
		uint8_t *subData = subString(pBuff, 8, 8);

		memcpy(strCommand, subCommand, 4);
		memcpy(strOpt, subOpt, 3);
		memcpy(strData, subData, 8);

		free(subCommand);
		free(subOpt);
		free(subData);

		bDataAvailable = true;
	}
	else
	{
		bDataAvailable = false;	
	}
	return bDataAvailable;
}

bool serialProcess(void)
		{
			uint8_t nIndex = 0;
			if (bDataAvailable == true)
			{
				if (StrCompare(strCommand, (uint8_t *)"MOVL", 4))
				{
					memcpy(nTxData + nIndex, STX, 1);
					nIndex += 1;
					memcpy(nTxData + nIndex, strCommand, 4);
					nIndex += 4;
					memcpy(nTxData + nIndex, strOpt, 3);
					nIndex += 3;
					memcpy(nTxData + nIndex, strData, 8);
					nIndex += 8;
					memcpy(nTxData + nIndex, ACK, 1);
					nIndex += 1;
					memcpy(nTxData + nIndex, ETX, 1);

					WriteComm(nTxData, MAX_LEN);
				}
				else if (StrCompare(strCommand, (uint8_t *)"GPOS", 4))
				{
					memcpy(nTxData + nIndex, STX, 1);
					nIndex += 1;
					memcpy(nTxData + nIndex, strCommand, 4);
					nIndex += 4;
					memcpy(nTxData + nIndex, strOpt, 3);
					nIndex += 3;
					memcpy(nTxData + nIndex, strData, 8);
					nIndex += 8;
					memcpy(nTxData + nIndex, ACK, 1);
					nIndex += 1;
					memcpy(nTxData + nIndex, ETX, 1);

					WriteComm(nTxData, MAX_LEN);
				}
				else if (StrCompare(strCommand, (uint8_t *)"GVEL", 4))
				{
					memcpy(nTxData + nIndex, STX, 1);
					nIndex += 1;
					memcpy(nTxData + nIndex, strCommand, 4);
					nIndex += 4;
					memcpy(nTxData + nIndex, strOpt, 3);
					nIndex += 3;
					memcpy(nTxData + nIndex, strData, 8);
					nIndex += 8;
					memcpy(nTxData + nIndex, ACK, 1);
					nIndex += 1;
					memcpy(nTxData + nIndex, ETX, 1);

					WriteComm(nTxData, MAX_LEN);
				}
				else if (StrCompare(strCommand, (uint8_t *)"GSTT", 4))
				{
					memcpy(nTxData + nIndex, STX, 1);
					nIndex += 1;
					memcpy(nTxData + nIndex, strCommand, 4);
					nIndex += 4;
					memcpy(nTxData + nIndex, strOpt, 3);
					nIndex += 3;
					memcpy(nTxData + nIndex, strData, 8);
					nIndex += 8;
					memcpy(nTxData + nIndex, ACK, 1);
					nIndex += 1;
					memcpy(nTxData + nIndex, ETX, 1);

					WriteComm(nTxData, MAX_LEN);
				}
				else if (StrCompare(strCommand, (uint8_t *)"GCUS", 4))
				{
					memcpy(nTxData + nIndex, STX, 1);
					nIndex += 1;
					memcpy(nTxData + nIndex, strCommand, 4);
					nIndex += 4;
					memcpy(nTxData + nIndex, strOpt, 3);
					nIndex += 3;
					memcpy(nTxData + nIndex, strData, 8);
					nIndex += 8;
					memcpy(nTxData + nIndex, ACK, 1);
					nIndex += 1;
					memcpy(nTxData + nIndex, ETX, 1);

					WriteComm(nTxData, MAX_LEN);
				}
				else if (StrCompare(strCommand, (uint8_t *)"GTIM", 4))
				{
					memcpy(nTxData + nIndex, STX, 1);
					nIndex += 1;
					memcpy(nTxData + nIndex, strCommand, 4);
					nIndex += 4;
					memcpy(nTxData + nIndex, strOpt, 3);
					nIndex += 3;
					memcpy(nTxData + nIndex, strData, 8);
					nIndex += 8;
					memcpy(nTxData + nIndex, ACK, 1);
					nIndex += 1;
					memcpy(nTxData + nIndex, ETX, 1);

					WriteComm(nTxData, MAX_LEN);
				}
				else if (StrCompare(strCommand, (uint8_t *)"DLED", 4))
				{
					memcpy(nTxData + nIndex, STX, 1);
					nIndex += 1;
					memcpy(nTxData + nIndex, strCommand, 4);
					nIndex += 4;
					memcpy(nTxData + nIndex, strOpt, 3);
					nIndex += 3;
					memcpy(nTxData + nIndex, strData, 8);
					nIndex += 8;
					memcpy(nTxData + nIndex, ACK, 1);
					nIndex += 1;
					memcpy(nTxData + nIndex, ETX, 1);

					if (StrCompare(strData, (uint8_t *)"LED1-ON", 8))
					{
						HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_SET);
					}
					else if (StrCompare(strData, (uint8_t *)"LED1-OFF", 8))
					{
						HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_RESET);
					}
					
					if (StrCompare(strData, (uint8_t *)"LED2-ON", 8))
					{
						HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);
					}
					else if (StrCompare(strData, (uint8_t *)"LED2-OFF", 8))
					{
						HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
					}
					
					if (StrCompare(strData, (uint8_t *)"LED3-ON", 8))
					{
						HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);
					}
					else if (StrCompare(strData, (uint8_t *)"LED3-OFF", 8))
					{
						HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);
					}
					
					if (StrCompare(strData, (uint8_t *)"LED4-ON", 8))
					{
						HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
					}
					else if (StrCompare(strData, (uint8_t *)"LED4-OFF", 8))
					{
						HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
					}
					
					WriteComm(nTxData, MAX_LEN);					
				}
				else if (StrCompare(strCommand, (uint8_t *)"ALED", 4))
				{
					memcpy(nTxData + nIndex, STX, 1);
					nIndex += 1;
					memcpy(nTxData + nIndex, strCommand, 4);
					nIndex += 4;
					memcpy(nTxData + nIndex, strOpt, 3);
					nIndex += 3;
					memcpy(nTxData + nIndex, strData, 8);
					nIndex += 8;
					memcpy(nTxData + nIndex, ACK, 1);
					nIndex += 1;
					memcpy(nTxData + nIndex, ETX, 1);

					if (StrCompare(strOpt, (uint8_t *)"ADC", 3))
					{
						adcFlag = true;
					}
					else
					{
						int PWMDuty = 0;
						for (int i = 0; i < 4; i++) 
						{
							PWMDuty = PWMDuty * 10 + (int)(strData[i]-(uint8_t)'0');
						}
						__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2, PWMDuty);
						
						adcFlag = false;
					}
					
					WriteComm(nTxData, MAX_LEN);					
				}
				else
				{
					memcpy(nTxData + nIndex, STX, 1);
					nIndex += 1;
					memcpy(nTxData + nIndex, (uint8_t *)"NULL", 4);
					nIndex += 4;
					memcpy(nTxData + nIndex, (uint8_t *)strOpt, 3);
					nIndex += 3;
					memcpy(nTxData + nIndex, (uint8_t *)strData, 8);
					nIndex += 8;
					memcpy(nTxData + nIndex, ACK, 1);
					nIndex += 1;
					memcpy(nTxData + nIndex, ETX, 1);

					WriteComm(nTxData, MAX_LEN);
				}
				bDataAvailable = false;
			}
			return true;
		}

// Rx Transfer completed callbacks
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
 if(huart->Instance == huart1.Instance)
 {
	ReadComm(nRxData, MAX_LEN);

	HAL_UART_Receive_IT(&huart1, (uint8_t *)nRxData, MAX_LEN);
 }
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
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
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_239CYCLES_5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 127;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 4096;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */
  HAL_TIM_MspPostInit(&htim2);

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);

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
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5|GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1|GPIO_PIN_11, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA5 PA7 */
  GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PA6 */
  GPIO_InitStruct.Pin = GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB1 PB11 */
  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PB6 PB7 */
  GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

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
