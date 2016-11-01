#ifndef _MOTOR_OUT_
#define _MOTOR_OUT_

#include "sys.h"          

#define Forward 0
#define Backward 1
#define TurnLeft 2
#define TurnRight 3
#define Debug 4   //调试参数 不输出 

#define T_factor  0.3 //转向因子

#define AIN1 PAout(4)
#define AIN2 PAout(5)
#define BIN1 PBout(0)
#define BIN2 PBout(1)

/*****************************************
AIN1	0		1		0
AIN2	0		0		1
		 停止 正转 反转
		 
BIN的控制与AIN相同
*****************************************/

#define DirFoward() AIN1=1;\
									  AIN2=0;\
									  BIN1=1;\
									  BIN2=0
										
#define DirBackward() AIN1=0;\
											AIN2=1;\
											BIN1=0;\
											BIN2=1	

#endif
