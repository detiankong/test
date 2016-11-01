#include "usart_.h"
#include "delay.h"
#include "control.h"

extern AnglePID_ AnglePID;
extern PID SpeedPID;

#define BufferSize 23

float UsartSendData_float[4];
int UsartSendData_int[4];
u8 ANO_RxBuf[BufferSize];

void Usart_Init(uint32_t BaudRate)
{
	USART_InitTypeDef USART_InitTstruct;
	NVIC_InitTypeDef NVIC_Initstruct;
	GPIO_InitTypeDef GPIO_InitTstruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTstruct.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitTstruct.GPIO_Pin=GPIO_Pin_9;//TX
	GPIO_InitTstruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitTstruct);
	
	GPIO_InitTstruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitTstruct.GPIO_Pin=GPIO_Pin_10;//RX
	GPIO_InitTstruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitTstruct);
	
	USART_InitTstruct.USART_BaudRate=BaudRate;
	USART_InitTstruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitTstruct.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_InitTstruct.USART_Parity=USART_Parity_No;
	USART_InitTstruct.USART_StopBits=USART_StopBits_1;
	USART_InitTstruct.USART_WordLength=USART_WordLength_8b;
	USART_Init(USART1,&USART_InitTstruct);
	
	USART_Cmd(USART1,ENABLE);
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	
	NVIC_Initstruct.NVIC_IRQChannel=USART1_IRQn;
	NVIC_Initstruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Initstruct.NVIC_IRQChannelPreemptionPriority=0X00;
	NVIC_Initstruct.NVIC_IRQChannelSubPriority=0X02;
	NVIC_Init(&NVIC_Initstruct);
}

void USART1_IRQHandler(void)
{
	u8 res;
	if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)
	{
		res=USART_ReceiveData(USART1);
		USART_SendData(USART1,res);
	}
	USART_ClearITPendingBit(USART1,USART_IT_RXNE);
}

void UsartSend_u8(u8 Data)
{
	USART_SendData(USART1,Data);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
}

void Usart2_Init(uint32_t BaudRate)
{
	USART_InitTypeDef USART_InitTstruct;
	NVIC_InitTypeDef NVIC_Initstruct;
	GPIO_InitTypeDef GPIO_InitTstruct;
	DMA_InitTypeDef DMA_InitTstruct;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	
	GPIO_InitTstruct.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitTstruct.GPIO_Pin=GPIO_Pin_2;//TX
	GPIO_InitTstruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitTstruct);
	
	GPIO_InitTstruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitTstruct.GPIO_Pin=GPIO_Pin_3;//RX
	GPIO_InitTstruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitTstruct);
	
	USART_InitTstruct.USART_BaudRate=BaudRate;
	USART_InitTstruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitTstruct.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_InitTstruct.USART_Parity=USART_Parity_No;
	USART_InitTstruct.USART_StopBits=USART_StopBits_1;
	USART_InitTstruct.USART_WordLength=USART_WordLength_8b;
	USART_Init(USART2,&USART_InitTstruct);		
	
	DMA_InitTstruct.DMA_BufferSize=BufferSize;
	DMA_InitTstruct.DMA_DIR=DMA_DIR_PeripheralSRC;
	DMA_InitTstruct.DMA_M2M=DMA_M2M_Disable;
	DMA_InitTstruct.DMA_MemoryBaseAddr=(u32)ANO_RxBuf;
	DMA_InitTstruct.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte;
	DMA_InitTstruct.DMA_MemoryInc=DMA_MemoryInc_Enable;
	DMA_InitTstruct.DMA_Mode=DMA_Mode_Circular;
	DMA_InitTstruct.DMA_PeripheralBaseAddr=(u32)&(USART2->DR);
	DMA_InitTstruct.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte;
	DMA_InitTstruct.DMA_PeripheralInc=DMA_PeripheralInc_Disable;
	DMA_InitTstruct.DMA_Priority=DMA_Priority_Medium;
	DMA_Init(DMA1_Channel6,&DMA_InitTstruct);
	
	DMA_ITConfig(DMA1_Channel6,DMA_IT_TC,ENABLE);
	
	USART_DMACmd(USART2, USART_DMAReq_Rx,ENABLE);
	
	NVIC_Initstruct.NVIC_IRQChannel=DMA1_Channel6_IRQn;
	NVIC_Initstruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Initstruct.NVIC_IRQChannelPreemptionPriority=0X00;
	NVIC_Initstruct.NVIC_IRQChannelSubPriority=0X02;
	NVIC_Init(&NVIC_Initstruct);
	
	DMA_Cmd(DMA1_Channel6,ENABLE);
#if 0	
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
	
	NVIC_Initstruct.NVIC_IRQChannel=USART2_IRQn;
	NVIC_Initstruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Initstruct.NVIC_IRQChannelPreemptionPriority=0X20;
	NVIC_Initstruct.NVIC_IRQChannelSubPriority=0X00;
	NVIC_Init(&NVIC_Initstruct);
