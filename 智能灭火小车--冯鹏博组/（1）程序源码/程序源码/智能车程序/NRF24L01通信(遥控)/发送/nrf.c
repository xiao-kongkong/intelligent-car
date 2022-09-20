#include"nrf.h"
#include<stc12c5a.h>
#define unchar unsigned char
#define unint unsigned int
unchar bdata sta;
sbit RX_DR=sta^6;
sbit TX_DS=sta^5;
sbit MAX_RT=sta^4;
unchar TxAddr[]={0x34,0x43,0x10,0x10,0x01};//发送地址

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

/**********************NRF24L01初始化函数*******************************/
void NRF24L01Int()
{
	Ddelay(2);//让系统什么都不干
	CE=0; //待机模式1   
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

//unchar NRFWriteTxDate1(unchar RegAddr,unchar *TxData,unchar DateLen)
//{ //寄存器地址//写入数据存放变量//读取数据长度//用于发送
//   unchar BackDate,i;
//   CSN=0;
//   BackDate=NRFSPI(RegAddr);//写入要写入寄存器的地址
//   for(i=0;i<DateLen;i++)//写入数据
//     {
//	    NRFSPI(*TxData++);
//	 }   
//   CSN=1;
//   return(BackDate);
//   }

/*****************NRF设置为发送模式并发送数据******************************/
void NRFSetTxMode()
{		//发送模式
    CE=0; 
   	NRFWriteTxDate(W_REGISTER+TX_ADDR,TxAddr,TX_ADDR_WITDH);//写寄存器指令+接收地址使能指令+接收地址+地址宽度
	NRFWriteTxDate(W_REGISTER+RX_ADDR_P0,TxAddr,TX_ADDR_WITDH);//为了应答接收设备，接收通道0地址和发送地址相同 

	NRFWriteReg(W_REGISTER+RF_CH,0x20);       // 选择射频通道0x40
  	NRFWriteReg(W_REGISTER+RF_SETUP,0x0f);    // 数据传输率1Mbps，发射功率0dBm，低噪声放大器增益
		//******下面有关寄存器配置**************

  	NRFWriteReg(W_REGISTER+EN_AA,0x01);       // 使能接收通道0自动应答
  	NRFWriteReg(W_REGISTER+EN_RXADDR,0x01);   // 使能接收通道0
}
/*******************************************/
void NRF_Send(unchar *TxDate)
{
   	NRFWriteTxDate(W_TX_PAYLOAD,TxDate,TX_DATA_WITDH);//写入数据
  	NRFWriteReg(W_REGISTER+SETUP_RETR,0x0a);  // 自动重发延时等待250us+86us，自动重发10次
  	
        NRFWriteReg(W_REGISTER+CONFIG,0x0a);      // CRC使能，8位CRC校验，上电  
        CE=1;
}
//void NRF_Send1(unchar *TxData)
//{
//   	NRFWriteTxDate1(W_TX_PAYLOAD,TxData,TX_DATA_WITDH);//写入数据
//  	NRFWriteReg(W_REGISTER+SETUP_RETR,0x0a);  // 自动重发延时等待250us+86us，自动重发10次
//  	
//        NRFWriteReg(W_REGISTER+CONFIG,0x0a);      // CRC使能，8位CRC校验，上电  
//        CE=1;
//}
/****************************检测应答信号******************************/
unchar CheckACK()
{  //用于发射
	sta=NRFReadReg(R_REGISTER+STATUS);                    // 返回状态寄存器
	if(TX_DS||MAX_RT) //发送完毕中断
	{
	   NRFWriteReg(W_REGISTER+STATUS,0xff);  // 清除TX_DS或MAX_RT中断标志
	   CSN=0;
	   NRFSPI(FLUSH_TX);//用于清空FIFO ！！关键！！不然会出现意想不到的后果！！！大家记住！！  
       CSN=1; 
	   return(0);
	}
	else
	   return(1);
}