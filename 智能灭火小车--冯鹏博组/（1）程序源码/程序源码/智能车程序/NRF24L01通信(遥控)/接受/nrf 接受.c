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
   NRFSetRXMode();//设置为接收模式 
   TMOD=0x11;		   //设T0 T1为方式1，GATE=1；  mode1 16位内部计时器
	TH0=0;
	TL0=0;          
	TH1=0xf8;		   //2MS定时
	TL1=0x30;
	ET0=1;             //允许T0中断
	ET1=1;			   //允许T1中断
	TR1=1;			   //开启定时器
	EA=1;			   //开启总中断

	feng = 0;
   while(1)
   {
	   
	    GetDate();     //开始接受数据	  	// RevTempDate[0]
		num2=(RevTempDate[1]);		//y轴
		num = (RevTempDate[0]);		//num控制左右x
		car(num,num2);

	switch(RevTempDate[2] )		  //按键
	{
	 	//第一行键值码	 //1是灭 0是亮		  //行*列
		case 0xee:	feng = 1;			break;	   //1*1
		case 0xde: m = 0; k = 1;		break;	   //1*2
		case 0xbe: 	k = 0;	break;	   //1*3
						  
		
		//第二行键值码
		case 0xed: 	yinxiang = 1;  ;		break;	  //2*1
		case 0xdd:  		break;	  //2*2
		case 0xbd:   ;		break;	  //2*3


		//第三行键值码
		case 0xeb: m = 1; douji1(130,2);		break;	   //3*1
		case 0xdb: m = 1;feng = 0; yinxiang = 0;douji1(130,3) ;		break;	   //3*2
		case 0xbb: m = 1;douji1(130,4) ;		break;	   //3*3
	}
	if (k==1) {chao ();move ();}	 
}	 
}
						                                                                                                                        
 /********************************************************/
     void zd0() interrupt 1 		 //T0中断用来计数器溢出,超过测距范围
  {
    flag=1;							 //中断溢出标志
  }
/********************************************************/
   void  zd3 () interrupt 3  		 //T1中断用来扫描数码管和计800MS启动模块
  {
	 if (m == 0)
	 {TH1=0xf8;
	 TL1=0x30;
	 zhongduan(); }
	
	 else 
	 {
	 TH1  = 0xfe;             //重新赋值
	 TL1  = 0x30;
     if(count< jd)              //判断0.5ms次数是否小于角度标识
       pwm0=1;                  //确实小于，PWM输出高电平
     else
       pwm0=0;                  //大于则输出低电平
     count=(count+1);          //0.5ms次数加1
     count=count%40;     //次数始终保持为40 即保持周期为20ms
	 }

  } 
