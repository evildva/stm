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
#include "./usart/bsp_debug_usart.h"

#include "GUIPicture_Port.h"   
#include "ff.h"

//����getData������ָ��
typedef struct
{
	FIL *file;
	uint8_t *_acBuffer;
}IN_DATA;


 /**
  * @brief  BMP/GIF/JPEG��ȡ�ⲿͼƬ�ļ����ݵĻص���������ΪGUI_xx_DrawEx�Ļص�����
  * @param  p: �ⲿ����ʱ�����ָ�룬һ��ʹ���ļ�ָ��.
  * @param  NumBytesReq:������ֽ�����
  * @param 	ppData��ָ�򵽻�ȡ�����ݵ�ָ�롣��GetData���������뽫ָ�����õ������������ڵ���Чλ�á�
  * @param  Off ������˱��Ϊ 1��Ӧ������ָ�����õ�����������ʼλ��
  * @retval ���ؿ��õ������ֽ���
  */
static int _GetData_BMP_GIF_JPEG(void * p, const U8 ** ppData, unsigned NumBytesReq, U32 Off) 
{

	int FileAddress = 0;
	UINT NumBytesRead;
	IN_DATA *in_data;
	FRESULT result;  

	
	in_data = (IN_DATA *)p;
	
	/*
	* ���Buffer��С
	*/
	if (NumBytesReq > PIC_BUFFRE_SIZE) {
	NumBytesReq = PIC_BUFFRE_SIZE;
	}

	/*
	* ����Off��������λ��
	*/
	if(Off == 1) 
		FileAddress = 0;
	else 
		FileAddress = Off;
	
	//���ļ����ж�λ
	result =f_lseek(in_data->file, FileAddress);
	if (result != FR_OK)
	{
		return 0;
	}

//printf("lseek:result->(%d) off->(%ld) address->(%d)\n",result,Off,FileAddress);
	/*
	* ��ȡ���ݵ�Buffer
	*/
	result = f_read(in_data->file, in_data->_acBuffer, NumBytesReq, &NumBytesRead);
//printf("read:result->(%d) numreq->(%d),numread->(%d)\n",result,NumBytesReq,NumBytesRead);
	/*
	* ����ָ��ָ�򻺳���
	*/
	*ppData = (const U8 *)in_data->_acBuffer;

	/*
	* ���ض�ȡ������Ч�ֽ���
	*/
	return NumBytesRead;
}


 /**
  * @brief  PNG/BITMAPS��ȡ�ⲿͼƬ�ļ����ݵĻص���������ΪGUI_xx_DrawEx�Ļص�����
  * @param  p: �ⲿ����ʱ�����ָ�룬һ��ʹ���ļ�ָ��.
  * @param  NumBytesReq:������ֽ�����
  * @param 	ppData����ȡ��������Ҫ����ָ�롣����ʹ�� ��GetData���������ָ��ָ���λ�á�
  * @param  Off ������˱��Ϊ 1��Ӧ������ָ�����õ�����������ʼλ��
  * @retval ���ؿ��õ������ֽ���
  */
static int _GetData_PNG_BITMAPS(void * p, const U8 **ppData, unsigned int NumBytesReq, U32 Off) {
	
	int FileAddress = 0;
	UINT    NumBytesRead;
	U8     * pData;
  FIL *p_file;
	FRESULT result;  

	p_file=(FIL *)p;
	pData  = (U8 *)*ppData;
	
	/*
	* ����Off��������λ��
	*/	
	if(Off == 1) 
		FileAddress = 0;
	else 
		FileAddress = Off;
	
	result =f_lseek(p_file, FileAddress);
	if (result != FR_OK)
	{
		return 0;
	}
//  printf("lseek:result->(%d) off->(%ld) address->(%d)\n",result,Off,FileAddress);
	/*
	* ��ȡ���ݵ�ָ���λ��
	*/
	result = f_read(p_file, pData, NumBytesReq, &NumBytesRead);
//  printf("read:result->(%d) numreq->(%d),numread->(%d)\n",result,NumBytesReq,NumBytesRead);
	/*
	* ���ض�ȡ������Ч�ֽ���
	*/
	return NumBytesRead;
}

 /**
  * @brief  ��ʾ�ļ�ϵͳ�е�BMPͼƬ
  * @param  sFilename: ͼƬ������·��
  * @param  usPOSX:ͼƬ����ʾλ��X
  * @param 	usPOSY��ͼƬ����ʾλ��Y
  * @retval ��
  */
