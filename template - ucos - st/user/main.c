#include "main.h"


//任务优先级
#define TASK1_TASK_PRIO		4
//任务堆栈大小	
#define TASK1_STK_SIZE 		128
//任务控制块
OS_TCB Task1_TaskTCB;
//任务堆栈	
CPU_STK TASK1_TASK_STK[TASK1_STK_SIZE];
void task_task(void *p_arg);


int main()
{
	OS_ERR err;
	CPU_SR_ALLOC();
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_CRC, ENABLE);
	USART_Config();
	ILI9806G_Init();
	OSInit(&err);
	
	ILI9806G_DispStringLine_EN(270,"Init finish");
	
	OS_CRITICAL_ENTER();
	
	OSTaskCreate((OS_TCB 	* )&Task1_TaskTCB,		
				 (CPU_CHAR	* )"Task1 task", 		
                 (OS_TASK_PTR )task_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )TASK1_TASK_PRIO,     
                 (CPU_STK   * )&TASK1_TASK_STK[0],	
                 (CPU_STK_SIZE)TASK1_STK_SIZE/10,	
                 (CPU_STK_SIZE)TASK1_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR 	* )&err);
								 
	OS_CRITICAL_EXIT();	//退出临界区	
								 
	OSStart(&err);      //开启UCOSIII
								 
}

void task_task(void *p_arg)
{
	while(1)
	{
		ILI9806G_DrawCircle(100,100,100,1);
	  printf("usart test \n");
		ILI9806G_DispStringLine_EN(300,"usart ili9806g");
		ILI9806G_DispStringLine_EN(330,"usart ili9806g");
	}
}
