#ifndef _USART_H
#define	_USART_H

#include "stm32f4xx.h"
#include "misc.h"
#include <stdio.h>

void USART_gpio(int rate);
void USART_nvic();
//int fputc(int ch, FILE *f);

#endif /* __USART1_H */
