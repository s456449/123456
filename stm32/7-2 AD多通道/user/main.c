#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "AD.h"
uint16_t AD0,AD1,AD2,AD3;
float V0,V1,V2,V3;
int main(void)
{
	OLED_Init();
	AD_Init();
	OLED_ShowString(1,1,"AD0:0.00V");
	OLED_ShowString(2,1,"AD1:0.00V");
	OLED_ShowString(3,1,"AD2:0.00V");
	OLED_ShowString(4,1,"AD3:0.00V");
	while(1)
	{
		AD0=AD_GetValue(ADC_Channel_0);
		AD1=AD_GetValue(ADC_Channel_1);
		AD2=AD_GetValue(ADC_Channel_2);
		AD3=AD_GetValue(ADC_Channel_3);
		V0=(float)AD0/4095*3.3;
		V1=(float)AD1/4095*3.3;
		V2=(float)AD2/4095*3.3;
		V3=(float)AD3/4095*3.3;
		
		OLED_ShowNum(1,5,V0,1);
		OLED_ShowNum(1,7,(unsigned short int)(V0*100)%100,2);
		OLED_ShowNum(2,5,V1,1);
		OLED_ShowNum(2,7,(unsigned short int)(V1*100)%100,2);		
		OLED_ShowNum(3,5,V2,1);
		OLED_ShowNum(3,7,(unsigned short int)(V2*100)%100,2);
		OLED_ShowNum(4,5,V3,1);
		OLED_ShowNum(4,7,(unsigned short int)(V3*100)%100,2);
		
		Delay_ms(100);
	}
}
