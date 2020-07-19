#include "main.h"

#include  "usbd_hid_core.h"
#include  "usbd_usr.h"
#include  "usbd_desc.h"

__ALIGN_BEGIN USB_OTG_CORE_HANDLE     USB_OTG_dev __ALIGN_END;

int ready=0;
extern USBD_Class_cb_TypeDef  USBD_HID_cb;

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

int main()
{
	USART_gpio(9600);
	
	printf("usart init \n");
	
	USBD_Init(&USB_OTG_dev,
            USB_OTG_FS_CORE_ID,
            &USR_desc, 
						&USBD_HID_cb, 
						&USR_cb);

	printf("usb init \n");
	
	unsigned char *str="abcde";
	
	while(1)
	{
		if(ready==1)
		{
			USBD_CtlSendData(&USB_OTG_dev,str,sizeof(str));
		}
	  //printf("usart test \n");
		printf("usb test \n");
		//USART_SendString("usb \n\n");
	}
}
