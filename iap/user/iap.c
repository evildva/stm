#include "iap.h"
#include "usart.h"

static unsigned char bootloaderversion=0x22;
static unsigned char cmd_count=11;
static unsigned char cmd[11]={0x00,0x01,0x02,0x11,0x21,0x31,0x43,0x63,0x73,0x82,0x92};

void jump_to_app(u32 appaddr)  //��ת����
{
	  iapfun jump2app; 
	
		if(((*(vu32*)appaddr)&0x2FFE0000)==0x20000000)
		{ 
			__set_PRIMASK(1);
			__set_MSP(*(vu32*)appaddr);
			jump2app=(iapfun)*(vu32*)(appaddr+4);
			jump2app(); 
		}
}

unsigned char checksum(unsigned char *data, int len) //����p��ʼlen���ֽڵ�checksum��Ҳ���Ǽ������
{
    int i;
    unsigned char cs;
    cs = 0;
    for ( i=0; i<len; i++ )
        cs ^= data[i];
    return cs;
}

void Getcommand(void) //AN2606 page10
{ 
	unsigned char i;
		
	sengdata(cmd_count);
	sengdata(bootloaderversion);
		
	for(i=0;i<cmd_count;i++){
		sengdata(cmd[i]);
	}
	sengdata(ACK);
}

void GetVersion(void)  //AN2606 page12
{
	  sengdata(bootloaderversion);
	  sengdata(0x01);
	  sengdata(0x01);
	  sengdata(ACK);
}

void GetID(void)  //AN2606 page14
{
	  sengdata(0x01);
	  sengdata(0x04);
	  sengdata(0x10);
		sengdata(ACK);
}
unsigned int addr=0,temp1;
unsigned int* flashdata;
void ReadMemorycommand(void)  //AN2606 page16
{

	unsigned char temp[4],recchecksum,len,tempsum=0,i;
	
	temp[0]= waitdata();
	temp[1]= waitdata();
	temp[2]= waitdata();
	temp[3]= waitdata();
	
    addr=(temp[0]<<24)|(temp[1]<<16)|(temp[2]<<8)|temp[3];
		recchecksum = waitdata();
    if(recchecksum==checksum(temp,4)&&(addr>=0x08000000)||(addr<0x08010000)){
		sengdata(ACK);
	}else{
		sengdata(NACK);
		return;
	}
	len=waitdata();
	recchecksum=waitdata();
	tempsum=~len;
	if(recchecksum==tempsum){
			sengdata(ACK);
	}else{
			sengdata(NACK);
			return;
	}
	for(i=0;i<len+1;i++){
			flashdata=(unsigned int*)(addr+i);
		    temp1=*flashdata;
			sengdata(*flashdata);
	}
}
void Gocommand(void)  //AN2606 page18
{
		unsigned int addr;
		unsigned char temp[4],recchecksum;
	
		temp[0]= waitdata();
		temp[1]= waitdata();
		temp[2]= waitdata();
		temp[3]= waitdata();
	
	  addr=(temp[0]<<24)|(temp[1]<<16)|(temp[2]<<8)|temp[3];
		recchecksum = waitdata();
	  if(recchecksum==checksum(temp,4)&&(addr>=0x08000000)&&(addr<0x08010000)){
			sengdata(ACK);
		}else{
			sengdata(NACK);
			return;
		}
		//���������־
		FLASH_Unlock(); //���� 
		FLASH_ProgramWord(updata_flagaddr,0x00);
		FLASH_Lock();	  //����
		FLASH_WaitForLastOperation();//�ȴ���������
	  jump_to_app(addr);
}

void WriteMemorycommand(void) //AN2606 page20
{
	  unsigned int Status;
	  unsigned int addr,recdata_32bit,i;
		unsigned char temp[4],recchecksum=0,len,recdata[0xFF];
	
		temp[0]= waitdata();
		temp[1]= waitdata();
		temp[2]= waitdata();
		temp[3]= waitdata();
	
	  addr=(temp[0]<<24)|(temp[1]<<16)|(temp[2]<<8)|temp[3];
		recchecksum = waitdata();
	  if(recchecksum==checksum(temp,4)&&(addr>=0x08000000)&&(addr<0x08010000)){
			sengdata(ACK);
		}else{
			sengdata(NACK);
			return;
		}
		len=waitdata();
		for(i=0;i<len+1;i++){
				recdata[i]=waitdata();
		}
		recchecksum=waitdata();
		if(recchecksum==(len^checksum(recdata,len+1))){
			//дflash
			FLASH_Unlock();    //����
			for(i=0;i<len+1-3;i+=4){
				recdata_32bit=recdata[i+0]|(recdata[i+1]<<8)|(recdata[i+2]<<16)|(recdata[i+3]<<24);
				FLASH_ProgramWord(addr,recdata_32bit);   
				addr+=4;
			}
			FLASH_Lock();	//����
			Status=FLASH_WaitForLastOperation();//�ȴ���д����
			if(Status==FLASH_COMPLETE){
			//д��ɹ�
			}
			sengdata(ACK);
		}else{
			sengdata(NACK);
			return;
		}
}
void Erasecommand(void) //AN2606 page24
{
	  unsigned int Status;
		unsigned char pagecount,erasepagearry[50],recchecksum,i,tm;
	
		pagecount=waitdata();
	  for(i=0;i<pagecount+1;i++){
				erasepagearry[i]=waitdata();
		}
		recchecksum=waitdata();
		tm=checksum(erasepagearry,pagecount+1)^pagecount;
	  if(recchecksum==tm){
			//����ҳ
			FLASH_Unlock(); //����
			for(i=0;i<pagecount+1;i++){
					FLASH_ErasePage(0x08000000+erasepagearry[i]*1024);  
					FLASH_EraseSector(,VoltageRange_4);				
			}
			FLASH_Lock();	  //����
			Status=FLASH_WaitForLastOperation();//�ȴ���������
		
			if(Status==FLASH_COMPLETE){
				//�����ɹ�
			}
			sengdata(ACK);
		}else{
			sengdata(NACK);
			return;
		}
}
//�����ĸ���ʱû�õ���������û��ʵ��
void WriteProtectcommand(void)
{
}
void WriteUnprotectcommand(void)
{
}
void ReadoutProtectcommand(void)
{
}
void ReadoutUnprotectcommand(void)
{
}

/*
Byte 4: 0x00 �C Get command
Byte 5: 0x01 �C Get Version and Read Protection Status
Byte 6: 0x02 �C Get ID
Byte 7: 0x11 �C Read Memory command
Byte 8: 0x21 �C Go command
Byte 9: 0x31 �C Write Memory command
Byte 10: 0x43 �C Erase command
Byte 11: 0x63 �C Write Protect command
Byte 12: 0x73 �C Write Unprotect command
Byte 13: 0x82 �C Readout Protect command
Byte 14: 0x92 �C Readout Unprotect command
*/
//������Ӧ�����ĺ�����ַ���浽�������棬�������������λִ���������Ӧ�ĺ���
const CommandHandleStruct CmdHdlStr[11]={
    {0x00,Getcommand},
    {0x01,GetVersion},
    {0x02,GetID},
    {0x11,ReadMemorycommand},
    {0x21,Gocommand},
    {0x31,WriteMemorycommand},
    {0x43,Erasecommand},
    {0x63,WriteProtectcommand},
    {0x73,WriteUnprotectcommand},
    {0x82,ReadoutProtectcommand},
    {0x92,ReadoutUnprotectcommand} ,
};
