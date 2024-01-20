//
// Created by LMF on 2024/1/13.
//
#include "dht11.h"
#include "delay.h"
void DHT11_IO_OUT(void )
{
    GPIO_InitTypeDef GPIO_InitStructure;
//    DHT11_CLK();
__HAL_RCC_GPIOG_CLK_ENABLE();
    GPIO_InitStructure.Pin=DHT11_PIN;
    GPIO_InitStructure.Mode=GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Speed=GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStructure.Pull=GPIO_PULLUP;
    HAL_GPIO_Init(DHT11_PORT,&GPIO_InitStructure);
}
void DHT11_IO_IN(void ){
    GPIO_InitTypeDef GPIO_InitStructure;
//    DHT11_CLK();
__HAL_RCC_GPIOA_CLK_ENABLE();
    GPIO_InitStructure.Pin=DHT11_PIN;
    GPIO_InitStructure.Mode=GPIO_MODE_INPUT;
    GPIO_InitStructure.Pull=GPIO_PULLUP;
    HAL_GPIO_Init(DHT11_PORT,&GPIO_InitStructure);
}
void DHT11_ReSet(void ){
    DHT11_IO_OUT();
    HAL_GPIO_WritePin(DHT11_PORT,DHT11_PIN,GPIO_PIN_RESET);
    delay_ms(20);
    HAL_GPIO_WritePin(DHT11_PORT,DHT11_PIN,GPIO_PIN_SET);
    delay_us(30);
}
uint8_t DHT11_Check(void ){
    uint8_t retry=0;
    DHT11_IO_IN();
    while (GPIO_PIN_SET==HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN)&&retry<100)
    {
        retry++;
        delay_us(1);
    }
    if (retry>=100) return 1;
    else retry=0;
    while (GPIO_PIN_RESET==HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN)&&retry<100)
    {
        retry++;
        delay_us(1);
    }
    if (retry>=100)
        return 1;
    return 0;
}
uint8_t DHT11_Read_Bit(void ){
    uint8_t retry=0;
    while (GPIO_PIN_SET==HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN)&&retry<100)
    {
        retry++;
        delay_us(1);
    }
    retry=0;
    while (GPIO_PIN_RESET==HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN)&&retry<100)
    {
        retry++;
        delay_us(1);
    }
    delay_us(40);
    if (GPIO_PIN_SET==HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_11)) return 1;
    else return 0;
}
uint8_t DHT11_Read_Byte(void ){
    uint8_t i,dat;
    dat=0;
    for (i=0;i<8;i++)
    {
        dat<<=1;
        dat|=DHT11_Read_Bit();
    }
    return dat;
}
uint8_t Read_DHT11_Data(uint8_t *temp,uint8_t *hum){
    uint8_t buf[5];
    DHT11_ReSet();
    if(DHT11_Check() == 0)
    {
        for(uint8_t i=0;i<5;i++)
            buf[i]=DHT11_Read_Byte();
        if((buf[0]+buf[1]+buf[2]+buf[3])==buf[4])
        {
            *hum=buf[0];       //这里省略小数部分
            *temp=buf[2];
        }
    }
    else
        return 1;
    return 0;
}
uint8_t DHT11_Init(void ){
    DHT11_ReSet();
    return DHT11_Check();
}