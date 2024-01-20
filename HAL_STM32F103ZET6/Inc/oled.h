//
// Created by LMF on 2024/1/3.
//

#ifndef STM32F103ZET6_OLED_H
#define STM32F103ZET6_OLED_H
#include "stm32f1xx.h"
#include "i2c.h"
#include "oledfont.h"
void OLED_SHowfloat(uint8_t x,uint8_t y,float num,uint8_t a,uint8_t b,uint8_t size);
//初始化命令
void WriteCmd(void );
void OLED_WR_CMD(uint8_t cmd);//写入命令
void OLED_WR_DATA(uint8_t data);//写入数据
void OLED_Init(void );//初始化
void OLED_Clear(void );//清屏
void OLED_Display_On(void );//开启显示屏显示
void OLED_Display_Off(void );//关闭显示屏显示
void OLED_Set_Pos(uint8_t x,uint8_t y);//设置坐标
void OLED_On(void );//开启显示屏
//显示数字
void OLED_ShowNum(uint8_t x,uint8_t y, unsigned int num,uint8_t len,uint8_t size2);
//显示字符
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t CharSize);
//显示字符串
void OLED_ShowString(uint8_t x,uint8_t y,uint8_t *chr,uint8_t CharSize);
//显示汉字
void OLED_ShowChinese(uint8_t x,uint8_t y,const unsigned  char chr[][32],uint8_t no);
//void OLED_
#endif //STM32F103ZET6_OLED_H
