#include "stm32f10x.h"                                                               // Device header
#include "OLED.h"
#include "Servo.h"
#include "Key.h"
#include "Serial.h"
#include "PWM.h"
#include "stupid.h"
/************���߶���*************
*		R180�ȶ��PWM��������A0
*		R270�ȶ��PWM��������A1
*		G180�ȶ��PWM��������A2
*		G270�ȶ��PWM��������A3
*		��ͣ������������A4
*		����������������A6
*		USART----TX-A10,RX-A9
*********************************/
int main(void)
{	
	Key_Init();                                                                      //������ʼ��
	Servo_Init();                                                                    //�����ʼ��
	Serial_Init();                                                                   //���ڳ�ʼ��
			
	PWM_SetCompare1(1500);
	PWM_SetCompare2(1500);

	while (1)	
	{		
		while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6) == RESET)					 //����Ҫ��2��
		{
			Stupid_Init();
		}	
	}
}
