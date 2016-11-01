#ifndef _MOTOR_OUT_
#define _MOTOR_OUT_

#include "sys.h"          

#define Forward 0
#define Backward 1
#define TurnLeft 2
#define TurnRight 3
#define Debug 4   //���Բ��� ����� 

#define T_factor  0.3 //ת������

#define AIN1 PAout(4)
#define AIN2 PAout(5)
#define BIN1 PBout(0)
#define BIN2 PBout(1)

/*****************************************
AIN1	0		1		0
AIN2	0		0		1
		 ֹͣ ��ת ��ת
		 
BIN�Ŀ�����AIN��ͬ
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
