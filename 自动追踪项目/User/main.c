#include "stm32f10x.h"                                                               // Device header
#include "OLED.h"
#include "Servo.h"
#include "Key.h"
#include "stupid.h"
#include "Serial.h"
#include <string.h>

/************���߶���*************
*		180�ȶ��PWM��������A0
*		270�ȶ��PWM��������A1
*		��ͣ������������A2
*		��λ������������A4
*		����������������A6
*		USART----TX-A10,RX-A9
*********************************/

int main(void)
{	
	Key_Init();                                                                      //������ʼ��
	Servo_Init();                                                                    //�����ʼ��
	Serial_Init();                                                                   //���ڳ�ʼ��
		
	Servo_180_Angle(90);                                                             //��λ��ԭ��		                    
	Servo_270_Angle(135);

	while (1)	
	{		
		while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6) == RESET)					 //����Ҫ��2��
		{
			Stupid_Init_1();
		}	
	}
}
