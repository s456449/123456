#include "stm32f10x.h"                  // Device header
void Timer_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitTypeDefStructure;
	TIM_TimeBaseInitTypeDefStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitTypeDefStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitTypeDefStructure.TIM_Period=100-1;
	TIM_TimeBaseInitTypeDefStructure.TIM_Prescaler=7200-1;	//10ms 10000HZ
	TIM_TimeBaseInitTypeDefStructure.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitTypeDefStructure);
	
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_InitTypeDefStructure;
	NVIC_InitTypeDefStructure.NVIC_IRQChannel=TIM2_IRQn;
	NVIC_InitTypeDefStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitTypeDefStructure.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitTypeDefStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitTypeDefStructure);
	TIM_Cmd(TIM2,ENABLE);
}

/*
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET)
	{
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
		

	}
}
*/
