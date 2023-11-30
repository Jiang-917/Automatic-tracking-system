#include "stm32f10x.h"                                                               // Device header
#include "PWM.h"

void Servo_Init(void)                                                                //�����ʼ��
{
	PWM_Init();
}

//void Servo_180_Angle(float Angle)                                                    //180�����Ƕȸ���
//{																					 //PWM:1333-1667
//	PWM_SetCompare1(Angle / 180 * 2000 + 500);
//}

//void Servo_270_Angle(float Angle)                                                    //270�����Ƕȸ���
//{																					 //PWM:1388-1612
//	PWM_SetCompare2(Angle / 270 * 2000 + 500);
//}

void Servo_180_Angle(float Angle)                                                    //180�����Ƕȸ���
{																					 //PWM:1333-1667
	PWM_SetCompare1(Angle);
}

void Servo_270_Angle(float Angle)                                                    //270�����Ƕȸ���
{																					 //PWM:1388-1612
	PWM_SetCompare2(Angle);
}
