/*
ע�� ���㺯����÷��ں���ִ�У���Ȼ�ᱻд����ĺ������ǵ���
*/
#include "lcd5110.h"
//#include"math.h"

void LCD_Delay(int t)
{
	int i,j;
	for(i=t;i>0;i--)
		for(j=110;j>0;j--);
}

//------------GPIO������----------------------------
void LCD_GPIO_Config(void)
{	
	GPIO_InitTypeDef GPIO_InitStructure; 
	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);	// �ı�ָ���ܽŵ�ӳ�� GPIO_Remap_SWJ_JTAGDisable ��JTAG-DP ���� + SW-DP ʹ��
	RCC_APB2PeriphClockCmd(LCD_RCC_PORT, ENABLE);
	GPIO_InitStructure.GPIO_Pin = LCD_REST_BIT| LCD_SCE_BIT| LCD_DC_BIT| LCD_SDIN_BIT| LCD_SCLK_BIT; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(LCD_PORT, &GPIO_InitStructure); 
}
//----------------------------------Ӣ���ַ���-------------------------------------
// 6 x 8 font
// 1 pixel space at left and bottom
// λ�� = (ASCII - 32)*6
//----------------------------------------------------------------------------------
//****************************************************************************************************
// 	Ӣ���ַ���С
//****************************************************************************************************
#define WIDTH    6
#define HEIGHT   8
//****************************************************************************************************
// �����ַ���С
//****************************************************************************************************
#define WIDTH_CN	12
#define HEIGHT_CN	16
 
unsigned char lcd_display[]="0123456789";	//LCD_WriteNumber������ʹ��  

