#include<stc12c5a.h>
#include"nrf24l01receive.h"
#include"car.h"
#include "duoji.h"

sbit bee = P2^3;
sbit yinxiang = P2^0;
#define uchar unsigned char 
#define uint unsigned int
unsigned long num,num2;

unsigned char RxDate[5] ;

void main()
{
   SPI_Init('L'); 
   NRF24L01Int();
   SPI_Init('H');
   NRFSetRXMode();//����Ϊ����ģʽ 
   while(1)
   {
	   
	    GetDate();     //��ʼ��������	  	// RevTempDate[0]
		num2=(RevTempDate[1]);		//y��
		num = (RevTempDate[0]);		//num��������x
		car(num,num2);
//	
//		GetDate();     //��ʼ��������	  	// RevTempDate[0]
//	num2=(RevTempDate[1]);		 //1
//	num = (RevTempDate[0]);		//num��������		 //0
//	car(num,num2);
//    chao()  ;
	switch(RevTempDate[2] )		  //����
	{
	 	//��һ�м�ֵ��	 //1���� 0����		  //��*��
		case 0xee:	bee = 1;			break;	   //1*1
		case 0xde:  		break;	   //1*2
		case 0xbe: 		break;	   //1*3
						  
		
		//�ڶ��м�ֵ��
		case 0xed: 	yinxiang = 1;  ;		break;	  //2*1
		case 0xdd:   ;		break;	  //2*2
		case 0xbd:   ;		break;	  //2*3


		//�����м�ֵ��
		case 0xeb:  douji1(130,2);		break;	   //3*1
		case 0xdb: bee = 0; yinxiang = 0;douji1(130,3) ;		break;	   //3*2
		case 0xbb: douji1(130,4) ;		break;	   //3*3
	} 	 
}	
}
						                                                                                                                        

