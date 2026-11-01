#include <REGX52.H>
#include "Delay.h"
#include "LCD1602.h"
#include "DS18B20.h"
#include "OneWire.h"
#include "P3Key.h"
#include "Timer0.h"
#include "Buzzer.h"

float T;
float T_Temp;
unsigned char KeyNum;
int Tlow=10;
int Thigh=30;
void main()
{
	DS18B20_ConvertT();
	Delay(1000);
	Timer0_Init();
	LCD_Init();
	LCD_ShowString(1,1,"TL:");
	LCD_ShowString(1,9,"TH:");
	LCD_ShowNum(1,4,Tlow,3);
	LCD_ShowNum(1,12,Thigh,3);
	LCD_ShowString(2,1,"T:");
	LCD_ShowChar(2,7,'.');
	
	while(1)
	{
		if(T_Temp!=T)
		{
			if(T<0)
			{
				LCD_ShowChar(2,3,'-');
				LCD_ShowNum(2,4,-T,3);
				LCD_ShowNum(2,8,(unsigned long)(-T*10000)%10000,4);
			}
			else
			{
				LCD_ShowChar(2,3,'+');
				LCD_ShowNum(2,4,T,3);
				LCD_ShowNum(2,8,(unsigned long)(T*10000)%10000,4);
			}
		}
		KeyNum=Key();
		if(KeyNum)
		{
			if(KeyNum==1)
			{
				Tlow--;
			}
			if(KeyNum==2)
			{
				Tlow++;
				while(Tlow>=Thigh){Thigh++;}
			}
			if(KeyNum==3)
			{
				Thigh--;
				while(Tlow>=Thigh){Tlow--;}
			}
			if(KeyNum==4)
			{
				Thigh++;
			}
			LCD_ShowNum(1,4,Tlow,3);
			LCD_ShowNum(1,12,Thigh,3);
		}
	}
}

void Timer0_Routine() interrupt 1
{
	static unsigned int T0count,T0count2;//静态局部变量，不丢失值
	TL0=0x66;
	TH0=0xFC;
	T0count++;
	T0count2++;
	if(T0count>=20)
	{
		T0count=0;
		Key_Update();
		DS18B20_ConvertT();
		T_Temp=T;
		T=DS18B20_ReadT();
	}
	if(T0count2>=500)
	{
		T0count2=0;
		if(T>Thigh|T<Tlow)
		{
			Buzzer_Time(50);
		}
	}
}