const char font[][6] =
{
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // space
	{ 0x00, 0x00, 0x00, 0x2f, 0x00, 0x00 },   // !
	{ 0x00, 0x00, 0x07, 0x00, 0x07, 0x00 },   // "
	{ 0x00, 0x14, 0x7f, 0x14, 0x7f, 0x14 },   // #
	{ 0x00, 0x24, 0x2a, 0x7f, 0x2a, 0x12 },   // $
	{ 0x00, 0x62, 0x64, 0x08, 0x13, 0x23 },   // %
	{ 0x00, 0x36, 0x49, 0x55, 0x22, 0x50 },   // &
	{ 0x00, 0x00, 0x05, 0x03, 0x00, 0x00 },   // '
	{ 0x00, 0x00, 0x1c, 0x22, 0x41, 0x00 },   // (
	{ 0x00, 0x00, 0x41, 0x22, 0x1c, 0x00 },   // )
	{ 0x00, 0x14, 0x08, 0x3E, 0x08, 0x14 },   // *
	{ 0x00, 0x08, 0x08, 0x3E, 0x08, 0x08 },   // +
	{ 0x00, 0x00, 0x00, 0xA0, 0x60, 0x00 },   // ,
	{ 0x00, 0x08, 0x08, 0x08, 0x08, 0x08 },   // -
	{ 0x00, 0x00, 0x60, 0x60, 0x00, 0x00 },   // .
	{ 0x00, 0x20, 0x10, 0x08, 0x04, 0x02 },   // /
	{ 0x00, 0x3E, 0x51, 0x49, 0x45, 0x3E },   // 0
	{ 0x00, 0x00, 0x42, 0x7F, 0x40, 0x00 },   // 1
	{ 0x00, 0x42, 0x61, 0x51, 0x49, 0x46 },   // 2
	{ 0x00, 0x21, 0x41, 0x45, 0x4B, 0x31 },   // 3
	{ 0x00, 0x18, 0x14, 0x12, 0x7F, 0x10 },   // 4
	{ 0x00, 0x27, 0x45, 0x45, 0x45, 0x39 },   // 5
	{ 0x00, 0x3C, 0x4A, 0x49, 0x49, 0x30 },   // 6
	{ 0x00, 0x01, 0x71, 0x09, 0x05, 0x03 },   // 7
	{ 0x00, 0x36, 0x49, 0x49, 0x49, 0x36 },   // 8
	{ 0x00, 0x06, 0x49, 0x49, 0x29, 0x1E },   // 9
	{ 0x00, 0x00, 0x36, 0x36, 0x00, 0x00 },   // :
	{ 0x00, 0x00, 0x56, 0x36, 0x00, 0x00 },   // ;
	{ 0x00, 0x08, 0x14, 0x22, 0x41, 0x00 },   // <
	{ 0x00, 0x14, 0x14, 0x14, 0x14, 0x14 },   // =
	{ 0x00, 0x00, 0x41, 0x22, 0x14, 0x08 },   // >
	{ 0x00, 0x02, 0x01, 0x51, 0x09, 0x06 },   // ?
	{ 0x00, 0x32, 0x49, 0x59, 0x51, 0x3E },   // @
	{ 0x00, 0x7C, 0x12, 0x11, 0x12, 0x7C },   // A
	{ 0x00, 0x7F, 0x49, 0x49, 0x49, 0x36 },   // B
	{ 0x00, 0x3E, 0x41, 0x41, 0x41, 0x22 },   // C
	{ 0x00, 0x7F, 0x41, 0x41, 0x22, 0x1C },   // D
	{ 0x00, 0x7F, 0x49, 0x49, 0x49, 0x41 },   // E
	{ 0x00, 0x7F, 0x09, 0x09, 0x09, 0x01 },   // F
	{ 0x00, 0x3E, 0x41, 0x49, 0x49, 0x7A },   // G
	{ 0x00, 0x7F, 0x08, 0x08, 0x08, 0x7F },   // H
	{ 0x00, 0x00, 0x41, 0x7F, 0x41, 0x00 },   // I
	{ 0x00, 0x20, 0x40, 0x41, 0x3F, 0x01 },   // J
	{ 0x00, 0x7F, 0x08, 0x14, 0x22, 0x41 },   // K
	{ 0x00, 0x7F, 0x40, 0x40, 0x40, 0x40 },   // L
	{ 0x00, 0x7F, 0x02, 0x0C, 0x02, 0x7F },   // M
	{ 0x00, 0x7F, 0x04, 0x08, 0x10, 0x7F },   // N
	{ 0x00, 0x3E, 0x41, 0x41, 0x41, 0x3E },   // O
	{ 0x00, 0x7F, 0x09, 0x09, 0x09, 0x06 },   // P
	{ 0x00, 0x3E, 0x41, 0x51, 0x21, 0x5E },   // Q
	{ 0x00, 0x7F, 0x09, 0x19, 0x29, 0x46 },   // R
	{ 0x00, 0x46, 0x49, 0x49, 0x49, 0x31 },   // S
	{ 0x00, 0x01, 0x01, 0x7F, 0x01, 0x01 },   // T
	{ 0x00, 0x3F, 0x40, 0x40, 0x40, 0x3F },   // U
	{ 0x00, 0x1F, 0x20, 0x40, 0x20, 0x1F },   // V
	{ 0x00, 0x3F, 0x40, 0x38, 0x40, 0x3F },   // W
	{ 0x00, 0x63, 0x14, 0x08, 0x14, 0x63 },   // X
	{ 0x00, 0x07, 0x08, 0x70, 0x08, 0x07 },   // Y
	{ 0x00, 0x61, 0x51, 0x49, 0x45, 0x43 },   // Z
	{ 0x00, 0x00, 0x7F, 0x41, 0x41, 0x00 },   // [
	{ 0x00, 0x55, 0x2A, 0x55, 0x2A, 0x55 },   // 55
	{ 0x00, 0x00, 0x41, 0x41, 0x7F, 0x00 },   // ]
	{ 0x00, 0x04, 0x02, 0x01, 0x02, 0x04 },   // ^
	{ 0x00, 0x40, 0x40, 0x40, 0x40, 0x40 },   // _
	{ 0x00, 0x00, 0x01, 0x02, 0x04, 0x00 },   // '
	{ 0x00, 0x20, 0x54, 0x54, 0x54, 0x78 },   // a
	{ 0x00, 0x7F, 0x48, 0x44, 0x44, 0x38 },   // b
	{ 0x00, 0x38, 0x44, 0x44, 0x44, 0x20 },   // c
	{ 0x00, 0x38, 0x44, 0x44, 0x48, 0x7F },   // d
	{ 0x00, 0x38, 0x54, 0x54, 0x54, 0x18 },   // e
	{ 0x00, 0x08, 0x7E, 0x09, 0x01, 0x02 },   // f
	{ 0x00, 0x18, 0xA4, 0xA4, 0xA4, 0x7C },   // g
	{ 0x00, 0x7F, 0x08, 0x04, 0x04, 0x78 },   // h
	{ 0x00, 0x00, 0x44, 0x7D, 0x40, 0x00 },   // i
	{ 0x00, 0x40, 0x80, 0x84, 0x7D, 0x00 },   // j
	{ 0x00, 0x7F, 0x10, 0x28, 0x44, 0x00 },   // k
	{ 0x00, 0x00, 0x41, 0x7F, 0x40, 0x00 },   // l
	{ 0x00, 0x7C, 0x04, 0x18, 0x04, 0x78 },   // m
	{ 0x00, 0x7C, 0x08, 0x04, 0x04, 0x78 },   // n
	{ 0x00, 0x38, 0x44, 0x44, 0x44, 0x38 },   // o
	{ 0x00, 0xFC, 0x24, 0x24, 0x24, 0x18 },   // p
	{ 0x00, 0x18, 0x24, 0x24, 0x18, 0xFC },   // q
	{ 0x00, 0x7C, 0x08, 0x04, 0x04, 0x08 },   // r
	{ 0x00, 0x48, 0x54, 0x54, 0x54, 0x20 },   // s
	{ 0x00, 0x04, 0x3F, 0x44, 0x40, 0x20 },   // t
	{ 0x00, 0x3C, 0x40, 0x40, 0x20, 0x7C },   // u
	{ 0x00, 0x1C, 0x20, 0x40, 0x20, 0x1C },   // v
	{ 0x00, 0x3C, 0x40, 0x30, 0x40, 0x3C },   // w
	{ 0x00, 0x44, 0x28, 0x10, 0x28, 0x44 },   // x
	{ 0x00, 0x1C, 0xA0, 0xA0, 0xA0, 0x7C },   // y
	{ 0x00, 0x44, 0x64, 0x54, 0x4C, 0x44 },   // z
	{ 0x00, 0x00, 0x08, 0x36, 0x41, 0x00 },   // 7b {
	{ 0x00, 0x00, 0x00, 0x7f, 0x00, 0x00 },   // 7c |
	{ 0x00, 0x00, 0x41, 0x36, 0x08, 0x00 },   // 7d }
	{ 0x00, 0x10, 0x08, 0x08, 0x10, 0x08 },   // 7e ~
	{ 0x00, 0x78, 0x46, 0x41, 0x46, 0x78 },   // 7f (delete)
};

