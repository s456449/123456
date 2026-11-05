#include <REGX52.H>
#include "Timer0.h"
#include "Delay.h"
#include "P3Key.h"
#include "ShuMaGuan.h"

sbit Motor=P1^0;

code unsigned char CompareTable[4] = {0, 50, 75, 100};
static unsigned char T0count1,T0count2,T0flag;//静态局部变量，不丢失值
unsigned char Compare;
unsigned char KeyNum,Speed;
void main()
{
	Motor=0;
	Timer0_Init();
	shumaguan_SetBuf(1,Speed);
	while(1)
	{
		if(T0flag>100){T0flag=0;Key_Update();}
		KeyNum=Key();
		if(KeyNum)
		{
			if(KeyNum==1&&Speed!=0){Speed--;}
			if(KeyNum==2&&Speed<3){Speed++;}
			if(KeyNum==3){Speed=0;}
			if(KeyNum==4){Speed++;if(Speed>3){Speed=0;}}
			Compare=CompareTable[Speed];
			shumaguan_SetBuf(1,Speed);
		}
	}

}
void Timer0_Routine() interrupt 1
{
	TL0=0xA4;
	TH0=0xFF;//0.1ms
	T0count1++;
	if(T0count1>=20){T0count1=0;T0flag++;shumaguan_Loop();}
	T0count2++;
	if(T0count2>=100){T0count2=0;}//10ms
	if(T0count2<Compare){Motor=1;}
	else{Motor=0;}
}
