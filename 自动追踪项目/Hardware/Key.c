#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Servo.h"

void Key_Init(void)                                                                  //按键初始化
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_2 |GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
//	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource4);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource2);
	
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = EXTI_Line4 | EXTI_Line2 |GPIO_Pin_6;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
		
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
//	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
//	NVIC_Init(&NVIC_InitStructure);
}
/******************
	中断函数定义
******************/
void EXTI2_IRQHandler(void)                                                          //按下暂停，释放继续
{
	if (EXTI_GetITStatus(EXTI_Line2) == SET)
	{
		while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2) == RESET)
		{
			
		}
	}
	EXTI_ClearITPendingBit(EXTI_Line2);
}

//void EXTI4_IRQHandler(void)                                                          //按下复位，释放回位
//{
//	if (EXTI_GetITStatus(EXTI_Line4) == SET)
//	{
//		Servo_180_Angle(1500);		                    
//		Servo_270_Angle(1500);		
//		while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4) == RESET)
//		{
//			
//		}		
//	}
//	EXTI_ClearITPendingBit(EXTI_Line4);
//}
