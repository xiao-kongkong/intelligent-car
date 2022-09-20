#include <stc12c5a.h>
#define uchar unsigned char
#define uint unsigned int
sbit rig = P0^1;
sbit lif = P0^2;
sbit rig0 = P0^3;
sbit lif0 = P0^4;
sbit flame1 = P3^5;  //火焰感应	zuo
sbit flame2 = P3^6;	 // 		zhong
sbit flame3 = P3^7;	 //			you
sbit bee = P2^3;


void delayms (uint i)
{	uint j,k;
	for (j = 0; j<i; j++)
		for (k = 0; k<120;k++);
	
}
void pwm (uchar x, uchar y)				  //越小越快  PCA模拟PWM
{
	CCON = 0;                       //Initial PCA control register
                                   
                                   
    CL = 0;                         //Reset PCA base timer
    CH = 0;
    CMOD = 0x02;                    //Set PCA timer clock source as Fosc/2
                                    //Disable PCA timer overflow interrupt
    CCAP0H = CCAP0L = x;         //PWM0 port output 50% duty cycle square wave
    CCAPM0 = 0x42;                  //PCA module-0 work in 8-bit PWM mode and no PCA interrupt

    CCAP1H = CCAP1L = y;         //PWM1 port output 0% duty cycle square wave
//    PCA_PWM1 = 0x03;
    CCAPM1 = 0x42;                  //PCA module-1 work in 8-bit PWM mode and no PCA interrupt

    CR = 1;                         //PCA timer start run
}

void qian()
{
	rig=0;
	lif=1;
	rig0=0;
	lif0=1;
	delayms(1);
	pwm(98,98);
}
void zuozuo()
{
	rig=1;
	lif=0;
	rig0=0;
	lif0=1;
	delayms(1);
	pwm(75,75);
	if(flame1==1) pwm (87,87);
}
void youyou()
{
	rig=0;
	lif=1;
	rig0=1;
	lif0=0;
	delayms(1);
	pwm(75,75);
	if(flame3==1) pwm (87,87);
}
void ting()
{
	rig=1;		  
	lif=1;
	rig0=1;
	lif0=1;		  //ting
	delayms(5000);
	rig=1;
	lif=0;
	rig0=1;		 
	lif0=0;
	delayms(1);	 //houtui
	pwm(98,98);
	delayms(4500);
   	rig=1;
	lif=0;
	rig0=0;
	lif0=1;		  	
	delayms(1);	   //houzhuan
	pwm(50,56);
	delayms(7050);

	rig=1;		   //ting
	lif=1;
	rig0=1;
	lif0=1;
	bee = 1;
	delayms(10000);
	bee = 0;

}


void main ()
{  	
	bee = 0;
	while (1)
	{
	  if (flame1==0&&flame2==0&&flame3==0)	   ting();
	  if (flame1==0&&flame3==0)	   				ting();
	  if(flame1==1&&flame2==0&&flame3==1)	   qian();
	  if(flame1==0&&flame2==1&&flame3==1)	  zuozuo();
	  if(flame1==1&&flame2==1&&flame3==0)	  youyou();

//	  ting();
	}
}
