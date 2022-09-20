#include<stc12c5a.h>
#include"nrf24l01receive.h"
#include"car.h"
#include "duoji.h"
#include <shengbo.h>
#include <zhuan.h>

//sbit bee = P2^3;
bit    flag = 0 ;
sbit yinxiang = P2^0;
#define uchar unsigned char 
#define uint unsigned int
unsigned long num,num2;

unsigned char RxDate[5] ;

void main()
{  uchar k;
   SPI_Init('L'); 
   NRF24L01Int();
   SPI_Init('H');
   NRFSetRXMode();//����Ϊ����ģʽ 
   TMOD=0x11;		   //��T0 T1Ϊ��ʽ1��GATE=1��  mode1 16λ�ڲ���ʱ��
	TH0=0;
	TL0=0;          
	TH1=0xf8;		   //2MS��ʱ
	TL1=0x30;
	ET0=1;             //����T0�ж�
	ET1=1;			   //����T1�ж�
	TR1=1;			   //������ʱ��
	EA=1;			   //�������ж�

	feng = 0;
   while(1)
   {
	   
	    GetDate();     //��ʼ��������	  	// RevTempDate[0]
		num2=(RevTempDate[1]);		//y��
		num = (RevTempDate[0]);		//num��������x
		car(num,num2);

	switch(RevTempDate[2] )		  //����
	{
	 	//��һ�м�ֵ��	 //1���� 0����		  //��*��
		case 0xee:	feng = 1;			break;	   //1*1
		case 0xde: m = 0; k = 1;		break;	   //1*2
		case 0xbe: 	k = 0;	break;	   //1*3
						  
		
		//�ڶ��м�ֵ��
		case 0xed: 	yinxiang = 1;  ;		break;	  //2*1
		case 0xdd:  		break;	  //2*2
		case 0xbd:   ;		break;	  //2*3


		//�����м�ֵ��
		case 0xeb: m = 1; douji1(130,2);		break;	   //3*1
		case 0xdb: m = 1;feng = 0; yinxiang = 0;douji1(130,3) ;		break;	   //3*2
		case 0xbb: m = 1;douji1(130,4) ;		break;	   //3*3
	}
	if (k==1) {chao ();move ();}	 
}	 
}
						                                                                                                                        
 /********************************************************/
     void zd0() interrupt 1 		 //T0�ж��������������,������෶Χ
  {
    flag=1;							 //�ж������־
  }
/********************************************************/
   void  zd3 () interrupt 3  		 //T1�ж�����ɨ������ܺͼ�800MS����ģ��
  {
	 if (m == 0)
	 {TH1=0xf8;
	 TL1=0x30;
	 zhongduan(); }
	
	 else 
	 {
	 TH1  = 0xfe;             //���¸�ֵ
	 TL1  = 0x30;
     if(count< jd)              //�ж�0.5ms�����Ƿ�С�ڽǶȱ�ʶ
       pwm0=1;                  //ȷʵС�ڣ�PWM����ߵ�ƽ
     else
       pwm0=0;                  //����������͵�ƽ
     count=(count+1);          //0.5ms������1
     count=count%40;     //����ʼ�ձ���Ϊ40 ����������Ϊ20ms
	 }

  } 
