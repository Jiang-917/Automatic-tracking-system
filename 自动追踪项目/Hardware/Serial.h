#ifndef __SERIAL_H
#define __SERIAL_H

#include <stdio.h>

/*������HEXģʽ���ı�ģʽ��ע��*/
extern uint8_t Serial_TxPacket[];
extern uint8_t Serial_RxPacket[];

/*�������ı�ģʽ��HEXģʽ��ע��*/
//extern char Serial_RxPacket[];
//extern uint8_t Serial_RxFlag;

/*ͨ�ú���*/
void Serial_Init(void);                                                              //USART��ʼ������
void Serial_SendByte(uint8_t Byte);                                                  //�����ֽ�
void Serial_SendArray(uint8_t *Array, uint16_t Length);                              //��������
void Serial_SendString(char *String);                                                //�����ַ�
void Serial_SendNumber(uint32_t Number, uint8_t Length);                             //�ַ�����ʽ����
void Serial_Printf(char *format, ...);                                               //sprintf
uint8_t Serial_GetRxFlag(void);                                                      //�Ƿ���ܵ����ݰ������յ�Ϊ1

/*������HEXģʽ���ı�ģʽ��ע��*/
void Serial_SendPacket(void);                                                        //HEXģʽ�������ݰ�

#endif
