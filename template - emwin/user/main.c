#include "main.h"
#include "BUTTON.h"

int main()
{
	SysTick_Config(SystemCoreClock / 1000);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_CRC, ENABLE);
	USART_Config();
	ILI9806G_Init();
	GUI_Init();
	
	while(1)
	{
    ILI9806G_DispString_EN(20,20,"abc lcd");
	}
}

