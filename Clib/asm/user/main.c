#include "main.h"

extern int addnum(int a,int b);
extern void runapp(int addr);
extern int* SOFTWAREVERSION;

char version[]="1.1.0";

int multiple(int a,int b)
{
	return a*b;
}

int ma=3,mb=4;

int main()
{
	USART_Config();
	
	FLASH_Unlock();
	FLASH_EraseSector(FLASH_Sector_11,VoltageRange_4);
	FLASH_ProgramWord(0x080E0000,0x12345678);
	FLASH_Lock();
	
	int result=0;
	
	result=addnum(1,2);
	
	printf("asm result is %d\n",result);
	printf("current version address is %d\n",*(int*)0x080E0000);
	
	while(1);
}
