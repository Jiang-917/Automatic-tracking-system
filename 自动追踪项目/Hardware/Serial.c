/*USART*/
/******主体分为HEX模式和文本模式两种模式，使用时注意注释另一种模式的语句******/

#include "stm32f10x.h"                                                               // Device header
#include <stdio.h>
#include <stdarg.h>

/*HEX模式所需变量*/
uint8_t Serial_TxPacket[4];                                                        //发送数组
uint8_t Serial_RxPacket[4];                                                        //接收数组

/*文本模式所需变量*/
//char Serial_RxPacket[100];                                                           //接收数组

/*通用变量*/
uint8_t Serial_RxFlag;                                                               //读取标志位

void Serial_Init(void)                                                               // USART初始化函数
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);                           //使用USART1
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
	USART_InitStructure.USART_BaudRate = 9600;                                       //波特率
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;  //硬件流控制
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;                  //串口模式
	USART_InitStructure.USART_Parity = USART_Parity_No;                              //校验位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;                           //停止位
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;                      //字长
	USART_Init(USART1, &USART_InitStructure);
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);                                   //配置中断接收数据
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&NVIC_InitStructure);

	USART_Cmd(USART1, ENABLE);
}

void Serial_SendByte(uint8_t Byte)                                                   //发送字节
{
	USART_SendData(USART1, Byte);
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);                    //等待TXE标志位置1
}

void Serial_SendArray(uint8_t *Array, uint16_t Length)                               //发送数组
{
	uint16_t i;
	for (i = 0; i < Length; i ++)
	{
		Serial_SendByte(Array[i]);
	}
}

void Serial_SendString(char *String)                                                 //发送字符
{
	uint8_t i;
	for (i = 0; String[i] != '\0'; i ++)
	{
		Serial_SendByte(String[i]);
	}
}

uint32_t Serial_Pow(uint32_t X, uint32_t Y)                                          //服务于Serial_SendNumber()
{
	uint32_t Result = 1;
	while (Y --)
	{
		Result *= X;
	}
	return Result;
}

void Serial_SendNumber(uint32_t Number, uint8_t Length)                              //字符串形式数字
{
	uint8_t i;
	for (i = 0; i < Length; i ++)
	{
		Serial_SendByte(Number / Serial_Pow(10, Length - i - 1) % 10 + '0');
	}
}

int fputc(int ch, FILE *f)                                                           //printf重定向到串口,文本模式
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

/*服务于HEX模式，文本模式需注释*/
void Serial_SendPacket(void)                                                       //HEX模式发送数据包
{
	Serial_SendByte(0xFF);
	Serial_SendArray(Serial_TxPacket,4);
	Serial_SendByte(0xFE);
}

uint8_t Serial_GetRxFlag(void)                                                       //获取读标志位
{
	if(Serial_RxFlag == 1)
	{
		Serial_RxFlag = 0;
		return 1;
	}
	return 0;
}

/*中断函数***中断状态机***HEX模式*/
void USART1_IRQHandler(void)                                                         //接收数据包
{
	static uint8_t RxState = 0;                                                      //状态变量
	static uint8_t pRxPacket = 0;                                                    //接收数量

	if(USART_GetFlagStatus(USART1, USART_IT_RXNE) == SET)
	{
		uint8_t RxData = USART_ReceiveData(USART1);
		
		if(RxState == 0)                                                             //等待包头
		{
			if(RxData == 0xFF)                                                       //包头定义位置
			{
				RxState = 1;
				pRxPacket = 0;
			}
		}
		else if(RxState == 1)                                                        //接收数据
		{
			Serial_RxPacket[pRxPacket] = RxData;
			pRxPacket++;
			if(pRxPacket >= 2)
			{
				RxState = 2;
			}
		}
		else if(RxState == 2)                                                        //等待包尾
		{
			if(RxData == 0xFE)                                                       //包尾定义位置
			{
				RxState = 0;
				Serial_RxFlag = 1;
			}
		}	
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}
}

/*中断函数***中断状态机***文本模式****\r \n***/
//void USART1_IRQHandler(void)                                                       //接收数据包
//{
//	static uint8_t RxState = 0;                                                      //状态变量
//	static uint8_t pRxPacket = 0;                                                    //接收数量

//	if(USART_GetFlagStatus(USART1, USART_IT_RXNE) == SET)
//	{
//		uint8_t RxData = USART_ReceiveData(USART1);
//		
//		if(RxState == 0)                                                             //等待包头
//		{
//			if(RxData == '@')                                                        //包头定义位置
//			{
//				RxState = 1;
//				pRxPacket = 0;
//			}
//		}
//		else if(RxState == 1)                                                        //接收数据
//		{
//			if (RxData == '\r')                                                      //长度不确定，必须先判断是不是包尾
//			{
//				RxState = 2;
//			}
//			else
//			{
//				Serial_RxPacket[pRxPacket] = RxData;
//				pRxPacket++;
//			}
//		}
//		else if(RxState == 2)                                                        //等待包尾
//		{
//			if(RxData == '\n')                                                       //包尾定义位置
//			{
//				RxState = 0;
//				Serial_RxPacket[pRxPacket] =  '\0';
//				Serial_RxFlag = 1;
//			}
//		}	
//		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
//	}
//}

/*UART*//*示例*/
//		if (Serial_GetRxFlag() == 1)	
//		{
//			OLED_ShowHexNum(1, 6, Serial_RxPacket[0], 3);	
//			OLED_ShowHexNum(2, 6, Serial_RxPacket[1], 3);
//			
//			Servo_180_Angle(Serial_RxPacket[0]);
//			Servo_270_Angle(Serial_RxPacket[1]);
//			
//		}
