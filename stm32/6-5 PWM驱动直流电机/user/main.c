#include "stm32f10x.h"                  // Device header
#include "PWM.h"
#include "Delay.h"
#include "Moter.h"
#include "OLED.h"
#include "Key.h"

unsigned char KeyNum,Mark=1;
unsigned char Speed;
int main(void)
{
	Key_Init();
	OLED_Init();
	Moter_Init();
	Moter_SetSpeed(0);
	OLED_ShowString(1,1,"Speed:");
	OLED_ShowNum(1,7,Speed,3);
	while(1)
	{
		KeyNum=Key_GetNum();
		if(KeyNum==1)
		{
			if(Mark){Speed+=20;}
			else{Speed-=20;}
			if(Speed>=100){Mark=0;}
			if(Speed<=0){Mark=1;}
			OLED_ShowNum(1,7,Speed,3);
			Moter_SetSpeed(Speed);
		}
	}
}
