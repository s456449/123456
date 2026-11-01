#include <REGX52.H>
void Timer0_Init()//1MS@11.0592MHz
{
	TMOD&=0xF0;//TMOD低四位清零，高四位保持不变
	TMOD|=0x01;//TMOD最低位置1，高四位保持不变
	/*代替TMOD=0x01;*/
	TF0=0;
	TR0=1;
	TH0=64613/256;//1ms
	TL0=64613%256+1;
	ET0=1;
	EA=1;
	PT0=0;
}
/*定时函数模板
void Timer0_Routine() interrupt 1
{
	static unsigned int T0count;//静态局部变量，不丢失值
	TL0=0x66;
	TH0=0xFC;
	T0count++;
	if(T0count>=1000)//1000ms
	{
		T0count=0;
		
		
	}
}
*/