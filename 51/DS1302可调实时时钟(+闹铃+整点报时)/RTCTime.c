#include <REGX52.H>
#include "LCD1602.h"
#include "shared.h"
unsigned char TimeSetFlashFlag;
unsigned char TimeSetSelect;
char AlarmClock_Time[]={0,0,0};//时 分 启停:1启0停
unsigned char AlarmClockTimeGetFlag;

void TimeSet()
{
	if(KeyNum==2)//设置第TimeSetSelect位时间
	{
		TimeSetSelect++;
		if(TimeSetSelect>5){TimeSetSelect=0;}
	}
	if(KeyNum==3)//时间加
	{
		DS1302_Time[TimeSetSelect]++;
		//秒
		if(DS1302_Time[5]>59){DS1302_Time[5]=0;DS1302_Time[4]++;}
		//分
		if(DS1302_Time[4]>59){DS1302_Time[4]=0;DS1302_Time[3]++;}
		//时
		if(DS1302_Time[3]>23){DS1302_Time[3]=0;DS1302_Time[2]++;}
		//日
		if(DS1302_Time[1]==1||DS1302_Time[1]==3||DS1302_Time[1]==5||DS1302_Time[1]==7||
			DS1302_Time[1]==8||DS1302_Time[1]==10||DS1302_Time[1]==12)//日（大月）
		{
			if(DS1302_Time[2]>31){DS1302_Time[2]=1;DS1302_Time[1]++;}
		}
		if(DS1302_Time[1]==4||DS1302_Time[1]==6||DS1302_Time[1]==9||DS1302_Time[1]==11)//小月
		{
			if(DS1302_Time[2]>30){DS1302_Time[2]=1;DS1302_Time[1]++;}
		}
		if(DS1302_Time[1]==2)
		{
			if(DS1302_Time[0]%4==0)
			{
				if(DS1302_Time[2]>29){DS1302_Time[2]=1;DS1302_Time[1]++;}//闰年2月
			}
			else
			{
				if(DS1302_Time[2]>28){DS1302_Time[2]=1;DS1302_Time[1]++;}//平年2月
			}
		}
		//月
		if(DS1302_Time[1]>12){DS1302_Time[1]=1;DS1302_Time[0]++;}
		//年
		if(DS1302_Time[0]>99){DS1302_Time[0]=0;}
	}
	
	if(KeyNum==4)//时间减
	{
		DS1302_Time[TimeSetSelect]--;
		//秒
		if(DS1302_Time[5]<0){DS1302_Time[5]=59;DS1302_Time[4]--;}
		//分
		if(DS1302_Time[4]<0){DS1302_Time[4]=59;DS1302_Time[3]--;}
		//时
		if(DS1302_Time[3]<0){DS1302_Time[3]=23;DS1302_Time[2]--;}
		//日
		if(DS1302_Time[2]<1)
		{
			DS1302_Time[2]=31;DS1302_Time[1]--;
			if(DS1302_Time[1]==1||DS1302_Time[1]==3||DS1302_Time[1]==5||DS1302_Time[1]==7||
				DS1302_Time[1]==8||DS1302_Time[1]==10||DS1302_Time[1]==12)//日（大月）
			{
				if(DS1302_Time[2]>31){DS1302_Time[2]=31;}
			}
			if(DS1302_Time[1]==4||DS1302_Time[1]==6||DS1302_Time[1]==9||DS1302_Time[1]==11)//小月
			{
				if(DS1302_Time[2]>30){DS1302_Time[2]=30;}
			}
			if(DS1302_Time[1]==2)
			{
				if(DS1302_Time[0]%4==0)
				{
					if(DS1302_Time[2]>29){DS1302_Time[2]=29;}//闰年2月
				}
				else
				{
					if(DS1302_Time[2]>28){DS1302_Time[2]=28;}//平年2月
				}
			}
		}
		//月
		if(DS1302_Time[1]<1){DS1302_Time[1]=12;DS1302_Time[0]--;}
		//年
		if(DS1302_Time[0]<0){DS1302_Time[0]=99;}
	}
	if(TimeSetSelect==0 && TimeSetFlashFlag==1){LCD_ShowString(1,1,"  ");}
	else {LCD_ShowNum(1,1,DS1302_Time[0],2);}
	if(TimeSetSelect==1 && TimeSetFlashFlag==1){LCD_ShowString(1,4,"  ");}
	else {LCD_ShowNum(1,4,DS1302_Time[1],2);}
	if(TimeSetSelect==2 && TimeSetFlashFlag==1){LCD_ShowString(1,7,"  ");}
	else {LCD_ShowNum(1,7,DS1302_Time[2],2);}
	if(TimeSetSelect==3 && TimeSetFlashFlag==1){LCD_ShowString(2,1,"  ");}
	else {LCD_ShowNum(2,1,DS1302_Time[3],2);}
	if(TimeSetSelect==4 && TimeSetFlashFlag==1){LCD_ShowString(2,4,"  ");}
	else {LCD_ShowNum(2,4,DS1302_Time[4],2);}
	if(TimeSetSelect==5 && TimeSetFlashFlag==1){LCD_ShowString(2,7,"  ");}
	else {LCD_ShowNum(2,7,DS1302_Time[5],2);}
}

void AlarmClockTimeGet()
{
	unsigned char i;
	if(AlarmClockTimeGetFlag)
	{
		for(i=0;i<2;i++)
		{
			AlarmClock_Time[i]=DS1302_Time[i+3];
		}
		AlarmClockTimeGetFlag=0;
	}
}

void AlarmClockSet()
{
	AlarmClockTimeGet();
	if(KeyNum==2)//设置第TimeSetSelect位
	{
		TimeSetSelect++;
		if(TimeSetSelect>2){TimeSetSelect=0;}
	}
	if(KeyNum==3)//值加
	{
		AlarmClock_Time[TimeSetSelect]++;
		//启停
		if(AlarmClock_Time[2]>1){AlarmClock_Time[2]=0;}
		//分
		if(AlarmClock_Time[1]>59){AlarmClock_Time[1]=0;AlarmClock_Time[0]++;}
		//时
		if(AlarmClock_Time[0]>23){AlarmClock_Time[0]=0;}
		
	}
	
	if(KeyNum==4)//值减
	{
		AlarmClock_Time[TimeSetSelect]--;
		//启停
		if(AlarmClock_Time[2]<0){AlarmClock_Time[2]=1;}
		//分
		if(AlarmClock_Time[1]<0){AlarmClock_Time[1]=59;AlarmClock_Time[0]--;}
		//时
		if(AlarmClock_Time[0]<0){AlarmClock_Time[0]=23;}
	}
	if(TimeSetSelect==0 && TimeSetFlashFlag==1){LCD_ShowString(2,1,"  ");}
	else {LCD_ShowNum(2,1,AlarmClock_Time[0],2);}
	
	if(TimeSetSelect==1 && TimeSetFlashFlag==1){LCD_ShowString(2,4,"  ");}
	else {LCD_ShowNum(2,4,AlarmClock_Time[1],2);}
	
	if(TimeSetSelect==2 && TimeSetFlashFlag==1){LCD_ShowString(2,10,"   ");}
	else if(AlarmClock_Time[2]==0){LCD_ShowString(2,10,"OFF");}
	else if(AlarmClock_Time[2]==1){LCD_ShowString(2,10,"ON ");}
}
