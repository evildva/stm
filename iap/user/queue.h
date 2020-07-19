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

/*队列的特点：先进先出，若队列满了，不能再放数据。可循环使用队列的位置*/

void QueueCreate(QueueT* thiz,uint8_t* BufAddress,uint16_t  BufSize); //创建一个队列，初始化结构体里面的成员
uint16_t getDataCount(QueueT* thiz); //获取队列里面有效的数据的大小
uint16_t getEmptyCount(QueueT* thiz); //获取队列里面还剩余多少空的位置
uint8_t inQueue(QueueT* thiz,uint8_t data); //将一个数据放进队列
uint8_t outQueue(QueueT* thiz); //从队列里面拿一个数据出来

#endif //__QUEUE__H__
