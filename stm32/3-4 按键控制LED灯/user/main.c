#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Key.h"
#include "LED.h"

unsigned int LEDmode,KeyNum;
int main(void)
{
	Key_Init();
	LED_Init();
	LED_OFF(16);
	while(1)
	{
		KeyNum=Key_GetNum();
		if(KeyNum)
		{
			if(KeyNum==1)
			{
				if(LEDmode<7)
				{LEDmode++;}
				
			}
			if(KeyNum==2)
			{
				if(LEDmode)
				{LEDmode--;}
			}
			LED_OFF(16);
			LED_ON(LEDmode);
		}

	}
}
