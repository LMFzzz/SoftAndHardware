//
// Created by LMF on 2024/1/13.
//

#ifndef SGP30DHT11_DHT11_H
#define SGP30DHT11_DHT11_H
#include "stm32f1xx.h"
#define DHT11_OUT GPIO_PIN_11
#define DHT11_IN GPIO_PIN_11
#define DHT11_PORT GPIOG
#define DHT11_CLK() __HAL_RCC_GPIOG_CLK_ENABLE()
#define DHT11_PIN GPIO_PIN_11
uint8_t DHT11_Init(void );//��ʼ��DHT11
uint8_t Read_DHT11_Data(uint8_t *temp,uint8_t *hum);//��ȡ��ʪ��
uint8_t DHT11_Read_Byte(void );//����һ���ֽ�
uint8_t DHT11_Read_Bit(void );//����һ��λ
uint8_t DHT11_Check(void );//����Ƿ����DHT11
void DHT11_ReSet(void );//��λDHT11
#endif //SGP30DHT11_DHT11_H
