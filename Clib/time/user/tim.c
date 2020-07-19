#include "tim.h"
#include "stm32f4xx.h"

typedef void(*Callback)(void);

void Tim_Config(void)
{

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct=// time=(period+1) * (pres+1)/Fpclk
  {
		.TIM_Period=10*1000-1,//1000 ms
		.TIM_Prescaler=SystemCoreClock/10000-1,
		.TIM_CounterMode=TIM_CounterMode_Up,
		//.TIM_ClockDivision=TIM_CKD_DIV1,
		.TIM_RepetitionCounter=0
	};
	
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStruct);
	
	NVIC_InitTypeDef NVIC_InitStruct=
	{
		.NVIC_IRQChannel=TIM1_UP_TIM10_IRQn,
		.NVIC_IRQChannelPreemptionPriority=1,
		.NVIC_IRQChannelSubPriority=1,
		.NVIC_IRQChannelCmd=ENABLE
	};
	
	NVIC_Init(&NVIC_InitStruct);
	
	TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);
	
	TIM_Cmd(TIM1,ENABLE);
}

void TIM_Handler(Callback tim)
{
	TIM_ClearITPendingBit(TIM1,TIM_IT_Update);
	tim();
}

