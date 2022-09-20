#include <stc12c5a.h>
#include "duoji.h"
#define uchar unsigned char 
#define uint unsigned int 
uchar m;
 uchar count;      //0.5ms次数标识
         //PWM信号输出


 unsigned char jd;         //角度标识
 void delay1(unsigned int i)//延时
 {
	   unsigned int j,k;
	   for(j=i;j>0;j--)
	     for(k=5500;k>0;k--);
 }
 void Time0_Init()          //定时器初始化
 {
	 TR1=0;         
//	 IE   = 0x82;
	 TH1  = 0Xfe;
	 TL1  = 0X30;     //11.0592MZ晶振，0.5ms
     TR1=1;                 //定时器开始
 }
// void Time0_Int() interrupt 1 //中断程序
// {
//	 TH1  = 0xfe;             //重新赋值
//	 TL1  = 0x30;
//     if(count< jd)              //判断0.5ms次数是否小于角度标识
//       pwm=1;                  //确实小于，PWM输出高电平
//     else
//       pwm=0;                  //大于则输出低电平
//     count=(count+1);          //0.5ms次数加1
//     count=count%40;     //次数始终保持为40 即保持周期为20ms
// }

 void douji1(uint x,uchar m)
 {
	 Time0_Init(); 

		 jd=m; count=0;
		 delay1(x);	

 }
  void douji2(uint x,uchar m)
 {
	 Time0_Init(); 

		 jd=m; count=0;
		 delay1(x);	

 }