/********************
��һ������
********************/

#include "stm32f10x.h"                  
#include "Servo.h"                  
#include "Delay.h"                  

void Stupid_Init_1(void)
{
	uint8_t i,j;
	
	for(j = 148;j >= 119;j--)                                                        //�������������ƶ�
	{
		Servo_180_Angle(76);		              
		Servo_270_Angle(j);							
		Delay_ms(20);
	}
	for(i = 76;i <= 103;i++)                                                         //�����ϵ������ƶ�
	{
		Servo_180_Angle(i);		                  
		Servo_270_Angle(119);                     
		Delay_ms(20);
	}
	for(j = 119;j <= 150;j++)                                                        //�������������ƶ�
	{
		Servo_180_Angle(103);		              
		Servo_270_Angle(j);                       
		Delay_ms(20);
	}
	for(i = 103;i >= 76 ;i--)                                                        //�������������ƶ�
	{
		Servo_180_Angle(i);		                  
		Servo_270_Angle(150);                     
		Delay_ms(20);
	}
//	Servo_180_Angle(76);                                                             //��λ��ԭ��		                    
//	Servo_270_Angle(149);
}
