/**********嵌入式作业——平衡小车*********/
/***************2016.10.26***************/
/*
内容：1.ucos3的移植 
			2.串口（√），pwm（√），编码器（），IIC（√），LED（√），定时器（√）等的驱动
			3.姿态结算部分
			4.控制策略
			5.与操作系统的结合
*/

/***************资源分配*****************/
/*
管脚连接：
		PB10--SCL
		PB11--SCA

		PA9 --TX  信号发送端
		PA10--RX
		
		PA2 --TX  调试  串口2
		PA3 --RX
		
		PA6 --PWM1
		PA7 --PWM2
		
		PA0 --A相  TIM2
		PA1 --B相
		
		PB6 --A相  TIM2
		PB7 --B相
		
		PA4 --AIN1	左电机
		PA5 --AIN2
		
		PB0 --BIN1 右电机
		PB1 --BIN2

芯片资源：
   定时器3--pwm输出
	 定时器4--右编码器
	 定时器2--左编码器
	 串口1--通信使用
	 IIC2--MPU6050读取
*/

/*******2016.10.28********/
/*没有完成的任务：匿名四周的上位机协议的移植      //移植结束 没有测试
								 编码器模式是否正确未知 获取速度的M法是否正确 计数跳转的时候该如何处理没有整理
								 陀螺仪采集的数据没看 dmp库的结果也没有测试				//大致正确
								 没有开控制用的定时器 总的终端控制没有写
*/                 


#include "stm32f10x.h"
#include "sys.h"
#include "bsp.h"

#include "usart.h"	

#include "usart_.h"	

#include "prepare_data.h"


#define LED PCout(13) //PC13为LED信号灯

//虽然不懂 但是有用
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
	//MPU_Init();//初始化mpu6050

	delay_ms(10);
	//while(mpu_dmp_init())//初始化dmp库	
		 
	//dmp_read_fifo(gyro, accel, quat, &sensor_timestamp, &sensors,&more);//有用

	TIM_SetCompare1(TIM3,1500);
	TIM_SetCompare2(TIM3,1500);
	
	while(1)
	{
	delay_ms(50);
	LED=~LED;//信号灯翻转
		
	 //PrepareData();
   GetSpeed(a);
		
	}
}

