/**
  ******************************************************************************
  * @file    usbh_usr.c
  * @author  MCD Application Team
  * @version V2.2.1
  * @date    17-March-2018
  * @brief   This file includes the usb host library user callbacks
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2015 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                      <http://www.st.com/SLA0044>
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------ */
#include <string.h>
#include "usbh_usr.h"
              /* FATFS */
#include "usbh_msc_core.h"
#include "usbh_msc_scsi.h"
#include "usbh_msc_bot.h"

/** @addtogroup USBH_USER
* @{
*/

/** @addtogroup USBH_MSC_DEMO_USER_CALLBACKS
* @{
*/

/** @defgroup USBH_USR 
* @brief    This file includes the usb host stack user callbacks
* @{
*/

/** @defgroup USBH_USR_Private_TypesDefinitions
* @{
*/
/**
* @}
*/


/** @defgroup USBH_USR_Private_Defines
* @{
*/
#define IMAGE_BUFFER_SIZE    512
/**
* @}
*/


/** @defgroup USBH_USR_Private_Macros
* @{
*/
extern USB_OTG_CORE_HANDLE USB_OTG_Core;
/**
* @}
*/


/** @defgroup USBH_USR_Private_Variables
* @{
*/
uint8_t USBH_USR_ApplicationState = USH_USR_FS_INIT;
uint8_t filenameString[15] = { 0 };

/* Points to the DEVICE_PROP structure of current device */
/* The purpose of this register is to speed up the execution */

USBH_Usr_cb_TypeDef USR_cb = {
  USBH_USR_Init,
  USBH_USR_DeInit,
  USBH_USR_DeviceAttached,
  USBH_USR_ResetDevice,
  USBH_USR_DeviceDisconnected,
  USBH_USR_OverCurrentDetected,
  USBH_USR_DeviceSpeedDetected,
  USBH_USR_Device_DescAvailable,
  USBH_USR_DeviceAddressAssigned,
  USBH_USR_Configuration_DescAvailable,
  USBH_USR_Manufacturer_String,
  USBH_USR_Product_String,
  USBH_USR_SerialNum_String,
  USBH_USR_EnumerationDone,
  USBH_USR_UserInput,
  USBH_USR_MSC_Application,
  USBH_USR_DeviceNotSupported,
  USBH_USR_UnrecoveredError
};

/**
* @}
*/

/** @defgroup USBH_USR_Private_Constants
* @{
*/
/*--------------- LCD Messages ---------------*/
uint8_t MSG_HOST_INIT[] = "> Host Library Initialized\n";
uint8_t MSG_DEV_ATTACHED[] = "> Device Attached \n";
uint8_t MSG_DEV_DISCONNECTED[] = "> Device Disconnected\n";
uint8_t MSG_DEV_ENUMERATED[] = "> Enumeration completed \n";
uint8_t MSG_DEV_HIGHSPEED[] = "> High speed device detected\n";
uint8_t MSG_DEV_FULLSPEED[] = "> Full speed device detected\n";
uint8_t MSG_DEV_LOWSPEED[] = "> Low speed device detected\n";
uint8_t MSG_DEV_ERROR[] = "> Device fault \n";

uint8_t MSG_MSC_CLASS[] = "> Mass storage device connected\n";
uint8_t MSG_HID_CLASS[] = "> HID device connected\n";
uint8_t MSG_DISK_SIZE[] = "> Size of the disk in MBytes: \n";
uint8_t MSG_LUN[] = "> LUN Available in the device:\n";
uint8_t MSG_ROOT_CONT[] = "> Exploring disk flash ...\n";
uint8_t MSG_WR_PROTECT[] = "> The disk is write protected\n";
uint8_t MSG_UNREC_ERROR[] = "> UNRECOVERED ERROR STATE\n";

/**
* @}
*/


/** @defgroup USBH_USR_Private_FunctionPrototypes
* @{
*/
static uint8_t Explore_Disk(char *path, uint8_t recu_level);
static uint8_t Image_Browser(char *path);
static void Show_Image(void);
static void Toggle_Leds(void);
/**
* @}
*/


/** @defgroup USBH_USR_Private_Functions
* @{
*/


/**
* @brief  USBH_USR_Init 
*         Displays the message on LCD for host lib initialization
* @param  None
* @retval None
*/
void USBH_USR_Init(void)
{
	printf("USBH_USR_Init \n");
}

/**
* @brief  USBH_USR_DeviceAttached 
*         Displays the message on LCD on device attached
* @param  None
* @retval None
*/
void USBH_USR_DeviceAttached(void)
{
  printf("USBH_USR_DeviceAttached \n");
}


/**
* @brief  USBH_USR_UnrecoveredError
* @param  None
* @retval None
*/
void USBH_USR_UnrecoveredError(void)
{
	printf("USBH_USR_UnrecoveredError \n");
}


/**
* @brief  USBH_DisconnectEvent
*         Device disconnect event
* @param  None
* @retval Status
*/
void USBH_USR_DeviceDisconnected(void)
{
	printf("USBH_USR_DeviceDisconnected \n");
}

/**
* @brief  USBH_USR_ResetUSBDevice 
* @param  None
* @retval None
*/
void USBH_USR_ResetDevice(void)
{
  /* callback for USB-Reset */
	printf("USBH_USR_ResetDevice \n");
}


