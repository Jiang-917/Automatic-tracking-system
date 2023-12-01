#include "stm32f10x.h"                                                               // Device header
#include "PWM.h"

void Servo_Init(void)                                                                //舵机初始化
{
	PWM_Init();
}

void Servo_R_180_Angle(float Angle)                                                  //180°舵机角度给予
{																					 //PWM:1333-1667
	PWM_SetCompare1(Angle);
}

void Servo_R_270_Angle(float Angle)                                                  //270°舵机角度给予
{																					 //PWM:1388-1612
	PWM_SetCompare2(Angle);
}

void Servo_G_180_Angle(float Angle)                                                  //180°舵机角度给予
{																					 //PWM:1333-1667
	PWM_SetCompare3(Angle);
}

void Servo_G_270_Angle(float Angle)                                                  //270°舵机角度给予
{																					 //PWM:1388-1612
	PWM_SetCompare4(Angle);
}
