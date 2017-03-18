/******************** (C) COPYRIGHT 2011 ********************
 * �ļ���  ��main.c
 * ����    ��         
 * ʵ��ƽ̨��
 * ��汾  ��ST3.0.0
 *
 * ����    ��
**********************************************************************************/

#include "stm32f10x.h"
#include "lcd5110.h"

/* 
 * ��������main
 * ����  : ������
 * ����  ����
 * ���  : ��
 */
int main(void)
{
	unsigned char i;
	/* ����ϵͳʱ��Ϊ72M */
	SystemInit();   
	LCD_GPIO_Config();
	LCD_Init();
	LCD_Clear();
	{		
		LCD_DrawLine(0,30,30,47);
		//LCD_WriteByte(0x0d,0);	//cmd(0x0d)	//��ɫ��ʾ	
		LCD_WriteString_en_NOT(0,0,"dlut.edu.cn");
		//LCD_WriteByte(0x0c,0);
		LCD_WriteCn(15, 2, 0);
		LCD_WriteCn(35, 2, 1);
		LCD_WriteCn(55, 2, 2);

		LCD_WriteSymbol(70, 0, 21);

		//LCD_WriteIcon(73, 0, 28);
		LCD_WriteIcon(73, 1, 29);
		LCD_WriteIcon(73, 2, 30);
		LCD_WriteIcon(73, 3, 31);
		//LCD_WriteIcon(73, 4, 36);
		LCD_WriteIcon(73, 5, 37);
		LCD_DrawDot(0,0);
	}
	while (1)
	{
		
		for(i=0;i<38;i++)
		{
			LCD_Delay(10000);
			LCD_Delay(10000);
			LCD_Delay(10000);
			LCD_Delay(10000);
			LCD_Delay(10000);
			LCD_WriteIcon(73, 1, i);
		}
	}
}	


/******************* (C) COPYRIGHT 2011 *****END OF FILE****/
