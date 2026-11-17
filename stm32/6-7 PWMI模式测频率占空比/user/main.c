#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "IC.h"
#include "PWM.h"
#include "Key.h"

unsigned char KeyNum=0;
unsigned int i=50,I;
int main(void)
{
	OLED_Init();
	IC_Init();
	PWM_Init();
	Key_Init();
	OLED_ShowString(1,1,"Freq:     Hz");
	OLED_ShowString(2,1,"Duty:     %");
	OLED_ShowString(3,1,"Compare:  %");
	PWM_SetPrescaler(720-1);
	PWM_SetCompare1(i);
	while(1)
	{
		KeyNum=Key_GetNum();
		if(KeyNum)
		{
			if(KeyNum==1&&i>=20){i-=10;}
			if(KeyNum==2&&i<=80){i+=10;}
			PWM_SetCompare1(i);
		}
		I=IC_GetDuty();
		OLED_ShowNum(1,6,IC_GetFreq(),5);
		OLED_ShowNum(2,9,I,2);
		OLED_ShowNum(3,9,i,2);
		
		
	}
}
