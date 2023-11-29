/*USART*/
/******�����ΪHEXģʽ���ı�ģʽ����ģʽ��ʹ��ʱע��ע����һ��ģʽ�����******/

#include "stm32f10x.h"                                                               // Device header
#include <stdio.h>
#include <stdarg.h>

/*HEXģʽ�������*/
uint8_t Serial_TxPacket[4];                                                        //��������
uint8_t Serial_RxPacket[4];                                                        //��������

/*�ı�ģʽ�������*/
//char Serial_RxPacket[100];                                                           //��������

/*ͨ�ñ���*/
uint8_t Serial_RxFlag;                                                               //��ȡ��־λ

void Serial_Init(void)                                                               // USART��ʼ������
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);                           //ʹ��USART1
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;                                             //TX_Init
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);                                           //RX_Init
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 9600;                                       //������
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;  //Ӳ��������
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;                  //����ģʽ
	USART_InitStructure.USART_Parity = USART_Parity_No;                              //У��λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;                           //ֹͣλ
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;                      //�ֳ�
	USART_Init(USART1, &USART_InitStructure);
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);                                   //�����жϽ�������
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&NVIC_InitStructure);

	USART_Cmd(USART1, ENABLE);
}

void Serial_SendByte(uint8_t Byte)                                                   //�����ֽ�
{
	USART_SendData(USART1, Byte);
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);                    //�ȴ�TXE��־λ��1
}

void Serial_SendArray(uint8_t *Array, uint16_t Length)                               //��������
{
	uint16_t i;
	for (i = 0; i < Length; i ++)
	{
		Serial_SendByte(Array[i]);
	}
}

void Serial_SendString(char *String)                                                 //�����ַ�
{
	uint8_t i;
	for (i = 0; String[i] != '\0'; i ++)
	{
		Serial_SendByte(String[i]);
	}
}

uint32_t Serial_Pow(uint32_t X, uint32_t Y)                                          //������Serial_SendNumber()
{
	uint32_t Result = 1;
	while (Y --)
	{
		Result *= X;
	}
	return Result;
}

void Serial_SendNumber(uint32_t Number, uint8_t Length)                              //�ַ�����ʽ����
{
	uint8_t i;
	for (i = 0; i < Length; i ++)
	{
		Serial_SendByte(Number / Serial_Pow(10, Length - i - 1) % 10 + '0');
	}
}

int fputc(int ch, FILE *f)                                                           //printf�ض��򵽴���,�ı�ģʽ
{
	Serial_SendByte(ch);
	return ch;
}

void Serial_Printf(char *format, ...)                                                //sprintf
{
	char String[100];
	va_list arg;
	va_start(arg, format);
	vsprintf(String, format, arg);
	va_end(arg);
	Serial_SendString(String);
}

/*������HEXģʽ���ı�ģʽ��ע��*/
void Serial_SendPacket(void)                                                       //HEXģʽ�������ݰ�
{
	Serial_SendByte(0xFF);
	Serial_SendArray(Serial_TxPacket,4);
	Serial_SendByte(0xFE);
}

uint8_t Serial_GetRxFlag(void)                                                       //��ȡ����־λ
{
	if(Serial_RxFlag == 1)
	{
		Serial_RxFlag = 0;
		return 1;
	}
	return 0;
}

/*�жϺ���***�ж�״̬��***HEXģʽ*/
void USART1_IRQHandler(void)                                                         //�������ݰ�
{
	static uint8_t RxState = 0;                                                      //״̬����
	static uint8_t pRxPacket = 0;                                                    //��������

	if(USART_GetFlagStatus(USART1, USART_IT_RXNE) == SET)
	{
		uint8_t RxData = USART_ReceiveData(USART1);
		
		if(RxState == 0)                                                             //�ȴ���ͷ
		{
			if(RxData == 0xFF)                                                       //��ͷ����λ��
			{
				RxState = 1;
				pRxPacket = 0;
			}
		}
		else if(RxState == 1)                                                        //��������
		{
			Serial_RxPacket[pRxPacket] = RxData;
			pRxPacket++;
			if(pRxPacket >= 2)
			{
				RxState = 2;
			}
		}
		else if(RxState == 2)                                                        //�ȴ���β
		{
			if(RxData == 0xFE)                                                       //��β����λ��
			{
				RxState = 0;
				Serial_RxFlag = 1;
			}
		}	
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}
}

/*�жϺ���***�ж�״̬��***�ı�ģʽ****\r \n***/
//void USART1_IRQHandler(void)                                                       //�������ݰ�
//{
//	static uint8_t RxState = 0;                                                      //״̬����
//	static uint8_t pRxPacket = 0;                                                    //��������

//	if(USART_GetFlagStatus(USART1, USART_IT_RXNE) == SET)
//	{
//		uint8_t RxData = USART_ReceiveData(USART1);
//		
//		if(RxState == 0)                                                             //�ȴ���ͷ
//		{
//			if(RxData == '@')                                                        //��ͷ����λ��
//			{
//				RxState = 1;
//				pRxPacket = 0;
//			}
//		}
//		else if(RxState == 1)                                                        //��������
//		{
//			if (RxData == '\r')                                                      //���Ȳ�ȷ�����������ж��ǲ��ǰ�β
//			{
//				RxState = 2;
//			}
//			else
//			{
//				Serial_RxPacket[pRxPacket] = RxData;
//				pRxPacket++;
//			}
//		}
//		else if(RxState == 2)                                                        //�ȴ���β
//		{
//			if(RxData == '\n')                                                       //��β����λ��
//			{
//				RxState = 0;
//				Serial_RxPacket[pRxPacket] =  '\0';
//				Serial_RxFlag = 1;
//			}
//		}	
//		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
//	}
//}

/*UART*//*ʾ��*/
//		if (Serial_GetRxFlag() == 1)	
//		{
//			OLED_ShowHexNum(1, 6, Serial_RxPacket[0], 3);	
//			OLED_ShowHexNum(2, 6, Serial_RxPacket[1], 3);
//			
//			Servo_180_Angle(Serial_RxPacket[0]);
//			Servo_270_Angle(Serial_RxPacket[1]);
//			
//		}
