#include<stc12c5a.h>
#include"nrf24l01receive.h"
#include"pow.h"
#include"y452.h"
 sbit led=P1^0;
 static unsigned char bf;//����ȫ�ֱ�������λ�ñ���
 static unsigned char jp0;//����ȫ�ֱ�������ʱ�䵥λ����0.03s
 static unsigned char jp1;//����ȫ�ֱ������Ʋ���ʱ�伴����
 yinyue()
{//��ѭ��
    bf=0;//ȫ�ֱ�������λ�ñ�����ʼ
    jp0=0;//ȫ�ֱ�������ʱ�䵥λ����ʼ
    jp1=0;//ȫ�ֱ������Ʋ���ʱ�伴���ĳ�ʼ
    ds1();//���ö�ʱ��ʹ�ú�����ʼ����
//while(1);//����������Ҫͬʱִ�е���������
}
void main()
{  
	TMOD = 0x11;//�򿪶�ʱ��01������ģʽΪ1
    TR1=1;//��ʱ��0���ش�
    EA=1;//���жϴ�
    ET1=1;//��ʱ
   SPI_Init('L'); 
   NRF24L01Int();
   SPI_Init('H');
   NRFSetRXMode();
   
while(1);
}








void ds1_dl()interrupt 3
{
	TH1 = 0x00;
	TL1 = 0x00;	
		GetDate();
 	switch(RevTempDate[2] )		  //����
	{
	 	//��һ�м�ֵ��	 //1���� 0����		  //��*��
		case 0xee:	;			break;	   //1*1
		case 0xde:	;		break;	   //1*2
		case 0xbe:	;			break;	   //1*3
						  
		
		//�ڶ��м�ֵ��
		case 0xed:	pow() ;   	break;	  //2*1
		case 0xdd:  yinyue();	break;	  //2*2
		case 0xbd: ET0=0;fmq=0	;	break;	  //2*3	   stop()


		//�����м�ֵ��
		case 0xeb:   ;		break;	   //3*1
		case 0xdb:pows()	;		break;	   //3*2
		case 0xbb: 		break;	   //3*3
	}
}
						                 