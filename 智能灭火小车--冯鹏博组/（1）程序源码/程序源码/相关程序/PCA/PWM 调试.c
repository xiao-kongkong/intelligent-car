#include<stc12c5a.h>

#define uchar unsigned char
#define uint unsigned int
sbit rig = P0^1;
sbit lif = P0^2;
sbit rig0 = P0^3;
sbit lif0 = P0^4;
unsigned long num1;

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

void delayms (uint i)
{	uint j,k;
	for (j = 0; j<i; j++)
		for (k = 0; k<120;k++);
	
}

void main ()
{	 while(1)
	  {
//			rig=0;
//			lif=1;
//			rig0=1;
//			lif0=0;		  	
//			delayms(1);
//			pwm(56,50);
//			delayms(3200);		   //右转75度
//
//	  		rig=1;
//			lif=1;
//			rig0=1;
//			lif0=1;		  	
//			delayms(1);
//			pwm(56,50);
//			delayms(6000);
//
//			rig=1;
//			lif=0;
//			rig0=0;
//			lif0=1;		  	
//			delayms(1);
//			pwm(56,50);
//			delayms(3200);		   //左转75度

	  		rig=1;
			lif=0;
			rig0=0;
			lif0=1;		  	
			delayms(1);
			pwm(42,40);
			delayms(4120);
			
			rig=1;
			lif=1;
			rig0=1;
			lif0=1;		  	
			delayms(1);
			pwm(56,50);
			delayms(6000);
		
		
	   }
}
