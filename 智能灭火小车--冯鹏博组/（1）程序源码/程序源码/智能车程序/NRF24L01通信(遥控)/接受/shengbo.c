#include <stc12c5a.h>
#include <shengbo.h>
#include <intrins.h>
#include <zhuan.h>
//#include"nrf24l01receive.h"
#define uchar unsigned char
#define uint unsigned int
 void Conut(uchar i)
	{
	 if (i == 1)
	 {
	 time=TH0*256+TL0;
	 TH0=0;
	 TL0=0;
	 S1=(time*1.7)/100;}
	 if (i == 2)
	 {
	 time=TH0*256+TL0;
	 TH0=0;
	 TL0=0;
	 S2=(time*1.7)/100;}
	 if (i == 3)
	 {
	 time=TH0*256+TL0;
	 TH0=0;
	 TL0=0;
	 S3=(time*1.7)/100;}     
	}

	void txbo (uchar i)
 {	
 	  if (i == 1)
 	  {TX1=1;			               
	  _nop_();_nop_(); _nop_(); _nop_();
	  _nop_();_nop_(); _nop_(); _nop_();
	  _nop_();_nop_(); _nop_(); _nop_();
	  _nop_();_nop_(); _nop_(); _nop_();
	  _nop_();_nop_(); _nop_();_nop_();_nop_();
	  TX1=0;
	  }
	  if (i == 2)
 	  {TX2=1;			                
	  _nop_();_nop_(); _nop_(); _nop_();
	  _nop_();_nop_(); _nop_(); _nop_();
	  _nop_();_nop_(); _nop_(); _nop_();
	  _nop_();_nop_(); _nop_(); _nop_();
	  _nop_();_nop_(); _nop_();_nop_();_nop_();
	  TX2=0;
	  }
	  if (i == 3)
 	  {TX3=1;			               
	  _nop_();_nop_(); _nop_(); _nop_();
	  _nop_();_nop_(); _nop_(); _nop_();
	  _nop_();_nop_(); _nop_(); _nop_();
	  _nop_();_nop_(); _nop_(); _nop_();
	  _nop_();_nop_(); _nop_();_nop_();_nop_();
	  TX3=0;
	  }
 } 

 void cebo ()
 {	unsigned long k=100000,l=100000;
 	while(!RX1&&k--);		//��RXΪ��ʱ�ȴ�
	 TR0=1;			    //��������
	 while(RX1&&l--);			//��RXΪ1�������ȴ�
	 TR0=0;	k=100000;l=100000;			//�رռ���
	 Conut(1);
	 while(!RX2&&k--);		//��RXΪ��ʱ�ȴ�
	 TR0=1;			    //��������
	 while(RX2&&l--);			//��RXΪ1�������ȴ�
	 TR0=0;		k=100000;l=100000;			//�رռ���
	 Conut(2);

	 
	 while(!RX3&&k--);		//��RXΪ��ʱ�ȴ�
	 TR0=1;			    //��������
	 while(RX3&&l--);			//��RXΪ1�������ȴ�
	 TR0=0;		k=30000;l=30000;				//�رռ���
	 Conut(3);				//����
 } 

 void zhongduan()
 {		  
 		 timer++; 
		 if(timer>=16)
		 { 
		  timer=0;
		  
		   
		 }
	 if(timer == 5)
	 {
	 	txbo (1);
	 }
	 if(timer == 10)
	 {
	 	txbo (2);
	 }
	 if(timer == 15)
	 {
	 	txbo (3);
	 }
	
 }

 void chao ()
 {	uchar k;
   	while(1)		    	//S3 �ҳ�����	 S2������
	{ 
	  cebo ();
	  move ();		  										//ǰ��
//	  if (xun1 == 0||xun2 == 0 )  {houzhuan();	   }
//	  else
//	  {
		  if (S1<=23&&S2>30&&S3<30) {zuozhuan();}	  //2					//����ת
		  if (S1<23&&S2<30&&S3>30)	{youzhuan();}	  //3					//����ת
		  if (S1<23&&S2>20&&S3>20) 											//����ת
		  {	if (S2>S3)youzhuan();							   				//����ת
		  	if (S2<S3)zuozhuan();											//����ת
		  }
		  
		  if(S1>30&&S2>30&&S3<20)	zuo();									//С����ת
		  if(S1>30&&S2<20&&S3>30)	you();									//С����ת
//	  } 
	  	 k++; 
		 if(flame1==0||flame2==0||flame3==0)
		 {	o = 0;
			 while (!o){	if (flame1==0&&flame2==0&&flame3==0)	   ting();
					  if (flame1==0&&flame3==0)	   				ting();
					  if(flame1==1&&flame2==0&&flame3==1)	   qian();
					  if(flame1==0&&flame2==1&&flame3==1)	  zuozuo();
					  if(flame1==1&&flame2==1&&flame3==0)	  youyou();
					  if(n1 == 2&&n2 == 2){	xiaoqian();	n1=0;n2=0;		}
			 		   }
		}
	  if (k == 5){k=0; move ();break;}


    }
 }
