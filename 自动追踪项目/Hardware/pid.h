#ifndef __PID_H
#define __PID_H

extern float Kp,Ki,Kd;   //直立环参数
extern float err;               //此次误差
extern float last_err;          //上次误差
extern float err_sum=0;         //误差累加
extern float err_difference;    //误差的差值

#endif
