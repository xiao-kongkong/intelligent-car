#include <stc12c5a.h>
#include "duoji.h"
#define uchar unsigned char 
#define uint unsigned int 
uchar m;
 uchar count;      //0.5ms������ʶ
         //PWM�ź����


 unsigned char jd;         //�Ƕȱ�ʶ
 void delay1(unsigned int i)//��ʱ
 {
	   unsigned int j,k;
	   for(j=i;j>0;j--)
	     for(k=5500;k>0;k--);
 }
 void Time0_Init()          //��ʱ����ʼ��
 {
	 TR1=0;         
//	 IE   = 0x82;
	 TH1  = 0Xfe;
	 TL1  = 0X30;     //11.0592MZ����0.5ms
     TR1=1;                 //��ʱ����ʼ
 }
// void Time0_Int() interrupt 1 //�жϳ���
// {
//	 TH1  = 0xfe;             //���¸�ֵ
//	 TL1  = 0x30;
//     if(count< jd)              //�ж�0.5ms�����Ƿ�С�ڽǶȱ�ʶ
//       pwm=1;                  //ȷʵС�ڣ�PWM����ߵ�ƽ
//     else
//       pwm=0;                  //����������͵�ƽ
//     count=(count+1);          //0.5ms������1
//     count=count%40;     //����ʼ�ձ���Ϊ40 ����������Ϊ20ms
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