void _ShowBMPEx(const char * sFilename, uint16_t usPOSX, uint16_t usPOSY) 
{	 
	FRESULT result;  

	IN_DATA in_data;
	
	GUI_HMEM hMem,hMem2;	
  
	//��emwin�ڴ��з���ռ�
	hMem = GUI_ALLOC_AllocZero(PIC_BUFFRE_SIZE);
	//�ѿռ���ת��ָ��
	in_data._acBuffer = GUI_ALLOC_h2p(hMem);
	
	//��emwin�ڴ��з���ռ�
	hMem2 = GUI_ALLOC_AllocZero(sizeof(FIL));

	//�ѿռ���ת��ָ��
	in_data.file = GUI_ALLOC_h2p(hMem2);
	
    /* ���ļ� */		
	result = f_open(in_data.file, sFilename, FA_OPEN_EXISTING | FA_READ | FA_OPEN_ALWAYS);
  
	if (result != FR_OK)
	{
		return;
	}

  printf("file open ok\n");
	
	GUI_BMP_DrawEx(_GetData_BMP_GIF_JPEG, &in_data, usPOSX, usPOSY);

	f_close(in_data.file);
	
	//�ͷ�����Ŀռ�
	GUI_ALLOC_Free(hMem);
		//�ͷ�����Ŀռ�
	GUI_ALLOC_Free(hMem2);

}

 /**
  * @brief  ��ʾ�ļ�ϵͳ�е�JPEGͼƬ
  * @param  sFilename: ͼƬ������·��
  * @param  usPOSX:ͼƬ����ʾλ��X
  * @param 	usPOSY��ͼƬ����ʾλ��Y
  * @retval ��
  */
void _ShowJPEGEx(const char * sFilename, uint16_t usPOSX, uint16_t usPOSY)  
{	 
	FRESULT result;  

	IN_DATA in_data;
	
	GUI_HMEM hMem,hMem2;	
  
	//��emwin�ڴ��з���ռ�
	hMem = GUI_ALLOC_AllocZero(PIC_BUFFRE_SIZE);
	//�ѿռ���ת��ָ��
	in_data._acBuffer = GUI_ALLOC_h2p(hMem);
	
	//��emwin�ڴ��з���ռ�
	hMem2 = GUI_ALLOC_AllocZero(sizeof(FIL));

	//�ѿռ���ת��ָ��
	in_data.file = GUI_ALLOC_h2p(hMem2);

	
	/* ���ļ� */		
	result = f_open(in_data.file, sFilename, FA_OPEN_EXISTING | FA_READ | FA_OPEN_ALWAYS);
	if (result != FR_OK)
	{
		printf("result = %d",result);
		return;
	}

  GUI_JPEG_DrawEx(_GetData_BMP_GIF_JPEG, &in_data, usPOSX, usPOSY);

	f_close(in_data.file);
	

	//�ͷ�����Ŀռ�
	GUI_ALLOC_Free(hMem);
		//�ͷ�����Ŀռ�
	GUI_ALLOC_Free(hMem2);

}


/**
  * @brief  ��ʾ�ڲ���GIFͼƬ
  * @param  sFilename: ͼƬ������·��
  * @param  usPOSX:ͼƬ����ʾλ��X
  * @param 	usPOSY��ͼƬ����ʾλ��Y
  * @param 	ctime��GIFͼƬѭ����ʾ���ٴΣ�
                   ������ctimeΪ0,��һֱѭ����ʾGIFͼƬ���������ڲ�����ѭ��
  * @retval ��
  */
void _ShowGIF(uint8_t * imgBuffer, uint32_t BufferSize,uint16_t usPOSX, uint16_t usPOSY,uint32_t ctime)  
{	   
 	GUI_GIF_INFO 				GIFInfo;
	GUI_GIF_IMAGE_INFO  GIF_ImageInfo;
	uint16_t		i=0;
	uint32_t   t0,t1;
	uint8_t 		forver =  0;
	
	//�������ctime == 0��GIFͼƬһֱѭ����ʾ
	if(ctime == 0) forver =1;	

	//��ȡGIFͼƬ��Ϣ
	GUI_GIF_GetInfo(imgBuffer,BufferSize,&GIFInfo);

	while(ctime-- || forver)
	{
		i=0;
		//ѭ����ʾ������ͼƬ
		while(i<GIFInfo.NumImages)
		{
			GUI_GIF_GetImageInfo(imgBuffer,BufferSize,&GIF_ImageInfo,i);
		
			//emwinҪ�󣬵�GIF_ImageInfo.Delay ==0 ʱ��Ҫ��ʱ100ms
			if(GIF_ImageInfo.Delay == 0)
				GUI_Delay(100);
			
			t0 = GUI_GetTime();
			GUI_GIF_DrawSub(imgBuffer,
													BufferSize, 
													usPOSX, 
													usPOSY,
													i++);
			//������뱾�����ĵ�ʱ��
			t1 = GUI_GetTime() - t0;
			
			//GIF_ImageInfo.Delay�ĵ�λΪ10ms�����Գ���10
			if(t1 < GIF_ImageInfo.Delay*10)
			{
				GUI_Delay(GIF_ImageInfo.Delay*10 - t1);
			}			
		}	
	}

}

 /**
  * @brief  ��ʾ�ļ�ϵͳ�е�GIFͼƬ
  * @param  sFilename: ͼƬ������·��
  * @param  usPOSX:ͼƬ����ʾλ��X
  * @param 	usPOSY��ͼƬ����ʾλ��Y
  * @param 	ctime��GIFͼƬѭ����ʾ���ٴΣ�
                   ������ctimeΪ0,��һֱѭ����ʾGIFͼƬ���������ڲ�����ѭ��
  * @retval ��
  */
