#include "bsp.h"

void BSP_Init(void)
{
	delay_init();//初始化延时函数
	led_init();//初始化LED管脚
	DirtionPin_init();//初始化控制方向的管脚
  //Usart_Init(115200);//初始化串口
 	Timer3_Init(2500,71);//初始化pwm输出
	Timer2_Init(0xffff,0);//初始化左编码器
	Timer4_Init(0xffff,0);//初始化右编码器
	  Usart2_Init(9600);
}
