#ifndef __CONTROL_H_
#define __CONTROL_H_

/*********************************变量定义***********************************/

/********************************PID参数*******************************************/
typedef struct
{
	float Kp;
	float Ki;
	float Kd;
}PID;
/******************************角度环PID参数****************************************/
typedef struct
{
	PID Core;
	PID Shell;
}AnglePID_;

void AngleControl(float *Core_Out);
void SpeedControl(float *Speed_OutLeft,float *Speed_OutRight);


#endif
