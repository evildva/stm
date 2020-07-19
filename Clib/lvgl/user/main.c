#include "main.h"
#include "lvgl.h"
#include "lv_hal_disp.h"

int main()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_CRC, ENABLE);
	USART_Config();
	lv_init();
	lv_port_disp_init();
	while(1)
	{
	  lv_task_handler();
	}
}
