#include<stc12c5a.h>  
#include"car.h" 
#include <pwm.h>
#define uchar unsigned char
#define uint  unsigned int
unsigned long num1;

	 //����


void car(unsigned long x,unsigned long y)
{	
	uchar xin;
	
	if ((x>90&&x<150)&&(y>100&&y<140))  // ͣ
		{ 
				pwm(255,255);
			rig=1;
			lif=1;
			rig0=1;
			lif0=1;
		}
		
		else  if (x<90 && (y>80&&y<160))  // ��
				{
				       if(x>20)
					   {
						   	pwm(20,20);
							rig=0;
							lif=1;
							rig0=1;
							lif0=1;
						}
						else
						{  	pwm(35,35);
							rig=0;
							lif=1;
							rig0=1;
							lif0=0;
						}	
				}
		      else  if(x>150 && (y>80&&y<160)) // ��
			  		{
						if(x<230)
						{
						    pwm(20,20);
							rig=1;
							lif=1;
							rig0=0;
							lif0=1;
						}
						else
						{
							pwm(35,35);
							rig=1;
							lif=0;
							rig0=0;
							lif0=1;
						}
		
					}
			     else  if(y<100)              //ǰ
				 		{	

							if(y<6)
							{
						    	rig=0;
								lif=1;
								rig0=0;
								lif0=1;
							   	pwm(0,15);			//you,zuo
							}
							else
							{
								rig=0;
								lif=1;
								rig0=0;
								lif0=1;
							    num1=y;		
								xin=num1+5;
				 				pwm(xin,xin);
							}
								 
						}
					   else                     // ��
					   {	if(y>250)
					   		{
								rig=1;
								lif=0;
								rig0=1;
								lif0=0;
								rig=1;
								pwm(0,0);	
							}
							else
							{
							    rig=1;
								lif=0;
								rig0=1;
								lif0=0;
								rig=1;
					 
								num1=145-(y-145);
						 	   	xin=num1+5;
				 				pwm(xin,xin);
							}
						} 
}