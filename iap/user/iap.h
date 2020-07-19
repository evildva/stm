#ifndef __IAP_H__
#define __IAP_H__
#include "stdint.h"
#include "stm32f4xx.h"
#define updata_flagaddr 0x8002C00  //升级标志
#define verify_flagaddr 0x800FF10    //在app里面
#define ACK   0x79        //肯定应答
#define NACK  0x1F        //否定应答

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
unsigned char waitdata(void)  //阻塞等待一个数据到来
{
	while(1){
		if(getDataCount(&RxQueueEntity)!=0){
		      return outQueue(&RxQueueEntity);
			}
	}
}
#endif //__IAP_H__
