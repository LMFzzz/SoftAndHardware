//
// Created by LMF on 2023/12/31.
//

#ifndef DHT11_DHT11_H
#define DHT11_DHT11_H
#include "stm32f1xx.h"
#include "tim.h"
#define	DHT11_DQ_IN   HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_11)
void DHT11_OUT(void );
void DHT11_IN(void );

uint8_t DHT11_Init(void);//初始化DHT11
uint8_t DHT11_Read_Data(uint8_t *humiH,uint8_t *humiL,uint8_t *tempH,uint8_t *tempL);//读取温湿度
uint8_t DHT11_Read_Byte(void);//读出一个字节
uint8_t DHT11_Read_Bit(void);//读出一个位
uint8_t DHT11_Check(void);//检测是否存在DHT11
void DHT11_Rst(void);//复位DHT11
#endif //DHT11_DHT11_H
