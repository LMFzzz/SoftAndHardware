//
// Created by LMF on 2024/1/17.
//
#include "sgp30.h"
#include "tim.h"
#include "usart.h"

void SGP30_GPIO_Init(void ){
    GPIO_InitTypeDef GPIO_InitStructure;
    __HAL_RCC_GPIOA_CLK_ENABLE();
    GPIO_InitStructure.Pin=SGP30_SCL;
    GPIO_InitStructure.Mode=GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Speed=GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(SGP30_PORT,&GPIO_InitStructure);
    __HAL_RCC_GPIOA_CLK_ENABLE();
    GPIO_InitStructure.Pin=SGP30_SDA;
    HAL_GPIO_Init(SGP30_PORT,&GPIO_InitStructure);
}
void SDA_OUT(void ){
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.Pin=SGP30_SDA;
    GPIO_InitStructure.Mode=GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Speed=GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(SGP30_PORT,&GPIO_InitStructure);
}
void SDA_IN(void ){
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.Pin=SGP30_SDA;
    GPIO_InitStructure.Mode=GPIO_MODE_INPUT;
    GPIO_InitStructure.Speed=GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(SGP30_PORT,&GPIO_InitStructure);
}
//����IIC��ʼ�ź�
void SGP30_IIC_Start(void )
{
    SDA_OUT();
    SGP30_SDA_H();
    SGP30_SCL_H();
    delay_us(20);
    SGP30_SDA_L();
    delay_us(20);
    SGP30_SCL_L();
}
//����IICֹͣ�ź�
void SGP30_IIC_Stop(void )
{
    SDA_OUT();
    SGP30_SCL_L();
    SGP30_SDA_L();
    delay_us(20);
    SGP30_SCL_H();
    SGP30_SDA_H();
    delay_us(20);
}
//�ȴ�Ӧ���ź�
uint8_t SGP30_IIC_Wait_Ack(void )
{
    uint8_t ucErrTime=0;
    SDA_IN();
    SGP30_SDA_H();
    delay_us(10);
    SGP30_SCL_H();
    delay_us(10);
    while (SGP30_SDA_READ()){
        ucErrTime++;
        if (ucErrTime>250)
        {
            SGP30_IIC_Stop();
            return 1;
        }
    }
    SGP30_SCL_L();
    return 0;
}
//����AckӦ��
void SGP30_IIC_Ack(void ){
    SGP30_SCL_L();
    SDA_OUT();
    SGP30_SDA_L();
    delay_us(20);
    SGP30_SCL_H();
    delay_us(20);
    SGP30_SCL_L();
}
//������ACKӦ��
void SGP30_IIC_NAck(void ){
    SGP30_SCL_L();
    SDA_OUT();
    SGP30_SDA_H();
    delay_us(20);
    SGP30_SCL_H();
    delay_us(20);
    SGP30_SCL_L();
}
//IIC����һ���ֽ�
void SGP30_IIC_Send_Byte(uint8_t txd)
{
    uint8_t t;
    SDA_OUT();
    SGP30_SCL_L();
    for (t=0;t<8;t++)
    {
        if ((txd&0x80)>>7)
            SGP30_SDA_H();
        else
            SGP30_SDA_L();
        txd<<=1;
        delay_us(20);
        SGP30_SCL_H();
        delay_us(20);
        SGP30_SCL_L();
        delay_us(20);
    }
    delay_us(20);
}
//��һ���ֽ�
uint16_t SGP30_IIC_Read_Byte(uint8_t ack)
{
    uint8_t i;
    uint16_t receive=0;
    SDA_IN();
    for (i=0;i<8;i++)
    {
        SGP30_SCL_L();
        delay_us(20);
        SGP30_SCL_H();
        receive<<=1;
        if (SGP30_SDA_READ())
            receive++;
        delay_us(20);
    }
    if (!ack)
        SGP30_IIC_NAck();
    else
        SGP30_IIC_Ack();
    return receive;
}
//��ʼ��
void SGP30_Init(void )
{
    SGP30_GPIO_Init();
    SGP30_Write(0x20,0x03);
}
void SGP30_Write(uint8_t a,uint8_t b){
    SGP30_IIC_Start();
    SGP30_IIC_Send_Byte(SGP30_write);
    SGP30_IIC_Wait_Ack();
    SGP30_IIC_Send_Byte(a);
    SGP30_IIC_Wait_Ack();
    SGP30_IIC_Send_Byte(b);
    SGP30_IIC_Wait_Ack();
    SGP30_IIC_Stop();
    HAL_Delay(100);
}
uint32_t SGP30_Read(void ){
    uint32_t dat;
    uint8_t crc;
    SGP30_IIC_Start();
    SGP30_IIC_Send_Byte(SGP30_read);
    SGP30_IIC_Wait_Ack();
    dat= SGP30_IIC_Read_Byte(1);
    dat<<=8;
    dat+= SGP30_IIC_Read_Byte(1);
    crc= SGP30_IIC_Read_Byte(1);
    crc=crc;
    dat<<=8;
    dat+= SGP30_IIC_Read_Byte(1);
    dat<<=8;
    dat+= SGP30_IIC_Read_Byte(0);
    SGP30_IIC_Stop();
    return (dat);
}