//----------------------------------Symbol��-------------------------------------
// 6 x 8 Symbol 
//----------------------------------------------------------------------------------
const unsigned char symbol[][6] =
{
	{0x00, 0x08, 0x08, 0x2a, 0x1c, 0x08}, // 00 ->
	{0x00, 0x08, 0x1c, 0x2a, 0x08, 0x08}, // 01 <-
	{0x00, 0x04, 0x02, 0x7f, 0x02, 0x04}, // 02 ��
	{0x00, 0x10, 0x20, 0x7f, 0x20, 0x10}, // 03 ��
	{0x00, 0x15, 0x16, 0x7c, 0x16, 0x15}, // 04 ��
	{0x00, 0x03, 0x3b, 0x44, 0x44, 0x44}, // 05 ��
	{0x00, 0x03, 0x03, 0x7c, 0x14, 0x14}, // 06 �H
	{0x00, 0x44, 0x28, 0x10, 0x28, 0x44}, // 07 ��
	{0x00, 0x08, 0x08, 0x2a, 0x08, 0x08}, // 08 ��
	{0x00, 0x38, 0x44, 0x48, 0x30, 0x2c}, // 09 ��
	{0x00, 0xf8, 0x54, 0x54, 0x54, 0x28}, // 0a ��
	{0x00, 0x28, 0x54, 0x54, 0x44, 0x20}, // 0b ��
	{0x00, 0x3e, 0x49, 0x09, 0x09, 0x06}, // 0c ��
	{0x00, 0x38, 0x44, 0x4c, 0x54, 0x24}, // 0d ��
	{0x00, 0x40, 0x3f, 0x08, 0x08, 0x1f}, // 0e ��
	{0x00, 0x1f, 0x08, 0x08, 0x3f, 0x40}, // 0f ��
	{0x00, 0x3c, 0x4a, 0x4a, 0x4a, 0x3c}, // 10 ��
	{0x00, 0x58, 0x64, 0x04, 0x64, 0x58}, // 11 ��
	{0x00, 0x44, 0x3c, 0x04, 0x7c, 0x44}, // 12 ��
	{0x00, 0x30, 0x28, 0x10, 0x28, 0x18}, // 13 ��
	{0x00, 0x30, 0x28, 0x24, 0x28, 0x30}, // 14 ��
	{0x00, 0x08, 0x1c, 0x08, 0x08, 0x0e}, // 15 (Enter)
};

