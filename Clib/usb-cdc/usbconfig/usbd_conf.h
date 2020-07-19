/**
  ******************************************************************************
  * @file    usbd_conf.h
  * @author  MCD Application Team
  * @version V1.2.1
  * @date    17-March-2018
  * @brief   USB Device configuration file
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USBD_CONF__H__
#define __USBD_CONF__H__

/* Includes ------------------------------------------------------------------*/
#include "usb_conf.h"

/** @defgroup USB_CONF_Exported_Defines
  * @{
  */ 


#define USBD_CFG_MAX_NUM           1
#define USBD_ITF_MAX_NUM           1

#define USB_MAX_STR_DESC_SIZ       64 

#define USBD_SELF_POWERED               

#define USBD_DYNAMIC_DESCRIPTOR_CHANGE_ENABLED 

/** @defgroup USB_String_Descriptors
  * @{
  */ 


/** @defgroup USB_HID_Class_Layer_Parameter
  * @{
  */ 
#define CDC_IN_EP                    0x81
#define CDC_IN_PACKET                4

/**
  * @}
  */ 
/** @defgroup USB_CONF_Exported_Types
  * @{
  */ 
/**
  * @}
  */ 


/** @defgroup USB_CONF_Exported_Macros
  * @{
  */ 
#define CDC_OUT_EP                    0x01
#define CDC_OUT_PACKET                4

#define APP_RX_DATA_SIZE 							64
#define CDC_CMD_PACKET_SIZE 					64
#define CDC_DATA_MAX_PACKET_SIZE 			64
#define CDC_CMD_EP										0x80
#define CDC_IN_FRAME_INTERVAL					64

/**
  * @}
  */ 

/** @defgroup USB_CONF_Exported_Variables
  * @{
  */ 
/**
  * @}
  */ 

/** @defgroup USB_CONF_Exported_FunctionsPrototype
  * @{
  */ 
/**
  * @}
  */ 


#endif /* __USBD_CONF__H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

