#include<reg52.h>
#include "intrins.h"
#define uchar unsigned char
#define uint unsigned int
sbit lcden=P3^4;	//1602
sbit rs=P3^5;		//1602
sbit rw=P3^6;		//1602
uchar j,k;
uchar ch = 0;  
uchar t = 0;
uint PWM_T = 0;                       
uchar num,num1;

uchar a0,b0,c0;
	 //���
sbit en=P3^7;		 
sbit rig=P3^3;		 //���
sbit lif=P3^2;		 //���

/*�����Ĵ��� */
sfr ADC_CONTR   =   0xBC;           //ADC control register
sfr ADC_RES     =   0xBD;           //ADC hight 8-bit result register
sfr ADC_LOW2    =   0xBE;           //ADC low 2-bit result register
sfr P1ASF       =   0x9D;           //P1 secondary function control register
 
/*���� ADC_CONTR �Ĵ��� */
#define ADC_POWER   0x80            //ADC power control bit
#define ADC_FLAG    0x10            //ADC complete flag
#define ADC_START   0x08            //ADC start control bit
#define ADC_SPEEDLL 0x00            //420 clocks
#define ADC_SPEEDL  0x20            //280 clocks
#define ADC_SPEEDH  0x40            //140 clocks
#define ADC_SPEEDHH 0x60            //70 clocks
	
//uchar table1[]= num;
uchar table2[]="  Thank you  ";
void delay(uint x)
{
	uint a,b;
	for(a=x;a>0;a--)
		for(b=10;b>0;b--); 
}
void delay1(uchar i)
{
	for(j=i;j>0;j--)
	for(k=125;k>0;k--);
}

void write_com(uchar com)
{
	P0=com;
	rs=0;
	lcden=0;
	delay(10);
	lcden=1;
	delay(10);
	lcden=0;
	
}

void write_date(uchar date)
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
{
      rw=0;
	write_com(0x38);   //��ʾģʽ���ã�16��2��ʾ��5��7����8λ���ݽӿ�
	delay(20);
	write_com(0x0f);   //��ʾģʽ����
	delay(20);
	write_com(0x06);   //��ʾģʽ���ã�������ƣ��ַ�����
	delay(20);
	write_com(0x01);   //����Ļָ�����ǰ����ʾ�������
	delay(20);
	
	TMOD = 0x02;   //��ʱ��0������ģʽ2��8λ��ʱģʽ
	TH0=255;     //д��Ԥ�ó�ֵ��ȡֵ1-255����Խ��PWMƵ��Խ�ߣ�
	TL0=255;     //д��Ԥ��ֵ ��ȡֵ1-255����Խ��PWMƵ��Խ�ߣ�
	TR0=1;       //������ʱ��
	ET0=1;       //����ʱ��0�ж�
	EA=1;        //�������ж�

	 P1ASF = 0x01;   //	InitADC();            
    ADC_RES = 0;                
    ADC_CONTR = ADC_POWER | ADC_SPEEDLL | ADC_START | ch;
    delay1(2); 	 
	
}

void main()
{
	uchar a;
	lcdinit();
	IE = 0xa2;		//�ж��ܿ���



	while (1)
	{
	PWM_T=num1;
	   	lif=0;	 	rig=1;
		en=1;	
	if(num<10)
	{
		a0=num;b0=16;c0=16;
	}
	else
	{
		if(num<100)
		{a0=num/10;b0=num%10;c0=16;}
		else
		{
			if(num<1000)
			{a0=num/100;b0=num%100/10;c0=num%10;}
		}
	}

		write_com(0x80);	 //����һ���ַ�д������ƫ��17���ַ�����Ϊ�����������������׼����
		delay(20);
		write_date('s');
		write_date('p');
		write_date('e');
		write_date('e');
		write_date('d');
		write_date(61);
		write_date(a0+48);
		write_date(b0+48);
		write_date(c0+48);
		delay(20);		
		
	
		write_com(0xc0);
		delay(20);
		for(a=0;a<13;a++)
		{
		write_date(table2[a]);
		delay(20);		
		}
	}
	for(a=0;a<16;a++)
	{
		write_com(0x18); //����
		delay1(600);
	}  
	
} 
void adc_isr() interrupt 5 using 1
{
    ADC_CONTR &= !ADC_FLAG;        
	num=ADC_RES;
    
    //if (++ch > 0) 
	ch = 0;       //ֻѡ��  P1^0 ͨ�� 
    ADC_CONTR = ADC_POWER | ADC_SPEEDLL | ADC_START | ch;
}

timer0() interrupt 1  
{ 
    TH0=210;     //д��Ԥ�ó�ֵ��ȡֵ1-255����Խ��PWMƵ��Խ�ߣ�
	TL0=210;
	  
	 t++;    //ÿ�ζ�ʱ�������1
	 if(num<180)
	  {		
	  		rig=0;
			lif=1;
	         num1=num;
	 
			 if(t==180)   //PWM���� 100����λ
				   {
					  t=0;  //ʹt=0����ʼ�µ�PWM����
				 	}
		
			 if(t<PWM_T)  //���յ�ǰռ�ձ��л����Ϊ�ߵ�ƽ
				 {  
				 	en=0;        //  
		}		 }
			else
			en=1;  //�����?
	if(num>=180&&num<=200)  
	{ 
		en = 0;
		rig=0;
			lif=0;
	}
	if(num>200)
	{
		   
			lif=0;	 	rig=1;
			  num1=(num-200);
	 
			 if(t==55)   //PWM���� 100����λ
				 {
					  t=0;  //ʹt=0����ʼ�µ�PWM����
				 }
		
			 if(t<PWM_T)  //���յ�ǰռ�ձ��л����Ϊ�ߵ�ƽ
				 {  
				 	en=1;          
				 }
			else
			en=0;  //�����

	
	}
}