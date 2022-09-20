#include"nrf.h"
#include<stc12c5a.h>
#define unchar unsigned char
#define unint unsigned int
unchar bdata sta;
sbit RX_DR=sta^6;
sbit TX_DS=sta^5;
sbit MAX_RT=sta^4;
unchar TxAddr[]={0x34,0x43,0x10,0x10,0x01};//���͵�ַ

void Ddelay(unint t)
{
  unint y;
  while(t--)
   for(y=200;y>0;y--);
}

void SPI_Init(unsigned char chose)
{
   switch(chose)
	{
 	  case 'H':SPCTL=0xd0;break;
 	  case 'L':SPCTL=0xd1;break;
	}
}

unchar NRFSPI(unchar dat) 
{
    CE=0;
	SPDAT=dat;
    while((SPSTAT&0x80)==0);
	SPSTAT=0x80;
	CE=1;
	return(SPDAT);
}

/**********************NRF24L01��ʼ������*******************************/
void NRF24L01Int()
{
	Ddelay(2);//��ϵͳʲô������
	CE=0; //����ģʽ1   
	CSN=1;  
	SCLK=0;
	IRQ=1;	 
}

/*****************SPI���Ĵ���һ�ֽں���*********************************/
unchar NRFReadReg(unchar RegAddr)
{
   unchar BackDate;
   CSN=0;//����ʱ��
   NRFSPI(RegAddr);//д�Ĵ�����ַ
   BackDate=NRFSPI(0x00);//д����Ĵ���ָ��  
   CSN=1;
   return(BackDate); //����״̬
}
/*****************SPIд�Ĵ���һ�ֽں���*********************************/
unchar NRFWriteReg(unchar RegAddr,unchar date)
{
   unchar BackDate;
   CSN=0;//����ʱ��
   BackDate=NRFSPI(RegAddr);//д���ַ
   NRFSPI(date);//д��ֵ
   CSN=1;
   return(BackDate);
}
/*****************SPIд��TXFIFO�Ĵ�����ֵ**********************************/
unchar NRFWriteTxDate(unchar RegAddr,unchar *TxDate,unchar DateLen)
{ //�Ĵ�����ַ//д�����ݴ�ű���//��ȡ���ݳ���//���ڷ���
   unchar BackDate,i;
   CSN=0;
   BackDate=NRFSPI(RegAddr);//д��Ҫд��Ĵ����ĵ�ַ
   for(i=0;i<DateLen;i++)//д������
     {
	    NRFSPI(*TxDate++);
	 }   
   CSN=1;
   return(BackDate);
}

//unchar NRFWriteTxDate1(unchar RegAddr,unchar *TxData,unchar DateLen)
//{ //�Ĵ�����ַ//д�����ݴ�ű���//��ȡ���ݳ���//���ڷ���
//   unchar BackDate,i;
//   CSN=0;
//   BackDate=NRFSPI(RegAddr);//д��Ҫд��Ĵ����ĵ�ַ
//   for(i=0;i<DateLen;i++)//д������
//     {
//	    NRFSPI(*TxData++);
//	 }   
//   CSN=1;
//   return(BackDate);
//   }

/*****************NRF����Ϊ����ģʽ����������******************************/
void NRFSetTxMode()
{		//����ģʽ
    CE=0; 
   	NRFWriteTxDate(W_REGISTER+TX_ADDR,TxAddr,TX_ADDR_WITDH);//д�Ĵ���ָ��+���յ�ַʹ��ָ��+���յ�ַ+��ַ���
	NRFWriteTxDate(W_REGISTER+RX_ADDR_P0,TxAddr,TX_ADDR_WITDH);//Ϊ��Ӧ������豸������ͨ��0��ַ�ͷ��͵�ַ��ͬ 

	NRFWriteReg(W_REGISTER+RF_CH,0x20);       // ѡ����Ƶͨ��0x40
  	NRFWriteReg(W_REGISTER+RF_SETUP,0x0f);    // ���ݴ�����1Mbps�����书��0dBm���������Ŵ�������
		//******�����йؼĴ�������**************

  	NRFWriteReg(W_REGISTER+EN_AA,0x01);       // ʹ�ܽ���ͨ��0�Զ�Ӧ��
  	NRFWriteReg(W_REGISTER+EN_RXADDR,0x01);   // ʹ�ܽ���ͨ��0
}
/*******************************************/
void NRF_Send(unchar *TxDate)
{
   	NRFWriteTxDate(W_TX_PAYLOAD,TxDate,TX_DATA_WITDH);//д������
  	NRFWriteReg(W_REGISTER+SETUP_RETR,0x0a);  // �Զ��ط���ʱ�ȴ�250us+86us���Զ��ط�10��
  	
        NRFWriteReg(W_REGISTER+CONFIG,0x0a);      // CRCʹ�ܣ�8λCRCУ�飬�ϵ�  
        CE=1;
}
//void NRF_Send1(unchar *TxData)
//{
//   	NRFWriteTxDate1(W_TX_PAYLOAD,TxData,TX_DATA_WITDH);//д������
//  	NRFWriteReg(W_REGISTER+SETUP_RETR,0x0a);  // �Զ��ط���ʱ�ȴ�250us+86us���Զ��ط�10��
//  	
//        NRFWriteReg(W_REGISTER+CONFIG,0x0a);      // CRCʹ�ܣ�8λCRCУ�飬�ϵ�  
//        CE=1;
//}
/****************************���Ӧ���ź�******************************/
unchar CheckACK()
{  //���ڷ���
	sta=NRFReadReg(R_REGISTER+STATUS);                    // ����״̬�Ĵ���
	if(TX_DS||MAX_RT) //��������ж�
	{
	   NRFWriteReg(W_REGISTER+STATUS,0xff);  // ���TX_DS��MAX_RT�жϱ�־
	   CSN=0;
	   NRFSPI(FLUSH_TX);//�������FIFO �����ؼ�������Ȼ��������벻���ĺ����������Ҽ�ס����  
       CSN=1; 
	   return(0);
	}
	else
	   return(1);
}