//----------------------------------Icon��-------------------------------------
// D:\Zimo3Pro �½�10w x 8h ���Ͻǵ�2�� ��ɫ����Һ����ģ ����ȡģ �ֽڵ���
//----------------------------------------------------------------------------------
static const char icon[][10] = {
	
	// battery
	{0x1c, 0x3e, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x3e}, // battery level 0	//index 0
	{0x1c, 0x3e, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x3e, 0x3e}, // battery level 1	//index 1
	{0x1c, 0x3e, 0x22, 0x22, 0x22, 0x22, 0x22, 0x3e, 0x3e, 0x3e}, // battery level 2	//index 2
	{0x1c, 0x3e, 0x22, 0x22, 0x22, 0x22, 0x3e, 0x3e, 0x3e, 0x3e}, // battery level 3	//index 3
	{0x1c, 0x3e, 0x22, 0x22, 0x22, 0x3e, 0x3e, 0x3e, 0x3e, 0x3e}, // battery level 4	//index 4
	{0x1c, 0x3e, 0x22, 0x22, 0x3e, 0x3e, 0x3e, 0x3e, 0x3e, 0x3e}, // battery level 5	//index 5
	{0x1c, 0x3e, 0x22, 0x3e, 0x3e, 0x3e, 0x3e, 0x3e, 0x3e, 0x3e}, // battery level 6	//index 6
	{0x1c, 0x3e, 0x3e, 0x3e, 0x3e, 0x3e, 0x3e, 0x3e, 0x3e, 0x3e}, // battery level 7	//index 7
	
	// resistance
	{0x08, 0x08, 0x1c, 0x14, 0x14, 0x14, 0x1c, 0x08, 0x08, 0x00},	//index 8
	
	// capacity A
	{0x08, 0x08, 0x08, 0x3e, 0x00, 0x1c, 0x2a, 0x08, 0x08, 0x00},	//index 9
	
	// capacity B
	{0x08, 0x08, 0x08, 0x3e, 0x00, 0x3e, 0x08, 0x08, 0x08, 0x00},	//index 10
	
	// transistor
	{0x00, 0x08, 0x08, 0x3e, 0x08, 0x14, 0x63, 0x00, 0x00, 0x00},	//index 11
	
	// inductance
	{0x08, 0x08, 0x08, 0x00, 0x3e, 0x20, 0x20, 0x08, 0x08, 0x08},	//index 12
	
	// diode
	{0x08, 0x08, 0x3e, 0x14, 0x08, 0x3e, 0x08, 0x08, 0x00, 0x00},	//index 13
	
	// GND
	{0x00, 0x00, 0x08, 0x18, 0x28, 0x4e, 0x28, 0x18, 0x08, 0x00},	//index 14
	
	// wave
	{0x08, 0x08, 0x0e, 0x02, 0x3e, 0x20, 0x38, 0x08, 0x08, 0x00},	//index 15
	
	// music A
	{0x00, 0x00, 0x60, 0x7e, 0x02, 0x02, 0x62, 0x7e, 0x00, 0x00},	//index 16
	
	// music B
	{0x00, 0x00, 0x20, 0x50, 0x50, 0x3f, 0x06, 0x0c, 0x00, 0x00},	//index 17
	
	// heart
	{0x00, 0x0c, 0x12, 0x22, 0x44, 0x22, 0x12, 0x0c, 0x00, 0x00},	//index 18
	
	// rocket or dick
	{0x00, 0x00, 0xe0, 0xbe, 0x41, 0xbe, 0xe0, 0x00, 0x00, 0x00},	//index 19
	
	// satellite
	{0x00, 0x32, 0x34, 0x48, 0x4f, 0x48, 0x34, 0x32, 0x00, 0x00},	//index 20
	
	// speaker
	{0x00, 0x00, 0x3c, 0x3c, 0x24, 0x42, 0xff, 0x00, 0x00, 0x00},	//index 21
	
	// play
	{0x00, 0x00, 0x00, 0x7f, 0x3e, 0x1c, 0x08, 0x00, 0x00, 0x00},	//index 22
	
	// pause
	{0x00, 0x00, 0x3e, 0x3e, 0x00, 0x00, 0x3e, 0x3e, 0x00, 0x00},	//index 23
	
	// stop
	{0x00, 0x00, 0x3e, 0x3e, 0x3e, 0x3e, 0x3e, 0x00, 0x00, 0x00},	//index 24
	
	// forward
	{0x00, 0x3e, 0x1c, 0x08, 0x00, 0x3e, 0x1c, 0x08, 0x00, 0x00},	//index 25
	
	// backward
	{0x00, 0x08, 0x1c, 0x3e, 0x00, 0x08, 0x1c, 0x3e, 0x00, 0x00},	//index 26
	
	// clock
	{0x00, 0x18, 0x24, 0x42, 0x9D, 0x91, 0x52, 0x24, 0x18, 0x00},	//index 27
	
	// train
	{0x18, 0x24, 0x82, 0x81, 0xF9, 0x81, 0x82, 0x24, 0x18, 0x00},	//index 28
	
	// key
	{0x18, 0x24, 0x5A, 0x5A, 0x24, 0x18, 0x10, 0x18, 0x10, 0x18},	//index 29
	
	// bluetooth
	{0x00, 0x00, 0x00, 0x24, 0x18, 0xFF, 0x5A, 0x24, 0x00, 0x00},	//index 30
	
	// right
	{0x00, 0x10, 0x20, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x00},	//index 31
	
	// message
	{0xFF, 0xC5, 0xA9, 0x91, 0xA1, 0xA1, 0x91, 0xA9, 0xC5, 0xFF},	//index 32
	
	// previous
	{0x00, 0x00, 0x00, 0x10, 0x38, 0x7C, 0xFE, 0x00, 0x00, 0x00},	//index 33
	
	// next
	{0x00, 0x00, 0x00, 0xFE, 0x7C, 0x38, 0x10, 0x00, 0x00, 0x00},	//index 34
	
	// signal A
	{0x00, 0x80, 0x00, 0xE0, 0x00, 0xF8, 0x00, 0xFE, 0x00, 0x00},	//index 35
	
	// signal B
	{0x3E, 0x00, 0x9C, 0x80, 0xF8, 0x80, 0x9C, 0x00, 0x3E, 0x00},	//index 36
	
	// recycle
	{0x02, 0x7E, 0x86, 0xFF, 0x87, 0xFF, 0x86, 0x7E, 0x02, 0x00},	//index 37 
	};
	
