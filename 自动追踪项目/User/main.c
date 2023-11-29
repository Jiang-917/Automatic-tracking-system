#include "stm32f10x.h"                                                               // Device header
#include "OLED.h"
#include "Servo.h"
#include "Key.h"
#include "stupid.h"
#include "Serial.h"
#include <string.h>

/************接线定义*************
*		180度舵机PWM————A0
*		270度舵机PWM————A1
*		暂停按键————A2
*		复位按键————A4
*		启动按键————A6
*		USART----TX-A10,RX-A9
*********************************/

int main(void)
{	
	Key_Init();                                                                      //按键初始化
	Servo_Init();                                                                    //舵机初始化
	Serial_Init();                                                                   //串口初始化
		
	Servo_180_Angle(90);                                                             //复位到原点		                    
	Servo_270_Angle(135);

	while (1)	
	{		
		while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6) == RESET)					 //基本要求（2）
		{
			Stupid_Init_1();
		}	
	}
}
