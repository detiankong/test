#include "bsp.h"

void BSP_Init(void)
{
	delay_init();//��ʼ����ʱ����
	led_init();//��ʼ��LED�ܽ�
	DirtionPin_init();//��ʼ�����Ʒ���Ĺܽ�
  //Usart_Init(115200);//��ʼ������
 	Timer3_Init(2500,71);//��ʼ��pwm���
	Timer2_Init(0xffff,0);//��ʼ���������
	Timer4_Init(0xffff,0);//��ʼ���ұ�����
	  Usart2_Init(9600);
}
