#include "main.h"


int main()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_CRC, ENABLE);
	ILI9806G_Init();
	
	while(1)
	{
		ILI9806G_DrawCircle(100,100,100,1);
		ILI9806G_DispStringLine_EN(300,"usart ili9806g");
		ILI9806G_DispStringLine_EN(330,"usart ili9806g");
	}
}
