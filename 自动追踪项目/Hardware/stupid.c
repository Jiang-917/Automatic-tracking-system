/********************
第一、二问
********************/

#include "stm32f10x.h"                  
#include "Servo.h"                  
#include "Delay.h"                  

void Stupid_Init_1(void)
{
	uint8_t i,j;
	
	for(j = 150;j >= 120;j--)                                                        //从左上向右上移动
	{
		Servo_180_Angle(75);		              
		Servo_270_Angle(j);							
		Delay_ms(20);
	}
	for(i = 75;i <= 105;i++)                                                         //从右上到右下移动
	{
		Servo_180_Angle(i);		                  
		Servo_270_Angle(120);                     
		Delay_ms(20);
	}
	for(j = 120;j <= 150;j++)                                                        //从右下向左下移动
	{
		Servo_180_Angle(105);		              
		Servo_270_Angle(j);                       
		Delay_ms(20);
	}
	for(i = 105;i >= 75 ;i--)                                                        //从左下向左上移动
	{
		Servo_180_Angle(i);		                  
		Servo_270_Angle(150);                     
		Delay_ms(20);
	}
	Servo_180_Angle(90);                                                             //复位到原点		                    
	Servo_270_Angle(135);
}
