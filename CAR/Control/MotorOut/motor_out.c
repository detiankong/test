#include "motor_out.h"
#include "control.h"
									
void MotorOut(u8 mode)
{
	float SpeedLeftOut,SpeedRightOut,AngleOut;
	float LeftOut,RightOut;
		
	AngleControl(&AngleOut);//获得角度闭环的输出结果
	
	SpeedControl(&SpeedLeftOut,&SpeedRightOut);//获得速度闭环的输出结果，左右两个轮子分开
	
	LeftOut=AngleOut+SpeedLeftOut;//左轮的输出
	RightOut=AngleOut+SpeedRightOut;//右轮的输出
	
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
									TIM_SetCompare1(TIM3,LeftOut*T_factor);//差速左转，左轮转的慢
									TIM_SetCompare2(TIM3,RightOut);
									break;
		case TurnRight:
									TIM_SetCompare1(TIM3,LeftOut);
									TIM_SetCompare2(TIM3,RightOut*T_factor);//差速右转，右轮转的慢
									break;;
		case Debug:break;
	}
}
