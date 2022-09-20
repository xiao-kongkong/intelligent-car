#include<stc12c5a.h>
#include<1602ADC.h>
#include<nrf.h>
#define uchar unsigned char
#define uint unsigned int


uchar TxDate[5] ;

//unsigned char *TxDate;

void main ()
{	 
	SPI_Init('H');
    NRF24L01Int();
    NRFSetTxMode();
    Ddelay(10);

	IE = 0xa0;		//中断总开关		
	lcdinit();
	while (1)
	{			
		shuzi ();
		xianshi ();
		deng ();
		delay1(20);

//	 *TxData=bnum;
	 NRF_Send(TxDate);

     while(CheckACK());	//检测是否发送
	}
}

void adc_isr() interrupt 5 using 1
{	uchar ch;
    
    ADC_CONTR &= !ADC_FLAG;                  
	  if (ch == 0)
	  {
	  *TxDate=ADC_RES;
	  xnum = *TxDate;
	  }
	  if(ch == 1)
	  {
	  	*(TxDate+1)=ADC_RES;
		ynum = *(TxDate+1);
	  }
	  if (++ch>1)
	  { 
	 	 ch = 0;
		*(TxDate+2) = KeyScan();
	  }
	ADC_CONTR = ADC_POWER | ADC_SPEEDLL | ADC_START | ch;
}
