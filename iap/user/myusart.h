char rece[128];

void receive()
{
	char dr[16];
	while(!USART_GetFlagStatus(USART1,USART_FLAG_IDLE))
	{
		if(USART_GetFlagStatus(USART1,USART_FLAG_RXNE))
		{
			*dr=USART1->DR;
			strcat(rece,dr);
		}
	}
}

////////////////////////////////////////////////////
#define size 128

struct
{
	char data[size];
	int curindex;
}
Receive={.curindex=0};

void add(char ch)
{
	if(Receive.curindex<size)
	{
		Receive.data[Receive.curindex++]=ch;
	}
}

void put()
{
	Usart_SendString(USART1,Receive.data);
	Receive.curindex=0;
}