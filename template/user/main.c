#include "main.h"

int main()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_CRC, ENABLE);
	//USART_Config();
	ILI9806G_Init();
	GTP_Init_Panel();
	
	while(1)
	{
		ILI9806G_DrawCircle(100,100,100,1);
	  //printf("usart test \n");
		ILI9806G_DispStringLine_EN(300,"usart ili9806g");
		ILI9806G_DispStringLine_EN(330,"usart ili9806g");
	}
}
