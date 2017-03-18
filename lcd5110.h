#ifndef __LCD5110_H
#define __LCD5110_H

#include "stm32f10x.h"
//////////////////////////////////////////////
//------------------------------------------//
//  RST    ------------PA0  //片选					//
//  SCE    ------------PA1  //位选					//
//  D/C    ------------PA2  //1写数据 0写指令		//
//  SD     ------------PA3  //数据				 	//
//  SCLK   ------------PA4  //时钟				 	//
//  LCD    ------------3.3V //背光				 	//
//////////////////////////////////////////////
/*------5110端口和引脚宏定义--------*/  
#define LCD_RCC_PORT		RCC_APB2Periph_GPIOA
#define LCD_PORT			GPIOA		//5110所在端口 
#define LCD_REST_BIT		GPIO_Pin_0	//REST端口位
#define LCD_SCE_BIT			GPIO_Pin_1	//SCE端口位
#define LCD_DC_BIT			GPIO_Pin_2	//DC端口位
#define LCD_SDIN_BIT		GPIO_Pin_3	//SDIN端口位    
#define LCD_SCLK_BIT		GPIO_Pin_4	//SCLK端口位  

#define LCD_REST_L	GPIO_ResetBits(LCD_PORT, LCD_REST_BIT)	//复位,0复位
#define LCD_SCE_L	GPIO_ResetBits(LCD_PORT, LCD_SCE_BIT)	//片选
#define LCD_DC_L	GPIO_ResetBits(LCD_PORT, LCD_DC_BIT)	//1写数据，0写指令
#define LCD_SDIN_L	GPIO_ResetBits(LCD_PORT, LCD_SDIN_BIT)	//数据
#define LCD_SCLK_L	GPIO_ResetBits(LCD_PORT, LCD_SCLK_BIT)	//时钟

#define LCD_REST_H	GPIO_SetBits(LCD_PORT, LCD_REST_BIT)	//复位,0复位
#define LCD_SCE_H	GPIO_SetBits(LCD_PORT, LCD_SCE_BIT)		//片选
#define LCD_DC_H	GPIO_SetBits(LCD_PORT, LCD_DC_BIT)		//1写数据，0写指令
#define LCD_SDIN_H	GPIO_SetBits(LCD_PORT, LCD_SDIN_BIT)	//数据
#define LCD_SCLK_H	GPIO_SetBits(LCD_PORT, LCD_SCLK_BIT)	//时钟

//#define PI	3.141592653

void LCD_GPIO_Config(void);
void LCD_Init(void);
void LCD_WriteByte(unsigned char dt, unsigned char command);
void LCD_Set_XY(unsigned char X, unsigned char Y);
void LCD_Clear(void);
void LCD_WriteChar(unsigned char x,unsigned char y,char c);
void LCD_WriteString_en(unsigned char X,unsigned char Y,char *s);
void LCD_WriteChar_NOT(unsigned char x,unsigned char y,char c);
void LCD_WriteString_en_NOT(unsigned char X,unsigned char Y,char *s);
void LCD_WriteNumber(unsigned char x,unsigned char y, unsigned long number);
void LCD_WriteCn(unsigned char row, unsigned char page,unsigned char c);
void LCD_WriteSymbol(unsigned char row, unsigned char page,unsigned char c);
void LCD_WriteIcon(unsigned char row, unsigned char page,unsigned char c);
void LCD_DrawDot(unsigned char x,unsigned char y);
void LCD_DrawLineX(unsigned char x,unsigned char y1,unsigned char y2);
void LCD_DrawLineY(unsigned char x1,unsigned char x2,unsigned char y);
void LCD_DrawLine(int x1,int y1,int x2,int y2);

void LCD_Delay(int t);
#endif
