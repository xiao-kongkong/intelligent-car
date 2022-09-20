#ifndef __NRF_H__
#define __NRF_H__

#include<stc12c5a.h>
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
#define  len             32

extern unchar bdata sta;   //״̬��־
extern unchar TxAddr[];

sbit CE  =P1^2;  //RX/TXģʽѡ���
sbit IRQ =P1^4; //�������ж϶�
sbit CSN =P1^3; //SPIƬѡ��//����SS
sbit MOSI=P1^5;	//SPI��������ӻ������
sbit MISO=P1^6;	//SPI��������ӻ������
sbit SCLK=P1^7;	//SPIʱ�Ӷ�



unchar NRFACK();
unchar NRFSPI(unchar date);
unchar NRFReadReg(unchar RegAddr);
unchar NRFWriteReg(unchar RegAddr,unchar date);
unchar NRFReadRxDate(unchar RegAddr,unchar *RxDate,unchar DateLen);
unchar NRFWriteTxDate(unchar RegAddr,unchar *TxDate,unchar DateLen);
//unchar NRFWriteTxDate1(unchar RegAddr,unchar *TxData,unchar DateLen);
unchar NRFRevDate(unchar *RevDate);
void   NRFSetTxMode();
void   NRF24L01Int();
void   NRFSetRXMode();
void   Ddelay(unint t);
unchar CheckACK();
void SPI_Init(unsigned char chose);
void NRF_Send(unchar *TxDate);
//void NRF_Send1(unchar *TxData);
			 
#endif