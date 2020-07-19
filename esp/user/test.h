#ifndef  __TEST_H
#define	 __TEST_H



#include "stm32f4xx.h"
#include "esp8266.h"
#include <stdio.h>  
#include <string.h>  
#include <stdbool.h>
#include "common.h"


/********************************** �û���Ҫ���õĲ���**********************************/
#define      macUser_ESP8266_ApSsid                       "CUCC-web"                //Ҫ���ӵ��ȵ������
#define      macUser_ESP8266_ApPwd                        "964272296aaaa@"          //Ҫ���ӵ��ȵ����Կ

#define      macUser_ESP8266_TcpServer_IP                 "10.181.34.2"        //Ҫ���ӵķ������� IP
#define      macUser_ESP8266_TcpServer_Port               "8000"               //Ҫ���ӵķ������Ķ˿�



/********************************** �ⲿȫ�ֱ��� ***************************************/
extern volatile uint8_t ucTcpClosedFlag;



/********************************** ���Ժ������� ***************************************/
void  ESP8266_StaTcpClient_UnvarnishTest  ( void );



#endif

