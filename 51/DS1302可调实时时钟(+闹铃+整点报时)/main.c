#include <REGX52.H>
#include "DS1302.h"
#include "LCD1602.h"
#include "P3key.h"
#include "Timer0.h"
#include "RTCTime.h"
#include "shared.h"

//蜂鸣器端口：
sbit Buzzer=P1^7;

unsigned char MODE;
unsigned char AlarmClockOpenFlag,OnTimeClockOpenFlag;
static unsigned int AlarmClockTime_Num,OnTimeClockTime_Num;

void TimeShow()
{
	LCD_ShowNum(1,1,DS1302_Time[0],2);
	LCD_ShowNum(1,4,DS1302_Time[1],2);
	LCD_ShowNum(1,7,DS1302_Time[2],2);
	LCD_ShowNum(2,1,DS1302_Time[3],2);
	LCD_ShowNum(2,4,DS1302_Time[4],2);
	LCD_ShowNum(2,7,DS1302_Time[5],2);
	if(AlarmClock_Time[2]==0){LCD_ShowChar(1,16,' ');}
}

void Stop_AlarmClock()
{
	AlarmClockOpenFlag=0;
	AlarmClockTime_Num=0;
	OnTimeClockTime_Num=0;
	OnTimeClockOpenFlag=0;
	Buzzer=1;
}

void ClockBuzzer()
{
	static unsigned char NowState=0xFF;
	unsigned char LastState=NowState;
	NowState=DS1302_Time[4];
	if(NowState!=LastState)//每分钟检测一次
	{
		if(AlarmClock_Time[2])
		{
			if(AlarmClock_Time[1]==DS1302_Time[4]
				&&AlarmClock_Time[0]==DS1302_Time[3])
			{
				AlarmClockOpenFlag=1;
			}
		}
		
		if(NowState==0&&AlarmClockOpenFlag==0)
		{
			OnTimeClockOpenFlag=1;
		}
	}
	
	if(KeyNum==2 && AlarmClockOpenFlag==1)
	{
		Stop_AlarmClock();
	}
}

void main()
{
	Timer0_Init();
	LCD_Init();
	DS1302_Init();
	DS1302_SetTime();
	Buzzer=1;
	LCD_ShowString(1,3,"-  -");
	LCD_ShowString(2,3,"-  -");
	LCD_ShowString(1,10,"Time   ");
	while(1) 
	{	
		KeyNum=Key();
		if(KeyNum==1)
		{
			if(MODE==0){MODE=1;TimeSetSelect=0;LCD_ShowString(1,3,"-  -   TimeSet");}
			
			else if(MODE==1)
			{
				MODE=2;
				TimeSetSelect=0;TimeSet();DS1302_SetTime();
				if(AlarmClock_Time[2]==0)
				{AlarmClockTimeGetFlag=1;}
				LCD_ShowString(1,1,"         Alarm  ");
				LCD_ShowNum(2,7,0,2);
			}
			
			else if(MODE==2)
			{
				MODE=0;
				LCD_ShowString(1,3,"-  -   Time   ");LCD_ShowString(2,10,"   ");
				if(AlarmClock_Time[2]){LCD_ShowChar(1,16,'A');}
			}
			KeyNum=0;
		}
		
		switch(MODE)
		{
			case 0:DS1302_ReadTime();TimeShow();ClockBuzzer();break;
			case 1:TimeSet();break;
			case 2:AlarmClockSet();break;
		}
	}
}


void Timer0_Routine() interrupt 1
{
	static unsigned int T0count1,T0count2;//静态局部变量，不丢失值
	TL0=0x33;//0.5ms
	TH0=0xFE;
	T0count1++;
	if(T0count1>=40)//20ms
	{
		T0count1=0;
		Key_Update();
		if(MODE)
		{
			static unsigned char FlashCnt=0;
			if(++FlashCnt>=12)
			{
				FlashCnt=0;TimeSetFlashFlag=!TimeSetFlashFlag;
			}
		}
	}
	
	if(AlarmClockOpenFlag||OnTimeClockOpenFlag)
	{
		T0count2++;
		if(T0count2>=1000)
		{
			T0count2=0;
			if(AlarmClockOpenFlag)
			{
				Buzzer=!Buzzer;
				AlarmClockTime_Num++;
				if(AlarmClockTime_Num>=600)//0.5s *2*60*5(5分钟自动关闭)
				{
					Stop_AlarmClock();
					
				}
			}
			
			if(OnTimeClockOpenFlag&&AlarmClockOpenFlag==0)
			{
				Buzzer=!Buzzer;
				OnTimeClockTime_Num++;
				if(OnTimeClockTime_Num>=6)//0.5s *2*3(3秒自动关闭)
				{
					Stop_AlarmClock();
				}
			}
		}
	}
	
}