//
// Created by LMF on 2024/1/13.
//

#ifndef SGP30DHT11_SGP30_H
#define SGP30DHT11_SGP30_H
#include "stm32f1xx.h"
#define SGP30_SCL GPIO_PIN_5
#define SGP30_SDA GPIO_PIN_6
#define SGP30_PORT GPIOA
#define SGP30_SDA_READ() HAL_GPIO_ReadPin(SGP30_PORT,SGP30_SDA)
#define SGP30_read 0xb1 //SGP30�Ķ���ַ
#define SGP30_write 0xb0 //SGP30��д��ַ

void SGP30_IIC_Start(void );//����IIC��ʼ�ź�
void SGP30_IIC_Stop(void );//����IICֹͣ�ź�
void SGP30_IIC_Send_Byte(uint8_t txd);//IIC����һ���ֽ�
uint16_t SGP30_IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
uint8_t SGP30_IIC_Wait_Ack(void );//IIC�ȴ�ACK�ź�
void SGP30_IIC_Ack(void );//IIC����ACK�ź�
void SGP30_IIC_NAck(void );//IIC������ACK�ź�
void SGP30_IIC_Write_One_Byte(uint8_t daddr,uint8_t addr,uint8_t data);
uint8_t SGP30_IIC_Read_One_Byte(uint8_t daddr,uint8_t addr);
void SGP30_Init(void );
void SGP30_Write(uint8_t a,uint8_t b);
uint32_t  SGP30_Read(void );
#endif //SGP30DHT11_SGP30_H
