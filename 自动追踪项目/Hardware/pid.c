#include "stm32f10x.h"                  // Device header

float Kp,Ki,Kd;         
float err;               //�˴����
float last_err;          //�ϴ����
float err_sum=0;         //����ۼ�
float err_difference;    //���Ĳ�ֵ

