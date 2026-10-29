#include "stm32f10x.h"                  // Device header
uint16_t LED[]={GPIO_Pin_0,GPIO_Pin_1,GPIO_Pin_2,GPIO_Pin_3,GPIO_Pin_4,GPIO_Pin_5,GPIO_Pin_6,GPIO_Pin_7,GPIO_Pin_8,GPIO_Pin_9,GPIO_Pin_10,GPIO_Pin_11,GPIO_Pin_12,GPIO_Pin_13,GPIO_Pin_14,GPIO_Pin_15,GPIO_Pin_All};

void LED_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_AInitStruct;
	GPIO_AInitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_AInitStruct.GPIO_Pin=GPIO_Pin_All;
	GPIO_AInitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_AInitStruct);
}
void LED_ON(unsigned int x)
{
	GPIO_ResetBits(GPIOA,LED[x]);
}
void LED_OFF(unsigned int x)
{
	GPIO_SetBits(GPIOA,LED[x]);
}
