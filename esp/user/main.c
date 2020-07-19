#include "main.h"
#include "usart3.h"

int times=10;

int main()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_CRC, ENABLE);
	USART_Config();
	usart3_init();
	//ILI9806G_Init();
	
	print(USART1,"%s \n","abcde");
	
	while(times--)
	{
		
	}
	
}