//----------------------------------�����ַ���-------------------------------------
//D:\��ģ����2.2���հ汾 �½�12*24����
//----------------------------------------------------------------------------------
const unsigned char chinese1[]={
0x00,0xF8,0x88,0x88,0x88,0xFF,0x88,0x88,0x88,0xF8,0x00,0x00,0x00,0x01,0x00,0x00,
0x00,0x0F,0x00,0x00,0x00,0x01,0x00,0x00, //��
};

//****************************************************************************************************
//**���ƣ�LCD_Init(void) 
//**���ܣ�LCD��ʼ��
//**˵����
//**��ע:
//**����:2011��2��27��
//**************************************************************************************************** 
void LCD_Init(void)
{
	LCD_SCE_H;
	LCD_REST_L;//����һ����LCD��λ�ĵ͵�ƽ����
	LCD_Delay(10);//78us
	LCD_REST_H;
	LCD_Delay(100);//799us
	LCD_WriteByte(0x21,0);//ʹ��ˮƽѰַ,������չָ��
	LCD_WriteByte(0x13,0);//��Һ��ƫ��ϵͳ 1:48
	LCD_WriteByte(0xbb,0);//�趨����Vop,�൱������ 
	LCD_WriteByte(0x20,0);//оƬ� ʹ�û���ָ���ˮƽѰַ
	LCD_WriteByte(0x0c,0);//�趨��ʾģʽ��������ʾ
	LCD_Clear();
}

