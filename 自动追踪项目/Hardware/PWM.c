#include "stm32f10x.h"                                                               // Device header

void PWM_Init(void)                                                                  //PWM��ʼ����ʹ��TIM2��ʱ����1��2��3��4ͨ��
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	TIM_InternalClockConfig(TIM2);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 20000 - 1;		                         //ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1;		                         //PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;		                                         //CCR
		
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);
	TIM_OC4Init(TIM2, &TIM_OCInitStructure);

	TIM_Cmd(TIM2, ENABLE);
}

void PWM_SetCompare1(uint16_t Compare1)                                              //R180����PWM����
{
	TIM_SetCompare1(TIM2, Compare1);                                                 //TIM2,1ͨ��CCR����
}

void PWM_SetCompare2(uint16_t Compare2)                                              //R270����PWM����
{
	TIM_SetCompare2(TIM2, Compare2);                                                 //TIM2,2ͨ��CCR����
}

void PWM_SetCompare3(uint16_t Compare3)                                              //G180����PWM����
{
	TIM_SetCompare3(TIM2, Compare3);                                                 //TIM2,3ͨ��CCR����
}

void PWM_SetCompare4(uint16_t Compare4)                                              //G270����PWM����
{
	TIM_SetCompare4(TIM2, Compare4);                                                 //TIM2,4ͨ��CCR����
}
