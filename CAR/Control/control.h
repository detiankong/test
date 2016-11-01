#ifndef __CONTROL_H_
#define __CONTROL_H_

/*********************************��������***********************************/

/********************************PID����*******************************************/
typedef struct
{
	float Kp;
	float Ki;
	float Kd;
}PID;
/******************************�ǶȻ�PID����****************************************/
typedef struct
{
	PID Core;
	PID Shell;
}AnglePID_;

void AngleControl(float *Core_Out);
void SpeedControl(float *Speed_OutLeft,float *Speed_OutRight);


#endif
