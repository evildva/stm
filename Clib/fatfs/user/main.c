#include "main.h"

void putch(unsigned char a)
{
	FILE *f=NULL;
	fputc(a,f);
}

int main()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_CRC, ENABLE);
	USART_Config();
	//xfunc_out=putch;
	
	while(1)
	{
		//xprintf("%d %s %c \n",1,"abc",12);
	  printf("usart test \n");
	}
}
