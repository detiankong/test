/**********Ƕ��ʽ��ҵ����ƽ��С��*********/
/***************2016.10.26***************/
/*
���ݣ�1.ucos3����ֲ 
			2.���ڣ��̣���pwm���̣���������������IIC���̣���LED���̣�����ʱ�����̣��ȵ�����
			3.��̬���㲿��
			4.���Ʋ���
			5.�����ϵͳ�Ľ��
*/

/***************��Դ����*****************/
/*
�ܽ����ӣ�
		PB10--SCL
		PB11--SCA

		PA9 --TX  �źŷ��Ͷ�
		PA10--RX
		
		PA2 --TX  ����  ����2
		PA3 --RX
		
		PA6 --PWM1
		PA7 --PWM2
		
		PA0 --A��  TIM2
		PA1 --B��
		
		PB6 --A��  TIM2
		PB7 --B��
		
		PA4 --AIN1	����
		PA5 --AIN2
		
		PB0 --BIN1 �ҵ��
		PB1 --BIN2

оƬ��Դ��
   ��ʱ��3--pwm���
	 ��ʱ��4--�ұ�����
	 ��ʱ��2--�������
	 ����1--ͨ��ʹ��
	 IIC2--MPU6050��ȡ
*/

/*******2016.10.28********/
/*û����ɵ������������ܵ���λ��Э�����ֲ      //��ֲ���� û�в���
								 ������ģʽ�Ƿ���ȷδ֪ ��ȡ�ٶȵ�M���Ƿ���ȷ ������ת��ʱ�����δ���û������
								 �����ǲɼ�������û�� dmp��Ľ��Ҳû�в���				//������ȷ
								 û�п������õĶ�ʱ�� �ܵ��ն˿���û��д
*/                 


#include "stm32f10x.h"
#include "sys.h"
#include "bsp.h"

#include "usart.h"	

#include "usart_.h"	

#include "prepare_data.h"


#define LED PCout(13) //PC13ΪLED�źŵ�

//��Ȼ���� ��������
/******************************/
	unsigned long sensor_timestamp;
	short gyro[3], accel[3], sensors;
	unsigned char more;
	long quat[4];
/******************************/


int main(void)
{
	float a[4];
	BSP_Init();
	//MPU_Init();//��ʼ��mpu6050

	delay_ms(10);
	//while(mpu_dmp_init())//��ʼ��dmp��	
		 
	//dmp_read_fifo(gyro, accel, quat, &sensor_timestamp, &sensors,&more);//����

	TIM_SetCompare1(TIM3,1500);
	TIM_SetCompare2(TIM3,1500);
	
	while(1)
	{
	delay_ms(50);
	LED=~LED;//�źŵƷ�ת
		
	 //PrepareData();
   GetSpeed(a);
		
	}
}

