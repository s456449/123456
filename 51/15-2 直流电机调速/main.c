#include <REGX52.H>
#include "Timer0.h"
#include "Delay.h"
#include "P3Key.h"
#include "ShuMaGuan.h"

sbit Motor=P1^0;
static unsigned int T0count1,T0count2;//静态局部变量，不丢失值
unsigned char Compare;
unsigned char KeyNum,Speed;
void main()
{
	Timer0_Init();
	shumaguan_SetBuf(1,Speed);
	while(1)
	{
		KeyNum=Key();
		if(KeyNum)
		{
			if(KeyNum==1&Speed!=0){Speed--;}
			if(KeyNum==2&Speed<3){Speed++;}
//			if(KeyNum==3){Speed=0;}
			if(KeyNum==4){Speed++;if(Speed>3){Speed=0;}}
			if(Speed==0){Compare=0;}
			if(Speed==1){Compare=50;}
			if(Speed==2){Compare=75;}
			if(Speed==3){Compare=100;}
			shumaguan_SetBuf(1,Speed);
		}
	}

}
void Timer0_Routine() interrupt 1
{
	TL0=0xA4;
	TH0=0xFF;//0.1ms
	T0count1++;
	if(T0count1>=20)//2ms
	{
		T0count1=0;
		Key_Update();
		shumaguan_Loop();
	}
	T0count2++;
	if(T0count2>=100){T0count2=0;}//10ms
	if(T0count2<Compare&Motor==0){Motor=1;}
	if(T0count2>=Compare&Motor==1){Motor=0;}
}
