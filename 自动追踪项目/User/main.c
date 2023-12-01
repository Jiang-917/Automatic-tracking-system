#include "stm32f10x.h"                                                               // Device header
#include "OLED.h"
#include "Servo.h"
#include "Key.h"
#include "Serial.h"
#include "PWM.h"
#include "stupid.h"
/************接线定义*************
*		R180度舵机PWM————A0
*		R270度舵机PWM————A1
*		G180度舵机PWM————A2
*		G270度舵机PWM————A3
*		暂停按键————A4
*		启动按键————A6
*		USART----TX-A10,RX-A9
*********************************/
int main(void)
{	
	Key_Init();                                                                      //按键初始化
	Servo_Init();                                                                    //舵机初始化
	Serial_Init();                                                                   //串口初始化
			
	PWM_SetCompare1(1500);
	PWM_SetCompare2(1500);

	while (1)	
	{		
		while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6) == RESET)					 //基本要求（2）
		{
			Stupid_Init();
		}	
	}
}
