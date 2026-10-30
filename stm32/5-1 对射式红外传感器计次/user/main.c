#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "CountSensor.h"
#include "Buzzer.h"
unsigned int CountNum=0,Temp;
int main(void)
{
	CountSensor_Init();
	OLED_Init();
	Buzzer_Init();
	OLED_ShowString(1,1,"CountNum:");
	OLED_ShowNum(2,1,CountNum,10);
	while(1)
	{
		Temp=CountNum;
		CountNum=CountSensor_Get();
		if(CountNum>Temp)
		{
			OLED_ShowNum(2,1,CountNum,10);
			Buzzer_ON();
			Delay_ms(50);
			Buzzer_OFF();
		}
	}
}
