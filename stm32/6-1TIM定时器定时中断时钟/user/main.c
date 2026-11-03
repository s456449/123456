#include "stm32f10x.h"                  // Device header
#include "Timer.h"
#include "OLED.h"

unsigned int hour,min,sec,minsec;
int main(void)
{
	OLED_Init();
	Timer_Init();
	OLED_ShowString(1,1,"Time");
	OLED_ShowString(2,3,".  .  .");
	OLED_ShowNum(2,1,hour,2);
	OLED_ShowNum(2,4,min,2);
	OLED_ShowNum(2,7,sec,2);
	OLED_ShowNum(2,10,minsec,2);
	while(1)
	{
		if(minsec>99)
		{
			minsec=0;
			sec++;
			if(sec>59)
			{
				sec=0;
				min++;
				if(min>59)
				{
					min=0;
					hour++;
					if(hour>23)
					{
						hour=0;
					}
					OLED_ShowNum(2,1,hour,2);
				}
				OLED_ShowNum(2,4,min,2);
			}
			OLED_ShowNum(2,7,sec,2);
		}
		OLED_ShowNum(2,10,minsec,2);
	}
}
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET)
	{
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
		minsec++;

	}
}