void _ShowGIFEx(const char * sFilename, uint16_t usPOSX, uint16_t usPOSY,uint32_t ctime)  
{	  
	FRESULT result;  	
 	GUI_GIF_INFO 				GIFInfo;
	GUI_GIF_IMAGE_INFO  GIF_ImageInfo;
	uint16_t		i=0;
	uint32_t   t0,t1;
	uint8_t 		forver =  0;
		
	IN_DATA in_data;
	
	GUI_HMEM hMem,hMem2;	
  
	//��emwin�ڴ��з���ռ�
	hMem = GUI_ALLOC_AllocZero(PIC_BUFFRE_SIZE);
	//�ѿռ���ת��ָ��
	in_data._acBuffer = GUI_ALLOC_h2p(hMem);
	
	//��emwin�ڴ��з���ռ�
	hMem2 = GUI_ALLOC_AllocZero(sizeof(FIL));

	//�ѿռ���ת��ָ��
	in_data.file = GUI_ALLOC_h2p(hMem2);

	
	//�������ctime == 0��GIFͼƬһֱѭ����ʾ
	if(ctime == 0) forver =1;	

	/* ���ļ� */		
	result = f_open(in_data.file, sFilename, FA_OPEN_EXISTING | FA_READ | FA_OPEN_ALWAYS);
	if (result != FR_OK)
	{
		return;
	}
	

	//��ȡGIFͼƬ��Ϣ
	GUI_GIF_GetInfoEx(_GetData_BMP_GIF_JPEG,&in_data,&GIFInfo);

	while(ctime-- || forver)
	{
		i=0;
		//ѭ����ʾ������ͼƬ
		while(i<GIFInfo.NumImages)
		{
			GUI_GIF_GetImageInfoEx(_GetData_BMP_GIF_JPEG,&in_data,&GIF_ImageInfo,i);
		
			//emwinҪ�󣬵�GIF_ImageInfo.Delay ==0 ʱ��Ҫ��ʱ100ms
			if(GIF_ImageInfo.Delay == 0)
				GUI_Delay(100);
			
			t0 = GUI_GetTime();
			GUI_GIF_DrawSubEx(_GetData_BMP_GIF_JPEG,
													&in_data, 
													usPOSX, 
													usPOSY,
													i++);
			//������뱾�����ĵ�ʱ��
			t1 = GUI_GetTime()-t0;
			
			//GIF_ImageInfo.Delay�ĵ�λΪ10ms�����Գ���10
			if(t1 < GIF_ImageInfo.Delay*10)
			{
				GUI_Delay(GIF_ImageInfo.Delay*10-t1);
			}			
		}	
	}

	f_close(in_data.file);

	//�ͷ�����Ŀռ�
	GUI_ALLOC_Free(hMem);
		//�ͷ�����Ŀռ�
	GUI_ALLOC_Free(hMem2);

}

 /**
  * @brief  ��ʾ�ļ�ϵͳ�е�PNGͼƬ
  * @param  sFilename: ͼƬ������·��
  * @param  usPOSX:ͼƬ����ʾλ��X
  * @param 	usPOSY��ͼƬ����ʾλ��Y
  * @retval ��
  */
void _DrawPNG_file(const char * sFilename, uint16_t usPOSX, uint16_t usPOSY) 
{  
	FRESULT result;  

	FIL *file;
	
	GUI_HMEM hMem;	
  
	//��emwin�ڴ��з���ռ�
	hMem = GUI_ALLOC_AllocZero(sizeof(FIL));

	//�ѿռ���ת��ָ��
	file = GUI_ALLOC_h2p(hMem);

	
	
/* ���ļ� */		
	result = f_open(file, sFilename, FA_OPEN_EXISTING | FA_READ | FA_OPEN_ALWAYS);
//  printf("\nopen file (%s) result->(%d)\n",sFilename,result);
	if (result != FR_OK)
	{
		return;
	}  
	GUI_PNG_DrawEx(_GetData_PNG_BITMAPS, file, usPOSX, usPOSY); 
//  printf("png draw ok\n");
	f_close(file);		

	//�ͷ�����Ŀռ�
	GUI_ALLOC_Free(hMem);


}
/*********************************************END OF FILE**********************/
