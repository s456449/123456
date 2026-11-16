#include <REGX52.H>
#include "Delay.h"
unsigned char Key_KeyNumber;
unsigned char KeyNum;
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
    static unsigned char NowState=0;
    static unsigned char Stable  =0;
    static unsigned char Count   =0;
    unsigned char s=Key_GetState();
	
    if(s==NowState)
    {
        if(Count<3) Count++;
    }
    else
    {
        NowState=s;
        Count=0;
    }

    if(Count>=3 && NowState!=Stable)
    {
        if(Stable!= 0 && NowState==0)
        {
            Key_KeyNumber=Stable;
        }
        Stable=NowState;
    }
}

unsigned char Key()
{
	unsigned char Temp=0;
	Temp=Key_KeyNumber;
	Key_KeyNumber=0;
	return Temp;
}