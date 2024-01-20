//
// Created by LMF on 2023/12/31.
//
#include "dht11.h"
#include "tim.h"
/*
 *TIM3��ʱ��ʵ��us����ʱ
 */


//���
void DHT11_OUT(void ){
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /*Configure GPIO pin : PB12 */
    GPIO_InitStruct.Pin = GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);
}
//����
void DHT11_IN(void ){
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /*Configure GPIO pin : PB12 */
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pin = GPIO_PIN_11;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);
}
//��λDHT11
void DHT11_Reset(void ){
    DHT11_OUT();                                          //����Ϊ���
    HAL_GPIO_WritePin(GPIOG, GPIO_PIN_11, GPIO_PIN_RESET);     //��������
    HAL_Delay(20);                                             //�ӳ�20ms
    HAL_GPIO_WritePin(GPIOG, GPIO_PIN_11, GPIO_PIN_SET);       //��������
    delay_us(30);
}
//�ȴ�DHT11��Ӧ
uint8_t DHT11_Check(void)
{
    uint8_t retry=0;
    DHT11_IN();                                           //����Ϊ����
    while(GPIO_PIN_SET==HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_11) && retry<100)
    {
        retry++;
        delay_us(1);
    }
    if(retry>=100)
        return 1;
    else
        retry=0;

    while(GPIO_PIN_RESET==HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_11) && retry<100)
    {
        retry++;
        delay_us(1);
    }
    if(retry>=100)
        return 1;
    return 0;
}
//��DHT11��ȡһ��λ
uint8_t DHT11_Read_Bit(void)
{
    uint8_t retry=0;
    while(GPIO_PIN_SET==HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_11) && retry<100)
    {
        retry++;
        delay_us(1);
    }
    retry=0;

    while(GPIO_PIN_RESET==HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_11) && retry<100)
    {
        retry++;
        delay_us(1);
    }
    delay_us(40);

    if(GPIO_PIN_SET==HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_11))
        return 1;
    else
        return 0;
}

//��DHT11��ȡһ���ֽ�
uint8_t DHT11_Read_Byte(void)
{
    uint8_t dat=0;
    for(uint8_t i=0;i<8;i++)
    {
        dat <<= 1;
        dat |= DHT11_Read_Bit();
    }
    return dat;
}
//��DHT11��ȡһ������
uint8_t DHT11_Read_Data(uint8_t* humiH,uint8_t *humiL,uint8_t* tempH,uint8_t *tempL)
{
    uint8_t buf[5];
    DHT11_Reset();
    if(DHT11_Check() == 0)
    {
        for(uint8_t i=0;i<5;i++)
            buf[i]=DHT11_Read_Byte();
        if((buf[0]+buf[1]+buf[2]+buf[3])==buf[4])
        {
            *humiH=buf[0];       //����ʡ��С������
            *humiL=buf[1];
            *tempH=buf[2];
            *tempL=buf[3];
        }
    }
    else
        return 1;
    return 0;
}
uint8_t DHT11_Init(void ){
    GPIO_InitTypeDef GPIO_InitStructure;
    __HAL_RCC_GPIOG_CLK_ENABLE();
    GPIO_InitStructure.Pin=GPIO_PIN_11;
    GPIO_InitStructure.Mode=GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull=GPIO_NOPULL;
    GPIO_InitStructure.Speed=GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOG,&GPIO_InitStructure);
    HAL_GPIO_WritePin(GPIOG,GPIO_PIN_11,GPIO_PIN_SET);
    DHT11_Reset();
    return DHT11_Check();
}