//****************************************************************************************************
//**���ƣ�LCD_WriteByte(unsigned char dt, unsigned char command) 
//**���ܣ���������
//**˵����
//		dt:		����
//		command:	0 ����
//					1 ����
//**��ע:
//**����:2011��2��27��
//**************************************************************************************************** 
void LCD_WriteByte(unsigned char dt, unsigned char command)
{
	unsigned char i; 
	LCD_SCE_L;            	//ʹ��LCD
	if(command==0)   	//��������
		LCD_DC_L;
	else
		LCD_DC_H;         	//��������
	for(i=0;i<8;i++)
	{ 
		if(dt&0x80)
			LCD_SDIN_H;
		else
			LCD_SDIN_L;
		dt=dt<<1;		
		LCD_SCLK_L;		
		LCD_SCLK_H;
	}	
	LCD_DC_H;
	LCD_SCE_H;//�ر�LCD
	LCD_SDIN_H;
}

//****************************************************************************************************
//**���ƣ�LCD_Set_XY(unsigned char X, unsigned char Y) 
//**���ܣ���������
//**˵����X:0-83	�У���λpix��
//        Y:0-5		ҳ
//**��ע:
//**����:2011��2��27��
//**************************************************************************************************** 
void LCD_Set_XY(unsigned char X, unsigned char Y)
{
	Y|=0x40;
	X|=0x80;
	LCD_WriteByte(Y, 0);// ��
	LCD_WriteByte(X, 0);// ��
	LCD_SCE_H;
}
 
//****************************************************************************************************
//**���ƣ�LCD_Clear(void) 
//**���ܣ�LCD����
//**˵����
//**��ע:
//**����:2011��2��27��
//****************************************************************************************************
void LCD_Clear(void)
{
	unsigned char t,k;
	LCD_Set_XY(0,0);
	for(t=0;t<6;t++)
	{ 
		for(k=0;k<84;k++)
		{ 
			LCD_WriteByte(0x00,1);		
		} 
	}
}

//****************************************************************************************************
//**���ƣ�LCD_WriteChar(unsigned char x,unsigned char y,unsigned char c) 
//**���ܣ�дһ���ַ�
//**˵����x:0-83	�У���λpix��
//        y:0-5		ҳ
//		  c:�ַ�
//**��ע:
//**����:2011��2��27��
//****************************************************************************************************
void LCD_WriteChar(unsigned char x,unsigned char y,char c)
{
	unsigned char i,j ;
	const char *map = &font[0][0];
	c -= 32; //�任
	map += c *( HEIGHT/8*WIDTH);
   
	for(i=0;i<HEIGHT/8;i++)
	{
		LCD_Set_XY(x, y+i);
		for(j=0;j<WIDTH;j++)
			LCD_WriteByte(*map++, 1);
	}
}

//****************************************************************************************************
//**���ƣ�LCD_WriteString_en(unsigned char x,unsigned char y,unsigned char *s) 
//**���ܣ�дӢ���ַ���
//**˵����x:0-83	�У���λpix��
//        y:0-5		ҳ
//		  *s:�ַ�����ʼ��ַ
//**��ע:
//**����:2011��2��27��
//****************************************************************************************************
void LCD_WriteString_en(unsigned char x,unsigned char y,char *s)
{
	unsigned char i=0,j=0;
	while (*s)
	{
		LCD_WriteChar(x,y,*s++);
		x+=WIDTH;
		i++;  
		if(i>=(84/WIDTH))
		{
			x=0;
			y+=HEIGHT;
			i=0;
			j++;
		}
		if(j>=(48/HEIGHT))
		{
			return ;
		}  
    }
} 

