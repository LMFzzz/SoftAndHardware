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

uint8_t DHT11_Init(void);//��ʼ��DHT11
uint8_t DHT11_Read_Data(uint8_t *humiH,uint8_t *humiL,uint8_t *tempH,uint8_t *tempL);//��ȡ��ʪ��
uint8_t DHT11_Read_Byte(void);//����һ���ֽ�
uint8_t DHT11_Read_Bit(void);//����һ��λ
uint8_t DHT11_Check(void);//����Ƿ����DHT11
void DHT11_Rst(void);//��λDHT11
#endif //DHT11_DHT11_H
