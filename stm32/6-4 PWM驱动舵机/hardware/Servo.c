#include "stm32f10x.h"                  // Device header
void Servo_SetAngle(float Angle)
{
	unsigned int Compare;
	Compare=Angle/180*2000+500;//ARR 20000 20ms>0.5ms~2.5ms<500~2500>
	TIM_SetCompare2(TIM2,Compare);
}