//****************************************************************************************************
//**���ƣ�LCD_WriteChar_NOT(unsigned char x,unsigned char y,unsigned char c) 
//**���ܣ�дһ���ַ�	��ɫ
//**˵����x:0-83	��
//        y:0-5		ҳ
//		  c:�ַ�
//**��ע:
//**����:2011��2��27��
//****************************************************************************************************
void LCD_WriteChar_NOT(unsigned char x,unsigned char y,char c)
{
	unsigned char i,j ;
	const char *map = &font[0][0];
	c -= 32; //�任
	map += c *( HEIGHT/8*WIDTH);
   
	for(i=0;i<HEIGHT/8;i++)
	{
		LCD_Set_XY(x, y+i);
		for(j=0;j<WIDTH;j++)
			LCD_WriteByte(~(*map++), 1);
	}
}

//****************************************************************************************************
//**���ƣ�LCD_WriteString_en_NOT(unsigned char x,unsigned char y,unsigned char *s) 
//**���ܣ�дӢ���ַ���	��ɫ
//**˵����x:0-83	��
//        y:0-5		ҳ
//		  *s:�ַ�����ʼ��ַ
//**��ע:
//**����:2011��2��27��
//****************************************************************************************************
void LCD_WriteString_en_NOT(unsigned char x,unsigned char y,char *s)
{
	unsigned char i=0,j=0;
	while (*s)
	{
		LCD_WriteChar_NOT(x,y,*s++);
		x+=WIDTH;
		i++;  
		if(i>=(84/WIDTH))
		{
			x=0;
			y+=HEIGHT;
			i=0;
			j++;
		}
		if(j>=(48/HEIGHT))
		{
			return ;
		}  
    }
} 
//****************************************************************************************************
//**���ƣ�LCD_WriteNumber(unsigned char x,unsigned char y, unsigned long number) 
//**���ܣ�дһ����λ��
//**˵����x:0-83	�У���λpix��
//        y:0-5		ҳ
//		  number:Ҫ��ʾ����
//**��ע:
//**����:2011��2��27��
//****************************************************************************************************
void LCD_WriteNumber(unsigned char x,unsigned char y, unsigned long number)
{
	char num[10]={""},i,j,k;
	if(number==0)							//number 0 ʱ��
	{
		LCD_WriteChar(x, y,'0');
	}
	else
	{
		for(i=0;number>0;i++)
		{
			num[i]=lcd_display[number%10];	//ÿλ���ַ���ʾ
			number/=10; 
		}
		for(j=0;j<i/2;j++){k=num[j];num[j]=num[i-1-j];num[i-1-j]=k;}
		LCD_WriteString_en(x,y,num);
	}
}

//****************************************************************************************************
//**���ƣ�LCD_Write_cn(unsigned char row, unsigned char page,unsigned char c) 
//**���ܣ�дһ������
//**˵����row:0-83	�У���λpix��
//        page:0-5	ҳ
//		  c:���Ŷ�ά���������	�ַ�λ��
//**��ע:
//**����:2011��2��27��
//****************************************************************************************************
void LCD_WriteCn(unsigned char row, unsigned char page,unsigned char c) 
{
	unsigned char i;  	
	
	LCD_Set_XY(row, page);	// �У�ҳ 
	for(i=0; i<12;i++) 
	{
		LCD_WriteByte(chinese1[c*24+i],1); 		
	}
	LCD_Set_XY(row, page+1);// �У�ҳ 
	for(i=12; i<24;i++) 
	{
		LCD_WriteByte(chinese1[c*24+i],1);
	}	
}

//****************************************************************************************************
//**���ƣ�LCD_Write_symbol(unsigned char row, unsigned char page,unsigned char c) 
//**���ܣ���һ������
//**˵����row:0-83	�У���λpix��
//        page:0-5	ҳ
//		  c:���Ŷ�ά���������	�ַ�λ��
//**��ע:
//**����:2011��2��27��
//****************************************************************************************************
void LCD_WriteSymbol(unsigned char row, unsigned char page,unsigned char c) 
{
	unsigned char i;

	LCD_Set_XY(row, page);	// �У�ҳ 
	for(i=0; i<6;i++) 
	{
		LCD_WriteByte(symbol[c][i],1); 		
	}	
}

