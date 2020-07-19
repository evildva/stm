#ifndef __QUEUE__H__
#define __QUEUE__H__ 
//#include "core_cm4.h"
#include "stdint.h"
typedef struct  
{
	uint16_t in;
	uint16_t out;
	uint16_t cntMax;
	uint8_t*  pBuf;
}QueueT;

/*���е��ص㣺�Ƚ��ȳ������������ˣ������ٷ����ݡ���ѭ��ʹ�ö��е�λ��*/

void QueueCreate(QueueT* thiz,uint8_t* BufAddress,uint16_t  BufSize); //����һ�����У���ʼ���ṹ������ĳ�Ա
uint16_t getDataCount(QueueT* thiz); //��ȡ����������Ч�����ݵĴ�С
uint16_t getEmptyCount(QueueT* thiz); //��ȡ�������滹ʣ����ٿյ�λ��
uint8_t inQueue(QueueT* thiz,uint8_t data); //��һ�����ݷŽ�����
uint8_t outQueue(QueueT* thiz); //�Ӷ���������һ�����ݳ���

#endif //__QUEUE__H__
