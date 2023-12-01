/********************
��һ������
********************/
#include "stm32f10x.h"                  
#include "Servo.h"            
#include "Delay.h"
#include "stupid.h"

void Stupid_Init(void)
{
	uint16_t i,j;
	
	for(j = y1;j >= y2;j--)                                                      //�������������ƶ�
	{
		Servo_R_180_Angle(x1);		              
		Servo_R_270_Angle(j);							
		Delay_ms(30);
	}
	for(i = x1;i <= x2;i++)                                                      //�����ϵ������ƶ�
	{
		Servo_R_180_Angle(i);		                  
		Servo_R_270_Angle(y2);                     
		Delay_ms(30);
	}
	for(j = y2;j <= y1;j++)                                                      //�������������ƶ�
	{
		Servo_R_180_Angle(x2);		              
		Servo_R_270_Angle(j);                       
		Delay_ms(30);
	}
	for(i = x2;i >= x1 ;i--)                                                     //�������������ƶ�
	{
		Servo_R_180_Angle(i);		                  
		Servo_R_270_Angle(y1);                     
		Delay_ms(30);
	}
}
