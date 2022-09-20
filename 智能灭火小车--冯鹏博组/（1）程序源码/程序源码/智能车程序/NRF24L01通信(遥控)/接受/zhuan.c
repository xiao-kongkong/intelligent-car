#include <stc12c5a.h>
#include <intrins.h>
#include <zhuan.h>
#include <shengbo.h>
#include"car.h" 

#define uchar unsigned char
#define uint unsigned int

	 unsigned int  time;
	 unsigned int  timer;
	 unsigned char posit;
	 unsigned int S1,S2,S3;
	 unsigned char o;
	 unsigned char n1,n2;
// 	 unsigned int num1;

extern void pwm (uchar x, uchar y)				  //越小越快  PCA模拟PWM
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
//	ET1=0;
	for (j = 0; j<i; j++)
		for (k = 0; k<120;k++);
//	ET1=1;
	
}
void youzhuan()
{  
	rig=0;
	lif=1;
	rig0=1;
	lif0=0;		  	
	delayms(1);
	
	pwm(60,66); 
	delayms(4200);
		

}
void zuozhuan()
{

	rig=1;
	lif=0;
	rig0=0;
	lif0=1;		  	
	delayms(1);
	pwm(50,56);
	delayms(3300);
}
void houzhuan()
{

	rig=1;
	lif=0;
	rig0=0;
	lif0=1;		  	
	delayms(1);
	pwm(50,56);
	delayms(6600);
}
void move ()
{
    rig=0;
	lif=1;
	rig0=0;
	lif0=1;		  	
	delayms(1);
	pwm(70,76);
//	delayms(1);				  	   
//	pwm(55,60);
//	if (S1<40) pwm(76,72);
//	if (S1<30) pwm(90,97);
	

} 
void you()
{
	rig=0;
	lif=1;
	rig0=1;
	lif0=0;		  	
	delayms(1);
	pwm(50,56);
	delayms(10);
}
void zuo()
{
	rig=1;
	lif=0;
	rig0=0;
	lif0=1;		  	
	delayms(1);
	pwm(50,56);
	delayms(10);
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
void xiaoqian()
{
	rig=0;
	lif=1;
	rig0=0;
	lif0=1;
	delayms(1);
	pwm(98,98);
	delayms(150);
}
void zuozuo()
{
	rig=1;
	lif=0;
	rig0=0;
	lif0=1;
	delayms(1);
	n1++;
	if(n1 >= 2) n1 = 2;
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
	n2++;
	if(n2 >= 2) n2 = 2;
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
	feng = 1;
	delayms(10000);
	feng = 0;
	delayms(2000);

	rig=1;
	lif=0;
	rig0=0;
	lif0=1;		  	
	delayms(1);	   //houzhuan
	pwm(50,56);
	delayms(6500);

	o=1;

}