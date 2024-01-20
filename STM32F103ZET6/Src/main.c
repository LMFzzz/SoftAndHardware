/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "i2c.h"
#include "rtc.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "oledfont.h"
#include "oled.h"
#include "bh1750.h"
#include "delay.h"
#include "stdio.h"
#include "sgp30.h"
#include "dht11.h"
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

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void) {
    /* USER CODE BEGIN 1 */
    uint8_t temp = 1;
    uint8_t hum = 1;
    char *CntState = "No Connect!\r\n";
    uint8_t aTxBuffer[50];
    uint32_t SGPData;
    uint32_t CO2Data, TVOCData;
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
    MX_I2C1_Init();
    MX_I2C2_Init();
    MX_RTC_Init();
    MX_USART1_UART_Init();
    MX_USART2_UART_Init();
    /* USER CODE BEGIN 2 */
    OLED_Init();
    OLED_Clear();


    delay_Init();
    HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_2);
    DHT11_Init();
    BH1750_Init();
    SGP30_Init();
    do {
        SGP30_Write(0x20, 0x08);
        SGPData = SGP30_Read();
        CO2Data = (SGPData & 0xffff0000) >> 16;
        TVOCData = SGPData & 0x0000ffff;
        delay_ms(500);
    } while (CO2Data == 400 && TVOCData == 0);
    OLED_ShowChinese(0, 0, TEMP, 0);//��
    OLED_ShowChinese(16, 0, TEMP, 1);//��
    OLED_ShowChinese(32, 0, MAO, 0);//:
    OLED_ShowChinese(64, 0, C, 0);//��
    OLED_ShowChinese(0, 2, HUM, 0);//ʪ
    OLED_ShowChinese(16, 2, HUM, 0);//��
    OLED_ShowChinese(32, 2, MAO, 0);//:
    OLED_ShowString(80, 2, "%", 16);
    OLED_ShowChinese(0, 4, LIGHT, 0);//��
    OLED_ShowChinese(16, 4, LIGHT, 1);//��
    OLED_ShowChinese(32, 4, LIGHT, 2);//ǿ
    OLED_ShowChinese(48, 4, LIGHT, 3);//��
    OLED_ShowChinese(64, 4, MAO, 0);//:
    OLED_ShowString(112, 4, "lx", 16);
    OLED_ShowChinese(0, 6, AIR, 0);//��
    OLED_ShowChinese(16, 6, AIR, 1);//��
    OLED_ShowChinese(32, 6, AIR, 2);//��
    OLED_ShowChinese(48, 6, AIR, 3);//��
    OLED_ShowChinese(64, 6, MAO, 0);//:
    OLED_ShowString(96, 6, "ppm", 16);

    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    while (1) {
        Read_DHT11_Data(&temp, &hum);
        SGP30_Write(0x20, 0x08);
        SGPData = SGP30_Read();
        CO2Data = (SGPData & 0xffff0000) >> 16;
        TVOCData = SGPData & 0x0000ffff;
//        printf("temp:%d ��,\rhum:%d %% ,\r,Light:%d\r\n,co2:%lu ppd\r\n", temp, hum,BH1750_Get_Value(), CO2Data);
        OLED_ShowNum(48,0,temp,2,16);//�¶�
        OLED_ShowNum(48,2,hum,2,16);//ʪ��
        OLED_ShowNum(80,4,BH1750_Get_Value(),3,16);//����ǿ��
        OLED_ShowNum(80,6,CO2Data,3,16);//CO2Ũ��
//        printf("Hello World!\r\n");
        delay_us(1000);
        /* USER CODE END WHILE */

        /* USER CODE BEGIN 3 */
    }
    /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
    RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

    /** Initializes the RCC Oscillators according to the specified parameters
    * in the RCC_OscInitTypeDef structure.
    */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI | RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.LSIState = RCC_LSI_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        Error_Handler();
    }

    /** Initializes the CPU, AHB and APB buses clocks
    */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                  | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
        Error_Handler();
    }
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
    PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
        Error_Handler();
    }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void) {
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1) {
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
