#ifndef __USART_H_
#define __USART_H_
#include "stm32f10x.h"

void Usart_Init(uint32_t BaudRate);
void UsartSend_u8(u8 Data);
void UsartSend_int(int *data);
void ANO_Send_Ack(u8 head, u8 check_sum);
void Usart2_Init(uint32_t BaudRate);

void ANO_Send_float(float *data);
void ANO_Send_fly(float pitch,float roll,float yaw);



#define ByteTrans_3(data) (*((char*) (&data)+3))
#define ByteTrans_2(data) (*((char*) (&data)+2))
#define ByteTrans_1(data) (*((char*) (&data)+1))
#define ByteTrans_0(data) (*((char*) (&data)+0))

extern float UsartSendData_float[4];
extern int UsartSendData_int[4];

	
#endif

