#include"stc12c5a.h"




/***************************************************************/
#define unchar unsigned char
#define unint  unsigned int

/**********************************************************************************/
//NRF24L01�������
/*******************************************************/
#define TX_ADDR_WITDH 5	//���͵�ַ�������Ϊ5���ֽ�
#define RX_ADDR_WITDH 5	//���յ�ַ�������Ϊ5���ֽ�
#define TX_DATA_WITDH 10//�������ݿ��1���ֽ�
#define RX_DATA_WITDH 10//�������ݿ��1���ֽ�
/*******************����Ĵ���***************************/
#define  R_REGISTER      0x00//��ȡ���üĴ���
#define  W_REGISTER      0x20//д���üĴ���
#define  R_RX_PAYLOAD 	 0x61//��ȡRX��Ч����
#define  W_TX_PAYLOAD	 0xa0//дTX��Ч����
#define  FLUSH_TX		 0xe1//���TXFIFO�Ĵ���
#define  FLUSH_RX		 0xe2//���RXFIFO�Ĵ���
#define  REUSE_TX_PL     0xe3//����ʹ����һ����Ч����
#define  NOP             0xff//�ղ���
/******************�Ĵ�����ַ****************************/
#define  CONFIG          0x00//���üĴ���
#define  EN_AA			 0x01//ʹ���Զ�Ӧ��
#define  EN_RXADDR       0x02//����ͨ��ʹ��0-5��ͨ��
#define  SETUP_AW        0x03//��������ͨ����ַ���3-5
#define  SETUP_RETR      0x04//�����Զ��ط�
#define  RF_CH           0x05//��Ƶͨ������
#define  RF_SETUP        0x06//��Ƶ�Ĵ���
#define  STATUS          0x07//״̬�Ĵ���
#define  OBSERVE_TX      0x08//���ͼ��Ĵ���
#define  CD              0x09//�ز�
#define  RX_ADDR_P0      0x0a//����ͨ��0���յ�ַ
#define  RX_ADDR_P1      0x0b//����ͨ��1���յ�ַ
#define  RX_ADDR_P2      0x0c//����ͨ��2���յ�ַ
#define  RX_ADDR_P3      0x0d//����ͨ��3���յ�ַ
#define  RX_ADDR_P4      0x0e//����ͨ��4���յ�ַ
#define  RX_ADDR_P5      0x0f//����ͨ��5���յ�ַ
#define  TX_ADDR         0x10//���͵�ַ
#define  RX_PW_P0        0x11//P0ͨ�����ݿ������
#define  RX_PW_P1        0x12//P1ͨ�����ݿ������
#define  RX_PW_P2        0x13//P2ͨ�����ݿ������
#define  RX_PW_P3        0x14//P3ͨ�����ݿ������
#define  RX_PW_P4        0x15//P4ͨ�����ݿ������
#define  RX_PW_P5        0x16//P5ͨ�����ݿ������
#define  FIFO_STATUS     0x17//FIFO״̬�Ĵ���

#define  len  32
/*******************��غ�������**************************/
unchar NRFACK();
unchar NRFSPI(unchar date);
unchar NRFReadReg(unchar RegAddr);
unchar NRFWriteReg(unchar RegAddr,unchar date);
unchar NRFReadRxDate(unchar RegAddr,unchar *RxDate,unchar DateLen);
unchar NRFWriteTxDate(unchar RegAddr,unchar *TxDate,unchar DateLen);
void NRFSetTxMode(unchar *TxDate);
void NRF24L01Int();
void NRFSetRXMode();
//void CheckACK();
void GetDate();
unchar bdata sta;
unchar RevTempDate[33];


sbit CE  =P3^2;  //RX/TXģʽѡ���	 
sbit IRQ =P3^4;  //�������ж϶�		
sbit CSN =P3^3;  //SPIƬѡ��//����SS
sbit MOSI=P1^5;	 //SPI��������ӻ������
sbit MISO=P1^6;	 //SPI��������ӻ������
sbit SCLK=P1^7;	 //SPIʱ�Ӷ�


unchar code TxAddr[5]={0x34,0x43,0x10,0x10,0x01};//���͵�ַ
/*****************״̬��־*****************************************/


sbit RX_DR =sta^6;
sbit TX_DS =sta^5;
sbit MAX_RT=sta^4;



/*******************��غ�������**************************;
/*************************/


void NRFDelay(unchar t)
{
   unchar y;
   while(t--)
    for(y=110;y>0;y--);
}
/**********************************/
void SPI_Init(unsigned char chose)
{
   switch(chose)
	{
 	  case 'H':SPCTL=0xd0;break;
 	  case 'L':SPCTL=0xd1;break;
	}
}
/*****************SPIʱ����******************************************/
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
	NRFDelay(2);//��ϵͳʲô������
	CE=0;
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
/*****************SPI��ȡRXFIFO�Ĵ�����ֵ********************************/
unchar NRFReadRxDate(unchar RegAddr,unchar *RxDate,unchar DateLen)
{  //�Ĵ�����ַ//��ȡ���ݴ�ű���//��ȡ���ݳ���//���ڽ���
    unchar BackDate,i;
	CSN=0;//����ʱ��
	BackDate=NRFSPI(RegAddr);//д��Ҫ��ȡ�ļĴ�����ַ
	for(i=0;i<DateLen;i++) //��ȡ����
	  {
	     RxDate[i]=NRFSPI(0);
	  } 
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
/*****************NRF����Ϊ����ģʽ����������******************************/
//����ģʽ
void NRFSetRXMode()
{
    CE=0;
  	NRFWriteTxDate(W_REGISTER+RX_ADDR_P0,TxAddr,TX_ADDR_WITDH);  // �����豸����ͨ��0ʹ�úͷ����豸��ͬ�ķ��͵�ַ
  	NRFWriteReg(W_REGISTER+EN_AA,0x01);               // ʹ�ܽ���ͨ��0�Զ�Ӧ��
  	NRFWriteReg(W_REGISTER+EN_RXADDR,0x01);           // ʹ�ܽ���ͨ��0
  	NRFWriteReg(W_REGISTER+RF_CH,0x20);                 // ѡ����Ƶͨ��0x40
  	NRFWriteReg(W_REGISTER+RX_PW_P0,TX_DATA_WITDH);  // ����ͨ��0ѡ��ͷ���ͨ����ͬ��Ч���ݿ��
  	NRFWriteReg(W_REGISTER+RF_SETUP,0x0f);            // ���ݴ�����2Mbps�����书��0dBm���������Ŵ�������
	  NRFWriteReg(W_REGISTER+CONFIG,0x0b);             // CRCʹ�ܣ�8λCRCУ�飬�ϵ磬����ģʽ       
}
/*************************��������*********************************************/
void GetDate()				 
{	

    CE = 1; 
 	  NRFDelay(5);  
    sta=NRFReadReg(R_REGISTER+STATUS);//�������ݺ��ȡ״̬�Ĵ���
     if(RX_DR)
     {
	   CE=0;//����
	   NRFReadRxDate(R_RX_PAYLOAD,RevTempDate,RX_DATA_WITDH);// ��RXFIFO��ȡ���� ����4λ���ɣ���һλλ����λ
	   NRFWriteReg(W_REGISTER+STATUS,0xff); //���յ����ݺ�RX_DR,TX_DS,MAX_PT���ø�Ϊ1��ͨ��д1������жϱ�
	   CSN=0;
	   NRFSPI(FLUSH_RX);//�������FIFO �����ؼ�������Ȼ��������벻���ĺ����������Ҽ�ס���� 
	   CSN=1;		 
     }	  
} 

void delay(unsigned int i)	  
{
	unsigned int m,n;
	for(m=i;m>0;m--)
		for(n=90;n>0;n--);
}							  //��ʱ