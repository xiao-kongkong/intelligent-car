#include"stc12c5a.h"




/***************************************************************/
#define unchar unsigned char
#define unint  unsigned int

/**********************************************************************************/
//NRF24L01相关申明
/*******************************************************/
#define TX_ADDR_WITDH 5	//发送地址宽度设置为5个字节
#define RX_ADDR_WITDH 5	//接收地址宽度设置为5个字节
#define TX_DATA_WITDH 10//发送数据宽度1个字节
#define RX_DATA_WITDH 10//接收数据宽度1个字节
/*******************命令寄存器***************************/
#define  R_REGISTER      0x00//读取配置寄存器
#define  W_REGISTER      0x20//写配置寄存器
#define  R_RX_PAYLOAD 	 0x61//读取RX有效数据
#define  W_TX_PAYLOAD	 0xa0//写TX有效数据
#define  FLUSH_TX		 0xe1//清除TXFIFO寄存器
#define  FLUSH_RX		 0xe2//清除RXFIFO寄存器
#define  REUSE_TX_PL     0xe3//重新使用上一包有效数据
#define  NOP             0xff//空操作
/******************寄存器地址****************************/
#define  CONFIG          0x00//配置寄存器
#define  EN_AA			 0x01//使能自动应答
#define  EN_RXADDR       0x02//接收通道使能0-5个通道
#define  SETUP_AW        0x03//设置数据通道地址宽度3-5
#define  SETUP_RETR      0x04//建立自动重发
#define  RF_CH           0x05//射频通道设置
#define  RF_SETUP        0x06//射频寄存器
#define  STATUS          0x07//状态寄存器
#define  OBSERVE_TX      0x08//发送检测寄存器
#define  CD              0x09//载波
#define  RX_ADDR_P0      0x0a//数据通道0接收地址
#define  RX_ADDR_P1      0x0b//数据通道1接收地址
#define  RX_ADDR_P2      0x0c//数据通道2接收地址
#define  RX_ADDR_P3      0x0d//数据通道3接收地址
#define  RX_ADDR_P4      0x0e//数据通道4接收地址
#define  RX_ADDR_P5      0x0f//数据通道5接收地址
#define  TX_ADDR         0x10//发送地址
#define  RX_PW_P0        0x11//P0通道数据宽度设置
#define  RX_PW_P1        0x12//P1通道数据宽度设置
#define  RX_PW_P2        0x13//P2通道数据宽度设置
#define  RX_PW_P3        0x14//P3通道数据宽度设置
#define  RX_PW_P4        0x15//P4通道数据宽度设置
#define  RX_PW_P5        0x16//P5通道数据宽度设置
#define  FIFO_STATUS     0x17//FIFO状态寄存器

#define  len  32
/*******************相关函数声明**************************/
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


sbit CE  =P3^2;  //RX/TX模式选择端	 
sbit IRQ =P3^4;  //可屏蔽中断端		
sbit CSN =P3^3;  //SPI片选端//就是SS
sbit MOSI=P1^5;	 //SPI主机输出从机输入端
sbit MISO=P1^6;	 //SPI主机输出从机输出端
sbit SCLK=P1^7;	 //SPI时钟端


unchar code TxAddr[5]={0x34,0x43,0x10,0x10,0x01};//发送地址
/*****************状态标志*****************************************/


sbit RX_DR =sta^6;
sbit TX_DS =sta^5;
sbit MAX_RT=sta^4;



