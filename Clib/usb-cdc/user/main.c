#include "main.h"
#include "fsmc.h"
#include "gt5xx.h"
#include "sram.h"
#include "GUI.h"
#include "LISTVIEW.h"
#include "usbd_usr.h"
#include "usbd_desc.h"
#include "usbd_cdc_if.h"

uint32_t APP_Rx_ptr_in=0;
CDC_IF_Prop_TypeDef  APP_FOPS;

__ALIGN_BEGIN USB_OTG_CORE_HANDLE     USB_OTG_dev __ALIGN_END;

extern USBD_Class_cb_TypeDef  USBD_CDC_cb;

void USART_SendString(char* string)
{
	while(*string!='\0')
	{
		USART_SendData(USART1,*string);
		string++;
		while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);	
	}
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);
}


int times=0;
typedef struct{
	char* info[200];
	int handled;
}debmess;

debmess info={.handled=0};

void addinfo(char* mess)
{
	info.info[times]=mess;
	times++;
}

LISTVIEW_Handle list;

void show(int time,char* message)
{
	char mess[64]="";
	sprintf(mess,"%s",message);
	char p[1];
	sprintf(p,"%d",time);
	char* info[2]={p,mess};
	LISTVIEW_AddRow(list,info);
	GUI_Delay(100);
}

static __IO u32 TimingDelay;
void SysTick_Init(void)
{
	/* SystemFrequency / 1000    1ms中断一次
	 * SystemFrequency / 100000	 10us中断一次
	 * SystemFrequency / 1000000 1us中断一次
	 */
	if (SysTick_Config(SystemCoreClock / 1000))
	{ 
		/* Capture error */ 
		while (1);
	}
}

/**
  * @brief   us延时程序,10us为一个单位
  * @param  
  *		@arg nTime: Delay_us( 1 ) 则实现的延时为 1 * 10us = 10us
  * @retval  无
  */
void Delay_us(__IO u32 nTime)
{ 
	TimingDelay = nTime;	

	while(TimingDelay != 0);
}

/**
  * @brief  获取节拍程序
  * @param  无
  * @retval 无
  * @attention  在 SysTick 中断函数 SysTick_Handler()调用
  */
void TimingDelay_Decrement(void)
{
	if (TimingDelay != 0x00)
	{ 
		TimingDelay--;
	}
}

void  AppTaskDesktop (void)
{
	GUI_SetColor(GUI_WHITE);
  GUI_SetFont(GUI_FONT_32B_ASCII);
  //GUI_DispStringHCenterAt("Starting...\nWait a moment",250,100);
  GUI_Delay(50);
	
	list=LISTVIEW_CreateEx(0,0,LCD_GetXSize(),LCD_GetYSize(),WM_HBKWIN,WM_CF_SHOW,0,1);
	LISTVIEW_AddColumn(list,60,"times",GUI_TA_LEFT|GUI_TA_VCENTER);
	LISTVIEW_AddColumn(list,LCD_GetXSize()-60,"message",GUI_TA_LEFT|GUI_TA_VCENTER);
	LISTVIEW_SetAutoScrollV(list,1);
	LISTVIEW_SetGridVis(list,1);
	LISTVIEW_SetRowHeight(list,0);
	GUI_Delay(100);
}

int main()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_CRC, ENABLE); 
	
	FSMC_SRAM_Init();
	
	USART_gpio(9600);
	
	GUI_Init();
	
	ILI9806G_Init();
	
	GTP_Init_Panel();
	
	SysTick_Init();

	AppTaskDesktop();
	
	USBD_Init(&USB_OTG_dev,
            USB_OTG_FS_CORE_ID,
            &USR_desc, 
						&USBD_CDC_cb, 
						&USR_cb);
	
	int i=0;
	
	while(1)
	{
		if(times>0)
		{
			
			int i;
			for(i=info.handled;i<times;i++)
			{
				if(i<200)
				{
					if(info.info[i]!=NULL)
					{
						show(i,info.info[i]);
						info.handled++;
					}
				}
			}
		}
		LISTVIEW_InsertRow(list,0,NULL);
		LISTVIEW_DeleteRow(list,0);
		GUI_Delay(50);
	}
}
