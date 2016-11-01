#include "motor_out.h"
#include "control.h"
									
void MotorOut(u8 mode)
{
	float SpeedLeftOut,SpeedRightOut,AngleOut;
	float LeftOut,RightOut;
		
	AngleControl(&AngleOut);//��ýǶȱջ���������
	
	SpeedControl(&SpeedLeftOut,&SpeedRightOut);//����ٶȱջ����������������������ӷֿ�
	
	LeftOut=AngleOut+SpeedLeftOut;//���ֵ����
	RightOut=AngleOut+SpeedRightOut;//���ֵ����
	
	switch(mode)
	{
		case Forward:	
									DirFoward();
									TIM_SetCompare1(TIM3,LeftOut);
									TIM_SetCompare2(TIM3,RightOut);
									break;
		case Backward:
									DirBackward();
									TIM_SetCompare1(TIM3,LeftOut);
									TIM_SetCompare2(TIM3,RightOut);
									break;
		case TurnLeft:
									TIM_SetCompare1(TIM3,LeftOut*T_factor);//������ת������ת����
									TIM_SetCompare2(TIM3,RightOut);
									break;
		case TurnRight:
									TIM_SetCompare1(TIM3,LeftOut);
									TIM_SetCompare2(TIM3,RightOut*T_factor);//������ת������ת����
									break;;
		case Debug:break;
	}
}
