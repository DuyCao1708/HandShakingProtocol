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
TIM_HandleTypeDef htim2;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_TIM2_Init(void);
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
  MX_USART1_UART_Init();
  MX_TIM2_Init();
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
		serialProcess();
//		strData[0] = 0x30;
//		strData[1] = 0x30;
//		strData[2] = 0x31;
//		uint8_t analogDuty = 0;
//					for (int i = 0; i < 3; i++) 
//					{
//						analogDuty = analogDuty * 10 + (strData[i]-(uint8_t)'0');
//					}
//					__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2, analogDuty*62);
//					HAL_Delay(1000);
//					
//					for (int i = 0; i < 3; i++) 
//					{
//						analogDuty = analogDuty * 10 + (strData[i]-(uint8_t)'0');
//					}
//					__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2, 62);
//					HAL_Delay(1000);
//					
//					for (int i = 0; i < 3; i++) 
//					{
//						analogDuty = analogDuty * 10 + (strData[i]-(uint8_t)'0');
//					}
//					__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2, 1);
//					HAL_Delay(1000);
					
//		strData[0] = 0x30;
//		strData[1] = 0x35;
//		strData[2] = 0x30;
//					for (int i = 0; i < 3; i++) 
//					{
//						analogDuty = analogDuty * 10 + (strData[i]-(uint8_t)'0');
//					}
//					__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2, analogDuty*62);
//					HAL_Delay(1000);
//					
//	 strData[0] = 0x31;
//		strData[1] = 0x30;
//		strData[2] = 0x30;
//					for (int i = 0; i < 3; i++) 
//					{
//						analogDuty = analogDuty * 10 + (strData[i]-(uint8_t)'0');
//					}
//					__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2, analogDuty*62);
//					HAL_Delay(1000);

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

					if (StrCompare(strData, (uint8_t *)"LED-ON", 8))
					{
						HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
					}
					else if (StrCompare(strData, (uint8_t *)"LED-OFF", 8))
					{
						HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
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

					int analogDuty = 0;
					for (int i = 0; i < 3; i++) 
					{
						analogDuty = analogDuty * 10 + (int)(strData[i]-(uint8_t)'0');
					}
					__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2, analogDuty);
					HAL_Delay(1000);
					
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
  htim2.Init.Period = 625;
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

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PA6 */
  GPIO_InitStruct.Pin = GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

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
