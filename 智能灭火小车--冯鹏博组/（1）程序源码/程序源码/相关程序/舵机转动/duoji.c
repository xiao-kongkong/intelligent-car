#include <stc12c5a.h>
#include "duoji.h"
#define uchar unsigned char 
#define uint unsigned int 
 uchar count;      //0.5ms次数标识
 sbit pwm =P0^1 ;          //PWM信号输出
 sbit jia =P3^0;           //角度增加按键检测IO口
 sbit jan =P3^1;           //角度减少按键检测IO口

 unsigned char jd;         //角度标识
 void delay(unsigned int i)//延时
 {
	   unsigned int j,k;
	   for(j=i;j>0;j--)
	     for(k=5500;k>0;k--);
 }
 void Time0_Init()          //定时器初始化
 {
	 TMOD = 0x01;           //定时器0工作在方式1   
	 IE   = 0x82;
	 TH0  = 0Xfe;
	 TL0  = 0X30;     //11.0592MZ晶振，0.5ms
     TR0=1;                 //定时器开始
 }
 void Time0_Int() interrupt 1 //中断程序
 {
	 TH0  = 0xfe;             //重新赋值
	 TL0  = 0x30;
     if(count< jd)              //判断0.5ms次数是否小于角度标识
       pwm=1;                  //确实小于，PWM输出高电平
     else
       pwm=0;                  //大于则输出低电平
     count=(count+1);          //0.5ms次数加1
     count=count%40;     //次数始终保持为40 即保持周期为20ms
 }

 void douji(uint x,uchar m,uchar n)
 {
	 Time0_Init(); 

		 jd=m; count=0;
		 delay(x);
		 jd=n;	count=0;
		 delay(x); 
	
 }