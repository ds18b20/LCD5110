/******************** (C) COPYRIGHT 2011 ********************
 * �ļ���  ��led.c
 * ����    ��led Ӧ�ú�����
 *          
 * ʵ��ƽ̨��
 * Ӳ�����ӣ�PC3 - LED1
 *           PC4 - LED2
 *           PC5 - LED3
 * ����    ��mrt2  QQ: 313303034
 * ʱ��    ��2011-06-01
 * �汾    ��V1.0
**********************************************************************************/

#include "led.h"

void LED_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE );
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //max
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOC, GPIO_Pin_6 | GPIO_Pin_7);	 // turn on all led
}


/******************* (C) COPYRIGHT 2011 *******************/
