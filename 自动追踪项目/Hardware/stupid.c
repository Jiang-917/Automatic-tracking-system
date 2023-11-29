/********************
第一、二问
********************/

#include "stm32f10x.h"                  
#include "Servo.h"                  
#include "Delay.h"                  

void Stupid_Init_1(void)
{
	uint8_t i,j;
	
	for(j = 148;j >= 119;j--)                                                        //从左上向右上移动
	{
		Servo_180_Angle(76);		              
		Servo_270_Angle(j);							
		Delay_ms(20);
	}
	for(i = 76;i <= 103;i++)                                                         //从右上到右下移动
	{
		Servo_180_Angle(i);		                  
		Servo_270_Angle(119);                     
		Delay_ms(20);
	}
	for(j = 119;j <= 150;j++)                                                        //从右下向左下移动
	{
		Servo_180_Angle(103);		              
		Servo_270_Angle(j);                       
		Delay_ms(20);
	}
	for(i = 103;i >= 76 ;i--)                                                        //从左下向左上移动
	{
		Servo_180_Angle(i);		                  
		Servo_270_Angle(150);                     
		Delay_ms(20);
	}
//	Servo_180_Angle(76);                                                             //复位到原点		                    
//	Servo_270_Angle(149);
}