//****************************************************************************************************
//**���ƣ�LCD_Write_icon(unsigned char row, unsigned char page,unsigned char c)
//**���ܣ���һ��ͼ��
//**˵����row:0-83	�У���λpix��
//        page:0-5	ҳ
//		  c:ͼ���ά���������	�ַ�λ��
//**��ע:
//**����:2011��2��27��
//****************************************************************************************************
void LCD_WriteIcon(unsigned char row, unsigned char page,unsigned char c) 
{
	unsigned char i;  	
	
	LCD_Set_XY(row, page);	// �У�ҳ 
	for(i=0; i<10;i++) 
	{
		LCD_WriteByte(icon[c][i],1); 		
	}	
}

///**********************************************
//**����:LCD_DrawDot(unsigned char x,unsigned char y)
//**���ܣ�������λ�ô�һ����
//**˵����x:0-83
//        y:0-47
//**��ע:
//**����:2011��2��27��
//**********************************************/
void LCD_DrawDot(unsigned char x,unsigned char y) 	//��㺯��
{
	unsigned char y1,y2;
	y1=y/8;				//�ж����Ǹ��ֽ�
	y2=y%8;				//�ж�������ֽڵ��Ǹ�λ
	LCD_Set_XY(x,y1);				//���ô��ĵ�ַ
	LCD_WriteByte(0x01<<y2,1);		//��λ��ǰ
}
///**********************************************
//**����:LCD_DrawLineX(unsigned char x,unsigned char y1,unsigned char y2)
//**���ܣ�������λ�û�һ������
//**˵����x:0-83
//        y1<y2:0-47
//**��ע:
//**����:2011��2��27��
//**********************************************/
void LCD_DrawLineX(unsigned char x,unsigned char y1,unsigned char y2) 
{
	unsigned char temp;
	if(y1>y2)//y1>y2������������
	{
		temp=y1;
		y1=y2;
		y2=temp;
	}
	for(y1=y1;y1<y2;y1++)
	LCD_DrawDot(x,y1); //����Щ����ʾ����
}
///**********************************************
//**����:LCD_DrawLine(unsigned char x1,unsigned char x2,unsigned char y)
//**���ܣ�������λ�����һ������
//**˵����x1<x2:0-83
//        y:0-47
//**��ע:
//**����:2011��2��27��
//**********************************************/
void LCD_DrawLineY(unsigned char x1,unsigned char x2,unsigned char y) 
{
	unsigned char temp;
	if(x1>x2)//��x1>x2��������
	{
		temp=x1;
		x1=x2;
		x2=temp;
	}
	for(;x1<x2;x1++)
		LCD_DrawDot(x1,y);
}
/**********************************************
**����:LCD_DrawLine(int x1,int y1,int x2,int y2)
**���ܣ��������һ��ֱ��
**˵����x1 x2:0-83
        y1 y2:0-47
**��ע:
**����:2011��2��27��
**********************************************/
void LCD_DrawLine(int x1,int y1,int x2,int y2) //����֮�仭����ֱ��
{
	int x,y,dx,dy,s1,s2,temp,status,p,i;
	x=x1;
	y=y1;
	if(x1>x2) //�ж�x1,x2�Ĵ�С
	{
		dx=x1-x2; //
		s1=-1; //x������Ϊ-1
	}
	else
	{
		dx=x2-x1;
		s1=1; //x������Ϊ1
	}
	if(y1>y2)
	{
		dy=y1-y2;
		s2=-1;//y������Ϊ-1
	}
	else
	{
		dy=y2-y1;
		s2=1; //y������Ϊ1
	}
	if(dx<dy) //����y�ᣬ��y����ʾx
	{
		temp=dx;
		dy=dx;//x��y�ĺ���
		dx=temp;
		status=1;//��ʾ����Y��
	}
	else
	status=0;//��ʾ����x��
	p=2*dy-dx; //ʹ��Bresenhan�㷨
	for(i=1;i<dx;i++)
	{
		LCD_DrawDot(x,y); //�����
		if(p>0)
		{
			if(status==0)//����x��
			y+=s2;
			else
			x+=s1;
			p=p-2*dx;
		}
		if(status==0)
			x=x+s1;
		else
			y=y+s2;
		p=p+2*dy;
	}     
}