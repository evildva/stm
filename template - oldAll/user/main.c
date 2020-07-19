#include "main.h"

#define str(number) #number

int main()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_CRC, ENABLE);
	//USART_Config();
	ILI9806G_Init();
	
	int i=0;
	int row=250;
	
	while(1)
	{
		ILI9806G_DrawCircle(100,100,100,1);
	  //printf("usart test \n");
		for(i=0;i<10;i++){
			ILI9806G_DispStringLine_EN(row,str(*));
			//ILI9806G_DispStringLine_EN(row+30,str(*));
			row=row+31;
			if(row>800)
				row=row-615;
		}
	}
}
