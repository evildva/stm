#include "usart.h"

void USART_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;
		
  RCC_AHB1PeriphClockCmd( USART_RX_GPIO_CLK|USART_TX_GPIO_CLK, ENABLE);

  RCC_APB2PeriphClockCmd(USART_CLK, ENABLE);
  
  GPIO_PinAFConfig(USART_RX_GPIO_PORT,USART_RX_SOURCE, USART_RX_AF);

  GPIO_PinAFConfig(USART_TX_GPIO_PORT,USART_TX_SOURCE,USART_TX_AF);

  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;

  GPIO_InitStructure.GPIO_Pin = USART_TX_PIN  ;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(USART_TX_GPIO_PORT, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Pin = USART_RX_PIN;
  GPIO_Init(USART_RX_GPIO_PORT, &GPIO_InitStructure);
			
  USART_InitStructure.USART_BaudRate = USART_BAUDRATE;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No ;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(USART, &USART_InitStructure); 
  USART_Cmd(USART, ENABLE);
}

int fputc(int ch, FILE *f)
{
		
		USART_SendData(USART, (uint8_t) ch);
		while (USART_GetFlagStatus(USART, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}

int fgetc(FILE *f)
{

		while (USART_GetFlagStatus(USART, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(USART);
}

