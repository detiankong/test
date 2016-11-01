#include "key.h"
#include "delay.h"

void KeyGPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_Initstruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOE,ENABLE);
	
	GPIO_Initstruct.GPIO_Mode=GPIO_Mode_IPD;
	GPIO_Initstruct.GPIO_Pin=GPIO_Pin_0; 
	GPIO_Initstruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Initstruct);  //WK_UP

	GPIO_Initstruct.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Initstruct.GPIO_Pin=GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;
	GPIO_Initstruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOE,&GPIO_Initstruct);	//KEY2,KEY1,KEY0
}

	
void Key_Init(void)
{
	KeyGPIO_Init();
}


//mode=0 不支持连按
//mode=1 支持连按
//KeyUp=1 没有按下
//KeyUp=0 已经按下
int KeyScan(unsigned char mode)
{
	u8 static KeyUp=1;//是否已经按下
	if(mode)  KeyUp=1;
	if(KeyUp==1&&(WK_UP==1||KEY2==0||KEY1==0||KEY0==0))
	{
		delay_ms(10);//消除抖动
		KeyUp=0;  //已经按下
		if(WK_UP==1)	return  WKUP_PRESS;
		else if(KEY2==0)	return KEY2_PRESS;
		else if(KEY1==0)	return KEY1_PRESS;
		else if(KEY0==0)	return KEY0_PRESS;
	}
	else if(WK_UP==0&&KEY2==1&&KEY1==1&&KEY0==1) KeyUp=1;
	return  0;
}
