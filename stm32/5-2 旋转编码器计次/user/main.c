#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Enconder.h"
#include "OLED.h"
#include "Buzzer.h"
#include "LED.h"

int CountNum,Temp,LEDNUM,LEDTemp;
int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	OLED_Init();
	LED_Init();
	CountSensor_Init();
	Buzzer_Init();
	OLED_ShowString(1,1,"CountNum:");
	OLED_ShowSignedNum(2,1,CountNum,10);
	LED_OFF(16);

	while(1)
	{
		Temp=CountNum;
		CountNum=Enconder_Get();
		LEDTemp=LEDNUM;
		LEDNUM=(CountNum%9);
		if(CountNum!=Temp)
		{
			OLED_ShowSignedNum(2,1,CountNum,10);
			Buzzer_ON();
			Delay_ms(50);
			Buzzer_OFF();
		}
		if(LEDNUM!=LEDTemp)
		{
			LED_OFF(16);
			LED_ON(LEDNUM);
		}
	}
}
