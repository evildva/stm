#include "main.h"

int a[10]={1,2,3,4,5,6,7,8,9,10},b[10];
int f=1;

void Dma_Config()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
	
	DMA_DeInit(DMA2_Stream0);
	
	while (DMA_GetCmdStatus(DMA2_Stream0) != DISABLE)
  {
  }
	
	DMA_InitTypeDef DMA_InitStructure;
	DMA_InitStructure.DMA_Channel = DMA_Channel_0;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)a;
	DMA_InitStructure.DMA_Memory0BaseAddr = b;
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToMemory;
	DMA_InitStructure.DMA_BufferSize = 10;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	
	DMA_ITConfig(DMA2_Stream0,DMA_IT_TC,ENABLE);
	
	DMA_ClearFlag(DMA2_Stream0,DMA_IT_TC);
	DMA_Init(DMA2_Stream0,&DMA_InitStructure);
	DMA_Cmd(DMA2_Stream0,ENABLE);
}


int main()
{
	Dma_Config();
	//DMA_NVIC_Config();
	USART_Config();
	
	while(DMA_GetFlagStatus(DMA2_Stream0,DMA_FLAG_TCIF0)==DISABLE)
  {
  }
	
	while(1)
	{
		if(f)
		{
			for(f=0;f<10;f++)
			{
				printf("%d\n",b[f]);
			}
			//f=0;
		}
	  //printf("usart dma test \n");
	}
}

void DMA2_Stream0_IRQHandler(void)
{
	if(DMA_GetITStatus(DMA2_Stream0,DMA_IT_TC)==SET)
	{
		f=1;
		DMA_ClearITPendingBit(DMA2_Stream0,DMA_IT_TC);
	}
}
