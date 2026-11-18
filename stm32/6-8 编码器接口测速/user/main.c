#include "stm32f10x.h"                  // Device header
#include "Timer.h"
#include "OLED.h"
#include "Enconder.h"

short int Speed;
int main(void)
{
	OLED_Init();
	Timer_Init();
	Enconder_Init();
	OLED_ShowString(1,1,"Speed:");
	while(1)
	{
		OLED_ShowSignedNum(1,7,Speed,5);
	}
}

void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET)
	{
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
		Speed = Enconder_Get();

	}
}
