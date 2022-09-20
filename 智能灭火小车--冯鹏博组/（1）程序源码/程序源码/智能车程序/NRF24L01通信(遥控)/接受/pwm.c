#include <stc12c5a.h>
#include <pwm.h>

void pwm(unsigned char x,unsigned char y)
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