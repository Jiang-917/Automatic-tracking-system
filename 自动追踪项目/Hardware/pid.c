#include "stm32f10x.h"                  // Device header

float Kp,Ki,Kd;         
float err;               //此次误差
float last_err;          //上次误差
float err_sum=0;         //误差累加
float err_difference;    //误差的差值