/*******************相关函数声明**************************;
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
/*****************SPI时序函数******************************************/
unchar NRFSPI(unchar dat) 
{
    CE=0;
	SPDAT=dat;
    while((SPSTAT&0x80)==0);
	SPSTAT=0x80;
	CE=1;
	return(SPDAT);
}
/**********************NRF24L01初始化函数*******************************/
void NRF24L01Int()
{
	NRFDelay(2);//让系统什么都不干
	CE=0;
	CSN=1;  
	SCLK=0;
	IRQ=1; 
}
/*****************SPI读寄存器一字节函数*********************************/
unchar NRFReadReg(unchar RegAddr)
{
   unchar BackDate;
   CSN=0;//启动时序
   NRFSPI(RegAddr);//写寄存器地址
   BackDate=NRFSPI(0x00);//写入读寄存器指令  
   CSN=1;
   return(BackDate); //返回状态
}
/*****************SPI写寄存器一字节函数*********************************/
unchar NRFWriteReg(unchar RegAddr,unchar date)
{
   unchar BackDate;
   CSN=0;//启动时序
   BackDate=NRFSPI(RegAddr);//写入地址
   NRFSPI(date);//写入值
   CSN=1;  
   return(BackDate);
}
/*****************SPI读取RXFIFO寄存器的值********************************/
unchar NRFReadRxDate(unchar RegAddr,unchar *RxDate,unchar DateLen)
{  //寄存器地址//读取数据存放变量//读取数据长度//用于接收
    unchar BackDate,i;
	CSN=0;//启动时序
	BackDate=NRFSPI(RegAddr);//写入要读取的寄存器地址
	for(i=0;i<DateLen;i++) //读取数据
	  {
	     RxDate[i]=NRFSPI(0);
	  } 
    CSN=1;
   return(BackDate); 
}
/*****************SPI写入TXFIFO寄存器的值**********************************/
unchar NRFWriteTxDate(unchar RegAddr,unchar *TxDate,unchar DateLen)
{ //寄存器地址//写入数据存放变量//读取数据长度//用于发送
   unchar BackDate,i;
   CSN=0;
   BackDate=NRFSPI(RegAddr);//写入要写入寄存器的地址
   for(i=0;i<DateLen;i++)//写入数据
     {
	    NRFSPI(*TxDate++);
	 }   
   CSN=1;
   return(BackDate);
}
/*****************NRF设置为接收模式并接收数据******************************/
//接收模式
void NRFSetRXMode()
{
    CE=0;
  	NRFWriteTxDate(W_REGISTER+RX_ADDR_P0,TxAddr,TX_ADDR_WITDH);  // 接收设备接收通道0使用和发送设备相同的发送地址
  	NRFWriteReg(W_REGISTER+EN_AA,0x01);               // 使能接收通道0自动应答
  	NRFWriteReg(W_REGISTER+EN_RXADDR,0x01);           // 使能接收通道0
  	NRFWriteReg(W_REGISTER+RF_CH,0x20);                 // 选择射频通道0x40
  	NRFWriteReg(W_REGISTER+RX_PW_P0,TX_DATA_WITDH);  // 接收通道0选择和发送通道相同有效数据宽度
  	NRFWriteReg(W_REGISTER+RF_SETUP,0x0f);            // 数据传输率2Mbps，发射功率0dBm，低噪声放大器增益
	  NRFWriteReg(W_REGISTER+CONFIG,0x0b);             // CRC使能，8位CRC校验，上电，接收模式       
}
/*************************接收数据*********************************************/
void GetDate()				 
{	

    CE = 1; 
 	  NRFDelay(5);  
    sta=NRFReadReg(R_REGISTER+STATUS);//发送数据后读取状态寄存器
     if(RX_DR)
     {
	   CE=0;//待机
	   NRFReadRxDate(R_RX_PAYLOAD,RevTempDate,RX_DATA_WITDH);// 从RXFIFO读取数据 接收4位即可，后一位位结束位
	   NRFWriteReg(W_REGISTER+STATUS,0xff); //接收到数据后RX_DR,TX_DS,MAX_PT都置高为1，通过写1来清楚中断标
	   CSN=0;
	   NRFSPI(FLUSH_RX);//用于清空FIFO ！！关键！！不然会出现意想不到的后果！！！大家记住！！ 
	   CSN=1;		 
     }	  
} 

void delay(unsigned int i)	  
{
	unsigned int m,n;
	for(m=i;m>0;m--)
		for(n=90;n>0;n--);
}							  //延时