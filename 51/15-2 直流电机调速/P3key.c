#include <REGX52.H>
#include "Delay.h"
unsigned char Key_KeyNumber;
unsigned char P3key()
{
	unsigned char KeyNumber=0;
	if(P3_1==0){Delay(20);while(P3_1==0);Delay(20);KeyNumber=1;}
	if(P3_0==0){Delay(20);while(P3_0==0);Delay(20);KeyNumber=2;}
	if(P3_2==0){Delay(20);while(P3_2==0);Delay(20);KeyNumber=3;}
	if(P3_3==0){Delay(20);while(P3_3==0);Delay(20);KeyNumber=4;}
	return KeyNumber;
}
unsigned char Key_GetState()
{
	unsigned char KeyNumber=0;
	if(P3_1==0){KeyNumber=1;}
	if(P3_0==0){KeyNumber=2;}
	if(P3_2==0){KeyNumber=3;}
	if(P3_3==0){KeyNumber=4;}
	return KeyNumber;
}

void Key_Update(void)
{
    static unsigned char NowState=0;    /* 本次采样 */
    static unsigned char Stable  =0;    /* 已确认的稳定状态 */
    static unsigned char Count   =0;    /* 连续一致次数 */
    unsigned char s=Key_GetState();
	
    if(s==NowState)
    {
        if(Count<3) Count++;            /* 3 × 2ms = 6ms 一致才算数 */
    }
    else
    {
        NowState=s;
        Count=0;
    }

    if(Count>=3 && NowState!=Stable)
    {
        if(Stable!= 0 && NowState==0)  /* 松手沿 */
        {
            Key_KeyNumber=Stable;
        }
        Stable=NowState;
    }
}
/*  前代码，问题：P3.2误触发。
	static unsigned char NowState=0,Stable=0,Count=0;
	static unsigned char LastState,NowState;
	LastState=NowState;
	NowState=Key_GetState();
	if(LastState)
	{
		if(LastState==1 && NowState==0)
		{Key_KeyNumber=1;}
		if(LastState==2 && NowState==0)
		{Key_KeyNumber=2;}
		if(LastState==3 && NowState==0)
		{Key_KeyNumber=3;}
		if(LastState==4 && NowState==0)
		{Key_KeyNumber=4;}
	}*/

unsigned char Key()
{
	unsigned char Temp=0;
	Temp=Key_KeyNumber;
	Key_KeyNumber=0;
	return Temp;
}