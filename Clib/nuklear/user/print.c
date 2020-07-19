#include "print.h"

struct __FILE 
{ 
	int handle; 
};

FILE __stdout;

void _sys_exit(int x) 
{ 
	x = x; 
}

int print(void* out, const char*fmt, ...)
{
	#define PRINTF_NUM  100
	
	int ret;
	char *p;
	char temp[PRINTF_NUM]={'\0'};
	
	va_list ap; 
	p= temp;   
	va_start(ap,fmt);
	ret=vsprintf(p,fmt,ap);
	
	do{
		USART_SendData(out, *(p++));
		while (USART_GetFlagStatus(out, USART_FLAG_TXE) == RESET);
	}
	while(*p!='\0');
	va_end(ap);
	
	return ret;
}
