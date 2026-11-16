#include <REGX52.H>

sbit DS1302_SCLK=P3^6;
sbit DS1302_IO=P3^4;
sbit DS1302_CE=P3^5;

#define DS1302_Seconds   0x80	//写地址宏定义
#define DS1302_Minutes   0x82
#define DS1302_Hour      0x84
#define DS1302_Data      0x86
#define DS1302_Month     0x88
#define DS1302_Year      0x8C
#define DS1302_Day       0x8A
#define DS1302_WP        0x8E

//存放的时间
char DS1302_Time[]={26,11,11,21,11,0,3};//20~年 月日时分秒星期几

void DS1302_Init()
{
	DS1302_CE=0;
	DS1302_SCLK=0;
}

void DS1302_WriteByte(unsigned char Command,Data)//写时间,Command(寄存器地址)
{
	unsigned char i;
	DS1302_CE=1;
	for(i=0;i<8;i++)
	{
		DS1302_IO=Command&(0x01<<i);
		DS1302_SCLK=1;
		DS1302_SCLK=0;
	}
	for(i=0;i<8;i++)
	{
		DS1302_IO=Data&(0x01<<i);
		DS1302_SCLK=1;
		DS1302_SCLK=0;
	}
	DS1302_CE=0;
}

unsigned char DS1302_ReadByte(unsigned char Command)//读时间
{
	unsigned char i,Data=0x00;
	DS1302_CE=1;
	for(i=0;i<8;i++)
	{
		DS1302_IO=Command&(0x01<<i);
		DS1302_SCLK=0;
		DS1302_SCLK=1;
	}
	for(i=0;i<8;i++)
	{	
		DS1302_SCLK=1; 
		DS1302_SCLK=0;
		if(DS1302_IO){Data|=(0x01<<i);}//如果IO数据为1时传递给Data第i位
	}
	DS1302_CE=0;
	DS1302_IO=0;
	return Data;
}

//1302读出格式为BCD码,DEC=BCD/16*10+BCD%16	xD->xH 例:26D->38D->26H
void DS1302_SetTime()
{
	DS1302_WriteByte(DS1302_WP,0x00);
	DS1302_WriteByte(DS1302_Year,DS1302_Time[0]/10*16+DS1302_Time[0]%10);
	DS1302_WriteByte(DS1302_Month,DS1302_Time[1]/10*16+DS1302_Time[1]%10);
	DS1302_WriteByte(DS1302_Data,DS1302_Time[2]/10*16+DS1302_Time[2]%10);
	DS1302_WriteByte(DS1302_Hour,DS1302_Time[3]/10*16+DS1302_Time[3]%10);
	DS1302_WriteByte(DS1302_Minutes,DS1302_Time[4]/10*16+DS1302_Time[4]%10);
	DS1302_WriteByte(DS1302_Seconds,DS1302_Time[5]/10*16+DS1302_Time[5]%10);
	DS1302_WriteByte(DS1302_Day,DS1302_Time[6]/10*16+DS1302_Time[6]%10);
	DS1302_WriteByte(DS1302_WP,0x80);
}

//xH->xD
void DS1302_ReadTime()
{
	unsigned char DS1302_time;
	DS1302_time=DS1302_ReadByte(DS1302_Year|0x01);
	DS1302_Time[0]=DS1302_time/16*10+DS1302_time%16;
	DS1302_time=DS1302_ReadByte(DS1302_Month|0x01);
	DS1302_Time[1]=DS1302_time/16*10+DS1302_time%16; 
	DS1302_time=DS1302_ReadByte(DS1302_Data|0x01);
	DS1302_Time[2]=DS1302_time/16*10+DS1302_time%16; 
	DS1302_time=DS1302_ReadByte(DS1302_Hour|0x01);
	DS1302_Time[3]=DS1302_time/16*10+DS1302_time%16; 
	DS1302_time=DS1302_ReadByte(DS1302_Minutes|0x01);
	DS1302_Time[4]=DS1302_time/16*10+DS1302_time%16; 
	DS1302_time=DS1302_ReadByte(DS1302_Seconds|0x01);
	DS1302_Time[5]=DS1302_time/16*10+DS1302_time%16;
	DS1302_time=DS1302_ReadByte(DS1302_Day|0x01);
	DS1302_Time[6]=DS1302_time/16*10+DS1302_time%16;
}