/**
* @brief  USBH_USR_DeviceSpeedDetected 
*         Displays the message on LCD for device speed
* @param  Device speed
* @retval None
*/
void USBH_USR_DeviceSpeedDetected(uint8_t DeviceSpeed)
{
  printf("USBH_USR_DeviceDisconnected \n");
}

/**
* @brief  USBH_USR_Device_DescAvailable 
*         Displays the message on LCD for device descriptor
* @param  device descriptor
* @retval None
*/
void USBH_USR_Device_DescAvailable(void *DeviceDesc)
{
  printf("USBH_USR_Device_DescAvailable \n");
	printf("vid : %04xh\n",(uint32_t)(*(USBH_DevDesc_TypeDef*)DeviceDesc).idVendor);
	printf("vid : %04xh\n",(uint32_t)(*(USBH_DevDesc_TypeDef*)DeviceDesc).idProduct);
}

/**
* @brief  USBH_USR_DeviceAddressAssigned 
*         USB device is successfully assigned the Address 
* @param  None
* @retval None
*/
void USBH_USR_DeviceAddressAssigned(void)
{
	printf("USBH_USR_DeviceAddressAssigned \n");
}


/**
* @brief  USBH_USR_Conf_Desc 
*         Displays the message on LCD for configuration descriptor
* @param  Configuration descriptor
* @retval None
*/
void USBH_USR_Configuration_DescAvailable(USBH_CfgDesc_TypeDef * cfgDesc,
                                          USBH_InterfaceDesc_TypeDef * itfDesc,
                                          USBH_EpDesc_TypeDef * epDesc)
{
  printf("USBH_USR_Configuration_DescAvailable \n");
}

/**
* @brief  USBH_USR_Manufacturer_String 
*         Displays the message on LCD for Manufacturer String 
* @param  Manufacturer String 
* @retval None
*/
void USBH_USR_Manufacturer_String(void *ManufacturerString)
{
	printf("USBH_USR_Manufacturer_String : %s\n",ManufacturerString);
}

/**
* @brief  USBH_USR_Product_String 
*         Displays the message on LCD for Product String
* @param  Product String
* @retval None
*/
void USBH_USR_Product_String(void *ProductString)
{
  printf("USBH_USR_Product_String : %s\n",ProductString);
}

/**
* @brief  USBH_USR_SerialNum_String 
*         Displays the message on LCD for SerialNum_String 
* @param  SerialNum_String 
* @retval None
*/
void USBH_USR_SerialNum_String(void *SerialNumString)
{
  printf("USBH_USR_SerialNum_String : %s\n",SerialNumString);
}



/**
* @brief  EnumerationDone 
*         User response request is displayed to ask application jump to class
* @param  None
* @retval None
*/
void USBH_USR_EnumerationDone(void)
{
	printf("USBH_USR_EnumerationDon \n");
}


/**
* @brief  USBH_USR_DeviceNotSupported
*         Device is not supported
* @param  None
* @retval None
*/
void USBH_USR_DeviceNotSupported(void)
{
	printf("USBH_USR_DeviceNotSupported \n");
}


/**
* @brief  USBH_USR_UserInput
*         User Action for application state entry
* @param  None
* @retval USBH_USR_Status : User response for key button
*/
USBH_USR_Status USBH_USR_UserInput(void)
{
  printf("USBH_USR_UserInput \n");
	return USBH_USR_RESP_OK;
}

/**
* @brief  USBH_USR_OverCurrentDetected
*         Over Current Detected on VBUS
* @param  None
* @retval Status
*/
void USBH_USR_OverCurrentDetected(void)
{
  printf("USBH_USR_OverCurrentDetecte \n");
}


/**
* @brief  USBH_USR_MSC_Application 
*         Demo application for mass storage
* @param  None
* @retval Status
*/
int USBH_USR_MSC_Application(void)
{
  printf("USBH_USR_MSC_Application \n");
  return (0);
}

/**
* @brief  Explore_Disk 
*         Displays disk content
* @param  path: pointer to root path
* @retval None
*/
static uint8_t Explore_Disk(char *path, uint8_t recu_level)
{
  printf("USBH_USR_DeviceDisconnected \n");
  return 1;
}

static uint8_t Image_Browser(char *path)
{
  printf("USBH_USR_DeviceDisconnected \n");
  return 1;
}

/**
* @brief  Show_Image 
*         Displays BMP image
* @param  None
* @retval None
*/
static void Show_Image(void)
{
	printf("USBH_USR_DeviceDisconnected \n");
}

void delay(__IO uint32_t nCount)
{
  __IO uint32_t index = 0;
  for (index = (100000 * nCount); index != 0; index--)
  {
  }
}

/**
* @brief  Toggle_Leds
*         Toggle leds to shows user input state
* @param  None
* @retval None
*/
static void Toggle_Leds(void)
{
  
}

/**
* @brief  USBH_USR_DeInit
*         Deinit User state and associated variables
* @param  None
* @retval None
*/
void USBH_USR_DeInit(void)
{
  printf("USBH_USR_DeInit \n");
}


/**
* @}
*/

/**
* @}
*/

/**
* @}
*/

/**
* @}
*/

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
