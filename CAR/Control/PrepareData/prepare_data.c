#include "prepare_data.h"
#include "usart_.h"

GyroOffestData GOData;//������ƫ��

GyroData GData;//������ԭʼ����

float pitch,roll,yaw;//pitch��yaw��roll�ĽǶ�

void GetGyroOffestData(void)	//����ƫ��
{
	u16 num;
	int16_t GyroX,GyroY,GyroZ;
	int32_t SumX,SumY,SumZ;

	for(num=0;num<2000;num++)
	{
		if(MPU_Get_Gyroscope(&GyroX,&GyroY,&GyroZ)==0)
		{
			SumX+=GyroX;
			SumY+=GyroY;
			SumZ+=GyroZ;
		}
	}
	GOData.GyroX=SumX/2000;
	GOData.GyroY=SumY/2000;
	GOData.GyroZ=SumZ/2000;
}

void PrepareData(void)
{
	u8 i;
	
	static u8 num=0;
	
	static float GyroX_data[10];
	static float GyroY_data[10];
	static float GyroZ_data[10];
	
	int16_t GyroX,GyroY,GyroZ;
	
	float SumX,SumY,SumZ;
	
	MPU_Get_Gyroscope(&GyroX,&GyroY,&GyroZ);
	
	GyroX_data[num]=(GyroX-GOData.GyroX)*Gyro_G;
	GyroY_data[num]=(GyroY-GOData.GyroY)*Gyro_G;	
	GyroZ_data[num]=(GyroZ-GOData.GyroZ)*Gyro_G;	
	
	num=(num+1)%10;
	
	for(i=0;i<10;i++)
	{
		SumX+=GyroX_data[i];
		SumY+=GyroY_data[i];
		SumZ+=GyroZ_data[i];
	}
	
	//���������3����ٶ�
	GData.GyroX=SumX/10;
	GData.GyroY=SumY/10;
	GData.GyroZ=SumZ/10;
	
	//���pitch�Ƕ�
	mpu_dmp_get_data(&pitch,&roll,&yaw);
	ANO_Send_fly(roll,pitch,yaw);

}

//��M������
//n=(60*M)/(Z*Tc)
//M��Tcʱ�����������
//Z�ǵ��תһȦ�������������
//Tc��һ��ʱ��

void GetSpeed (float *Speed)
{
	  TIM_Cmd(TIM4,DISABLE);
	  TIM_Cmd(TIM2,DISABLE);
		Speed[0] =  TIM_GetCounter (TIM2);
		TIM_SetCounter(TIM2,0);
		Speed[1] =  TIM_GetCounter (TIM4);	
		TIM_SetCounter(TIM4,0);
	  
	  ANO_Send_float(Speed);
	  TIM_SetCounter(TIM2,0);
	  TIM_SetCounter(TIM4,0);
		TIM_Cmd(TIM4,ENABLE);
	  TIM_Cmd(TIM2,ENABLE);
}

