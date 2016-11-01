#ifndef _PREPARE_DATA_H
#define _PREPARE_DATA_H

#include "stm32f10x.h"
#include "mpu6050.h"
#include "inv_mpu.h"

/****************************陀螺仪原始数据****************************************/
typedef struct  
{
	float GyroX;
	float GyroY;
	float GyroZ;
}GyroData;
/****************************陀螺仪偏差数据****************************************/
typedef struct 
{
	int16_t GyroX;
	int16_t GyroY;
	int16_t GyroZ;
}GyroOffestData;

extern float pitch,roll,yaw;//pitch，yaw，roll的角度
extern GyroData GData;//陀螺仪原始数据


#define Gyro_G 	0.03051756

void GetGyroOffestData(void);	//计算偏差
void PrepareData(void);
void GetSpeed (float* Speed);


#endif
