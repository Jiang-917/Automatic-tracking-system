#include "stm32f10x.h"                                                               // Device header
#include "OLED.h"
#include "Servo.h"
#include "Key.h"
#include "stupid.h"
#include "Serial.h"
#include <string.h>

/*********���߶���**********
*		180�ȶ��PWM��������A0
*		270�ȶ��PWM��������A1
*		��ͣ������������A2
*		��λ������������A4
*		����������������A6
*		USART----TX-A10,RX-A9
***************************/

int main(void)
{
	OLED_Init();
	Servo_Init();
	Key_Init();
	Serial_Init();
	
	while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6) == SET)
	{
		
	}
	while (1)	
	{
		Stupid_Init_1();
	}
}
