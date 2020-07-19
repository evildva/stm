#ifndef _USART_H
#define	_USART_H

#include "stm32f4xx.h"
#include <stdio.h>



//引脚定义
/*******************************************************/
#define USART                             USART1
#define USART_CLK                         RCC_APB2Periph_USART1

#define USART_RX_GPIO_PORT                GPIOA
#define USART_RX_GPIO_CLK                 RCC_AHB1Periph_GPIOA
#define USART_RX_PIN                      GPIO_Pin_10
#define USART_RX_AF                       GPIO_AF_USART1
#define USART_RX_SOURCE                   GPIO_PinSource10

#define USART_TX_GPIO_PORT                GPIOA
#define USART_TX_GPIO_CLK                 RCC_AHB1Periph_GPIOA
#define USART_TX_PIN                      GPIO_Pin_9
#define USART_TX_AF                       GPIO_AF_USART1
#define USART_TX_SOURCE                   GPIO_PinSource9
/************************************************************/


//串口波特率
#define USART_BAUDRATE                    9600



void USART_Config(void);
//int fputc(int ch, FILE *f);

#endif /* __USART1_H */
