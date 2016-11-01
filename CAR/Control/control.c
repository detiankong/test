#include "control.h"
#include "prepare_data.h"

AnglePID_ AnglePID={{11,1,1},{2,2,2}};//ƽ�⻷PID����

PID SpeedPID={1,1,1};;//�ٶȻ�PID����



//pid�㷨��������ʽ�㷨
//u(k)=u(k-1)+delat(u)
//delta(u)=Kp*(e(k)-e(k-1))+Ki*e(k)+Kd(e(k)-2e(k-1)+e(k-2))
//�⻷�ǽǶȻ����ڻ��ǽ��ٶȻ�
//�⻷��������̬���������ڻ������������ǽ��ٶ�

//�����ķ���ֵ�ǽǶȿ����������
#define k 2
void AngleControl(float *Core_Out)
{
	float AngleTarget=0;
	
	static float Angle_e[k+1],			//�����洢�ǶȻ���e(k)     e(k-1)  e(k-2)
							 AngleSpeed_e[k+1];	//�����洢���ٶȻ���e(k)     e(k-1)  e(k-2)			
	float AngleBias,AngleSpeedBias;
	float Shell_P_Part,Shell_D_Part,Shell_I_Part,Shell_Out,
				Core_P_Part,Core_D_Part,Core_I_Part;
	
	//�⻷����
	
	AngleBias=AngleTarget-pitch;
	
	Angle_e[k-2]=Angle_e[k-1];
	Angle_e[k-1]=Angle_e[k];
	Angle_e[k]=AngleBias;//e(k)����λ�洢
	
	Shell_P_Part=AnglePID.Shell.Kp*(Angle_e[k]-Angle_e[k-1]);
	Shell_I_Part=AnglePID.Shell.Ki*Angle_e[k];
	Shell_D_Part=AnglePID.Shell.Kd*(Angle_e[k]-2*Angle_e[k-1]+Angle_e[k-2]);
	Shell_Out=Shell_P_Part+Shell_I_Part+Shell_D_Part;
	
	//�ڻ�����
	AngleSpeedBias=Shell_Out-GData.GyroZ;
	
	AngleSpeed_e[k-2]=AngleSpeed_e[k-1];
	AngleSpeed_e[k-1]=AngleSpeed_e[k];
	AngleSpeed_e[k]=AngleSpeedBias;//e(k)����λ�洢
	
	Core_P_Part=AnglePID.Core.Kp*(AngleSpeed_e[k]-AngleSpeed_e[k-1]);
	Core_I_Part=AnglePID.Core.Ki*AngleSpeed_e[k];
	Core_D_Part=AnglePID.Core.Kd*(AngleSpeed_e[k]-2*AngleSpeed_e[k-1]+AngleSpeed_e[k-2]);
	(*Core_Out)=Core_P_Part+Core_I_Part+Core_D_Part;
}

;
void SpeedControl(float *Speed_OutLeft,float *Speed_OutRight)
{
	float Speed[2];//0��ʾ���֣�1��ʾ����
	float SpeedTargetLeft,SpeedTargetRight;
	
	static float SpeedLeft_e[k+1],SpeedRight_e[k+1];			//�����洢�ǶȻ���e(k)     e(k-1)  e(k-2)			
	float SpeedBiasLeft,SpeedBiasRight;
	float Speed_P_Part,Speed_D_Part,Speed_I_Part;
		
	/*
	ȱ��SpeedTarget�Ļ�ȡ
	*/
	
	GetSpeed(Speed);//��������ֵ��ٶ�
	
	//���ּ���
	
	SpeedBiasLeft=SpeedTargetLeft-Speed[0];//Speed[0]�����ٶ�
	
	SpeedLeft_e[k-2]=SpeedLeft_e[k-1];
	SpeedLeft_e[k-1]=SpeedLeft_e[k];
	SpeedLeft_e[k]=SpeedBiasLeft;//e(k)����λ�洢
	
	Speed_P_Part=SpeedPID.Kp*(SpeedLeft_e[k]-SpeedLeft_e[k-1]);
	Speed_I_Part=SpeedPID.Ki*SpeedLeft_e[k];
	Speed_D_Part=SpeedPID.Kd*(SpeedLeft_e[k]-2*SpeedLeft_e[k-1]+SpeedLeft_e[k-2]);
	
	(*Speed_OutLeft)=Speed_P_Part+Speed_I_Part+Speed_D_Part;
	
	//�ұ��ּ���
	
	SpeedBiasRight=SpeedTargetRight-Speed[1];//Speed[1]�����ٶ�
	
	SpeedRight_e[k-2]=SpeedRight_e[k-1];
	SpeedRight_e[k-1]=SpeedRight_e[k];
	SpeedRight_e[k]=SpeedBiasRight;//e(k)����λ�洢
	
	Speed_P_Part=SpeedPID.Kp*(SpeedRight_e[k]-SpeedRight_e[k-1]);
	Speed_I_Part=SpeedPID.Ki*SpeedRight_e[k];
	Speed_D_Part=SpeedPID.Kd*(SpeedRight_e[k]-2*SpeedRight_e[k-1]+SpeedRight_e[k-2]);
	
	(*Speed_OutRight)=Speed_P_Part+Speed_I_Part+Speed_D_Part;
	
}
