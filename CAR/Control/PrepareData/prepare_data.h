#ifndef _PREPARE_DATA_H
#define _PREPARE_DATA_H

#include "stm32f10x.h"
#include "mpu6050.h"
#include "inv_mpu.h"

/****************************������ԭʼ����****************************************/
typedef struct  
{
	float GyroX;
	float GyroY;
	float GyroZ;
}GyroData;
/****************************������ƫ������****************************************/
typedef struct 
{
	int16_t GyroX;
	int16_t GyroY;
	int16_t GyroZ;
}GyroOffestData;

extern float pitch,roll,yaw;//pitch��yaw��roll�ĽǶ�
extern GyroData GData;//������ԭʼ����


#define Gyro_G 	0.03051756

void GetGyroOffestData(void);	//����ƫ��
void PrepareData(void);
void GetSpeed (float* Speed);


#endif
