#include "main.h"
#include <string.h>

void Usart_SendByte( USART_TypeDef * USARTx, uint8_t ch)
 {
	USART_SendData(USARTx,ch);
	while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);
 }
 
void Usart_SendString( USART_TypeDef * USARTx, char *str)
{
 unsigned int k=0;
 do {
 Usart_SendByte( USARTx, *(str + k) );
 k++;
 } while (*(str + k)!='\0');
 
 while (USART_GetFlagStatus(USARTx,USART_FLAG_TC)==RESET){}
}

void Usart_Rece(char buf[],int size)
{
	int n=0;
	while(buf[n]!='\0')
	{
	if(USART_GetITStatus(USART1,USART_IT_RXNE))
	{
		buf[n++]=USART_ReceiveData(USART1);
	}
  }
}

void wait()
{
	int i;
	for(i=0;i<1000000;i++);
}
////////////////////////////////////////////////////

char a[64],b[64],ind=0,inde=0;
int idle=0,idlee=0;

int main()
{
	int i;
	
	usart1_init();
	usart3_init();
	//sprintf(a,"%d",*(int*)0xE0042000);
	//Usart_SendString(USART1,a);
	/*
	while(1)
	{
		
		if(idle)
		{
			idle=0;
			
			Usart_SendString(USART3,a);
			for(i=0;i<ind;i++)
			{
				a[i]='\0';
			}
			
			ind=0;
			printf("\n");
		}
		
		if(idlee)
		{
			idlee=0;
			
			Usart_SendString(USART1,b);
			for(i=0;i<inde;i++)
			{
				b[i]='\0';
			}
			
			inde=0;
			printf("\n");
		}
		
	}
	*/
}

void USART1_IRQHandler()
{
	if(USART_GetITStatus(USART1,USART_IT_RXNE))
	{
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
		a[ind]=USART_ReceiveData(USART1);
		ind++;
		printf("%c",USART1->DR);
	}
	
	if(USART_GetITStatus(USART1,USART_IT_IDLE))
	{
		//USART_ClearITPendingBit(USART1,USART_IT_IDLE);
		USART1->SR;
		USART1->DR;
		idle=1;
		printf("%s","idle");
	}

}

void USART3_IRQHandler()
{
	if(USART_GetITStatus(USART3,USART_IT_RXNE))
	{
		USART_ClearITPendingBit(USART3,USART_IT_RXNE);
		b[inde]=USART_ReceiveData(USART3);
		inde++;
		printf("%c",USART3->DR);
	}
	
	if(USART_GetITStatus(USART3,USART_IT_IDLE))
	{
		//USART_ClearITPendingBit(USART1,USART_IT_IDLE);
		USART3->SR;
		USART3->DR;
		idlee=1;
		printf("%s","idlee");
	}

}
