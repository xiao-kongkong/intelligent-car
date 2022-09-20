#ifndef __1602ADC_H__
#define __1602ADC_H__

#define uchar unsigned char
#define uint unsigned int
sbit lcden=P3^4;	//1602
sbit rs=P3^5;		//1602
sbit rw=P3^6;		//1602
sbit zuodeng = P3^2;
sbit youdeng = P3^3;
sbit houdeng = P3^7;
extern uchar xnum,ynum,num0; 
extern uint PWM_T;                       
extern unsigned char a0,b0,c0;
void delay1(uint i);
void delay(uint x);
void write_com(unsigned char com);
void write_date(unsigned char date);
void lcdinit();
void shuzi ();
void xianshi ();
uchar KeyScan();
void deng ();

#endif