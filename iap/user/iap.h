#ifndef __IAP_H__
#define __IAP_H__
#include "stdint.h"
#include "stm32f4xx.h"
#define updata_flagaddr 0x8002C00  //������־
#define verify_flagaddr 0x800FF10    //��app����
#define ACK   0x79        //�϶�Ӧ��
#define NACK  0x1F        //��Ӧ��

typedef struct{
	  unsigned char cmd;
	  void (*pfunction)(void);
}CommandHandleStruct;

typedef  void (*iapfun)(void);
void jump_to_app(uint32_t appxaddr);			

extern const CommandHandleStruct CmdHdlStr[11];

void sengdata(unsigned char data)
{
	USART_SendData(USART1, (unsigned char) data);
	while( USART_GetFlagStatus(USART1,USART_FLAG_TC)!= SET);	
}
#include "queue.h"
extern QueueT RxQueueEntity;
unsigned char waitdata(void)  //�����ȴ�һ�����ݵ���
{
	while(1){
		if(getDataCount(&RxQueueEntity)!=0){
		      return outQueue(&RxQueueEntity);
			}
	}
}
#endif //__IAP_H__
