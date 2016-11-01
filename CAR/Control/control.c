#include "control.h"
#include "prepare_data.h"

AnglePID_ AnglePID={{11,1,1},{2,2,2}};//平衡环PID参数

PID SpeedPID={1,1,1};;//速度环PID参数



//pid算法采用增量式算法
//u(k)=u(k-1)+delat(u)
//delta(u)=Kp*(e(k)-e(k-1))+Ki*e(k)+Kd(e(k)-2e(k-1)+e(k-2))
//外环是角度环，内环是角速度环
//外环反馈是姿态结算结果，内环反馈是陀螺仪角速度

//函数的返回值是角度控制器的输出
#define k 2
void AngleControl(float *Core_Out)
{
	float AngleTarget=0;
	
	static float Angle_e[k+1],			//用来存储角度环的e(k)     e(k-1)  e(k-2)
							 AngleSpeed_e[k+1];	//用来存储角速度环的e(k)     e(k-1)  e(k-2)			
	float AngleBias,AngleSpeedBias;
	float Shell_P_Part,Shell_D_Part,Shell_I_Part,Shell_Out,
				Core_P_Part,Core_D_Part,Core_I_Part;
	
	//外环计算
	
	AngleBias=AngleTarget-pitch;
	
	Angle_e[k-2]=Angle_e[k-1];
	Angle_e[k-1]=Angle_e[k];
	Angle_e[k]=AngleBias;//e(k)的移位存储
	
	Shell_P_Part=AnglePID.Shell.Kp*(Angle_e[k]-Angle_e[k-1]);
	Shell_I_Part=AnglePID.Shell.Ki*Angle_e[k];
	Shell_D_Part=AnglePID.Shell.Kd*(Angle_e[k]-2*Angle_e[k-1]+Angle_e[k-2]);
	Shell_Out=Shell_P_Part+Shell_I_Part+Shell_D_Part;
	
	//内环计算
	AngleSpeedBias=Shell_Out-GData.GyroZ;
	
	AngleSpeed_e[k-2]=AngleSpeed_e[k-1];
	AngleSpeed_e[k-1]=AngleSpeed_e[k];
	AngleSpeed_e[k]=AngleSpeedBias;//e(k)的移位存储
	
	Core_P_Part=AnglePID.Core.Kp*(AngleSpeed_e[k]-AngleSpeed_e[k-1]);
	Core_I_Part=AnglePID.Core.Ki*AngleSpeed_e[k];
	Core_D_Part=AnglePID.Core.Kd*(AngleSpeed_e[k]-2*AngleSpeed_e[k-1]+AngleSpeed_e[k-2]);
	(*Core_Out)=Core_P_Part+Core_I_Part+Core_D_Part;
}

;
void SpeedControl(float *Speed_OutLeft,float *Speed_OutRight)
{
	float Speed[2];//0表示左轮，1表示右轮
	float SpeedTargetLeft,SpeedTargetRight;
	
	static float SpeedLeft_e[k+1],SpeedRight_e[k+1];			//用来存储角度环的e(k)     e(k-1)  e(k-2)			
	float SpeedBiasLeft,SpeedBiasRight;
	float Speed_P_Part,Speed_D_Part,Speed_I_Part;
		
	/*
	缺少SpeedTarget的获取
	*/
	
	GetSpeed(Speed);//获得左右轮的速度
	
	//左轮计算
	
	SpeedBiasLeft=SpeedTargetLeft-Speed[0];//Speed[0]左轮速度
	
	SpeedLeft_e[k-2]=SpeedLeft_e[k-1];
	SpeedLeft_e[k-1]=SpeedLeft_e[k];
	SpeedLeft_e[k]=SpeedBiasLeft;//e(k)的移位存储
	
	Speed_P_Part=SpeedPID.Kp*(SpeedLeft_e[k]-SpeedLeft_e[k-1]);
	Speed_I_Part=SpeedPID.Ki*SpeedLeft_e[k];
	Speed_D_Part=SpeedPID.Kd*(SpeedLeft_e[k]-2*SpeedLeft_e[k-1]+SpeedLeft_e[k-2]);
	
	(*Speed_OutLeft)=Speed_P_Part+Speed_I_Part+Speed_D_Part;
	
	//右边轮计算
	
	SpeedBiasRight=SpeedTargetRight-Speed[1];//Speed[1]右轮速度
	
	SpeedRight_e[k-2]=SpeedRight_e[k-1];
	SpeedRight_e[k-1]=SpeedRight_e[k];
	SpeedRight_e[k]=SpeedBiasRight;//e(k)的移位存储
	
	Speed_P_Part=SpeedPID.Kp*(SpeedRight_e[k]-SpeedRight_e[k-1]);
	Speed_I_Part=SpeedPID.Ki*SpeedRight_e[k];
	Speed_D_Part=SpeedPID.Kd*(SpeedRight_e[k]-2*SpeedRight_e[k-1]+SpeedRight_e[k-2]);
	
	(*Speed_OutRight)=Speed_P_Part+Speed_I_Part+Speed_D_Part;
	
}
