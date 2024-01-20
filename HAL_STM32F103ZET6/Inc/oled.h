//
// Created by LMF on 2024/1/3.
//

#ifndef STM32F103ZET6_OLED_H
#define STM32F103ZET6_OLED_H
#include "stm32f1xx.h"
#include "i2c.h"
#include "oledfont.h"
void OLED_SHowfloat(uint8_t x,uint8_t y,float num,uint8_t a,uint8_t b,uint8_t size);
//��ʼ������
void WriteCmd(void );
void OLED_WR_CMD(uint8_t cmd);//д������
void OLED_WR_DATA(uint8_t data);//д������
void OLED_Init(void );//��ʼ��
void OLED_Clear(void );//����
void OLED_Display_On(void );//������ʾ����ʾ
void OLED_Display_Off(void );//�ر���ʾ����ʾ
void OLED_Set_Pos(uint8_t x,uint8_t y);//��������
void OLED_On(void );//������ʾ��
//��ʾ����
void OLED_ShowNum(uint8_t x,uint8_t y, unsigned int num,uint8_t len,uint8_t size2);
//��ʾ�ַ�
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t CharSize);
//��ʾ�ַ���
void OLED_ShowString(uint8_t x,uint8_t y,uint8_t *chr,uint8_t CharSize);
//��ʾ����
void OLED_ShowChinese(uint8_t x,uint8_t y,const unsigned  char chr[][32],uint8_t no);
//void OLED_
#endif //STM32F103ZET6_OLED_H
