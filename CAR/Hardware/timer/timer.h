#ifndef _TIMER_H_
#define _TIMER_H_

#include "stm32f10x.h"         

void Timer2_Init(uint16_t period,uint16_t prescaler);//�������
void Timer3_Init(uint16_t period,uint16_t prescaler);//pwm���
void Timer4_Init(uint16_t period,uint16_t prescaler);//�б�����

#define PWM_Mode 1
#define IC_Mode 0


#endif