#endif

	USART_Cmd(USART2,ENABLE);	
}
#if 1
void USART2_IRQHandler(void)
{
	u8 res;
	if(USART_GetITStatus(USART2,USART_IT_RXNE)!=RESET)
	{
		res=USART_ReceiveData(USART2);
		USART_SendData(USART2,res);
	}
	USART_ClearITPendingBit(USART2,USART_IT_RXNE);
}
#endif


 void ANO_Decode(void)
{
	u8 sum=0,i;
	
	for(i=0;i<BufferSize-1;i++)
		sum+=ANO_RxBuf[i];					//根据协议 求校验和
	if( (sum!=ANO_RxBuf[BufferSize-1]) || (ANO_RxBuf[0]!=0xAA) || (ANO_RxBuf[1]!=0xAF) )	
	   return ;//判断校验和 以及帧头 不对就返回
	if( (ANO_RxBuf[2]==0x10)&&(ANO_RxBuf[3]==0x12) )
	{
		AnglePID.Core.Kp=((int16_t)ANO_RxBuf[4])<<8|ANO_RxBuf[5];
		AnglePID.Core.Ki=((int16_t)ANO_RxBuf[6])<<8|ANO_RxBuf[7];
		AnglePID.Core.Kd=((int16_t)ANO_RxBuf[8])<<8|ANO_RxBuf[9];
		AnglePID.Shell.Kp=((int16_t)ANO_RxBuf[10])<<8|ANO_RxBuf[11];
		AnglePID.Shell.Ki=((int16_t)ANO_RxBuf[12])<<8|ANO_RxBuf[13];
		AnglePID.Shell.Kd=((int16_t)ANO_RxBuf[14])<<8|ANO_RxBuf[15];
		SpeedPID.Kp=((int16_t)ANO_RxBuf[16])<<8|ANO_RxBuf[17];
		SpeedPID.Ki=((int16_t)ANO_RxBuf[18])<<8|ANO_RxBuf[19];
		SpeedPID.Kd=((int16_t)ANO_RxBuf[20])<<8|ANO_RxBuf[21];
	}	
	ANO_Send_Ack(ANO_RxBuf[2],sum);	//向上位机发送ACK
}

void ANO_Send_Ack(u8 head, u8 check_sum)
{
	u8 cnt=0,i,sum;
	char data_buff[7];
	
	data_buff[cnt++]=0xAA;
	data_buff[cnt++]=0xAA;
	data_buff[cnt++]=0xEF;
	data_buff[cnt++]=2;
	data_buff[cnt++]=head;
	data_buff[cnt++]=check_sum;
	
	for(i=0;i<cnt;i++)
		sum+=data_buff[i];
	
	data_buff[cnt++]=sum;
	
		for(i=0;i<cnt;i++)
	{
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);
		USART_SendData(USART2,*(data_buff+cnt));
		delay_us(10);
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);
	}	
}
void DMA1_Channel6_IRQHandler(void)
{
	if(DMA_GetITStatus(DMA1_IT_TC6)!=RESET)
	{
		ANO_Decode();//数据解析		
	}
		DMA_ClearITPendingBit(DMA1_IT_TC6);	
	
}



#define BYTE0(dwTemp)       ( *( (char *)(&dwTemp)		) )
#define BYTE1(dwTemp)       ( *( (char *)(&dwTemp) + 1) )
#define BYTE2(dwTemp)       ( *( (char *)(&dwTemp) + 2) )
#define BYTE3(dwTemp)       ( *( (char *)(&dwTemp) + 3) )


void ANO_Send_float(float *data)
{
	char data_buff[16];
	u8 num,sum,cnt=0;
	
	data_buff[cnt++]=0xAA;//帧头
	data_buff[cnt++]=0xAA;
	
	data_buff[cnt++]=0xF1;	//功能字
	
	data_buff[cnt++]=0;	//数据长度  后面计算
	
	
	for(num=0;num<4;num++)
	{
		data_buff[cnt++]=BYTE3(*(data+num));
		data_buff[cnt++]=BYTE2(*(data+num));
		data_buff[cnt++]=BYTE1(*(data+num));
		data_buff[cnt++]=BYTE0(*(data+num));
	}
	
	data_buff[3]=cnt-4;	//计算 长度
	
	for(num=0;num<cnt;num++)
		sum+=data_buff[num];
	
	data_buff[cnt++]=sum;
	
	for(num=0;num<cnt;num++)
	{
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);
		USART_SendData(USART2,*(data_buff+num));
		delay_us(10);
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);
	}
	
}
void ANO_Send_fly(float angle_rol, float angle_pit, float angle_yaw)
{
	u8 _cnt=0,num,sum=0;
	vs16 _temp;
	vs32 _temp2 = 0;
	u8 data_to_send[17];
	
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0x01;
	data_to_send[_cnt++]=0;
	
	_temp = (int)(angle_rol*100);
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = (int)(angle_pit*100);
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = (int)(angle_yaw*100);
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	
	data_to_send[_cnt++]=BYTE3(_temp2);
	data_to_send[_cnt++]=BYTE2(_temp2);
	data_to_send[_cnt++]=BYTE1(_temp2);
	data_to_send[_cnt++]=BYTE0(_temp2);
	
	data_to_send[_cnt++] = 0;
	
	data_to_send[_cnt++] = 1;
	
	data_to_send[3] = _cnt-4;
	
	for(num=0;num<_cnt;num++)
		sum += data_to_send[num];
	data_to_send[_cnt++]=sum;
	
	for(num=0;num<_cnt;num++)
	{
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);
		USART_SendData(USART2,*(data_to_send+num));
		delay_us(10);
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);
	}
	
}

