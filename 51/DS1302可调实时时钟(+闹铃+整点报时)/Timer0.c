#include <REGX52.H>
void Timer0_Init()//1MS @11.0592MHz
{
	TMOD&=0xF0;
	TMOD|=0x01;
	TF0=0;
	TR0=1;
	TH0=65075/256;//公式：初值=65536-定时时间*f/12
	TL0=65075%256;//0.5ms
	ET0=1;
	EA=1;
	PT0=0;
}
