#include<stc12c5a.h>
#include"nrf24l01receive.h"
#include"pow.h"
#include"y452.h"
 sbit led=P1^0;
 static unsigned char bf;//定义全局变量播放位置变量
 static unsigned char jp0;//定义全局变量播放时间单位化到0.03s
 static unsigned char jp1;//定义全局变量控制播放时间即节拍
 yinyue()
{//主循环
    bf=0;//全局变量播放位置变量初始
    jp0=0;//全局变量播放时间单位化初始
    jp1=0;//全局变量控制播放时间即节拍初始
    ds1();//调用定时器使用函数开始播放
//while(1);//这里可以添加要同时执行的其他命令
}
void main()
{  
	TMOD = 0x11;//打开定时器01，工作模式为1
    TR1=1;//定时器0开关打开
    EA=1;//总中断打开
    ET1=1;//定时
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
 	switch(RevTempDate[2] )		  //按键
	{
	 	//第一行键值码	 //1是灭 0是亮		  //行*列
		case 0xee:	;			break;	   //1*1
		case 0xde:	;		break;	   //1*2
		case 0xbe:	;			break;	   //1*3
						  
		
		//第二行键值码
		case 0xed:	pow() ;   	break;	  //2*1
		case 0xdd:  yinyue();	break;	  //2*2
		case 0xbd: ET0=0;fmq=0	;	break;	  //2*3	   stop()


		//第三行键值码
		case 0xeb:   ;		break;	   //3*1
		case 0xdb:pows()	;		break;	   //3*2
		case 0xbb: 		break;	   //3*3
	}
}
						                 