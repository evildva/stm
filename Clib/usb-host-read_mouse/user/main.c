#include "main.h"
#include "usb_conf.h"
#include "usb_bsp.h"
#include "usb_hcd_int.h"
#include "usbh_core.h"

#include "usbh_msc_scsi.h"
#include "usbh_msc_bot.h"
#include "usbh_msc_core.h"

#include "usbh_usr.h"

USB_OTG_CORE_HANDLE   USB_OTG_Core;
USBH_HOST             USB_Host;
extern USBH_Class_cb_TypeDef  HID_cb;

int main()
{

	USART_Config();
	USBH_Init(&USB_OTG_Core,USB_OTG_FS_CORE_ID,
            &USB_Host,
            &HID_cb,
            &USR_cb);
	
	while(1)
	{
		USBH_Process(&USB_OTG_Core, &USB_Host);
	  //printf("usart test \n");
	}
}
