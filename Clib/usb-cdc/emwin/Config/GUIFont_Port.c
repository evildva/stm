/**
  ******************************************************************************
  * @file    bsp_led.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   XBF��ʽ����emwin�����ӿ�
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ��  STM32 F407 ������  
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */

#include "./fatfs/drivers/fatfs_flash_spi.h"
#include "GUIFont_Port.h"   
#include "ff.h"

/*�ֿ�洢·��*/
#if (XBF_FONT_SOURCE == USE_FLASH_FONT)

	static const uint32_t  FONT_XINSONGTI_25_ADDR	 = (30*4096);
	static const uint32_t  FONT_XINSONGTI_19_ADDR	 = (680*4096);

#elif (XBF_FONT_SOURCE == USE_SDCARD_FONT)

	static const char  FONT_STORAGE_ROOT_DIR[] = "0:";
	static const char FONT_XINSONGTI_25_ADDR[] = 	 "0:srcdata/������25.xbf";
	static const char FONT_XINSONGTI_19_ADDR[] = 	 "0:srcdata/������19.xbf";

#elif (XBF_FONT_SOURCE == USE_FLASH_FILESYSTEM_FONT)
	
	static const char FONT_STORAGE_ROOT_DIR[] =  		"1:";
	static const char FONT_XINSONGTI_25_ADDR[] = 	 "1:������25.xbf";
	static const char FONT_XINSONGTI_19_ADDR[] = 	 "1:������19.xbf";

#endif


/*�ֿ�ṹ��*/
GUI_XBF_DATA 	XBF_XINSONGTI_25_Data;
GUI_FONT     	FONT_XINSONGTI_25;

GUI_XBF_DATA 	XBF_XINSONGTI_19_Data;
GUI_FONT     	FONT_XINSONGTI_19;

/*�洢����ʼ����־*/
static uint8_t storage_init_flag = 0;


/*�ֿ�洢���ļ�ϵͳʱ��Ҫʹ�õı���*/
#if (XBF_FONT_SOURCE == USE_SDCARD_FONT || XBF_FONT_SOURCE == USE_FLASH_FILESYSTEM_FONT)
	static FIL fnew;										/* file objects */
	static FATFS fs;										/* Work area (file system object) for logical drives */
	static FRESULT res; 
	static UINT br;            				/* File R/W count */
#endif

 /**
  * @brief  ��ȡ�������ݵĻص�����
  * @param  Offset��Ҫ��ȡ��������XBF�ļ��е�ƫ��λ��
  * @param  NumBytes��Ҫ��ȡ���ֽ���
	* @param  pVoid���Զ������ݵ�ָ��
  * @param  pBuffer���洢��ȡ���ݵ�ָ��
  * @retval 0 �ɹ�, 1 ʧ��
  */
static int _cb_FONT_XBF_GetData(U32 Offset, U16 NumBytes, void * pVoid, void * pBuffer)
{
#if (XBF_FONT_SOURCE == USE_FLASH_FONT)
	
	if (storage_init_flag == 0)
	{
		//��ʼ��flash
		TM_FATFS_FLASH_SPI_disk_initialize();
		storage_init_flag = 1;
	}
	
	//��pVoid�л�ȡ�ֿ�Ĵ洢��ַ(pvoid��ֵ��GUI_XBF_CreateFont�д���)
	SPI_FLASH_BufferRead(pBuffer,*(uint32_t *)pVoid+Offset,NumBytes);
	
	return 0;
	
#elif (XBF_FONT_SOURCE == USE_SDCARD_FONT || XBF_FONT_SOURCE == USE_FLASH_FILESYSTEM_FONT)

	if (storage_init_flag == 0)
	{
		//����sd���ļ�ϵͳ
		res = f_mount(&fs,FONT_STORAGE_ROOT_DIR,1);
		storage_init_flag = 1;
	}
	
	//��pVoid�л�ȡ�ֿ�Ĵ洢��ַ(pvoid��ֵ��GUI_XBF_CreateFont�д���)
	res = f_open(&fnew , (char *)pVoid, FA_OPEN_EXISTING | FA_READ);

	if ( res == FR_OK ) 
	{
			f_lseek (&fnew, Offset);		//ָ��ƫ��
		
			//��ȡ����
			res = f_read( &fnew, pBuffer, NumBytes, &br );		 
			
			f_close(&fnew);
			
			return 0;  
	}    
	else
			return 1; 

#endif

}




 /**
  * @brief  ����XBF����
  * @param  ��
  * @retval ��
  */
void Creat_XBF_Font(void) 
{	
	//
	// ������25
	//
	GUI_XBF_CreateFont(&FONT_XINSONGTI_25,    					// GUI_FONT ����ṹ��ָ��
					   &XBF_XINSONGTI_25_Data,         						// GUI_XBF_DATA �ṹ��ָ��
					   GUI_XBF_TYPE_PROP_EXT, 										// ��������
					   _cb_FONT_XBF_GetData,  							// ��ȡ�������ݵĻص�����
					   (void *)&FONT_XINSONGTI_25_ADDR);        	// Ҫ������ص��������Զ�������ָ�룬�˴������ֿ�ĵ�ַ
	//
	// ������19
	//
	GUI_XBF_CreateFont(&FONT_XINSONGTI_19,    				// GUI_FONT ����ṹ��ָ��
					 &XBF_XINSONGTI_19_Data,         						// GUI_XBF_DATA �ṹ��ָ��
					 GUI_XBF_TYPE_PROP_EXT, 										// ��������
					 _cb_FONT_XBF_GetData,  							// ��ȡ�������ݵĻص�����
					 (void *)&FONT_XINSONGTI_19_ADDR);        	// Ҫ������ص��������Զ�������ָ�룬�˴������ֿ�ĵ�ַ

}


 /**
  * @brief  GBKתUTF8
  * @param  src��������ַ�����GBK��ʽ��
  * @param  str��������ַ�����UTF8��ʽ��
  * @retval ��
  */
void COM_gbk2utf8(const char *src, char *str)
{
	uint32_t j=0,k=0;
	uint16_t gbkdata=0;
	uint16_t UCbuffer[512]={0};
	for(j=0,k=0;src[j]!='\0';k++)
	{
		if((uint8_t)src[j]>0x80)
		{
			gbkdata=src[j+1]+src[j]*256;
			UCbuffer[k]=ff_convert(gbkdata,1);
			j+=2;
		}
		else
		{
			UCbuffer[k]=0x00ff&src[j];
			j+=1;
		}
	}
	UCbuffer[k]='\0';
	GUI_UC_ConvertUC2UTF8(UCbuffer,2*k+2,str,k*3);
	str[k*3]=0;
}

/*********************************************END OF FILE**********************/
