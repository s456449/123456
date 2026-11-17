#ifndef __PWM_H
#define __PWM_H

void PWM_Init(void);//ARR100 PSC720
void PWM_SetCompare1(uint16_t Compare);//CCR
void PWM_SetPrescaler(uint16_t Prescaler);//PSC

#endif
