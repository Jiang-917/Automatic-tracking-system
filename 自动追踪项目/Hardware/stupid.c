/********************
��һ������
********************/

#include "stm32f10x.h"                  
#include "Servo.h"                  
#include "Delay.h"                  

void Stupid_Init_1(void)
{
	uint8_t i,j;
	
	for(j = 150;j >= 120;j--)                                                        //�������������ƶ�
	{
		Servo_180_Angle(75);		              
		Servo_270_Angle(j);							
		Delay_ms(20);
	}
	for(i = 75;i <= 105;i++)                                                         //�����ϵ������ƶ�
	{
		Servo_180_Angle(i);		                  
		Servo_270_Angle(120);                     
		Delay_ms(20);
	}
	for(j = 120;j <= 150;j++)                                                        //�������������ƶ�
	{
		Servo_180_Angle(105);		              
		Servo_270_Angle(j);                       
		Delay_ms(20);
	}
	for(i = 105;i >= 75 ;i--)                                                        //�������������ƶ�
	{
		Servo_180_Angle(i);		                  
		Servo_270_Angle(150);                     
		Delay_ms(20);
	}
	Servo_180_Angle(90);                                                             //��λ��ԭ��		                    
	Servo_270_Angle(135);
}
