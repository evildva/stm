#include "main.h"

int main()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_CRC, ENABLE);
	USART_Config();
	
	while(1)
	{
	  printf("usart test \n");
	}
}
