#include <reg52.h>
#define uchar unsigned char
#define uint  unsigned int
sbit led = P3^2;

void delay(uint z)
{
	uint x,y;
	for(x = z; x > 0; x--)
		for(y = 114; y > 0 ; y--);
}


uchar KeyScan()	//带返回值的子函数
{
	uchar cord_l,cord_h;//声明列线和行线的值的储存变量
	P2 = 0x0f;//0000 1111
	if( (P2 & 0x0f) != 0x0f)//判断是否有按键按下
	{
		delay(5);//软件消抖
		if( (P2 & 0x0f) != 0x0f)//判断是否有按键按下
		{
			  cord_h = P2 & 0x0f;// 储存行线值
			  P2 = cord_l | 0xf0;
			  cord_l = P2 & 0xf0;// 储存列线值
			  while( (P2 & 0xf0) != 0xf0 );//松手检测
			  return (cord_l + cord_h);//返回键值码
		}	
	}
	return (cord_l + cord_h);//返回键值码	
}

void KeyPro()
{
	switch( KeyScan() )
	{
	 	//第一行键值码	 //1是灭 0是亮		  //行*列
		case 0xee: led = 1 ;		break;	   //1*1
		case 0xde: led = 0 ;		break;	   //1*2
		case 0xbe: led = 0 ;		break;	   //1*3

		
		//第二行键值码
		case 0xed: led = 1 ;		break;	  //2*1
		case 0xdd: led = 0 ;		break;	  //2*2
		case 0xbd: led = 0 ;		break;	  //2*3


		//第三行键值码
		case 0xeb: led = 1 ;		break;	   //3*1
		case 0xdb: led = 1 ;		break;	   //3*2
		case 0xbb: led = 0 ;		break;	   //3*3


	}	
}

void main()
{
	





	while(1)
	{
		
	 	KeyPro();//提取键值码并且送不同数值给数码管显示
	}
}