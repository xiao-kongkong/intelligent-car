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
 	while(!RX1&&k--);		//当RX为零时等待
	 TR0=1;			    //开启计数
	 while(RX1&&l--);			//当RX为1计数并等待
	 TR0=0;	k=100000;l=100000;			//关闭计数
	 Conut(1);
	 while(!RX2&&k--);		//当RX为零时等待
	 TR0=1;			    //开启计数
	 while(RX2&&l--);			//当RX为1计数并等待
	 TR0=0;		k=100000;l=100000;			//关闭计数
	 Conut(2);

	 
	 while(!RX3&&k--);		//当RX为零时等待
	 TR0=1;			    //开启计数
	 while(RX3&&l--);			//当RX为1计数并等待
	 TR0=0;		k=30000;l=30000;				//关闭计数
	 Conut(3);				//计算
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
   	while(1)		    	//S3 右超声波	 S2左超声波
	{ 
	  cebo ();
	  move ();		  										//前进
//	  if (xun1 == 0||xun2 == 0 )  {houzhuan();	   }
//	  else
//	  {
		  if (S1<=23&&S2>30&&S3<30) {zuozhuan();}	  //2					//左右转
		  if (S1<23&&S2<30&&S3>30)	{youzhuan();}	  //3					//左右转
		  if (S1<23&&S2>20&&S3>20) 											//左右转
		  {	if (S2>S3)youzhuan();							   				//左右转
		  	if (S2<S3)zuozhuan();											//左右转
		  }
		  
		  if(S1>30&&S2>30&&S3<20)	zuo();									//小左右转
		  if(S1>30&&S2<20&&S3>30)	you();									//小左右转
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
