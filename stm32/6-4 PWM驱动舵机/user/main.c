#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "Key.h"
#include "Servo.h"
#include "PWM.h"
#include "Delay.h"
float Angle;
unsigned char KeyNum;
int main(void)
{
	OLED_Init();
	Key_Init();
	PWM_Init();
	
	OLED_ShowString(1,1,"Angle:");
	
	while(1)
	{
		KeyNum=Key_GetNum();
		Angle+=1;
		Delay_ms(10);
		if(KeyNum==1)
		{
			Angle+=30;
			if(Angle>180){Angle=0;}
		}
		Servo_SetAngle(Angle);
		OLED_ShowNum(1,7,Angle,3);
	}
}
