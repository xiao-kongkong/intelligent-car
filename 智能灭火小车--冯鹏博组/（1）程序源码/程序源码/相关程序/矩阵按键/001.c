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


uchar KeyScan()	//������ֵ���Ӻ���
{
	uchar cord_l,cord_h;//�������ߺ����ߵ�ֵ�Ĵ������
	P2 = 0x0f;//0000 1111
	if( (P2 & 0x0f) != 0x0f)//�ж��Ƿ��а�������
	{
		delay(5);//�������
		if( (P2 & 0x0f) != 0x0f)//�ж��Ƿ��а�������
		{
			  cord_h = P2 & 0x0f;// ��������ֵ
			  P2 = cord_l | 0xf0;
			  cord_l = P2 & 0xf0;// ��������ֵ
			  while( (P2 & 0xf0) != 0xf0 );//���ּ��
			  return (cord_l + cord_h);//���ؼ�ֵ��
		}	
	}
	return (cord_l + cord_h);//���ؼ�ֵ��	
}

void KeyPro()
{
	switch( KeyScan() )
	{
	 	//��һ�м�ֵ��	 //1���� 0����		  //��*��
		case 0xee: led = 1 ;		break;	   //1*1
		case 0xde: led = 0 ;		break;	   //1*2
		case 0xbe: led = 0 ;		break;	   //1*3

		
		//�ڶ��м�ֵ��
		case 0xed: led = 1 ;		break;	  //2*1
		case 0xdd: led = 0 ;		break;	  //2*2
		case 0xbd: led = 0 ;		break;	  //2*3


		//�����м�ֵ��
		case 0xeb: led = 1 ;		break;	   //3*1
		case 0xdb: led = 1 ;		break;	   //3*2
		case 0xbb: led = 0 ;		break;	   //3*3


	}	
}

void main()
{
	





	while(1)
	{
		
	 	KeyPro();//��ȡ��ֵ�벢���Ͳ�ͬ��ֵ���������ʾ
	}
}