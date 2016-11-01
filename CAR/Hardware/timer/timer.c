#include "timer.h"


void Timer3_Init(uint16_t period,uint16_t prescaler)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitstruct;
	#if	PWM_Mode 	
	GPIO_InitTypeDef GPIO_InitTstruct;	
	TIM_OCInitTypeDef TIM_OCInitTstruct;
	#endif 
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	TIM_TimeBaseInitstruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitstruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitstruct.TIM_Period=period;
	TIM_TimeBaseInitstruct.TIM_Prescaler=prescaler;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitstruct);
	
	
	#if	PWM_Mode 	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
		
		GPIO_InitTstruct.GPIO_Mode=GPIO_Mode_AF_PP;
		GPIO_InitTstruct.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7;
		GPIO_InitTstruct.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_Init(GPIOA,&GPIO_InitTstruct);
		
		
		TIM_OCInitTstruct.TIM_OCMode=TIM_OCMode_PWM2;
		TIM_OCInitTstruct.TIM_OCPolarity= TIM_OCPolarity_High;
		TIM_OCInitTstruct.TIM_OutputState=TIM_OutputState_Enable;
		TIM_OCInitTstruct.TIM_Pulse=1000;
		TIM_OC1Init(TIM3,&TIM_OCInitTstruct);
		TIM_OC2Init(TIM3,&TIM_OCInitTstruct);

		TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);
		TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);
		
	#endif 
		
	TIM_Cmd(TIM3,ENABLE);
}



//void Timer4_Init(uint16_t period,uint16_t prescaler)
//{
//	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitstruct;
//	NVIC_InitTypeDef NVIC_InitTstruct; 	
//		
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
//	
//	TIM_TimeBaseInitstruct.TIM_ClockDivision=TIM_CKD_DIV1;
//	TIM_TimeBaseInitstruct.TIM_CounterMode=TIM_CounterMode_Up;
//	TIM_TimeBaseInitstruct.TIM_Period=period;
//	TIM_TimeBaseInitstruct.TIM_Prescaler=prescaler;
//	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitstruct);
//	
//	NVIC_InitTstruct.NVIC_IRQChannel=TIM4_IRQn;
//	NVIC_InitTstruct.NVIC_IRQChannelCmd=ENABLE;
//	NVIC_InitTstruct.NVIC_IRQChannelPreemptionPriority=0x02;
//	NVIC_InitTstruct.NVIC_IRQChannelSubPriority=0x01;
//	NVIC_Init(&NVIC_InitTstruct);
//	
//	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
//		
//	TIM_Cmd(TIM4,ENABLE);
//}


void Timer2_Init(uint16_t period,uint16_t prescaler)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitstruct;	
	GPIO_InitTypeDef GPIO_InitTstruct;	
	TIM_ICInitTypeDef TIM_ICInitTstruct;
		
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

	GPIO_InitTstruct.GPIO_Mode=GPIO_Mode_IPD;
	GPIO_InitTstruct.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;
	GPIO_InitTstruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitTstruct);
	
	TIM_TimeBaseInitstruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitstruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitstruct.TIM_Period=period;
	TIM_TimeBaseInitstruct.TIM_Prescaler=prescaler;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitstruct);
	
	TIM_EncoderInterfaceConfig(TIM2,TIM_EncoderMode_TI12,TIM_ICPolarity_BothEdge,TIM_ICPolarity_BothEdge);
		
	TIM_ICInitTstruct.TIM_Channel=TIM_Channel_1;
	TIM_ICInitTstruct.TIM_ICFilter=0x03;
	TIM_ICInitTstruct.TIM_ICPolarity=TIM_ICPolarity_BothEdge;
	TIM_ICInitTstruct.TIM_ICPrescaler=TIM_ICPSC_DIV1;
	TIM_ICInitTstruct.TIM_ICSelection=TIM_ICSelection_DirectTI;
	TIM_ICInit(TIM2,&TIM_ICInitTstruct);
	
	TIM_ICInitTstruct.TIM_Channel=TIM_Channel_2;
	TIM_ICInit(TIM2,&TIM_ICInitTstruct);
	
	TIM_SetCounter(TIM2,0);
	
	TIM_Cmd(TIM2,ENABLE);
}
void Timer4_Init(uint16_t period,uint16_t prescaler)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitstruct;	
	GPIO_InitTypeDef GPIO_InitTstruct;	
	TIM_ICInitTypeDef TIM_ICInitTstruct;
		
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

	GPIO_InitTstruct.GPIO_Mode=GPIO_Mode_IPD;
	GPIO_InitTstruct.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitTstruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitTstruct);
	
	TIM_TimeBaseInitstruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitstruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitstruct.TIM_Period=period;
	TIM_TimeBaseInitstruct.TIM_Prescaler=prescaler;
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitstruct);
	
	TIM_EncoderInterfaceConfig(TIM4,TIM_EncoderMode_TI12,TIM_ICPolarity_BothEdge,TIM_ICPolarity_BothEdge);
		
	TIM_ICInitTstruct.TIM_Channel=TIM_Channel_1;
	TIM_ICInitTstruct.TIM_ICFilter=0x03;
	TIM_ICInitTstruct.TIM_ICPolarity=TIM_ICPolarity_BothEdge;
	TIM_ICInitTstruct.TIM_ICPrescaler=TIM_ICPSC_DIV1;
	TIM_ICInitTstruct.TIM_ICSelection=TIM_ICSelection_DirectTI;
	TIM_ICInit(TIM4,&TIM_ICInitTstruct);
	
	TIM_ICInitTstruct.TIM_Channel=TIM_Channel_2;
	TIM_ICInit(TIM4,&TIM_ICInitTstruct);
	
	TIM_SetCounter(TIM4,0);
	
	TIM_Cmd(TIM4,ENABLE);
}
