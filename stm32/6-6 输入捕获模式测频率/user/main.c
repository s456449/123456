#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "IC.h"
#include "PWM.h"

unsigned char Compare=50;
int main(void)
{
	OLED_Init();
	IC_Init();
	PWM_Init();
	OLED_ShowString(1,1,"Freq:     Hz");
	OLED_ShowString(2,1,"Compare:  %");
	PWM_SetPrescaler(720-1);
	PWM_SetCompare1(Compare);
	while(1)
	{
		OLED_ShowNum(1,6,IC_GetFreq(),5);
		OLED_ShowNum(2,9,Compare,2);
		
	}
}
