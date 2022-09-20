#include <stc12c5a.h>
#include "duoji.h"
#define uchar unsigned char 
#define uint unsigned int 
 uchar count;      //0.5ms������ʶ
 sbit pwm =P0^1 ;          //PWM�ź����
 sbit jia =P3^0;           //�Ƕ����Ӱ������IO��
 sbit jan =P3^1;           //�Ƕȼ��ٰ������IO��

 unsigned char jd;         //�Ƕȱ�ʶ
 void delay(unsigned int i)//��ʱ
 {
	   unsigned int j,k;
	   for(j=i;j>0;j--)
	     for(k=5500;k>0;k--);
 }
 void Time0_Init()          //��ʱ����ʼ��
 {
	 TMOD = 0x01;           //��ʱ��0�����ڷ�ʽ1   
	 IE   = 0x82;
	 TH0  = 0Xfe;
	 TL0  = 0X30;     //11.0592MZ����0.5ms
     TR0=1;                 //��ʱ����ʼ
 }
 void Time0_Int() interrupt 1 //�жϳ���
 {
	 TH0  = 0xfe;             //���¸�ֵ
	 TL0  = 0x30;
     if(count< jd)              //�ж�0.5ms�����Ƿ�С�ڽǶȱ�ʶ
       pwm=1;                  //ȷʵС�ڣ�PWM����ߵ�ƽ
     else
       pwm=0;                  //����������͵�ƽ
     count=(count+1);          //0.5ms������1
     count=count%40;     //����ʼ�ձ���Ϊ40 ����������Ϊ20ms
 }

 void douji(uint x,uchar m,uchar n)
 {
	 Time0_Init(); 

		 jd=m; count=0;
		 delay(x);
		 jd=n;	count=0;
		 delay(x); 
	
 }