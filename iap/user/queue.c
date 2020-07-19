#include "queue.h"
void QueueCreate(QueueT* thiz,uint8_t* BufAddress,uint16_t  BufSize)
{
		thiz->in=0;
		thiz->out=0;
		thiz->cntMax=BufSize;
	    thiz->pBuf=BufAddress;
}

uint16_t getDataCount(QueueT* thiz)
{
	  if (thiz->in >= thiz->out){
        return (thiz->in - thiz->out);
     }else{
        return (thiz->in + thiz->cntMax - thiz->out);
     }
}

uint16_t  getEmptyCount(QueueT* thiz)
{
	uint16_t dataCnt;
		 
    if (thiz->in >= thiz->out){
        dataCnt=(thiz->in - thiz->out);
    }else{
        dataCnt=(thiz->in + thiz->cntMax - thiz->out);
    }
		
	if ((dataCnt+1u) >= thiz->cntMax){
        return 0; //fifo full
    }
	return  (thiz->cntMax-dataCnt-1u);

}

uint8_t inQueue(QueueT* thiz,uint8_t data)
{
	    uint16_t   in;

     in =  thiz->in + 1u;
     if (in >= thiz->cntMax){
         in = 0;
     }

     if (in == thiz->out){ //full fifo
         return 0;
     }

     thiz->pBuf[thiz->in] = data;
     thiz->in = in;

     return 1;
}

uint8_t  outQueue(QueueT* thiz)
{
	   uint8_t   data;
     uint16_t  out;
	
     if (thiz->in == thiz->out){ //empty fifo
         return 0;
     }

     out = thiz->out;
     data = thiz->pBuf[out];
     out++;
     if (out >= thiz->cntMax){
         out = 0;
     }
     thiz->out = out;

     return data;
}
