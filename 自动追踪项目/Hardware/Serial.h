#ifndef __SERIAL_H
#define __SERIAL_H

#include <stdio.h>

/*服务于HEX模式，文本模式需注释*/
extern uint8_t Serial_TxPacket[];
extern uint8_t Serial_RxPacket[];

/*服务于文本模式，HEX模式需注释*/
//extern char Serial_RxPacket[];
//extern uint8_t Serial_RxFlag;

/*通用函数*/
void Serial_Init(void);                                                              //USART初始化函数
void Serial_SendByte(uint8_t Byte);                                                  //发送字节
void Serial_SendArray(uint8_t *Array, uint16_t Length);                              //发送数组
void Serial_SendString(char *String);                                                //发送字符
void Serial_SendNumber(uint32_t Number, uint8_t Length);                             //字符串形式数字
void Serial_Printf(char *format, ...);                                               //sprintf
uint8_t Serial_GetRxFlag(void);                                                      //是否接受到数据包，接收到为1

/*服务于HEX模式，文本模式需注释*/
void Serial_SendPacket(void);                                                        //HEX模式接收数据包

#endif
