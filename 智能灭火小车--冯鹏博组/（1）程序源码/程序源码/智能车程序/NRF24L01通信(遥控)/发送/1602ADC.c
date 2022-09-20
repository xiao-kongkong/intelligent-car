#include<stc12c5a.h>
#include<1602ADC.h>
#define uchar unsigned char
#define uint unsigned int

uchar xnum,ynum,num0; 
uint PWM_T;                       
unsigned char a0,b0,c0;

void delay(uint x)
{
	uint a,b;
	for(a=x;a>0;a--)
		for(b=10;b>0;b--); 
}
void delay1(uint i)
{	uint l,m;
	for(l=i;l>0;l--)
	for(m=125;m>0;m--);
}

void write_com(unsigned char com)
{
	P0=com;
	rs=0;
	lcden=0;
	delay(10);
	lcden=1;
	delay(10);
	lcden=0;
	
}

void write_date(unsigned char date)
{
	P0=date;
	rs=1;
	lcden=0;
	delay(10);
	lcden=1;
	delay(10);
	lcden=0;
	
}

void lcdinit()
{	uchar ch;				  
    rw=0;
	write_com(0x38);   //显示模式设置：16×2显示，5×7点阵，8位数据接口
	delay(20);
	write_com(0x0f);   //显示模式设置
	delay(20);
	write_com(0x06);   //显示模式设置：光标右移，字符不移
	delay(20);
	write_com(0x01);   //清屏幕指令，将以前的显示内容清除
	delay(20);

	P1ASF = 0x03;   //	InitADC();            
    ADC_RES = 0;                
    ADC_CONTR = ADC_POWER | ADC_SPEEDLL | ADC_START | ch;
    delay1(2); 	 
	
}

void shuzi ()
{
	num0 = ynum;
		if (ynum>145)	num0 = ynum-145;
		if (ynum>=110 && ynum<=145)	num0 = 0;
		if (ynum<110) num0 = 110-ynum;
		if(num0<10)
		{
			a0=num0;b0=16;c0=16;
		}
		else
		{
			if(num0<100)
			{a0=num0/10;b0=num0%10;c0=16;}
			else
			{
				if(num0<1000)
				{a0=num0/100;b0=num0%100/10;c0=num0%10;}
			}
		}
}

void xianshi ()
{	  	
		unsigned char table2[]="  Thank you  ";
		unsigned char a;
		write_com(0x80);	 //将第一个字符写在第一行第一个空
		delay(20);
		write_date('s');
		write_date('p');
		write_date('e');
		write_date('e');
		write_date('d');
		write_date(61);
		if (num0 >100)
		{
		 write_date(a0+48);
		 write_date(b0+48);
		 write_date(c0+48);
		 delay(200);
		 

		}
		else
		{write_date(31);
		 write_date(a0+48);
		 write_date(b0+48);
		 delay(200);
		}		
			
		write_com(0xc0);
		delay(20);
		for(a=0;a<13;a++)
		{
		write_date(table2[a]);
		delay(200);		
		}
}

uchar KeyScan()	//带返回值的子函数 //矩阵键盘
{
	uchar cord_l,cord_h;//声明列线和行线的值的储存变量
	P2 = 0x0f;//0000 1111
	if( (P2 & 0x0f) != 0x0f)//判断是否有按键按下
	{
		delay1(5);//软件消抖
		if( (P2 & 0x0f) != 0x0f)//判断是否有按键按下
		{
			  cord_h = P2 & 0x0f;// 储存行线值
			  P2 = cord_l | 0xf0;
			  cord_l = P2 & 0xf0;// 储存列线值
			  while( (P2 & 0xf0) != 0xf0 );//松手检测
			  return (cord_l + cord_h);//返回键值码
		}	
	}
	return (cord_l + cord_h);//返回键值码	
}

void deng ()
{
	if (ynum>190) houdeng = 0;
	else houdeng = 1;

	if (xnum < 50)  youdeng = 0;
	else if (xnum > 190) zuodeng = 0;
		else {zuodeng = 1; youdeng = 1;}	
}